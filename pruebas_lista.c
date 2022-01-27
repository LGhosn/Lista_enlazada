#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

/**************************FUNCIONES AUXILIARES****************************/
// COMPARACION DE CADENAS 
bool comparar_cadena(char cadena1[], char cadena2[], int len){
    for (int i = 0; i < len; i++){
        if (cadena1[i] != cadena2[i]){
            return false;
        }
    }
    return true;
}

//WRAPPER PARA DESTRUIR PILAS
void destruir_wrapper(void *elem){
    pila_destruir(elem);
}

// 'VISITAR' PARA EL ITERADOR INTERNO
bool sumar_todos(void *dato, void *extra){
    *(int*) extra += *(int*) dato;
    return true;
}

bool imprimir_todos(void *dato, void *extra){
    printf("El elemento es %d\n", *(int*) dato);
    return true;
}
/**************************************************************************/

static void prueba_lista_vacia(void){
    lista_t *lista = lista_crear();

    /*  La lista esta vacia  */
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    print_test("No hay primero", lista_ver_primero(lista) == NULL);
    print_test("No hay ultimo", lista_ver_ultimo(lista) == NULL);
    print_test("Borrar devuevle NULL por estar vacia", lista_borrar_primero(lista) == NULL);
    print_test("El largo es 0", lista_largo(lista) == 0);

    /*  La lista no esta vacia */
    int nueve = 9;
    lista_insertar_primero(lista, &nueve);
    print_test("Agrego un elemento y deja de estar vacia", !lista_esta_vacia(lista));

    lista_destruir(lista, NULL);    
}

static void prueba_algunos_elementos(void){
    lista_t *lista = lista_crear();

    int numeros[] = {3, 2, 1};
    char cadena_1[] = "algoritmos";
    int len_1 = 10;
    char cadena_2[] = "programacion";
    int len_2 = 12;

    /*  Pruebo que se agregan los elementos  */
    print_test("Se agrega el numero 3 al principio", lista_insertar_primero(lista, &numeros[0]));
    print_test("Se agrega 'algoritmos' al principio", lista_insertar_primero(lista, &cadena_1));
    print_test("Se agrega el numero 2 al final", lista_insertar_ultimo(lista, &numeros[1]));
    print_test("Se agrega el numero 1 al final", lista_insertar_ultimo(lista, &numeros[2]));
    print_test("agregar NULL es valido al principio", lista_insertar_primero(lista, NULL));
    print_test("Se agrega 'programacion' al final", lista_insertar_ultimo(lista, &cadena_2));

    printf("Compruebo invariantes\n");
    print_test("El primero es NULl", lista_ver_primero(lista) == NULL);

    char *ver_cadena = lista_ver_ultimo(lista);
    print_test("El ultimo es 'programacion'", comparar_cadena(ver_cadena, cadena_2, len_2));

    print_test("El largo de la lista es 6", lista_largo(lista) == 6);

    printf("Comienzo a sacar elementos\n");
    print_test("Sacar el primero devuelve el elemento NULL", lista_borrar_primero(lista) == NULL);
    print_test("Ahora el largo de la lista es 5", lista_largo(lista) == 5);

    ver_cadena = lista_ver_primero(lista);
    print_test("Ahora el primero es 'algoritmos'", comparar_cadena(ver_cadena, cadena_1, len_1));

    char *primero_cadena = lista_borrar_primero(lista);
    print_test("Sacar devuelve 'algoritmos'", comparar_cadena(primero_cadena, cadena_1, len_1));
    print_test("Ahora el largo de la lista es 4", lista_largo(lista) == 4);

    int *ver_entero = lista_ver_primero(lista);
    print_test("Ahora el primero es 3", *ver_entero == numeros[0]);

    int *primero_entero = lista_borrar_primero(lista);
    print_test("Sacar devuelve 3", *primero_entero == numeros[0]);
    print_test("Ahora el largo de la lista es 3", lista_largo(lista) == 3);

    ver_entero = lista_ver_primero(lista);
    print_test("Ahora el primero es 2", *ver_entero == numeros[1]);

    primero_entero = lista_borrar_primero(lista);
    print_test("Sacar devuelve 2", *primero_entero == numeros[1]);
    print_test("Ahora el largo de la lista es 2", lista_largo(lista) == 2);

    ver_entero = lista_ver_primero(lista);
    print_test("Ahora el primero es 1", *ver_entero == numeros[2]);

    primero_entero = lista_borrar_primero(lista);
    print_test("Sacar devuelve 1", *primero_entero == numeros[2]);
    print_test("Ahora el largo de la lista es 1", lista_largo(lista) == 1);

    ver_cadena = lista_ver_primero(lista);
    print_test("Ahora el primero es 'programacion'", comparar_cadena(ver_cadena, cadena_2, len_2));

    primero_cadena = lista_borrar_primero(lista);
    print_test("Sacar devuelve 'programacion'", comparar_cadena(primero_cadena, cadena_2, len_2));
    print_test("Ahora el largo de la lista es 0", lista_largo(lista) == 0);
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    print_test("No hay primero", lista_ver_primero(lista) == NULL);
    print_test("No hay ultimo", lista_ver_ultimo(lista) == NULL);

    printf("Pruebo agregando el primer elemento al final\n");
    print_test("La lista esta vacia y agrego al final", lista_insertar_ultimo(lista, &numeros[0]));
    ver_entero = lista_ver_primero(lista);
    print_test("El primero es 3", *ver_entero == numeros[0]);

    lista_destruir(lista, NULL);
}

static void prueba_dinamismo(void){
    lista_t *lista = lista_crear();

    /*  Creo un vector de 1000 elementos diferentes  */
    int numeros[1000];
    for (int i = 0; i < 1000; i++){
        numeros[i] = i;
    }

    printf("Encolo mil elementos\n");
    /*  Encolo todos los elementos  */
    for (int j = 0; j < 1000; j++){
        lista_insertar_ultimo(lista, &numeros[j]);
    }

    int *primero;
    int *desencolar;
    for (int r = 0; r < 1000; r++){
        printf("El primero es %i\n", r);
        primero = lista_ver_primero(lista);
        print_test("Primero correcto", *primero == numeros[r]);

        printf("Se desencola %i\n", r);
        desencolar = lista_borrar_primero(lista);
        print_test("Desapilado correcto", *desencolar == numeros[r]);
    }
    print_test("La lista esta nuevamente vacia", lista_esta_vacia(lista));

    lista_destruir(lista, NULL);
}

static void prueba_destruir(void){
    lista_t *lista = lista_crear();

    int volumen_datos = 10;
    int *numeros = malloc(volumen_datos * sizeof(int));
    char *cadena = malloc((volumen_datos - 2) * sizeof(char));
    
    /*  Iniializo la cadena  */
    cadena[0] = 'p';
    cadena[1] = 'r';
    cadena[2] = 'o';
    cadena[3] = 'g';
    cadena[4] = 'r';
    cadena[5] = 'a';
    cadena[6] = 'm';
    cadena[7] = 'a';

    /*  Guardo elementos en el arreglo de numeros  */
    for (int i = 0; i < 10; i++){
        numeros[i] = i;
    }

    printf("Pruebo con elementos guardados en memoria dinamica\n");

    /*  Inserto los elementos  */
    print_test("Inserto el arreglo de enteros", lista_insertar_ultimo(lista, numeros));
    print_test("Inserto la cadena", lista_insertar_ultimo(lista, cadena));

    int *primero_entero = lista_ver_primero(lista);
    print_test("El primero es el arreglo de numeros", *primero_entero == numeros[0]);

    printf("Destruyo la lista y paso 'free' por paramatro para que se destruya todo\n");

    lista_destruir(lista, free);

    /*  Pruebas insertando otro tipo de tda */
    lista_t *lista_2 = lista_crear();

    pila_t *pila_1 = pila_crear(); // creo una pila para encolarla
    pila_t *pila_2 = pila_crear(); // creo otra pila para encolarla

    int numeros_2[] = {1,2,3,4};
    pila_apilar(pila_1, &numeros_2[0]);
    pila_apilar(pila_1, &numeros_2[2]);
    pila_apilar(pila_2, &numeros_2[1]);
    pila_apilar(pila_2, &numeros_2[3]);

    printf("Pruebas insertando pilas\n");
    print_test("Inserto una pila", lista_insertar_ultimo(lista_2, pila_1));
    print_test("Inserto otra pila", lista_insertar_ultimo(lista_2, pila_2));

    printf("Destruyo la lista y paso el wrapper por parametro para que se destruyan las pilas\n");

    lista_destruir(lista_2, destruir_wrapper);
}

static void prueba_iterador_externo(void){
    lista_t *lista = lista_crear();

    int numeros[] = {1,2,3,4,5};
    lista_insertar_primero(lista, &numeros[3]);
    lista_insertar_primero(lista, &numeros[2]);
    lista_insertar_primero(lista, &numeros[1]);
    lista_insertar_primero(lista, &numeros[0]);

    printf("Inicializo una lista con algunos elementos y creo el iterador\n");
    lista_iter_t *iterador = lista_iter_crear(lista);

    print_test("El actual del iterador es primero de la lista", lista_iter_ver_actual(iterador) == lista_ver_primero(lista));
    print_test("El iterador no esta en el final de la lista", !lista_iter_al_final(iterador));
    print_test("Avanzo el iterador", lista_iter_avanzar(iterador));
    
    int *ver_actual = lista_iter_ver_actual(iterador);
    print_test("El nuevo actual es el segundo elemento", *ver_actual == numeros[1]);
    print_test("Avanzo el iterador", lista_iter_avanzar(iterador));

    ver_actual = lista_iter_ver_actual(iterador);
    print_test("El nuevo actual es el tercer elemento", *ver_actual == numeros[2]);
    print_test("Avanzo el iterador", lista_iter_avanzar(iterador));

    ver_actual = lista_iter_ver_actual(iterador);
    print_test("El nuevo actual es el tercer elemento", *ver_actual == numeros[3]);
    print_test("Avanzo el iterador", lista_iter_avanzar(iterador));

    print_test("El iterador esta al final de la lista", lista_iter_al_final(iterador));
    print_test("Avanzar devuelve false por estar al final del iterador", lista_iter_avanzar(iterador) == false);
    print_test("Ver el actual devuelve NULL por estar al final", lista_iter_ver_actual(iterador) == NULL);

    lista_iter_destruir(iterador);

    printf("Creo otro iterador para para probar insertar y borrar\n");
    lista_iter_t *iterador_2 = lista_iter_crear(lista);

    print_test("Se puede agregar un elemento al principio de todo", lista_iter_insertar(iterador_2, &numeros[4]));
    print_test("Ahora el primero es el agregado en el paso anterior", lista_iter_ver_actual(iterador_2) == lista_ver_primero(lista));

    int *elem_borrado = lista_iter_borrar(iterador_2);
    print_test("Se puede borrar el primer elemento de la lista y lo devuelve", *elem_borrado == numeros[4]);

    lista_iter_avanzar(iterador_2);
    lista_iter_avanzar(iterador_2);

    print_test("Se puede agregar elementos en cualquier posicion", lista_iter_insertar(iterador_2, &numeros[4]));

    ver_actual = lista_iter_ver_actual(iterador_2);
    print_test("Ahora el actual es el agregado en el paso anterior", *ver_actual == numeros[4]);

    elem_borrado = lista_iter_borrar(iterador_2);
    print_test("Se puede borrar elementos en cualquier posicion", *elem_borrado == numeros[4]);

    lista_iter_avanzar(iterador_2);
    lista_iter_avanzar(iterador_2);

    print_test("Estoy al final de la lista", lista_iter_al_final(iterador_2));
    print_test("Se puede agregar elementos al final de la lista", lista_iter_insertar(iterador_2, &numeros[4]));
    print_test("Ahora el ultimo elemento es el agregado en el paso anterior", lista_iter_ver_actual(iterador_2) == lista_ver_ultimo(lista));
    print_test("Dejo de estar al final de la lista", !lista_iter_al_final(iterador_2));

    elem_borrado = lista_iter_borrar(iterador_2);
    print_test("Se puede borrar el ultimo elemento de la lista y lo devuelve", *elem_borrado == numeros[4]);
    print_test("Vuelvo a estar al final de la lista", lista_iter_al_final(iterador_2));

    lista_iter_destruir(iterador_2);
    lista_destruir(lista, NULL);
}

static void prueba_iterador_interno(void){
    lista_t *lista = lista_crear();

    int numeros[] = {1,2,3,4};
    lista_insertar_ultimo(lista, &numeros[0]);
    lista_insertar_ultimo(lista, &numeros[1]);
    lista_insertar_ultimo(lista, &numeros[2]);
    lista_insertar_ultimo(lista, &numeros[3]);

    size_t suma = 0;
    lista_iterar(lista, sumar_todos, &suma);
    print_test("La iteracion con 'sumar_todos' es correcta", suma == 10);

    print_test("La iteracion con 'imprimir_todos' es correcta", true);
    lista_iterar(lista, imprimir_todos, NULL);

    lista_destruir(lista, NULL);
}

void pruebas_lista_estudiante(){
    prueba_lista_vacia();
    prueba_algunos_elementos();
    prueba_dinamismo();
    prueba_destruir();
    prueba_iterador_externo();
    prueba_iterador_interno();
}

#ifndef CORRECTOR // Para que no dé conflicto con el main() del corrector.

int main(void){
    pruebas_lista_estudiante();
    return failure_count() > 0; // Indica si falló alguna prueba.
}

#endif
