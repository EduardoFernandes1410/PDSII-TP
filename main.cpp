#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <iomanip>
#include "Document.h"
#include "Query.h"
#include "InvertedIndex.h"
using namespace std;

// Gera vetor com os paths de todos os arquivos do dateset
vector<string> getPaths() {
  vector<string> paths;
  string path;
  fstream fin("input.txt");

  if(!fin.is_open()) {
    throw invalid_argument("input file not found");
  }

  while(fin >> path) {
    paths.push_back(path);
  }
  fin.close();

  return paths;
}

// Gera vetor de documentos do dataset
vector<Document> getDocuments(vector<string> &paths) {
  vector<Document> docs;

  for(auto &path : paths) {
    try {
      Document doc(path);
      docs.push_back(doc);
    } catch(...) {}
  }

  return docs;
}

// Calcula as coordenadas de cada documento do dataset
void calculateCoordsDocs(InvertedIndex &index, vector<Document> &docs) {
  for(auto doc = docs.begin(); doc != docs.end(); ++doc)
    doc->makeCoords(index, (int)docs.size());
}

// Exibe resultados da busca
void displayResults(Query &query) {
  multiset<pair<double, Document> > sim = query.similarities();

  cout << "Aqui estão os seus resultados:" << endl << endl;
  int i = 0;
  for(auto it = sim.rbegin(); it != sim.rend() && i < 10; ++it, ++i){
    cout << fixed << setprecision(4) << "(" << it->first << ") - " << it->second.name() << endl;
  }
}

// Gera query
void getQuery(InvertedIndex index, vector<Document> docs) {
  string search;

  cout << "Insira a sua busca: ";
  getline(cin, search);
  cout << "Pesquisando..." << endl << endl;

  Query query(search);
  query.makeCoords(index, (int)docs.size());
  query.cosSimilarityAll(docs);

  displayResults(query);
}

int main() {
  cout << "===== BEM VINDO AO BUSCA1 =====" << endl;
  cout << "Aguarde enquanto geramos o índice de busca..." << endl << endl;

  // Obtem os paths de todos os arquivos do dataset
  vector<string> paths = getPaths();
  // for(auto path : paths)
  //   cout << path << endl;

  // Obtem lista de Documentos
  vector<Document> docs = getDocuments(paths);
  // for(auto doc : docs)
  //   cout << doc.name() << endl;

  // Cria indice invertido
  InvertedIndex index(docs);
  // for(auto k : index.index()) {
  //   cout << k.first << endl;
  //
  //   for(auto v : k.second) {
  //     cout << "\t" << v.first.name() << " - " << v.second << endl;
  //   }
  // }

  // Calcula as coordenadas dos documentos
  calculateCoordsDocs(index, docs);
  // int i = 0;
  // for(auto doc : docs){
  //   cout << "W_D" << i << ": ";
  //   for(auto w : doc.coords() ){
  //     cout << w << " ";
  //   }
  //   cout << endl;
  //   i++;
  // }

  // Gera query e exibe os resultados
  getQuery(index, docs);
}
