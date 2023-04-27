/*
| ProjektniZadatak_2023                 |
| Na projektu radio: Demir Halilbasic   |
| Student I godine                      |
| Smijer Informatika i racunarstvo      |
| Datum pocetka: 08.01.2023.            |
| Datum zavrsetka: 17.01.2023.          |
| IPI Akademija Tuzla                   |
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "struct.h"
#include "login.h"
#include "apanel.h"
#include "upanel.h"
#include "test.h"

int main()
{
    //test(); // AKTIVIRATI/DEAKTIVIRATI PO POTREBI ZA UPIS LOGINA ADMINA (U 'test.h' MODIFIKOVATI PODATKE)
    int login_check, clear_check=0;
    char repeat_check;
    login_check=login();
    if(login_check==2)
    {
        adminpanel();
    }
    else if(login_check==1)
    {
        userpanel();
    }
    do
    {
        if(clear_check==0)
        {
            system("cls");
            printf("\n\t** Da li zelite ponovo da se ulogujete na nalog? Y/N **\n\tOdabir: ");
        }
        scanf(" %c",&repeat_check);
        if((repeat_check=='Y')||(repeat_check=='y'))
        {
            clear_check=0;
            system("cls");
            login_check=login();
            if(login_check==2)
            {
                adminpanel();
            }
            else if(login_check==1)
            {
                userpanel();
            }
        }
        else if((repeat_check=='N')||(repeat_check=='n'))
        {
            printf("\n\t~~ Uspjesno ste se izlogovali iz systema ~~\n\t~~ Hvala na koristenju, pozdrav ~~\n");
        }
        else
        {
            printf("\n\tGRESKA: Pogresan unos! Koristite 'Y' ili 'N'\n\tOdabir: ");
            clear_check=1;
        }
    }
    while((repeat_check!='N')&&(repeat_check!='n'));
    return 0;
}
