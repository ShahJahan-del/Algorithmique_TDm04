#include <stdio.h> /* pour affichages */
#include <stdlib.h> /* pour malloc */
#include <ctype.h> /* pour tolower() dans le choix de menu */

#include "util.h" /* les differents remplissages et utilitaires*/
#include "chrono.h" /* gestion du chronometrage et des interruptions en cas de depassement de temps */
#include "tests.h" /* fonctions de teste */







char affiche_menu_opt(int nbelts, double tps_max) {
    /* etat actuel */
    printf("\n--------------- Configuration actuelle --------------\n\n");
    printf("%-20s : %d\n%-20s : %.3f s\n",
             "Taille", nbelts,
             "Limite de temps", tps_max); 

    /********************* MENU *****************************/
    printf("\n\t\t--- Menu ---\n");
    printf("\t1. Lancer les tests du tableau dynamique\n");
    printf("\t2. Lancer les tests de la liste chainee\n");
    printf("\t3. Lancer les tests de tri\n");
    printf("\t4. Lancer les tests de la liste chainee sur un tableau\n");
    printf("\t5. Lancer les tests d'insertion à la fin d'une liste\n");
    printf("\n");

    printf("\t6. Changer le (n)ombre d'elements\n");
    printf("\t7. Changer la (l)imite de temps\n");
    printf("\n");
    printf("\t0. (Q)uitter le programme\n");

    /**************************** reponse  ***********************/
    char  *rep = saisie_rep();
    return tolower(rep[0]);
}


int main() { 
    double tps_max = 2.0;  // temps limite
    double x;              // double pour la saisie
    double t;              // temps de tri

    char op;               // reponse utilisateur
    int n;                 //nombre saisi

    int nbelts = 10000;    // nombre d'elements du tableau
    int fin = 0;           // pour terminer

    double * array = initialize_array(NULL, nbelts);

    do {
        op = affiche_menu_opt(nbelts, tps_max);

        printf("\n-----------------------------------------------------\n");
        if (op == 'n' || op == '6') {
            printf("\nEntrez le nombre d'elements a utiliser (0 pour quitter) : ");
            n = saisie_int();
            if (n < 0 )
                printf("%d : nb elements impossible \n\n", n);
            else if (n > 0) {
                nbelts = n;
                array = initialize_array(NULL, nbelts);
            }
        }
        else if (op == 'l' || op == '7') {
            printf("\nEntrez le temps maximum autorise (0 pour quitter) : ");
            x = saisie_double();
            if (x < 0) 
                printf("%.3f : temps maxi autorise impossible \n\n", x);
            if (x > 0) 
                tps_max = x;
        }
        else if (op == 'q' || op == '0') {
            fin = -1;
        }
        else if (op == '1') {
            t = chronometre(test_tableau_dynamique, array, nbelts, tps_max);

            if (t >= 0) 
                printf("Tests reussis en %.3f s\n", t);
            else if (t == HORS_DELAI) 
                printf("Tests non termine en %.3f s\n", tps_max);
            else
                printf("Erreur dans les tests!\n");
        }
        else if (op == '2') {
            t = chronometre(test_liste, array, nbelts, tps_max);

            if (t >= 0) 
                printf("Tests reussis en %.3f s\n", t);
            else if (t == HORS_DELAI) 
                printf("Tests non termine en %.3f s\n", tps_max);
            else
                printf("Erreur dans les tests!\n");
        }
        else if (op == '3') {
            t = chronometre(test_tri_fusion_1, array, nbelts, tps_max);

            if (t >= 0) 
                printf("Test reussis en %.3f s\n", t);
            else if (t == HORS_DELAI) 
                printf("Test non termine en %.3f s\n", tps_max);
            else
                printf("Erreur dans les test!\n");

            t = chronometre(test_tri_fusion_2, array, nbelts, tps_max);

            if (t >= 0) 
                printf("Test reussis en %.3f s\n", t);
            else if (t == HORS_DELAI) 
                printf("Test non termine en %.3f s\n", tps_max);
            else
                printf("Erreur dans les test!\n");

            t = chronometre(test_tri_rapide, array, nbelts, tps_max);

            if (t >= 0) 
                printf("Test reussis en %.3f s\n", t);
            else if (t == HORS_DELAI) 
                printf("Test non termine en %.3f s\n", tps_max);
            else
                printf("Erreur dans les test!\n");
        }
        else if (op == '4') {
            t = chronometre(test_lstbl, array, nbelts, tps_max);

            if (t >= 0) 
                printf("Tests reussis en %.3f s\n", t);
            else if (t == HORS_DELAI) 
                printf("Tests non termine en %.3f s\n", tps_max);
            else
                printf("Erreur dans les tests!\n");
        }
        else if (op == '5') {
            t = chronometre(test_liste_fin_1, array, nbelts, tps_max);
            if (t >= 0) 
                printf("Tests reussis en %.3f s\n", t);
            else if (t == HORS_DELAI) 
                printf("Tests non termine en %.3f s\n", tps_max);
            else
                printf("Erreur dans les tests!\n");

            t = chronometre(test_liste_fin_2, array, nbelts, tps_max);
            if (t >= 0) 
                printf("Tests reussis en %.3f s\n", t);
            else if (t == HORS_DELAI) 
                printf("Tests non termine en %.3f s\n", tps_max);
            else
                printf("Erreur dans les tests!\n");
        }
    } while (! fin);

    return 0;
}

