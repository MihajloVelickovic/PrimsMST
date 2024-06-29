#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstddef>
#include "node.h"

class Graph{
private:
    Node* m_Start;
    size_t m_Size;

public:
    Graph();
    ~Graph();
    bool insert_node(uint32_t element);
    bool remove_node(uint32_t element);
    bool insert_edge(uint32_t first, uint32_t second, uint32_t weight);
    bool insert_edge_directed(uint32_t first, uint32_t second, uint32_t weight);
    bool remove_edge(uint32_t first, uint32_t second);
    bool is_empty() const;
    size_t get_size() const;
    Node* get_start() const;
    Node* find_node(uint32_t value) const;
    Node* find_node_key(uint32_t key) const;
    Edge* find_edge(Node* first, Node* second) const;
    void print(std::ostream& stream = std::cout) const;
    void set_keys_max();
    Graph prims_mst();

};

#endif
