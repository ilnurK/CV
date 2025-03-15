CXX      := g++
STD      := -std=c++20
CXXFLAGS := -Wall -Werror -Wextra $(STD)

TARGET      := graph
TEST_TARGET := graph_tests

SRCS  := $(TARGET).cc main.cc
OBJS  := $(SRCS:.cc=.o)

TESTS       := graph_tests.cc $(TARGET).cc
TEST_OBJS   := $(TESTS:.cc=.o)

all: $(TARGET)

tests: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	@$(CXX) $(CXXFLAGS) $^ -o $@
	./$(TEST_TARGET)

$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) $^ -o $@
	./$(TARGET)

%.o: %.cc
	@$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)
