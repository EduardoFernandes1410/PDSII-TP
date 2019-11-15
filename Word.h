#ifndef WORD_H
#define WORD_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

class Word {
  public:
    // Construtor
    Word(string name);
    // Operador < para ser possivel colocar em um set
    bool operator<(const Word &x) const;
    // Retorna o nome da palavra
    string name() const;

  int tf(Document doc, InvertedIndex index);

  double idf(int N, InvertedIndex index);

  private:
    string name_;


};

#endif
