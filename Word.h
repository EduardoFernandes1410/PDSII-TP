#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "InvertedIndex.h"
#include "Document.h"
#include <math.h>
using namespace std;

class Document;
class InvertedIndex;

class Word {
  public:
    // Construtor
    Word(string name);
    // Operador < para ser possivel colocar em um set
    bool operator<(const Word &x) const;
    // Retorna o nome da palavra
    string name() const;
    // Retorna o 'tf' de uma palavra em funcao de um documento
    int tf(Document &doc, InvertedIndex &index) const;
    // Recebe o numero de documentos, e o indice invertido em questao
    double idf(int N, InvertedIndex &index) const;

  private:
    string name_;
};

#endif
