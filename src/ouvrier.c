#include <gtk/gtk.h>
#include "ouvrier.h"
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
enum
{
	OCIN,
	ONOM,
	OPRENOM,
	OTEL,
	COLUMNS,
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void O_ajouter( ouv o) 
{
	FILE* f; 
 
   	f=fopen("ouvrier.txt","a+");
    	if (f!=NULL){
        	fprintf(f,"%s %s %s %s \n", o.cin, o.nom, o.prenom, o.tel);   
    	}
	fclose(f);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int O_trouve(char cin[])
{

	FILE* f; int test=0; char ch[20];
	f=fopen("ouvrier.txt","a"); fclose(f);
	f=fopen("ouvrier.txt","r");
	if (f!=NULL){
		while(fscanf(f,"%s %*s %*s %*s \n",ch)!=EOF){	
			if (strcmp(cin,ch)==0)
				test=1;
		}
	}
	fclose(f);
	return test;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int O_modif(char cin[],int choice,char modif[])
{
	FILE* fw;
	FILE* f; 
	int test=0;
	char ch1[20];
	char ch2[20];
	char ch3[20];
	char ch4[20];
	
	f=fopen("ouvrier.txt","r"); 
	fw=fopen("fichierAUX.txt","a+");
	if ((fw!=NULL) && (f!=NULL)){
		while (fscanf (f, "%s %s %s %s \n",ch1,ch2,ch3,ch4)!=EOF){
			if (strcmp (ch1,cin) == 0){
				test=1;
				switch (choice)
				{	
					case 1:
						fprintf (fw, "%s %s %s %s \n",ch1,modif,ch3,ch4);
						break;
                        		case 2:
                           			fprintf (fw, "%s %s %s %s \n",ch1,ch2,modif,ch4);
                           			break;
					case 3:
                            			fprintf (fw, "%s %s %s %s \n",ch1,ch2,ch3,modif);
                            			break;
					
                       		}
                	}
			else{
				fprintf (fw, "%s %s %s %s \n",ch1,ch2,ch3,ch4);
			}
		}
	}
	fclose(f); fclose(fw);
	remove("ouvrier.txt");
	rename("fichierAUX.txt","ouvrier.txt");
	return test;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void O_supprimer(char cin[])
{
	FILE *f,*f_temp;
	int test ;
	char ch1[20];
	char ch2[20];
	char ch3[20];
	char ch4[20];


	f=fopen("ouvrier.txt","r");
	f_temp=fopen("fichAux.txt","w");

	if((f != NULL)&&(f_temp != NULL)){
		while (fscanf(f,"%s %s %s %s\n",ch1,ch2,ch3,ch4)!=EOF){
			if(strcmp(ch1,cin)!=0){
				fprintf(f_temp,"%s %s %s %s\n",ch1,ch2,ch3,ch4);
			}
		}
		fclose(f);
		fclose(f_temp);
	}
	remove("ouvrier.txt");
	rename("fichAux.txt","ouvrier.txt");

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void O_afficher(GtkWidget* liste)
{
	GtkCellRenderer *renderer;  //envoyer la saisir de l'utilisateur de 		chaque champ 
	GtkTreeViewColumn *column;//correspendre le contenue du champ a son 		attribue de la liste
	GtkTreeIter   iter;    //itterateur sur l'ensemble des elements de 		treeview
	GtkListStore  *store;    //l'enregistrement de treeview

   char cin[20];
    char nom[20];
    char prenom[20];
    char tel[20];


	
	 store=NULL;
	 FILE *F;

	store=gtk_tree_view_get_model(liste);//va prendre comme variable de la liste
	if(store==NULL)
	{
	renderer = gtk_cell_renderer_text_new (); //cellule contenant du texte
	column = gtk_tree_view_column_new_with_attributes("CIN:", 		renderer,"text",OCIN,NULL);//creation d'une colonne avec du 		texte
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);//associer 		la colonne à l'afficher (GtkTreeView);

	renderer = gtk_cell_renderer_text_new (); 
	column = gtk_tree_view_column_new_with_attributes("NOM:", 		  renderer,"text",ONOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new (); 
	column = gtk_tree_view_column_new_with_attributes("PRENOM:", 		  renderer,"text",OPRENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new (); 
	column = gtk_tree_view_column_new_with_attributes("TELEPHONE", 		renderer,"text",OTEL,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	
	}
//lA liste contient 7 colonnes de type chaine de caracteres
	store=gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
F=fopen("ouvrier.txt","r");
if(F==NULL)
{
	return;
}
else
{ 
   F=fopen("ouvrier.txt","a+");
   while(fscanf(F,"%s %s %s %s \n",cin,nom,prenom,tel)!=EOF)
{       

        	
gtk_list_store_append (store, &iter);//variable intermediaire store
	gtk_list_store_set (store, &iter,OCIN,cin,ONOM,nom,OPRENOM,prenom,OTEL,tel, -1);//correspondre chaque champ a mon variable
}
	fclose(F);
	gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));//
	g_object_unref (store);
}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int o_int_ch(char ch[])
{
	if (ch[0]=='1')
		return 1;
	else if (ch[0]=='2')
		return 2;
	else if (ch[0]=='3')
		return 3;

}
