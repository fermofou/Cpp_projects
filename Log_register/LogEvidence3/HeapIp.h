#ifndef HeapIp_H
#define HeapIp_h

#include <vector>
using namespace std; 

template <class T>
class HeapIp{
private:
    vector<T> heap;
public:
    HeapIp();
    HeapIp(vector<T> list);
    HeapIp(initializer_list<T> list);
    int getSize();
    void print();
    void swap(int a, int b);
    void downSort(int father);
    bool empty();
    void push(T data);
    void pop();

    
    
};

template <class T>
HeapIp<T>::HeapIp(){
}

template <class T>
HeapIp<T>::HeapIp(vector<T> list){  //hacer heap a una lista
    heap=list;
    int LastFather=list.size()/2-1;
    //recorro padres de derecha a izq
    while (LastFather>=0){ //cada padre
        downSort(LastFather);
        LastFather--;
    }
}

template <class T>
void HeapIp<T>::pop(){
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
void HeapIp<T>::downSort(int father) {
    int son1, son2, bigSon;
    while (father * 2 + 1 < heap.size()) {
        son1 = father * 2 + 1;
        if (father * 2 + 2 < heap.size()) {
            son2 = father * 2 + 2;
            heap[son1].counter>heap[son2].counter?bigSon=son1 : bigSon =son2;
        }else{
            bigSon=son1; //si solo hay 1 hijo
        }

        if (heap[father].counter < heap[bigSon].counter) {
            swap(father, bigSon);
            father = bigSon;
        } else {
            father = heap.size();
        }
    }
}


template <class T>
void HeapIp<T>::swap(int a, int b){
    T aux=heap[a];
    heap[a]=heap[b];
    heap[b]=aux;
}

template <class T>
HeapIp<T>::HeapIp(initializer_list<T> list){
    heap=list;
    int LastFather=list.size()/2-1;
    //recorro padres de derecha a izq
    while (LastFather>=0){ //cada padre
        downSort(LastFather);
        LastFather--;
    }
}

template <class T>
int HeapIp<T>::getSize(){
    return heap.size();
}

template <class T>
void HeapIp<T>::print(){
    int y=0;
    for (int i=0;i<10;i++){
        cout<<"IP: "<<heap[0].ip<<" Registros: "<<heap[0].counter<<endl;
        y++;
        heap.erase(heap.begin());
        int LastFather=heap.size()/2-1;
        //recorro padres de derecha a izq
        while (LastFather>=0){ //cada padre
        downSort(LastFather);
        LastFather--;
        }
        if(y==10){
            break;
         }
    }
}

template <class T>
bool HeapIp<T>::empty(){
    return heap.empty();
}

template <class T>
void HeapIp<T>::push(T data){
    heap.push_back(data);
    int LastFather=heap.size()/2-1;
    //recorro padres de derecha a izq
    while (LastFather>=0){ //cada padre
        downSort(LastFather);
        LastFather--;
    }
}



#endif 