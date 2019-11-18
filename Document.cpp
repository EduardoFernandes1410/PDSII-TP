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
#include "InvertedIndex.h"
#include "Document.h"
#include "Word.h"
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

  while(fin >> word) {
    new_word.clear();
    for(int i = 0; i < word.size(); i++) {
      if(isalpha(word[i]) || isdigit(word[i]))
        new_word.push_back(tolower(word[i], loc));
    }
    if(new_word != "") (this->words_).push_back(new_word); 
  }
  fin.close();
};

Document::Document(string query, bool flag){
  cout << "CRIANDO O DOC QUERY \n";
  string new_word;
  locale loc;
  for(int i = 0; i < query.size(); i++){
    if(isalpha(query[i]) || isdigit(query[i]))
      new_word.push_back(tolower(query[i], loc));
    else if(query[i] == ' ' ){
      if(new_word != "") (this->words_).push_back(new_word);
      new_word.clear();
    }
  }
  if(new_word != "") (this->words_).push_back(new_word);
}


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


// N eh o numero de documentos em questao
void Document::makeCoords(InvertedIndex index, int N){
  int i = 0;
  for(auto word : index.vocabulary() ){
    this->coords_.push_back(word.tf(*this, index) * word.idf(N, index));
    i++;
  }
}


void Document::makeQueryCoords(InvertedIndex index, int N){
  vector<Document> querySet;
  querySet.push_back(*this);
  InvertedIndex queryIndex(querySet);
  int i = 0;
  for(auto word : index.vocabulary() ){
    this->coords_.push_back(word.tf(*this, queryIndex) * word.idf(N, index));
    i++;
  }
}

vector<double> Document::coords() const{
  return this->coords_;
};

double Document::cosSimilarity(Document &query){
  double numerator = 0, denominator, denominatorPt1 = 0, denominatorPt2 = 0;
  double W_dj, W_query;
  
  int i = 0;
  for(auto it : this->coords_ ){
    // cout << i;
    W_dj = this->coords_[i];
    // cout << "aaaaa";
    // printf("Query coords size: %d\n", query.coords().size());
    W_query = query.coords_[i];
    // cout << "bbb";
    numerator += (W_dj * W_query);
    // cout << "cccc";
    denominatorPt1 += pow(W_dj, 2);
    // cout << "dddd";
    denominatorPt2 += pow(W_query, 2);
    // cout << "eeee";
    i++;
  }
  denominator = (sqrt(denominatorPt1)*sqrt(denominatorPt2));

  return (numerator/denominator);
}