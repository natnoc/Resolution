
#include <stdio.h>
#include <stdbool.h>

typedef struct clause_list{
	struct clause* claus;
	struct clause_list* next;
}clause_list;

typedef struct clause{
	struct atom* head;
	struct atom_list* tail;
}clause;

typedef struct atom_list{
	struct atom* atm;
	struct atom_list* next;
}atom_list;

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


//void addAtomToClause(atom* atm, clause* clause);
clause_list* toClauseList(clause* claus, clause_list* next);
clause* toclause(atom_list* atmList, atom* atm);
atom* toAtom(char* prSym, term_list* trmList);
term_list* toTermList(term* trm, term_list* next);
term* toTerm(char* fOrC, term_list* arg);
atom_list* toAtomList(atom* atm, atom_list* next);
bool isInAtomList(atom* atm, atom_list* atomList);

char* print_term(term* trm);
char* print_term_liste(term_list* trm_lst);
char* print_atom(atom* atm);
char* print_clause(clause* claus);

bool comp_atom(atom* atm1, atom* atm2);
bool comp_atomList(atom_list* atm1, atom_list* atm2);
bool comp_termList(term_list* trmL1, term_list* trmL2);
bool comp_term(term* trm1, term* trm2);
bool comp_clause(clause* c1, clause* c2);
bool loeseFormel(clause_list* ziel_claus_list, clause_list* regel_claus_list);
clause* mergeClauses(clause* ziel_claus, clause* regel_claus);
void appendClauseList(clause_list** claus_list, clause* claus);
