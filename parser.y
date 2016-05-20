%{
	#include <stdio.h>
	#include "header.h"

	clause_list* ziel_claus_list = NULL;
	clause_list* regel_claus_list = NULL;

	extern int yyerror(char* err);
	extern FILE* yyin;
%}

%union{
	char* name;
	struct clause* claus;
	struct atom* atm;
	struct term_list* termLst;
	struct term* trm;
	struct atom_list* atmList;
}


%start start

%token CONST
%token FUNCT
%token RELATION
%token COMMA
%token OPENPAR
%token CLOSEPAR
%token AND
%token IMPL
%token TRUE
%token FALSE
%token NEWLINE
%token ERROR
%token exit_command

%%

start: formseq {
	printf("Start\n");

}

formseq: /* Empty */
    | form  NEWLINE formseq {

		}
	| NEWLINE formseq       {}
    	| error NEWLINE formseq {};  /* After an error, start afresh */

form: left IMPL right {
			printf("\nFormel eingelesen!\n");


			$<claus>$ = toclause($<atmList>1,$<atm>3);

		

			if($<claus>$->head == NULL) {
				ziel_claus_list = toClauseList($<claus>$, ziel_claus_list);
			} else {
					regel_claus_list = toClauseList($<claus>$, regel_claus_list);
				}

		}

right: atom {
			$<atm>$ = $<atm>1;
			//$<bd>$ = tobody($<atm>1, $<bd>$);
			printf("\nRechts:\t");
			//print_body($<bd>$);
		}
		| FALSE {
			printf("False");
			//$<bd>$ = tobody(NULL, $<bd>$);
			//$<bd>$->isZielClause = TRUE;
			
			$<atm>$ = NULL;
		}

left: conj {
			printf("\nLinks:\t");
			//$<claus>$ = toclause($<atmList>1, NULL);
			$<atmList>$ = $<atmList>1;
			//print_clause($<claus>$);
		} | TRUE {
			printf("True");
			$<atmList>$ = NULL;
		}

conj: atom {
			//$<bd>$ = tobody($<atm>1, NULL);
			//print_body($<bd>$);
			$<atmList>$ = toAtomList($<atm>1, NULL);
		}
		| atom AND conj {
			//$<bd>$ = tobody($<atm>1, $<bd>3);
			//print_body($<bd>$);
			$<atmList>$ = toAtomList($<atm>1, $<atmList>3);
		}

atom: RELATION {
			$<atm>$ = toAtom($<name>1, NULL);
			//print_atom($<atm>$);
		}
		| RELATION OPENPAR terms CLOSEPAR {
			$<atm>$ = toAtom($<name>1, $<termLst>3);
			//print_atom($<atm>$);
		}

terms: term {
		$<termLst>$ = toTermList($<trm>1, NULL);
		//print_term_liste($<termLst>$);
		}
		| term COMMA terms {
		$<termLst>$=toTermList($<trm>1, $<termLst>3);
		}

term: CONST {
			//printf("\nConstant:\t%s\n", $<name>1);
			$<trm>$=toTerm($<name>1, NULL);
			//print_term($<trm>$);
		} |
		FUNCT OPENPAR terms CLOSEPAR {
			//printf("\nFunction:\t%s\n", $<name>1);
			$<trm>$=toTerm($<name>1, $<termLst>3);
			//print_term($<trm>$);
		}

%%

int yyerror(char* err)
{
   printf("Error: %s\n", err);
   return 0;
}


int main (int argc, char* argv[])
{
  ++argv, --argc;  /* skip over program name */
   if ( argc > 0 )
      yyin = fopen( argv[0], "r" );
   else
      yyin = stdin;

  yyparse();
	
  puts("-------------\n Starte Lösen\n-----------------");
  
  
  /*
 clause_list* ziel_claus_list_tmp = regel_claus_list; 
 while(ziel_claus_list_tmp != NULL){
  	//print_clause(ziel_claus_list_tmp->claus);
	puts("Keine Lust mehr");
	ziel_claus_list_tmp = ziel_claus_list_tmp->next;	
  }*/
  
  loeseFormel(ziel_claus_list, regel_claus_list);
  
  puts("\nFertig ;D\n");
  return 1;

}
