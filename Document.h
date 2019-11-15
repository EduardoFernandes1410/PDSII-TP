#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

class Document{
  public:
    Document::Document(string path);

    vector<string> Document::words();

  private:
    // Guarda as palavras, já filtradas, presentes no documento
    vector<string> words_;

    // Guarda o vetor no R_n com a importância  do documento para cada P_i
    vector<double> coords_;

}