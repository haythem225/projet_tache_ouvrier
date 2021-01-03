#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "ouvrier.h"
#include "abscence.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int aa=0;
int jj=0;
int mm=0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_buttonAjouter1B_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
	ouv o; 
	GtkWidget *input1, *input2, *input3, *input4;
	GtkWidget *pt;
	GtkWidget *ajout_ouvrier;
	FILE* f;
	char msg[70]; int test; char x[20];

	input1 = lookup_widget(objet, "entryNom_ajout") ;
	input2 = lookup_widget(objet, "entryPrenom_ajout") ;
	input3 = lookup_widget(objet, "entryTelephone_ajout") ;
	input4 = lookup_widget(objet, "entryCIN_ajout") ;
	pt = lookup_widget(objet,"labelAjout");

	strcpy(o.nom,gtk_entry_get_text(GTK_ENTRY(input1)));
	strcpy(o.prenom,gtk_entry_get_text(GTK_ENTRY(input2)));
	strcpy(o.tel,gtk_entry_get_text(GTK_ENTRY(input3)));
	strcpy(o.cin,gtk_entry_get_text(GTK_ENTRY(input4)));
	
	test=O_trouve(o.cin);
	sprintf(x,"%d",test); 
	
	if (strcmp(x,"0")==0 && strlen(o.nom)!=0 && strlen(o.prenom)!=0 &&strlen(o.tel)!=0 && strlen(o.cin)==8 ){ 
		 O_ajouter(o);
		 sprintf(msg,"Ajout reussi!");
		 gtk_label_set_text(GTK_LABEL(pt),msg);
		}
	    else if (strlen(o.nom)==0 || strlen(o.prenom)==0|| strlen(o.tel)==0|| strlen(o.cin)==0 )
		{
		    sprintf(msg,"ERREUR: Veuillez remplir tous les champs.");
		    gtk_label_set_text(GTK_LABEL(pt),msg);
		}
	else if (strlen(o.cin)<8)
	{
		sprintf(msg,"ERREUR: Veuillez vérifier votre CIN!");
		    gtk_label_set_text(GTK_LABEL(pt),msg);
	}
	     else{
		    sprintf(msg,"ERREUR: Ouvrier déjà existant!");
		    gtk_label_set_text(GTK_LABEL(pt),msg);

		} 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_buttonHome_ajout_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *home,*window0,*window1,*window2,*window3,*window4 ;
	home=create_gestion_ouvrier();
	gtk_widget_show (home);
	window0=lookup_widget(objet,"ajout_ouvrier");
	gtk_widget_destroy(window0);
	window1=lookup_widget(objet,"supprime_ouvrier");
	gtk_widget_destroy(window1);
	window2=lookup_widget(objet,"modifier_ouvrier");
	gtk_widget_destroy(window2);
	window3=lookup_widget(objet,"consulter_ouvrier");
	gtk_widget_destroy(window3);
	window4=lookup_widget(objet,"affichage_ouvrier");
	gtk_widget_destroy(window4);


}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_button_ouvrier_mois_clicked         (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *ouvrier_mois1 ;
	//abscences abs;
	GtkWidget *out;
	char msg[177];
	//char *meilleur2;

	ouvrier_mois1=create_ouvrier_mois();

	gtk_widget_show(ouvrier_mois1);
	
	out = lookup_widget(objet,"label_ouvrier_mois");
	
	
	strcpy(msg,"haythem");
	gtk_label_set_text(GTK_LABEL(out),msg);
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_buttonAjout1A_clicked               (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget* window0, *window;
	window0=lookup_widget(objet,"gestion_ouvrier");
	gtk_widget_destroy(window0);

	window=create_ajout_ouvrier();
	gtk_widget_show(window);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_buttonSupprimer_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{

	GtkWidget* window0, *window;
	window0=lookup_widget(objet,"gestion_ouvrier");
	gtk_widget_destroy(window0);

	window=create_supprime_ouvrier();
	gtk_widget_show(window);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_buttonModifier_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
	
	GtkWidget* window0, *window;

	window0=lookup_widget(objet,"gestion_ouvrier");
	gtk_widget_destroy(window0);

	window=create_modifier_ouvrier();;
	gtk_widget_show(window);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_button_gestion_aff_ouv_clicked      (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window_gest, *window_consul ,*O_treeview;

	window_gest=lookup_widget(objet,"gestion_ouvrier");
	gtk_widget_destroy(window_gest);
	
	window_consul=create_affichage_ouvrier();
	gtk_widget_show(window_consul);

	O_treeview=lookup_widget(window_consul,"O_treeview");

	O_afficher(O_treeview);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_buttonConsulter_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{

	GtkWidget *consulter ;
	GtkWidget *aff;

	aff=lookup_widget(objet,"gestion_ouvrier");
	gtk_widget_destroy(aff);

	consulter=create_consulter_ouvrier();
	gtk_widget_show (consulter);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_buttonCIN_supp_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{

	GtkWidget* cin,*window_supp, *out;
	char id[20], msg[50]; 
	int test;

	window_supp=lookup_widget(objet,"supprime_ouvrier");
	cin=lookup_widget(objet,"entryCIN_supp");

	strcpy(id,gtk_entry_get_text(GTK_ENTRY(cin)));
	out = lookup_widget(objet,"labelSupp");
	
	if(strlen(id)==8){
		O_supprimer(id);
		abs_supprimer(id);
		sprintf(msg,"Suppression validé");
		gtk_label_set_text(GTK_LABEL(out),msg);
	}
	else{
		sprintf(msg,"Erreur : CIN invalid");
		gtk_label_set_text(GTK_LABEL(out),msg);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_buttonHome_supp_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_buttonHome_modif_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_button_retour_modif_clicked         (GtkWidget       *objet,
                                        gpointer         user_data)
{
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_buttonVerif_modif_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
	char ch_element[70]="",ch_value[20]="",cin1[20],ch[50]; 
	int e,test;
	GtkWidget *element,*val,*cin01,*pt;
	
	pt=lookup_widget(objet,"label_modif_reussi");

	
	cin01=lookup_widget(objet,"entry_cin_modif");
	strcpy(cin1,gtk_entry_get_text(GTK_ENTRY(cin01))); 
  
	element=lookup_widget(objet,"combobox1_modif");
	strcpy(ch_element,gtk_combo_box_get_active_text(GTK_COMBO_BOX(element)));

	val=lookup_widget(objet,"entry_info_modif");
	strcpy(ch_value,gtk_entry_get_text(GTK_ENTRY(val)));

	//gtk_label_set_text(GTK_LABEL(pt),ch_element);
	//c=int_ch(ch_element); 
	//sprintf(ch,"%d",e);
	//strcpy(ch,ch_element[0]);
	//sscanf(&ch,"%d",e); 
	//sprintf(ch,"%d",e);
	//sprintf(ch," %d",e);
	//gtk_label_set_text(GTK_LABEL(pt),ch);
	
	e=o_int_ch(ch_element); 
	//gtk_label_set_text(GTK_LABEL(pt),ch_value);
	test=O_modif(cin1,e,ch_value);

	sprintf(ch,"%d",test); 
	if ((strcmp(ch,"1")==0) && (strlen(ch_value)!=0) && (strlen(ch_element)!=0) && (strlen(cin1)!=0))
	{ 	
			 
		sprintf(ch,"Modification reussie!");
		gtk_label_set_text(GTK_LABEL(pt),ch);
		
	}
	else if ((strlen(ch_value)==0) || (strlen(ch_element)==0) || (strlen(cin1)==0))
	{
		sprintf(ch,"ERREUR : Veuillez remplir tous les champs.");
		gtk_label_set_text(GTK_LABEL(pt),ch);
	}
	else
	{			
		sprintf(ch,"ERREUR : identifiant inexistant");
		gtk_label_set_text(GTK_LABEL(pt),ch);
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_button_aff_modif_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window_gest, *window_consul ,*O_treeview;

	window_gest=lookup_widget(objet,"gestion_ouvrier");
	gtk_widget_destroy(window_gest);
	
	window_consul=create_affichage_ouvrier();
	gtk_widget_show(window_consul);

	O_treeview=lookup_widget(window_consul,"O_treeview");

	O_afficher(O_treeview);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_calendar1_day_selected              (GtkCalendar     *calendar,
                                        gpointer         user_data)
{
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_buttonHome_consult_clicked          (GtkWidget       *objet,
                                        gpointer         user_data)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_button_consult_clicked              (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *input1;
	GtkWidget *pt;
	FILE* f;
	
	abscences abs;
	abscences abs1;
	int mycode=1;

	char msg[70];
	int test;
	char cin1[20];
	char datte[20];
	char ch[20];

	pt=lookup_widget(objet,"labelabs_reussit");

	input1 = lookup_widget(objet,"entry_cin_consulter") ;
	//fflush(stdin);
	strcpy(abs1.cin,gtk_entry_get_text(GTK_ENTRY(input1)));

	mycode=make_code(abs1.cin);
	sprintf(ch,"%d",mycode);

	strcpy(abs1.code,ch);

	sprintf(datte,"%d/%d/%d",jj,mm,aa);
	strcpy(abs1.date,datte);


	
	if((strlen(abs1.cin)==8 && O_trouve(abs1.cin)==1)){
		consulter_ouvrier(abs1);
		sprintf(msg,"Abscence confirmée");
		gtk_label_set_text(GTK_LABEL(pt),msg);
	}
	else if (O_trouve(abs1.cin)!=1)
{
		sprintf(msg,"Ouvrier non existant");
		gtk_label_set_text(GTK_LABEL(pt),msg);
}
	else{
		sprintf(msg,"Erreur : Longeur de num CIN invalid");
		gtk_label_set_text(GTK_LABEL(pt),msg);
	}

}
	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_buttonAfficheAbs_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window_consulter, *window_aff ,*abs_treeview;

	window_consulter=lookup_widget(objet,"consulter_ouvrier");
	gtk_widget_destroy(window_consulter);
	
	window_aff=create_affichage_abscence();
	gtk_widget_show(window_aff);

	abs_treeview=lookup_widget(window_aff,"treeview_abs");

	afficher_abscence(abs_treeview);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_button_chercher_abs_clicked         (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *window_consulter, *window_aff ,*abs_indiv_treeview;
	GtkWidget *input;
	char cin00[20];
	
	

	window_consulter=lookup_widget(objet,"consulter_ouvrier");

	input=lookup_widget(objet,"entry_cin_consulter");
	strcpy(cin00,gtk_entry_get_text(GTK_ENTRY(input)));

	gtk_widget_destroy(window_consulter);

	window_aff=create_abscence_indiv();
	gtk_widget_show(window_aff);

	abs_indiv_treeview=lookup_widget(window_aff,"treeview_abs_indiv");

	chercher(cin00,abs_indiv_treeview);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_buttonRetour_consulter_clicked      (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *gestion ;
	GtkWidget* window0;

	window0=lookup_widget(objet,"consulter_ouvrier");
	gtk_widget_destroy(window0);

	gestion=create_gestion_ouvrier();
	gtk_widget_show (gestion);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_treeview_abs_row_activated          (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_buttonRetour_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_btn_home_aff_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_treeview_ouvrier_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_button_retour_aff_ouv_clicked       (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *gestion ;
	GtkWidget *aff;
	
	aff=lookup_widget(objet,"affichage_ouvrier");
	gtk_widget_destroy(aff);
	
	gestion=create_gestion_ouvrier();
	gtk_widget_show (gestion);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_button_confirmer_avancement_clicked (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *input1;
	GtkWidget *pt;
	GtkWidget *avancement11;
	FILE* f;
	
	tache t;
	abscences abs;

	char msg[70];
	int test;
	
	pt=lookup_widget(objet,"label_out_avancement");

	input1 = lookup_widget(objet, "entry_cin_avancement") ;
	strcpy(t.cin1,gtk_entry_get_text(GTK_ENTRY(input1)));

	
	avancement11=lookup_widget(objet,"spinbutton1");
	t.percent=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(avancement11));

	if(strlen(t.cin1)==8 && O_trouve(t.cin1)){
		avancement(t);
		sprintf(msg,"Avancement confirmé");
		gtk_label_set_text(GTK_LABEL(pt),msg);
	}
	else if (strlen(t.cin1)==0){
		sprintf(msg,"Veuillez remplir tous les champs");
		gtk_label_set_text(GTK_LABEL(pt),msg);
	}
	else{
		sprintf(msg,"Erreur : Longeur de num CIN invalid");
		gtk_label_set_text(GTK_LABEL(pt),msg);
	}
		
	
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_treeview_abs_indiv_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_button_avancement_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *avancement1 ;
	GtkWidget *gestion;

	gestion=lookup_widget(objet,"gestion_ouvrier");
	gtk_widget_destroy(gestion);

	avancement1=create_avancement();
	gtk_widget_show (avancement1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_button_retour_supp_ouv_clicked      (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *gestion ;
	GtkWidget *supp;

	supp=lookup_widget(objet,"supprime_ouvrier");
	gtk_widget_destroy(supp);

	gestion=create_gestion_ouvrier();
	gtk_widget_show (gestion);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_button_home_list_ouv_clicked        (GtkWidget       *objet,
                                        gpointer         user_data)
{
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_button_retour_avancement_clicked    (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *gestion ;
	GtkWidget *supp;

	supp=lookup_widget(objet,"avancement");
	gtk_widget_destroy(supp);

	gestion=create_gestion_ouvrier();
	gtk_widget_show (gestion);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_button_retour_ajout_clicked         (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *gestion ;
	GtkWidget *supp;

	supp=lookup_widget(objet,"ajout_ouvrier");
	gtk_widget_destroy(supp);

	gestion=create_gestion_ouvrier();
	gtk_widget_show (gestion);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_buttonRetourModif_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *retour ;
	GtkWidget* window0, *window;
	
	window0=lookup_widget(objet,"modifier_ouvrier");
	gtk_widget_destroy(window0);

	retour=create_gestion_ouvrier();
	gtk_widget_show (retour);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_calendar_abs_day_selected           (GtkCalendar     *calendar,
                                        gpointer         user_data)
{
	gtk_calendar_get_date(calendar,&jj,&mm,&aa);
	mm+=1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_button_retour_indiv_clicked         (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *consult;
	GtkWidget *aff;

	aff=lookup_widget(objet,"abscence_indiv");
	gtk_widget_destroy(aff);

	consult=create_consulter_ouvrier();
	gtk_widget_show (consult);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
on_buttonRetour_aff_abs_clicked        (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *consult;
	GtkWidget *aff;

	aff=lookup_widget(objet,"affichage_abscence");
	gtk_widget_destroy(aff);

	consult=create_consulter_ouvrier();
	gtk_widget_show (consult);
}

