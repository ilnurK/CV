
#include "graph.h"

int main() {
    try {
        const char* filename{"tests/graph3.txt"};
        calcGraph(filename);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "error occured" << std::endl;
    }
    return 0;
}