#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

class Word{
  public:
    bool operator<(Word x);

    int tf( Document doc);

    // Recebe o numero de documentos, e o indice invertido em questao
    double idf(int N, InvertedIndex index);

  private:
    string name_;

    // A quantidade de documentos que Px apareceu
  

    // 
    // unordered_map<Document, double> coord;
}