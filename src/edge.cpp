#include "edge.h"

Edge::Edge(uint32_t weight, Edge* edge, Node* dest)
    :m_Weight{weight}, m_Next{edge}, m_Dest{dest}{}

Edge::~Edge(){
    m_Next = nullptr;
    m_Dest = nullptr;
}

uint32_t Edge::get_weight() const{
    return m_Weight;
}

Edge* Edge::get_next() const{
    return m_Next;
}

Node* Edge::get_dest() const{
    return m_Dest;
}

void Edge::set_weight(uint32_t value){
    m_Weight = value;
}

void Edge::set_next(Edge* edge){
    m_Next = edge;
}

void Edge::set_dest(Node* dest){
    m_Dest = dest;
}
