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

/* Cambio 1.7
Francisco Espinoza
    se modifico la funcion de camara de origen ya que esta no contabilizaba los votos
    se modifico el main ya que no se inicalizaba bien el Agregar y Mostrar diputados y senadores
*/

/* Cambio 1.8
Francisco Espinoza
    se agrego NodoPropuestas
    se agrego insertarPropuesta (al ABB)
    se modifico el crearPropuesta
    se agrego buscar propuesta(POR ID)
    se modifico el main
    SE DEBE MODIFICAR:
    SE DEBE AGREGAR EL ABB PARA RECORRER LA PROPUESTA
        
        cambio 1.8.1 Francisco Espinoza
            se arreglo la funcion de camara de origen:
                -recorre el nodoProyecto y lo busca por ID
                - se puede ejecutar mas de 1 vez con diferentes proyectos
    SE DEBE MODIFICAR:
        -CAMARA REVISORIA
        -COMISION MIXTA
        -PROMULGACION Y VETO PRESIDENCIAL
    ---SIN REVISAR---

        cambio 1.8.2 Francisco espinoza
        se arreglaron las funcionciones de comision Mixta y promulgacion o veto presidencial
            - las dos recorren el nodoProyecto y busca el proyecto en cuestion a travez del ID
            - se puede ejecutar mas de 1 vez con diferentes proyectos
            ---SIN REVISAR---
    SE DEBE MODIFICAR:
        -COMISION MIXTA

--IMPORTANTE---
    SE DEBE ARREGLAR EL MAIN YA QUE AL UTILIZAR EL STRUCT CONGRESO LO USA CON "." EN VEZ DE "->"

*/

/* Cambio 1.9 
Simon Ledezma

    // cosas que he notado y que hay que arreglar:
        - agregar datos estadisticos
        - en la funcion 14 el pause no funciona cuando se ejecuta el veto presidencial, revisar xfa
        - la estructura ProcesoLegislativo no se inicia en el main sino que se inician las que estan dentro de ella, revisar eso
        - hay que hacer una funcion que permita cambiar el cargo de un ciudadano a diputado o senador y viceversa
        - hay que hacer una funcion que permita cambiar el voto de un ciudadano, diputado o senador
        - hay que hacer una funcion que permita eliminar un ciudadano
        - hay que hacer una funcion que permita eliminar una propuesta
        - en las funciones de eliminar diputado y senador hay que cambiar el cargo de la persona a ciudadano
    //

    // cambios: 
        - se cambio la estructura de congreso, ahora se inicializa como puntero, se le asigna memoria y se accede con ->

        - se modifico la funcion comisionMixta, ahora recorre la lista de diputados y senadores 
            y pide el voto de cada uno mediante la funcion votoDiputadoCmMixta y votoSenadorCmMixta
            
        - se agregaron las funciones pause y cls, para pausar el programa y limpiar la pantalla respectivamente
            + la funcion pause es para que el programa se detenga y al presionar enter continue
            + la funcion cls es para limpiar la pantalla, para pruebas se puede cambiar el for para que no limpie tanto

        - se modularizo la funcion de crearCiudadano, el main queda mas limpio
        - al crear una persona no se le asigna un voto ya que no se ha votado nada aun
        - se agregaron las funciones buscarDiputadoPorRUT y buscarSenadorPorRUT para verificar si un diputado o senador ya existe
        - se cambio el cargo del struct persona y ahora es un int, 0 = ciudadano, 1 = diputado, 2 = senador, 3 = presidente
        - se robustiza la funcion crearCiudadano, ahora se verifica que se ingresen datos validos
        - se cambio la funcion de agregarDiputado, ahora se verifica si el ciudadano ya es senador o presidente
        - se cambio la funcion de agregarSenador, ahora se verifica si el ciudadano ya es diputado o presidente
        - la funcion mostrarCiudadanos ahora muestra el cargo correcto de la persona
    //

    iba a meter datos de prueba pero no se q wea hice y no quiso andar </3
    
*/

/* cambios 1.10
Francisco Espinoza
    - se modifico la funcion de comision mixta, ahora busca el proyecto por ID
    - se arreglo uno de los 10 warnings de VS code
    -se encuentra probema en agregar presidente (segmentation fault)

*/

/* --- NOTA ---
    el dia de hoy se va revisar el codigo en turbo C para tener constancia de los warnings y errores que se den en este
    Hora: 20:30.
    favor de ingresar
    primera constancia: [numero de errores]

*/
struct ProcesoLegislativo{
  struct presidente *presidente;
  struct congreso *congreso;
  struct nodoPropuestas *propuesta;
  struct nodoCiudadano *ciudadanos;
  struct tribunalConstitucional *tc; // pensando en q esto es como la imagen del coco del tf2 q no hace nada pero si lo borras se rompe todo
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
    char *estado;
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
  int cargo; // 0 = ciudadano, 1 = diputado, 2 = senador
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

void pause() {
    printf("\nPresiona Enter para continuar...");
    getchar();
}

void cls() {
    int i;
    for(i = 0; i < 100; i++) {
        printf("\n");
    }
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Vaciar el buffer
    }
}

struct persona *crearPersona(char *rut, char *nombre, int edad, char *especialidad, int voto, int cargo) {

    struct persona *nuevaPersona;
    nuevaPersona = (struct persona *) malloc(sizeof(struct persona));

    nuevaPersona->rut = (char *) malloc(sizeof(char) * strlen(rut) + 1);
    strcpy(nuevaPersona->rut, rut);

    nuevaPersona->nombre = (char *) malloc(sizeof(char) * strlen(nombre) + 1);
    strcpy(nuevaPersona->nombre, nombre);

    nuevaPersona->edad = edad;

    nuevaPersona->cargo = cargo;

    nuevaPersona->especialidad = (char *) malloc(sizeof(char) * strlen(especialidad) + 1);
    strcpy(nuevaPersona->especialidad, especialidad);

    nuevaPersona->voto = voto;

    return nuevaPersona;
}


struct persona* crearCiudadano() {

    struct persona *nuevoCiudadano;
    char rut[20], nombre[50], especialidad[50];
    int edad, voto, cargo;

    printf("Ingresa el RUT: ");
    fgets(rut, sizeof(rut), stdin);
    rut[strcspn(rut, "\n")] = '\0';

    printf("Ingresa el nombre: ");
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    printf("Ingresa la edad: ");

    while (1) {
        if (scanf("%d", &edad) == 1 && edad >= 18) {
            limpiarBuffer();
            break;
        } else {
            printf("Edad inválida. Inténtalo de nuevo\n");
            limpiarBuffer();
        }
    }

    printf("Ingresa la especialidad: ");
    fgets(especialidad, sizeof(especialidad), stdin);
    especialidad[strcspn(especialidad, "\n")] = '\0';

    printf("Ingresa el cargo (0 = Ciudadano, 1 = Diputado, 2 = Senador, 3 = Presidente): ");

    while (1) {
        if (scanf("%d", &cargo) == 1) {
            if (cargo >= 0 && cargo <= 2) {
                limpiarBuffer();
                break;
            } else if (cargo == 3) {
                printf("No puedes crear un presidente directamente. Debe ser ingresado mediante la opcion 7 luego de ser creado como ciudadano.\n");
            } else {
                printf("Cargo inválido. Inténtalo de nuevo\n");
            }
        } else {
            printf("Entrada inválida. Inténtalo de nuevo\n");
            limpiarBuffer();
        }
    }

    voto = 0; // Inicialmente no ha votado en nada

    nuevoCiudadano = crearPersona(rut, nombre, edad, especialidad, voto, cargo);
    return nuevoCiudadano;
}

struct nodoCiudadano *crearNodoCiudadano(struct persona *ciudadano) {
    struct nodoCiudadano *nuevoCiudadano;
    nuevoCiudadano = (struct nodoCiudadano *) malloc(sizeof(struct nodoCiudadano));
    nuevoCiudadano->datos = ciudadano;
    nuevoCiudadano->ant = nuevoCiudadano->sig = NULL;
    return nuevoCiudadano;
}

struct persona *buscarCiudadanoPorRUT(struct nodoCiudadano *ciudadanos, char *rut) {
    struct nodoCiudadano *rec = ciudadanos;
    
    if (rec == NULL) {
        return NULL;
    }

    while (rec != NULL) {
        if (strcmp(rec->datos->rut, rut) == 0) {
            return rec->datos;
        }
        rec = rec->sig;
    }
    return NULL;
}

int buscarDiputadoPorRUT(struct nodoDiputado *diputados, char *rut) {
    struct nodoDiputado *rec = diputados;

    if (rec == NULL) {
        return 0;
    }
    do {
        if (strcmp(rec->headDiputados->rut, rut) == 0) {
            return 1;
        }
        rec = rec->sig;
    } while (rec != diputados);

    return 0;
}

int buscarSenadorPorRUT(struct nodoSenador *senadores, char *rut) {
    struct nodoSenador *rec = senadores;

    if (rec == NULL) {
        return 0;
    }
    do {
        if (strcmp(rec->headSenadores->rut, rut) == 0) {
            return 1;
        }
        rec = rec->sig;
    } while (rec != senadores);

    return 0;
}

struct nodoCiudadano *agregarCiudadano(struct nodoCiudadano *ciudadanos, struct persona *ciudadano) {
    struct nodoCiudadano *nuevoCiudadano = crearNodoCiudadano(ciudadano);

    if (buscarCiudadanoPorRUT(ciudadanos, ciudadano->rut) != NULL) {
        printf("Ciudadano con RUT %s ya existe en el sistema\n", ciudadano->rut);
        return ciudadanos;
    }

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
    printf("Ciudadano agregado exitosamente.\n");
    return ciudadanos;
}


void mostrarCiudadanos(struct nodoCiudadano *ciudadanos) {
    if (ciudadanos == NULL) {
        printf("No hay ciudadanos en el sistema.\n");
        return;
    }

    struct nodoCiudadano *rec = ciudadanos;
    while (rec != NULL) {
        printf("Nombre: %s\n", rec->datos->nombre);
        printf("RUT: %s\n", rec->datos->rut);
        printf("Edad: %d\n", rec->datos->edad);
        printf("Especialidad: %s\n", rec->datos->especialidad);
        if (rec->datos->cargo == 0) {
            printf("Cargo: Ciudadano\n\n");
        } else if (rec->datos->cargo == 1) {
            printf("Cargo: Diputado\n\n");
        } else if (rec->datos->cargo == 2) {
            printf("Cargo: Senador\n\n");
        } else if (rec->datos->cargo == 3) {
            printf("Cargo: Presidente\n\n");
        }
        rec = rec->sig;
    }
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

    if(ciudadano->cargo == 2){
        printf("La persona con RUT %s tiene el cargo de senador.\n", ciudadano->rut);
        return diputados;
    }

    if(ciudadano->cargo == 3){
        printf("La persona con RUT %s tiene el cargo de presidente.\n", ciudadano->rut);
        return diputados;
    }

    if(buscarDiputadoPorRUT(diputados, rut) == 1){
        printf("Diputado con RUT %s ya existe en el sistema\n", ciudadano->rut);
        return diputados;
    }

    ciudadano->cargo = 1;
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
    printf("Diputado agregado exitosamente.\n");
    return diputados;
}

void mostrarDiputados(struct nodoDiputado *diputados){
    struct nodoDiputado *rec = diputados;
    if (rec == NULL) {
        printf("No hay diputados en el sistema.\n");
        return;
    }
    do{
        printf("Nombre: %s\n", rec->headDiputados->nombre);
        printf("Edad: %d\n", rec->headDiputados->edad);
        printf("Especialidad: %s\n", rec->headDiputados->especialidad);
        printf("Cargo: Diputado\n");
        rec = rec->sig;
    } while (rec != diputados);
}

struct nodoPropuestas *insertarPropuesta(struct nodoPropuestas *raiz, struct propuesta *nuevaPropuesta) {
    if (raiz == NULL) {
        struct nodoPropuestas *nuevoNodo = (struct nodoPropuestas *)malloc(sizeof(struct nodoPropuestas));
        nuevoNodo->datos = nuevaPropuesta;
        nuevoNodo->izq = nuevoNodo->der = NULL;
        return nuevoNodo;
    }
    
    if (nuevaPropuesta->id < raiz->datos->id) {
        raiz->izq = insertarPropuesta(raiz->izq, nuevaPropuesta);
    } else if (nuevaPropuesta->id > raiz->datos->id) {
        raiz->der = insertarPropuesta(raiz->der, nuevaPropuesta);
    } else {
        printf("Propuesta con ID %d ya existe.\n", nuevaPropuesta->id);
    }
    
    return raiz;
}

struct presidente *crearPresidente(struct persona *persona) {
    int anioMandato;

    if (persona->cargo == 1) {
        printf("La persona tiene el cargo de diputado.\n");
        return NULL;
    } else if (persona->cargo == 2) {
        printf("La persona tiene el cargo de senador.\n");
        return NULL;
    } else if (persona->cargo == 3) {
        printf("La persona ya tiene el cargo de presidente.\n");
        return NULL;
    }

    persona->cargo = 3;
    printf("Ingresa el año de mandato del presidente: ");
    scanf("%d", &anioMandato);
    limpiarBuffer();

    struct presidente *nuevoPresidente;
    nuevoPresidente = (struct presidente *)malloc(sizeof(struct presidente));

    nuevoPresidente->persona = persona;
    nuevoPresidente->anioMandato = anioMandato;
    nuevoPresidente->voto = 0;

    printf("Presidente agregado exitosamente.\n");

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
    } else if (ciudadano->cargo == 1) {
        printf("La persona con RUT %s tiene el cargo de diputado.\n", ciudadano->rut);
        return senadores;
    } else if (ciudadano->cargo == 3) {
        printf("La persona con RUT %s tiene el cargo de presidente.\n", ciudadano->rut);
        return senadores;
    } else if (buscarSenadorPorRUT(senadores, rut) == 1) {
        printf("Senador con RUT %s ya existe en el sistema.\n", ciudadano->rut);
        return senadores;
    }

    ciudadano->cargo = 2;
    struct nodoSenador *nuevoSenador = crearNodoSenador(ciudadano);

    if (senadores == NULL) {
        senadores = nuevoSenador;
    } else {
        struct nodoSenador *rec = senadores;
        while (rec->sig != senadores) {
            rec = rec->sig;
        }
        nuevoSenador->headSenadores->cargo = 2;
        rec->sig = nuevoSenador;
        nuevoSenador->ant = rec;
        nuevoSenador->sig = senadores;
        senadores->ant = nuevoSenador;
    }

    printf("Senador agregado exitosamente.\n");
    return senadores;
}

struct propuesta *buscarPropuesta(struct nodoPropuestas *raiz, int id) {
    if (raiz == NULL) {
        return NULL; // No encontrada
    }

    if (id == raiz->datos->id) {
        return raiz->datos;
    } else if (id < raiz->datos->id) {
        return buscarPropuesta(raiz->izq, id);
    } else {
        return buscarPropuesta(raiz->der, id);
    }
}

struct nodoPropuestas *crearPropuesta(struct nodoPropuestas *raiz, struct persona *autor) {
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

    return insertarPropuesta(raiz, nuevaPropuesta); // Insertar en el ABB
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
        printf("Cargo: Senador\n\n");
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
    printf("================================\n");
}

void camaraDeOrigen(struct nodoPropuestas *raizPropuestas, struct congreso *congreso) {
    int idPropuesta;
    printf("Ingresa el ID de la propuesta a discutir: ");
    scanf("%d", &idPropuesta);

    // Buscar la propuesta por ID en el ABB
    struct propuesta *propuesta = buscarPropuesta(raizPropuestas, idPropuesta);
    if (propuesta == NULL) {
        printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
        return;
    }

    int votosAFavor = 0, votosEnContra = 0;

    // Verificar si el proyecto debe iniciar en la Cámara de Diputados o en el Senado
    if (strcmp(propuesta->tipo, "financiero") == 0 || strcmp(propuesta->tipo, "tributario") == 0) {
        printf("El proyecto de tipo %s debe ser discutido primero en la Cámara de Diputados.\n", propuesta->tipo);
        
        // Simular votación de todos los miembros de la Cámara de Diputados
        struct nodoDiputado *rec = congreso->diputados;
        if (rec == NULL) {
            printf("No hay diputados disponibles para votar.\n");
            return;
        }

        do {
            if (rec->headDiputados->voto == 1) {
                votosAFavor++;
            } else {
                votosEnContra++;
            }
            rec = rec->sig;
        } while (rec != congreso->diputados);  // Iteración completa de la lista circular de diputados
        
    } else {
        printf("El proyecto de tipo %s será discutido en el Senado.\n", propuesta->tipo);
        
        // Simular votación de todos los miembros del Senado
        struct nodoSenador *rec = congreso->senadores;
        if (rec == NULL) {
            printf("No hay senadores disponibles para votar.\n");
            return;
        }

        do {
            if (rec->headSenadores->voto == 1) {
                votosAFavor++;
            } else {
                votosEnContra++;
            }
            rec = rec->sig;
        } while (rec != congreso->senadores);  // Iteración completa de la lista circular de senadores
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
    pause();
}

void mostrarPropuesta(struct propuesta *propuesta) {
    if (propuesta == NULL) {
        printf("No se encontró la propuesta con el ID especificado.\n");
    } else {
        printf("\n===== Datos de la Propuesta =====\n");
        printf("ID de la propuesta: %d\n", propuesta->id);
        printf("Tipo: %s\n", propuesta->tipo);
        printf("Tema: %s\n", propuesta->tema);
        printf("Autor: %s\n", propuesta->personaAcargo->nombre);
        printf("=================================\n");
    }
}
void mostrarPropuestas(struct nodoPropuestas *raiz) {
    if (raiz == NULL) {
        printf("No hay propuestas registradas.\n");
        return;
    }

    // Recorrido inorden (izquierda, raíz, derecha)
    if (raiz->izq != NULL) {
        mostrarPropuestas(raiz->izq); // Lado izquierdo del árbol
    }

    // Mostrar la propuesta actual (nodo raíz)
    printf("\n===== Datos de la Propuesta =====\n");
    printf("ID de la propuesta: %d\n", raiz->datos->id);
    printf("Tipo: %s\n", raiz->datos->tipo);
    printf("Tema: %s\n", raiz->datos->tema);
    printf("Autor: %s\n", raiz->datos->personaAcargo->nombre);
    printf("=================================\n");

    // Recorrido por el lado derecho del árbol
    if (raiz->der != NULL) {
        mostrarPropuestas(raiz->der);
    }
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
/* Función para manejar la Cámara Revisora */
void camaraRevisora(struct nodoPropuestas *raizPropuestas, struct congreso *congreso) {
    int idPropuesta;
    printf("Ingresa el ID de la propuesta a discutir en la Cámara Revisora: ");
    scanf("%d", &idPropuesta);

    // Buscar la propuesta por ID en el ABB
    struct propuesta *propuesta = buscarPropuesta(raizPropuestas, idPropuesta);
    if (propuesta == NULL) {
        printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
        return;
    }

    printf("La propuesta con ID %d ha llegado a la Cámara Revisora.\n", idPropuesta);

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
    pause();
}

/* Función Promulgación y Veto Presidencial */
void promulgacionOVetoPresidencial(struct presidente *presidente, struct nodoPropuestas *raizPropuestas, struct congreso *congreso) {
    int idPropuesta;
    int decisionPresidencial;

    if (presidente == NULL) {
        printf("No hay un presidente registrado.\n");
        return;
    }

    printf("Ingresa el ID de la propuesta a discutir para promulgación o veto presidencial: ");
    scanf("%d", &idPropuesta);

    // Buscar la propuesta por ID en el ABB
    struct propuesta *propuesta = buscarPropuesta(raizPropuestas, idPropuesta);
    if (propuesta == NULL) {
        printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
        return;
    }

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

            if ((votosFavor * 3) >= (votosTotales * 2 && votosContra < votosFavor)) {
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

int votoDiputadoCmMixta(struct nodoDiputado *diputado) {
    int voto;
    printf("Ingrese el voto del diputado %s (1 = A favor, Otro numero = En contra): ", diputado->headDiputados->nombre);
    scanf("%d", &voto);
    return voto;
}

int votoSenadorCmMixta(struct nodoSenador *senador) {
    int voto;
    printf("Ingrese el voto del senador %s (1 = A favor, Otro numero = En contra): ", senador->headSenadores->nombre);
    scanf("%d", &voto);
    return voto;
}

void comisionMixta(struct nodoPropuestas *raizPropuestas, struct congreso *congreso) {
    int idPropuesta;
    printf("Ingresa el ID de la propuesta a enviar a la Comisión Mixta: ");
    scanf("%d", &idPropuesta);
    limpiarBuffer();  // Para evitar errores al leer entrada

    // Buscar la propuesta por ID en el ABB de propuestas
    struct propuesta *propuesta = buscarPropuesta(raizPropuestas, idPropuesta);
    if (propuesta == NULL) {
        printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
        return;
    }

    printf("\n===== Comisión Mixta =====\n");
    printf("La propuesta '%s' ha sido enviada a la Comisión Mixta para resolver discrepancias.\n", propuesta->tema);

    int votoDiputado, votoSenador;
    int votosAFavorDiputados = 0, votosEnContraDiputados = 0;
    int votosAFavorSenadores = 0, votosEnContraSenadores = 0;
    int consenso = 0;

    // Votación de los diputados en la Comisión Mixta
    printf("\nVotación de los Diputados en la Comisión Mixta:\n");
    struct nodoDiputado *diputadoRec = congreso->diputados;
    if (diputadoRec != NULL) {
        do {
            votoDiputado = votoDiputadoCmMixta(diputadoRec);
            if (votoDiputado == 1) {
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
            votoSenador = votoSenadorCmMixta(senadorRec);
            if (votoSenador == 1) {
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
    printf("10. Mostrar Propuesta por ID\n");
    printf("11. Mostrar Todas las Propuestas\n"); // Nueva opción
    printf("12. Iniciar Cámara de Origen\n");
    printf("13. Iniciar Cámara Revisora\n");
    printf("14. Promulgación o Veto Presidencial\n");
    printf("15. Eliminar Diputado\n");
    printf("16. Eliminar Senador\n");
    printf("17. Comisión Mixta\n");
    printf("18. Salir\n");
    printf("================\n");
}

int main() {
    struct ProcesoLegislativo *procesoLegislativo = NULL;
    struct nodoDiputado *diputados = NULL;
    struct nodoSenador *senadores = NULL;
    struct nodoCiudadano *ciudadanos = NULL;
    struct presidente *presidente = NULL;
    struct nodoPropuestas *propuestas = NULL;  // Árbol de propuestas

    int opcion;
    char *rut, *nombre, *especialidad, *cargo;
    int edad, voto, anioMandato;
    int salir = 0;

    // Inicializa el congreso y le asigna memoria, si falla retorna 1
    struct congreso *congreso;
    congreso = (struct congreso *)malloc(sizeof(struct congreso));
    if (congreso == NULL) {
        printf("Error al asignar memoria para la estructura congreso.\n");
        return 1;
    }

    congreso->diputados = NULL;  // Inicializando en NULL para evitar acceso a memoria no válida
    congreso->senadores = NULL;

    /* Datos de ciudadanos de prueba

    struct ciudadano *ciudadano1 = crearPersona("12345678-9", "Juan Perez", 30, "Ingeniero", 1, "Ciudadano");
    struct ciudadano *ciudadano2 = crearPersona("98765432-1", "Maria Lopez", 25, "Abogada", 0, "Ciudadano");
    struct ciudadano *ciudadano3 = crearPersona("11223344-5", "Carlos Sanchez", 40, "Doctor", 1, "Ciudadano");
    struct ciudadano *ciudadano4 = crearPersona("55667788-0", "Ana Martinez", 35, "Arquitecta", 1, "Ciudadano");
    struct ciudadano *ciudadano5 = crearPersona("99887766-5", "Luis Gomez", 28, "Economista", 0, "Ciudadano");

    */

    do {
        cls();
        mostrarMenu();
        printf("Elige una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        if (opcion == 1) {
            // Crear Ciudadano
            struct persona *ciudadano = crearCiudadano();
            ciudadanos = agregarCiudadano(ciudadanos, ciudadano);
            pause();

        } else if (opcion == 2) {
            // Mostrar Ciudadanos
            mostrarCiudadanos(ciudadanos);
            pause();

        } else if (opcion == 3) {
            // Agregar Diputado
            printf("Ingresa el RUT del ciudadano a agregar como diputado: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            congreso->diputados = agregarDiputado(congreso->diputados, ciudadanos, rut); // Modificar correctamente la lista de diputados
            pause();

        } else if (opcion == 4) {
            // Mostrar Diputados
            mostrarDiputados(congreso->diputados);
            pause();

        } else if (opcion == 5) {
            // Agregar Senador
            printf("Ingresa el RUT del ciudadano a agregar como senador: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            congreso->senadores = agregarSenador(congreso->senadores, ciudadanos, rut);
            pause();

        } else if (opcion == 6) {
            // Mostrar Senadores
            mostrarSenadores(congreso->senadores);
            pause();

        } else if (opcion == 7) {
            // Agregar Presidente
            printf("Ingresa el RUT del presidente: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';

            struct persona *personaPresidente = buscarCiudadanoPorRUT(ciudadanos, rut);
            if (personaPresidente == NULL) {
                printf("El ciudadano con RUT %s no existe.\n", rut);
            }

            presidente = crearPresidente(personaPresidente);
            pause();
    
        } else if (opcion == 8) {
            // Mostrar Presidente
            mostrarPresidente(presidente);
            pause();

        } else if (opcion == 9) {
            // Crear Propuesta y agregarla al ABB
            if (presidente == NULL) {
                printf("Primero debes agregar un presidente para asignar una propuesta.\n");
            } else {
                propuestas = crearPropuesta(propuestas, presidente->persona);
            }
            pause();

        } else if (opcion == 10) {
            // Mostrar Propuesta por ID
            int idPropuesta;
            printf("Ingresa el ID de la propuesta a buscar: ");
            scanf("%d", &idPropuesta);
            limpiarBuffer();

            struct propuesta *propuestaEncontrada = buscarPropuesta(propuestas, idPropuesta);
            mostrarPropuesta(propuestaEncontrada); // Esta función ya maneja el caso si la propuesta es NULL
            pause();

        } else if (opcion == 11) {
            // Mostrar todas las propuestas
            mostrarPropuestas(propuestas);
            pause();

        } else if (opcion == 12) {
            // Iniciar Cámara de Origen
            if (propuestas == NULL) {
                printf("Primero debes crear una propuesta para iniciar la Cámara de Origen.\n");
            } else {
                camaraDeOrigen(propuestas, congreso);  // Asegurarse de pasar la estructura congreso correctamente
            }
            pause();

        } else if (opcion == 13) {
            // Iniciar Cámara Revisora
            if (propuestas == NULL) {
                printf("Primero debes crear una propuesta para iniciar la Cámara Revisora.\n");
            } else {
                camaraRevisora(propuestas, congreso);  // Asegurarse de pasar la estructura congreso correctamente
            }
            pause();
        } else if (opcion == 14) {
            // Promulgación o Veto Presidencial
            if (presidente == NULL || propuestas == NULL) {
                printf("Se necesita tanto un presidente como una propuesta para proceder con la promulgación o veto.\n");
                
            } else {
                promulgacionOVetoPresidencial(presidente, propuestas, congreso);  // Asegurarse de pasar la estructura congreso correctamente
                
            }
            pause();
        } else if (opcion == 15) {
            // Eliminar Diputado
            printf("Ingresa el RUT del diputado a eliminar: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            congreso->diputados = eliminarDiputado(congreso->diputados, rut);  // Modificar correctamente la lista de diputados
            pause();

        } else if (opcion == 16) {
            // Eliminar Senador
            printf("Ingresa el RUT del senador a eliminar: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            congreso->senadores = eliminarSenador(congreso->senadores, rut);  // Modificar correctamente la lista de senadores
            pause();
            
        } else if (opcion == 17) {
            // Comisión Mixta
            if (propuestas == NULL) {
                printf("Primero debes crear una propuesta para enviar a la Comisión Mixta.\n");
            } else {
                comisionMixta(propuestas, congreso);  // Asegurarse de pasar la estructura congreso correctamente
            }
            pause();
            
        } else if (opcion == 18) {
            printf("Saliendo del programa...\n");
            salir = 1;
            pause();

        } else {
            printf("Opción no válida. Por favor, intenta de nuevo.\n");
            pause();
        }
    } while (!salir);

    return 0;
}
