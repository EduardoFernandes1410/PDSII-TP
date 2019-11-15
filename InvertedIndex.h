#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "Word.h"

class InvertedIndex{
  public:
    // Recebe um vetor com os documentos e gera o indice invertido
    InvertedIndex(vector<Document> docs );

    // Retorna um int correspondente a quantidade de documentos que Word aparece
    int get_nx(Word target);

  private:
    map<Word, unordered_map<Document, int> > index;

}
