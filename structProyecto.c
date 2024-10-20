#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXMINISTROSTRIBUNAL 10

/* cambios 1.1

    se agrego la funcion crearPersona para crear una persona con los datos necesarios
    se agrego la funcion crearNodoDiputado para crear un nodo de diputado con los datos necesarios
    se agrego la funcion agregarDiputado para agregar un diputado a la lista de diputados
    se agrego la funcion mostrarDiputados para mostrar los diputados de la lista de diputados

    mas tarde o mañana voy a hacer para los ciudadanos y senadores, ademas de la funcion de quitar
    
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
    struct persona *headDiputados;
    struct nodoDiputado *ant, *sig;
};

/*lista circular doble*/
struct nodoSenador{
    struct persona *headSenadores;
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

struct persona *crearPersona(char *rut, char *nombre, int edad, char *especialidad, int voto){

    struct persona *nuevaPersona;
    nuevaPersona = (struct persona *) malloc(sizeof(struct persona));

    nuevaPersona->rut = (char *) malloc(sizeof(char) * strlen(rut) + 1);
    strcpy(nuevaPersona->rut, rut);

    nuevaPersona->nombre = (char *) malloc(sizeof(char) * strlen(nombre) + 1);
    strcpy(nuevaPersona->nombre, nombre);

    nuevaPersona->edad = edad;

    nuevaPersona->especialidad = (char *) malloc(sizeof(char) * strlen(especialidad) + 1);
    strcpy(nuevaPersona->especialidad, especialidad);

    nuevaPersona->voto = voto;

    return nuevaPersona;
}

struct nodoDiputado *crearNodoDiputado(struct persona *diputado){
    struct nodoDiputado *nuevoDiputado;
    nuevoDiputado = (struct nodoDiputado *) malloc(sizeof(struct nodoDiputado));

    nuevoDiputado->headDiputados = diputado;
    nuevoDiputado->ant = nuevoDiputado;
    nuevoDiputado->sig = nuevoDiputado;

    return nuevoDiputado;
}

struct nodoDiputado *agregarDiputado (struct nodoDiputado *diputados, struct persona *diputado){
    struct nodoDiputado *nuevoDiputado;
    nuevoDiputado = crearNodoDiputado(diputado);
    nuevoDiputado->headDiputados = diputado;

    if(diputados == NULL){
        diputados = nuevoDiputado;
        nuevoDiputado->ant = nuevoDiputado;
        nuevoDiputado->sig = nuevoDiputado;
    } else {
        struct nodoDiputado *rec = diputados;
        while(rec->sig != diputados){
            rec = rec->sig;
        }
        rec->sig = nuevoDiputado;
        nuevoDiputado->ant = rec;
        nuevoDiputado->sig = diputados;
        diputados->ant = nuevoDiputado;
    }
    return diputados;
}

void mostrarDiputados(struct nodoDiputado *diputados){
    struct nodoDiputado *rec = diputados;
    do{
        printf("Nombre: %s\n", rec->headDiputados->nombre);
        printf("Edad: %d\n", rec->headDiputados->edad);
        printf("Especialidad: %s\n", rec->headDiputados->especialidad);
        printf("Voto: %d\n\n", rec->headDiputados->voto);
        rec = rec->sig;
    } while (rec != diputados);
}

int main () {
    struct ProcesoLegislativo *proceso;
    proceso = (struct ProcesoLegislativo *) malloc(sizeof(struct ProcesoLegislativo));
    
    proceso->presidente = NULL;
    proceso->congreso = NULL;
    proceso->propuesta = NULL;
    proceso->ciudadanos = NULL;
    proceso->tc = NULL;
    proceso->boletinEstado = NULL;


    /* datos de prueba */

    struct presidente presidente = {"Sebastian Pinera", 70, 2018, 1};
    proceso->presidente = &presidente;
    

    printf("Nombre presidente: %s\n", proceso->presidente->nombre);
    printf("Edad presidente: %d\n", proceso->presidente->edad);
    printf("Anio mandato presidente: %d\n\n", proceso->presidente->anioMandato);


    /* diputados de prueba, formato {rut, nombre, edad, especialidad, voto}, esto para agregar/quitarlos del proceso legislativo */

    struct persona *diputado1 = crearPersona("21777777-6", "Rodrigo Teniente", 30, "Educacion", 0);
    struct persona *diputado2 = crearPersona("15325949-K", "Juan Perez", 50, "Economia", 0);
    struct persona *diputado3 = crearPersona("93429349-6", "Jorge Fernandez", 37, "Trabajo", 0);
    struct persona *diputado4 = crearPersona("24055505-4", "Rene Puentes", 43, "Salud", 0);
    struct persona *diputado5 = crearPersona("21777777-7", "Jorge El Flaco Johnson", 21, "Educacion", 0);

    proceso->congreso = (struct congreso *) malloc(sizeof(struct congreso)); // inicializar congreso
    proceso->congreso->camaraDeOrigen = (struct camaraDeOrigen *) malloc(sizeof(struct camaraDeOrigen)); // inicializar camara de origen
    proceso->congreso->camaraDeOrigen->diputados = NULL; // inicializar lista de diputados

    proceso->congreso->camaraDeOrigen->diputados = agregarDiputado(proceso->congreso->camaraDeOrigen->diputados, diputado1);
    proceso->congreso->camaraDeOrigen->diputados = agregarDiputado(proceso->congreso->camaraDeOrigen->diputados, diputado4);
    proceso->congreso->camaraDeOrigen->diputados = agregarDiputado(proceso->congreso->camaraDeOrigen->diputados, diputado5);

    mostrarDiputados(proceso->congreso->camaraDeOrigen->diputados);

    return 0;
}
