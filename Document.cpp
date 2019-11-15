#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <locale>
#include <unordered_map>
#include <fstream>
#include "Document.h"
using namespace std;

// Construtor
Document::Document(string path){
  string word, new_word;
  locale loc;

  fstream fin(path);

  if(!fin.is_open()) {
    throw invalid_argument("invalid path");
  }

  while(true) {
    fin >> word;
    if(fin.eof()) break;

    new_word.clear();
    for(int i = 0; i < word.size(); i++) {
      if(isalpha(word[i]) || isdigit(word[i]))
        new_word.push_back(tolower(word[i], loc));
    }

    if(new_word != "") (this->words_).push_back(new_word);
  }

  fin.close();
};

// Operator <
bool Document::operator<(const Document &x) const {
  return this->name_ < x.name_;
}

void Document::make_coords(InvertedIndex index){
  int i = 0;
  for(auto word : index.vocabulary() ){
      this->coords_[i] = word->tf(*this, index) * (word->idf(vocabulary.size(), index));
    i++;
  }

}


// Retorna as palavras do documento
vector<string> Document::words() const {
  return this->words_;
}

Document::cosSimilarity(Document query){
    double numerator = 0, denominator, denominatorPt1 = 0, denominatorPt2 = 0;
    double W_dj, Wquery;

    for(int i=0; i<this->words().coords(); i++){
      Wdj = this->coords[i];
          Wquery = query.coords[i];
      numerator += (W_dj * W_query);
      denominatorPt1 += pow(W_dj, 2);
      denominatorPt2 += pow(W_query, 2);
    }

    denominator = (sqrt(denominatorPt1)*sqrt(denominatorPt2));

    return (numerator/denominator);
  };