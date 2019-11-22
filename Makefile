CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++14 -ggdb


all: bin/main bin/test_inverted_index bin/test_document bin/test_query

clean:
	rm -rf bin/* .vscode/ipch

run: bin/main
	clear
	./bin/main

test_inverted_index: bin/test_inverted_index
	clear
	./bin/test_inverted_index

test_document: bin/test_document
	clear
	./bin/test_document

test_query: bin/test_query
	clear
	./bin/test_query

bin/Document.o: src/Document.cpp
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

bin/InvertedIndex.o: src/InvertedIndex.cpp
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

bin/Query.o: src/Query.cpp
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

bin/test_inverted_index: bin/Document.o bin/InvertedIndex.o bin/Query.o src/InvertedIndex.test.cpp
	$(CXX) $(CXX_FLAGS) -I include/ $^ -o $@

bin/test_document: bin/Document.o bin/InvertedIndex.o bin/Query.o src/Document.test.cpp
	$(CXX) $(CXX_FLAGS) -I include/ $^ -o $@

bin/test_query: bin/Document.o bin/InvertedIndex.o bin/Query.o src/Query.test.cpp
	$(CXX) $(CXX_FLAGS) -I include/ $^ -o $@

bin/main: bin/Document.o bin/InvertedIndex.o bin/Query.o src/main.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@
