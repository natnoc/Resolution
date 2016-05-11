#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*clause* toclause(atom* atm, body* bd, clause* next){
	clause* claus;
	claus = malloc (sizeof(clause));

	claus->head = atm;
	claus->bd = bd;
	claus->next = next;

	return claus;
}*/

clause_list* toClauseList(clause* claus, clause_list* next) {
	clause_list* clslst;
	clslst = malloc(sizeof(clause_list));

	clslst->claus = claus;
	clslst->next = next;

	return clslst;
}


clause* toclause(body* bd) {
	clause* claus;
	claus = malloc (sizeof(clause));

	claus->bd = bd;

	return claus;
}

atom* toAtom(char* prSym, term_list* trmList){
	atom* atm;
	atm = malloc (sizeof(atom));

	atm->predSym = prSym;
	atm->trm_lst = trmList;

	return atm;
}

term_list* toTermList(term* trm, term_list* next){
	term_list* termList;
	termList = malloc(sizeof(term_list));

	termList->trm = trm;
	termList->next = next;

	return termList;
}

term* toTerm(char* fOrC, term_list* arg){
	term* trm;
	trm = malloc (sizeof(term));

	trm->fOrConst = fOrC;
	trm->argm = arg;

	return trm;
}
/*function* toFunction(char* fOrC, term_list* arg, function* next){
	function* funct;
	funct = malloc (sizeof(function));

	funct->fOrConst = fOrC;
	funct->argm = arg;
	funct->next = next;

	return funct;
}*/
body* tobody(atom* head, body* bd){

	body* boy;
	boy = malloc (sizeof(body));

	boy->head = head;
	boy->next = bd;

	return boy;
}

char* print_term(term* trm) {
	puts ("print term");
	if (trm != NULL) {
		printf("Symbol: %s\n", trm->fOrConst);
		print_term_liste(trm->argm);
	}
}

char* print_term_liste(term_list* trm_lst) {
	puts ("print term liste");
	while (trm_lst != NULL) {
		print_term(trm_lst->trm);
		trm_lst = trm_lst->next;
	}
}

char* print_atom(atom* atm) {
	puts ("print atom");
	if (atm != NULL) {
		printf("PredSymbol: %s\n", atm->predSym);
		print_term_liste(atm->trm_lst);
	}
}

char* print_body(body* boy){
	puts ("\nprint body");
	while (boy != NULL) {
		print_atom(boy->head);
		boy = boy->next;
	}
}

char* print_clause(clause* claus) {
	puts ("print clause");
	if (claus != NULL) {
		print_body(claus->bd);
	}
}
