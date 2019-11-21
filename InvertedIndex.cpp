#include "InvertedIndex.h"

// Construtor
InvertedIndex::InvertedIndex(vector<Document> &docs){
  vector<string> words;

  for(auto &doc : docs) {
    words = doc.words();

    for(auto &word : words) {
      Word w(word);
      this->index_[w][doc] += 1;
      // this->vocabulary_.insert(w);
    }
  }
}

// Retorna o indice
map<Word, map<Document, int> > InvertedIndex::index() {
  return this->index_;
}

// Retorna tf da palavra alvo em funcao do arquivo dado
int InvertedIndex::getTf(Word target, Document &doc) {
  return this->index_[target][doc];
}

int InvertedIndex::getNx(Word target){
  return this->index_[target].size();
}
