#include <locale>
#include "Query.h"

Query::Query(string query){
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


void Query::makeCoords(InvertedIndex index, int N){
  vector<Document> querySet;
  querySet.push_back(*this);

  InvertedIndex queryIndex(querySet);

  for(auto word : index.vocabulary()) {
    this->coords_.push_back(word.tf(*this, queryIndex) * word.idf(N, index));
  }
}
