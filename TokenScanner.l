%option noyywrap

%{
	#include "parser.tab.h"
	#include "header.h"
%}

DIGIT 	  [0-9]
CONST 	  [a-m]
FUNCT     [n-z]
RELATION  [A-Z]
COMMA     ","
OPENPAR   "("
CLOSEPAR  ")"
AND 	"&"
IMPL 	"->"
TRUE 	"TRUE"|"true"
FALSE 	"FALSE"|"false"


%%
{CONST}  {
  printf("CONST: %s\n",yytext);
   yylval.name = strdup(yytext); return(CONST);
}

{FUNCT} {
  printf("FUNCT: %s\n",yytext);
	 yylval.name = strdup(yytext); return(FUNCT);
}
{RELATION} {
  printf("RELATION: %s\n",yytext);
	yylval.name = strdup(yytext); return(RELATION);
}
{COMMA} {
  return COMMA;
}
{OPENPAR} {
  printf("OPENPAR: %s\n",yytext);
  return OPENPAR;
}
{CLOSEPAR} {
  printf("CLOSEPAR: %s\n",yytext);
  return CLOSEPAR;
}
{AND} {
  printf("AND: %s\n",yytext);
	return AND;
}
{IMPL} {
	return IMPL;
}
{TRUE} {
  printf("TRUE: %s\n",yytext);
	return TRUE;
}
{FALSE} {
  printf("FALSE: %s\n",yytext);
  return FALSE;
}
\n {
	return NEWLINE;
}
[ ] {
	/*Skip blanks*/
}
. {
	return ERROR;
}


%%
