#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

class Word;
class InvertedIndex;

class Document{
  public:
    // Construtores
    Document();

    Document(string path);

    Document(string query, bool flag);

    // Operador < para ser possivel colocar em um set
    bool operator<(const Document &x) const;

    // Retorna as palavras que o documento contem
    vector<string> words() const;

    // Retorna nome do documento
    string name() const;

    // PRE-REQUISITO: makeCoords já foi executado antes
    double cosSimilarity(Document &query);

    // Gera coordenadas do vetor do documento
    virtual void makeCoords(InvertedIndex index, int N);

    // TIRAR ISSO DEPOIS
    vector<double> coords() const;

  protected:
    // Nome do documento
    string name_;
    // Guarda as palavras, já filtradas, presentes no documento
    vector<string> words_;
    // Guarda o vetor no R_n com a importância  do documento para cada P_i
    vector<double> coords_;
};

#endif
