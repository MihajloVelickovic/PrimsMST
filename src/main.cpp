#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include "graph.h"

static uint8_t k_vals[] = {2, 5, 10, 20, 33, 50};

static std::string cases[] = {"Random", "Daisy chain"};

int main(){

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());

    std::ofstream output("../data/output.txt");

    for(auto test_case{0}; test_case < 2; ++test_case)
        for(auto i{100}; i <= 100000; i *= 10)
            for(auto val: k_vals){

                Graph graph;
                std::uniform_int_distribution<uint32_t> distribution(0 , i-1);

                while(graph.get_size() != i)
                    graph.insert_node(distribution(generator));

                if(test_case == 0){

                    Node* node{nullptr};
                    while(!node)
                        node = graph.find_node(distribution(generator));

                    for(auto s_node{graph.get_start()}; s_node; s_node = s_node->get_next())
                        graph.insert_edge(node->get_value(), s_node->get_value(), distribution(generator));

                    for(auto k{0}; k < val * i; ++k)
                        graph.insert_edge(distribution(generator), distribution(generator), distribution(generator));

                }

                else{

                    for(auto node{graph.get_start()}; node; node = node->get_next()){

                        if(node->get_next())
                            graph.insert_edge(node->get_value(), node->get_next()->get_value(), distribution(generator));
                        else
                            graph.insert_edge(node->get_value(), graph.get_start()->get_value(), distribution(generator));

                    }

                    for(auto k{0}; k < val * i; ++k)
                        graph.insert_edge(distribution(generator), distribution(generator), distribution(generator));

                }

                auto start = std::chrono::high_resolution_clock::now();
                auto mst{graph.prims_mst()};
                auto end = std::chrono::high_resolution_clock::now();

                auto prims_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


                output<<"Case: "<<cases[test_case]<<", N: "<<i<<", k: "<<val*i<<std::endl;
                output<<"Execution time: "<<(float)prims_duration.count() / 1000000<<"s"<<std::endl;

                output<<std::endl;
                output<<std::endl;

            }

    return 0;

}
