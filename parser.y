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
	struct body* bd;
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
			clause_list* clsLst = toClauseList($<claus>1, ziel_claus_list);
			ziel_claus_list = clsLst;
		}
		| NEWLINE formseq       {}
    | error NEWLINE formseq {};  /* After an error, start afresh */

form: left IMPL right {
		printf("\nFormel eingelesen!\n");
		//comp_atom($<claus>$->bd->head,$<claus>$->bd->next->head);
		//Wenn linke Seite = true
		if($<bd>1 == NULL) {

		} else {
			//Wenn rechte Seite = false
			if ($<bd>3 == NULL) {

			//Wenn beide Seiten Formeln enthalten
			} else {

			}
		}
		}

right: atom {
			$<bd>$ = tobody($<atm>1, NULL);
			printf("\nRechts:\t");
			print_body($<bd>$);
		}
		| FALSE {
			printf("False");
			$<bd>$ = NULL;
		}

left: conj {
			printf("\nLinks:\t");
			$<claus>$ = toclause($<bd>1);
			print_clause($<claus>$);
		} | TRUE {
			printf("True");
			$<bd>$ = NULL;
		}

conj: atom {
			$<bd>$ = tobody($<atm>1, NULL);
			//print_body($<bd>$);
		}
		| atom AND conj {
			$<bd>$ = tobody($<atm>1, $<bd>3);
			//print_body($<bd>$);
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
  loeseFormel(ziel_claus_list, regel_claus_list);
  puts("\nFertig ;D\n");
  return 1;

}
