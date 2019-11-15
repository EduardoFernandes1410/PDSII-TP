#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "InvertedIndex.h"
using namespace std;

// Construtor
InvertedIndex::InvertedIndex(set<Document> docs){
  vector<string> words;

  for(auto doc : docs) {
    words = doc.words();

    for(auto word : words) {
      Word w(word);
      this->index_[w][doc] += 1;
    }
  }
}

// Retorna o indice
map<Word, map<Document, int> > InvertedIndex::index() {
  return this->index_;
}

// Retorna o vocabulario
set<Word> InvertedIndex::vocabulary() {
  return this->vocabulary_;
}

// Retorna tf da palavra alvo em funcao do arquivo dado
int InvertedIndex::getTf(Word target, Document doc) {
  return this->index_[target][doc];
}
