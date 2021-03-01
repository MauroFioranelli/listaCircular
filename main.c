#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

typedef struct ventas {
    int cod;
    float monto;
    struct ventas *sig;
} tventas;

typedef struct vendedor {
    int codigo;
    char nombre[MAX];
} tvendedor;

typedef struct nodo {
    tvendedor vend;
    tventas *sub;
    struct nodo *sig;
} tnodo;

void inicializar_circular(tnodo **lis);
tnodo *genera_nodo();
void carga_lista(tnodo **lis);
tventas *genera_subnodo();
void carga_sublista(tnodo **lis);
void mostrar_vendedor(tnodo *aux);
void mostrar_nombre_lista(tnodo *lis);
void modificar_vendedor(tnodo **lis);
void modificar_subventa(tnodo **lis);
void destruir_subnodo(tventas *sub);
void eliminar_subnodo(tnodo **lis);
void eliminar_vendedor(tnodo **lis);

///  ORDENAR, DESTRUIR ME FALTAN

int main() {
    tnodo *l;
    inicializar_circular(&l);
    carga_lista(&l);
    carga_lista(&l);
    carga_lista(&l);
    carga_sublista(&l);
    //carga_sublista(&l);
    //carga_sublista(&l);
    mostrar_nombre_lista(l);
    //modificar_vendedor(&l);
    //modificar_subventa(&l);
    //mostrar_nombre_lista(l);
    //eliminar_subnodo(&l);
    eliminar_vendedor(&l);
    mostrar_nombre_lista(l);

    return 0;
}

void inicializar_circular(tnodo **lis) {
    *lis = NULL;
}

tnodo *genera_nodo() {
    tnodo *aux = malloc(sizeof(tnodo));
    printf("Ingrese codigo del vendedor: ");
    fflush(stdin);
    scanf("%d",&aux->vend.codigo);
    printf("Ingrese nombre del vendedor: ");
    fflush(stdin);
    gets(aux->vend.nombre);
    aux->sig = NULL;
    aux->sub = NULL;
    return aux;
}

void carga_lista(tnodo **lis) {
    tnodo *nuevo = genera_nodo();

    if(*lis == NULL) {
        *lis = nuevo;
        nuevo->sig = *lis;
    } else {
        tnodo *aux = *lis;
        nuevo->sig = *lis;
        while(aux->sig != *lis)
            aux = aux->sig;
        aux->sig = nuevo;
        *lis = nuevo;
    }
}

tventas *genera_subnodo() {
    tventas *aux = malloc(sizeof(tventas));
    printf("Ingrese codigo de venta: ");
    fflush(stdin);
    scanf("%d",&aux->cod);
    printf("Ingrese monto de venta: ");
    fflush(stdin);
    scanf("%f",&aux->monto);
    aux->sig = NULL;
    return aux;
}

void carga_sublista(tnodo **lis) {
    if(*lis == NULL) {
        puts("Lista vacia");
    } else {
        int ref;
        printf("Ingrese codigo del vendedor a cargar venta: ");
        fflush(stdin);
        scanf("%d",&ref);
        tnodo *aux = *lis;
        while(aux->sig != *lis && ref != aux->vend.codigo)
            aux = aux->sig;
        if(aux->sig == *lis && ref != aux->vend.codigo)
            puts("Vendedor no encotrado");
        else {
            tventas *subnuevo = genera_subnodo();
            if(aux->sub == NULL)
                aux->sub = subnuevo;
            else {
                tventas *auxsub = aux->sub;
                while(auxsub->sig != NULL)
                    auxsub = auxsub->sig;
                auxsub->sig = subnuevo;
            }
            puts("Venta cargada correctamente");
        }
    }
    system("pause");
}

void mostrar_vendedor(tnodo *aux) {
    puts("------------------------------");
    printf("Codigo: %d",aux->vend.codigo);
    printf("\nNombre: %s",aux->vend.nombre);
    if(aux->sub != NULL) {
        printf("\n\tVentas realizadas:");
        tventas *auxsub = aux->sub;
        while(auxsub != NULL) {
            printf("\n\tCodigo venta: %d",auxsub->cod);
            printf("\n\tMonto venta: %g",auxsub->monto);
            auxsub = auxsub->sig;
        }
    } else
        printf("\n\tNo registra ventas realizadas:");
    puts("\n------------------------------");
}

void mostrar_nombre_lista(tnodo *lis) {
    if(lis == NULL) {
        puts("Lista vacia");
    } else {
        tnodo *aux = lis;
        while(aux->sig != lis) {
            mostrar_vendedor(aux);
            aux = aux->sig;
        }
        mostrar_vendedor(aux);
    }
    system("pause");
}

void modificar_vendedor(tnodo **lis) {
    if(*lis == NULL)
        puts("Lista vacia");
    else {
        int ref;
        printf("Ingrese el codigo del vendedor a modificar: ");
        fflush(stdin);
        scanf("%d",&ref);
        tnodo *aux = *lis;
        while(aux->sig != *lis && aux->vend.codigo != ref)
            aux = aux->sig;
        if(aux->sig == *lis && aux->vend.codigo != ref)
            puts("Vendedor no encontrado");
        else {
            printf("Vendedor encontrado:\n");
            mostrar_vendedor(aux);
            printf("Ingrese el nuevo nombre: ");
            fflush(stdin);
            gets(aux->vend.nombre);
            puts("Modificacion realizada correctamente.");
        }
    }
    system("pause");
}

void modificar_subventa(tnodo **lis) {
    if( *lis == NULL)
        puts("Lista vacia");
    else {
        int ref;
        printf("Ingrese codigo del vendedor a modificar venta: ");
        fflush(stdin);
        scanf("%d",&ref);
        tnodo *aux = *lis;
        while(aux->sig != *lis && aux->vend.codigo != ref)
            aux = aux->sig;
        if(aux->sig == *lis && aux->vend.codigo != ref)
            puts("Vendedor no enocntrado");
        else {
            if(aux->sub == NULL)
                puts("El vendedor no tiene ventas realizadas");
            else {
                printf("Vendedor encontrado:\n");
                mostrar_vendedor(aux);
                int cod_venta;
                printf("Ingrese codigo de venta a modificar valor: ");
                fflush(stdin);
                scanf("%d",&cod_venta);
                tventas *auxsub = aux->sub;
                while(auxsub != NULL && auxsub->cod != cod_venta)
                    auxsub = auxsub->sig;
                if(auxsub == NULL)
                    puts("Codigo de venta no encontrado");
                else {
                    printf("Ingrese el nuevo monto: ");
                    fflush(stdin);
                    scanf("%f",&auxsub->monto);
                    puts("Modificacion realizada");
                }
            }
        }
        system("pause");
    }
}

void destruir_subnodo(tventas *sub) {
    if(sub != NULL) {
        destruir_subnodo(sub->sig);
        free(sub);
    }
}

void eliminar_subnodo(tnodo **lis) {
    if(*lis == NULL)
        puts("Lista vacia");
    else {
        int ref;
        printf("Ingrese el codigo del vendedor a eliminar ventas: ");
        fflush(stdin);
        scanf("%d",&ref);
        tnodo *aux = *lis;
        while(aux->sig != *lis && aux->vend.codigo != ref)
            aux = aux->sig;
        if(aux->sig == *lis && aux->vend.codigo != ref)
            puts("Vendedor no encontrado");
        else if(aux->sub == NULL)
            puts("Vendedor sin ventas a eliminar");
        else {
            destruir_subnodo(aux->sub);
            aux->sub = NULL;
            puts("Ventas eliminadas correctamente");
        }
    }
    system("pause");
}

void eliminar_vendedor(tnodo **lis) {
    if(*lis == NULL)
        puts("Lista vacia");
    else {
        int ref;
        printf("Ingrese el codigo del vendedor a eliminar: ");
        fflush(stdin);
        scanf("%d",&ref);
        tnodo *ant = *lis, *act = *lis;
        while(act->sig != *lis && act->vend.codigo != ref) {
            ant = act;
            act = act->sig;
        }
        if(act->sig == *lis && act->vend.codigo != ref)
            puts("Vendedor no encontrado");
        else {
            if(ant == act) {
                if(ant->sig == *lis) {              ///ES UNICO
                    inicializar_circular(lis);
                } else {
                    while(ant->sig != *lis)         ///ES PRIMERO
                        ant = ant->sig;
                    *lis = act->sig;
                    ant->sig = *lis;
                }
            } else if(act->sig == *lis)             ///ES ULTIMO
                ant->sig = *lis;
            else {
                ant->sig = act->sig;                ///ES CENTRAL
            }
            if(act->sub != NULL)
                destruir_subnodo(act->sub);
            free(act);
            puts("Vendedor eliminado correctamente");
        }
    }
    system("pause");
}

void destruir_lista(tnodo **circ, tnodo *siguiente) {
    if(siguiente->sig != *circ) {
        destruir_lista(&(*circ),siguiente->sig);
        free(siguiente);
    } else {
        inicializar_circular(&(*circ));
        free(siguiente);
        puts("Lista destruida");
    }
}

void carga_lista_ordenada(tnodo **lis) {

    tnodo *nuevo = genera_nodo();

    if ( (*lis) == NULL ) {

        nuevo->sig = nuevo;
        (*lis) = nuevo;

    } else if ( nuevo->vend.cod < (*lis)->vend.cod) {     /// primero

        nuevo->sig = (*lis);

        tnodo * aux = (*lis);

        while ( aux->sig != (*lis) ) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
        (*lis) = nuevo;

    } else {
        tnodo *ant = (*lis);
        tnodo *act = (*lis)->sig;
        while ((act != (*lis)) && (act->vend.cod < nuevo->vend.cod)) {
            ant = act;
            act = act->sig;
        }
        if ( (act == (*lis)) || (act->vend.cod >nuevo->vend.cod)) {
            nuevo->sig = act;
            ant->sig = nuevo;
        }
    }
}

/*
void eliminar_nodo_circular( TNodoCircular ** ptrLista, int d ){

    if ( (*ptrLista) != NULL ){

        TNodoCircular * ptrActual;
        ptrActual = (*ptrLista);

        while ( (ptrActual->siguiente != (*ptrLista)) && (ptrActual->siguiente->dato != d ))
               ptrActual = ptrActual->siguiente;

        if ( ptrActual->siguiente->dato == d ){

            TNodoCircular * ptrEliminar = ptrActual->siguiente;

            if ( ptrEliminar->siguiente == ptrEliminar)
                (*ptrLista) = NULL;
            else{

                if ( ptrEliminar == (*ptrLista))
                 (*ptrLista) = ptrEliminar->siguiente;

                ptrActual->siguiente = ptrEliminar->siguiente;
            }

            free(ptrEliminar);
        }

    }

}
*/
