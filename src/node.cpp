#include "node.h"

Node::Node(uint32_t value, Node *next, Edge *adj, int32_t key)
    :m_Value{value}, m_Next{next}, m_Adj{adj}, m_Key{key}{}

Node::~Node(){
    m_Next = nullptr;
    m_Adj = nullptr;
}

uint32_t Node::get_value() const{
    return m_Value;
}

Node* Node::get_next() const{
    return m_Next;
}

Edge* Node::get_adj() const{
    return m_Adj;
}

int32_t Node::get_key() const{
    return m_Key;
}

void Node::set_value(int32_t value){
    m_Value = value;
}

void Node::set_next(Node* next){
    m_Next = next;
}

void Node::set_adj(Edge* adj){
    m_Adj = adj;
}

void Node::set_key(int32_t key){
    m_Key = key;
}
