#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "Word.h"
#include "Document.h"
using namespace std;

class InvertedIndex{
  public:
    // Recebe um vetor com os documentos e gera o indice invertido
    InvertedIndex(set<Document> docs);
    // Retorna o index
    map<Word, map<Document, int> > index();
    // Retorna vocabulario
    set<Word> vocabulary();
    // Retorna um int correspondente a quantidade de documentos que Word aparece
    int getNx(Word target);
    // Retorna tf de dada palavra em dado documento
    int getTf(Word target, Document doc);

  private:
    map<Word, map<Document, int> > index_;
    set<Word> vocabulary_;
};

#endif
