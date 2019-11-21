#include "Word.h"
#include <iostream>

using namespace std;
// Construtor
Word::Word(string name) {
  this->name_ = name;
}

// Operador <
bool Word::operator<(const Word &x) const {
  return this->name_ < x.name_;
}

// Nome da palavra
string Word::name() const {
  return this->name_;
}

int Word::tf(Document &doc, InvertedIndex &index) const{
  return index.getTf(*this, doc);
}

double Word::idf(int N, InvertedIndex &index) const{
  int nx = index.getNx(*this);
  return (nx != 0) ? log((double) N / nx) : 0;
}
