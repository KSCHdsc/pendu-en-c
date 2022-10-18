#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <ctype.h>

char recupCaract ();//recupère les caractères saisie par l'utilisateur

int verification(char motDecouvert[]);//vérifie que le mot ne soit pas totalement découvert

int compteurMot();// on compte les mots présent dans le fichier

int tirageMot(int nombreDeMots);//tire au hasard un numéro d'après le nombre de mots

int tailleMot(int numeroMot);//calcul la taille d'un mot d'après sa position dans la liste

void recupMot(int numeroMot,int tailleMot,char *motSecret);//ici on recupere le mot d'après son numéro

void affiche(char *motSecret, int tailleMot);//pour afficher le mot tiré

void creerMotMystere(int tailleMot, char *motMystere);//Creer un mot mystère de la taille de celui tiré
