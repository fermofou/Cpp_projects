#ifndef Heap_H
#define Heap_h

#include <vector>

template <class T>
class Heap{
private:
    vector<T> heap;
public:
    Heap();
    Heap(vector<T> list);
    Heap(initializer_list<T> list);
    int getSize();
    void print();
    void swap(int a, int b);
    void downSort(int father);
    bool empty();
    void push(T data);
    void pop();
    T top();
    void fileOut(string name);
};

template <class T>
Heap<T>::Heap(){
}

template <class T>
Heap<T>::Heap(vector<T> list){  //hacer heap a una lista
    heap=list;
    int LastFather=list.size()/2-1;
    //recorro padres de derecha a izq
    while (LastFather>=0){ //cada padre
        downSort(LastFather);
        LastFather--;
    }
}


template <class T>
void Heap<T>::downSort(int father){
        int son1,son2,bigSon;
        while(father*2+1<heap.size()){
            son1=father*2+1; //variable 1er hijo
            if (father*2+2<heap.size()){ //checo si hay 2o hijo
                son2=father*2+2;
                heap[son1].key2>heap[son2].key2?bigSon=son1 : bigSon =son2;
            }else{
                bigSon=son1; //si solo hay 1 hijo
            }
            //checamos si es mayor que padre (ocupa cambiar)
            if(heap[bigSon].key2>heap[father].key2){
                swap(father,bigSon);
                father= bigSon;
            }else{
                father=heap.size();
            }  
        }

}

template <class T>
void Heap<T>::swap(int a, int b){
    T aux=heap[a];
    heap[a]=heap[b];
    heap[b]=aux;
}

template <class T>
Heap<T>::Heap(initializer_list<T> list){
    heap=list;
    int LastFather=list.size()/2-1;
    //recorro padres de derecha a izq
    while (LastFather>=0){ //cada padre
        downSort(LastFather);
        LastFather--;
    }
}

template <class T>
int Heap<T>::getSize(){
    return heap.size();
}

template <class T>
void Heap<T>::print(){
    for (auto x:heap){
        cout<<x<<endl;
        // cout<<x.key1<<endl; funcionan bien ambas :)
        // cout<<x.key2<<endl;
    }
    cout<<endl;
}

template <class T>
bool Heap<T>::empty(){
    return heap.empty();
}

template <class T>
void Heap<T>::pop(){
    if (heap.size()!=0){
        heap.erase(heap.begin());
    }else{
        cout<<"lista esta vacia"<<endl;
    }
    int LastFather=heap.size()/2-1;
    //recorro padres de derecha a izq
    while (LastFather>=0){ //cada padre
        downSort(LastFather);
        LastFather--;
    }
}

template <class T>
void Heap<T>::push(T data){
    heap.push_back(data);
    int LastFather=heap.size()/2-1;
    //recorro padres de derecha a izq
    while (LastFather>=0){ //cada padre
        downSort(LastFather);
        LastFather--;
    }
}

template <class T>
T Heap<T>::top(){
    if (heap.size()!=0){
        return heap[0];
    }else{
    throw out_of_range("vacio");
    }
}

template <class T>
void Heap<T>::fileOut(string name){
    ofstream fileOut(name);
    for(int i=0;i<heap.size();i++){
                const Log& log = heap[i];
                cout << log.year << " " << log.month << " " << log.day << " " << log.time << " "<< log.ip << " " << log.message << " " <<  "\n";
                fileOut<< log.year << " " << log.month << " " << log.day << " " << log.time << " " << log.ip << " " << log.message << endl;  
    }
                fileOut.close();
}


#endif 