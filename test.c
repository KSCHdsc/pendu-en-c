#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h> 
#include "pendu.h"


int main (int argc, char* argv[])
{
    int nombreMots = compteurMot();
    int i , j;
    char caractereRecup = 0;
    int numeroMot = tirageMot(nombreMots);
    int nombreLettre = tailleMot(numeroMot);

    //printf("%d %d\n",numeroMot, nombreLettre);

    char* motSecret = NULL;
    motSecret=malloc(nombreLettre * sizeof(char));//on crée un tableau de la taille du mot tiré au hasard
    if (motSecret==NULL)
    {
        exit(0);
    }

    recupMot(numeroMot,nombreLettre,motSecret);
    //affiche(motSecret,nombreLettre);

    char* motMystere = NULL;
    motMystere=malloc(nombreLettre * sizeof(char));
    if (motMystere==NULL)
    {
        exit(0);
    }

    creerMotMystere(nombreLettre,motMystere);


    printf("Bienvenue dans le jeu du pendu\n");

    for (i = 0 ; i < 10 ; i++) // compteur pour le nombre de partie
    {
        printf("Il vous reste %d coups\n", 10-i);
        printf("Quel est le mot secret ? %s\n",motMystere);
        caractereRecup = recupCaract();
        //ici on recupère le caractere via une fonction qui va en plus vider le buffer et passer le caracter en majuscule

        for (j = 0 ; motSecret[j] != '\0' ; j++) 
        // compteur pour passer en revue les caractere du mot Secret et le comparé avec le caractere saisi
        {
            if (motSecret[j] == caractereRecup)
            // Si la caractere saisi est dans le motsecret alors on l'affiche 
            {
                motMystere[j] = caractereRecup;
                i--;
            }
        }
        printf("%s\n",motMystere);

        if (verification(motMystere))
        //cette fonction regarde s'il reste des caractere non trouvé '*' dans le mot et retourne 1 si non
        {
            printf("Vous avez gagné !\n");
            exit(0);
        }
    }

    printf("Vous avez perdu, le mot mystère était : ");
    affiche(motSecret,nombreLettre);
    printf("\n");

    free(motSecret);
    free(motMystere);
    return 0;
}

char recupCaract ()//recupère les caractères saisie par l'utilisateur
{
    char caractere = 0;
    scanf("%c",&caractere);
    caractere = toupper(caractere); // On met en majuscule le caractere saisie par l'utilisateur
    while(getchar() != '\n'); //on vide le buffer

    return caractere; // on renvoit le caractere saisi
}

int verification(char motDecouvert[])//vérifie que le mot ne soit pas totalement découvert
{
    int i;
    for (i=0; motDecouvert[i] != '\0'; i++)//Tant qu'on est pas arrivé a la fin de al chaine de caractère
    {
        if (motDecouvert[i]=='*')// Si une lettre mystère est trouvé alors on renvoit 0, la partie n'est pas gagné
            return 0;
    }
    return 1; //sinon c'est que tout a été découvert, et on renvoit 1
}

int compteurMot() // on compte les mots présent dans le fichier
{
    FILE* fichier = NULL;
    int nombreDeMots = 0;
    char lettreLue = 0;

    fichier = fopen("dictionnaire","r"); // on ouvre le fichier dictionnaire en mode lecture
    if (fichier != NULL) //on test si l'ouverture a fonctionnée
    {
        rewind(fichier); //on place le curseur en haut du fichier
        while ((lettreLue = fgetc(fichier)) != EOF) // Tant qu'on a pas atteind la fin du fichier
        {
            if (lettreLue == '\n') // Quand on trouve un \n c'est qu'il y a un nouveau mot
            {
                nombreDeMots++;
            }
        }
        fclose(fichier);
    }
    return(nombreDeMots);
}

int tirageMot(int nombreDeMots)//tire au hasard un numéro d'après le nombre de mots
{
    int numeroMot= 0;

    srand(time(NULL)); // Initialise le générateur de nombre aléatoire
    numeroMot = (rand() % nombreDeMots)+1; //+1 sinon il peut tirer 0
    return(numeroMot);
}

int tailleMot(int numeroMot) //calcul la taille d'un mot d'après sa position dans la liste
{
    FILE* fichier = NULL;
    char lettreLue = 0;
    int compteurEspace = 0;
    int compteurLettre = 0;

    fichier = fopen("dictionnaire","r"); // on ouvre le fichier dictionnaire en mode lecture
    if (fichier != NULL) //on test si l'ouverture a fonctionnée
    {
        rewind(fichier); //on place le curseur en haut du fichier
        while (compteurEspace != numeroMot-1) // Tant qu'on a pas atteind la ligne avant le mot tiré
        {
            lettreLue = fgetc(fichier); //on lit les caractères 1 à 1

            if (lettreLue == '\n') // Quand on trouve un \n c'est qu'il y a un nouveau mot
            {
                compteurEspace++; //on incrémente donc le nb d'espace (correspondant au nb de ligne)
            }
        }
        //une fois sortie de cette boucle on est donc juste devant le mot tiré
        //On fait un do while sinon le premier caractère sera \n
        do
        {
            lettreLue = fgetc(fichier);
            compteurLettre++; //on compte le nombre de lettre jusqu'a la fin de al ligne
        }
        while (lettreLue != '\n');
        compteurLettre--; //on retire 1 au compteur car il a compté le \n du début
        
    }
    return (compteurLettre);
}

void recupMot(int numeroMot,int tailleMot,char *motSecret) //ici on recupere le mot d'après son numéro
{
    FILE* fichier = NULL;
    char lettreLue = 0;
    int compteurEspace = 0;
    int compteurLettre = 0;
    int i = 0;

    fichier = fopen("dictionnaire","r"); // on ouvre le fichier dictionnaire en mode lecture
    if (fichier != NULL) //on test si l'ouverture a fonctionnée
    {
        rewind(fichier); //on place le curseur en haut du fichier
        while (compteurEspace != numeroMot-1) // Tant qu'on a pas atteind la ligne avant le mot tiré
        {
            lettreLue = fgetc(fichier); //on lit les caractères 1 à 1

            if (lettreLue == '\n') // Quand on trouve un \n c'est qu'il y a un nouveau mot
            {
                compteurEspace++; //on incrémente donc le nb d'espace (correspondant au nb de ligne)
            }
        }
        //une fois sortie de cette boucle on est donc juste devant le mot tiré
        do //on doit le faire 1 fois sinn la condition ne marche pas
        {
            lettreLue = fgetc(fichier);
            motSecret[i] = lettreLue;
            i++;
        }
        while (lettreLue != '\n');
    }
}

void affiche(char *motSecret, int tailleMot)//pour afficher le mot tiré
{
    int i;
    for ( i=0 ; i < tailleMot ; i++)
    {
        printf("%c",motSecret[i]);
    }
}

void creerMotMystere(int tailleMot, char *motMystere)//Creer un mot mystère de la taille de celui tiré
{
    int i;
    for (i=0; i<tailleMot; i++)
    {
        motMystere[i]= '*';
    }
}
