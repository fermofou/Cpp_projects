#ifndef doubleLink_h
#define doubleLink_h

#include "Node.h"
#include "Log.h"

template<class T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;  

public:
    LinkedList();
    void addFirst(T data);
    void addLast(T data);
    int getSize();
    bool isEmpty();
    void insert(T data, int index);
    int findData(Log data);
   
    void deleteAll();
    void quickSort(Node<T>* head);
    void _quickSort(Node<T>* l, Node<T>* h);
    Node<T>* partition(Node<T>* l, Node<T>* h);

    void quickSort2(Node<T>* head);
    void _quickSort2(Node<T>* l, Node<T>* h);
    Node<T>* partition2(Node<T>* l, Node<T>* h);

    Node<T>* getHead() const {
        return head;
    }
    Node<T>* getTail() const {
        return tail;
    }
    void push(Log data);
    string addZero(const string& str);
    string ipGen(Log log);
    void printList(Node<T> *head);

};
template<class T>
void LinkedList<T>::printList(Node<T> *head) { 
    while (head) 
    { 
        cout << head->data << " "; 
        head = head->next; 
    } 
    cout << endl; 
} 
 template<class T>
void LinkedList<T>::push(Log data) {
    Node<T>* new_node = new Node(data);
    new_node->prev = nullptr;
    new_node->next = head;

    if (head == nullptr) {
        
        head = tail = new_node;
    } else {
       
        head->prev = new_node;
       
        head = new_node;
    }
    size++;
}


template<class T>
    Node<T>* LinkedList<T>::partition(Node<T>* l, Node<T>* h) {
    string x = h->data.key1;
    Node<T>* i = l->prev;
    for (Node<T>* j = l; j != h; j = j->next) {
        if (j->data.key1 <= x) {
            i = (i == nullptr) ? l : i->next;
            swap(i->data, j->data);
        }
    }
    i = (i == nullptr) ? l : i->next;
    swap(i->data, h->data);
    return i;
}

template<class T>
void LinkedList<T>::_quickSort(Node<T>* l, Node<T>* h) {
    if (h != nullptr && l != h && l != h->next) {
        Node<T>* p = partition(l, h);
        _quickSort(l, p->prev);
        _quickSort(p->next, h);
    }
}

template<class T>
void LinkedList<T>::quickSort(Node<T>* head) {
    Node<T>*h = lastNode(head);
    _quickSort(head, h);
}

template<class T>
    Node<T>* LinkedList<T>::partition2(Node<T>* l, Node<T>* h) {
    string x = h->data.key2;
    Node<T>* i = l->prev;
    for (Node<T>* j = l; j != h; j = j->next) {
        if (j->data.key2 <= x) {
            i = (i == nullptr) ? l : i->next;
            swap(i->data, j->data);
        }
    }
    i = (i == nullptr) ? l : i->next;
    swap(i->data, h->data);
    return i;
}

template<class T>
void LinkedList<T>::_quickSort2(Node<T>* l, Node<T>* h) {
    if (h != nullptr && l != h && l != h->next) {
        Node<T>* p = partition2(l, h);
        _quickSort2(l, p->prev);
        _quickSort2(p->next, h);
    }
}

template<class T>
void LinkedList<T>::quickSort2(Node<T>* head) {
    Node<T>*h = lastNode(head);
    _quickSort2(head, h);
}



template<class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<class T>
int LinkedList<T>::getSize() {
    return size;
}

template<class T>
void LinkedList<T>::addFirst(T data) {
    head = new Node<T>(data, nullptr, head);
    size++;
    if (size==1){
        tail=head;
    }
}

template<class T>
void LinkedList<T>::addLast(T data) {
    if (isEmpty()) {
        head = tail = new Node<T>(data);
    } else {
        tail->next = new Node<T>(data, nullptr, tail);
        tail = tail->next;
    }

    size++;
}

template<class T>
int LinkedList<T>::findData(Log data) {
    Node<Log>* current = head;
    int position = 0;
    string buscar= ipGen(data);
    while (current != nullptr) {
        const Log& log = current->data;
        string comparar = ipGen(log);
        if (buscar <= comparar) {
            cout << "esta en posicion: " << position << endl;
            return position;
        }

        current = current->next;
        position++;
    }
    return position;
}


template<class T>
bool LinkedList<T>::isEmpty() {
    return size == 0;
}



template<class T>
void LinkedList<T>::insert(T data, int index) {
    if (index < 0 || index > size) {
        cout << "Index not available" << endl;
        return;
    }

    if (index == 0) {
        addFirst(data);
    } else if (index == size) {
        addLast(data);
    } else {
        Node<T>* current = head;
        int currentIndex = 0;

        while (currentIndex < index - 1) {
            current = current->next;
            currentIndex++;
        }

        current->next = new Node<T>(data, current->next, current);
        current->next->next->prev = current->next;

        size++;
    }
}



template<class T>
void LinkedList<T>::deleteAll() {
    Node<T>* current = head;

    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }

    head = tail = nullptr;
    size = 0;
}


template<class T>
string LinkedList<T>::addZero(const string& str) {
    if (str.length() < 3) {
        return string(3 - str.length(), '0') + str;
    }
    return str;
}
template<class T>
string LinkedList<T>::ipGen(Log log) {
    string ipcopy=log.ip;
    size_t start = 0;
    
    vector<string> sections;
    string formattedIp;
    size_t end = ipcopy.find('.');
    while (end != string::npos) {
        sections.push_back(ipcopy.substr(start, end - start));
        start = end + 1;
            end = ipcopy.find('.', start);
        }
        sections.push_back(ipcopy.substr(start));
        for (const string& section : sections) {

            formattedIp += addZero(section) + ".";
            formattedIp.pop_back();
            }
    ipcopy=formattedIp;
    ipcopy.erase(std::remove(ipcopy.begin(), ipcopy.end(), '.'), ipcopy.end());
    string key2= ipcopy.erase(0,6);
    return key2;
}




#endif