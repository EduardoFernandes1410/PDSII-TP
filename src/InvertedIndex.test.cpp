#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "InvertedIndex.h"
#include "Document.h"

#include "doctest.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <cmath>

using std::string;
using std::map;

class Test {
public:
  static map<string, map<Document, int> > index(const InvertedIndex &i) {
    return  i.index_;
  }
};

bool operator==(const Document& x, const Document& y) {
  if( x.name() != y.name()) return false;
  if( x.words().size() != y.words().size()) return false;

  for(int i = 0; i < (int) x.words().size(); i++){
    if(x.words()[i] != y.words()[i]) return false;
  }
  return true;
}

TEST_SUITE("InvertedIndex") {
  TEST_CASE("InvertedIndex()") {
    vector<Document> docs;
    Document doc1("../test_documents/d1.txt");
    Document doc2("../test_documents/d2.txt");

    docs.push_back(doc1);
    docs.push_back(doc2);

    InvertedIndex i(docs);

    CHECK(Test::index(i)["a"][docs[0]] == 3);
    CHECK(Test::index(i)["a"][docs[1]] == 2);
    CHECK(Test::index(i)["b"][docs[0]] == 1);
    CHECK(Test::index(i)["c"][docs[1]] == 1);
  }

  TEST_CASE("index()") {
    vector<Document> docs;
    Document doc1("../test_documents/d1.txt");
    Document doc2("../test_documents/d2.txt");

    docs.push_back(doc1);
    docs.push_back(doc2);

    InvertedIndex i(docs);
    map<string, map<Document, int> > test = Test::index(i);
    map<string, map<Document, int> > res = i.index();

    REQUIRE(test.size() == res.size());

    for(auto words1 = test.begin(), words2 = res.begin();
         words1 != test.end();
         ++words1, ++words2){

      // Veririca se as palavras sao as mesmas
      CHECK(words1->first == words2->first);
      REQUIRE(words1->second.size() == words2->second.size());

      for(auto docs1 = words1->second.begin(), docs2 = words2->second.begin();
           docs1 != words1->second.end();
           ++docs1, ++docs2){

        // Verifica se as listas de documentos sao iguais
        CHECK(docs1->first == docs2->first);
        CHECK(docs1->second == docs2->second);
      }
    }
  }

  TEST_CASE("getTf()") {
    vector<Document> docs;
    Document doc1("../test_documents/d1.txt");
    Document doc2("../test_documents/d2.txt");
    Document doc3("../test_documents/d3.txt");

    docs.push_back(doc1);
    docs.push_back(doc2);

    InvertedIndex i(docs);

    CHECK(i.getTf("a", doc1) == 3);
    CHECK(i.getTf("a", doc2) == 2);
    CHECK(i.getTf("b", doc1) == 1);
    CHECK(i.getTf("b", doc2) == 0);
    CHECK(i.getTf("c", doc1) == 0);
    CHECK(i.getTf("c", doc2) == 1);

    // Testa palavra fora do vocabulario
    CHECK(i.getTf("d", doc1) == 0);

    // Teste documento nao indexado
    CHECK(i.getTf("a", doc3) == 0);
  }

  TEST_CASE("getIdf()") {
    vector<Document> docs;
    Document doc1("../test_documents/d1.txt");
    Document doc2("../test_documents/d2.txt");

    docs.push_back(doc1);
    docs.push_back(doc2);

    InvertedIndex i(docs);

    CHECK(i.getIdf("a", 2) == 0);
    CHECK(floor(i.getIdf("b", 2)*pow(10,8))/pow(10,8) == 0.69314718);
    CHECK(floor(i.getIdf("c", 2)*pow(10,8))/pow(10,8) == 0.69314718);

    // Testa palavra fora do vocabulario
    CHECK(floor(i.getIdf("d", 2)*pow(10,8))/pow(10,8) == 0.0);
  }
}
