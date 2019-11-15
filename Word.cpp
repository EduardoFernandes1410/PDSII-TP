#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <math.h>

// #include "Document.h"
#include "Word.h"
// #include "InvertedIndex.h"

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
// int Word::tf(Document doc){
//}

// double Word::idf(int N, InvertedIndex index){
//   return log( N / index.get_nx(this));
// }
