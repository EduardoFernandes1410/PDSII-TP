#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include "Document.h"
#include "Word.h"
using namespace std;

class Word;
class Document;

class InvertedIndex{
  public:
    // Recebe um vetor com os documentos e gera o indice invertido
    InvertedIndex(vector<Document> &docs);
    // Retorna o index
    map<Word, map<Document, int> > index();
    // Retorna tf de dada palavra em dado documento
    int getTf(Word target, Document &doc);
    // Retorna um int correspondente a quantidade de documentos que Word aparece
    int getNx(Word target);

  private:
    map<Word, map<Document, int> > index_;
};

#endif
