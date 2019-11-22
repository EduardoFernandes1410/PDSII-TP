#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include "Document.h"
using namespace std;

class Word;
class Document;

class InvertedIndex{
  public:
    // Recebe um vetor com os documentos e gera o indice invertido
    // PRE-REQUISITO: o vetor de documentos nao esta vazio
    InvertedIndex(vector<Document> &docs);
    // Retorna o index
    map<string, map<Document, int> > index();
    // Retorna tf de dada palavra em dado documento
    int getTf(string target, Document &doc);
    // Retorna o idf de uma palavra
    double getIdf(string target, int N);

  private:
    map<string, map<Document, int> > index_;

  friend class Test;
};

#endif
