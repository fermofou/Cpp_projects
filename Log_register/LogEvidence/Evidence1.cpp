//Fernando Morán Fougerat A01284623
//este código ordena un log, y muestra una sección de este.
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
#include "Log.h"

//funcion que intercambia objetos en una lista
void swap(vector<Log> &list, int a, int b) {
        Log aux = list[a];
        list[a] = list[b];
        list[b] = aux;
    
}
//busqueda binaria que encuentra posicion de hora en log 
int busqBinaria(vector<Log> list, long long data) {
    int left = 0;
    int right = list.size() - 1;
    int position = -1;
    int mid=left + (right - left) / 2;
//-1 por si hay error
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (data == list[mid].key) {
            // se encontro
            return mid;
        } else if (data < list[mid].key) {
            right = mid - 1;
            position = mid;
        } else {
            left = mid + 1;
            position = left;
        }
    }
    //si no esta el mismo valor, regresa donde se quedo
    return position;
}
//bubble sort para ordenar log
void bubbleSort(vector<Log> &list, int &comparisons, int &swaps) {
    int iter = 0;
    bool control = true;
    // Iteración por cada pasada
    while (iter < list.size()-1 && control) {
        // Inicializamos la variable de control
        control = false;
        for (int i=1; i<list.size()-iter; i++) {
            comparisons++;
            // Comparamos ambas keys
            if (list[i-1].key > list[i].key){
                swaps++;
                swap(list, i-1, i);
                control = true;
            }
        }
        // Incrementamos en 1 la variable iter
        iter++;
    }
}

//imprime cada log en un rango dado
template<class Log>
void print(vector<Log> list,int a, int b) {
    for (int i=a; i<b+1;i++) {
    cout << list[i].year << " " << list[i].month << " " << list[i].day << " " << list[i].time << " " << list[i].ip << " " << list[i].message<<endl;   }
    cout << endl;
}

//cambia el mes de nombre a numero,siempre siendo string
template<class T>
void monthSwitch(T& month) {
    if (month == "Jan") {
        month = "01";
    } else if (month == "Feb") {
        month = "02";
    } else if (month == "Mar") {
        month = "03";
    } else if (month == "Apr") {
        month = "04";
    } else if (month == "May") {
        month = "05";
    } else if (month == "Jun") {
        month = "06";
    } else if (month == "Jul") {
        month = "07";
    } else if (month == "Aug") {
        month = "08";
    } else if (month == "Sep") {
        month = "09";
    } else if (month == "Oct") {
        month = "10";
    } else if (month == "Nov") {
        month = "11";
    } else if (month == "Dec") {
        month = "12";
    }
}

int main() {
    ifstream fileIn("log602.txt");
    ofstream fileOut("output602.out");
    string line;
    string word;
    string year;
    string month;
    string day;
    string time;
    string ip;
    string message;
    vector <Log> logs;
    int cont = 0;

    //lleno mi vector de logs con cada línea
    while (getline(fileIn, line)) { 
        message = "";
        stringstream ss(line);
        ss >> month >> day >> year >> time >> ip;
        monthSwitch(month);
        while (ss >> word) {
            message = message + " " + word;
        }
       Log loog(year,month,day,time,ip,message);
       loog.keyGenerator();
       logs.push_back(loog);
        cont++;
    }
    cout << "contador de registros: " << cont << endl;
    //creo una lista auxiliar, la lleno de los logs que ya encontre
    vector<Log> listAux;
    listAux=logs;
    int comparisons = 0;
    int swaps = 0;
    //ordeno con bubble sort esta lista
    bubbleSort(listAux, comparisons, swaps);
    cout << "Ordenamiento por Burbuja" << endl;
    print(listAux,0,listAux.size()-1);
    cout << "Comparaciones: " << comparisons << " - intercambios: " << swaps << endl;
    ofstream Salida("output602.txt");
    //creo un txt y lo lleno con los datos ordenados
    for (const Log& log : listAux) {
        Salida << log.year << " " << log.month << " " << log.day << " " << log.time << " " << log.ip << " " << log.message << endl;
    }
    Salida.close();
    //pido 2 datos, los cuales seran inicio y fin del rango
    cout<<"Da fecha y hora inicial para busqueda binaria (AAAAMMDDHHHHHH)"<<endl;
    long long a=0;
    cin>>a;
    int inicio=0;
    inicio =busqBinaria(listAux,a);
    cout<<"Da fecha y hora final para busqueda binaria (AAAAMMDDHHHHHH)"<<endl;
    long long b=0;
    cin>>b;
    int fin=0;
    fin=busqBinaria(listAux,b);
    //aun si no existen igual, se encuentran todos los datos entre las fechas y se imprime
    print(listAux,inicio,fin-1);
    ofstream Rango("range602.txt");
    for (int i=inicio;i<(fin-1);i++) {
        Rango << listAux[i].year << " " << listAux[i].month << " " << listAux[i].day << " " << listAux[i].time << " " << listAux[i].ip << " " << listAux[i].message << endl;
    }
    //imprimo y agrego a un txt nuevo el rango
    Rango.close();
    return 0;
}