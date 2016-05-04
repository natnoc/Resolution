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
    | NEWLINE formseq       {}
    | form  NEWLINE formseq {}
    | error NEWLINE formseq {};  /* After an error, start afresh */

form: left IMPL right

right: atom | FALSE

left: conj | TRUE

conj: atom | conj AND atom

atom: RELATION | RELATION OPENPAR terms CLOSEPAR

terms: term {
		$<termLst>$=toTermList($<trm>$, NULL);
		print_term_liste($<termLst>$);
		}
		| term COMMA terms

term: CONST {
			printf("\nConstant:\t%s\n", $<name>1);
			$<trm>$=toTerm($<name>1, NULL);
			print_term($<trm>$);
		} |
		FUNCT OPENPAR terms CLOSEPAR {
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

  return yyparse();
}
