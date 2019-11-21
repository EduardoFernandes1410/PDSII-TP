#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "InvertedIndex.h"
#include "Document.h"

#include "doctest.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <cmath>

using std::string;

class Test {
public:
  static map<string, map<Document, int> > index(const InvertedIndex &i) {
    return  i.index_;
  }
};

TEST_SUITE("InvertedIndex") {  
  TEST_CASE("InvertedIndex()") {
    vector<Document> docs;
    Document doc("/test_documents/d1.txt");
    docs.push_back(doc);
    InvertedIndex i(docs);
    CHECK(Test::index(i)["A"][docs[0]] == 4);
  }

  TEST_CASE("index()") {
    vector<Document> docs;
    Document doc("/test_documents/d1.txt");
    docs.push_back(doc);
    InvertedIndex i(docs);
    CHECK(Test::index(i) == i.index);
  }

  TEST_CASE("getTf()") {
    vector<Document> docs;
    Document doc("/test_documents/d1.txt");
    docs.push_back(doc);
    InvertedIndex i(docs);
    CHECK(Test::index(i)["A"][docs[0]] == i.getTf("A", doc));
    CHECK(i.getTf("B", doc) == 0);
  }

  TEST_CASE("getIdf()") {
    vector<Document> docs;
    Document doc1("/test_documents/d1.txt");
    Document doc2("/test_documents/d2.txt");
    docs.push_back(doc1);
    docs.push_back(doc2);
    InvertedIndex i(docs);
    CHECK(i.getIdf("A", 2) == 0);
    CHECK(i.getIdf("B", 2) == 0);
  }
}