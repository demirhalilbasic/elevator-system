#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

struct pristup
{
    char email[30];
    char pass[30];
    int admin;
}*logovanje;

struct nosila
{
    char naziv_nosila[20];
    int broj_spratova;
    int broj_koristenja;
    int normalan_rad;
    int sa_zastavicom;
    int blokirano;
}*lift;

#endif // STRUCT_H_INCLUDED
