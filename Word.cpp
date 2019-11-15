#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <math.h>

#include "Document.h"
#include "Word.h"
#include "InvertedIndex.h"

bool Word::operator<(Word x){}

int Word::tf(Document doc){
  int count = 0;
  for( int i = 0; i < doc.words().size(); i ++){
    if( doc.words()[i] == this->name_){
      count ++;
    }
  }
  return count;
}

double Word::idf(int N, InvertedIndex index){
  return log( N / index.get_nx(this));
}