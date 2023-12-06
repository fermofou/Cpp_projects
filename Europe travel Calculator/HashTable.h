#ifndef HashTable_h
#define HashTable_h

#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Graph;

template <class T>  
class HashTable{
private:
    vector <string> table;
    int hash (string data);
public:
    HashTable();
    void insert(string data);
    int findData(string data);
    void delet(string data);
    friend class Graph<T>;
};

template <class T>  
HashTable<T>::HashTable(){
    table.resize(82); 
}

template <class T>  
int HashTable<T>::hash(string data){
    int hashValue = 0;
    for (char ch : data) {
        hashValue += static_cast<int>(ch);
    }
    return hashValue % 81;

}

template <class T>  
void HashTable<T>::insert(string data) {
    int check = findData(data);
    if (check != -1) {
        return; // Data already in table
    } else {
        int index = hash(data);
        int og = index;
        
        while (table[index] != "") {
            index = (index + 1) % 82; // Adjust the size if needed
            if (index == og) {
                // Handle the case where the table is full
                throw overflow_error("HashTable is full");
            }
        }
        table[index] = data;
        // cout << data << " inserted at index " << index << endl;
    }
}


template <class T>  
void HashTable<T>::delet(string data){
    int index=hash(data);
    if (table[index]==data){
        table[index]="";
        cout<<"deleted"<<endl;
    }else{
        int og=index;
        while (index!=og){
            index++;
            if (table[index]==data){
                table[index]="";
                cout<<"deleted"<<endl;
                break;
            }
            if (index==99){
                index=-1;
            }
        }
        cout<<"data not deleted"<<endl;
    }
}

template <class T>  
int HashTable<T>::findData(string data){
    int index= hash(data);
    if (table[index]==data){
        return index;
    }else{
        int og=index;
        while (index!=og){
            index++;
            if (table[index]==data){
                return index;
            }
            if (index==82){
                index=-1;
            }
        }
        return -1;
    }
}



#endif /*HashTable_h*/