#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <unordered_map>
#include <fstream>
#include <locale>
#include "InvertedIndex.h"
using namespace std;

class Word;
class InvertedIndex;

class Document {
  public:
    // Construtor vazio
    Document();
    // Construtor usando path para arquivo
    Document(string path);
    // Operador < para ser possivel colocar em um set
    bool operator<(const Document &x) const;
    // PRE-REQUISITO: makeCoords já foi executado antes
    double cosSimilarity(Document &query);
    // Gera coordenadas do vetor do documento
    virtual void makeCoords(InvertedIndex &index, int N);
    // Retorna o vetor de coordenadas do documento
    vector<double> coords() const;
    // Retorna as palavras que o documento contem
    vector<string> words() const;
    // Retorna nome do documento
    string name() const;

  protected:
    // Nome do documento
    string name_;
    // Guarda as palavras, já filtradas, presentes no documento
    vector<string> words_;
    // Guarda o vetor no R_n com a importância  do documento para cada P_i
    vector<double> coords_;

  friend class Test;
};

#endif
