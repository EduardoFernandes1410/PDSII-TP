#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "Document.h"
#include "doctest.h"
#include <math.h>

using namespace std;

class Test{
  public:
    static string name(const Document &w){
      return w.name_;
    }

    static vector<string> words(const Document &w){
      return w.words_;
    }

    static vector<double> coords(const Document &w){
      return w.coords_;
    }
};


TEST_SUITE("Document"){
  TEST_CASE("Document(string path)"){
		SUBCASE("Normal document"){
		  Document x("../test_documents/d1.txt");
		  CHECK(Test::name(x) == "../test_documents/d1.txt");
		  CHECK(Test::words(x)[0] == "a");
		  CHECK(Test::words(x)[1] == "a");
			CHECK(Test::words(x)[2] == "a");
			CHECK(Test::words(x)[3] == "b");
		}
		SUBCASE("Empty document"){
			Document x("../test_documents/empty_doc.txt");
			CHECK(Test::words(x).size() == 0);
		}

		SUBCASE("Invalid path"){
			int n;
			try{
				Document x("invalid path");
			}catch(...){
				n = 1;
			}
			CHECK(n == 1);
		}

  }

  TEST_CASE("operator <()"){
    Document x("../test_documents/d1.txt");
    Document y("../test_documents/d2.txt");
    CHECK(x<y);
		CHECK(!(y<x));
  }

  TEST_CASE("makeCoords()"){
    Document d1("../test_documents/d1.txt");
    Document d2("../test_documents/d2.txt");
    Document d3("../test_documents/d3.txt");
    Document d4("../test_documents/d4.txt");
		Document out_doc("../test_documents/out_doc.txt");
    vector<Document> docs;

    docs.push_back(d1);
    docs.push_back(d2);
    docs.push_back(d3);
    docs.push_back(d4);

    InvertedIndex index(docs);
    d1.makeCoords(index, 4);
    d2.makeCoords(index, 4);

    CHECK(floor(Test::coords(d1)[0] * pow(10,8) )/ pow(10,8) == 0.86304621);
    CHECK(floor(Test::coords(d1)[1] * pow(10,8) )/ pow(10,8) == 0.69314718);
    CHECK(floor(Test::coords(d1)[2] * pow(10,8) )/ pow(10,8) == 0);

    CHECK(floor(Test::coords(d2)[0] * pow(10,8) )/ pow(10,8) == 0.57536414);
    CHECK(floor(Test::coords(d2)[1] * pow(10,8) )/ pow(10,8) == 0);
    CHECK(floor(Test::coords(d2)[2] * pow(10,8) )/ pow(10,8) == 1.38629436);
		out_doc.makeCoords(index, 4);
		CHECK(floor(Test::coords(out_doc)[0] * pow(10,8) )/ pow(10,8) == 0);
    CHECK(floor(Test::coords(out_doc)[1] * pow(10,8) )/ pow(10,8) == 0);
    CHECK(floor(Test::coords(out_doc)[2] * pow(10,8) )/ pow(10,8) == 0);

  }

  TEST_CASE("cosSimilarity()"){
    Document d1("../test_documents/d1.txt");
    Document d2("../test_documents/d2.txt");
    Document d3("../test_documents/d3.txt");
    Document d4("../test_documents/d4.txt");
    Document out_doc("../test_documents/out_doc.txt");
    vector<Document> docs;

    docs.push_back(d1);
    docs.push_back(d2);
    docs.push_back(d3);
    docs.push_back(d4);

    InvertedIndex index(docs);
    d1.makeCoords(index, 4);
    d2.makeCoords(index, 4);
    out_doc.makeCoords(index,4);

    CHECK(d1.cosSimilarity(out_doc) == 0);
    CHECK(floor(d1.cosSimilarity(d2)*pow(10,8))/pow(10,8) == 0.29887432);
  }

  TEST_CASE("coords()"){
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
    d1.makeCoords(index, 4);
    d2.makeCoords(index, 4);
    
    CHECK(floor(d1.coords()[0] * pow(10,8) )/ pow(10,8) == 0.86304621);
    CHECK(floor(d1.coords()[1] * pow(10,8) )/ pow(10,8) == 0.69314718);
    CHECK(floor(d1.coords()[2] * pow(10,8) )/ pow(10,8) == 0);

		CHECK(floor(d2.coords()[0] * pow(10,8) )/ pow(10,8) == 0.57536414);
    CHECK(floor(d2.coords()[1] * pow(10,8) )/ pow(10,8) == 0);
    CHECK(floor(d2.coords()[2] * pow(10,8) )/ pow(10,8) == 1.38629436);
  }

  TEST_CASE("words()"){
    Document d1("../test_documents/d1.txt");
    CHECK(d1.words()[0] == "a");
    CHECK(d1.words()[1] == "a");
    CHECK(d1.words()[2] == "a");
    CHECK(d1.words()[3] == "b");
  }

  TEST_CASE("name()"){
    Document d1("../test_documents/d1.txt");
    CHECK(d1.name() == "../test_documents/d1.txt");
  }
}
