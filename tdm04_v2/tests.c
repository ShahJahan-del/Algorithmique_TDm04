#include "tests.h"

#include <time.h> /* pour l'initialisation du geneateur de nombres  aleatoires */
#include <stdio.h> /* pour affichages */
#include <stdlib.h> /* pour malloc */

#include "util.h" /* les differents remplissages et utilitaires*/
#include "tableau_double.h"
#include "liste_double.h"
#include "liste_tableau_double.h"
// #include "liste2_double.h"

int verif_elements(double a, double b, int i);
int verif_elements_leq(double a, double b, int i);
int verif_nombre(int n, int nn);
int verif_index(int i, int ii, char* s);
int verif_capacite(int m, int mm);
int verif_capacite_suf(int m, int mm);
int verif_memoire(void* p);
void pass();



time_t seed = 0;
double* initialize_array(double* array, int n) {
    if (!seed) seed = time(NULL);
    if (array) free(array);

    array = malloc(sizeof(double)*n);
    if (!array) {
        printf("Erreur de allocation\n");
        exit(-1);
    }

    srand(seed+n);
    remplirAlea(array, n);
    return array;
}

int test_tableau_dynamique(double* array, int n) {
    int i, j;
    printf("------------- Tests du tableau dynamique ------------\n");

    if (n < 4) {
        printf("Test impossible avec moins de 4 éléments\n");
        return -2;
    }

    int m = 4;
    tableau_double tbl = nouveau_tableau(m);
    printf("Test d'initialisation... \t");
    if (verif_memoire((void*)tbl.t) || verif_nombre(tbl.n, 0) || verif_capacite(tbl.m, m))
        return -3;
    tbl.t[m-1] += 0; // Teste la memoire (peut generer un Segmentation Fault si incorrect)
    pass();

    m = 20;
    redim_tableau(&tbl, m);
    printf("Test de redimensionnement...\t");
    if (verif_memoire((void*)tbl.t) || verif_nombre(tbl.n, 0) || verif_capacite(tbl.m, m))
        return -4;
    tbl.t[m-1] += 0; // Teste la memoire (peut generer un Segmentation Fault si incorrect)
    pass();

    printf("Test de insertion a la fin...\t");
    for (j=0; j<n/2; j++)
        inserer_tableau(&tbl, j, array[j]);
    i=j;
    if (verif_nombre(tbl.n, i) || verif_capacite_suf(tbl.m, i))
        return -5;
    for (j=0; j<i; j++)
        if (verif_elements(tbl.t[j], array[j], j))
            return -5;
    pass();

    printf("Test de insertion...\t\t");
    for (j=n-1; j>=i; j--)
        inserer_tableau(&tbl, i, array[j]);
    if (verif_nombre(tbl.n, n) || verif_capacite_suf(tbl.m, n))
        return -6;
    for (j=0; j<n; j++)
        if (verif_elements(tbl.t[j], array[j], j))
            return -6;
    pass();

    int c=0, p=1, l=0;
    printf("Test de suppression...\t\t");
    for (j=1;j<n-c;j*=2) {
        supprimer_tableau(&tbl, j);
        c++;
    }
    if (verif_nombre(tbl.n, n-c) || verif_capacite_suf(tbl.m, n-c))
        return -7;
    for (j=0; j<n; j++) {
        if (j-l == p) {
            p *= 2;
            l++;
            continue;
        }
        if (verif_elements(tbl.t[j-l], array[j], j-l))
            return -7;
    }
    pass();

    liberer_tableau(&tbl);
    return 0;
}

int test_liste(double* array, int n) {
    int i, j;
    liste_double lst=NULL, p;
    printf("------------- Tests de la liste chainee -------------\n");

    if (n < 4) {
        printf("Test impossible avec moins de 4 éléments\n");
        return -2;
    }

    printf("Test de nouveau maillon... \t");
    lst = nouveau_maillon(array[0]);
    if (verif_elements((*lst).val, array[0], 0))
        return -3;
    pass();

    printf("Test de insertion apres... \t");
    i = 1+n/2;
    for (j=i-1; j>=1; j--)
        inserer_apres_liste(lst, array[j]);
    p = lst;
    for (j=0; j<i; j++) {
        if ((p==NULL && verif_nombre(j,i)) || verif_elements(p->val, array[j],j))
            return -4;
        p = p->suiv;
    }
    pass();

    printf("Test de avancer... \t\t");
    p = avancer_liste(lst, i/2);
    if ((p==NULL && verif_nombre(0,1)) || verif_elements(p->val, array[i/2],i/2))
        return -5;
    pass();

    printf("Test de longueur... \t\t");
    if (verif_nombre(longueur_liste(lst), i))
        return -6;
    pass();

    printf("Test de insertion position...\t");
    for (j=n-1; j>=i; j--)
        inserer_position_liste(&lst, i, array[j]);
    if (verif_nombre(longueur_liste(lst), n))
        return -6;
    p = lst;
    for (j=0; j<n; j++) {
        if ((p==NULL && verif_nombre(j,n)) || verif_elements(p->val, array[j],j))
            return -6;
        p = p->suiv;
    }
    pass();

    printf("Test de suppression apres...\t");
    supprimer_apres_liste(lst);
    supprimer_apres_liste(lst->suiv);
    p = lst;
    for (j=0; j<3; j++) {
        if ((p==NULL && verif_nombre(j,n)) || verif_elements(p->val, array[2*j],j))
            return -7;
        p = p->suiv;
    }
    pass();

    int c=2, k=1, l=0;
    printf("Test de suppression position...\t");
    for (j=4;j<n-c;j*=2) {
        supprimer_position_liste(&lst, j);
        c++;
    }
    if (verif_nombre(longueur_liste(lst), n-c))
        return -8;
    p = lst;
    for (j=0; j<n; j++) {
        if (j-l == k) {
            k *= 2;
            l++;
            continue;
        }
        if ((p==NULL && verif_nombre(j,n)) || verif_elements(p->val, array[j], j-l))
            return -8;
        p = p->suiv;
    }
    pass();

    printf("Test de liberation...\t\t");
    liberer_liste(lst);
    pass();

    return 0;
}

maillon_double* inserer_fin_liste(liste_double* lst, double val) {
    return inserer_position_liste(lst, longueur_liste(*lst), val);
}

int test_liste_fin(double* array, int n, int t) {
    int j;
    liste_double lst=NULL, p;
    printf("------- Tests d'insertion a la fin d'une liste ------\n");

    if (n < 4) {
        printf("Test impossible avec moins de 4 éléments\n");
        return -2;
    }

    printf("Test de insertion a la %s\t", (t==1?"position n-1...":"fin...\t"));
    for (j=0; j<n; j++) {
        if (t==1) inserer_position_liste(&lst,  j, array[j]);
        else      inserer_fin_liste(&lst, array[j]);
    }
    if (verif_nombre(longueur_liste(lst), n))
        return -3;
    p = lst;
    for (j=0; j<n; j++) {
        if ((p==NULL && verif_nombre(j,n)) || verif_elements(p->val, array[j],j))
            return -3;
        p = p->suiv;
    }
    pass();

    printf("Liberation...\t\t\t\t");
    liberer_liste(lst);
    pass();

    return 0;
}

int test_liste_fin_1(double* array, int n) {
    return test_liste_fin(array, n, 1);
}

int test_liste_fin_2(double* array, int n) {
    return test_liste_fin(array, n, 2);
}



int test_tri(double* array, int n, int tri) {
    liste_double lst = NULL, p;
    int j;

    char* nom = "";
    if (tri == 1) nom = "fusion 1";
    if (tri == 2) nom = "fusion 2";
    if (tri == 3) nom = "rapide";

    printf("--------------- Tests du tri %-10s ---------------\n", nom);

    printf("Insertion...\t\t");
    for (j=n-1; j>=0; j--)
        inserer_position_liste(&lst, 0, array[j]);
    p = lst;
    for (j=0; j<n; j++) {
        if ((p==NULL && verif_nombre(j,n)) || verif_elements(p->val, array[j],j))
            return -2;
        p = p->suiv;
    }
    pass();

    printf("Tri %s...\t\t", nom);
    if (tri == 1) tri_fusion_1(&lst, n);
    if (tri == 2) tri_fusion_2(&lst);
    if (tri == 3) tri_rapide(&lst);
    p = lst;
    if (p == NULL && verif_nombre(0,1))
        return -3;
    for (j=0; j<n-1; j++) {
        if ((p->suiv==NULL && verif_nombre(j,n)) || verif_elements_leq(p->val, p->suiv->val, j))
            return -3;
        p = p->suiv;
    }
    if (p->suiv != NULL && verif_nombre(0,1))
        return -3;
    return 0;
}

int test_tri_fusion_1(double* array, int n) {
    return test_tri(array, n, 1);
}

int test_tri_fusion_2(double* array, int n) {
    return test_tri(array, n, 2);
}

int test_tri_rapide(double* array, int n) {
    return test_tri(array, n, 3);
}

int test_lstbl(double* array, int n) {
    int i, j, p;
    lstbl_double lst;
    printf("-------- Tests de la liste chainee sur tableau --------\n");

    if (n < 4) {
        printf("Test impossible avec moins de 4 éléments\n");
        return -2;
    }

    printf("Test de nouvelle liste... \t");
    lst = nouveau_lstbl(n);
    if (verif_memoire(lst.contenu) || verif_memoire(lst.suivant) 
            || verif_index(lst.p_tete, -1, "p_tete") || verif_index(lst.p_libre, 0, "p_libre"))
        return -3;
    pass();

    printf("Insertion premier element...\t");
    inserer_position_lstbl(&lst, 0, array[0]);
    if (verif_index(lst.p_tete, 0, "p_tete") || verif_index(lst.p_libre, 1, "p_libre")
        || verif_elements(lst.contenu[0], array[0], 0) || verif_index(lst.suivant[0], -1, "suivant[0]")) {
        printf("-> Insertion manuelle...\t");
        lst.p_tete = 0; lst.p_libre = 1;
        lst.contenu[0] = array[0]; lst.suivant[0] = -1;
    }
    pass();

    printf("Test de insertion apres... \t");
    i = 1+n/2;
    for (j=i-1; j>=1; j--)
        inserer_apres_lstbl(&lst, 0, array[j]);
    p = lst.p_tete;
    for (j=0; j<i; j++) {
        if ((p==-1 && verif_nombre(j,i)) || verif_elements(lst.contenu[p], array[j], j))
            return -4;
        p = lst.suivant[p];
    }
    pass();

    printf("Test de avancer... \t\t");
    p = avancer_lstbl(lst, lst.p_tete, i/2);
    if ((p==-1 && verif_nombre(0,1)) || verif_elements(lst.contenu[p], array[i/2], i/2))
        return -5;
    pass();

    printf("Test de longueur... \t\t");
    if (verif_nombre(longueur_lstbl(lst), i))
        return -6;
    pass();

    printf("Test de insertion position...\t");
    for (j=n-1; j>=i; j--)
        inserer_position_lstbl(&lst, i, array[j]);
    if (verif_nombre(longueur_lstbl(lst), n))
        return -6;
    p = lst.p_tete;
    for (j=0; j<n; j++) {
        if ((p==-1 && verif_nombre(j,n)) || verif_elements(lst.contenu[p], array[j],j))
            return -6;
        p = lst.suivant[p];
    }
    pass();

    printf("Test de suppression apres...\t");
    supprimer_apres_lstbl(&lst, lst.p_tete);
    if (lst.p_tete==-1 && verif_nombre(0,1))
        return -7;
    supprimer_apres_lstbl(&lst, lst.suivant[lst.p_tete]);
    p = lst.p_tete;
    for (j=0; j<3; j++) {
        if ((p==-1 && verif_nombre(j,n)) || verif_elements(lst.contenu[p], array[2*j],j))
            return -7;
        p = lst.suivant[p];
    }
    pass();

    int c=2, k=1, l=0;
    printf("Test de suppression position...\t");
    for (j=4;j<n-c;j*=2) {
        supprimer_position_lstbl(&lst, j);
        c++;
    }
    if (verif_nombre(longueur_lstbl(lst), n-c))
        return -8;
    p = lst.p_tete;
    for (j=0; j<n; j++) {
        if (j-l == k) {
            k *= 2;
            l++;
            continue;
        }
        if ((p==-1 && verif_nombre(j,n)) || verif_elements(lst.contenu[p], array[j], j-l))
            return -8;
        p = lst.suivant[p];
    }
    pass();

    printf("Suppression complete...\t\t");
    while(lst.p_tete != -1)
        supprimer_position_lstbl(&lst, 0);
    pass();

    printf("Test de redimensionnement...\t");
    for (j=2*n-1; j>=0; j--)
        inserer_position_lstbl(&lst, 0, array[j%n]);
    if (verif_nombre(longueur_lstbl(lst), 2*n))
        return -9;
    p = lst.p_tete;
    for (j=0; j<2*n; j++) {
        if ((p==-1 && verif_nombre(j,n)) || verif_elements(lst.contenu[p], array[j%n],j))
            return -8;
        p = lst.suivant[p];
    }
    pass();

    printf("Test de liberation...\t\t");
    liberer_lstbl(lst);
    pass();

    return 0;
}




// Outils

int verif_elements(double a, double b, int i) {
    if (a == b) return 0;
    printf("Element %d incorrect\n", i);
    return -1;
}

int verif_elements_leq(double a, double b, int i) {
    if (a <= b) return 0;
    printf("Ordre des elements %d et %d incorrecte\n", i,i+1);
    return -1;
}

int verif_nombre(int n, int nn) {
    if (n == nn) return 0;
    printf("Nombre d'elements incorrect\n");
    return -1;
}

int verif_index(int i, int ii, char* s) {
    if (i == ii) return 0;
    printf("Position incorrecte (%s est %d, doit etre %d)\n",s, i, ii);
    return -1;
}

int verif_capacite(int m, int mm) {
    if (m == mm) return 0;
    printf("Capacite incorrecte\n");
    return -1;
}

int verif_capacite_suf(int m, int mm) {
    if (m >= mm) return 0;
    printf("Capacite trop faible\n");
    return -1;
}

int verif_memoire(void* p) {
    if (p != NULL) return 0;
    printf("Memoire pas allouee\n");
    return -1;
}

void pass() {
    printf("Reussi\n");
}