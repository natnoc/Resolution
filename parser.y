%{
	#include <stdio.h>

	extern int yyerror(char* err);
	extern FILE* yyin;
%}


%start formseq

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

%%

formseq: /* Empty */
    | NEWLINE formseq       {}
    | form  NEWLINE formseq {}
    | error NEWLINE formseq {};  /* After an error, start afresh */

form: left IMPL right

right: molec | FALSE

left: conj | TRUE

conj: molec | conj AND molec

molec: atom | term

atom: CONST | RELATION OPENPAR terms CLOSEPAR

terms: term | term COMMA terms

term: CONST | FUNCT OPENPAR terms CLOSEPAR

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
