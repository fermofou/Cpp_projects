#ifndef MinHeap_H
#define MinHeap_h

#include <vector>

template <class T>
class MinHeap{
private:
    vector<T> heap;
public:
    MinHeap();
    MinHeap(vector<T> list);
    MinHeap(initializer_list<T> list);
    int getSize();
    void print();
    void swap(int a, int b);
    void upSort(int father);
    bool empty();
    void push(T data);
    void pop();
    void top();
    void fileOut(string name);
};

template <class T>
MinHeap<T>::MinHeap(){
}

template <class T>
MinHeap<T>::MinHeap(vector<T> list){  //hacer MinHeap a una lista
    heap=list;
    int LastFather=list.size()/2-1;
    //recorro padres de derecha a izq
    while (LastFather>=0){ //cada padre
        upSort(LastFather);
        LastFather--;
    }
}


template <class T>
void MinHeap<T>::upSort(int father){
        int son1,son2,babySon;
        while(father*2+1<heap.size()){
            son1=father*2+1; //variable 1er hijo
            if (father*2+2<heap.size()){ //checo si hay 2o hijo
                son2=father*2+2;
                heap[son1].key2<heap[son2].key2?babySon=son1 : babySon =son2;
            }else{
                babySon=son1; //si solo hay 1 hijo
            }
            //checamos si es mayor que padre (ocupa cambiar)
            if(heap[babySon].key2<heap[father].key2){
                swap(father,babySon);
                father= babySon;
            }else{
                father=heap.size();
            }  
        }

}

template <class T>
void MinHeap<T>::swap(int a, int b){
    T aux=heap[a];
    heap[a]=heap[b];
    heap[b]=aux;
}

template <class T>
MinHeap<T>::MinHeap(initializer_list<T> list){
    heap=list;
    int LastFather=list.size()/2-1;
    //recorro padres de derecha a izq
    while (LastFather>=0){ //cada padre
        upSort(LastFather);
        LastFather--;
    }
}

template <class T>
int MinHeap<T>::getSize(){
    return heap.size();
}

template <class T>
void MinHeap<T>::print(){
    for (auto x:heap){
        cout<<x<<endl;
        cout<<x.key2<<endl;
    }
    cout<<endl;
}

template <class T>
bool MinHeap<T>::empty(){
    return heap.empty();
}

template <class T>
void MinHeap<T>::pop(){
    if (heap.size()!=0){
        cout<<heap[0]<<endl;
        heap.erase(heap.begin());
    }else{
        cout<<"lista esta vacia"<<endl;
    }
    int LastFather=heap.size()/2-1;
    //recorro padres de derecha a izq
    while (LastFather>=0){ //cada padre
        upSort(LastFather);
        LastFather--;
    }
}

template <class T>
void MinHeap<T>::push(T data){
    heap.push_back(data);
    int LastFather=heap.size()/2-1;
    //recorro padres de derecha a izq
    while (LastFather>=0){ //cada padre
        upSort(LastFather);
        LastFather--;
    }
}

template <class T>
void MinHeap<T>::top(){
    if (heap.size()!=0){
        cout<<heap[0]<<endl;
    }else{
        cout<<"lista esta vacia"<<endl;
    }
}

template <class T>
void MinHeap<T>::fileOut(string name){
    ofstream fileOut(name);
    for(int i=0;i<heap.size();i++){
                const Log& log = heap[i];
                cout << log.year << " " << log.month << " " << log.day << " " << log.time << " "<< log.ip << " " << log.message << " " <<  "\n";
                fileOut<< log.year << " " << log.month << " " << log.day << " " << log.time << " " << log.ip << " " << log.message << endl;  
    }
                fileOut.close();
}

#endif 