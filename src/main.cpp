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
void getPaths(vector<string> &paths) {
  string path;
  fstream fin("../input.txt");

  if(!fin.is_open()) {
    throw invalid_argument("input file not found");
  }

  while(fin >> path) {
    paths.push_back(path);
  }
  fin.close();
}

// Gera vetor de documentos do dataset
void getDocuments(vector<string> &paths, vector<Document> &docs) {
  for(auto &path : paths) {
    try {
      Document doc(path);
      docs.push_back(doc);
    } catch(...) {}
  }
}

// Checa se algum documento foi indexado
void checkDocuments(vector<Document> &docs) {
  if(docs.size() > 0) {
    cout << docs.size() << " documento(s) encontrados(s)..." << endl;
  } else {
    cout << "ERRO! Nenhum documento encontrado." << endl;
    exit(-1);
  }
}

// Calcula as coordenadas de cada documento do dataset
void calculateCoordsDocs(InvertedIndex &index, vector<Document> &docs) {
  for(auto doc = docs.begin(); doc != docs.end(); ++doc)
    doc->makeCoords(index, (int)docs.size());

  cout << "Indexação concluída com sucesso." << endl << endl;
}

// Exibe resultados da busca
void displayResults(Query &query, int numRes) {
  multiset<pair<double, Document> > sim = query.similarities();

  if(sim.rbegin()->first == 0)
    cout << "Nenhum resultado encontrado." << endl;
  else
    cout << "Aqui estão os seus resultados:" << endl << endl;

  int i = 0;
  for(auto it = sim.rbegin(); it != sim.rend() && i < numRes; ++it, ++i){
    if(it->first > 0.0)
      cout << fixed << setprecision(4) << "(" << it->first << ") - " << it->second.name() << endl;
    else
      break;
  }
}

// Roda uma query
void runQuery(InvertedIndex index, vector<Document> docs) {
  string search, strMaxRes, ctrl = "s";
  int numMaxRes;
  locale loc;

  // Obtem query do usuario
  while(ctrl == "s" || ctrl == "S") {
    cout << "Insira a sua busca: ";
    cin.sync();
    getline(cin, search);

    do {
      cout << "Insira o numero máximo de resutados que deseja ver: ";
      getline(cin, strMaxRes);

      stringstream(strMaxRes) >> numMaxRes;
      if(numMaxRes <= 0) cout << "Valor inválido" << endl;
    } while(numMaxRes <= 0);

    cout << "Pesquisando..." << endl << endl;

    // Cria objeto query e calcula suas propriedades
    Query query(search);
    query.makeCoords(index, (int)docs.size());
    query.cosSimilarityAll(docs);

    // Exibe os resultados da busca
    displayResults(query, numMaxRes);

    cout << "\nDeseja realizar mais uma busca? [S/n] ";
    getline(cin, ctrl);
  }
}

// Inicializa o programa, obtendo os caminhos para o dataset
void init(vector<string> &paths) {
  cout << "===== BEM VINDO AO BUSCA1 =====" << endl;
  cout << "Aguarde enquanto geramos o índice de busca..." << endl;

  try {
    getPaths(paths);
  } catch(...) {
    cout << "ERRO! Não foi possível abrir o arquivo com o caminho para o dataset." << endl;
    exit(-1);
  }
}

int main() {
  // Inicializa o programa
  vector<string> paths;
  init(paths);

  // Obtem lista de Documentos
  vector<Document> docs;
  getDocuments(paths, docs);
  checkDocuments(docs);

  // Cria indice invertido
  InvertedIndex index(docs);

  // Calcula as coordenadas dos documentos
  calculateCoordsDocs(index, docs);

  // Gera query e exibe os resultados
  runQuery(index, docs);
}
