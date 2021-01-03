#include<gtk/gtk.h>

typedef struct{
	char cin[10];
	char code[5];
	char date[20];
}abscences;

typedef struct{
	char cin1[10];
	int percent;
}tache;

void abs_supprimer(char cin[]);
void consulter_ouvrier(abscences abs);
void afficher_abscence(GtkWidget *liste);
void best(char *meilleur);
void chercher(char cin[], GtkWidget *liste);
void checher_taches(char mini_cin[],int mini_code[],char *meilleur1);
void avancement(tache t);
int make_code(char cin1[]);
