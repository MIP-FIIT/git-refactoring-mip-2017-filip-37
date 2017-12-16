#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct zaznam {
	char kategoria [51];
	char znacka [51];
	char predajca [101];			
	int cena;
	int rok;
	char stav [201];
	struct zaznam *dalsi;
} ZAZNAM;			




ZAZNAM		*nacitaj (int *poc_zaznamov,int poc_n,ZAZNAM *p_prv)
{
FILE *fr;
int i;
char q[3];
ZAZNAM  *p_akt,*p_uvolnit;

fr=fopen("auta.txt","r");

if (fr==NULL) {
	printf ("Zaznamy neboli nacitane");
	return NULL;
}
	
if (poc_n!=0)									
{
	p_akt=p_prv;
	for (i=1;i<=*poc_zaznamov;i++)
		{
		p_uvolnit=p_akt;
		p_akt=p_akt->dalsi;
		free(p_uvolnit);
		}
}
p_prv=(ZAZNAM *)malloc(sizeof(ZAZNAM));			
while ((fgets(q,3,fr))!=NULL)	{

	if (q[0] =='$')
	(*poc_zaznamov)++;
}								

rewind(fr);
p_akt=p_prv;

for (i=1;i<=*poc_zaznamov;i++)
{
fgets(q,3,fr);																				

fgets(p_akt->kategoria,51,fr);
fgets(p_akt->znacka,51,fr);
fgets(p_akt->predajca,101,fr);
fscanf (fr,"%d\n",&p_akt->cena);
fscanf (fr,"%d\n",&p_akt->rok);
fgets(p_akt->stav,201,fr);

p_akt->dalsi = (ZAZNAM *) malloc(sizeof(ZAZNAM));		

p_akt=p_akt->dalsi;								
}
printf ("Nacitalo sa %d zaznamov\n",*poc_zaznamov);
fclose(fr); 

return p_prv;
}			


void		vypis (int *poc_zaznamov,ZAZNAM *p_prv)
{
ZAZNAM *p_akt;
int i=1;

p_akt=p_prv;

for (i=1;i<=*poc_zaznamov;i++){			

printf ("%d.\n",i);
printf ("kategoria: %s",p_akt->kategoria);
printf ("znacka: %s",p_akt->znacka);
printf ("predajca: %s",p_akt->predajca);
printf ("cena: %d\n",p_akt->cena);
printf ("rok_vyroby: %d\n",p_akt->rok);
printf ("stav_vozidla: %s",p_akt->stav);

p_akt=p_akt->dalsi;
	}
}


ZAZNAM		*pridat (int *poc_zaznamov,ZAZNAM *p_prv)
{
int poz,i;
ZAZNAM *p_akt,*p_novy;

scanf (" %d",&poz);

p_akt=p_prv;
p_novy=(ZAZNAM *)malloc(sizeof(ZAZNAM));		
	
	scanf ("\n");
	gets(p_novy->kategoria);
	gets(p_novy->znacka);
	gets(p_novy->predajca);
	scanf("%d\n", &p_novy->cena);
	scanf(" %d\n", &p_novy->rok);
	scanf ("\n");
	gets(p_novy->stav); 

	p_novy->kategoria[strlen(p_novy->kategoria)+1]='\0';
	p_novy->kategoria[strlen(p_novy->kategoria)]='\n';	
	p_novy->znacka[strlen(p_novy->znacka)+1]='\0';
	p_novy->znacka[strlen(p_novy->znacka)]='\n';
	p_novy->predajca[strlen(p_novy->predajca)+1]='\0';
	p_novy->predajca[strlen(p_novy->predajca)]='\n';
	p_novy->stav[strlen(p_novy->stav)+1]='\0';
	p_novy->stav[strlen(p_novy->stav)]='\n';
 
	if	((poz==1)||(*poc_zaznamov==0))		
	{
		p_novy->dalsi=p_akt;	
		p_prv=p_novy;	
	}
	else
	{
		if (poz>*poc_zaznamov) poz=*poc_zaznamov+1;		

		for (i=1;i<=poz-2;i++)		
			p_akt=p_akt->dalsi;

		p_novy->dalsi=p_akt->dalsi;		
		p_akt->dalsi=p_novy;
	}
(*poc_zaznamov)++;	
return p_prv;
}


ZAZNAM		*zmazat (int *poc_zaznamov,ZAZNAM *p_prv)
{
ZAZNAM *p_akt,*p_pred;													
char zadana_znacka[51],mala_znacka[51],mala_znacka_2[51];
int i,j,cyklus,a=0;

scanf (" %s",zadana_znacka);

	for (i=0;(zadana_znacka[i])!= '\0';i++)				
		{
		mala_znacka[i] = (tolower(zadana_znacka[i]));						
		mala_znacka[strlen(zadana_znacka)]='\0';
		}
	
	cyklus=*poc_zaznamov;
	p_pred=p_prv;			
	p_akt=p_prv;

	for (i=1;i<=cyklus;i++)
	{
		a++;
		strcpy(mala_znacka_2,p_akt->znacka);

		for (j=0;(mala_znacka_2[j])!= '\0';j++){
			mala_znacka_2[j] = (tolower(mala_znacka_2[j]));					
			mala_znacka_2[strlen(mala_znacka_2)]='\0';}
				
		if((strstr(mala_znacka_2,mala_znacka))!=0)		{
				if ((p_prv==p_akt)&&(*poc_zaznamov>1)){
						p_prv=p_akt->dalsi;
						free(p_akt);					
						p_akt=p_prv;
						p_pred=p_prv;
						*poc_zaznamov=*poc_zaznamov -1 ;
						a--;}
				else{ 
						p_pred->dalsi=p_akt->dalsi;
						free(p_akt);					
						p_akt=p_pred->dalsi;
						*poc_zaznamov=*poc_zaznamov -1 ;}							
			}
		else{ 
			p_akt=p_akt->dalsi;
			if (a>=2)p_pred=p_pred->dalsi;}										
	}
	printf ("Vymazalo sa %d zaznamov.\n",cyklus-*poc_zaznamov);
	return p_prv;
}


void		hladat (int *poc_zaznamov,ZAZNAM *p_prv)
{
int hladana_cena,i,poc=0;
ZAZNAM *p_akt;

scanf (" %d",&hladana_cena);

p_akt=p_prv;

for (i=1;i<=*poc_zaznamov;i++){	

	if	((p_akt->cena)<=hladana_cena)			
			{
			poc++;
			printf ("%d.\n",poc);
			printf ("kategoria: %s",p_akt->kategoria);
			printf ("zancka: %s",p_akt->znacka);
			printf ("predajca: %s",p_akt->predajca);
			printf ("cena: %d\n",p_akt->cena);
			printf ("rok_vyroby: %d\n",p_akt->rok);
			printf ("stav_vozidla: %s\n",p_akt->stav);
			p_akt=p_akt->dalsi;
			}
	else p_akt=p_akt->dalsi;
}
if (poc==0) printf ("V ponuke su len auta s vyssou cenou");
}


ZAZNAM		*aktualizacia (int *poc_zaznamov,ZAZNAM *p_prv)
{
int zadana_c=0,i,c,r,poc_a=0,a;
char zadana_z[51],k[51],z[51],p[101],s[201];
ZAZNAM *p_akt;
	
scanf(" %s",zadana_z);
a=strlen(zadana_z);
zadana_z[a]='\n';
zadana_z[a+1]='\0';

scanf(" %d",&zadana_c);

p_akt=p_prv;
for (i=1;i<=*poc_zaznamov;i++){

	if ((!strcmp(zadana_z,(p_akt->znacka)))&&(zadana_c==(p_akt->cena)))		
	{
		poc_a++;
		if (poc_a==1)					
			{
			scanf("%s",k);
			a=strlen(k);
			k[a]='\n';
			k[a+1]='\0';
			scanf("%s",z);
			a=strlen(z);
			z[a]='\n';
			z[a+1]='\0';
			scanf("%s",p);
			a=strlen(p);
			p[a]='\n';
			p[a+1]='\0';
			scanf("%d",&c);
			scanf("%d",&r);
			scanf("%s",s);
			a=strlen(s);
			s[a]='\n';
			s[a+1]='\0';
			}
		strcpy(p_akt->kategoria,k);				
		strcpy(p_akt->znacka,z);
		strcpy(p_akt->predajca,p);
		p_akt->cena = c;
		p_akt->rok = r;
		strcpy(p_akt->stav,s);
	}
	p_akt=p_akt->dalsi;
}

printf ("\nAktualizovalo sa %d zaznamov.\n",poc_a);
return p_prv;
}


int			konec (ZAZNAM *p_prv,int *poc_zaznamov,int poc_n)
{
ZAZNAM *p_akt,*p_uvolnit;
int i;
if (poc_n!=0)			
{
	p_akt=p_prv;
		for (i=1;i<=*poc_zaznamov;i++)
			{
			p_uvolnit=p_akt;
			p_akt=p_akt->dalsi;
			free(p_uvolnit);
			}
}
return 1;
}


int			main ()
{
ZAZNAM *p_prv=NULL;
char pismeno;
int poc_zaznamov=0,poc_n=0,k=0,otvorenie_suboru=0;

do{
	scanf (" %c",&pismeno);
	switch (pismeno){
	

	case 'n' :	p_prv=nacitaj(&poc_zaznamov,poc_n,p_prv) ;
				poc_n=1;		
				break;
	
	case 'v' :  if (poc_n==1)		
				{vypis (&poc_zaznamov,p_prv);}
				break;
	
	case 'p' :	p_prv=pridat(&poc_zaznamov,p_prv);
				poc_n=1;			
				break;
	
	case 'z' :	if (poc_n==1)		
				{p_prv=zmazat(&poc_zaznamov,p_prv);}
				break;
	
	case 'h' :	if (poc_n==1)		
				{hladat(&poc_zaznamov,p_prv);}
				break;
	
	case 'a' :	if (poc_n==1)		 
				{p_prv=aktualizacia(&poc_zaznamov,p_prv);}
				break;
	
	case 'k' :	 if (poc_n==1){
				k=konec(p_prv,&poc_zaznamov,poc_n);
				break;}
				k=1;
				break;

}
}while (k!=1);}