	#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "Query.h"
#include "doctest.h"
#include <math.h>

using namespace std;

class Test{
  public:
    static multiset<pair<double, Document> > similarities(const Query &w){
      return w.similarities_;
    }
};

bool operator==(const Document& x, const Document& y) {
  if( x.name() != y.name())return false;
  if( x.words().size() != y.words().size())return false;
  for(int i = 0; i < (int) x.words().size(); i++){
    if(x.words()[i] != y.words()[i])return false;
  }
  return true;
}

TEST_SUITE("Query"){
  TEST_CASE("Query(string query)"){
		SUBCASE("Normal query"){
		  Query x("making a query");
		  CHECK(x.words()[0] == "making");
		  CHECK(x.words()[1] == "a");
			CHECK(x.words()[2] == "query");
		}

		SUBCASE("Empty query"){
			Query x("");
			CHECK(x.words().size() == 0);
		}
  }


  TEST_CASE("makeCoords()"){
    Query query("A B");
    Query out_query("out");
    Document d1("../test_documents/d1.txt");
    Document d2("../test_documents/d2.txt");
    Document d3("../test_documents/d3.txt");
    Document d4("../test_documents/d4.txt");

    vector<Document> docs;
    docs.push_back(d1);
    docs.push_back(d2);
    docs.push_back(d3);
    docs.push_back(d4);
    InvertedIndex index(docs);
    query.makeCoords(index, 4);
    out_query.makeCoords(index, 4);

    CHECK(floor(query.coords()[0] * pow(10,8) )/ pow(10,8) == 0.28768207);
    CHECK(floor(query.coords()[1] * pow(10,8) )/ pow(10,8) == 0.69314718);
    CHECK(floor(query.coords()[2] * pow(10,8) )/ pow(10,8) == 0);

    CHECK(floor(out_query.coords()[0] * pow(10,8) )/ pow(10,8) == 0);
    CHECK(floor(out_query.coords()[1] * pow(10,8) )/ pow(10,8) == 0);
    CHECK(floor(out_query.coords()[2] * pow(10,8) )/ pow(10,8) == 0);

  }

  TEST_CASE("cosSimilarityAll()"){
    Query query("A B");
    Query out_query("out");
    Document d1("../test_documents/d1.txt");
    Document d2("../test_documents/d2.txt");
    Document d3("../test_documents/d3.txt");
    Document d4("../test_documents/d4.txt");

    vector<Document> docs;
    docs.push_back(d1);
    docs.push_back(d2);
    docs.push_back(d3);
    docs.push_back(d4);
    InvertedIndex index(docs);
    query.makeCoords(index, 4);
    out_query.makeCoords(index, 4);

    for(auto &doc : docs){
      doc.makeCoords(index, 4);
    }

    query.cosSimilarityAll(docs);
    out_query.cosSimilarityAll(docs);

    for( auto similarity : Test::similarities(query)){
      if( (similarity.second) == docs[0]) CHECK(floor(similarity.first*pow(10,8))/pow(10,8) == 0.87722689);
      if( (similarity.second) == docs[1]) CHECK(floor(similarity.first*pow(10,8))/pow(10,8) == 0.14694410);
      if( (similarity.second) == docs[2]) CHECK(floor(similarity.first*pow(10,8))/pow(10,8) == 0.38333288);
      if( (similarity.second) == docs[3]) CHECK(floor(similarity.first*pow(10,8))/pow(10,8) == 0.92361025);
    }

    for( auto similarity : Test::similarities(out_query)){
       CHECK(similarity.first == 0);
    }
  }

  TEST_CASE("similarities()"){
    Query query("A B");
    Document d1("../test_documents/d1.txt");
    Document d2("../test_documents/d2.txt");
    Document d3("../test_documents/d3.txt");
    Document d4("../test_documents/d4.txt");

    vector<Document> docs;
    docs.push_back(d1);
    docs.push_back(d2);
    docs.push_back(d3);
    docs.push_back(d4);
    InvertedIndex index(docs);
    query.makeCoords(index, 4);

    for(auto &doc : docs){
      doc.makeCoords(index, 4);
    }

    query.cosSimilarityAll(docs);
    for( auto similarity : query.similarities()){
      if( (similarity.second) == docs[0]) CHECK(floor(similarity.first*pow(10,8))/pow(10,8) == 0.87722689);
      if( (similarity.second) == docs[1]) CHECK(floor(similarity.first*pow(10,8))/pow(10,8) == 0.14694410);
      if( (similarity.second) == docs[2]) CHECK(floor(similarity.first*pow(10,8))/pow(10,8) == 0.38333288);
      if( (similarity.second) == docs[3]) CHECK(floor(similarity.first*pow(10,8))/pow(10,8) == 0.92361025);
    }
  }
}
