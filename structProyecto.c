#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* cambios

- ahora todos los participantes del proceso a excepcion del presidente se manejan mediante el struct persona
esto para evitar la redundancia de datos y facilitar la implementacion de las distintas listas en el proceso

- se agrego la estructura boletinEstado para manejar los proyectos de ley que se encuentran aprobados

- el congreso ahora se compone de una camara de origen que a su vez se compone de una camara de senadores y diputados
cada camara de senadores y diputados se maneja mediante una lista circular doble y es para facilitar el manejo de estos para
armar las distintas listas de votacion y de discusion (camara mixta, comisiones, etc)

- se agrego la estructura tribunalConstitucional para manejar los votos de los ministros del tribunal constitucional y asi 
poder validar la constitucionalidad de las propuesta, y esta se maneja mediante un arreglo estatico de 10 ministros

- en la estructura ProcesoLegislativo se agrego el puntero a la lista de ciudadanos para poder manejar a la ciudadania y agregar 
o quitar a distintos miembros de esta dependiendo de la necesidad del proyecto (por ejemplo para la discusion de una propuesta, 
consulta ciudadana, etc)

*/

struct ProcesoLegislativo{
  struct presidente *presidente;
  struct congreso *congreso;
  struct nodoPropuestas *propuesta;
  struct nodoCiudadano *ciudadanos;
  struct tribunalConstitucional *tc;
  struct nodoBoletin *boletinEstado;
};

struct presidente{
    char *nombre;
    int edad;
    int anioMandato;
    int voto;
};

/* nodoPropuestas ARBOL BINARIO DE BUSQUEDA*/
struct nodoPropuestas {
    struct propuesta *datos;
    struct nodoPropuestas *izq, *der;
};

struct propuesta{
    int id;
    char *tipo;
    char *tema;
    struct persona *personaAcargo;
};

struct congreso{
    struct camaraDeOrigen *camaraDeOrigen;
};

struct camaraDeOrigen{
    struct nodoSenador *senadores;
    struct nodoDiputado *diputados;
};

/*lista circular doble*/
struct nodoDiputado{
    struct persona *head;
    struct nodoDiputado *ant, *sig;
};

/*lista circular doble*/
struct nodoSenador{
    struct persona *head;
    struct nodoSenador *ant, *sig;
};

/*lista doble*/
struct nodoCiudadano{
  struct persona *datos;
  struct nodoCiudadano *ant, *sig;
};

struct persona{
  char *rut;
  char *nombre;
  int edad;
  char *especialidad;
  int voto;
};

struct tribunalConstitucional {
    struct persona *ministro[10];
    int cantidadVotos;
};

/* nodoBoletin LISTA SIMPLE */
struct nodoBoletin { 
    struct boletin *head;
    struct nodoBoletin *sig;
};

struct boletin {
    struct propuesta *propuesta;
    int numeroBoletin;
    char *fechaVigencia;
};
