#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include "Words.h"

class InvertedIndex{
  public:

    // Recebe um vetor com os paths dos arquivos e gera o indice invertido
    InvertedIndex(vector<Document> docs );

    // Retorna um int correspondente a quantidade de documentos que Word aparece
    int get_nx(Word target);

  private:
    map<Word, unordered_map<string, int> > index;
    
}
