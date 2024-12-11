#pragma once

typedef struct {
	double	*contenu;
	int		*suivant;
	int		p_tete;
	int		p_libre;
} lstbl_double;

lstbl_double nouveau_lstbl(int m);

int avancer_lstbl(lstbl_double lst, int p, int i);
int longueur_lstbl(lstbl_double lst);

int inserer_position_lstbl(lstbl_double* lst, int pos, double val);
int inserer_apres_lstbl(lstbl_double* lst, int p, double val);

void supprimer_position_lstbl(lstbl_double* lst, int pos);
void supprimer_apres_lstbl(lstbl_double* lst, int p);

void afficher_lstbl(lstbl_double lst);
void liberer_lstbl(lstbl_double lst);