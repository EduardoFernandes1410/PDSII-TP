#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include "Document.h"
#include "Word.h"
// #include "InvertedIndex.h"
using namespace std;

int main (){
  set<Word> vocabulary;
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

  // for(auto i : vocabulary) {
  //   cout << i.name() << endl;
  // }
  // cout << vocabulary.find(w1)->name() << endl;

  try {
    Document d1("./documents/59909");

    vector<string> words = d1.words();
    for(auto i : words) {
      cout << i << endl;
    }
  } catch(...) {
    cout << "deu pau" << endl;
  }
}
