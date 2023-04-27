#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

int provjera_email(char*);
int provjera_duzina(char*, char*);

int login()
{
    int brojac=0;
    printf("\n\t------------------------------------------------------------------------\n\t|                    ~~ Dobrodosli u LIFT system ~~                    |\n\t| * Molimo Vas da unesete Vase podatke kako biste pristupili systemu * |\n\t------------------------------------------------------------------------\n\n\tEmail: ");
    do
    {
        int global_check=1, email_check=0, length_check=0;
        char email[31], pass[31];
        scanf("%30s",email);
        printf("\tLozinka: ");
        scanf("%30s",pass);
        length_check=provjera_duzina(email,pass);
        email_check=provjera_email(email);
        if(length_check!=1)
        {
            printf("\n\n\tGRESKA: Vas email ili sifra su predugi (do 30 karaktera)!");
            email_check=0;
        }
        if(email_check==1)
        {
            FILE *file;
            logovanje=(struct pristup *)malloc(sizeof(struct pristup));
            if((file=fopen("admin.dat","ab+"))==NULL)
            {
                printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (admin)!\n");
                exit(1);
            }
            while(fread(logovanje,sizeof(struct pristup),1,file)==1)
            {
                if(strcmp(logovanje->email,email)==0)
                {
                    if(strcmp(logovanje->pass,pass)==0)
                    {
                        if(logovanje->admin==1)
                        {
                            free(logovanje);
                            fclose(file);
                            system("cls");
                            printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t| Uspjesno ste se prijavili na Vas nalog! |\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t| Obavijest: Upravljate kao administrator |\n\t-------------------------------------------\n");
                            return 2;
                        }
                        else if(logovanje->admin==0)
                        {
                            free(logovanje);
                            fclose(file);
                            system("cls");
                            printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t| Uspjesno ste se prijavili na Vas nalog! |\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                            return 1;
                        }
                        else
                        {
                            global_check=1;
                        }
                    }
                    else
                    {
                        global_check=1;
                    }
                }
                else
                {
                    global_check=1;
                }
            }
            if(global_check==1)
            {
                printf("\n\tGRESKA: Email ili sifra nisu ispravni!");
                brojac++;
            }
            free(logovanje);
            fclose(file);
        }
        else
        {
            if(length_check==1)
            {
                printf("\n\tGRESKA: Neispravan unos email-a (Pravilan format: ime.prezime@primjer.com)!");
            }
            brojac++;
        }
        if(brojac>=3)
        {
            printf("\n\tFATAL GRESKA: Prekoracili ste limit od tri pokusaja, system je blokiran!\n");
            exit(0);
        }
        printf("\n\n\tMolimo Vas ponovo unesite Vase podatke za pristup systemu! (Pokusaj %d/3)\n\n\tEmail: ",brojac+1);
    }
    while(brojac<3);
}

int provjera_email(char *email)
{
    int i, duzina=strlen(email), prva_provjera=0, druga_provjera=0;
    for(i=0; i<duzina; i++)
    {
        if(email[i]=='@')
        {
            prva_provjera=1;
        }
        if(email[i]=='.')
        {
            druga_provjera=1;
        }
    }
    if((prva_provjera==0)||(druga_provjera==0))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int provjera_duzina(char *email, char *pass)
{
    int duzina_email, duzina_pass;
    duzina_email=strlen(email);
    duzina_pass=strlen(pass);
    if((duzina_email>29)||(duzina_pass>29))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

#endif // LOGIN_H_INCLUDED
