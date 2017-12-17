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

void		Uvolnit	(ZAZNAM *p_prv,int *poc_zaznamov)	/* Funkcia na uvolnenie existujuceho spajaneho zoznamu */
{
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

char		Uprava (char str[201])	/* Funkcia na upravu stringu na tvar potrebny pri vypise */
{
	str[strlen(str)+1]='\0';
	str[strlen(str)]='\n';
	return *str;
}

char		Zmensenie (char str[51])	/* Funkcia na zmensenie znakov stringu */
{
	int i;
	for (i=0;(str[i])!= '\0';i++)
		{
		str[i] = (tolower(str[i]));					
		str[strlen(str)]='\0';
		}
	return *str;
}

ZAZNAM		*nacitaj (int *poc_zaznamov,int poc_n,ZAZNAM *p_prv)	/* Funkcia na nacitanie informacii zo suboru 'auta.txt' */
{
FILE *fr;
int i;
char $[3];
ZAZNAM  *p_akt,*p_uvolnit;

fr=fopen("auta.txt","r");

if (fr==NULL)
	{
	printf ("Zaznamy neboli nacitane");
	return NULL;
	}
	
if (poc_n!=0)									
	Uvolnit(p_prv,poc_zaznamov);	/* Pokila zoznam existoval funkcia ho uvolni */

p_prv=(ZAZNAM *)malloc(sizeof(ZAZNAM));			

while ((fgets($,3,fr))!=NULL)	/* Spocitanie zaznamov v subove podla pociatocneho znaku */
	{
	if ($[0] =='$')
	(*poc_zaznamov)++;
	}								

rewind(fr);
p_akt=p_prv;

for (i=1;i<=*poc_zaznamov;i++)
{
fgets($,3,fr);																				

fgets(p_akt->kategoria,51,fr);	/* Nacitanie informacii zo suboru */
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

void		vypis (int *poc_zaznamov,ZAZNAM *p_prv)	/* Funkcia na vypis nacitanych informacii */
{
ZAZNAM *p_akt;
int i;

p_akt=p_prv;
for (i=1;i<=*poc_zaznamov;i++)
	{			
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

ZAZNAM		*pridat (int *poc_zaznamov,ZAZNAM *p_prv)	/* Funkcia na pridanie zaznamu do spajaneho zoznamu */
{
int pozicia,i;
ZAZNAM *p_akt,*p_novy;

scanf (" %d",&pozicia);

p_akt=p_prv;
p_novy=(ZAZNAM *)malloc(sizeof(ZAZNAM));		
	
	scanf ("\n");				/* nacitanie noveho zaznamu */
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
 
	if	((pozicia==1)||(*poc_zaznamov==0))		/* Ak pridavame zaznamu na prve miesto alebo do prazdneho zoznamu */
		{
		p_novy->dalsi=p_akt;	
		p_prv=p_novy;	
		}
	else
		{
		if (pozicia>*poc_zaznamov) pozicia=*poc_zaznamov+1;		 /* Ak je pozicia vacsia ako pocet zaznamov , zaznam sa prida na koniec */

		for (i=1;i<=pozicia-2;i++)		
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
int i,pom_pocet,posuvanie_pred=0;

scanf (" %s",zadana_znacka);	/* Nacitanie a uprava znacky */
	Zmensenie (zadana_znacka);

pom_pocet=*poc_zaznamov;
p_pred=p_prv;			
p_akt=p_prv;

for (i=1;i<=pom_pocet;i++)
	{
	posuvanie_pred++;
	Zmensenie (p_akt->znacka);
				
		if ((strstr(p_akt->znacka,zadana_znacka))!=0)	/* Pokial je zadana znacka podretazec tej v zazname tak sa zaznam zmaze */
		{
		if (p_prv==p_akt)	
			{
			p_prv=p_akt->dalsi;
			free(p_akt);					
			p_akt=p_prv;
			p_pred=p_prv;
			(*poc_zaznamov)--;
			posuvanie_pred--;
			}
			else{ 
				p_pred->dalsi=p_akt->dalsi;
				free(p_akt);					
				p_akt=p_pred->dalsi;
				(*poc_zaznamov)--;
				}							
		}
		else
		{ 
		p_akt=p_akt->dalsi;
		if (posuvanie_pred>=2)	p_pred=p_pred->dalsi;	/* Ak je aktualny zaznam o 2 zaznamy dalej ako predchadzajuci tak predchadzajuci posunie za aktualny */
		}										
	}
printf ("Vymazalo sa %d zaznamov.\n",pom_pocet-*poc_zaznamov);
return p_prv;
}

void		hladat (int *poc_zaznamov,ZAZNAM *p_prv)	/* Funkcia na vyhladanie zaznamov z rovnakou alebo nizsou cenou ako bola zadana */
{
int hladana_cena,i,poc=0;
ZAZNAM *p_akt;

scanf (" %d",&hladana_cena);

p_akt=p_prv;
for (i=1;i<=*poc_zaznamov;i++)
	{	
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

ZAZNAM		*aktualizacia (int *poc_zaznamov,ZAZNAM *p_prv)	/* Funkcia na aktualizovanie zaznamu podla zadanej znacky a ceny */
{
int zadana_cena,i,poc_aktualizacii=0;
char zadana_znacka[51];
ZAZNAM *p_akt,*p_aktualizovany;

scanf ("\n");			/* Nacitanie a uprava znacky */
gets(zadana_znacka);
Uprava(zadana_znacka);

scanf(" %d",&zadana_cena);	/* nacitanie ceny */

p_akt=p_prv;
for (i=1;i<=*poc_zaznamov;i++)
{
	if ((!strcmp(zadana_znacka,(p_akt->znacka)))&&(zadana_cena==(p_akt->cena)))	/* Ak sa zhoduje znacka aj cena */
	{
		poc_aktualizacii++;
		if (poc_aktualizacii==1)	/* Ak sa zhoduje v jednom pripade tak nacitame aktualizovany zaznam */
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
		strcpy(p_akt->kategoria,p_aktualizovany->kategoria);	 /* V ostatnych pripadoch zhody uz nenacitavame ale len prepisujeme stary zaznam aktualizovanym */	
		strcpy(p_akt->znacka,p_aktualizovany->znacka);
		strcpy(p_akt->predajca,p_aktualizovany->predajca);
		p_akt->cena = p_aktualizovany->cena;
		p_akt->rok = p_aktualizovany->rok;
		strcpy(p_akt->stav,p_aktualizovany->stav);
	}
	p_akt=p_akt->dalsi;
}

printf ("\nAktualizovalo sa %d zaznamov.\n",poc_aktualizacii);
free(p_aktualizovany);	/* aktualizovany zaznam na konci funkcie uvolnime */
return p_prv;
}

int			konec (ZAZNAM *p_prv,int *poc_zaznamov)	/* Funkcia na ukoncenie programu */
{
ZAZNAM *p_akt,*p_uvolnit;

Uvolnit(p_prv,poc_zaznamov);	/* uvolnenie zoznamu a funkcia vrati '1' (cize program moze skoncit) */
return 1;
}


int			main ()
{
ZAZNAM *p_prv=NULL;
char pismeno;
int poc_zaznamov=0,zoznam=0,end=0;

do{
	scanf (" %c",&pismeno);	/* Nacitanie znaku pre volbu funkcie */
	switch (pismeno)
	{
	case 'n' :	p_prv=nacitaj(&poc_zaznamov,zoznam,p_prv) ;
				zoznam=1;		/* Ak sa zoznam == 1 tak existuje */
				break;

	case 'v' :  if (zoznam==1)		/* Pokial zoznam existuje prebehne funkcia */
					vypis (&poc_zaznamov,p_prv);						
				break;											
																
	case 'p' :	p_prv=pridat(&poc_zaznamov,p_prv);				
				zoznam=1;	/* Zoznam urcite existuje ak prebehla funkcia pridaj */								
				break;											
															
	case 'z' :	if (zoznam==1)	/* Pokial zoznam existuje prebehne funkcia */	
					p_prv=zmazat(&poc_zaznamov,p_prv);			
				break;											
																
	case 'h' :	if (zoznam==1)	/* Pokial zoznam existuje prebehne funkcia */	
					hladat(&poc_zaznamov,p_prv);
				break;
	
	case 'a' :	if (zoznam==1)	/* Pokial zoznam existuje prebehne funkcia */	 
					p_prv=aktualizacia(&poc_zaznamov,p_prv);
				break;
	
	case 'k' :	 if (zoznam==1)	/* Pokial zoznam existuje prebehne funkcia */
					{
					end=konec(p_prv,&poc_zaznamov); /* Do premennej end sa priradi '1' takze program skonci */
					break;
					}
				end=1; /* Ak zoznam neexistuje ale bolo zadanie 'k' tak program skonci */
				break;

	}
  }while (end!=1);
}