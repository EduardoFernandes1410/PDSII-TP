#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include "Document.h"
#include "Word.h"
#include "InvertedIndex.h"
using namespace std;

int main (){
  set<Word> vocabulary;
  set<Document> docs;

  Word w1("batata");
  Word w2("frita");
  Word w3("gosto");
  Word w4("nusga");
  Word w5("batata");

  vocabulary.insert(w1);
  vocabulary.insert(w2);
  vocabulary.insert(w3);
  vocabulary.insert(w4);
  vocabulary.insert(w5);

  Document d1, d2, d3;

  try {
    d1 = Document("./documents/d1.txt");
    d2 = Document("./documents/d2.txt");
    d3 = Document("./documents/d3.txt");

    docs.insert(d1);
    docs.insert(d2);
    docs.insert(d3);
  } catch(...) {
    cout << "deu pau" << endl;
  }

  InvertedIndex index(docs);
  map<Word, map<Document, int> > invertedIndex = index.index();

  for(auto k : invertedIndex) {
    cout << k.first.name() << endl;

    for(auto v : k.second) {
      cout << "\t" << v.first.name() << " - " << v.second << endl;
    }
  }
}
