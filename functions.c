#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

clause* toclause(atom* atm, body* bd, clause* next){
	clause* claus;
	claus = malloc (sizeof(clause));

	claus->head = atm;
	claus->bd = bd;
	claus->next = next;

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