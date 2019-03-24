%{
#include <stdio.h>
#include <stdlib.h>
#include "pdaToCfg.h"
extern int yylex();
extern int yyparse();
extern FILE * yyin;

extern States        Q;
extern Alphabet      Sigma;
extern StackAlphabet Gamma;
extern Transitions   delta;
extern States        final_states;

void yyerror(const char * s);
	%}

%union { char * StringType; }
%token ID COMMA ARROW SEMICOLON BAR
%type<StringType> ID
%%

start : states BAR alphabet BAR stack_alphabet BAR final_states BAR transitions {;}

states : ID { Q.insert($1); }
| ID COMMA states { Q.insert($1); }
;
alphabet : ID { Sigma.insert($1); }
|  ID COMMA alphabet { Sigma.insert($1); }
;
stack_alphabet : ID { Gamma.insert($1); }
|  ID COMMA stack_alphabet { Gamma.insert($1); }
;
final_states : ID { final_states.insert($1); }
| ID COMMA final_states { final_states.insert($1); }
;

transitions: 	transition { ; }
|	   	transition transitions { ; }
;
transition : ID COMMA ID COMMA ID ARROW ID COMMA ID SEMICOLON {
	delta[std::make_pair($1, std::make_pair($3, $5))].insert(std::make_pair($7, $9));
 }
;
%%

void yyerror(const char *s) {
  std::cout << "EEK, parse error!  Message: " << s << std::endl;
  // might as well halt now:
  exit(-1);
}
