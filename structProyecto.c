#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* cambios 1.1

    se agrego la funcion crearPersona para crear una persona con los datos necesarios
    se agrego la funcion crearNodoDiputado para crear un nodo de diputado con los datos necesarios
    se agrego la funcion agregarDiputado para agregar un diputado a la lista de diputados
    se agrego la funcion mostrarDiputados para mostrar los diputados de la lista de diputados
    
    cambios 1.2: movi unas partes del codigo para que compilara en el turbo c

    mas tarde o mañana voy a hacer para los ciudadanos y senadores, ademas de la funcion de quitar
    
*/
/* cambio 1.2
    se elimina tribunal constitucional ya que no es parte de la problematica del trabajo
    se elimina Struct camaraDeOrigen ya que pasara a ser una funcion dependiente del tema del proyecto y pasara a ser struct congreso
    se agrega "Cargo" dentro del struct persona para diferenciar diputados y senadores
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
  char *cargo;
  char *especialidad;
  int voto;
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

struct persona *crearPersona(char *rut, char *nombre, int edad, char *especialidad, int voto, char*cargo){

    struct persona *nuevaPersona;
    nuevaPersona = (struct persona *) malloc(sizeof(struct persona));

    nuevaPersona->rut = (char *) malloc(sizeof(char) * strlen(rut) + 1);
    strcpy(nuevaPersona->rut, rut);

    nuevaPersona->nombre = (char *) malloc(sizeof(char) * strlen(nombre) + 1);
    strcpy(nuevaPersona->nombre, nombre);

    nuevaPersona->edad = edad;

    nuevaPersona->cargo =(char *) malloc(sizeof(char) * strlen(cargo) + 1);
    strcpy(nuevaPersona->cargo, cargo);

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
        printf("Voto: %d\n", rec->headDiputados->voto);
        printf("Cargo: %s\n", rec->headDiputados->cargo);
        rec = rec->sig;
    } while (rec != diputados);
}
// Definición de structs y funciones omitida para abreviar (ya la tienes en el código)

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Vaciar el buffer
    }
}

void mostrarMenu() {
    printf("\n===== Menu =====\n");
    printf("1. Crear Persona\n");
    printf("2. Agregar Diputado\n");
    printf("3. Mostrar Diputados\n");
    printf("4. Salir\n");
    printf("================\n");
}

int main() {
    struct nodoDiputado *diputados = NULL;
    int opcion;
    char rut[20], nombre[50], especialidad[50], cargo[20];
    int edad, voto;
    int salir = 0;  // Variable para controlar el ciclo del menú

    do {
        mostrarMenu();
        printf("Elige una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();  // Limpiar el buffer para evitar problemas con el salto de línea

        if (opcion == 1) {
            printf("Ingresa el RUT: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';  // Eliminar el salto de línea

            printf("Ingresa el nombre: ");
            fgets(nombre, sizeof(nombre), stdin);
            nombre[strcspn(nombre, "\n")] = '\0';  // Eliminar el salto de línea

            printf("Ingresa la edad: ");
            scanf("%d", &edad);
            limpiarBuffer();  // Limpiar el buffer para evitar problemas con el salto de línea

            printf("Ingresa la especialidad: ");
            fgets(especialidad, sizeof(especialidad), stdin);
            especialidad[strcspn(especialidad, "\n")] = '\0';  // Eliminar el salto de línea

            printf("Ingresa el cargo (Diputado/Senador): ");
            fgets(cargo, sizeof(cargo), stdin);
            cargo[strcspn(cargo, "\n")] = '\0';  // Eliminar el salto de línea

            printf("Ingresa el voto (1=afirmativo, 0=negativo): ");
            scanf("%d", &voto);
            limpiarBuffer();  // Limpiar el buffer para evitar problemas con el salto de línea

            struct persona *nuevaPersona = crearPersona(rut, nombre, edad, especialidad, voto, cargo);
            printf("Persona creada exitosamente.\n");
        } 
        else if (opcion == 2) {
            printf("Ingresa el RUT de la persona que deseas agregar como diputado: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';  // Eliminar el salto de línea

            // Aquí se debería verificar que la persona fue creada (implementación opcional)
            struct persona *diputado = crearPersona(rut, nombre, edad, especialidad, voto, cargo);
            diputados = agregarDiputado(diputados, diputado);
            printf("Diputado agregado exitosamente.\n");
        } 
        else if (opcion == 3) {
            if (diputados == NULL) {
                printf("No hay diputados en la lista.\n");
            } else {
                mostrarDiputados(diputados);
            }
        } 
        else if (opcion == 4) {
            printf("Saliendo del programa...\n");
            salir = 1;  // Se marca la salida del ciclo
        } 
        else {
            printf("Opción no válida. Por favor, intenta de nuevo.\n");
        }
    } while (!salir);  // El ciclo se repite hasta que salir sea 1

    return 0;
}
