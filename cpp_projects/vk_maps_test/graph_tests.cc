#include <cassert>
#include <sstream>

#include "graph.h"

int main() {
    constexpr int N{4};
    std::string dir{"tests/"};
    std::string test_file_pn{dir + "graph"};
    std::string answer_file_pn{dir + "answer_graph"};
    std::ostringstream out;
    std::streambuf* std_out = std::cout.rdbuf(out.rdbuf());
    for (int i{}; i < N; ++i) {
        std::string postfix{std::to_string(i) + std::string(".txt")};
        calcGraph((test_file_pn + postfix).data());
        std::ifstream answer_stream((answer_file_pn + postfix));
        std::istringstream value_stream(out.str());
        int value{}, answer{}, cr{};
        while (value_stream >> value) {
            answer_stream >> answer;
            if (value != answer) {
                std::cerr << "Assertion failed " << test_file_pn + postfix
                          << " on " << cr << " string"
                          << ": value = " << value << ", expected = " << answer
                          << std::endl;
            }

            assert(value == answer);
            ++cr;
        }
        out.str("");
        std::cout.rdbuf(std_out);
        std::cout << "test " << i << ": complete\n";
        std_out = std::cout.rdbuf(out.rdbuf());
    }
    std::cout.rdbuf(std_out);

    std::cout << "all tests completed" << std::endl;
    return 0;
}