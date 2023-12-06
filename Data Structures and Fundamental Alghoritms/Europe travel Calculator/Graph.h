#ifndef Graph_h
#define Graph_h

#include "Edge.h"
#include "HashTable.h"
#include "Sort.h"
#include <stack>
#include <queue>

template <class T>
class Graph {
private:
    HashTable<T> vertices; //sera el hash aqui mismo
    vector< vector< Edge<T> > > adjacencyList;
    int findVertex(T vertex);
    void dfsr(T vertex, vector<bool> &status,ofstream &file);
    int findSmall(vector<bool> &status, vector<int> &cost);
public:
    Graph();
    Graph(HashTable<T> vertices, vector< Edge<T> > edges);
    void addEdge(Edge<T> edge);
    void addVertex(T vertex);
    void removeEdge(Edge<T> edge);
    void removeVertex(T Vertex);
    void bfs(T vertex);
    void dfs(T vertex);
    void dijkstraCar(T vertex, T destino);
    void dijkstraTrain(T vertex, T destino);
    void print(string fileOutName);
    void printCities(string fileOutName);
};

template <class T>
Graph<T>::Graph() {

}

template <class T>
int Graph<T>::findVertex(T vertex) {
    typename vector<T>::iterator it = find(this->vertices.table.begin(), this->vertices.table.end(), vertex);
    if (it != vertices.table.end()) {
        return it - vertices.table.begin();
    } else {
        return -1;
    }

}


template <class T>
Graph<T>::Graph(HashTable<T> vertices, vector< Edge<T> > edges) {
    // Actualizar la lista de vertices
    this->vertices = vertices;
    // Inicializamos la lista de adyacencias
    vector< Edge<T> > defaultEdges;
    adjacencyList.assign(vertices.table.size(), defaultEdges);
    
    // Recorremos la lista de adyacencias
    for (auto edge : edges) {
        // Buscamos el índice del vertice origen
        int sourceIndex = findVertex(edge.source);
        // Validamos si el vértice origen existe en la lista de vértices
        if (sourceIndex != -1) {
            // Agreamos el edge en la posición del vértice origen de nuestra lista de adyacencias
            adjacencyList[sourceIndex].push_back(edge);
        }
    }
}

template <class T>
void Graph<T>::addEdge(Edge<T> edge) {
    // Buscar el índice del vértice origen
    int sourceIndex = findVertex(edge.source);
    // Buscar el índice del vértice destino
    int targetIndex = findVertex(edge.target);
    // Validar que los dos vértices existan
    if (sourceIndex != -1 && targetIndex != -1) {
        // Buscar si ya existe el edgen en la lista de adyacencias 
        for (int i=0; i<adjacencyList[sourceIndex].size(); i++) {
            // Validamos si ya existe el target
            if (adjacencyList[sourceIndex][i].target == edge.target) {
                // Nos salimos de la función
                throw invalid_argument("El arco ya existe");
            }
        }
        // Si no existe agregarlo
        adjacencyList[sourceIndex].push_back(edge);
    } else {
        throw invalid_argument("Alguno de los vértices no existe");
    }
}

template <class T>
void Graph<T>::addVertex(T vertex) {    
    // Buscar si existe el vértice a agregar
    int vertexIndex = findVertex(vertex);
    // Agregarlos si no existe
    if (vertexIndex == -1) {
        // Agregamos el vértice en la lista de vértices
        vertices.insert(vertex);
        // Agregamos una elemento en la lista de adyacencias vacío
        vector < Edge<T> > adyacencies;
        adjacencyList.push_back(adyacencies);
    } else {
        throw invalid_argument("El vértice ya existe");
    }
}

template <class T>
void Graph<T>::bfs(T vertex) {
    // Verificamos si existe el vértice
    int vertexIndex = findVertex(vertex);
    if (vertexIndex != -1) { // Si existe
        ofstream fileOut("output602-3.out"); 
        // Creamos un vector de tipo bool del tamaño de la cantidad de vértices inicializado en false (status)
        vector<bool> status(vertices.table.size(), false);
        // Creamos una file de tipo int (Vamos a almacenar el índice del vértice)
        queue<int> bfsQueue; //queue de las ciudades
        // Agreamos el vértice que recibimos de parámetro a la fila
        bfsQueue.push(vertexIndex);
        // Cambiamos su estado a verdadero en la lista de estados
        status[vertexIndex] = true;
        // Hacemos un ciclo mientras la fila no este vacía
        while (!bfsQueue.empty()) {
            // Leemos el primer elemento de la fila
            int neighborIndex = bfsQueue.front();
            // Recorremos sus vecinos en la lista de adyacencias
            for (auto edge : adjacencyList[neighborIndex]) {
                // Buscamos el indice de vecino
                int targetIndex = findVertex(edge.target);
                // Validamos su estatus en el vector de estado
                if (!status[targetIndex]) {
                    // Si es falso agregamos el índice a la fila
                    bfsQueue.push(targetIndex);
                    // Actualizamos su estado
                    status[targetIndex]= true;
                }
            }
            fileOut<< vertices.table[bfsQueue.front()] << " ";
            // Imprimimos el elemento 
            cout << vertices.table[bfsQueue.front()] << " ";
            // Sacamos el elemento de la fila
            bfsQueue.pop();
        }
        cout << endl;
        fileOut.close();
    } else {
        throw invalid_argument("Vértice inválido");
    }
}

template <class T>
void Graph<T>::dfsr(T  vertex, vector<bool> &status, ofstream &file) {
    // Búscamos el índice del vértice
    int vertexIndex = findVertex(vertex);
    // Cambiamos su estado a verdadero
    status[vertexIndex] = true;
    cout<<vertices.table[vertexIndex]<<" ";
    file<<vertices.table[vertexIndex]<<" ";
    // Recorremos todos sus vecinos
    for (auto neighbor : adjacencyList[vertexIndex]) {
        // Buscamos el índice del vecino
        int neighborIndex = findVertex(neighbor.target);
        // Validamos si el estado esta en falso
        if (!status[neighborIndex]) {
            // Llamamos a la función de recursividad
            dfsr(neighbor.target, status,file);
        }
    }
}

template <class T>
void Graph<T>::dfs(T vertex) {
    // Validamos si el vértice éxiste
    int vertexIndex = findVertex(vertex);
    if (vertexIndex != -1) {
        // Creamos un vector de booleanos del tamaño de la cantidad de vértices
        vector<bool> status(vertices.table.size(), false);
        // Llamamos a la función de recursividad
        ofstream fileOut("output602-4.out"); 
        dfsr(vertex, status, fileOut);
        cout << endl;
        fileOut.close();
    } else {
        throw invalid_argument("El vértice no existe");
    }
}

template <class T>
void Graph<T>::dijkstraTrain(T vertex, T destino){
    int vertexIndex = findVertex(vertex);
    int destinoIndex=findVertex(destino);
    
    if (vertexIndex != -1 && destinoIndex != -1) {
        //creo lista de estado, costo y de paths
        vector<bool> status(vertices.table.size(), false);
        vector<int> costo(vertices.table.size(), INT_MAX);
        vector<int> path(vertices.table.size(), -1);
        vector<int> km(vertices.table.size(), -1);
        vector<int> min(vertices.table.size(), -1);
        //comenzamos del inicio, con un costo de 0
        costo[vertexIndex]=0;
        int shortestIndex=vertexIndex;
        while (shortestIndex !=destinoIndex){
            //se hace true
            status[shortestIndex]=true;
            for (auto neighbor : adjacencyList[shortestIndex]){
                int neighborIndex=findVertex(neighbor.target);
                if (costo[neighborIndex]>costo[shortestIndex]+neighbor.distanceTrain){
                    costo[neighborIndex]=costo[shortestIndex]+neighbor.distanceTrain;
                    path[neighborIndex]=shortestIndex;
                    km[neighborIndex]=km[shortestIndex]+neighbor.distanceTrain;
                    min[neighborIndex]=min[shortestIndex]+neighbor.timeTrain;
                }
            }
            shortestIndex=findSmall(status,costo);
            if (shortestIndex==destinoIndex){
                break; //encontrado
            }

        }
        //ya esta tabla lista, regresamos a -1. hago vector de pilas
        vector<stack<int>> shortestPaths(vertices.table.size());
        //llenamos la pila de manera secuencial
        for (int i=0;i<vertices.table.size();i++){
            //agregamos el indice a la pila
            shortestPaths[i].push(i);
            int pathInd=path[i];
            while (pathInd!=-1){
                shortestPaths[i].push(pathInd);
                pathInd=path[pathInd];
            }
        }
        //imprimimos el result
        cout<<vertices.table[destinoIndex]<<" - ";
            while(!shortestPaths[destinoIndex].empty()){
                cout<<vertices.table[shortestPaths[destinoIndex].top()]<<" ";
                shortestPaths[destinoIndex].pop();

            }cout<<"- ";
            if (costo[destinoIndex]!=INT_MAX){
                cout<<"Distancia total: "<<km[destinoIndex]<<" km. Tiempo total: "<<min[destinoIndex]/60<<"h : "<<min[destinoIndex]%60<<"m"<<endl;
            }else{
                cout<<"no hay ruta"<<endl;
            }    
        
    }else {
        throw invalid_argument("El vértice no existe");
    }
}

template <class T>
void Graph<T>::dijkstraCar(T vertex, T destino){
    int vertexIndex = findVertex(vertex);
    int destinoIndex=findVertex(destino);
    
    if (vertexIndex != -1 && destinoIndex != -1) {
        //creo lista de estado, costo y de paths
        vector<bool> status(vertices.table.size(), false);
        vector<int> costo(vertices.table.size(), INT_MAX);
        vector<int> path(vertices.table.size(), -1);
        vector<int> km(vertices.table.size(), -1);
        vector<int> min(vertices.table.size(), -1);
        //comenzamos del inicio, con un costo de 0
        costo[vertexIndex]=0;
        int shortestIndex=vertexIndex;
        while (shortestIndex !=destinoIndex){
            //se hace true
            status[shortestIndex]=true;
            for (auto neighbor : adjacencyList[shortestIndex]){
                int neighborIndex=findVertex(neighbor.target);
                if (costo[neighborIndex]>costo[shortestIndex]+neighbor.distanceCar){
                    costo[neighborIndex]=costo[shortestIndex]+neighbor.distanceCar;
                    path[neighborIndex]=shortestIndex;
                    km[neighborIndex]=km[shortestIndex]+neighbor.distanceCar;
                    min[neighborIndex]=min[shortestIndex]+neighbor.timeCar;
                }
            }
            shortestIndex=findSmall(status,costo);
            if (shortestIndex==destinoIndex){
                break; //encontrado
            }
        }
        //ya esta tabla lista, regresamos a -1. hago vector de pilas
        vector<stack<int>> shortestPaths(vertices.table.size());
        //llenamos la pila de manera secuencial
        for (int i=0;i<vertices.table.size();i++){
            //agregamos el indice a la pila
            shortestPaths[i].push(i);
            int pathInd=path[i];
            while (pathInd!=-1){
                shortestPaths[i].push(pathInd);
                pathInd=path[pathInd];
            }
        }
        //imprimimos el result
        cout<<vertices.table[destinoIndex]<<" - ";
            while(!shortestPaths[destinoIndex].empty()){
                cout<<vertices.table[shortestPaths[destinoIndex].top()]<<" ";
                shortestPaths[destinoIndex].pop();

            }cout<<"- ";
            if (costo[destinoIndex]!=INT_MAX){
                cout<<"Distancia total: "<<km[destinoIndex]<<" km. Tiempo total: "<<min[destinoIndex]/60<<"h : "<<min[destinoIndex]%60<<"m."<<endl;
            }else{
                cout<<"no hay ruta"<<endl;
            }    
        
    }else {
        throw invalid_argument("El vértice no existe");
    }
}

template <class T>
int Graph<T>::findSmall(vector<bool> &status, vector<int> &costo){
    int shortest =-1;
    int shortCost=INT_MAX;
    //secuencial
    for (int i=0;i<vertices.table.size();i++){
        //valido si es falso
        //checo si es menor, y lo regreso
        if(costo[i]<shortCost && !status[i]){
            shortCost=costo[i];
            shortest=i;
        }
    }
    return shortest;
}

template <class T>
void Graph<T>::print(string fileOutName) {
    ofstream fileOut(fileOutName);
    for (int i=0; i<vertices.table.size(); i++) {
        cout << vertices.table[i];
        fileOut << vertices.table[i];
        for (auto edge : adjacencyList[i]) {
            cout << " - " <<edge.target;
            fileOut << " - " <<edge.target;
        }
        cout << endl;
        fileOut << endl;
    }
}

template <class T>
void Graph<T>::printCities(string fileOutName) {
    ofstream fileOut(fileOutName);
    vector<string> ciudades=vertices.table;
    quickSort(ciudades,0,ciudades.size()-1);
    for (string x : ciudades) {
                cout <<x << endl;
                fileOut<<x<<endl;
            }
            fileOut.close();
}



#endif /* Graph_h */