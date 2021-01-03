#include <gtk/gtk.h>

typedef struct
{
char nom[20];
char prenom[20];
char tel[20];
char cin[20];
}ouv;

void O_ajouter(ouv o); 
void O_supprimer(char cin[]);
int O_trouve(char cin[]);
int O_modif (char cin[],int choice,char modif[]);
void O_afficher(GtkWidget* liste);
int o_int_ch(char ch[]);
