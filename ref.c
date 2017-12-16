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

void		Uvolnit (ZAZNAM *p_prv,int *poc_zaznamov){
int i;
ZAZNAM *p_akt,*p_uvolnit;

p_akt=p_prv;
	for (i=1;i<=*poc_zaznamov;i++)
		{
		p_uvolnit=p_akt;
		p_akt=p_akt->dalsi;
		free(p_uvolnit);
		}
}

char		Uprava (char str[201]){
	str[strlen(str)+1]='\0';
	str[strlen(str)]='\n';
	return *str;
}

char		Zmensenie (char str[51]){
	int i;
	for (i=0;(str[i])!= '\0';i++)
		{
		str[i] = (tolower(str[i]));					
		str[strlen(str)]='\0';
		}
	return *str;
}

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
	Uvolnit(p_prv,poc_zaznamov);

	p_prv=(ZAZNAM *)malloc(sizeof(ZAZNAM));			
while ((fgets(q,3,fr))!=NULL)
{
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

	Uprava(p_novy->kategoria);
	Uprava(p_novy->znacka);
	Uprava(p_novy->predajca);
	Uprava(p_novy->stav);
 
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
char zadana_znacka[51];
int i,pom_pocet,a=0;

scanf (" %s",zadana_znacka);

	Zmensenie (zadana_znacka);

	pom_pocet=*poc_zaznamov;
	p_pred=p_prv;			
	p_akt=p_prv;

	for (i=1;i<=pom_pocet;i++)
	{
		a++;
		Zmensenie (p_akt->znacka);
				
		if ((strstr(p_akt->znacka,zadana_znacka))!=0)
		{
				if (p_prv==p_akt){
						p_prv=p_akt->dalsi;
						free(p_akt);					
						p_akt=p_prv;
						p_pred=p_prv;
						(*poc_zaznamov)--;
						a--;}
				else{ 
						p_pred->dalsi=p_akt->dalsi;
						free(p_akt);					
						p_akt=p_pred->dalsi;
						(*poc_zaznamov)--;}							
			}
		else{ 
			p_akt=p_akt->dalsi;
			if (a>=2)p_pred=p_pred->dalsi;
			}										
	}
	printf ("Vymazalo sa %d zaznamov.\n",pom_pocet-*poc_zaznamov);
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
int zadana_c,i,poc_a=0;
char zadana_z[51];
ZAZNAM *p_akt,*p_aktualizovany;

scanf ("\n");
gets(zadana_z);
Uprava(zadana_z);

scanf(" %d",&zadana_c);

p_akt=p_prv;
for (i=1;i<=*poc_zaznamov;i++)
{
	if ((!strcmp(zadana_z,(p_akt->znacka)))&&(zadana_c==(p_akt->cena)))		
	{
		poc_a++;
		if (poc_a==1)					
			{
			p_aktualizovany=(ZAZNAM *)malloc(sizeof(ZAZNAM));
			scanf ("\n");
			gets(p_aktualizovany->kategoria);
			gets(p_aktualizovany->znacka);
			gets(p_aktualizovany->predajca);
			scanf("%d\n", &p_aktualizovany->cena);
			scanf(" %d\n", &p_aktualizovany->rok);
			scanf ("\n");
			gets(p_aktualizovany->stav); 

			Uprava(p_aktualizovany->kategoria);	
			Uprava(p_aktualizovany->znacka);
			Uprava(p_aktualizovany->predajca);
			Uprava(p_aktualizovany->stav);
			}
		strcpy(p_akt->kategoria,p_aktualizovany->kategoria);				
		strcpy(p_akt->znacka,p_aktualizovany->znacka);
		strcpy(p_akt->predajca,p_aktualizovany->predajca);
		p_akt->cena = p_aktualizovany->cena;
		p_akt->rok = p_aktualizovany->rok;
		strcpy(p_akt->stav,p_aktualizovany->stav);
	}
	p_akt=p_akt->dalsi;
}

printf ("\nAktualizovalo sa %d zaznamov.\n",poc_a);
free(p_aktualizovany);
return p_prv;
}


int			konec (ZAZNAM *p_prv,int *poc_zaznamov,int poc_n)
{
ZAZNAM *p_akt,*p_uvolnit;
int i;

if (poc_n!=0)			
	Uvolnit(p_prv,poc_zaznamov);

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