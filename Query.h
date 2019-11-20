#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <locale>
#include <unordered_map>
#include "Word.h"
#include "InvertedIndex.h"
#include "Document.h"
using namespace std;

class Word;
class InvertedIndex;
class Document;

class Query : public Document {
  public:
    // Construtores
    Query(string query);
    // Gera coordenadas do vetor da query
    virtual void makeCoords(InvertedIndex index, int N) override;
    // Faz similaridade com todos os documentos
    double cosSimilarityAll(vector<Document> &docs);
    // Retorna multiset de similaridades
    multiset<pair<double, Document> > similarities() const;

  private:
    // Guarda as similaridades com todos os documentos
    multiset<pair<double, Document> > similarities_;
};

#endif
