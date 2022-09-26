#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "persona.h"

nodo* archivo2lista(nodo*lista, char archivo[]);
void lista2archivo(char archivo[], nodo* lista);
int lista2arreglo(nodo*lista, stPersona d[], int dim);
nodo* arreglo2lista(nodo*lista, stPersona d[], int dim);
void agregarAlFinalPD(nodo** lista, nodo* nuevo);

nodo * iniciLista();
nodo * crearNodo(stPersona dato);
nodo * agregarAlPpio(nodo* lista, nodo* nuevo);
void muestraLista(nodo* lista);
void muestraNodo(nodo* n);
nodo * agregarAlPrincipioPro(nodo* lista, nodo* nuevo);
nodo* buscarUltimo(nodo* lista);
nodo* agregarAlFinal(nodo* lista, nodo* nuevo);
nodo* agregarEnOrdenPorEdad(nodo* lista, nodo* nuevo);
int cuentaNodosPorEdad(nodo* lista, int edad);
int cuentaNodosPorEdadRec(nodo* lista, int edad);
int cuentaNodosRec(nodo* lista);
int cuentaNodosRecTernario(nodo* lista);
int sumaNodosPorEdad(nodo* lista, int edad);
int sumaNodosPorEdadRec(nodo* lista, int edad);
int sumaNodosPorEdadRecTern(nodo* lista, int edad);
void muestraListaRec(nodo* lista);
stPersona verPrimero(nodo* lista);
stPersona verPrimero1(nodo* lista);
nodo* borrarPrimero(nodo* lista);
nodo* buscaNodoPorNombre(nodo* lista, char nombre[]);
nodo* borrarNodoPorNombre(nodo* lista, char nombre[]);
nodo* invertirLista(nodo* lista);
void agregarAlFinalPD(nodo** lista, nodo* nuevo);

int main()
{
    //Pila p;
    //inicPila(&p);
    nodo* lista;
    lista=iniciLista();
//    cargaArchivo("personas.dat");

    //lista = archivo2lista("personas.dat", lista, 0);
 //   lista = archivo2listaPorNombre("personas.dat", lista, "Pepe");
 //   agregarAlPpioPunteroDoble(&lista, crearNodo(cargaUnaPersona()));
    printf("\nLista de Personas Original!\n");
    muestraLista(lista);
    lista = invertirLista(lista);

    /*
    for(int i=0;i<50;i++){
       // lista=agregarAlPrincipioPro(lista, crearNodo(cargaUnaPersona()));
        lista=agregarEnOrdenPorEdad(lista, crearNodo(cargaUnaPersona()));
    }
    lista = agregarAlFinal(lista, crearNodo(cargaUnaPersona()));
*/
    printf("\nLista de Personas Invertida!\n");
    muestraLista(lista);

    return 0;
}
/// carga archivo


void cargaArchivo(char archivo[]){
    FILE* archi = fopen(archivo, "wb");
    stPersona p;
    if(archi){
        for(int i=0;i<10;i++){
            p = cargaUnaPersona();
            fwrite(&p, sizeof(stPersona), 1, archi);
        }
        fclose(archi);
    }
}

/// genera y muestra persona
stPersona cargaUnaPersona(){
    static int id=0;
    id++;
    stPersona p;
    p.id=id;
    strcpy(p.nombre, "Pepe");
    p.edad=rand()%100;
    //p.edad=10;
    p.sexo='m';
    return p;
}

void muestraUnaPersona(stPersona p){
    printf("\n ID...........: %d", p.id);
    printf("\n Nombre.......: %s", p.nombre);
    printf("\n Edad.........: %d", p.edad);
    printf("\n Sexo.........: %c", p.sexo);
    printf("\n _________________________________________");
}



///archivo a lista y alreves

nodo* archivo2lista(nodo*lista, char archivo[]){
    FILE* archi = fopen(archivo, "rb");
    stPersona p;

    if(archi){
        while(fread(&p,sizeof(archi),1,archi>0)){
          agregarAlPpio(lista, crearNodo(p));

        }

    }
    fclose(archi);
return lista;

}



void lista2archivo(char archivo[], nodo* lista){
    FILE* archi= fopen(archivo, "ab");
    stPersona p;
    nodo* seg=lista;
    if(archi){
        while(lista->siguiente!=NULL){
            p = lista->dato;
            fwrite(&p, sizeof(stPersona),1, archi);
            lista=lista->siguiente;

        }

    }
    fclose(archi);
}

///lista a arreglo y alreves
int lista2arreglo(nodo*lista, stPersona d[], int dim){
    int i = 0;
    while(lista && i<dim){
      stPersona dato= lista->dato;
        d[i]=dato;
        i++;
      lista=lista->siguiente;
    }


    return i;
}

nodo* arreglo2lista(nodo*lista, stPersona d[], int dim){
    int i=0;
    if(lista==NULL){
        while(i<dim){
         agregarAlPpio(lista, crearNodo(d[i]));
            i++;

        }

    }else{
        while(i<dim){
            agregarAlFinal(lista, crearNodo(d[i]));
            i++;
        }

    }

    return lista;
}

///agrega en orden por edad
nodo* agregarEnOrdenPorEdad(nodo* lista, nodo* nuevo){
    /// Si la lista esta vacia le asigno el nuevo nodo
    if(!lista){
        lista = nuevo;
    }else{
        /// si el nuevo nodo es menor al primero de la lista, agrego a principio
        if(nuevo->dato.edad <= lista->dato.edad){
            lista = agregarAlPpio(lista, nuevo);
        }else{
            /// buscamos el lugar donde insertar
            nodo* ante = lista;
            nodo* seg = lista;
            while(seg && (nuevo->dato.edad > seg->dato.edad)){
                ante = seg;
                seg = seg->siguiente;
            }
            /// insertar el nuevo nodo en la lista de manera ordenada
            nuevo->siguiente = seg;
            ante->siguiente = nuevo;
        }
    }
    return lista;
}

//intercalar y borrar nodo e invertir
nodo* invertirLista(nodo* lista){
    nodo* listaInvertida=NULL;
    nodo* aux=NULL;
    while(lista){
        aux=lista;
        lista=lista->siguiente;
        aux->siguiente=NULL;
        listaInvertida=agregarAlPpio(listaInvertida, aux);
    }
    return listaInvertida;
}

nodo* borrarNodoPorNombre(nodo* lista, char nombre[]){
    nodo* seg;
    nodo* ante;
    if(lista && strcmp(nombre, lista->dato.nombre)==0){
        nodo* aux=lista;
        lista=lista->siguiente;
        free(aux);
    }else{
        seg = lista;
        while(seg && strcmp(nombre, seg->dato.nombre)!=0){
            ante = seg;
            seg = seg->siguiente;
        }
        if(seg){
            ante->siguiente=seg->siguiente;
            free(seg);
        }
    }
    return lista;
}

nodo* intercalarListas(nodo* listaA, nodo* listaB, nodo* listaFinal){
    nodo* aux = NULL;
    while(listaA && listaB){ /// while(listaA != NULL && listaB != NULL)
        if(listaA->dato.edad < listaB->dato.edad){
            aux = listaA;
            listaA = listaA->siguiente;
        }else{
            aux = listaB;
            listaB = listaB->siguiente;
        }
        aux->siguiente = NULL;
        listaFinal = agregarAlFinal(listaFinal, aux);
    }
    if(listaA){
        listaFinal = agregarAlFinal(listaFinal, listaA);
    }else if(listaB){
        listaFinal = agregarAlFinal(listaFinal, listaB);
    }

    return listaFinal;
}


//funciones puntero doble
void agregarAlFinalPD(nodo** lista, nodo* nuevo){
    if(!(*lista)){
        (*lista) = nuevo;
    }else{
        nodo* ultimo = buscarUltimo(*lista);
        ultimo->siguiente = nuevo;
    }
}

void invertirListaPD(nodo** lista){
    nodo* listaInvertida=NULL;
    nodo* aux=NULL;
    while(*lista){
        aux=(*lista);
        (*lista)=(*lista)->siguiente;
        aux->siguiente=NULL;
        listaInvertida=agregarAlPpio(listaInvertida, aux);
    }
    (*lista)=listaInvertida;
}
/*
void agregarAlFinalPD(nodo** lista, nodo* nuevo){
    if(!(*lista)){
        (*lista) = nuevo;
    }else{
        nodo* ultimo = buscarUltimo(*lista);
        ultimo->siguiente = nuevo;
    }
}
*/
///funciones recursivas

nodo* borrarListaRecursiva(nodo* lista){
    nodo* aux=NULL;
    if(lista){
        aux=lista;
        lista=borrarListaRecursiva(lista->siguiente);
        free(aux);
    }
    return lista;
}

void muestraListaRec(nodo* lista){
    if(lista){
        muestraNodo(lista);
        muestraListaRec(lista->siguiente);
    }
}

int sumaNodosPorEdadRec(nodo* lista, int edad){
    int suma=0;
    if(lista){
        if(lista->dato.edad>edad){
            suma = lista->dato.edad + sumaNodosPorEdadRec(lista->siguiente, edad);
        }else{
            suma = sumaNodosPorEdadRec(lista->siguiente, edad);
        }
    }

    return suma;
}

int sumaNodosPorEdad(nodo* lista, int edad){
    int suma = 0;
    nodo* seg = lista;
    while(seg){
        if(seg->dato.edad>edad){
            suma += seg->dato.edad;
        }
        seg=seg->siguiente;
    }
    return suma;
}

int cuentaNodosRec(nodo* lista){
    int cont=0;
    if(lista){
        cont = 1 + cuentaNodosRec(lista->siguiente);
    }
    return cont;
}

int cuentaNodosPorEdadRec(nodo* lista, int edad){
    int cont=0;
    if(lista){
        if(lista->dato.edad > edad){
            cont = 1 + cuentaNodosPorEdadRec(lista->siguiente, edad);
        }else{
            cont = cuentaNodosPorEdadRec(lista->siguiente, edad);
        }
    }

    return cont;
}

//// pilas
#define Pila nodo*

void inicPila(Pila* pila);
int pilavacia(Pila* pila);
stPersona tope(Pila* pila);
stPersona desapilar(Pila* pila);
void apilar(Pila* pila, stPersona dato);
void mostrar(Pila* pila);

void inicPila(Pila* pila){
    (*pila)=iniciLista();
}

int pilavacia(Pila* pila){
    int rta=0;
    if((*pila)==NULL){
        rta=1;
    }
    return rta;
}

int pilavacia2(Pila* pila){
    return ((*pila)==NULL);
}

int pilavaciaTernario(Pila* pila){
    return (*pila)?1:0;
}

stPersona tope(Pila* pila){
    return verPrimero(*pila);
}

stPersona desapilar(Pila* pila){
    stPersona p = verPrimero(*pila);
    (*pila)=borrarPrimero(*pila);
    return p;
}

void apilar(Pila* pila, stPersona dato){
    (*pila)=agregarAlPpio(*pila, crearNodo(dato));
}

void mostrar(Pila* pila){
    muestraLista(*pila);
}

