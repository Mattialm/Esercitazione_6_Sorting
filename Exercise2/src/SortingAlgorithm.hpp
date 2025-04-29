#pragma once

#include <iostream>
#include <concepts>
#include <vector>

using namespace std;

namespace SortLibrary {

    template<typename T>    // Uso template per garantire generalità del codice per qualsiasi tipo T
    concept Sortable = requires(T& t)       // Definisco il concetto Sortable: il riferimento t al tipo T dev'essere ordinabile
    {
        {t < t} -> convertible_to<bool>;    // L'espressione dev'essere ben formata e convertibile a bool
    };

    template<Sortable T>
    void BubbleSort(vector<T>& v)   // Passo per riferimento per modificare direttamente
    {
        const unsigned int n = v.size();
        for(unsigned int i=0; i <= n-2; i++){
            for(unsigned int j = i+1; j < n; j++){
                if(v[j] < v[i]){
                    // Scambio v[j] e v[i]
                    T tmp = v[i];
                    v[i] = v[j];
                    v[j] = tmp;
                }
            }
        }
    }

    template<Sortable T>
    void HeapGenerator(vector<T>& v, unsigned int n, unsigned int i)
    {
        // Implemento heap come vettore dove la radice è al posto i e i figli ai posti 2i+1 e 2i+2
        unsigned int largest = i;   // Inizializzo largest come radice i
        unsigned int left = 2 * i + 1;
        unsigned int right = 2 * i + 2;

        // Controllo se i figli sono maggiori della radice, nel caso salvo come maggiore il figlio maggiore
        if (left < n && v[left] > v[largest]) 
            largest = left;

        if (right < n && v[right] > v[largest]) 
            largest = right;
        
        // Se i figli sono maggiori -> largest non è più la radice -> scambio figlio e radice
        if (largest != i) {
        T tmp = v[i];
        v[i] = v[largest];
        v[largest] = tmp;

        // Per costruire l'heap dei sottoalberi richiamo ricorsivamente HeapGenerator con radice largest
        HeapGenerator(v, n, largest);
        }
    }

    template<Sortable T>
    void HeapSort(vector<T>& v)
    {
        unsigned int n = v.size();

        // Riarrangiamo il vettore come un Heap: partiamo dal primo nodo padre e usiamo HeapGenerator per rendere
        // Heap tutti i sottoalberi (itero all'indietro tra nodi padri)
        for(int i = n/2 -1; i >= 0; i--){
            HeapGenerator(v, n, i);
        }

        // Operazione di Dequeue -> estraggo il massimo e lo metto al fondo ad ogni iterazione
        for(int j = n-1; j>0; j--){
            T tmp = v[0];
            v[0] = v[j];
            v[j] = tmp;

            HeapGenerator(v, j, 0); // Ricreo un Heap nella parte non ordinata (da indice 0 a indice j escluso)
        }
    }

}


