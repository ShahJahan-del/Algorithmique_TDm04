#include "liste_double.h"

maillon_double* nouveau_maillon(double val) {
	maillon_double* nv = malloc(sizeof(maillon_double));
	if (nv == NULL) return NULL;
	nv->val = val;
	nv->suiv = NULL;
	return nv;
}

maillon_double* inserer_apres_liste(maillon_double* m, double val) {
	maillon_double* nv = nouveau_maillon(val);
	if (nv == NULL) return NULL;
	nv->suiv = m->suiv;
	m->suiv = nv;
	return nv;
}



maillon_double* avancer_liste(maillon_double* p, int i) {
	// A ecrire
}

int longueur_liste(liste_double lst) {
	// A ecrire
	return 0;
}




maillon_double* inserer_position_liste(liste_double* lst, int i, double val) {
	// A ecrire
}

void supprimer_apres_liste(maillon_double* m) {
	// A ecrire
}

void supprimer_position_liste(liste_double* lst, int i) {
	// A ecrire
}



void afficher_liste(liste_double lst) {
	// A ecrire
}


void liberer_liste(liste_double lst) {
	// A ecrire
}





/*************
* TRI FUSION *
*************/

liste_double fusionner_1(liste_double l1, int n, liste_double l2, int m) {
	liste_double lst = nouveau_maillon(0);
	liste_double p = lst;
	while (n > 0 && m > 0) {
		if (m == 0 && l1->val <= l2->val) { //l1->val = contenu(l1), défini dans la structure liste_double.h
			l1->suiv = l1; //l1->suiv = suivant(l2)
			l1 = l1->suiv;
			n = n-1;
		} else l1->suiv = l2; l2 = l2->suiv; m = m-1;
	}
	l1->suiv = NULL;
	p = lst->suiv; //suivant(lst) = lst->suiv
	free(lst);
	return p;
	return l1;
}

int tri_fusion_1(liste_double* lst, int n) {
	if (n==0) lst = lst;
	else; 
	liste_double* p = lst; liste_double* q = lst;
	for (int i = 1; i < n/2; i++) {
		q = q->suiv;
	}
	tri_fusion_1(p, (int) n/2);
	tri_fusion_1(q, n - (int) n/2);
	lst = fusionner_1(p, (int) n/2, q, n - (int) n/2);
	return -1;
}



void separer_liste(liste_double lst, liste_double* l1, liste_double* l2) {
	// A ecrire
}

liste_double fusionner_2(liste_double l1, liste_double l2) {
	// A ecrire
	return l1;
}

int tri_fusion_2(liste_double* lst) {
	// A ecrire
	return -1;
}
