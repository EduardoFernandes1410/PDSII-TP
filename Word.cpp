#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <math.h>
#include "InvertedIndex.h"
#include "Word.h"


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

int Word::tf(Document doc, InvertedIndex index){
  return index.getTf(*this, doc);
}

double Word::idf(int N, InvertedIndex index){
  return log( N / index.getNx(*this));
}