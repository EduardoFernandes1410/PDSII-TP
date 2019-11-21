#include "Document.h"

// Construtor vazio
Document::Document(){}

// Construtor usando path para arquivo
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
    for(int i = 0; i < (int) word.size(); i++) {
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

// N eh o numero de documentos em questao
void Document::makeCoords(InvertedIndex &index, int N){
  for(auto &word : index.index()) {
    this->coords_.push_back(index.getTf(word.first, *this) * index.getIdf(word.first, N));
  }
}

double Document::cosSimilarity(Document &query){
  double numerator = 0, denominator, denominatorPt1 = 0, denominatorPt2 = 0;
  double W_dj, W_query;

  int i = 0;
  for(auto &it : this->coords_ ){
    W_dj = it;
    W_query = query.coords_[i];
    numerator += (W_dj * W_query);
    denominatorPt1 += pow(W_dj, 2);
    denominatorPt2 += pow(W_query, 2);

    i++;
  }
  denominator = (sqrt(denominatorPt1)*sqrt(denominatorPt2));

  return (denominator != 0) ? (numerator / denominator) : 0;
}

// Retorna o vetor de coordenadas do documento
vector<double> Document::coords() const {
  return this->coords_;
};

// Retorna as palavras do documento
vector<string> Document::words() const {
  return this->words_;
}

// Retorna nome do documento
string Document::name() const {
  return this->name_;
}
