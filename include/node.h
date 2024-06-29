#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <limits>
#include "edge.h"

class Node{
private:
    uint32_t m_Value;
    Node* m_Next;
    Edge* m_Adj;
    int32_t m_Key;

public:
    Node(uint32_t value, Node* next = nullptr, Edge* adj = nullptr, int32_t key = std::numeric_limits<int32_t>::min());
    ~Node();
    uint32_t get_value() const;
    Node* get_next() const;
    Edge* get_adj() const;
    int32_t get_key() const;
    void set_value(int32_t value);
    void set_next(Node* next);
    void set_adj(Edge* adj);
    void set_key(int32_t key);

 };

#endif
