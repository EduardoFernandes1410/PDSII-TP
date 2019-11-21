#include "InvertedIndex.h"

// Construtor
InvertedIndex::InvertedIndex(vector<Document> &docs){
  for(auto &doc : docs) {
    for(auto &word : doc.words()) {
      this->index_[word][doc] += 1;
    }
  }
}

// Retorna o indice
unordered_map<string, map<Document, int> > InvertedIndex::index() {
  return this->index_;
}

// Retorna tf da palavra alvo em funcao do arquivo dado
int InvertedIndex::getTf(string target, Document &doc) {
  return this->index_[target][doc];
}

double InvertedIndex::getIdf(string target, int N) {
  int nx = this->index_[target].size();
  return (nx != 0) ? log((double) N / nx) : 0;
}
