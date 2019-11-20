#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include "Document.h"
#include "Word.h"
#include "Query.h"
#include "InvertedIndex.h"
using namespace std;

int main (){
  set<Word> vocabulary;
  vector<Document> docs;
  Document d1, d2, d3, d4;


  try {
    d1 = Document("./doc_pdf/d1.txt");
    d2 = Document("./doc_pdf/d2.txt");
    d3 = Document("./doc_pdf/d3.txt");
    d4 = Document("./doc_pdf/d4.txt");
    docs.push_back(d1);
    docs.push_back(d2);
    docs.push_back(d3);
    docs.push_back(d4);
  }catch(...) {
    cout << "deu pau" << endl;
  }

  // cout << "PRINTANDO OS CONTEUDOS DOS ARQUIVOS: \n";
  // for ( auto doc : docs){
  //   cout << "doc: " << doc.name() << "-> ";
  //   for(auto palavra : doc.words()){
  //     cout << palavra << " ";
  //   }
  //   cout << endl;
  // }

  InvertedIndex index(docs);
  map<Word, map<Document, int> > invertedIndex = index.index();

  // cout << "PRINTANDO O INDICE INVERTIDO: \n";
  // for(auto k : invertedIndex) {
  //   cout << k.first.name() << endl;

  //   for(auto v : k.second) {
  //     cout << "\t" << v.first.name() << " - " << v.second << endl;
  //   }
  // }

  int i = 1;
  for(auto doc = docs.begin(); doc != docs.end(); ++doc){
    doc->makeCoords(index, (int)docs.size());
    cout << "W_D" << i << ": ";
    for(auto w : doc->coords() ){
      cout << w << " ";
    }
    cout << endl;
    i++;
  }


  Query query("A B");
  query.makeCoords(index, (int)docs.size());
  cout << "W_query: ";
  for(auto w : query.coords() ){
    cout << w << " ";
  }
  cout << endl;

  cout << "CALCULANDO AS SIMILARIDADES: \n";
  query.cosSimilarityAll(docs);

  multiset<pair<double, Document> > sim = query.similarities();
  for(auto it = sim.rbegin(); it != sim.rend(); it++){
    cout << "sim(" << it->second.name() << ", Query): " << it->first << endl;
  }
  cout << endl;
}
