#include <stdio.h>
#include <stdlib.h>
/* INCOMPLETO */

struct presidente{
    char *nombre;
    int edad;
    int anoMandato;
    int voto;
};

struct propuesta{
    int id;
    char *tipo;
    char *tema;
};

struct diputado{
    char *nombre;
    int edad;
    char *especialidad;
    int voto;
};
struct camaraDiputados{
    struct diputado *diputados[50];
};

struct congreso{
    struct camaraSenado *camaraSenadores;
    struct camaraDiputados *camaraDiputados;
};

/* INCOMPLETO */
