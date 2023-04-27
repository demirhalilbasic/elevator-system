#ifndef UPANEL_H_INCLUDED
#define UPANEL_H_INCLUDED

int aktivacija_lift(void);
int koristenje_lift(int*);
void upis_koristenja(int*);

char naziv_za_nosilo[20];
int blokirano;

void userpanel()
{
    int unos, aktivirao=0, koristio;
    char unos_ponovo;
    do
    {
        printf("\n\t[Korisnicki MENU] Odaberite zeljenu opciju:\n\t1. Aktivacija nosila ili lifta\n\t2. Pozivanje i koristenje nosila (lifta)\n\t3. Exit\n\n\tOdabir: ");
        scanf("%d",&unos);
        /*/
        ZABRANITI INPUT KARAKTERA - SVE OSIM DECIMALNIH BROJEVA
        /*/
        switch(unos)
        {
            case 1:
                if(aktivirao==0)
                {
                    aktivirao=aktivacija_lift();
                }
                else
                {
                    printf("\n\tNAPOMENA: Vec ste aktivirali Vase nosilo!\n");
                    printf("\n\tDa li zelite aktivirati NOVO nosilo za Vas nalog? Y/N\n\tOdabir: ");
                    do
                    {
                        scanf(" %c",&unos_ponovo);
                        if((unos_ponovo=='Y')||(unos_ponovo=='y'))
                        {
                            aktivirao=aktivacija_lift();
                        }
                        else if((unos_ponovo=='N')||(unos_ponovo=='n'))
                        {
                            system("cls");
                        }
                        //while((unesi!='Y')&&(unesi!='y')&&(unesi!='N')&&(unesi!='n'));
                        //else if((unos_ponovo!='N')&&(unos_ponovo!='n'))
                        else if((unos_ponovo!='Y')&&(unos_ponovo!='y')&&(unos_ponovo!='N')&&(unos_ponovo!='n'))
                        {
                            printf("\n\tGRESKA: Pogresan unos! Koristite 'Y' ili 'N'\n\tOdabir: ");
                        }
                    }
                    while((unos_ponovo!='Y')&&(unos_ponovo!='y')&&(unos_ponovo!='N')&&(unos_ponovo!='n'));
                }
                break;
            case 2:
                if(aktivirao!=0)
                {
                    koristio=koristenje_lift(&aktivirao);
                    upis_koristenja(&koristio);
                    system("cls");
                    printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t| Hvala Vam na koristenju usluga nosila! |\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                }
                else
                {
                    system("cls");
                    printf("\n\tGRESKA: Niste aktivirali Vase nosilo!\n");
                }
                break;
            case 3:
                printf("\n\t~~ Hvala na koristenju LIFT systema ~~\n");
                pauza(2);
                break;
            default:
                system("cls");
                printf("\n\tGRESKA: Odabrana opcija nepostojeca!\n");
                break;
        }
    }
    while(unos!=3);
}

int aktivacija_lift()
{
    int provjera=0, brojac=1, dostupna_provjera=1;
    //char ime_nosila[20];
    FILE *file;
    lift=(struct nosila *)malloc(sizeof(struct nosila));
    if((file=fopen("nosila.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (nosila)!\n");
        exit(1);
    }
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
    printf("\n\n\t| Dobrodosli u proces aktivacije Vaseg nosila!\n\t| Molimo unesite naziv zeljenog nosila za aktivaciju: ");
    scanf("%19s",naziv_za_nosilo);
    while(fread(lift,sizeof(struct nosila),1,file)==1)
    {
        if(strcmp(lift->naziv_nosila,naziv_za_nosilo)==0)
        {
            system("cls");
            printf("\a\n\t*** Cestitamo! ***\n\tUspjesno ste aktivirali Vase nosilo '%s' pod brojem %d.\n\tSada mozete koristiti Vase nosilo (lift) -> koristite opciju '2' u korisnickom meniju.\n",lift->naziv_nosila,brojac);
            provjera=brojac;
        }
        brojac++;
    }
    free(lift);
    fclose(file);
    if(provjera==0)
    {
        system("cls");
        printf("\n\t ** Zao nam je, nismo uspjeli pronaci Vase nosilo pod nazivom '%s' **\n\tObratite paznju da li ste pravilno unijeli naziv nosila, te pokusajte ponovo.\n",naziv_za_nosilo);
        return 0;
    }
    else
    {
        return provjera;
    }
}

int koristenje_lift(int *rb)
{
    //int brojac=1;
    int broj_koristenja;
    blokirano=0;
    FILE *file;
    lift=(struct nosila *)malloc(sizeof(struct nosila));
    if((file=fopen("nosila.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (nosila)!\n");
        exit(1);
    }
    while(fread(lift,sizeof(struct nosila),1,file)==1)
    {
        //if(brojac==(*rb))
        if(strcmp(lift->naziv_nosila,naziv_za_nosilo)==0)
        {
            int posljednji=(lift->broj_spratova)-1;
            int trenutni=(lift->broj_spratova)-1;
            int do_servisa=(lift->normalan_rad)-(lift->broj_koristenja);
            int do_blokade=(lift->sa_zastavicom)+(lift->normalan_rad)-(lift->broj_koristenja);
            int i, j, k, l, unos;
            broj_koristenja=lift->broj_koristenja;
            system("cls");
            //printf("\t** ZGRADA broj: %d | Naziv nosila: %s **\n\n",(*rb),lift->naziv_nosila);
            //printf("  ** ZGRADA broj: %d | Naziv nosila: %s | Broj koristenja: %d/%d **\n  ** Prizemlje: 0   | Broj posljednjeg sprata: %d **\n\n",(*rb),lift->naziv_nosila,lift->broj_koristenja,lift->normalan_rad,posljednji);
            printf("  ** Naziv nosila: %s | Broj koristenja: %d/%d | Broj prizemlja: 0 | Broj posljednjeg sprata: %d **\n\n",lift->naziv_nosila,broj_koristenja,lift->normalan_rad,posljednji);
            printf("\t_________________________\n\t|-----------------------|\n\t|    ZGRADA broj %3d    |\n\t|-----------------------|\n",(*rb));
            for(i=posljednji; i>=0; i--)
            {
                if(i==trenutni)
                {
                    printf("\t| Sprat: %d\t|||     |\n",i);
                }
                else
                {
                    printf("\t| Sprat: %d\t|\t|\n",i);
                }
            }
            printf("\t|-----------------------|\n");

            // POZIVANJE NA PRIZEMLJE
            int brojac_lift=0;
            printf("\n\nPritisnite '0' kako biste pozvali lift u prizemlje!\nOdabir: ");
            do
            {
                scanf("%d",&unos);
                switch(unos)
                {
                    case 0:
                        if(do_blokade<=0)
                        {
                            system("cls");
                            printf("\n\tGRESKA: Zao nam je, Vase nosilo je doseglo maksimum od %d koristenja te je BLOKIRANO!\n",broj_koristenja);
                            pauza(3);
                            blokirano=1;
                            free(lift);
                            fclose(file);
                            return broj_koristenja;
                        }
                        broj_koristenja++;
                        for(i=trenutni; i>=0; i--)
                        {
                            l=trenutni;
                            system("cls");
                            if(broj_koristenja>=(lift->normalan_rad))
                            {
                                printf("  ** Naziv nosila: %s | Broj koristenja: %d/%d | Broj prizemlja: 0 | Broj posljednjeg sprata: %d **\n  ** Upozorenje [ZASTAVICA ZA SERVIS]: Preostalo Vam je jos %d koristenja prije potpune blokade **\n\n",lift->naziv_nosila,broj_koristenja,lift->normalan_rad,posljednji,do_blokade);
                            }
                            else
                            {
                                printf("  ** Naziv nosila: %s | Broj koristenja: %d/%d | Broj prizemlja: 0 | Broj posljednjeg sprata: %d **\n\n",lift->naziv_nosila,broj_koristenja,lift->normalan_rad,posljednji);
                            }
                            printf("\t_________________________\n\t|-----------------------|\n\t|    ZGRADA broj %3d    |\n\t|-----------------------|\n",(*rb));
                            do_servisa=(lift->normalan_rad)-broj_koristenja;
                            do_blokade=(lift->sa_zastavicom)+(lift->normalan_rad)-broj_koristenja;
                            //printf("  ** ZGRADA broj: %d | Naziv nosila: %s | Broj koristenja: %d/%d **\n  ** Prizemlje: 0   | Broj posljednjeg sprata: %d **\n\n",(*rb),lift->naziv_nosila,broj_koristenja,lift->normalan_rad,posljednji);
                            if(brojac_lift!=0)
                            {
                                for(j=0; j<brojac_lift; j++)
                                {
                                    //printf("\t|\n");
                                    printf("\t| Sprat: %d\t|\t|\n",l);
                                    l--;
                                }
                            }
                            if(i+brojac_lift==trenutni)
                            {
                                //printf("\t|||\n");
                                printf("\t| Sprat: %d\t|||     |\n",l);
                                l--;
                            }
                            if(brojac_lift!=trenutni)
                            {
                                for(k=0; k<trenutni-brojac_lift; k++)
                                {
                                    //printf("\t|\n");
                                    printf("\t| Sprat: %d\t|\t|\n",l);
                                    l--;
                                }
                            }
                            printf("\t|-----------------------|\n");
                            brojac_lift++;
                            if(i==trenutni)
                            {
                                printf("\n\n\tLift zaprima naredbu...\n");
                            }
                            if(i!=0)
                            {
                                if(i!=trenutni)
                                {
                                    printf("\n\n\tStrpljivo... Lift u pokretu...\n");
                                }
                            }
                            else
                            {
                                printf("\n\n\tTrenutak... Lift se zaustavlja...");
                            }
                            pauza(2);
                            if(i==0)
                            {
                                printf("\a\n\tLift je pristigao.");
                            }
                        }
                        trenutni=0;
                        break;
                    default:
                        printf("\nGRESKA: Prvo morate pozvati lift do sebe (prizemlje)!\nOdabir: ");
                        break;
                }
            }
            while(unos!=0);

            // POZIVANJE NA GORE
            int provjera;
            printf("\n\nNapisite zeljeni broj sprata [0 - prizemlje, 1 - 1.sprat, itd.]!\n** Za izlaz koristite naredbu '99' **\nOdabir: ");
            do
            {
                provjera=1;
                scanf("%d",&unos);
                if(unos==0)
                {
                    printf("\nGRESKA: Trenutno se nalazite na prizemlju!\nOdabir: ");
                    provjera=0;
                }
                else if(unos<0)
                {
                    printf("\nGRESKA: Unijeli ste nepostojeci sprat!\nOdabir: ");
                    provjera=0;
                }
                else if(unos>posljednji)
                {
                    provjera=0;
                    if(unos!=99)
                    {
                        printf("\nGRESKA: Unijeli ste nepostojeci sprat!\nOdabir: ");
                    }
                    else if(unos==99)
                    {
                        provjera=5;
                    }
                }
                if(provjera==1)
                {
                    if(do_blokade<=0)
                    {
                        system("cls");
                        printf("\n\tGRESKA: Zao nam je, Vase nosilo je doseglo maksimum od %d koristenja te je BLOKIRANO!\n",broj_koristenja);
                        pauza(3);
                        blokirano=1;
                        free(lift);
                        fclose(file);
                        return broj_koristenja;
                    }
                    broj_koristenja++;
                    brojac_lift=posljednji;
                    for(i=0; i<=unos; i++)
                    {
                        l=posljednji;
                        system("cls");
                        if(broj_koristenja>=(lift->normalan_rad))
                        {
                            printf("  ** Naziv nosila: %s | Broj koristenja: %d/%d | Broj prizemlja: 0 | Broj posljednjeg sprata: %d **\n  ** Upozorenje [ZASTAVICA ZA SERVIS]: Preostalo Vam je jos %d koristenja prije potpune blokade **\n\n",lift->naziv_nosila,broj_koristenja,lift->normalan_rad,posljednji,do_blokade);
                        }
                        else
                        {
                            printf("  ** Naziv nosila: %s | Broj koristenja: %d/%d | Broj prizemlja: 0 | Broj posljednjeg sprata: %d **\n\n",lift->naziv_nosila,broj_koristenja,lift->normalan_rad,posljednji);
                        }
                        printf("\t_________________________\n\t|-----------------------|\n\t|    ZGRADA broj %3d    |\n\t|-----------------------|\n",(*rb));
                        do_servisa=(lift->normalan_rad)-broj_koristenja;
                        do_blokade=(lift->sa_zastavicom)+(lift->normalan_rad)-broj_koristenja;
                        //printf("  ** ZGRADA broj: %d | Naziv nosila: %s | Broj koristenja: %d/%d **\n  ** Prizemlje: 0   | Broj posljednjeg sprata: %d **\n\n",(*rb),lift->naziv_nosila,lift->broj_koristenja,lift->normalan_rad,posljednji);
                        if(brojac_lift!=0)
                        {
                            for(j=0; j<brojac_lift; j++)
                            {
                                //printf("\t|\n");
                                printf("\t| Sprat: %d\t|\t|\n",l);
                                l--;
                            }
                        }
                        if((i+brojac_lift)==(i+1)+(brojac_lift-1))
                        {
                            //printf("\t|||\n");
                            printf("\t| Sprat: %d\t|||     |\n",l);
                            l--;
                        }
                        if(i!=0)
                        {
                            for(k=0; k<i; k++)
                            {
                                //printf("\t|\n");
                                printf("\t| Sprat: %d\t|\t|\n",l);
                                l--;
                            }
                        }
                        printf("\t|-----------------------|\n");
                        brojac_lift--;
                        if(i==0)
                        {
                            printf("\n\n\tPokretanje lifta u toku...\n");
                        }
                        if(i!=unos)
                        {
                            if(i!=0)
                            {
                                printf("\n\n\tStrpljivo... Lift u pokretu...\n");
                            }
                        }
                        else
                        {
                            printf("\n\n\tTrenutak... Lift se zaustavlja...");
                        }
                        pauza(2);
                        if(i==unos)
                        {
                            printf("\a\n\tStigli ste na odrediste.");
                        }
                    }
                    trenutni=unos;
                    unos=99;
                }
            }
            while(unos!=99);

            if(provjera!=5)
            {
                // PONOVO NA PRIZEMLJE
                brojac_lift=0;
                printf("\n\nPritisnite '0' kako biste vratili lift u prizemlje!\nOdabir: ");
                do
                {
                    scanf("%d",&unos);
                    switch(unos)
                    {
                        case 0:
                            if(do_blokade<=0)
                            {
                                system("cls");
                                printf("\n\tGRESKA: Zao nam je, Vase nosilo je doseglo maksimum od %d koristenja te je BLOKIRANO!\n",broj_koristenja);
                                pauza(3);
                                blokirano=1;
                                free(lift);
                                fclose(file);
                                return broj_koristenja;
                            }
                            broj_koristenja++;
                            for(i=trenutni; i>=0; i--)
                            {
                                l=posljednji;
                                system("cls");
                                if(broj_koristenja>=(lift->normalan_rad))
                                {
                                    printf("  ** Naziv nosila: %s | Broj koristenja: %d/%d | Broj prizemlja: 0 | Broj posljednjeg sprata: %d **\n  ** Upozorenje [ZASTAVICA ZA SERVIS]: Preostalo Vam je jos %d koristenja prije potpune blokade **\n\n",lift->naziv_nosila,broj_koristenja,lift->normalan_rad,posljednji,do_blokade);
                                }
                                else
                                {
                                    printf("  ** Naziv nosila: %s | Broj koristenja: %d/%d | Broj prizemlja: 0 | Broj posljednjeg sprata: %d **\n\n",lift->naziv_nosila,broj_koristenja,lift->normalan_rad,posljednji);
                                }
                                printf("\t_________________________\n\t|-----------------------|\n\t|    ZGRADA broj %3d    |\n\t|-----------------------|\n",(*rb));
                                do_servisa=(lift->normalan_rad)-broj_koristenja;
                                do_blokade=(lift->sa_zastavicom)+(lift->normalan_rad)-broj_koristenja;
                                //printf("  ** ZGRADA broj: %d | Naziv nosila: %s | Broj koristenja: %d/%d **\n  ** Prizemlje: 0   | Broj posljednjeg sprata: %d **\n\n",(*rb),lift->naziv_nosila,lift->broj_koristenja,lift->normalan_rad,posljednji);
                                if(i!=posljednji)
                                {
                                    for(j=0; j<posljednji-i; j++)
                                    {
                                        //printf("\t|\n");
                                        printf("\t| Sprat: %d\t|\t|\n",l);
                                        l--;
                                    }
                                }
                                if(i+brojac_lift==trenutni)
                                {
                                    //printf("\t|||\n");
                                    printf("\t| Sprat: %d\t|||     |\n",l);
                                    l--;
                                }
                                if(brojac_lift!=trenutni)
                                {
                                    for(k=0; k<trenutni-brojac_lift; k++)
                                    {
                                        //printf("\t|\n");
                                        printf("\t| Sprat: %d\t|\t|\n",l);
                                        l--;
                                    }
                                }
                                printf("\t|-----------------------|\n");
                                brojac_lift++;
                                if(i==trenutni)
                                {
                                    printf("\n\n\tPokretanje lifta u toku...\n");
                                }
                                if(i!=0)
                                {
                                    if(i!=trenutni)
                                    {
                                        printf("\n\n\tStrpljivo... Lift u pokretu...\n");
                                    }
                                }
                                else
                                {
                                    printf("\n\n\tTrenutak... Lift se zaustavlja...");
                                }
                                pauza(2);
                                if(i==0)
                                {
                                    printf("\a\n\tStigli ste na odrediste.");
                                    pauza(2);
                                }
                            }
                            trenutni=0;
                            break;
                        default:
                            printf("\nGRESKA: Koristite '0' kako biste vratili lift u prizemlje!\nOdabir: ");
                            break;
                    }
                }
                while(unos!=0);
            }
            else
            {
                free(lift);
                fclose(file);
                //rewind(file);
                //upisi_koristenja(&broj_koristenja, rb);
                return broj_koristenja;
            }
        }
        //brojac++;
    }
    free(lift);
    fclose(file);
    //rewind(file);
    //upisi_koristenja(&broj_koristenja, rb);
    return broj_koristenja;
}

void upis_koristenja(int *broj_koristenja)
{
    int brojac=0, i=0;
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
        //temp[i].naziv_nosila=lift->naziv_nosila;
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
    //i=0;
    FILE *treci_file;
    lift=(struct nosila *)malloc(sizeof(struct nosila));
    if((treci_file=fopen("nosila.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (nosila)!\n");
        exit(1);
    }
    //while(fread(lift,sizeof(struct nosila),1,treci_file)==1)
    for(i=0; i<brojac; i++)
    {
        if(strcmp(temp[i].naziv_nosila,naziv_za_nosilo)==0)
        {
            strcpy(lift->naziv_nosila,temp[i].naziv_nosila);
            lift->broj_spratova=temp[i].broj_spratova;
            lift->broj_koristenja=(*broj_koristenja);
            lift->normalan_rad=temp[i].normalan_rad;
            lift->sa_zastavicom=temp[i].sa_zastavicom;
            lift->blokirano=blokirano;
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
        //i++;
    }
    free(lift);
    fclose(treci_file);
}

#endif // UPANEL_H_INCLUDED
