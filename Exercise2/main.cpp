#include <cmath> 
#include <iostream> 
#include <numeric>
#include <iostream>  
#include <sstream> 
#include <chrono> //libreria per la gestione e la misurazione del tempo 

#include "SortingAlgorithm.hpp"

using namespace std;

template<typename T>
string ArrayToString(const vector<T>& v) 
{
    string str; 
    ostringstream toString; // ostringstream -> manipolazione stringhe in output -> convertire il vettore in una stringa
    toString << "[ ";
    for (const T& e: v) //itero su ogni elemento del vettore 
        toString << e << " ";
    toString << "]";

    return toString.str(); // .str() -> restituisce un oggetto del tipo std::string
}

// Struttura ordinabile in base a value, ma necessario definire operatore di ordinamento <
struct ClassObj   
{
    double value;
};

// Inline -> si può inserire direttamente operatore senza dover chiamare la funzione
inline bool operator< (const ClassObj& lhs, const ClassObj& rhs) {return lhs.value < rhs.value;}


int main(int argc, char *argv[])
{
    cout << "argc: " << argc << endl;
    // Stampo iterativamente gli input da riga di comando
    for(int a = 0; a < argc; a++)
        cout << argv[a] << " ";
    cout << endl;

    size_t m = 10; // fisso il valore di default della dimensione di argc (qualora non venisse fornita)
    if(argc > 1)
    {
        istringstream convert(argv[1]); // converto l'argomento argv[1] in un oggetto di tipo istringstream
        convert >> m; // converto l'argomento (una stringa) in un intero
        cout << "use value: "  << m << endl; // uso il valore fornito dall'utente come valore di m 
    }
    else
        cerr << "use default value: "  << m << endl;

    
    // Def di v1
    vector<int> v1(m);
    iota(v1.begin(), v1.end(), -4);
    cout << "v1: " << ArrayToString(v1) << endl;


    // Def di v2
    srand(2); 
    vector<double> v2(m);
    for(size_t i = 0; i < m; i++)
        v2[i] = rand() / ((double)RAND_MAX);  // vettore di numeri casuali tra 0 e 1

    // Def di v3
    vector<int> v3(m, 0);   // vec di dim m inizializzato a soli zeri
    for(size_t i = floor(m * 0.5) + 1; i < m; i++)
        v3[i] = rand() % 1000; // % -> il resto della divisione tra rand() e 1000 -> valori tra 0 e 999.
    copy(v1.begin(), v1.begin() + floor(m * 0.5) + 1, v3.begin()); 
    // copio i primi m/2 + 1 elementi di v1 in v3 -> per metà costruito come v1, per metà come randomico

    
    unsigned int num_experiment = 100;


    // Bubblesort v1
    double time_elapsed_bubble_v1 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        vector<int> v(v1); // Copia di v1 per non modificarlo in ordianamento e riusarlo per Heapsort

        chrono::steady_clock::time_point start_time = chrono::steady_clock::now();  //prendo il tempo di inizio dell'ordinamento
        SortLibrary::BubbleSort<int>(v);
        chrono::steady_clock::time_point end_time = chrono::steady_clock::now(); //prendo il tempo di fine dell'ordinamento
        time_elapsed_bubble_v1 += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count(); // Calcolo il tempo in microsecondi impiegato per ordinare ogni iterazione
    }
    time_elapsed_bubble_v1 /= num_experiment; // Faccio una media tra il tempo totale e il numero di ordinamenti num_experiment
    cout << "Bubble Sort - v1: " << time_elapsed_bubble_v1 << endl; 


    // Bubblesort v2
    double time_elapsed_bubble_v2 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        vector<double> v(v2);

        chrono::steady_clock::time_point start_time = chrono::steady_clock::now();
        SortLibrary::BubbleSort<double>(v);
        chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
        time_elapsed_bubble_v2 += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    }
    time_elapsed_bubble_v2 /= num_experiment;

    cout << "Bubble Sort - v2: " << time_elapsed_bubble_v2 << endl;

    
    // Bubblesort v3
    double time_elapsed_bubble_v3 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        vector<int> v(v3);

        chrono::steady_clock::time_point start_time = chrono::steady_clock::now();
        SortLibrary::BubbleSort<int>(v);
        chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
        time_elapsed_bubble_v3 += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    }
    time_elapsed_bubble_v3 /= num_experiment;

    cout << "Bubble Sort - v3: " << time_elapsed_bubble_v3 << endl;


    // Heapsort v1
    double time_elapsed_heap_v1 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        vector<int> v(v1);

        chrono::steady_clock::time_point start_time = chrono::steady_clock::now();
        SortLibrary::HeapSort<int>(v);
        chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
        time_elapsed_heap_v1 += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    }
    time_elapsed_heap_v1 /= num_experiment;

    cout << "Heap Sort - v1: " << time_elapsed_heap_v1 << endl;

    // Heapsort v2
    double time_elapsed_heap_v2 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        vector<double> v(v2);

        chrono::steady_clock::time_point start_time = chrono::steady_clock::now();
        SortLibrary::HeapSort<double>(v);
        chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
        time_elapsed_heap_v2 += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    }
    time_elapsed_heap_v2 /= num_experiment;

    cout << "Heap Sort - v2: " << time_elapsed_heap_v2 << endl;

    // Heapsort v3
    double time_elapsed_heap_v3 = 0.0;
    for(unsigned int t = 0; t < num_experiment; t++)
    {
        vector<int> v(v3);

        chrono::steady_clock::time_point start_time = chrono::steady_clock::now();
        SortLibrary::HeapSort<int>(v);
        chrono::steady_clock::time_point end_time =chrono::steady_clock::now();
        time_elapsed_heap_v3 += chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    }
    time_elapsed_heap_v3 /= num_experiment;

    cout << "Heap Sort - v3: " << time_elapsed_heap_v3 << endl;


    return 0;
}


