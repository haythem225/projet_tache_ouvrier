#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include<gtk/gtk.h>
#include"ouvrier.h"
#include"abscence.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum
{
	ECIN,
	ECODE,
	EDATE,
	COLUMNS,
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void abs_supprimer(char cin[])
{
	FILE *f,*f_temp;
	int test ;
	abscences abs;


	f=fopen("abscence.txt","r");
	f_temp=fopen("fichAux.txt","w");

	if((f != NULL)&&(f_temp != NULL)){
		while (fscanf(f,"%s %s %s\n",abs.cin,abs.code,abs.date)!=EOF){
			if(strcmp(abs.cin,cin)!=0){
				fprintf(f_temp,"%s %s %s\n",abs.cin,abs.code,abs.date);
			}
		}
		fclose(f);
		fclose(f_temp);
	}
	remove("abscence.txt");
	rename("fichAux.txt","abscence.txt");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void consulter_ouvrier( abscences abs)
{
	FILE *f=NULL;

	f=fopen("abscence.txt","a+");
	if(f != NULL){
		fprintf(f,"%s %s %s\n",abs.cin,abs.code,abs.date);
	}
	fclose(f);

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void afficher_abscence(GtkWidget *liste)
{
	GtkCellRenderer *renderer;  //envoyer la saisir de l'utilisateur de 		chaque champ 
	GtkTreeViewColumn *column;//correspendre le contenue du champ a son 		attribue de la liste
	GtkTreeIter   iter;    //itterateur sur l'ensemble des elements de 		treeview
	GtkListStore  *store;    //l'enregistrement de treeview

	char cin[20];
	char code[5];
	char date[12];

	store = NULL;
	FILE *f;

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("CIN",renderer,"text",ECIN,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Code abscence",renderer,"text",ECODE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date d'abscence",renderer,"text",EDATE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);



	store = gtk_list_store_new (COLUMNS, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	
	f = fopen("abscence.txt","r");

	if(f == NULL){
		return;
	}
	else{
		f=fopen("abscence.txt","a+");
		while(fscanf(f,"%s %s %s\n",cin,code,date) != EOF){
			gtk_list_store_append(store,&iter);
			
			
			gtk_list_store_set(store,&iter,ECIN,cin,ECODE,code,EDATE,date,-1);
		}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref(store);
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void checher_taches(char mini_cin[],int mini_code[],char *meilleur)
{
	FILE *f1;
	int j,i,taille;
	tache t;

	int tpercent[100];
	char tcin[100];
	int max;
	int indx;
	ouv o2;
	
	char cin1[8];

	f1=fopen("listeDesTaches.txt","r");
	while(fscanf(f1,"%s %d",t.cin1,t.percent)!=EOF){
		strcpy(tcin[i],t.cin1);
		tpercent[i]=t.percent;
		i++;
	}

	taille=i;
	max=tpercent[0];

	for(j=1;j<taille;j++){
		if(max<tpercent[j]){
			max=tpercent[j];
			indx=j;
		}
	}


	while (fscanf(f1,"%s %s %s %s",o2.nom,o2.prenom,o2.tel,o2.cin)!=EOF){
		if(strcmp(cin1,tcin[indx])==0){
			strcpy(meilleur,o2.nom);
			strcat(meilleur,"_");
			strcat(meilleur,o2.prenom);
		}
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void best(char *meilleur1)
{
	FILE *f1,*f2;
	abscences abs;
	
	
	int tcode[100];
	char tcin[100][20];

	int mini_code[100];
	char mini_cin[100][20];

	int code123;

	int i=0,taille=0,j;
	int min;
	int indx;

	f1=fopen("ouvrier.txt","r");
	f2=fopen("abscence.txt","r");

	if((f1 != NULL)&&(f2 != NULL)){
		while (fscanf(f2,"%s %s %s",abs.cin,abs.code,abs.date)!=EOF){
			strcpy(tcin[i],abs.cin);
			code123=atoi(abs.code);
			tcode[i]=code123;
			i++;
		}

		taille=i;
		min=tcode[0];

		for(j=1;j<taille;j++){
			if(min>tcode[j]){
				min=tcode[j];
				indx=j;
			}
		}

		i=0;
		for(j=0;j<taille;j++){
			if(min = tcode[j]){
				mini_code[i] = tcode[j];
				strcpy(mini_cin[i],tcin[j]);
				i++;
			}
		}
		checher_taches(mini_cin,mini_code,&meilleur1);

		
	}


	fclose(f1);
	fclose(f2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void chercher(char cin[], GtkWidget *liste)
{
	GtkCellRenderer *renderer;  //envoyer la saisir de l'utilisateur de 		chaque champ 
	GtkTreeViewColumn *column;//correspendre le contenue du champ a son 		attribue de la liste
	GtkTreeIter   iter;    //itterateur sur l'ensemble des elements de 		treeview
	GtkListStore  *store;    //l'enregistrement de treeview

	char cin1[20];
	char code[5];
	char date[12];

	store = NULL;
	FILE *f;

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("CIN",renderer,"text",ECIN,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Code abscence",renderer,"text",ECODE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Date d'abscence",renderer,"text",EDATE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	store = gtk_list_store_new (COLUMNS, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	
	f = fopen("abscence.txt","r");

	if(f == NULL){
		return;
	}
	else{
		f=fopen("abscence.txt","a+");
		while(fscanf(f,"%s %s %s \n",cin1,code,date) != EOF){
			if(strcmp(cin1,cin)==0){
				gtk_list_store_append(store,&iter);

				gtk_list_store_set(store,&iter,ECIN,cin1,ECODE,code,EDATE,date,-1);
			}
		}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref(store);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void avancement(tache t)
{

	FILE *f=NULL;
	FILE *f_tmp=NULL;
	int test=0;
	char ch1[8];
	int ava;


	f=fopen("listeDesTaches.txt","r+");
	f_tmp=fopen("fichAux.txt","w+");

	if((f != NULL)&&(f_tmp != NULL)){
		while (fscanf(f,"%s %d \n",ch1,ava)!=EOF){
			if(strcmp(ch1,t.cin1)==0){
				fprintf(f_tmp,"%s %d\n",ch1,t.percent);
			}
			else {
				fprintf(f_tmp,"%s %d \n",ch1,ava);
			}
		}
		fclose(f);
		fclose(f_tmp);
	}
	remove("listeDesTaches.txt");
	rename("fichAux.txt","listeDesTaches.txt");


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int make_code(char cin1[])
{
	FILE *f;
	abscences abs;
	int codee=1;
	f=fopen("abscence.txt","r");
	if(f!=NULL){
		while(fscanf(f,"%s %s %s",abs.cin,abs.code,abs.date)!=EOF){
			if(strcmp(cin1,abs.cin)==0){
				codee=atoi(abs.code);
				codee+=1;
			}
		}
	}
	fclose(f);
	return (codee);
}



////////////////////////////////////////////////////////////////////////////


