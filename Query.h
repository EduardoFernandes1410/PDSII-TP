#ifndef QUERY_H
#define QUERY_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>
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

    // Gera coordenadas do vetor do documento
    virtual void makeCoords(InvertedIndex index, int N) override;

    // Faz similaridade com todos os documentos
    double cosSimilarityAll(vector<Document> docs);

  private:
    // Guarda as similaridades com todos os documentos
    set<pair<double, Document> > similarities;
};

#endif
