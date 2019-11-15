#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <locale>
#include <unordered_map>
#include <fstream>
#include <math.h>

#include "Document.h"
#include "InvertedIndex.h"
using namespace std;

// Construtores
Document::Document(){}

Document::Document(string path){
  this->name_ = path;

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

// Retorna as palavras do documento
vector<string> Document::words() const {
  return this->words_;
}

// Retorna nome do documento
string Document::name() const {
  return this->name_;
}

double Document::cosSimilarity(Document query){
  double numerator = 0, denominator, denominatorPt1 = 0, denominatorPt2 = 0;
  double W_dj, W_query;

  int i = 0;
  for(auto it : this->coords_ ){
    W_dj = this->coords_[i];
    W_query = query.coords_[i];
    numerator += (W_dj * W_query);
    denominatorPt1 += pow(W_dj, 2);
    denominatorPt2 += pow(W_query, 2);
  }

  denominator = (sqrt(denominatorPt1)*sqrt(denominatorPt2));

  return (numerator/denominator);
  }

void Document::makeCoords(InvertedIndex index){
  int i = 0;
  for(auto word : index.vocabulary() ){
      this->coords_[i] = word.tf(*this, index) * (word.idf(index.vocabulary().size(), index));
    i++;
  }

}