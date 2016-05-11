
#include <stdio.h>

typedef struct clause_list{
	struct clause* claus;
	struct clause_list* next;
}clause_list;

typedef struct clause{
	//struct atom* head;
	struct body* bd;
	//struct clause* next;
}clause;

typedef struct body{
	struct atom* head;
	struct body* next;
}body;

typedef struct atom{
	char* predSym;
	struct term_list* trm_lst;
}atom;

typedef struct term_list{
	struct term* trm;
	struct term_list* next;
}term_list;

typedef struct term{
	char* fOrConst;
	struct term_list* argm;
}term;


//clause* toclause(atom* atm, body* bd, clause* next);
clause_list* toClauseList(clause* claus, clause_list* next);
clause* toclause(body* bd);
atom* toAtom(char* prSym, term_list* trmList);
term_list* toTermList(term* trm, term_list* next);
term* toTerm(char* fOrC, term_list* arg);
//function* toFunction(char* fOrC, term_list* arg, function* next);
body* tobody(atom* head, body* bd);

char* print_term(term* trm);
char* print_term_liste(term_list* trm_lst);
char* print_atom(atom* atm);
char* print_body(body* boy);
char* print_clause(clause* claus);
