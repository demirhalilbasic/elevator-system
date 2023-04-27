#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

void test()
{
    FILE *file;
    logovanje=(struct pristup *)malloc(sizeof(struct pristup));
    if((file=fopen("admin.dat","ab+"))==NULL)
    {
        printf("\nSYS GRESKA: Neuspjesan pristup bazi podataka (admin)!\n");
        exit(1);
    }
    strcpy(logovanje->email,"admin@example.com");
    strcpy(logovanje->pass,"admin");
    logovanje->admin=1;
    fwrite(logovanje,sizeof(struct pristup),1,file);
    free(logovanje);
    fclose(file);
}

#endif // TEST_H_INCLUDED
