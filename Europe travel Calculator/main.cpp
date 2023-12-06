#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

#include "HashTable.h"
#include "Graph.h"
#include "Sort.h"

//cambio tiempo a solo minutos
int timeSwitch(string time) {
    int hour, minutes;
    char colon;
    istringstream ss(time);
    ss >> hour >> colon >> minutes;
    int total = (hour * 60) + minutes;
    return total;
}


int main(){
    ifstream fileIn("EuropeCities.csv");
    string line;
    string word;
    string cityOrigin;
    string cityDestiny;
    string timeTrain;
    string timeCar;
    int distanceTrain;
    int distanceCar;
    HashTable<string> vertices; //nombres de ciudades en hash table
    vector< Edge<string> > edges;
    Graph graph(vertices, edges);
    getline(fileIn, line); //me salto la primera linea
    while (getline(fileIn, line)) { 
        stringstream ss(line);
        getline(ss, cityOrigin, ',');
        getline(ss, cityDestiny, ',');
        getline(ss, timeTrain, ',');
        ss>>distanceTrain;
        ss.ignore();  //ignora la coma
        getline(ss, timeCar, ',');
        ss>> distanceCar;
        int tTrain=timeSwitch(timeTrain); //cambio hh:mm a minutos
        int tCar=timeSwitch(timeCar); 
        try{
            graph.addVertex(cityOrigin); 
        }catch (const invalid_argument &e) {
            
        }
        try{ //como todas tienen ida y vuelta solo agrego una vez
            graph.addVertex(cityDestiny); 
        }catch (const invalid_argument &e) {
        }
        // cout<<cityOrigin<<" "<<cityDestiny<<" "<<tTrain<<" "<<distanceTrain<<" "<<tCar<<" "<<distanceCar<<endl; //ya funciona :)
        graph.addEdge(Edge<string>(cityOrigin,cityDestiny,distanceTrain,distanceCar,tTrain,tCar)); //agrego edge al grafo
    }
    fileIn.close();
    int menu=0;
    cout<<"Bienvenido a la evidencia 4"<<endl;
    while(menu!=5){
        cout<<"\n1.Desplegar las ciudades ordenadas por alfabeto\n2.Desplegar la lista de adyacencias del grafo\n3.Desplegar los recorridos del grafo\n4.Ruta mas corta entre dos ciudades\n5.Salir"<<endl;
        cin>>menu;
        if(menu==1){
            cout<<"Ciudades ordenadas por alfabeto (quickSort)"<<endl;
            graph.printCities("output602-1.out");
        }else if (menu==2){
            cout<<"Lista de adyacencias del grafo"<<endl;
            graph.print("output602-2.out");
        }else if (menu==3){
            cout<<"Recorridos del grafo"<<endl;
            cout<<"Da vertice donde comenzar el recorrido"<<endl;
            string index;
            cin>>index;
            cout<<"BFS"<<endl;
            graph.bfs(index);
            cout<<"DFS"<<endl;
            graph.dfs(index);
        }else if (menu==4){
            cout<<"Ruta mas corta entre dos ciudades"<<endl;
            string A,B;
            cout<<"Ciudad de origen"<<endl;
            cin>>A;
            cout<<"Ciudad de destino"<<endl;
            cin>>B;
            cout<<"Ruta mas corta en carro"<<endl;
            graph.dijkstraCar(A,B);
            cout<<"Ruta mas corta en tren"<<endl;
            graph.dijkstraTrain(A,B);
        }else if(menu==5){
            cout<<"adios :) -fermofou"<<endl;
        }else{
            cout<<"Opcion no valida"<<endl;
        }
    }
    return 0;
}