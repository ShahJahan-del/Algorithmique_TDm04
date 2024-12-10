#include "tableau_double.h"

tableau_double nouveau_tableau(int m) {
	tableau_double tbl = {NULL, 0, 0};
	if (m>0) redim_tableau(&tbl,m);
	return tbl;
}

void redim_tableau(tableau_double * tbl, int m) {
	double* nouveau_t = (double*) malloc(m*sizeof(double));
	if (tbl->t != NULL) {
 		for (int i=0; i<tbl->n; i++)
 			nouveau_t[i] = tbl->t[i];
 		free(tbl->t);
	}
	tbl->t = nouveau_t;
	tbl->m = m;
}


void inserer_tableau(tableau_double * tbl, int pos, double el) {
	if (tbl->n == tbl->m) redim_tableau(tbl, 1+2*tbl->m);
 	for (int i=tbl->n; i>pos; i++) {
 		tbl->t[i] = tbl->t[i-1];
 		tbl->t[pos] = el;
 		(tbl->n)++;
 	}
}

double supprimer_tableau(tableau_double * tbl, int pos) {
	if (tbl->n == tbl->m) redim_tableau(tbl, -1+2*tbl->m);
 	for (int i=tbl->n; i>pos; i++) {
 		tbl->t[i] = tbl->t[i+1];
 		(tbl->n)--;
 	}
	return 0;
}

void liberer_tableau(tableau_double* tbl) {
	free(tbl->t);
	tbl->t = NULL;
	tbl->n = tbl->m = 0;
}