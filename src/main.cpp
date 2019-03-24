#include <iostream>
#include <vector>
#include "pdaToCfg.h"
#include "parser.tab.h"

extern int yylex();
extern int yyparse();
extern FILE * yyin;

using namespace std;

int main(){

  extern States        Q;
  extern Alphabet      Sigma;
  extern StackAlphabet Gamma;
  extern Transitions   delta;
  extern States        final_states;
  
  do {
	yyparse();
  } while(!feof(yyin));
  
  Grammar example = pda_to_cfg(Q, Sigma, Gamma, delta, final_states);
  cout << example;
	
  return 0;
}

