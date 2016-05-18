#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

bool comp_atom(atom* atm1, atom* atm2){
	puts("angekommen in comp_atom\n");
	//Predikatensymbol vergleichen
	if(strcmp(atm1->predSym,atm2->predSym) == 0){
		puts("predSym gleich\n");
		comp_termList(atm1->trm_lst,atm2->trm_lst);
	}
}

bool comp_termList(term_list* trmL1, term_list* trmL2){
	puts("angekommen in comp_termList\n");
	if(!comp_term(trmL1->trm,trmL2->trm)){
		puts("term (hat rekursiv Termliste) ungleich \n");
		return false;
	}
	if(trmL1->next == NULL && trmL2->next == NULL){
		return true;
	}
	return comp_termList(trmL1->next, trmL2->next);
return false;
}

bool comp_term(term* trm1, term* trm2){
	puts("angekommen in comp_term\n");
	if(strcmp(trm1->fOrConst,trm2->fOrConst) == 0){
		if(trm1->argm == NULL && trm2->argm == NULL){
			
			return true;
		}
		
		return comp_termList(trm1->argm,trm2->argm);
	}
puts("const von Term ungleich\n");
return false;
}

bool loeseFormel(clause_list* ziel_claus_list, clause_list* regel_claus_list) {
	clause_list* ziel_claus_list_anfang = ziel_claus_list;
	while(ziel_claus_list != NULL) { // Solange ZielKlauseln vorhanden sind
		printf("   ZielKlausel: ");
		//print_clause(ziel_claus_list->claus);
		clause_list* regel_claus_list_tmp = regel_claus_list;
		while(regel_claus_list_tmp != NULL) { // Überprüfe je RegelKlausel mit den ZielKlauseln
			printf("   RegelKlausel: ");
			//print_clause(regel_claus_list_tmp->claus);
			clause* ziel_claus = ziel_claus_list->claus;
			if(ziel_claus == NULL) { // Leere Klausel erkannt -> nicht erfüllbar
				printf("    Leere ZielKlausel erkannt!");
				return false;
			} else { // Klausel hat Literale -> Überprüfe ob neue ZielKlausel gebildet werden kann
				while(ziel_claus != NULL) {
					clause* regel_claus = regel_claus_list_tmp->claus;

					// Prüfen ob Klauseln ungleich, dann mergen und anhängen
					if(!comp_body(ziel_claus->bd, regel_claus->bd)) {
						clause* newZielClaus = mergeClauses(ziel_claus, regel_claus);
						appendClauseList(ziel_claus_list, newZielClaus);
				
						/*if(ziel_claus->lit->sign != regel_claus->lit->sign) {
							clause* new_ziel_claus = mergeClauses(ziel_claus_list->claus,regel_claus_list_tmp->claus, ziel_claus->lit->val);

							if(!checkForLoop(ziel_claus_list_anfang, new_ziel_claus)) {
								printf("    neue ZielKlausel: ");
								print_clause(new_ziel_claus);
								appendClauseList(ziel_claus_list, new_ziel_claus);
							} else {
								printf("   Loop erkannt!\n");
							}
						}*/
					}
					clause_list* temp = NULL;
					clause* tempC = NULL;
					temp = ziel_claus_list;
					while(temp->claus != (clause*) ziel_claus) {
						if(temp->claus == ziel_claus) {
							tempC = temp->next;		
							break;
						}					
					}
					ziel_claus = tempC;
				}
			}
			regel_claus_list_tmp = regel_claus_list_tmp->next;
		}
		ziel_claus_list = ziel_claus_list->next;
	}
	return true;
}

clause* mergeClauses(clause* ziel_claus, clause* regel_claus) {
	clause* new_claus = NULL;
	puts("angekommen in merge\n");

	// Ziel Klausel durchlaufen
	body* bd = ziel_claus->bd;
	while(bd != NULL) {
		if(!comp_atom(bd->head, regel_claus->bd->head)) {
				new_claus = toclause(bd->head, new_claus);
		}
		bd = bd->next;
	}
	
	// Regel Klausel durchlaufen
	while(regel_claus != NULL) {
		body* bd = regel_claus->next;
		while(bd != NULL) {
			if(!(comp_atom(bd->head, ziel_claus->bd->head)) {
				new_claus = toclause(bd->head, new_claus);
			}
		}
	}

	return new_claus;
}


bool comp_body(body* bd1, body* bd2){
	if(!(comp_atom(bd1->head,bd2->head)){
		return false;
	}
	if(!(bd1->next == NULL && bd2->next == NULL)){
		return true;
	}
	return comp_body(bd1->next,bd2->next);
}


void appendClauseList(clause_list* claus_list, clause* claus) {
	clause_list* next_pointer = claus_list;
	while(claus_list != NULL) {
		next_pointer = next_pointer->next;
	}
	next_pointer->next = claus;
}
