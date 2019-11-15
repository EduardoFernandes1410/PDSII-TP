#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>


  Document::Document(string path){
    fstream fileReader(path);
    if( fileReader.is_open() ){
      
    }
    this->wasRead_ = false;
  };

  vector<string> Document::words();

 

