#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>



clause_list* toClauseList(clause* claus, clause_list* next) {
	
	clause_list* clslst;
	clslst = malloc(sizeof(clause_list));

	clslst->claus = claus;
	clslst->next = next;

	return clslst;
}

atom_list* toAtomList(atom* atm, atom_list* next){
	atom_list* atomList;
	atomList = malloc(sizeof(atom_list));

	atomList->atm = atm;
	atomList->next = next;

	return atomList;		
}


clause* toclause(atom_list* atomList, atom* atm) {
	clause* claus;
	claus = malloc (sizeof(clause));

	claus->head = atm;
	claus->tail = atomList;

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

/*char* print_term(term* trm) {
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

char* print_clause(clause* claus) {
	puts ("print clause");
	if (claus != NULL) {
		print_body(claus->bd);
	}
}*/

bool comp_clause(clause* c1, clause* c2) {
	puts("\nangekommen in comp_clause");
	// Überprüfen Atom und dann Atomliste
	if(comp_atom(c1->head, c2->head)) {
		if(comp_atomList(c1->tail, c2->tail)) {
			return true;
		}
	}
	return false;
}

bool comp_atomList(atom_list* l1, atom_list* l2) {
	puts("\n angekommen in comp_atomList");
	if(!comp_atom(l1->atm,l2->atm)){
		return false;
	}
	if(l1->next == NULL && l2->next == NULL){
		return true;
	}	
	return comp_atomList(l1->next, l2->next);
return false;
}

bool comp_atom(atom* atm1, atom* atm2){	
	puts("\nangekommen in comp_atom");
	if(atm1 == NULL && atm2 == NULL) {
		return true;
	}

	//TODO: Bei dem STRCMP bzw Referenz auf predSym kommt seg fault!
	
	//Predikatensymbol und Terme vergleichen
	if(strcmp(atm1->predSym,atm2->predSym) == 0){
		puts("\npredSym gleich");
		return comp_termList(atm1->trm_lst,atm2->trm_lst);
	}
	return false;
}

bool isInAtomList(atom* atm, atom_list* atomList){
	puts("\n angekommen in inAtomList");
	atom_list* temp = atomList;
	while(temp != NULL){
		if(comp_atom(atm,temp->atm)){
			return true;
		}
	temp = temp->next;
	}
	return false;
}

bool comp_termList(term_list* trmL1, term_list* trmL2){
	puts("\nangekommen in comp_termList");
	if(trmL1->next == NULL && trmL2->next == NULL){
		return true;
	}
	
	if(!comp_term(trmL1->trm,trmL2->trm)){
		return false;
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
	if(ziel_claus_list==NULL) puts(" Zielclauselist null");
	if(regel_claus_list==NULL) puts(" Regelclauselist null");
	
	clause_list* ziel_claus_list_anfang = ziel_claus_list;	
	while(ziel_claus_list != NULL) { // Solange ZielKlauseln vorhanden sind
		printf("\n   ZielKlausel: ");
		clause_list* regel_claus_list_tmp = regel_claus_list;
		while(regel_claus_list_tmp != NULL) { // Überprüfe je RegelKlausel mit den ZielKlauseln
			printf("\n   RegelKlausel: ");
			clause* ziel_claus = ziel_claus_list->claus;
			if(ziel_claus == NULL) { // Leere Klausel erkannt -> nicht erfüllbar
				printf("\n    Leere ZielKlausel erkannt!");
				puts("\n FALSCH");
				return false;
			} else { // Klausel hat Literale -> Überprüfe ob neue ZielKlausel gebildet werden kann
				while(ziel_claus != NULL) {
					// Nächstes Klausel Element markieren
					clause_list* tmp_pntr = ziel_claus_list;
					while(tmp_pntr->claus != ziel_claus) {
						tmp_pntr = tmp_pntr->next;
					}
					tmp_pntr = tmp_pntr->next;

					// Prüfen ob Klauseln ungleich, dann mergen und anhängen
					clause* regel_claus = regel_claus_list_tmp->claus;
					if(!comp_clause(ziel_claus, regel_claus)) {
						// Neue Klausel erstellen und vorn anhängen
						clause* newZielClaus = mergeClauses(ziel_claus, regel_claus);
						regel_claus_list = toClauseList(newZielClaus, regel_claus_list);
						
						// Pointer wieder auf Start setzen, da Klausel neu
						tmp_pntr = ziel_claus_list;						
					}
					
					// Entweder zum nächsten Klauselement oder zum Start gehen
					ziel_claus = tmp_pntr->claus;
				}
			}
			regel_claus_list_tmp = regel_claus_list_tmp->next;
		}
		ziel_claus_list = ziel_claus_list->next;
	}
	puts("\nwahr");
	return true;
}

clause* mergeClauses(clause* ziel_claus, clause* regel_claus) {
	puts("angekommen in merge\n");
	// Neue Klausel erstellen
	clause* new_claus = (clause*) malloc(sizeof(clause));


	// Ziel Klausel durchlaufen
	atom_list* current = ziel_claus->tail;
	while(current != NULL) {
		// Jedes unterschiedliche Atom hinzufügen
		if(!comp_atom(current->atm, regel_claus->head)) {
				new_claus->tail = toAtomList(current->atm, new_claus->tail);
		}
		current = current->next;
	}
	
	// Regel Klausel durchlaufen
	current = regel_claus->tail;
	while(current != NULL) {
		// Jedes unterschiedliche Atom hinzufügen
		if(!comp_atom(current->atm, ziel_claus->head)) {
			new_claus->tail = toAtomList(current->atm, new_claus->tail);
		}
		current = current->next;
	}

	return new_claus;
}
