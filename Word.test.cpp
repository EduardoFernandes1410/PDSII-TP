#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "Word.h"
#include "doctest.h"

using std::string;

class Teste{
  public:
    static string name(const Word &w){
      return w.name_;
    }
};

// class Document{
//   public:
//     Document(){
//       name_ = "d1.txt";
//       words_.push_back("a");
//       words_.push_back("a");
//       words_.push_back("a");
//       words_.push_back("b");
//       coords_.push_back(0);
//       coords_.push_back(0);
//     }
//     vector<string> words(){
//       return words_;
//     }
//   protected:
//     string name_ ;
//     vector<string> words_;
//     vector<double> coords_;

//   friend class InvertedIndex;
// };

class Document{
  
};

class InvertedIndex{
  public:
    double getTf(Word target, Document doc){
      if(target.name() == "a"){
        return 3;
      }else if(target.name() == "b"){
        return 1;
      }else{
        return -1;
      }
    }
    
    double getNx(Word target){
      if(target.name() == "a"){
        return 1;
      }else if(target.name() == "b"){
        return 1;
      }else{
        return -1;
      }
    }
};

TEST_SUITE("Word"){
  TEST_CASE("Word(string name)"){
    Word x("a");
    CHECK(Teste::name(x) == "a");
  }

  TEST_CASE("name()"){
    Word x("a");
    CHECK(x.name() == "a");
  }

  TEST_CASE("operator<"){
    Word x("a");
    Word y("b");
    CHECK(x<y);
    CHECK(!(y<x));
  }

  TEST_CASE("tf(Document doc, InvertedIndex index"){
    Word x("a");
    Word y("b");
    InvertedIndex index;
    Document doc;
    CHECK(x.tf(doc, index) == 3);
    CHECK(y.tf(doc, index) == 1);
  }
}