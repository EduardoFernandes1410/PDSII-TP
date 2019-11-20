#include "Query.h"

// Construtor
Query::Query(string query){
  string new_word;
  locale loc;

  for(int i = 0; i < query.size(); i++){
    if(isalpha(query[i]) || isdigit(query[i]))
      new_word.push_back(tolower(query[i], loc));

    else if(query[i] == ' ' ){
      if(new_word != "") (this->words_.push_back(new_word));
      new_word.clear();
    }
  }
  if(new_word != "") (this->words_.push_back(new_word));
}

// Gera as coordenadas do vetor da query
void Query::makeCoords(InvertedIndex index, int N) {
  // Cria novo invertedIndex apenas com as palavras da query
  vector<Document> querySet;
  querySet.push_back(*this);

  InvertedIndex queryIndex(querySet);

  for(auto word : index.vocabulary()) {
    this->coords_.push_back(word.tf(*this, queryIndex) * word.idf(N, index));
  }
}

// Faz similaridade com todos os documentos
double Query::cosSimilarityAll(vector<Document> &docs) {
  double curSim;

  for(auto doc : docs) {
    curSim = this->cosSimilarity(doc);
    this->similarities_.emplace(curSim, doc);
  }
}

// Retorna multiset de similaridades
multiset<pair<double, Document> > Query::similarities() const {
  return this->similarities_;
}
