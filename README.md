# Prims MST

A C++ implementation of Prim's algorithm for Minimum Spanning Trees, using a [Fibonacci Heap](https://github.com/MihajloVelickovic/FibonacciHeap) as the priority queue data structure of choice

## Prim's Algoritm
Prim's algorithm works like this:
```
Prim(graph, random_node)
    queue <- vertices(graph)
    mst <- create_empty_graph()
    for node in queue:
        key(node) <- ∞
    key(random_node) <- 0
    parent(random_node) <- NULL
    while empty(queue) = false
        node <- extract_min(queue)
        for edge in edges(node)
            neighbor <- dest(edge)
            if contains(queue, neighbor) = true and weight(graph, node, neighbor) < key(neighbor)
                parent(neighbor) <- node
                decrease_key(neighbor, weight(node, neighbor))
                insert_node(mst, neighbor)
                insert_edge(mst, node, neighbor, weight(graph, node, neighbor))
    return mst
```

This repository comes with a complete undirected graph implementation.

The Fibonacci Heap found in ```lib/fibheap``` is a static library compiled for
**nix* operating systems. For Windows, clone the linked repository, and modify the ```CMakeLists.txt``` file to compile it as a library, and replace ```libfibheap.a``` with your newly compiled ```libfibheap.lib```

## Example program
The example program found in ```src/main.cpp``` finds the MST for two different cases of input graphs, and measures the time taken. Afterwards, it prints:
- The name of the case (Random, Daisy Chain)
- ```N```
- ```k```
- Time taken to find MST in seconds

to a file found in ```data/output.txt```

### Both cases
- The graph consists of ```N``` nodes
-```N = 10^i``` for ```i = 2, 3, 4, 5```
-```k``` edges created between random nodes.
-```k=N*i``` for ```i = 2, 5, 10, 20, 33, 50```

### First case
- A random node is connected to every other node in the graph

### Second case
- The nodes form a [daisy-chain](https://www.wikiwand.com/en/Daisy_chain_(electrical_engineering))


