

#include "graph.h"

void calcGraph(const char* filename) {
    gmap graph;
    GraphParams gp;
    graph = getGraphFromFile(filename, gp);
    for (int i{}; i < gp.vertices; ++i) {
        std::cout << calcMinDistance(graph, gp.search, i) << '\n';
    }
}

gmap getGraphFromFile(const char* filename, GraphParams& gp) {
    gmap graph{};

    std::ifstream graph_file(filename, std::ios::in);
    if (!graph_file.is_open()) {
        throw std::invalid_argument("file not found");
    }

    graph_file >> gp.vertices;
    graph_file >> gp.edges;

    for (int i{}; i < gp.edges; ++i) {
        int key{-1}, value{-1};
        graph_file >> key >> value;
        if (key == -1 || value == -1) {
            throw std::runtime_error("incorrect file");
        }
        graph[key].push_back(value);
        graph[value].push_back(key);
    }

    graph_file >> gp.search;
    return graph;
}

int calcMinDistance(const gmap& graph, int search, int match) {
    int res{0};
    std::set<int> visited{};
    std::queue<int> upcoming;
    upcoming.push(search);
    int heigh_flag{-1};
    upcoming.push(heigh_flag);
    bool is_found{};
    while (upcoming.size() && !is_found) {
        int key = upcoming.front();
        upcoming.pop();
        if (key == match) {
            is_found = true;
        } else if (graph.contains(key) && !visited.contains(key)) {
            for (auto& n : graph.at(key)) {
                if (!visited.contains(n)) {
                    upcoming.push(n);
                }
            }
            visited.insert(key);
        }
        if (!upcoming.empty() && upcoming.front() == heigh_flag &&
            key != match) {
            res += 1;
            upcoming.pop();
            upcoming.push(heigh_flag);
        }
    }
    res = (is_found) ? res : 0;
    return res;
}