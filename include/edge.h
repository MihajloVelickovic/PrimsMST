#ifndef EDGE_H
#define EDGE_H

#include <cstdint>

class Node;

class Edge{
private:
    uint32_t m_Weight;
    Edge* m_Next;
    Node* m_Dest;

public:
    Edge(uint32_t weight, Edge* edge = nullptr, Node* dest = nullptr);
    ~Edge();
    uint32_t get_weight() const;
    Edge* get_next() const;
    Node* get_dest() const;
    void set_weight(uint32_t value);
    void set_next(Edge* edge);
    void set_dest(Node* dest);

};

#endif
