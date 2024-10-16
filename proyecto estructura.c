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
    struct diputado *diputados[155];
};

struct congreso{
    struct camaraSenado *camaraSenadores;
    struct camaraDiputados *camaraDiputados;
};
struct camarasenado{
    struct senador *senadores[50];
};

struct senador{
    char *nombre;
    char *rut;
    int edad;
    int voto;
};

/* nodoPropuestas ARBOL BINARIO DE BUSQUEDA*/
struct nodoPropuestas{
    struct propuesta *datos;
    struct nodoPropuestas *izq, *der;
}
/* INCOMPLETO */
