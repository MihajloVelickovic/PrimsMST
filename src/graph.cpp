#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "graph.h"
#include "fibheap.h"

Graph::Graph()
    :m_Start{nullptr}, m_Size{0}{}

Graph::~Graph(){
    while(!is_empty())
        remove_node(m_Start->get_value());
}

bool Graph::insert_node(uint32_t element){

    if(find_node(element))
        return false;

    auto new_node = new Node{element, m_Start};
    m_Start = new_node;
    ++m_Size;
    return true;

}

bool Graph::remove_node(uint32_t element){

    if(is_empty())
        return false;

    auto to_del{find_node(element)};
    if(!to_del)
        return false;

    for(auto node{m_Start->get_next()}; node; node = node->get_next())
        remove_edge(node->get_value(), to_del->get_value());

    Edge* prev{nullptr};
    for(auto edge{to_del->get_adj()}; edge; edge = prev){
        prev = edge->get_next();
        delete edge;
    }

    if(m_Start == to_del)
        m_Start = to_del->get_next();

    else{

        auto node{m_Start->get_next()};
        for(; node->get_next() != to_del; node = node->get_next());
        node->set_next(to_del->get_next());

    }

    delete to_del;
    --m_Size;
    return true;

}

bool Graph::insert_edge(uint32_t first, uint32_t second, uint32_t weight){
    return insert_edge_directed(first, second, weight) &&
           insert_edge_directed(second, first, weight);
}

bool Graph::insert_edge_directed(uint32_t first, uint32_t second, uint32_t weight){

    if(first == second)
        return false;

    auto first_node {find_node(first)},
         second_node{find_node(second)};

    if(!first_node || !second_node)
        return false;

    if(find_edge(first_node, second_node))
        return false;

    auto new_edge = new Edge{weight, first_node->get_adj(), second_node};
    first_node->set_adj(new_edge);
    return true;

}

bool Graph::remove_edge(uint32_t first, uint32_t second){

    if(is_empty())
        return false;

    auto first_node {find_node(first)},
         second_node{find_node(second)};

    if(!find_edge(first_node, second_node))
        return false;

    Edge* prev{nullptr};
    for(auto edge_p{first_node->get_adj()}; edge_p; edge_p = edge_p->get_next()){

        if(edge_p->get_dest() == second_node){

            if(!prev){
                first_node->set_adj(edge_p->get_next());
                delete edge_p;
                return true;
            }
            else{
                prev->set_next(edge_p->get_next());
                delete edge_p;
                return true;
            }

        }
        else
            prev = edge_p;

    }

    return false;

}

bool Graph::is_empty() const{
    return m_Size <= 0;
}

size_t Graph::get_size() const{
    return m_Size;
}

Node* Graph::get_start() const{
    return m_Start;
}

Node* Graph::find_node(uint32_t value) const{

    for(auto node{m_Start}; node; node = node->get_next())
        if(node->get_value() == value)
            return node;

    return nullptr;

}

Node* Graph::find_node_key(uint32_t key) const{

    for(auto node{m_Start}; node; node = node->get_next())
        if(node->get_key() == key)
            return node;

    return nullptr;

}

Edge* Graph::find_edge(Node* first, Node* second) const{

    if(!first || !second)
        return nullptr;

    for(auto edge{first->get_adj()}; edge; edge = edge->get_next())
        if(edge->get_dest() == second)
            return edge;

    return nullptr;

}

void Graph::print(std::ostream& stream) const{

    for(auto node{m_Start}; node; node = node->get_next()){

        stream<<node->get_value()<<" | ";

        for(auto edge{node->get_adj()}; edge; edge = edge->get_next())
            stream<<edge->get_dest()->get_value()<<" -> ";

        stream<<std::endl;
    }

}

void Graph::set_keys_max(){
    for(auto node{m_Start}; node; node = node->get_next())
        node->set_key(std::numeric_limits<int32_t>::max());
}

Graph Graph::prims_mst(){

    std::srand(std::time(nullptr));

    Graph mst;
    FibHeap heap;

    set_keys_max();

    for(auto node{m_Start}; node; node = node->get_next())
        heap.insert(node->get_key());

    auto heap_min{heap.find_node(heap.find_min())};
    heap_min->set_key(0);
    heap_min->set_parent(nullptr);

    auto random_count{std::rand() % get_size()};

    auto random_node{m_Start};
    for(int i{0}; i < random_count; ++i)
        random_node = random_node->get_next();

    random_node->set_key(0);

    while(!heap.is_empty()){

        auto min{new FibNode{heap.find_min()}};
        min->set_parent(heap.find_node(heap.find_min())->get_parent());

        auto min_node{find_node_key(min->get_key())};

        heap.extract_min();

        mst.insert_node(min_node->get_value());


        if(min->get_parent()){

            auto parent{find_node_key(min->get_parent()->get_key())};
            auto edge{find_edge(min_node, parent)};

            if(edge){
                mst.insert_node(parent->get_value());
                mst.insert_edge(parent->get_value(), min_node->get_value(), edge->get_weight());
            }

        }

        for(auto edge{min_node->get_adj()}; edge; edge = edge->get_next()){

            auto dest{edge->get_dest()};
            auto dest_node{heap.find_node(dest->get_key())};

            if(dest_node && edge->get_weight() <= dest->get_key()){

                dest_node->set_key(edge->get_weight());
                dest_node->set_parent(min);

                dest_node->set_key(edge->get_weight());
                dest->set_key(edge->get_weight());
                mst.insert_node(dest->get_value());
                mst.insert_edge(min_node->get_value(), dest->get_value(), edge->get_weight());

            }

        }

    }

    return mst;

}
