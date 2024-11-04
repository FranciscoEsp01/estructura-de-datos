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
    - se agrega la funcion de publicacion y entrada en vigencia
    --- SIN REVISAR---

*/

/* cambios 1.11
Francisco espinoza
    - se arreglan los structs del main
    - se arreglan los warnings de datos sin utilizar
    ---SE DEBE PROBAR EN TURBO C---
*/

/* cambios 1.12
Francisco Espinoza
    -se arregla el codigo para que compile en turbo C
    - actualmente solo contiene 1 warning en la maquina virtual
*/
/* --- NOTA ---
    el dia de hoy se va revisar el codigo en turbo C para tener constancia de los warnings y errores que se den en este
    Hora: 20:30.
    favor de ingresar
    primera constancia: [numero de errores]

*/

/* cambios 1.13
Simon Ledezma

    *** cambios ***

    - se completa la logica de las funciones de comisionMixta y promulgacionOVetoPresidencial
        + antes se ocupaba el voto por defecto de los diputados y senadores, ahora se pide el voto de cada uno
        + se eliminan las funciones votoDiputadoCmMixta y votoSenadorCmMixta ya que no son necesarias para la logica actual

    *** funciones agregadas ***

    - se agrega la funcion eliminarLeyDeBoletin, que elimina una ley del boletin de estado
    - se agrega un arreglo de 10 ministros para el tribunal constitucional
    - en el main se asignan valores nulos al arreglo vacio de ministros, con la funcion poblarTribunalConstitucional
    - se agrega la funcion agregarMinistroTribunalConstitucional, que agrega un ministro al tribunal constitucional
    - se agrega la funcion mostrarTribunalConstitucional, que muestra los ministros del tribunal constitucional
    - se agrega la funcion eliminarMinistroTribunalConstitucional, que elimina un ministro del tribunal constitucional
    - se agrega funcion controlConstitucionalidad, para hacer el control constitucional con su respectiva votacion
        + esta hace uso de la funcion realizarVotacionMinistros, para asignar los votos de cada ministro para declarar la constitucionalidad de una ley
        + y tmb hace uso de la funcion verificarTC, si no hay suficientes ministros no se realiza la votación

    *** cambios en el main ***

    - se agregan las funciones al menu (19, 20, 21, 22, 23)
    - se ocupa la funcion de poblarTribunalConstitucional al inicio del main

    *** cosas a considerar ***

    - se debe probar la funcion de controlConstitucionalidad
    - hay varias declaraciones donde no deberían, cambiar para que compile en turbo c
    - si alguien se pone la 10 y modulariza el else del control constitucional en el main se lo agradecería

    *** nota ***

    la logica está completa a este punto, solo hay que armar el informe y la presentación
    y faltan las funciones extra, son secundarias pero el programa hace solo lo que pide el enunciado asiq hay que armarlas para q no nos descuenten puntaje
    (con una funcion que haga un porcentaje de proyectos aprobados y rechazados y otra que haga un promedio de edad de los diputados y senadores debería bastar)

*/

/* cambios 1.14
simon ledezma
    - se cambia el estado de la propuesta a int, 0 = en tramite, 1 = aprobada, 2 = rechazada
    - se agrega la funcion de eliminarCiudadano
    - se mueve el menú para que quede ordenado de forma que esten las funciones de cada tipo agrupadas
    - ahora las funciones que efectuan votaciones sobre una propuesta pueden cambiar el estado de esta
    - se completa la logica de absolutamente todas las funciones para votar
    - se agrega la funcion mostrarPromedioEdadCiudadanos
        + muestra el promedio de edad, la cantidad de ciudadanos y el porcentaje de los ciudadanos con una edad arriba del promedio

    - se agrega la funcion mostrarPorcentajeProyectosAprobados
        + esta hace uso de las funciones contarPropuestas y contarPropuestasAprobadas
        + muestra por pantalla el porcentaje de propuestas aprobadas, la cantidad de propuestas y la cantidad de propuestas aprobadas

    SOLO FALTA QUE COMPILE EN TURBO C Y SE TERMINA TODO ESTO DIOS SANTO
*/

/* cambios 1.15
simon ledezma
    - se agrega la funcion de eliminarCiudadano al menu q se me olvido
    - se revisaron todos los warnings que tira clion
    - se quitaron todas las tildes del programa pq el clion no las muestra cmo el visual
*/

struct presidente {
    struct persona *persona;
    int anioMandato;
    int voto;
};

/* nodoPropuestas ARBOL BINARIO DE BUSQUEDA*/
struct nodoPropuestas {
    struct propuesta *datos;
    struct nodoPropuestas *izq, *der;
};

struct propuesta {
    int id;
    char *tipo;
    char *tema;
    struct persona *personaAcargo;
    int estado; // 0 = en tramite, 1 = aprobada, 2 = rechazada
};

struct congreso {
    struct nodoSenador *senadores;
    struct nodoDiputado *diputados;
};

/*lista circular doble*/
struct nodoDiputado {
    struct persona *headDiputados;
    struct nodoDiputado *ant, *sig;
};

/*lista circular doble*/
struct nodoSenador {
    struct persona *headSenadores;
    struct nodoSenador *ant, *sig;
};

/*lista doble*/
struct nodoCiudadano {
  struct persona *datos;
  struct nodoCiudadano *ant, *sig;
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

struct persona {
  char rut[20];
  char nombre[50];
  int edad;
  int cargo; // 0 = ciudadano, 1 = diputado, 2 = senador, 3 = presidente, 4 = ministro
  char especialidad[20];
  int voto;
};

struct ProcesoLegislativo {
  struct presidente *presidente;
  struct congreso *congreso;
  struct nodoPropuestas *propuesta;
  struct nodoCiudadano *ciudadanos;
  struct nodoBoletin *boletinEstado;
  struct persona tribunalConstitucional[10];
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

struct persona *crearPersona(char *rut, char *nombre, int edad, char *especialidad, int voto) {

    struct persona *nuevaPersona;
    nuevaPersona = (struct persona *) malloc(sizeof(struct persona));

    strcpy(nuevaPersona->rut, rut);

    strcpy(nuevaPersona->nombre, nombre);

    nuevaPersona->edad = edad;

    nuevaPersona->cargo = 0;

    strcpy(nuevaPersona->especialidad, especialidad);

    nuevaPersona->voto = voto;

    return nuevaPersona;
}

struct persona* crearCiudadano() {

    struct persona *nuevoCiudadano;
    char rut[20], nombre[50], especialidad[50];
    int edad, voto;

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
            printf("Edad invalida. Intentalo de nuevo\n");
            limpiarBuffer();
        }
    }

    printf("Ingresa la especialidad: ");
    fgets(especialidad, sizeof(especialidad), stdin);
    especialidad[strcspn(especialidad, "\n")] = '\0';

    voto = 0; // Inicialmente no ha votado en nada

    nuevoCiudadano = crearPersona(rut, nombre, edad, especialidad, voto);
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
    struct nodoCiudadano *rec = ciudadanos;
    if (ciudadanos == NULL) {
        printf("No hay ciudadanos en el sistema.\n");
        return;
    }

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
        } else if (rec->datos->cargo == 4) {
            printf("Cargo: Ministro\n\n");
        }
        rec = rec->sig;
    }
}

struct nodoCiudadano *eliminarCiudadano(struct nodoCiudadano *ciudadanos, char *rut) {
    struct nodoCiudadano *rec = ciudadanos;

    if (rec == NULL) {
        printf("No hay ciudadanos en el sistema.\n");
        return ciudadanos;
    }

    while (rec != NULL) {
        if (strcmp(rec->datos->rut, rut) == 0) {
            // si es el unico ciudadano
            if (rec->ant == NULL && rec->sig == NULL) {
                printf("Ciudadano con RUT %s eliminado. No hay mas ciudadanos en el sistema.\n", rut);
                return NULL;

            // si es el primero
            } else if (rec->ant == NULL) {
                ciudadanos = rec->sig;
                ciudadanos->ant = NULL;
                printf("Ciudadano con RUT %s eliminado.\n", rut);
                return ciudadanos;

            // si es el ultimo
            } else if (rec->sig == NULL) {
                rec->ant->sig = NULL;
                printf("Ciudadano con RUT %s eliminado.\n", rut);
                return ciudadanos;

            // si esta entremedio
            } else {
                rec->ant->sig = rec->sig;
                rec->sig->ant = rec->ant;
                printf("Ciudadano con RUT %s eliminado.\n", rut);
                return ciudadanos;
            }
        }
        rec = rec->sig;
    }

    printf("Ciudadano con RUT %s no encontrado.\n", rut);
    return ciudadanos;
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
    struct nodoDiputado *nuevoDiputado = crearNodoDiputado(ciudadano);

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
    struct presidente *nuevoPresidente;
    int anioMandato;


    if (persona->cargo == 3) {
        printf("La persona ya tiene el cargo de presidente.\n");
        return NULL;
    }
    else if (persona->cargo != 0) {
        printf("La persona ya tiene un cargo publico. No puede ser presidente.\n");
        return NULL;
    }
    persona->cargo = 3;
    printf("Ingresa el año de mandato del presidente: ");
    scanf("%d", &anioMandato);
    limpiarBuffer();

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
    struct nodoSenador *nuevoSenador = crearNodoSenador(ciudadano);

    if (ciudadano == NULL) {
        printf("Ciudadano con RUT %s no encontrado.\n", rut);
        return senadores;
    } else if (buscarSenadorPorRUT(senadores, rut) == 1) {
        printf("Senador con RUT %s ya existe en el sistema.\n", ciudadano->rut);
        return senadores;
    } else if (ciudadano->cargo != 0) {
        printf("La persona con RUT %s ya tiene un cargo publico. No puede ser senador\n", ciudadano->rut);
        return senadores;
    }

    ciudadano->cargo = 2;

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
    char tipo[50];
    char tema[50];

    printf("Ingresa el ID de la propuesta: ");
    scanf("%d", &nuevaPropuesta->id);
    limpiarBuffer();

    printf("Ingresa el tipo de propuesta (financiero, tributario, educacion, etc.): ");
    fgets(tipo, sizeof(tipo), stdin);
    tipo[strcspn(tipo, "\n")] = '\0'; // Eliminar el salto de línea
    nuevaPropuesta->tipo = (char *)malloc(strlen(tipo) + 1);
    strcpy(nuevaPropuesta->tipo, tipo);

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
    struct nodoSenador *rec = senadores;
    if (senadores == NULL) {
        printf("No hay senadores en la lista.\n");
        return;
    }

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
    struct propuesta *propuesta = NULL;
    struct nodoDiputado *recDiputados = congreso->diputados;
    struct nodoSenador *recSenadores = congreso->senadores;
    int idPropuesta;
    int votosAFavor = 0, votosEnContra = 0;

    printf("Ingresa el ID de la propuesta a discutir: ");
    scanf("%d", &idPropuesta);
    propuesta = buscarPropuesta(raizPropuestas, idPropuesta);

    // Buscar la propuesta por ID en el ABB
    if (propuesta == NULL) {
        printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
        return;
    }

    // Verificar si el proyecto debe iniciar en la Cámara de Diputados o en el Senado
    if (strcmp(propuesta->tipo, "financiero") == 0 || strcmp(propuesta->tipo, "tributario") == 0) {
        printf("El proyecto de tipo %s debe ser discutido primero en la Camara de Diputados.\n", propuesta->tipo);

        // Simular votación de todos los miembros de la Cámara de Diputados
        if (recDiputados == NULL) {
            printf("No hay diputados disponibles para votar.\n");
            return;
        }

        do {
            printf("El diputado %s vota a favor o en contra de la propuesta? (1 = A favor | Otro numero = En contra)" , recDiputados->headDiputados->nombre);
            scanf("%d", &recDiputados->headDiputados->voto);
            limpiarBuffer();

            if (recDiputados->headDiputados->voto == 1) {
                votosAFavor++;
            } else {
                votosEnContra++;
            }
            recDiputados = recDiputados->sig;
        } while (recDiputados != congreso->diputados);  // Iteración completa de la lista circular de diputados

    } else {
        printf("El proyecto de tipo %s sera discutido en el Senado.\n", propuesta->tipo);

        // Simular votación de todos los miembros del Senado
        if (recSenadores == NULL) {
            printf("No hay senadores disponibles para votar.\n");
            return;
        }

        do {
            printf("El senador %s vota a favor o en contra de la propuesta? (1 = A favor | Otro numero = En contra)" , recSenadores->headSenadores->nombre);
            scanf("%d", &recSenadores->headSenadores->voto);
            limpiarBuffer();
            if (recSenadores->headSenadores->voto == 1) {
                votosAFavor++;
            } else {
                votosEnContra++;
            }
            recSenadores = recSenadores->sig;
        } while (recSenadores != congreso->senadores);  // Iteración completa de la lista circular de senadores
    }

    // Mostrar resultados de la votación
    printf("Resultados de la votacion:\n");
    printf("Votos a favor: %d\n", votosAFavor);
    printf("Votos en contra: %d\n", votosEnContra);

    if (votosAFavor > votosEnContra) {
        printf("La idea de legislar ha sido aprobada. El proyecto avanza a la siguiente etapa.\n");
        propuesta->estado = 0; // En tramite
    } else {
        printf("La idea de legislar ha sido rechazada. El proyecto no avanza.\n");
        propuesta->estado = 2; // Rechazada
    }
    pause();
}

void mostrarPropuesta(struct propuesta *propuesta) {
    if (propuesta == NULL) {
        printf("No se encontro la propuesta con el ID especificado.\n");
    } else {
        printf("\n===== Datos de la Propuesta =====\n");
        printf("ID de la propuesta: %d\n", propuesta->id);
        printf("Tipo: %s\n", propuesta->tipo);
        printf("Tema: %s\n", propuesta->tema);
        printf("Autor: %s\n", propuesta->personaAcargo->nombre);
        if (propuesta->estado == 0) {
            printf("Estado: En tramite\n");
        } else if (propuesta->estado == 1) {
            printf("Estado: Aprobada\n");
        } else if (propuesta->estado == 2) {
            printf("Estado: Rechazada\n");
        }
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
    if (raiz->datos->estado == 0) {
        printf("Estado: En tramite\n");
    } else if (raiz->datos->estado == 1) {
        printf("Estado: Aprobada\n");
    } else if (raiz->datos->estado == 2) {
        printf("Estado: Rechazada\n");
    }
    printf("=================================\n");

    // Recorrido por el lado derecho del árbol
    if (raiz->der != NULL) {
        mostrarPropuestas(raiz->der);
    }
}

struct nodoDiputado *eliminarDiputado(struct nodoDiputado *diputados, char *rut) {
    struct nodoDiputado *rec = diputados;
    if (diputados == NULL) {
        printf("La lista de diputados esta vacia.\n");
        return NULL;
    }


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
    struct nodoSenador *rec = senadores;
    if (senadores == NULL) {
        printf("La lista de senadores esta vacia.\n");
        return NULL;
    }

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
void camaraRevisora(struct nodoPropuestas *raizPropuestas, struct congreso *congreso) {
    struct propuesta *propuesta;
    int idPropuesta;
    int votosAFavor = 0, votosEnContra = 0;
    int modificacion = 0;  // Si la Cámara Revisora propone modificaciones
    printf("Ingresa el ID de la propuesta a discutir en la Camara Revisora: ");
    scanf("%d", &idPropuesta);
    propuesta = buscarPropuesta(raizPropuestas, idPropuesta);
    // Buscar la propuesta por ID en el ABB
    if (propuesta == NULL) {
        printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
        return;
    }

    if (propuesta->estado == 2) {
        printf("La propuesta con ID %d ya ha sido rechazada anteriormente.\n", idPropuesta);
        return;
    }
    printf("La propuesta con ID %d ha llegado a la Camara Revisora.\n", idPropuesta);

    // Lógica de votación en la Cámara Revisora
    if (strcmp(propuesta->tipo, "financiero") == 0 || strcmp(propuesta->tipo, "tributario") == 0) {
        struct nodoSenador *rec = congreso->senadores;
        if (rec != NULL) {
            do {
                printf("El senador %s vota a favor o en contra de la propuesta? (1 = A favor | Otro numero = En contra)" , rec->headSenadores->nombre);
                scanf("%d", &rec->headSenadores->voto);
                limpiarBuffer();

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
                printf("El diputado %s vota a favor o en contra de la propuesta? (1 = A favor | Otro numero = En contra)" , rec->headDiputados->nombre);
                scanf("%d", &rec->headDiputados->voto);
                limpiarBuffer();

                if (rec->headDiputados->voto == 1) {
                    votosAFavor++;
                } else {
                    votosEnContra++;
                }
                rec = rec->sig;
            } while (rec != congreso->diputados);
        }
    }

    printf("Resultados de la votacion en la Cámara Revisora:\n");
    printf("Votos a favor: %d\n", votosAFavor);
    printf("Votos en contra: %d\n", votosEnContra);

    // Resultado en la Cámara Revisora
    if (votosAFavor > votosEnContra) {
        printf("¿La Camara Revisora propone modificaciones? (1 = Sí, Otro Numero = No): ");
        scanf("%d", &modificacion);

        if (modificacion == 1) {
            propuesta->estado = 0; // En tramite
            printf("La Camara Revisora ha propuesto modificaciones. El proyecto vuelve a la Camara de Origen.\n");
        } else {
            propuesta->estado = 0; // En tramite
            printf("La Camara Revisora ha aprobado el proyecto sin cambios. Se envia al Presidente para su promulgacion.\n");
        }
    } else {
        propuesta->estado = 2; // Rechazada
        printf("El proyecto ha sido rechazado en la Camara Revisora. No se promulga.\n");
    }
    pause();
}

/* Función Promulgación y Veto Presidencial */
void promulgacionOVetoPresidencial(struct presidente *presidente, struct nodoPropuestas *raizPropuestas, struct congreso *congreso) {
    int idPropuesta;
    int decisionPresidencial;
    int decisionCongreso;
    struct propuesta *propuesta;

    if (presidente == NULL) {
        printf("No hay un presidente registrado.\n");
        return;
    }

    printf("Ingresa el ID de la propuesta a discutir para promulgacion o veto presidencial: ");
    scanf("%d", &idPropuesta);
    propuesta = buscarPropuesta(raizPropuestas, idPropuesta);
    // Buscar la propuesta por ID en el ABB
    if (propuesta == NULL) {
        printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
        return;
    }

    if(propuesta->estado == 2){
        printf("La propuesta con ID %d ya ha sido rechazada anteriormente.\n", idPropuesta);
        return;
    }

    printf("El presidente %s esta evaluando la propuesta \"%s\" (ID: %d).\n", presidente->persona->nombre, propuesta->tema, propuesta->id);
    printf("¿Cual es la decision del presidente?\n");
    printf("1. Promulgar la ley\n");
    printf("2. Veto total (rechazar todo el proyecto)\n");
    printf("3. Veto parcial (sugerir modificaciones a ciertos articulos)\n");
    printf("Elige una opcion: ");
    scanf("%d", &decisionPresidencial);

    // Decisión presidencial
    if (decisionPresidencial == 1) {
        printf("El presidente %s ha promulgado la propuesta \"%s\" como ley.\n", presidente->persona->nombre, propuesta->tema);
        propuesta->estado = 1; // Aprobada

    }
    else if (decisionPresidencial == 2) {
        printf("El presidente %s ha vetado totalmente la propuesta \"%s\".\n", presidente->persona->nombre, propuesta->tema);
        printf("El proyecto ha sido rechazado por el presidente y no avanzara.\n");
        propuesta->estado = 2; // Rechazada

    }
    else if (decisionPresidencial == 3) {
        printf("El presidente %s ha vetado parcialmente la propuesta \"%s\" y ha sugerido modificaciones.\n", presidente->persona->nombre, propuesta->tema);

        printf("El Congreso debe decidir si acepta las modificaciones.\n");
        printf("1. Aceptar las modificaciones del presidente\n");
        printf("2. Rechazar el veto con una mayoria de dos tercios\n");
        printf("Elige una opcion: ");
        scanf("%d", &decisionCongreso);

        if (decisionCongreso == 1) {
            printf("El Congreso ha aceptado las modificaciones. La ley ha sido promulgada con los cambios sugeridos por el presidente.\n");
            propuesta->estado = 1; // Aprobada

        }
        else if (decisionCongreso == 2) {
            int votosFavor = 0, votosContra = 0, votosTotales = 0;

            struct nodoDiputado *recDiputado = congreso->diputados;
            struct nodoSenador *recSenador = congreso->senadores;

            if (recDiputado != NULL) {
                do {
                    printf("El diputado %s vota a favor (1) o en contra (0) del veto presidencial?: ", recDiputado->headDiputados->nombre);
                    scanf("%d", &recDiputado->headDiputados->voto);
                    limpiarBuffer();

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
                    printf("El senador %s vota a favor (1) o en contra (0) del veto presidencial?: ", recSenador->headSenadores->nombre);
                    scanf("%d", &recSenador->headSenadores->voto);
                    limpiarBuffer();

                    if (recSenador->headSenadores->voto == 1) {
                        votosFavor++;
                    } else {
                        votosContra++;
                    }
                    recSenador = recSenador->sig;
                } while (recSenador != congreso->senadores);
            }

            if ((votosFavor * 3) >= (votosTotales * 2 && votosContra < votosFavor)) {
                printf("El Congreso ha rechazado el veto con una mayoria de dos tercios.\n");
                printf("La propuesta sera promulgada tal como fue aprobada por el Congreso.\n");
                propuesta->estado = 1; // Aprobada
            }
            else {
                printf("El Congreso no logro una mayoría de dos tercios. La propuesta sera modificada segun las sugerencias del presidente.\n");
                propuesta->estado = 1; // Aprobada
            }
        }
        else {
            printf("Opcion no valida.\n");

        }
    }
    else {
        printf("Opcion no válida. El proceso se cancela.\n");

    }
}

void comisionMixta(struct nodoPropuestas *raizPropuestas, struct congreso *congreso) {
    struct propuesta *propuesta = NULL;
    struct nodoDiputado *diputadoRec = congreso->diputados;
    struct nodoSenador *senadorRec = congreso->senadores;

    int idPropuesta;
    int votoDiputado, votoSenador;
    int votosAFavorDiputados = 0, votosEnContraDiputados = 0;
    int votosAFavorSenadores = 0, votosEnContraSenadores = 0;
    int consenso = 0;
    int votosAFavorTotal = 0, votosEnContraTotal = 0;

    printf("Ingresa el ID de la propuesta a enviar a la Comision Mixta: ");
    scanf("%d", &idPropuesta);
    propuesta  = buscarPropuesta(raizPropuestas, idPropuesta);
    limpiarBuffer();  // Para evitar errores al leer entrada

    // Buscar la propuesta por ID en el ABB de propuestas
    if (propuesta == NULL) {
        printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
        return;
    }

    if (propuesta->estado == 2) {
        printf("La propuesta con ID %d ya ha sido rechazada anteriormente.\n", idPropuesta);
        return;
    }

    printf("\n===== Comision Mixta =====\n");
    printf("La propuesta '%s' ha sido enviada a la Comision Mixta para resolver discrepancias.\n", propuesta->tema);

    // Votación de los diputados en la Comisión Mixta
    printf("\nVotacion de los Diputados en la Comision Mixta:\n");
    if (diputadoRec != NULL) {
        do {
            printf("El diputado %s vota a favor (1) o en contra (0) de la propuesta? ", diputadoRec->headDiputados->nombre);
            scanf("%d", &votoDiputado);
            limpiarBuffer();

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
    printf("\nVotacion de los Senadores en la Comision Mixta:\n");
    if (senadorRec != NULL) {
        do {
            printf("El senador %s vota a favor (1) o en contra (0) de la propuesta? ", senadorRec->headSenadores->nombre);
            scanf("%d", &votoSenador);
            limpiarBuffer();

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
        printf("\nLa Comision Mixta ha alcanzado un consenso. El informe sera enviado a ambas camaras para su votacion.\n");
    } else {
        propuesta->estado = 2; // Rechazada
        printf("\nNo se alcanzo un consenso en la Comision Mixta. El proyecto ha sido rechazado.\n");
    }

    // Si hay consenso, se procede a enviar el informe a ambas cámaras
    if (consenso) {
        printf("\nEl proyecto se envia a ambas camaras para su votacion final...\n");

        votosAFavorTotal = votosAFavorDiputados + votosAFavorSenadores;
        votosEnContraTotal = votosEnContraDiputados + votosEnContraSenadores;

        // Mostrar el resultado final de la votación combinada
        printf("Votos totales a favor: %d\n", votosAFavorTotal);
        printf("Votos totales en contra: %d\n", votosEnContraTotal);

        if (votosAFavorTotal > votosEnContraTotal) {
            printf("El proyecto ha sido aprobado por ambas camaras tras el consenso en la Comision Mixta.\n");
            propuesta->estado = 0; // En tramite
        } else {
            printf("El proyecto ha sido rechazado por ambas camaras tras la votacion final.\n");
            propuesta->estado = 2; // Rechazada
        }
    }
}
// Función para crear un nuevo boletín
struct nodoBoletin *crearBoletin(struct propuesta *propuesta, char *fechaVigencia, int numeroBoletin) {
    struct nodoBoletin *nuevoBoletin = (struct nodoBoletin *)malloc(sizeof(struct nodoBoletin));
    struct boletin *nuevoBoletinHead = (struct boletin *)malloc(sizeof(struct boletin));

    nuevoBoletinHead->propuesta = propuesta;
    nuevoBoletinHead->numeroBoletin = numeroBoletin;

    // Asignar fecha de publicación
    nuevoBoletinHead->fechaVigencia = (char *)malloc(strlen(fechaVigencia) + 1);
    strcpy(nuevoBoletinHead->fechaVigencia, fechaVigencia);

    nuevoBoletin->head = nuevoBoletinHead;
    nuevoBoletin->sig = NULL;

    return nuevoBoletin;
}

struct nodoBoletin* eliminarLeyDeBoletin(struct nodoBoletin *boletinEstado, int numeroBoletin) {
    struct nodoBoletin *rec = boletinEstado;
    struct nodoBoletin *temp = NULL;

    if (boletinEstado == NULL) {
        printf("No hay boletines en el sistema.\n");
        return NULL;
    }

    while (rec != NULL) {
        if (rec->head->numeroBoletin == numeroBoletin) {
            if (rec == boletinEstado) { // si es el primer boletín
                temp = rec->sig;
                rec->head->fechaVigencia = NULL;
                rec->head = NULL;
                rec = NULL;
                printf("Boletin con numero %d eliminado.\n", numeroBoletin);
                return temp;
            } else {
                temp->sig = rec->sig;
                rec->head->fechaVigencia = NULL;
                rec->head = NULL;
                rec = NULL;
                printf("Boletin con numero %d eliminado.\n", numeroBoletin);
                return boletinEstado;
            }
        }
        temp = rec;
        rec = rec->sig;
    }

    printf("Boletin con numero %d no encontrado.\n", numeroBoletin);
    return boletinEstado;
}

// Función para publicar una ley en el boletín y establecer su fecha de entrada en vigencia
struct nodoBoletin* publicarLeyEnBoletin(struct nodoBoletin *boletinEstado, struct propuesta *propuesta) {
    struct nodoBoletin *nuevoBoletin = NULL;
    char fechaPublicacion[20];
    char fechaVigencia[20];
    int entradaInmediata = 0;
    int numeroBoletin = 1;  // Contador de boletines

    // Solicitar fecha de publicación
    printf("Ingresa la fecha de publicacion (dd/mm/yyyy) para la ley '%s': ", propuesta->tema);
    fgets(fechaPublicacion, sizeof(fechaPublicacion), stdin);
    fechaPublicacion[strcspn(fechaPublicacion, "\n")] = '\0';  // Eliminar el salto de línea

    // Preguntar si la ley entra en vigencia de manera inmediata
    printf("Ley '%s' promulgada. ¿La ley entra en vigencia de manera inmediata? (1 = Sí, 0 = No): ", propuesta->tema);
    scanf("%d", &entradaInmediata);
    limpiarBuffer();  // Para evitar problemas con fgets después de scanf

    if (entradaInmediata == 1) {
        strcpy(fechaVigencia, fechaPublicacion);  // Vigencia inmediata
    } else {
        printf("Ingresa la fecha de entrada en vigencia (dd/mm/yyyy): ");
        fgets(fechaVigencia, sizeof(fechaVigencia), stdin);
        fechaVigencia[strcspn(fechaVigencia, "\n")] = '\0';  // Eliminar el salto de línea
    }

    // Crear el nuevo boletín
    nuevoBoletin = crearBoletin(propuesta, fechaVigencia, numeroBoletin);

    // Agregar el boletín al final de la lista
    if (boletinEstado == NULL) {
        boletinEstado = nuevoBoletin;
    } else {
        struct nodoBoletin *temp = boletinEstado;
        while (temp->sig != NULL) {
            temp = temp->sig;
        }
        temp->sig = nuevoBoletin;
    }

    printf("La ley '%s' ha sido publicada en el Diario Oficial bajo el Boletin N°%d y entrara en vigencia el %s.\n",
            propuesta->tema, nuevoBoletin->head->numeroBoletin, fechaVigencia);

    return boletinEstado;
}

void poblarTribunalConstitucional(struct persona tribunalConstitucional[10]) {
    for (int i = 0; i < 10; i++) {
        tribunalConstitucional[i].edad = 0;
    }
}

void agregarMinistroTribunalConstitucional(struct persona tribunalConstitucional[], struct nodoCiudadano *ciudadanos, char rut[20]) {
    struct persona *ministro = buscarCiudadanoPorRUT(ciudadanos, rut);
    int i;

    if(ministro == NULL) {
        printf("No se encontro un ciudadano con el RUT %s.\n", rut);
        return;
    }

    else if (ministro->cargo == 4) {
        printf("El ciudadano con RUT %s ya es ministro del Tribunal Constitucional.\n", rut);
        return;
    }
    else if (ministro->cargo != 0) {
        printf("El ciudadano con RUT %s ya tiene un cargo publico. No puede ser ministro del Tribunal Constitucional.\n", rut);
        return;
    }

    for (i = 0; i < 10; i++) {
        if (tribunalConstitucional[i].edad == 0) {
            strcpy(tribunalConstitucional[i].rut, ministro->rut);
            strcpy(tribunalConstitucional[i].nombre, ministro->nombre);
            tribunalConstitucional[i].edad = ministro->edad;
            strcpy(tribunalConstitucional[i].especialidad, ministro->especialidad);
            tribunalConstitucional[i].cargo = 4;
            ministro->cargo = 4;
            printf("Ministro del Tribunal Constitucional agregado correctamente.\n");
            return;
        }
    }
    printf ("No se pueden agregar más de 10 ministros del Tribunal Constitucional.\n");
}

void eliminarMinistroTribunalConstitucional(struct persona tribunalConstitucional[10], struct nodoCiudadano *ciudadanos, char rut[20]) {
    struct persona *ciudadano = buscarCiudadanoPorRUT(ciudadanos, rut);
    int i;

    if (ciudadano == NULL) {
        printf("No se encontro un ciudadano con el RUT %s.\n", rut);
        return;
    }

    for (i = 0; i < 10; i++) {
        if (strcmp(tribunalConstitucional[i].rut, rut) == 0) {
            tribunalConstitucional[i].edad = 0;
            strcpy(tribunalConstitucional[i].rut, "");
            strcpy(tribunalConstitucional[i].nombre, "");
            strcpy(tribunalConstitucional[i].especialidad, "");
            tribunalConstitucional[i].cargo = 0;
            ciudadano->cargo = 0;
            printf("Ministro del Tribunal Constitucional eliminado correctamente.\n");
            return;
        }
    }
    printf("No se encontro un ministro del Tribunal Constitucional con el RUT %s.\n", rut);
}

void mostrarTribunalConstitucional(struct persona tribunalConstitucional[10]) {
    int i, encontrado = 0;

    for (i = 0; i < 10; i++) {
        if (tribunalConstitucional[i].edad != 0) {
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("No hay ministros del Tribunal Constitucional registrados.\n");
        return;
    }

    for (i = 0; i < 10; i++) {
        if (tribunalConstitucional[i].edad != 0) {
            printf("\nNombre: %s\n", tribunalConstitucional[i].nombre);
            printf("Edad: %d\n", tribunalConstitucional[i].edad);
            printf("RUT: %s\n", tribunalConstitucional[i].rut);
            printf("Cargo: Ministro del Tribunal Constitucional\n");
            printf("Especialidad: %s\n\n", tribunalConstitucional[i].especialidad);
        }
    }
}

int verificarTC(struct persona tribunalConstitucional[10]) {
    int i;
    for (i = 0; i < 10; i++) {
        if (tribunalConstitucional->cargo == 0) {
            return 0; // no hay sufiicientes ministros
        }
    }
    return 1; // hay suficientes ministros
}

int realizarVotacionMinistros(struct persona tribunalConstitucional[10]) {
    int votosAFavor = 0, votosEnContra = 0;
    int i, voto;

    for (i = 0; i < 10; i++) {
        if (tribunalConstitucional[i].edad != 0) {
            printf("Ministro %s, ¿Aprueba la propuesta? (1 = Sí, Otro número = No): ", tribunalConstitucional[i].nombre);
            scanf("%d", &voto);
            if (voto == 1) {
                votosAFavor++;
            } else {
                votosEnContra++;
            }
        }
    }

    printf("Votos a favor: %d\n", votosAFavor);
    printf("Votos en contra: %d\n", votosEnContra);

    if (votosAFavor > votosEnContra) {
        return 1;  // Propuesta aprobada por el Tribunal Constitucional
    } else {
        return 0;  // Propuesta rechazada por el Tribunal Constitucional
    }
}

int controlConstitucionalidad(struct nodoBoletin *boletinEstado, struct propuesta *propuesta, struct persona tribunalConstitucional[10]) {
    struct nodoBoletin *rec = boletinEstado;
    int votacionMinistros = 0;

    while (rec != NULL) {
        if (rec->head->propuesta->id == propuesta->id) {
            printf("La propuesta ha sido publicada en el Boletin N°%d", rec->head->numeroBoletin);
            // Realizar votacion de los ministros del Tribunal Constitucional
            votacionMinistros = realizarVotacionMinistros(tribunalConstitucional);
            if (votacionMinistros) {
                printf("La propuesta ha sido aprobada por el Tribunal Constitucional.\n");
                return 1;  // Propuesta aprobada por el Tribunal Constitucional
            } else {
                printf("La propuesta ha sido rechazada por el Tribunal Constitucional.\n");
                propuesta->estado = 2; // Rechazada
                return 2;  // Propuesta rechazada por el Tribunal Constitucional
            }
        }
        rec = rec->sig;
    }
    printf("La propuesta no ha sido encontrada en el boletin oficial.\n");
    return 0;  // Propuesta no encontrada en el boletín
}

void mostrarPromedioEdadCiudadanos(struct nodoCiudadano *ciudadanos) {
    struct nodoCiudadano *rec = ciudadanos;
    int cantidadCiudadanos = 0;
    int cantidadSobrePromedio = 0;
    int sumaEdades = 0;
    float promedioEdad;

    if (rec == NULL) {
        printf("No hay ciudadanos registrados.\n");
        return;
    }

    // Calcular suma de edades y cantidad de ciudadanos
    while (rec != NULL) {
        if (rec->datos != NULL) {
            sumaEdades += rec->datos->edad;
            cantidadCiudadanos++;
        }
        rec = rec->sig;
    }

    if (cantidadCiudadanos == 0) {
        printf("No hay ciudadanos con edad registrada.\n");
        return;
    }

    promedioEdad = (float)sumaEdades / cantidadCiudadanos;

    rec = ciudadanos;
    while (rec != NULL) {
        if (rec->datos != NULL && rec->datos->edad > promedioEdad) {
            cantidadSobrePromedio++;
        }
        rec = rec->sig;
    }

    printf("\nPromedio de edad: %.2f\n", promedioEdad);
    printf("Cantidad de ciudadanos: %d\n", cantidadCiudadanos);
    printf("Porcentaje de ciudadanos sobre el promedio de edad: %.2f%%\n", (float)cantidadSobrePromedio / cantidadCiudadanos * 100);
}

int contarPropuestas(struct nodoPropuestas *raizPropuestas) {
    if (raizPropuestas == NULL) {
        return 0;
    }
    return 1 + contarPropuestas(raizPropuestas->izq) + contarPropuestas(raizPropuestas->der);
}

int contarPropuestasAprobadas(struct nodoPropuestas *raizPropuestas) {
    if (raizPropuestas == NULL) {
        return 0;
    }

    if (raizPropuestas->datos != NULL && raizPropuestas->datos->estado == 1) {
        return 1 + contarPropuestasAprobadas(raizPropuestas->izq) + contarPropuestasAprobadas(raizPropuestas->der);
    } else {
        return contarPropuestasAprobadas(raizPropuestas->izq) + contarPropuestasAprobadas(raizPropuestas->der);
    }
}

void mostrarPorcentajeProyectosAprobados(struct nodoPropuestas *raizPropuestas) {
    int cantidadPropuestas = contarPropuestas(raizPropuestas);
    int cantidadAprobadas = contarPropuestasAprobadas(raizPropuestas);

    if (cantidadPropuestas == 0) {
        printf("\nNo hay propuestas registradas.\n");
        return;
    }

    float porcentajeAprobadas = ((float)cantidadAprobadas / cantidadPropuestas) * 100;
    printf("\nPorcentaje de propuestas aprobadas: %.2f%%\n", porcentajeAprobadas);
    printf("Cantidad de propuestas: %d\n", cantidadPropuestas);
    printf("Cantidad de propuestas aprobadas: %d\n", cantidadAprobadas);
}

void mostrarMenu() {
    printf("\n===== Menu =====\n");
    printf("1. Crear Ciudadano\n");
    printf("2. Mostrar Ciudadanos\n");
    printf("\n");
    printf("3. Agregar Diputado\n");
    printf("4. Mostrar Diputados\n");
    printf("5. Eliminar Diputado\n");
    printf("\n");
    printf("6. Agregar Senador\n");
    printf("7. Mostrar Senadores\n");
    printf("8. Eliminar Senador\n");
    printf("\n");
    printf("9. Agregar Presidente\n");
    printf("10. Mostrar Presidente\n");
    printf("\n");
    printf("11. Crear Propuesta\n");
    printf("12. Mostrar Propuesta por ID\n");
    printf("13. Mostrar Todas las Propuestas\n");
    printf("\n");
    printf("14. Iniciar Camara de Origen\n");
    printf("15. Iniciar Camara Revisora\n");
    printf("16. Comision Mixta\n");
    printf("\n");
    printf("17. Promulgacion o Veto Presidencial\n");
    printf("\n");
    printf("18. Publicar Ley en Boletin y Establecer Vigencia\n");
    printf("19. Eliminar Ley de Boletin\n");
    printf("\n");
    printf("20. Agregar Ministro a Tribunal Constitucional\n");
    printf("21. Eliminar Ministro del Tribunal Constitucional\n");
    printf("22. Mostrar Ministros del Tribunal Constitucional\n");
    printf("23. Realizar Control de Constitucionalidad a un Proyecto\n");
    printf("\n");
    printf("24. Mostrar promedio de edad de los ciudadanos\n");
    printf("25. Mostrar porcentaje de proyectos aprobadados por el Tribunal Constitucional\n");
    printf("\n");
    printf("26. Salir\n");
    printf("================\n");
}

/*LINEAS ARREGLAR: 1245, 1274, 1342, 1362*/ // dios sabrá que hay que arreglar ahora
int main() {
    struct ProcesoLegislativo *procesoLegislativo;
    procesoLegislativo = (struct ProcesoLegislativo *)malloc(sizeof(struct ProcesoLegislativo));

    procesoLegislativo->congreso = NULL;
    procesoLegislativo->propuesta = NULL; // arbol de propuestas
    procesoLegislativo->ciudadanos = NULL;
    procesoLegislativo->presidente = NULL;
    procesoLegislativo->boletinEstado = NULL; // lista de boletines

    struct persona *personaPresidente = NULL;
    struct propuesta *propuestaEncontrada = NULL;
    struct propuesta *propuesta = NULL;

    int opcion;
    char rut[20];  // Cambiado a array estático
    int salir = 0;
    int idPropuesta;

    // Inicializa el congreso y le asigna memoria, si falla retorna 1
    procesoLegislativo->congreso = (struct congreso *)malloc(sizeof(struct congreso));
    if (procesoLegislativo->congreso == NULL) {
        printf("Error al asignar memoria para la estructura congreso.\n");
        return 1;
    }

    procesoLegislativo->congreso->diputados = NULL;  // Inicializando en NULL para evitar acceso a memoria no válida
    procesoLegislativo->congreso->senadores = NULL;

    poblarTribunalConstitucional(procesoLegislativo->tribunalConstitucional);

    do {
        cls();
        mostrarMenu();
        printf("Elige una opcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        if (opcion == 1) {
            // Crear Ciudadano
            struct persona *ciudadano = crearCiudadano();
            procesoLegislativo->ciudadanos = agregarCiudadano(procesoLegislativo->ciudadanos, ciudadano);
            pause();

        } else if (opcion == 2) {
            // Mostrar Ciudadanos
            mostrarCiudadanos(procesoLegislativo->ciudadanos);
            pause();

        } else if (opcion == 3) {
            // Agregar Diputado
            printf("Ingresa el RUT del ciudadano a agregar como diputado: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            procesoLegislativo->congreso->diputados = agregarDiputado(procesoLegislativo->congreso->diputados, procesoLegislativo->ciudadanos, rut);  // Modificar correctamente la lista de diputados
            pause();

        } else if (opcion == 4) {
            // Mostrar Diputados
            mostrarDiputados(procesoLegislativo->congreso->diputados);
            pause();

        } else if (opcion == 5) {
            // Eliminar Diputado
            printf("Ingresa el RUT del diputado a eliminar: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            procesoLegislativo->congreso->diputados = eliminarDiputado(procesoLegislativo->congreso->diputados, rut);  // Modificar correctamente la lista de diputados
            pause();

        } else if (opcion == 6) {
            // Agregar Senador
            printf("Ingresa el RUT del ciudadano a agregar como senador: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            procesoLegislativo->congreso->senadores = agregarSenador(procesoLegislativo->congreso->senadores, procesoLegislativo->ciudadanos, rut);
            pause();

        } else if (opcion == 7) {
            // Mostrar Senadores
            mostrarSenadores(procesoLegislativo->congreso->senadores);
            pause();

        } else if (opcion == 8) {
            // Eliminar Senador
            printf("Ingresa el RUT del senador a eliminar: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            procesoLegislativo->congreso->senadores = eliminarSenador(procesoLegislativo->congreso->senadores, rut);  // Modificar correctamente la lista de senadores
            pause();

        } else if (opcion == 9) {
            // Agregar Presidente
            printf("Ingresa el RUT del presidente: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            /*holaamigos de youtube arreglar*/
            personaPresidente = buscarCiudadanoPorRUT(procesoLegislativo->ciudadanos, rut);
            if (personaPresidente == NULL) {
                printf("El ciudadano con RUT %s no existe.\n", rut);
            } else {
                procesoLegislativo->presidente = crearPresidente(personaPresidente);  // Asignamos al presidente
            }
            pause();

        } else if (opcion == 10) {
            // Mostrar Presidente
            mostrarPresidente(procesoLegislativo->presidente);
            pause();

        } else if (opcion == 11) {
            // Crear Propuesta y agregarla al ABB
            if (procesoLegislativo->presidente == NULL) {
                printf("Primero debes agregar un presidente para asignar una propuesta.\n");
            } else {
                procesoLegislativo->propuesta = crearPropuesta(procesoLegislativo->propuesta, procesoLegislativo->presidente->persona);
            }
            pause();

        } else if (opcion == 12) {
            // Mostrar Propuesta por ID
            printf("Ingresa el ID de la propuesta a buscar: ");
            scanf("%d", &idPropuesta);
            limpiarBuffer();

            propuestaEncontrada = buscarPropuesta(procesoLegislativo->propuesta, idPropuesta);
            mostrarPropuesta(propuestaEncontrada);  // Esta función ya maneja el caso si la propuesta es NULL
            pause();

        } else if (opcion == 13) {
            // Mostrar todas las propuestas
            mostrarPropuestas(procesoLegislativo->propuesta);
            pause();

        } else if (opcion == 14) {
            // Iniciar Cámara de Origen
            if (procesoLegislativo->propuesta == NULL) {
                printf("Primero debes crear una propuesta para iniciar la Camara de Origen.\n");
            } else {
                camaraDeOrigen(procesoLegislativo->propuesta, procesoLegislativo->congreso);  // Asegurarse de pasar la estructura congreso correctamente
            }
            pause();

        } else if (opcion == 15) {
            // Iniciar Cámara Revisora
            if (procesoLegislativo->propuesta == NULL) {
                printf("Primero debes crear una propuesta para iniciar la Camara Revisora.\n");
            } else {
                camaraRevisora(procesoLegislativo->propuesta, procesoLegislativo->congreso);  // Asegurarse de pasar la estructura congreso correctamente
            }
            pause();

        } else if (opcion == 16) {
            // Comisión Mixta
            if (procesoLegislativo->propuesta == NULL) {
                printf("Primero debes crear una propuesta para enviar a la Comision Mixta.\n");
            } else {
                comisionMixta(procesoLegislativo->propuesta, procesoLegislativo->congreso);  // Asegurarse de pasar la estructura congreso correctamente
            }
            pause();

        } else if (opcion == 17) {
            // Promulgación o Veto Presidencial
            if (procesoLegislativo->presidente == NULL || procesoLegislativo->propuesta == NULL) {
                printf("Se necesita tanto un presidente como una propuesta para proceder con la promulgacion o veto.\n");
            } else {
                promulgacionOVetoPresidencial(procesoLegislativo->presidente, procesoLegislativo->propuesta, procesoLegislativo->congreso);  // Asegurarse de pasar la estructura congreso correctamente
            }
            pause();

        } else if (opcion == 18) {
            // Publicar Ley en Boletín y Establecer Vigencia

            printf("Ingresa el ID de la propuesta a publicar: ");
            scanf("%d", &idPropuesta);
            limpiarBuffer();  // Limpiar el buffer

            propuesta = buscarPropuesta(procesoLegislativo->propuesta, idPropuesta);
            if (propuesta == NULL) {
                printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
            } else {
                procesoLegislativo->boletinEstado = publicarLeyEnBoletin(procesoLegislativo->boletinEstado, propuesta);
            }
            pause();

        } else if (opcion == 19) {
            // Eliminar Ley de Boletín
            int numeroBoletin;
            printf("Ingresa el numero de boletin a eliminar: ");
            scanf("%d", &numeroBoletin);
            procesoLegislativo->boletinEstado = eliminarLeyDeBoletin(procesoLegislativo->boletinEstado, numeroBoletin);
            pause();

        } else if (opcion == 20) {
            // Agregar Ministro a Tribunal Constitucional
            printf("Ingresa el RUT del ciudadano a agregar como ministro del tribunal constitucional: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            agregarMinistroTribunalConstitucional(procesoLegislativo->tribunalConstitucional, procesoLegislativo->ciudadanos, rut);
            pause();

        } else if (opcion == 21) {
            // Eliminar Ministro del Tribunal Constitucional
            printf("Ingresa el RUT del ministro a eliminar del tribunal constitucional: ");
            fgets(rut, sizeof(rut), stdin);
            rut[strcspn(rut, "\n")] = '\0';
            eliminarMinistroTribunalConstitucional(procesoLegislativo->tribunalConstitucional, procesoLegislativo->ciudadanos, rut);
            pause();

        } else if (opcion == 22) {
            // Mostrar Ministros del Tribunal Constitucional
            mostrarTribunalConstitucional(procesoLegislativo->tribunalConstitucional);
            pause();

        } else if (opcion == 23) {
            // Control de Constitucionalidad
            int hayMinistros;
            hayMinistros = verificarTC(procesoLegislativo->tribunalConstitucional);

            if (hayMinistros == 0) {
                printf("No hay suficientes ministros en el tribunal constitucional para realizar el control de constitucionalidad.\n");
            } else { // si alguien modulariza esto seria un golazo
                printf("Ingresa el ID de la propuesta a verificar en el boletin: ");
                scanf("%d", &idPropuesta);
                limpiarBuffer();

                propuesta = buscarPropuesta(procesoLegislativo->propuesta, idPropuesta);
                int esConstitucional;
                if (propuesta == NULL) {
                    printf("Propuesta con ID %d no encontrada.\n", idPropuesta);
                } else {
                    esConstitucional = controlConstitucionalidad(procesoLegislativo->boletinEstado, propuesta, procesoLegislativo->tribunalConstitucional);
                    if (esConstitucional == 0) {
                        printf("La propuesta '%s' aun no se ha publicado en el boletin del estado.\n", propuesta->tema);
                    } else if (esConstitucional == 2) {
                        printf("La propuesta '%s' no es constitucional. ", propuesta->tema);
                        eliminarLeyDeBoletin(procesoLegislativo->boletinEstado, propuesta->id);
                    } else {
                        printf("La propuesta '%s' es constitucional y se mantiene en el boletin del estado\n", propuesta->tema);
                    }
                }
            }
            pause();

        } else if (opcion == 24) {
            // Mostrar promedio de edad de los ciudadanos
            mostrarPromedioEdadCiudadanos(procesoLegislativo->ciudadanos);
            pause();

        } else if (opcion == 25) {
            // Mostrar porcentaje de proyectos aprobados por el Tribunal Constitucional
            mostrarPorcentajeProyectosAprobados(procesoLegislativo->propuesta);
            pause();

        } else if (opcion == 26) {
            printf("Saliendo del programa...\n");
            salir = 1;
            pause();

        } else {
            printf("Opcion no valida. Por favor, intenta de nuevo.\n");
            pause();
        }
    } while (!salir);

    return 0;
}
