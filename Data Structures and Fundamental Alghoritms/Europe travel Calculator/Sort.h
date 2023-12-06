#ifndef Sort_h
#define Sort_h
#include <vector>
using namespace std;

template<class T>
void swap(vector<T> &list, int a, int b) {
    if (list[a] != list[b]) {
        T aux = list[a];
        list[a] = list[b];
        list[b] = aux;
    }
}

template<class T>
int getPivot(vector<T> &list, int left, int right) {
    // Definimos el pivote
    int pivot = right;
    // Definimos un índice auxiliar
    int auxIndex = left - 1;
    // Itereamos la lista desde left hasta right - 1
    for (int index=left; index<right; index++) {
        // comparamos el valor de index con el valor del pivot
        if (list[index] < list[pivot]) {
            // Incrementamos el indice auxiliar
            auxIndex++;
            // Intercambiamos el índice auxliar con index
            swap(list, index, auxIndex);
        }
    }
    // Incrementamos el indice auxiliar
    auxIndex++;
    // Intercambiamos el índice auxliar con index
    swap(list, pivot, auxIndex);
    // Regresamos el valor del indice auxiliar
    return auxIndex;
}

template <class T>
void  quickSort(vector<T> &list, int left, int right) {
    if (left < right) {
        // Obtenemos la posición final del privote
        int pivot = getPivot(list, left, right);
        // Ordenamos la lista del lado izquierdo
        quickSort(list, left, pivot-1);
        // Ordenamos la lista del lado derecho
        quickSort(list, pivot+1, right);
    }
}


#endif  // Sort_h
