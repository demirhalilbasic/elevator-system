#ifndef APANEL_H_INCLUDED
#define APANEL_H_INCLUDED

int kreiraj_nalog(void);
int kreiraj_nosilo(void);
int prikazi_nosila(void);
int prikazi_servis(void);
int prikazi_blokada(void);
void reset_koristenja(void);
void reset_blokada(void);
void pauza(int);

void adminpanel()
{
    int unos;
    do
    {
        printf("\n\t[ADMIN MENU] Odaberite zeljenu opciju:\n\t1. Kreiranje novog korisnika\n\t2. Kreiranje novog nosila\n\t3. Trenutni broj koristenih nosila\n\t4. Nosila spremna za servisiranje\n\t5. Blokirana nosila\n\t6. Exit\n\n\tOdabir: ");
        scanf("%d",&unos);
        switch(unos)
        {
            case 1:
                kreiraj_nalog();
                break;
            case 2:
                kreiraj_nosilo();
                break;
            case 3:
                prikazi_nosila();
                break;
            case 4:
                prikazi_servis();
                break;
            case 5:
                prikazi_blokada();
                break;
            case 6:
                printf("\n\t~~ Hvala na koristenju LIFT systema ~~\n");
                pauza(2);
                break;
            default:
                system("cls");
                printf("\n\tGRESKA: Odabrana opcija nepostojeca!\n");
                break;
        }
    }
    while(unos!=6);
}

int kreiraj_nalog()
{
    char email[30], pass[30];
    int status=0;
    FILE *file;
    logovanje=(struct pristup *)malloc(sizeof(struct pristup));
    if((file=fopen("admin.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (admin)!\n");
        exit(1);
    }
    printf("\n*** Zapoceli ste kreiranje novog korisnickog naloga! ***\nZa pocetak unesite zeljeni e-mail: ");
    scanf("%29s",email);
    if(strlen(email)>29)
    {
        system("cls");
        printf("\n\tGRESKA: Email korisnika je predug!\n");
        free(lift);
        fclose(file);
        return 0;
    }
    while(fread(logovanje,sizeof(struct pristup),1,file)==1)
    {
        if(strcmp(logovanje->email,email)==0)
        {
            system("cls");
            printf("\n\tGRESKA: Korisnik vec ima kreiran nalog!\n");
            free(logovanje);
            fclose(file);
            return 0;
        }
    }
    strcpy(logovanje->email,email);
    printf("Unesite zeljenu lozniku za korisnika: ");
    scanf("%29s",pass);
    if(strlen(pass)>29)
    {
        system("cls");
        printf("\n\tGRESKA: Lozinka korisnika je preduga!\n");
        free(lift);
        fclose(file);
        return 0;
    }
    strcpy(logovanje->pass,pass);
    printf("Unesite status za korisnika [0 - Obican korisnik, 1 - Admin]: ");
    scanf("%d",&status);
    if(status==1)
    {
        logovanje->admin=1;
    }
    else
    {
        logovanje->admin=0;
    }
    fwrite(logovanje,sizeof(struct pristup),1,file);
    system("cls");
    printf("\n\t*** Uspjesno ste kreirali novi korisnicki nalog! ***\n");
    free(logovanje);
    fclose(file);
    return 0;
}

int kreiraj_nosilo()
{
    char ime_nosila[20], upit;
    int broj_spratova, prije_servisa, prije_blokiranja, blokada;
    FILE *file;
    lift=(struct nosila *)malloc(sizeof(struct nosila));
    if((file=fopen("nosila.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (nosila)!\n");
        exit(1);
    }
    system("cls");
    printf("\n\tZapoceli ste kreiranje novog nosila!\n\tZa pocetak unesite zeljeni naziv nosila: ");
    scanf("%19s",ime_nosila);
    if(strlen(ime_nosila)>19)
    {
        system("cls");
        printf("\n\tGRESKA: Naziv nosila je predug!\n");
        free(lift);
        fclose(file);
        return 0;
    }
    while(fread(lift,sizeof(struct nosila),1,file)==1)
    {
        if(strcmp(lift->naziv_nosila,ime_nosila)==0)
        {
            system("cls");
            printf("\n\tGRESKA: Naziv nosila vec postoji!\n");
            free(lift);
            fclose(file);
            return 0;
        }
        /*/ ZA TESTIRANJE
        printf("\n1. Naziv nosila: %s\n",lift->naziv_nosila);
        printf("\n2. Broj spratova tog nosila: %d\n",lift->broj_spratova);
        printf("\n3. Broj koristenja: %d\n",lift->broj_koristenja);
        printf("\n4. Normalan rad nosila: %d\n",lift->normalan_rad);
        printf("\n5. Rad za zastavicom: %d\n",lift->sa_zastavicom);
        printf("\n6. Blokirano DA/NE: %d\n",lift->blokirano);
        /*/
    }
    //strcpy(lift->naziv_nosila,ime_nosila);
    printf("\tUnesite zeljeni broj spratova za koristenje nosila: ");
    scanf("%d", &broj_spratova);
    //lift->broj_spratova=broj_spratova;
    //lift->broj_koristenja=0;
    printf("\n\tUnesite broj koliko puta zelite da nosilo bude aktivirano,\n\tprije zastavice za servis: ");
    scanf("%d", &prije_servisa);
    //lift->normalan_rad=prije_servisa;
    printf("\n\tUnesite broj koliko puta se moze koristiti lift NAKON postavljene\n\tzastavice za servisiranje (prije finalne blokade): ");
    scanf("%d", &prije_blokiranja);
    //lift->sa_zastavicom=prije_blokiranja;
    //lift->blokirano=0;
    //////////
    printf("\n\tDa li zelite sacuvati nosilo u bazu sa sljedecim karakteristikama? Y/N\n\tNaziv nosila: %s\n\tBroj spratova: %d\n\tBroj koristenja nosila prije zastavice: %d\n\tBroj koristenja nosila sa zastavicom: %d\n\n\tOdabir: ",ime_nosila,broj_spratova,prije_servisa,prije_servisa+prije_blokiranja);
    do
    {
        scanf(" %c",&upit);
        if((upit=='Y')||(upit=='y'))
        {
            strcpy(lift->naziv_nosila,ime_nosila);
            lift->broj_spratova=broj_spratova;
            lift->broj_koristenja=0;
            lift->normalan_rad=prije_servisa;
            lift->sa_zastavicom=prije_blokiranja;
            lift->blokirano=0;
            fwrite(lift,sizeof(struct nosila),1,file);
        }
        else if((upit=='N')||(upit=='n'))
        {
            system("cls");
            free(lift);
            fclose(file);
            return 0;
        }
        //else if((upit!='Y')&&(upit!='y')&&(upit!='N')&&(upit!='n'))
        else
        {
            printf("\n\tGRESKA: Pogresan unos! Koristite 'Y' ili 'N'\n\tOdabir: ");
        }
    }
    while((upit!='Y')&&(upit!='y')&&(upit!='N')&&(upit!='n'));
    //////////
    system("cls");
    printf("\n\t*** Uspjesno ste kreirali novo nosilo! ***\n");
    free(lift);
    fclose(file);
    return 0;
}

int prikazi_nosila()
{
    int brojac=1;
    char unesi;
    FILE *file;
    lift=(struct nosila *)malloc(sizeof(struct nosila));
    if((file=fopen("nosila.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (nosila)!\n");
        exit(1);
    }
    printf("\n\tDa li zelite prikaz informacija o svim nosilima? Y/N\n\tOdabir: ");
    do
    {
        scanf(" %c",&unesi);
        if((unesi=='Y')||(unesi=='y'))
        {
            int nema_ispisa=0, do_servisa, do_blokade;
            while(fread(lift,sizeof(struct nosila),1,file)==1)
            {
                do_servisa=(lift->normalan_rad)-(lift->broj_koristenja);
                do_blokade=(lift->sa_zastavicom)+(lift->normalan_rad)-(lift->broj_koristenja);
                if(brojac==1)
                {
                    system("cls");
                    printf("\n\t~ Informacije o svim nosilima ~");
                }
                printf("\n\n\t * Nosilo broj %d",brojac);
                printf("\n\ta) Naziv nosila: %s",lift->naziv_nosila);
                printf("\n\tb) Ukupan broj koristenja: %d/%d",lift->broj_koristenja,lift->normalan_rad);
                if(do_servisa<=0)
                {
                    printf(" - Potreban servis!");
                }
                else
                {
                    printf(" - Nije potreban servis.");
                }
                printf("\n\tc) Rad za zastavicom za servis: %d/%d",lift->broj_koristenja,(lift->sa_zastavicom)+(lift->normalan_rad));
                if(do_blokade<=0)
                {
                    printf(" - Nosilo BLOKIRANO!");
                }
                else
                {
                    printf(" - Nosilo nije blokirano.");
                }
                nema_ispisa=1;
                brojac++;
            }
            if(nema_ispisa==0)
            {
                system("cls");
                printf("\n\t ** Nema unijetih vrijednosti u bazi nosila **\n");
            }
            else
            {
                printf("\n\n\t-------------------------------\n\t            ~ KRAJ ~\n\t-------------------------------\n");
            }
        }
        else if((unesi=='N')||(unesi=='n'))
        {
            int nema_ispisa=0, do_servisa, do_blokade, dostupna_provjera=1;
            char ime_nosila[20];
            while(fread(lift,sizeof(struct nosila),1,file)==1)
            {
                if(dostupna_provjera==1)
                {
                    printf("\n\t* Dostupna nosila: ");
                }
                else if(dostupna_provjera%5==0)
                {
                    printf("\n\t\t\t   ");
                }
                else
                {
                    printf(" | ");
                }
                printf("%s",(lift->naziv_nosila));
                dostupna_provjera++;
            }
            rewind(file);
            if(dostupna_provjera==1)
            {
                free(lift);
                fclose(file);
                system("cls");
                printf("\n\t ** Nema unijetih vrijednosti u bazi nosila **\n");
                return 0;
            }
            else
            {
                printf("\n");
            }
            printf("\n\tUnesite naziv zeljenog nosila za vise informacija: ");
            scanf("%19s",ime_nosila);
            while(fread(lift,sizeof(struct nosila),1,file)==1)
            {
                if(strcmp(lift->naziv_nosila,ime_nosila)==0)
                {
                    do_servisa=(lift->normalan_rad)-(lift->broj_koristenja);
                    do_blokade=(lift->sa_zastavicom)+(lift->normalan_rad)-(lift->broj_koristenja);
                    system("cls");
                    printf("\n\t~ Informacije o zeljenom nosilu ~");
                    printf("\n\n\t * Nosilo broj %d",brojac);
                    printf("\n\ta) Naziv nosila: %s",lift->naziv_nosila);
                    printf("\n\tb) Ukupan broj koristenja: %d/%d",lift->broj_koristenja,lift->normalan_rad);
                    if(do_servisa<=0)
                    {
                        printf(" - Potreban servis!");
                    }
                    else
                    {
                        printf(" - Nije potreban servis.");
                    }
                    printf("\n\tc) Rad za zastavicom za servis: %d/%d",lift->broj_koristenja,(lift->sa_zastavicom)+(lift->normalan_rad));
                    if(do_blokade<=0)
                    {
                        printf(" - Nosilo BLOKIRANO!");
                    }
                    else
                    {
                        printf(" - Nosilo nije blokirano.");
                    }
                    nema_ispisa=1;
                }
                brojac++;
            }
            if(nema_ispisa==0)
            {
                system("cls");
                printf("\n\t ** Nema rezultata u bazi nosila koje odgovara imenu '%s' **\n",ime_nosila);
            }
            else
            {
                printf("\n\n\t-------------------------------\n\t            ~ KRAJ ~\n\t-------------------------------\n");
            }
        }
        else
        {
            printf("\n\tGRESKA: Pogresan unos! Koristite 'Y' ili 'N'\n\tOdabir: ");
        }
    }
    while((unesi!='Y')&&(unesi!='y')&&(unesi!='N')&&(unesi!='n'));
    free(lift);
    fclose(file);
    return 0;
}

int prikazi_servis()
{
    int provjera=0, brojac=1, do_servisa;
    FILE *file;
    lift=(struct nosila *)malloc(sizeof(struct nosila));
    if((file=fopen("nosila.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (nosila)!\n");
        exit(1);
    }
    while(fread(lift,sizeof(struct nosila),1,file)==1)
    {
        do_servisa=(lift->normalan_rad)-(lift->broj_koristenja);
        if(do_servisa<=0)
        {
            int do_blokade;
            do_blokade=(lift->sa_zastavicom)+(lift->normalan_rad)-(lift->broj_koristenja);
            if(provjera==0)
            {
                system("cls");
                printf("\n\t~ Informacije o nosilima spremnim za servis ~");
            }
            printf("\n\n\t * Nosilo broj %d",brojac);
            printf("\n\ta) Naziv nosila: %s",lift->naziv_nosila);
            printf("\n\tb) Ukupan broj koristenja: %d/%d",lift->broj_koristenja,lift->normalan_rad);
            if(do_blokade==1)
            {
                printf("\n\t** Preostalo je jos %d koristenje nosila prije potpune blokade **",do_blokade);
            }
            else if(do_blokade>1)
            {
                printf("\n\t** Preostalo je jos %d koristenja nosila prije potpune blokade **",do_blokade);
            }
            else
            {
                printf("\n\t** Nazalost, ovo nosilo je blokirano **",do_blokade);
            }
            provjera=1;
        }
        brojac++;
    }
    if(provjera==0)
    {
        system("cls");
        printf("\n\t ** Sva nosila su funkcionalna, nije potreban servis **\n");
    }
    else
    {
        printf("\n\n\t-------------------------------\n\t            ~ KRAJ ~\n\t-------------------------------\n");
    }
    free(lift);
    fclose(file);
    if(provjera==1)
    {
        char unesi;
        printf("\n\tDa li zelite RESETOVATI sva nosila sa liste na 0 koristenja? Y/N\n\tOdabir: ");
        do
        {
            scanf(" %c",&unesi);
            if((unesi=='Y')||(unesi=='y'))
            {
                reset_koristenja();
            }
            else if((unesi=='N')||(unesi=='n'))
            {
                system("cls");
                return 0;
            }
            else
            {
                printf("\n\tGRESKA: Pogresan unos! Koristite 'Y' ili 'N'\n\tOdabir: ");
            }
        }
        while((unesi!='Y')&&(unesi!='y')&&(unesi!='N')&&(unesi!='n'));
    }
    return 0;
}

int prikazi_blokada()
{
    int provjera=0, brojac=1, do_blokade;
    FILE *file;
    lift=(struct nosila *)malloc(sizeof(struct nosila));
    if((file=fopen("nosila.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (nosila)!\n");
        exit(1);
    }
    while(fread(lift,sizeof(struct nosila),1,file)==1)
    {
        do_blokade=(lift->sa_zastavicom)+(lift->normalan_rad)-(lift->broj_koristenja);
        if(do_blokade<=0)
        {
            if(provjera==0)
            {
                system("cls");
                printf("\n\t~ Informacije o BLOKIRANIM nosilima ~");
            }
            printf("\n\n\t * Nosilo broj %d",brojac);
            printf("\n\ta) Naziv nosila: %s",lift->naziv_nosila);
            printf("\n\tb) Ukupno koristenje nosila (ukljucujuci i sa zastavicom za servis): %d/%d",lift->broj_koristenja,(lift->sa_zastavicom)+(lift->normalan_rad));
            printf("\n\t** Nosilo je od %d-og koristenja radilo sa zastavicom za servis, **\n\t** nakon cega je blokirano na finalnih %d koristenja **",lift->normalan_rad,lift->broj_koristenja);
            provjera=1;
        }
        brojac++;
    }
    if(provjera==0)
    {
        system("cls");
        printf("\n\t ** Trenutno nema BLOKIRANIH nosila **\n");
    }
    else
    {
        printf("\n\n\t-------------------------------\n\t            ~ KRAJ ~\n\t-------------------------------\n");
    }
    free(lift);
    fclose(file);
    if(provjera==1)
    {
        char unesi;
        printf("\n\tDa li zelite RESETOVATI sva blokirana nosila sa liste? Y/N\n\tOdabir: ");
        do
        {
            scanf(" %c",&unesi);
            if((unesi=='Y')||(unesi=='y'))
            {
                reset_blokada();
            }
            else if((unesi=='N')||(unesi=='n'))
            {
                system("cls");
                return 0;
            }
            else
            {
                printf("\n\tGRESKA: Pogresan unos! Koristite 'Y' ili 'N'\n\tOdabir: ");
            }
        }
        while((unesi!='Y')&&(unesi!='y')&&(unesi!='N')&&(unesi!='n'));
    }
    return 0;
}

void reset_koristenja()
{
    int brojac=0, i=0, do_servisa;
    FILE *file;
    lift=(struct nosila *)malloc(sizeof(struct nosila));
    if((file=fopen("nosila.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (nosila)!\n");
        exit(1);
    }
    while(fread(lift,sizeof(struct nosila),1,file)==1)
    {
        brojac++;
    }
    free(lift);
    fclose(file);
    /////////////
    struct nosila temp[brojac];
    FILE *drugi_file;
    lift=(struct nosila *)malloc(sizeof(struct nosila));
    if((drugi_file=fopen("nosila.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (nosila)!\n");
        exit(1);
    }
    while(fread(lift,sizeof(struct nosila),1,drugi_file)==1)
    {
        strcpy(temp[i].naziv_nosila,lift->naziv_nosila);
        temp[i].broj_spratova=lift->broj_spratova;
        temp[i].broj_koristenja=lift->broj_koristenja;
        temp[i].normalan_rad=lift->normalan_rad;
        temp[i].sa_zastavicom=lift->sa_zastavicom;
        temp[i].blokirano=lift->blokirano;
        i++;
    }
    free(lift);
    fclose(drugi_file);
    remove("nosila.dat");
    /////////////
    FILE *treci_file;
    lift=(struct nosila *)malloc(sizeof(struct nosila));
    if((treci_file=fopen("nosila.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (nosila)!\n");
        exit(1);
    }
    for(i=0; i<brojac; i++)
    {
        do_servisa=(temp[i].normalan_rad)-(temp[i].broj_koristenja);
        if(do_servisa<=0)
        {
            strcpy(lift->naziv_nosila,temp[i].naziv_nosila);
            lift->broj_spratova=temp[i].broj_spratova;
            lift->broj_koristenja=0;
            lift->normalan_rad=temp[i].normalan_rad;
            lift->sa_zastavicom=temp[i].sa_zastavicom;
            lift->blokirano=0;
            fwrite(lift,sizeof(struct nosila),1,treci_file);
        }
        else
        {
            strcpy(lift->naziv_nosila,temp[i].naziv_nosila);
            lift->broj_spratova=temp[i].broj_spratova;
            lift->broj_koristenja=temp[i].broj_koristenja;
            lift->normalan_rad=temp[i].normalan_rad;
            lift->sa_zastavicom=temp[i].sa_zastavicom;
            lift->blokirano=temp[i].blokirano;
            fwrite(lift,sizeof(struct nosila),1,treci_file);
        }
    }
    system("cls");
    printf("\n\t*** Sva nosila oznacena sa zastavicom za servis su RESETOVANA! ***\n");
    free(lift);
    fclose(treci_file);
}

void reset_blokada()
{
    int brojac=0, i=0, do_blokade;
    FILE *file;
    lift=(struct nosila *)malloc(sizeof(struct nosila));
    if((file=fopen("nosila.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (nosila)!\n");
        exit(1);
    }
    while(fread(lift,sizeof(struct nosila),1,file)==1)
    {
        brojac++;
    }
    free(lift);
    fclose(file);
    /////////////
    struct nosila temp[brojac];
    FILE *drugi_file;
    lift=(struct nosila *)malloc(sizeof(struct nosila));
    if((drugi_file=fopen("nosila.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (nosila)!\n");
        exit(1);
    }
    while(fread(lift,sizeof(struct nosila),1,drugi_file)==1)
    {
        strcpy(temp[i].naziv_nosila,lift->naziv_nosila);
        temp[i].broj_spratova=lift->broj_spratova;
        temp[i].broj_koristenja=lift->broj_koristenja;
        temp[i].normalan_rad=lift->normalan_rad;
        temp[i].sa_zastavicom=lift->sa_zastavicom;
        temp[i].blokirano=lift->blokirano;
        i++;
    }
    free(lift);
    fclose(drugi_file);
    remove("nosila.dat");
    /////////////
    FILE *treci_file;
    lift=(struct nosila *)malloc(sizeof(struct nosila));
    if((treci_file=fopen("nosila.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (nosila)!\n");
        exit(1);
    }
    for(i=0; i<brojac; i++)
    {
        do_blokade=(temp[i].sa_zastavicom)+(temp[i].normalan_rad)-(temp[i].broj_koristenja);
        if(do_blokade<=0)
        {
            strcpy(lift->naziv_nosila,temp[i].naziv_nosila);
            lift->broj_spratova=temp[i].broj_spratova;
            lift->broj_koristenja=temp[i].normalan_rad;
            lift->normalan_rad=temp[i].normalan_rad;
            lift->sa_zastavicom=temp[i].sa_zastavicom;
            lift->blokirano=0;
            fwrite(lift,sizeof(struct nosila),1,treci_file);
        }
        else
        {
            strcpy(lift->naziv_nosila,temp[i].naziv_nosila);
            lift->broj_spratova=temp[i].broj_spratova;
            lift->broj_koristenja=temp[i].broj_koristenja;
            lift->normalan_rad=temp[i].normalan_rad;
            lift->sa_zastavicom=temp[i].sa_zastavicom;
            lift->blokirano=temp[i].blokirano;
            fwrite(lift,sizeof(struct nosila),1,treci_file);
        }
    }
    system("cls");
    printf("\n\t*** Sva blokirana nosila su RESETOVANA! ***\n");
    free(lift);
    fclose(treci_file);
}

void pauza(int ms)
{
    int sec=ms*1000;
    clock_t pocetak=clock();
    while(clock()<pocetak+sec);
}

#endif // APANEL_H_INCLUDED
