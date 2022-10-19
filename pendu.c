/**
 * @file pendu.c
 * @author Quentin Bodart (github.com/KSCHdsc)
 * @brief 
 * @version 1.1.2
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 * CE TRAVAIL A ETE FORK DEPUIS TP_PENDU SUR GITHUB / AVEC L'AIDE DE LA DOC "Langage C" et Stakoverflow
 * plus jamais je referais de C sache le Hervé
 */

//déclaration des librairies
#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

#include <string.h>

#include <time.h>

#include <conio.h>

//Faire appel au fichier "./pendu.h" pour la déclaration de "lecturedecarac"
#include "pendu.h"


int main() {

  //Simple ajout un peu useless pour le style (Quentin a encore frappé)    :)
  system("cls");
  system("title Pendu Game V1.1.2");
  system("mode con cols=110 lines=30");
  system("color a");
  printf("\t\t             ________________________________________________\n");
  printf("\t\t            /                                                \\ \n");
  printf("\t\t           |    _________________________________________     |\n");
  printf("\t\t           |   |                                         |    |\n");
  printf("\t\t           |   |  C:\\> _     Jeu du pendu                |    |\n");
  printf("\t\t           |   |                                         |    |\n");
  printf("\t\t           |   |                   By                    |    |\n");
  printf("\t\t           |   |           Quentin  |  Adrien            |    |\n");
  printf("\t\t           |   |                                         |    |\n");
  printf("\t\t           |   |                                         |    |\n");
  printf("\t\t           |   |                                         |    |\n");
  printf("\t\t           |   |                                         |    |\n");
  printf("\t\t           |   |                                         |    |\n");
  printf("\t\t           |   |                                         |    |\n");
  printf("\t\t           |   |                                         |    |\n");
  printf("\t\t           |   |                                         |    |\n");
  printf("\t\t           |   |_________________________________________|    |\n");
  printf("\t\t           |                                                  |\n");
  printf("\t\t           \\_________________________________________________/\n");
  printf("\t\t                  \\___________________________________/\n");
  printf("\t\t               ___________________________________________\n");
  printf("\t\t             _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_\n");
  printf("\t\t          _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_\n");
  printf("\t\t       _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`__`. .-.-.-.`-_\n");
  printf("\t\t    _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.`-_\n");
  printf("\t\t _-'.-.-.-.-.-. .---.-. .-------------------------. .-.---. .---.-.-.-.`-_\n");
  printf("\t\t:-------------------------------------------------------------------------:\n");
  printf("\t\t`---._.-------------------------------------------------------------._.---'\n");

  //on declare nos variables pour les utiliser plus bas dans le code
  char mot_hide[100] = "";
  char cached[1] = "-";

  int compteur_Tableau = 0;
  int i = 0;
  int u = 0;
  int replaygame = 1;

  int bonne_lettre = 0;
  int fin_de_partie = 0;
  char relancer_partie[1] = "1";

  while (relancer_partie[0] != '0') {

    replaygame = 0;
    relancer_partie[0] = '0';
    int coups_restant = 8;
    int comparaison = 0;
    fin_de_partie = 0;

    // on definit le mot aleatoire :

    int nombre_ligne = 0;
    char mot_secret[100] = "";

    FILE * fichier = NULL;

    fichier = fopen("dico_des_mots", "r");

    // on determine le nombre de lignes

    if (fichier != NULL) {

      char c[100] = "";

      while (fgets(c, 100, fichier) != NULL) {
        nombre_ligne++;
      }

      rewind(fichier);
      fclose(fichier);

    } else {
      printf("erreur sur l'ouverture du fichier\n");
    }

    // on tire au hasard entre 1 et le nombre de ligne:

    int MIN = 1;
    int MAX = nombre_ligne;
    int i = 0;
    int ligne_a_tirer = 0;

    srand(time(NULL));
    ligne_a_tirer = (rand() % (MAX - MIN + 1)) + MIN;

    // on recupere le mot à la ligne tirée au hasard:

    fichier = fopen("dico_des_mots", "r");

    if (fichier != NULL) {

      for (i = 0; i < ligne_a_tirer; i++) {
        (fgets(mot_secret, 1000, fichier));

      }

      // si il y a un \n a la fin de la ligne on le remplace par \0
      char * p;

      if ((p = strchr(mot_secret, '\n')) != NULL)
        *
        p = '\0';

      fclose(fichier);

    } else {

      printf("erreur 2 le fichier ne s'ouvre pas\n");

    }
    // on mesure la longueur du mot secret : 

    int longueur = strlen(mot_secret);

    // on fait le mot etoilé

    for (i = 0; i < longueur; i++) {

      mot_hide[i] = * cached;

    }

    // on commence la boucle pour jouer

    // printf("test avant le while( partie finie == 0)");

    char str[100];
    system("title Game Started");
    sleep(3);
    system("cls");
    system("color b");
    printf("Entre ton pseudo: ");
    scanf("%s", str);
    system("cls");
    printf("\nBienvenue Joueur:  %s", str);
    sleep(2);
    system("color 0f");
    system("cls");

    //j'ai fais ça parce que jsuis abonné a mazdak et que jsavais pas pk ça beugé
    printf("\t  Si vous trouvez un beug dans notre jeu veuillez le priciser sur l'issue github renseigne :)\n\t\t\tTaper sur \"enter\" pour commencer a jouer\n\n");
    printf("\n\n\t\tGithub Issue ===>     https://github.com/KSCHdsc/pendu-en-c/issues/new\n");


    char ideedemerde = lecturedecarac();
    system("cls");



    //Fonction boucle principale, si le joueur n'a pas encore fini de jouer alors elle sera lue
    while (fin_de_partie == 0) {

      //affichage coups restant et le mot decouvert petit a petit

      printf("\nVous avez %d coups a jouer !\nQuel est le mot secret ? : %s \nProposez une lettre : ", coups_restant, mot_hide);

      char ma_lettre = lecturedecarac();

      bonne_lettre = 0;

      for (i = 0; i < longueur; i++) {

        if (mot_secret[i] == ma_lettre) { // le joueur decouvre une lettre !

          mot_hide[i] = ma_lettre; //affichage de la lettre decouverte
          bonne_lettre = 1;

        }

      }
      // Tableau des lettres essayé le max du tableau est à 26 car c'est le nombre de lettres qu'il y a dans l'alphabet.
      char tabLettre[26];
      int essaye = 0;
      for (int b = 0; b < compteur_Tableau; b++) {
        if (ma_lettre == tabLettre[b]) {
          essaye = 1;
          break;
        }
      }
      if (essaye == 1) {
        printf("\nVous avez deja tente cette lettre");
      } else {
        // On met les nouvelles lettres dans le tableau.
        tabLettre[compteur_Tableau] = ma_lettre;
        compteur_Tableau++;

        if (bonne_lettre == 0) { // le joueur perd 

          system("cls");
          //on retire -1 coup !
          coups_restant--;

          switch (coups_restant) {

            // le joueur perd un coup on affiche le pendu petit a petit
          case 7:
            printf("\t\t\t\t |   |______ \n");
            printf("\t\t\t\t |          | \n");
            printf("\t\t\t\t |__________|\n");
            break;

          case 6:
            printf("\t\t\t\t  _|_ \n");
            printf("\t\t\t\t |   |______ \n");
            printf("\t\t\t\t |          | \n");
            printf("\t\t\t\t |__________|\n");
            break;

          case 5:
            printf("\t\t\t\t   |\n");
            printf("\t\t\t\t   |\n");
            printf("\t\t\t\t   |\n");
            printf("\t\t\t\t   |\n");
            printf("\t\t\t\t  _|_ \n");
            printf("\t\t\t\t |   |______ \n");
            printf("\t\t\t\t |          | \n");
            printf("\t\t\t\t |__________|\n");
            break;

          case 4:
            printf("\t\t\t\t    ____ \n");
            printf("\t\t\t\t   |\n");
            printf("\t\t\t\t   |\n");
            printf("\t\t\t\t   |\n");
            printf("\t\t\t\t   |\n");
            printf("\t\t\t\t   |\n");
            printf("\t\t\t\t  _|_ \n");
            printf("\t\t\t\t |   |______ \n");
            printf("\t\t\t\t |          | \n");
            printf("\t\t\t\t |__________|\n");
            break;

          case 3:
            printf("\t\t\t\t    ____ \n");
            printf("\t\t\t\t   |    |    \n");
            printf("\t\t\t\t   |         \n");
            printf("\t\t\t\t   |         \n");
            printf("\t\t\t\t   |         \n");
            printf("\t\t\t\t   |         \n");
            printf("\t\t\t\t  _|_ \n");
            printf("\t\t\t\t |   |______ \n");
            printf("\t\t\t\t |          | \n");
            printf("\t\t\t\t |__________|\n");
            break;

          case 2:
            printf("\t\t\t\t    ____ \n");
            printf("\t\t\t\t   |    |    \n");
            printf("\t\t\t\t   |    o    \n");
            printf("\t\t\t\t   |   /|\\   \n");
            printf("\t\t\t\t   |         \n");
            printf("\t\t\t\t   |         \n");
            printf("\t\t\t\t  _|_ \n");
            printf("\t\t\t\t |   |______ \n");
            printf("\t\t\t\t |          | \n");
            printf("\t\t\t\t |__________|\n");
            break;

          case 1:
            printf("\t\t\t\t    ____ \n");
            printf("\t\t\t\t   |    |    \n");
            printf("\t\t\t\t   |    o    \n");
            printf("\t\t\t\t   |   /|\\   \n");
            printf("\t\t\t\t   |    |    \n");
            printf("\t\t\t\t   |         \n");
            printf("\t\t\t\t  _|_ \n");
            printf("\t\t\t\t |   |______ \n");
            printf("\t\t\t\t |          | \n");
            printf("\t\t\t\t |__________|\n");
            break;

            //le joueur perd on ne clear donc pas la console et on affiche le pendu total
          case 0:
            printf("\t\t\t\t    ____ \n");
            printf("\t\t\t\t   |    |    \n");
            printf("\t\t\t\t   |    o     \n");
            printf("\t\t\t\t   |   /|\\      \n");
            printf("\t\t\t\t   |    | \n");
            printf("\t\t\t\t   |   / \\ \n");
            printf("\t\t\t\t  _|_ \n");
            printf("\t\t\t\t |   |______ \n");
            printf("\t\t\t\t |          | \n");
            printf("\t\t\t\t |__________|\n");
            break;

          default:
            break;
          }
        }
      }

      // Si le mot est découvert, alors c'est gagné
      int comparaison = strcmp(mot_secret, mot_hide);

      if (comparaison == 0) {

        // on demande pour relancer une partie ou non
        printf("\n\nGAGNE ! le mot etait bien : %s\nVoulez vous relancer une partie ?\n OUI = 1     |       NON = 0 ", mot_secret);

        char vide[1] = ""; // pour reinitialiser mot_devoilé a "";

        for (i = 0; i < longueur; i++) {

          mot_hide[i] = * vide;

        }

        relancer_partie[0] = lecturedecarac();

        //le joueur ne veut pas rejouer on sort donc du programme!
        if ( * relancer_partie == '0') {

          printf("A bientot !\n");

        }

        fin_de_partie = 1;

      }

      // S'il ne reste plus de coup à jouer, alors c'est perdu 
      if (coups_restant <= 0) {
        printf("\n\nDesole vous avez perdu\nLe Mot cache ete : %s\nVoulez vous rejouer une partie ? \nOUI = 1     |     NON = 0 ", mot_secret);

        // REJOUER ?

        char vide[1] = ""; // pour reinitialiser mot_devoilé a "";

        for (i = 0; i < longueur; i++) {

          mot_hide[i] = * vide;

        }

        relancer_partie[0] = lecturedecarac();

        if ( * relancer_partie == '0') {

          printf("A bientot !\n");

        }

        fin_de_partie = 1;

      }
    }
  }

  return 0;
}

char lecturedecarac() {
  char caractere = 0;

  caractere = getchar(); // On lit le premier caractère
  caractere = toupper(caractere); // On met la lettre en majuscule si elle ne l'est pas déjà

  // On lit les autres caractères mémorisés un à un jusqu'au \n (pour les effacer) e
  while (getchar() != '\n');

  return caractere; // On retourne le premier caractère qu'on a lu 
}