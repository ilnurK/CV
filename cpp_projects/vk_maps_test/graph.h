#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

using gmap = std::unordered_map<int, std::vector<int>>;

struct GraphParams {
    int vertices{};
    int edges{};
    int search{};
};

void calcGraph(const char* filename);
int calcMinDistance(const gmap& graph, int search, int match);
gmap getGraphFromFile(const char* filename, GraphParams& gp);
