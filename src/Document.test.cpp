#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "Document.h"
#include "doctest.h"

class Teste{
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
    Document x("/doc_pdf/d1.txt");
    CHECK(Teste::name(x) == "/doc_pdf/d1.txt");
    CHECK(Teste::words(x)[0] == "a");
    CHECK(Teste::words(x)[1] == "b");
  }

  TEST_CASE("operator <()"){
    Document x("/doc_pdf/d1.txt");
    Document y("/doc_pdf/d2.txt");
    CHECK(x<y);
  }

  TEST_CASE("makeCoords()"){
    Document d1("/doc_pdf/d1.txt");
    Document d2("/doc_pdf/d2.txt");
    Document d3("/doc_pdf/d3.txt");
    Document d4("/doc_pdf/d4.txt");
    vector<Document> docs;
    docs.push_back(d1);
    docs.push_back(d2);
    docs.push_back(d3);
    docs.push_back(d4);

    InvertedIndex index(docs);
    d1.makeCoords(index, 4);
    CHECK(Teste::coords(d1)[0] == 0.863046);
    CHECK(Teste::coords(d1)[1] == 0.693147);
    CHECK(Teste::coords(d1)[2] == 0);

    CHECK(Teste::coords(d2)[0] == 0.575364);
    CHECK(Teste::coords(d2)[1] == 0);
    CHECK(Teste::coords(d2)[2] == 1.38629);
  }

  TEST_CASE("coords()"){
    Document d1("/doc_pdf/d1.txt");
    Document d2("/doc_pdf/d2.txt");
    Document d3("/doc_pdf/d3.txt");
    Document d4("/doc_pdf/d4.txt");
    vector<Document> docs;
    docs.push_back(d1);
    docs.push_back(d2);
    docs.push_back(d3);
    docs.push_back(d4);

    InvertedIndex index(docs);
    d1.makeCoords(index, 4);
    CHECK(d1.coords()[0] == 0.863046);
    CHECK(d1.coords()[1] == 0.693147);
    CHECK(d1.coords()[2] == 0);
    CHECK(d2.coords()[0] == 0.575364);
    CHECK(d2.coords()[1] == 0);
    CHECK(d2.coords()[2] == 1.38629);
  }

  TEST_CASE("words()"){
    Document d1("/doc_pdf/d1.txt");
    CHECK(d1.words()[0] = "a");
    CHECK(d1.words()[1] = "a");
    CHECK(d1.words()[2] = "a");
    CHECK(d1.words()[3] = "b");
  }

  TEST_CASE("name()"){
    Document d1("/doc_pdf/d1.txt");
    CHECK(d1.name() = "/doc_pdf/d1.txt");
  }
}