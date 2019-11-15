#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

class Document{
  public:
    // Construtor
    Document(string path);
    // Operador < para ser possivel colocar em um set
    bool operator<(const Document &x) const;
    // Retorna as palavras que o documento contem
    vector<string> words() const;

  private:
    // Nome do documento
    string name_;
    // Guarda as palavras, já filtradas, presentes no documento
    vector<string> words_;
    // Guarda o vetor no R_n com a importância  do documento para cada P_i
    vector<double> coords_;
};

#endif
