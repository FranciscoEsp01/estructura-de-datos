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
/* cambio 1.3
Francisco Espinoza
    se elimina tribunal constitucional ya que no es parte de la problematica del trabajo
    se elimina Struct camaraDeOrigen ya que pasara a ser una funcion dependiente del tema del proyecto y pasara a ser struct congreso
    se agrega "Cargo" dentro del struct persona para diferenciar diputados y senadores
    se agrego funcion camaraRevisoria (POR REVISAR) la cual puede que no cumpla con lo propuesto o que funcione con fallas etc.
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
    struct persona *persona;
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

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Vaciar el buffer
    }
}

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



struct presidente *crearPresidente(struct persona *persona, int anioMandato, int voto) {
    struct presidente *nuevoPresidente;
    nuevoPresidente = (struct presidente *)malloc(sizeof(struct presidente));

    nuevoPresidente->persona = persona;
    nuevoPresidente->anioMandato = anioMandato;
    nuevoPresidente->voto = voto;

    return nuevoPresidente;
}

/* Función para crear un nodo de senador */
struct nodoSenador *crearNodoSenador(struct persona *senador) {
    struct nodoSenador *nuevoSenador;
    nuevoSenador = (struct nodoSenador *)malloc(sizeof(struct nodoSenador));

    nuevoSenador->headSenadores = senador;
    nuevoSenador->ant = nuevoSenador;
    nuevoSenador->sig = nuevoSenador;

    return nuevoSenador;
}

/* Función para agregar un senador */
struct nodoSenador *agregarSenador(struct nodoSenador *senadores, struct persona *senador) {
    struct nodoSenador *nuevoSenador = crearNodoSenador(senador);

    if (senadores == NULL) {
        senadores = nuevoSenador;
    } else {
        struct nodoSenador *rec = senadores;
        while (rec->sig != senadores) {
            rec = rec->sig;
        }
        rec->sig = nuevoSenador;
        nuevoSenador->ant = rec;
        nuevoSenador->sig = senadores;
        senadores->ant = nuevoSenador;
    }
    return senadores;
}

/* Función para mostrar senadores */
void mostrarSenadores(struct nodoSenador *senadores) {
    if (senadores == NULL) {
        printf("No hay senadores en la lista.\n");
        return;
    }

    struct nodoSenador *rec = senadores;
    do {
        printf("Nombre: %s\n", rec->headSenadores->nombre);
        printf("Edad: %d\n", rec->headSenadores->edad);
        printf("Especialidad: %s\n", rec->headSenadores->especialidad);
        printf("Voto: %d\n", rec->headSenadores->voto);
        printf("Cargo: %s\n", rec->headSenadores->cargo);
        rec = rec->sig;
    } while (rec != senadores);
}


void mostrarPresidente(struct presidente *presidente) {
    if (presidente == NULL) {
        printf("No hay un presidente registrado.\n");
        return;
    }

    printf("\n===== Datos del Presidente =====\n");
    printf("Nombre: %s\n", presidente->persona->nombre);
    printf("Edad: %d\n", presidente->persona->edad);
    printf("Especialidad: %s\n", presidente->persona->especialidad);
    printf("Año de Mandato: %d\n", presidente->anioMandato);
    printf("Voto: %d\n", presidente->voto);
    printf("================================\n");
}


void camaraDeOrigen(struct propuesta *propuesta, struct congreso *congreso) {
    // Verificar si el proyecto debe iniciar en la Cámara de Diputados o en el Senado
    if (strcmp(propuesta->tipo, "financiero") == 0 || strcmp(propuesta->tipo, "tributario") == 0) {
        printf("El proyecto de tipo %s debe ser discutido primero en la Cámara de Diputados.\n", propuesta->tipo);
        // Aquí se podría agregar la lógica para derivar a la comisión de diputados
        // Ejemplo: Enviar a comisión de Hacienda si es financiero
    } else {
        printf("El proyecto de tipo %s será discutido en el Senado.\n", propuesta->tipo);
        // Aquí se podría agregar la lógica para derivar a la comisión de senadores
    }

    // Una vez derivado a la cámara correspondiente, simular el debate
    printf("Debatiendo la idea de legislar...\n");
    printf("Votando en la Cámara de Origen...\n");

    // Simular votación de todos los miembros de la cámara de origen
    int votosAFavor = 0, votosEnContra = 0;

    // Lógica de votación
    if (strcmp(propuesta->tipo, "financiero") == 0 || strcmp(propuesta->tipo, "tributario") == 0) {
        struct nodoDiputado *rec = congreso->diputados;
        if (rec != NULL) {
            do {
                if (rec->headDiputados->voto == 1) {
                    votosAFavor++;
                } else {
                    votosEnContra++;
                }
                rec = rec->sig;
            } while (rec != congreso->diputados);
        }
    } else {
        struct nodoSenador *rec = congreso->senadores;
        if (rec != NULL) {
            do {
                if (rec->headSenadores->voto == 1) {
                    votosAFavor++;
                } else {
                    votosEnContra++;
                }
                rec = rec->sig;
            } while (rec != congreso->senadores);
        }
    }

    // Mostrar resultados de la votación
    printf("Resultados de la votación:\n");
    printf("Votos a favor: %d\n", votosAFavor);
    printf("Votos en contra: %d\n", votosEnContra);

    if (votosAFavor > votosEnContra) {
        printf("La idea de legislar ha sido aprobada. El proyecto avanza a la siguiente etapa.\n");
    } else {
        printf("La idea de legislar ha sido rechazada. El proyecto no avanza.\n");
    }
}
struct propuesta *crearPropuesta(struct persona *autor) {
    struct propuesta *nuevaPropuesta = (struct propuesta *)malloc(sizeof(struct propuesta));

    printf("Ingresa el ID de la propuesta: ");
    scanf("%d", &nuevaPropuesta->id);
    limpiarBuffer();

    char tipo[50];
    printf("Ingresa el tipo de propuesta (financiero, tributario, educacion, etc.): ");
    fgets(tipo, sizeof(tipo), stdin);
    tipo[strcspn(tipo, "\n")] = '\0'; // Eliminar el salto de línea
    nuevaPropuesta->tipo = (char *)malloc(strlen(tipo) + 1);
    strcpy(nuevaPropuesta->tipo, tipo);

    char tema[50];
    printf("Ingresa el tema de la propuesta (educacion, salud, etc.): ");
    fgets(tema, sizeof(tema), stdin);
    tema[strcspn(tema, "\n")] = '\0'; // Eliminar el salto de línea
    nuevaPropuesta->tema = (char *)malloc(strlen(tema) + 1);
    strcpy(nuevaPropuesta->tema, tema);

    nuevaPropuesta->personaAcargo = autor;

    printf("Propuesta creada exitosamente.\n");

    return nuevaPropuesta;
}

void mostrarPropuesta(struct propuesta *propuesta){
    if(propuesta == NULL){
        printf("No hay propuesta registrada.\n");
        return;
    }
    printf("\n===== Datos de la Propuesta =====\n");
    printf("ID de la propuesta: %d\n", propuesta->id);
    printf("Tipo: %s\n", propuesta->tipo);
    printf("Tema: %s\n", propuesta->tema);
    printf("Autor: %s\n", propuesta->personaAcargo->nombre);
    printf("=================================\n");

}

/* Función para manejar la Cámara Revisora */
void camaraRevisora(struct propuesta *propuesta, struct congreso *congreso) {
    printf("La propuesta ha llegado a la Cámara Revisora.\n");

    printf("Debatiendo en la Cámara Revisora...\n");

    int votosAFavor = 0, votosEnContra = 0;
    int modificacion = 0;  // Si la Cámara Revisora propone modificaciones

    // Lógica de votación en la Cámara Revisora
    if (strcmp(propuesta->tipo, "financiero") == 0 || strcmp(propuesta->tipo, "tributario") == 0) {
        struct nodoSenador *rec = congreso->senadores;
        if (rec != NULL) {
            do {
                if (rec->headSenadores->voto == 1) {
                    votosAFavor++;
                } else {
                    votosEnContra++;
                }
                rec = rec->sig;
            } while (rec != congreso->senadores);
        }
    } else {
        struct nodoDiputado *rec = congreso->diputados;
        if (rec != NULL) {
            do {
                if (rec->headDiputados->voto == 1) {
                    votosAFavor++;
                } else {
                    votosEnContra++;
                }
                rec = rec->sig;
            } while (rec != congreso->diputados);
        }
    }

    printf("Resultados de la votación en la Cámara Revisora:\n");
    printf("Votos a favor: %d\n", votosAFavor);
    printf("Votos en contra: %d\n", votosEnContra);

    // Simulación de resultado en la Cámara Revisora
    if (votosAFavor > votosEnContra) {
        printf("¿La Cámara Revisora propone modificaciones? (1 = Sí, 0 = No): ");
        scanf("%d", &modificacion);

        if (modificacion == 1) {
            printf("La Cámara Revisora ha propuesto modificaciones. El proyecto vuelve a la Cámara de Origen.\n");
        } else {
            printf("La Cámara Revisora ha aprobado el proyecto sin cambios. Se envía al Presidente para su promulgación.\n");
        }
    } else {
        printf("El proyecto ha sido rechazado en la Cámara Revisora. No se promulga.\n");
    }
}

void mostrarMenu() {
    printf("\n===== Menu =====\n");
    printf("1. Crear Persona\n");
    printf("2. Agregar Diputado\n");
    printf("3. Mostrar Diputados\n");
    printf("4. Agregar Presidente\n");
    printf("5. Mostrar Senadores\n");
    printf("6. Mostrar Presidente\n");
    printf("7. Crear Propuesta\n");
    printf("8. Mostrar Propuesta\n");
    printf("9. Iniciar Cámara de Origen\n");
    printf("10. Iniciar Cámara Revisora\n");
    printf("11. Salir\n");
    printf("================\n");
}


int main() {
    struct nodoDiputado *diputados = NULL;
    struct nodoSenador *senadores = NULL;
    struct presidente *presidente = NULL;
    struct propuesta *propuesta = NULL;
    struct persona *autor = NULL;  // Persona que será el autor de la propuesta
    struct congreso congreso = {senadores, diputados};

    int opcion;
    char rut[20], nombre[50], especialidad[50], cargo[20];
    int edad, voto, anioMandato;
    int salir = 0;

    do {
        mostrarMenu();
        printf("Elige una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        if (opcion == 1) {
            printf("Ingresa el RUT: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';

            printf("Ingresa el nombre: ");
            fgets(nombre, sizeof(nombre), stdin);
            nombre[strcspn(nombre, "\n")] = '\0';

            printf("Ingresa la edad: ");
            scanf("%d", &edad);
            limpiarBuffer();

            printf("Ingresa la especialidad: ");
            fgets(especialidad, sizeof(especialidad), stdin);
            especialidad[strcspn(especialidad, "\n")] = '\0';

            printf("Ingresa el cargo (Diputado/Senador): ");
            fgets(cargo, sizeof(cargo), stdin);
            cargo[strcspn(cargo, "\n")] = '\0';

            printf("Ingresa el voto (1=afirmativo, 0=negativo): ");
            scanf("%d", &voto);
            limpiarBuffer();

            autor = crearPersona(rut, nombre, edad, especialidad, voto, cargo);
            printf("Persona creada exitosamente.\n");
        } 
        else if (opcion == 7) {
            if (autor == NULL) {
                printf("Primero debes crear una persona que será el autor de la propuesta.\n");
            } else {
                propuesta = crearPropuesta(autor);
            }
        } 
        else if (opcion == 8) {
            mostrarPropuesta(propuesta);
        } 
        else if (opcion == 9) {
            if (propuesta == NULL) {
                printf("Primero debes crear una propuesta para iniciar la Cámara de Origen.\n");
            } else {
                camaraDeOrigen(propuesta, &congreso);
            }
        } 
        else if (opcion == 10) {
            if (propuesta == NULL) {
                printf("Primero debes crear una propuesta para iniciar la Cámara Revisora.\n");
            } else {
                camaraRevisora(propuesta, &congreso);
            }
        } 
        else if (opcion == 11) {
            printf("Saliendo del programa...\n");
            salir = 1;
        } 
        else {
            printf("Opción no válida. Por favor, intenta de nuevo.\n");
        }
    } while (!salir);

    return 0;
}
