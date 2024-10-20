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
/* cambio 1.4
Francisco Espinoza
    se agrego el eliminar diputado
    se agrego el eliminar senador
    se agrego el agregar senador
    se amplio el menu a 14 funciones
    se actualizo el main
    ### SE DEBE CAMBIAR EL AGREGAR _____ YA QUE TOMA LA ULTIMA PERSONA REGISTRADA ###
*/

/* cambio 1.5
Joaquin Muñoz
    se agrego la funcion promulgacion o veto presidencial
    se agregó la funcion al menú
*/
/* cambio 1.6
Rigoberto Canales
    se agrega la funcion comision mixta
    se agrega la funcion a menu
    se hacen cambios en main para el uso de comision mixta
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
struct nodoCiudadano *crearNodoCiudadano(struct persona *ciudadano) {
    struct nodoCiudadano *nuevoCiudadano;
    nuevoCiudadano = (struct nodoCiudadano *) malloc(sizeof(struct nodoCiudadano));
    nuevoCiudadano->datos = ciudadano;
    nuevoCiudadano->ant = nuevoCiudadano->sig = NULL;
    return nuevoCiudadano;
}

struct nodoCiudadano *agregarCiudadano(struct nodoCiudadano *ciudadanos, struct persona *ciudadano) {
    struct nodoCiudadano *nuevoCiudadano = crearNodoCiudadano(ciudadano);

    if (ciudadanos == NULL) {
        ciudadanos = nuevoCiudadano;
    } else {
        struct nodoCiudadano *rec = ciudadanos;
        while (rec->sig != NULL) {
            rec = rec->sig;
        }
        rec->sig = nuevoCiudadano;
        nuevoCiudadano->ant = rec;
    }

    return ciudadanos;
}

void mostrarCiudadanos(struct nodoCiudadano *ciudadanos) {
    if (ciudadanos == NULL) {
        printf("No hay ciudadanos en la lista.\n");
        return;
    }

    struct nodoCiudadano *rec = ciudadanos;
    while (rec != NULL) {
        printf("Nombre: %s\n", rec->datos->nombre);
        printf("RUT: %s\n", rec->datos->rut);
        printf("Edad: %d\n", rec->datos->edad);
        printf("Especialidad: %s\n", rec->datos->especialidad);
        printf("Voto: %d\n", rec->datos->voto);
        printf("Cargo: %s\n\n", rec->datos->cargo);
        rec = rec->sig;
    }
}

struct persona *buscarCiudadanoPorRUT(struct nodoCiudadano *ciudadanos, char *rut) {
    struct nodoCiudadano *rec = ciudadanos;
    while (rec != NULL) {
        if (strcmp(rec->datos->rut, rut) == 0) {
            return rec->datos;
        }
        rec = rec->sig;
    }
    return NULL;
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

struct nodoDiputado *agregarDiputado(struct nodoDiputado *diputados, struct nodoCiudadano *ciudadanos, char *rut) {
    struct persona *ciudadano = buscarCiudadanoPorRUT(ciudadanos, rut);
    
    if (ciudadano == NULL) {
        printf("Ciudadano con RUT %s no encontrado.\n", rut);
        return diputados;
    }

    struct nodoDiputado *nuevoDiputado = crearNodoDiputado(ciudadano);

    if (diputados == NULL) {
        diputados = nuevoDiputado;
    } else {
        struct nodoDiputado *rec = diputados;
        while (rec->sig != diputados) {
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
struct nodoSenador *agregarSenador(struct nodoSenador *senadores, struct nodoCiudadano *ciudadanos, char *rut) {
    struct persona *ciudadano = buscarCiudadanoPorRUT(ciudadanos, rut);

    if (ciudadano == NULL) {
        printf("Ciudadano con RUT %s no encontrado.\n", rut);
        return senadores;
    }

    struct nodoSenador *nuevoSenador = crearNodoSenador(ciudadano);

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

struct nodoDiputado *eliminarDiputado(struct nodoDiputado *diputados, char *rut) {
    if (diputados == NULL) {
        printf("La lista de diputados está vacía.\n");
        return NULL;
    }

    struct nodoDiputado *rec = diputados;

    // Buscar el diputado por RUT
    do {
        if (strcmp(rec->headDiputados->rut, rut) == 0) {
            // Si es el único diputado en la lista
            if (rec->sig == rec && rec->ant == rec) {
                printf("Diputado eliminado correctamente (solo quedaba un diputado).\n");
                return NULL;
            }

            // Si es el diputado a eliminar y no es el único
            rec->ant->sig = rec->sig;
            rec->sig->ant = rec->ant;

            if (rec == diputados) {
                diputados = rec->sig; // Si es el primer diputado
            }

            printf("Diputado eliminado correctamente.\n");
            return diputados;
        }
        rec = rec->sig;
    } while (rec != diputados);

    printf("Diputado no encontrado.\n");
    return diputados;
}

struct nodoSenador *eliminarSenador(struct nodoSenador *senadores, char *rut) {
    if (senadores == NULL) {
        printf("La lista de senadores está vacía.\n");
        return NULL;
    }

    struct nodoSenador *rec = senadores;

    // Buscar el senador por RUT
    do {
        if (strcmp(rec->headSenadores->rut, rut) == 0) {
            // Si es el único senador en la lista
            if (rec->sig == rec && rec->ant == rec) {
                printf("Senador eliminado correctamente (solo quedaba un senador).\n");
                return NULL;
            }

            // Si es el senador a eliminar y no es el único
            rec->ant->sig = rec->sig;
            rec->sig->ant = rec->ant;

            if (rec == senadores) {
                senadores = rec->sig; // Si es el primer senador
            }

            printf("Senador eliminado correctamente.\n");
            return senadores;
        }
        rec = rec->sig;
    } while (rec != senadores);

    printf("Senador no encontrado.\n");
    return senadores;
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



/* Función Promulgación y Veto Presidencial */
void promulgacionOVetoPresidencial(struct presidente *presidente, struct propuesta *propuesta, struct congreso *congreso) {
    if (presidente == NULL) {
        printf("No hay un presidente registrado.\n");
        return;
    }

    int decisionPresidencial;
    printf("El presidente %s está evaluando la propuesta \"%s\" (ID: %d).\n", presidente->persona->nombre, propuesta->tema, propuesta->id);
    printf("¿Cuál es la decisión del presidente?\n");
    printf("1. Promulgar la ley\n");
    printf("2. Veto total (rechazar todo el proyecto)\n");
    printf("3. Veto parcial (sugerir modificaciones a ciertos artículos)\n");
    printf("Elige una opción: ");
    scanf("%d", &decisionPresidencial);

    // Decisión presidencial
    if (decisionPresidencial == 1) {
        printf("El presidente %s ha promulgado la propuesta \"%s\" como ley.\n", presidente->persona->nombre, propuesta->tema);
    } 
    else if (decisionPresidencial == 2) {
        printf("El presidente %s ha vetado totalmente la propuesta \"%s\".\n", presidente->persona->nombre, propuesta->tema);
        printf("El proyecto ha sido rechazado por el presidente y no avanzará.\n");
    } 
    else if (decisionPresidencial == 3) {
        printf("El presidente %s ha vetado parcialmente la propuesta \"%s\" y ha sugerido modificaciones.\n", presidente->persona->nombre, propuesta->tema);
        
        int decisionCongreso;
        printf("El Congreso debe decidir si acepta las modificaciones.\n");
        printf("1. Aceptar las modificaciones del presidente\n");
        printf("2. Rechazar el veto con una mayoría de dos tercios\n");
        printf("Elige una opción: ");
        scanf("%d", &decisionCongreso);

        if (decisionCongreso == 1) {
            printf("El Congreso ha aceptado las modificaciones. La ley ha sido promulgada con los cambios sugeridos por el presidente.\n");
        } 
        else if (decisionCongreso == 2) {
            int votosFavor = 0, votosContra = 0, votosTotales = 0;

            struct nodoDiputado *recDiputado = congreso->diputados;
            struct nodoSenador *recSenador = congreso->senadores;

            if (recDiputado != NULL) {
                do {
                    votosTotales++;
                    if (recDiputado->headDiputados->voto == 1) {
                        votosFavor++;
                    } else {
                        votosContra++;
                    }
                    recDiputado = recDiputado->sig;
                } while (recDiputado != congreso->diputados);
            }

            if (recSenador != NULL) {
                do {
                    votosTotales++;
                    if (recSenador->headSenadores->voto == 1) {
                        votosFavor++;
                    } else {
                        votosContra++;
                    }
                    recSenador = recSenador->sig;
                } while (recSenador != congreso->senadores);
            }

            if ((votosFavor * 3) >= (votosTotales * 2)) {
                printf("El Congreso ha rechazado el veto con una mayoría de dos tercios.\n");
                printf("La propuesta será promulgada tal como fue aprobada por el Congreso.\n");
            } 
            else {
                printf("El Congreso no logró una mayoría de dos tercios. La propuesta será modificada según las sugerencias del presidente.\n");
            }
        } 
        else {
            printf("Opción no válida.\n");
        }
    } 
    else {
        printf("Opción no válida. El proceso se cancela.\n");
    }
}

void comisionMixta(struct propuesta *propuesta, struct congreso *congreso) {
    printf("\n===== Comisión Mixta =====\n");
    printf("La propuesta ha sido enviada a la Comisión Mixta para resolver las discrepancias entre las cámaras.\n");

    int votosAFavorDiputados = 0, votosEnContraDiputados = 0;
    int votosAFavorSenadores = 0, votosEnContraSenadores = 0;
    int consenso = 0;

    // Votación de los diputados en la Comisión Mixta
    printf("\nVotación de los Diputados en la Comisión Mixta:\n");
    struct nodoDiputado *diputadoRec = congreso->diputados;
    if (diputadoRec != NULL) {
        do {
            if (diputadoRec->headDiputados->voto == 1) {
                votosAFavorDiputados++;
            } else {
                votosEnContraDiputados++;
            }
            diputadoRec = diputadoRec->sig;
        } while (diputadoRec != congreso->diputados);
    }

    printf("Diputados a favor: %d\n", votosAFavorDiputados);
    printf("Diputados en contra: %d\n", votosEnContraDiputados);

    // Votación de los senadores en la Comisión Mixta
    printf("\nVotación de los Senadores en la Comisión Mixta:\n");
    struct nodoSenador *senadorRec = congreso->senadores;
    if (senadorRec != NULL) {
        do {
            if (senadorRec->headSenadores->voto == 1) {
                votosAFavorSenadores++;
            } else {
                votosEnContraSenadores++;
            }
            senadorRec = senadorRec->sig;
        } while (senadorRec != congreso->senadores);
    }

    printf("Senadores a favor: %d\n", votosAFavorSenadores);
    printf("Senadores en contra: %d\n", votosEnContraSenadores);

    // Determinar si se alcanzó un consenso en la Comisión Mixta
    if ((votosAFavorDiputados > votosEnContraDiputados) && (votosAFavorSenadores > votosEnContraSenadores)) {
        consenso = 1;
        printf("\nLa Comisión Mixta ha alcanzado un consenso. El informe será enviado a ambas cámaras para su votación.\n");
    } else {
        printf("\nNo se alcanzó un consenso en la Comisión Mixta. El proyecto ha sido rechazado.\n");
    }

    // Si hay consenso, se procede a enviar el informe a ambas cámaras
    if (consenso) {
        printf("\nEl proyecto se envía a ambas cámaras para su votación final...\n");
        
        int votosAFavorTotal = votosAFavorDiputados + votosAFavorSenadores;
        int votosEnContraTotal = votosEnContraDiputados + votosEnContraSenadores;

        // Mostrar el resultado final de la votación combinada
        printf("Votos totales a favor: %d\n", votosAFavorTotal);
        printf("Votos totales en contra: %d\n", votosEnContraTotal);

        if (votosAFavorTotal > votosEnContraTotal) {
            printf("El proyecto ha sido aprobado por ambas cámaras tras el consenso en la Comisión Mixta.\n");
        } else {
            printf("El proyecto ha sido rechazado por ambas cámaras tras la votación final.\n");
        }
    }
}

/* Función mostrarMenu con nueva opción para veto presidencial */
void mostrarMenu() {
    printf("\n===== Menu =====\n");
    printf("1. Crear Ciudadano\n");
    printf("2. Mostrar Ciudadanos\n");
    printf("3. Agregar Diputado\n");
    printf("4. Mostrar Diputados\n");
    printf("5. Agregar Senador\n");
    printf("6. Mostrar Senadores\n");
    printf("7. Agregar Presidente\n");
    printf("8. Mostrar Presidente\n");
    printf("9. Crear Propuesta\n");
    printf("10. Mostrar Propuesta\n");
    printf("11. Iniciar Cámara de Origen\n");
    printf("12. Iniciar Cámara Revisora\n");
    printf("13. Promulgación o Veto Presidencial\n");
    printf("14. Eliminar Diputado\n");
    printf("15. Eliminar Senador\n");
    printf("16. Comisión Mixta\n");  // Nueva opción agregada aquí
    printf("17. Salir\n");
    printf("================\n");
}

int main() {
    struct nodoDiputado *diputados = NULL;
    struct nodoSenador *senadores = NULL;
    struct nodoCiudadano *ciudadanos = NULL;
    struct presidente *presidente = NULL;
    struct propuesta *propuesta = NULL;
    struct congreso congreso = {senadores, diputados}; // Estructura para el congreso

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
            // Crear Ciudadano
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

            printf("Ingresa el cargo (Diputado/Senador/Ciudadano): ");
            fgets(cargo, sizeof(cargo), stdin);
            cargo[strcspn(cargo, "\n")] = '\0';

            printf("Ingresa el voto (1=afirmativo, 0=negativo): ");
            scanf("%d", &voto);
            limpiarBuffer();

            struct persona *ciudadano = crearPersona(rut, nombre, edad, especialidad, voto, cargo);
            ciudadanos = agregarCiudadano(ciudadanos, ciudadano);
            printf("Ciudadano agregado exitosamente.\n");

        } else if (opcion == 2) {
            // Mostrar Ciudadanos
            mostrarCiudadanos(ciudadanos);

        } else if (opcion == 3) {
            // Agregar Diputado
            printf("Ingresa el RUT del ciudadano a agregar como diputado: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            diputados = agregarDiputado(diputados, ciudadanos, rut);

        } else if (opcion == 4) {
            // Mostrar Diputados
            mostrarDiputados(diputados);

        } else if (opcion == 5) {
            // Agregar Senador
            printf("Ingresa el RUT del ciudadano a agregar como senador: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            senadores = agregarSenador(senadores, ciudadanos, rut);

        } else if (opcion == 6) {
            // Mostrar Senadores
            mostrarSenadores(senadores);

        } else if (opcion == 7) {
            // Agregar Presidente
            printf("Ingresa el RUT del presidente: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';

            struct persona *personaPresidente = buscarCiudadanoPorRUT(ciudadanos, rut);
            if (personaPresidente == NULL) {
                printf("El ciudadano con RUT %s no existe.\n", rut);
            } else {
                printf("Ingresa el año de mandato del presidente: ");
                scanf("%d", &anioMandato);
                limpiarBuffer();

                presidente = crearPresidente(personaPresidente, anioMandato, personaPresidente->voto);
                printf("Presidente agregado exitosamente.\n");
            }

        } else if (opcion == 8) {
            // Mostrar Presidente
            mostrarPresidente(presidente);

        } else if (opcion == 9) {
            // Crear Propuesta
            if (presidente == NULL) {
                printf("Primero debes agregar un presidente para asignar una propuesta.\n");
            } else {
                propuesta = crearPropuesta(presidente->persona);
            }

        } else if (opcion == 10) {
            // Mostrar Propuesta
            mostrarPropuesta(propuesta);

        } else if (opcion == 11) {
            // Iniciar Cámara de Origen
            if (propuesta == NULL) {
                printf("Primero debes crear una propuesta para iniciar la Cámara de Origen.\n");
            } else {
                camaraDeOrigen(propuesta, &congreso);
            }

        } else if (opcion == 12) {
            // Iniciar Cámara Revisora
            if (propuesta == NULL) {
                printf("Primero debes crear una propuesta para iniciar la Cámara Revisora.\n");
            } else {
                camaraRevisora(propuesta, &congreso);
            }

        } else if (opcion == 13) {
            // Promulgación o Veto Presidencial
            if (presidente == NULL || propuesta == NULL) {
                printf("Se necesita tanto un presidente como una propuesta para proceder con la promulgación o veto.\n");
            } else {
                promulgacionOVetoPresidencial(presidente, propuesta, &congreso);
            }

        } else if (opcion == 14) {
            // Eliminar Diputado
            printf("Ingresa el RUT del diputado a eliminar: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            diputados = eliminarDiputado(diputados, rut);

        } else if (opcion == 15) {
            // Eliminar Senador
            printf("Ingresa el RUT del senador a eliminar: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            senadores = eliminarSenador(senadores, rut);

        } else if (opcion == 16) {
            // Comisión Mixta
            if (propuesta == NULL) {
                printf("Primero debes crear una propuesta para enviar a la Comisión Mixta.\n");
            } else {
                comisionMixta(propuesta, &congreso);
            }

        } else if (opcion == 17) {
            printf("Saliendo del programa...\n");
            salir = 1;

        } else {
            printf("Opción no válida. Por favor, intenta de nuevo.\n");
        }
    } while (!salir);

    return 0;
}
