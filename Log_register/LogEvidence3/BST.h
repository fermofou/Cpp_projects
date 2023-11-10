#ifndef BST_h
#define BST_h

#include "TNode.h"

template <class T>
class BST {
private:
    TNode<T>* root;
    void printTree(TNode<T>* aux, int level);
public:
    BST();
    void insert(T data);
    int find(string data);
    void print();
    bool isEmpty();
    int children(TNode<T>* aux);
    bool remove(T data);
    int whatLevelAmI(T data);
    void ancestors(T data);
    void height();
    int heightRecursiva(TNode<T>* node);
    void visit(int index);
    void printInorder(TNode<T>* node);
    void printPreOrder(TNode<T>* node);
    void printPostOrder(TNode<T>* node);
    int countLogs(string targetIp);
    void countLogsRecursive(TNode<T>* node, string targetIp, int& count);
   
};

template <class T>
BST<T>::BST() {
    root = nullptr;
}

template <class T>
int BST<T>::countLogs(string targetIp) {
    int count = 0; // Inicializar el contador una vez
    countLogsRecursive(root, targetIp, count);
    return count;
}

template <class T>
void BST<T>::countLogsRecursive(TNode<T>* node, string targetIp, int& count) {
    if (node == nullptr) {
        return;
    }
    
    if (node->data.ip == targetIp) {
        count++; // Aumentar el contador cuando se encuentra una IP coincidente
    }
    
    countLogsRecursive(node->left, targetIp, count);
    countLogsRecursive(node->right, targetIp, count);
    return;
}




template <class T>
void BST<T>::insert(T data) {
    // Validamos si el arbol esta vacío
    if (isEmpty()) {
        // El árbol está vacío
        // root va a ser igual a un nuevo nodo con el valor de data
        root = new TNode<T>(data);
    } else {
        // El arbol no está vacío
        // Creamos un apuntador auxiliar apuntado a roor
        TNode<T>* aux = root;
        // Iteramos el árbol hasta poder insertar el valor nuevo (aux != nullptr)
        while (aux != nullptr) {  
            // Comparamos si data es menor a aux->data
            if (data < aux->data) {
                // si es menor
                // Validamos si el apuntador del lado izquierdo de aux es nulo
                if (aux->left == nullptr) {
                      
                    // si es nulo
                    // aux->left va a ser igual a nuevo nodo con el valor de data
                    aux->left = new TNode<T>(data);
                    aux->left->parent = aux;
                    // nos salimos de la función
                    return;
                } else {
                    // no es nulo
                    // Recorremos aux hacia aux->left
                    aux = aux->left;
                }
            } else {
                // es mayor o igual
                // Validamos si el apuntador del lado derecho de aux es nulo
                if (aux->right == nullptr) {
                    // si es nulo
                    // aux->right va a ser igual a nuevo nodo con el valor de data
                    aux->right = new TNode<T>(data);
                    aux->right->parent=aux;
                    // nos salimos de la función
                    return;
                } else {
                    // no es nulo
                    // Recorremos aux hacia aux->right
                    aux = aux->right;
                }
            }
        }
    }
}

template <class T>
int BST<T>::find(string data) {
    int counter=0;
    // Creamos un apuntador auxiliar igual a root
    TNode<T>* aux = root;
    // Recorremos el árbol para buscar data
    while (aux != nullptr) {
        const Log& log = aux->data;
        // Validamos si data a igual aux->data
        if (log.ip == data) {
            counter++;
        } 
        data < log.ip ? aux = aux->left : aux = aux->right;
    }
    // No lo encontramos
    return counter;
}

// Regresa la cantidad de hijos del nodo
template <class T>
int  BST<T>::children(TNode<T>* aux) {
    if(aux->left==nullptr && aux->right==nullptr){
        return 0;
    }else if(aux->left!=nullptr && aux->right!=nullptr){
        return 2;
    }else{
        return 1;
    }
}

template <class T>
bool BST<T>::remove(T data) {
    TNode<T>* aux = root;
    // Buscar el nodo 
    // Recorremos el árbol para buscar data
    while (aux != nullptr) {
        // Validamos si data a igual aux->data
        if (aux->data == data) {
            int numb= children(aux);
            // Reviso la cantidad de hijos
            if (numb==0){      // Nodo con 0 hijos
                if(aux->data<aux->parent->data){ // si el nodo a borrar es menor que el padre
                    aux->parent->left=nullptr; // el apuntador del lado izquierdo del padre va a ser igual a nullptr
                }else{            // si el nodo a borrar es mayor o igual que el padre
                    aux->parent->right=nullptr; 
                }   
                aux=nullptr;// Nodo root igual a nullptr
                delete aux; // borro el nodo
                return true;
            }else if(numb==1){ // Nodo con 1 hijo
                if(aux->left!=nullptr){ //si el hijo esta a la izq
                    if(aux->data<aux->parent->data){ // si el nodo a borrar es menor que el padre
                        aux->parent->left=aux->left; // el apuntador del lado izquierdo del padre va a ser igual a izq del hijo
                        aux->left->parent=aux->parent;
                    }else{            // si el nodo a borrar es mayor o igual que el padre
                        aux->parent->right=aux->left;
                        aux->left->parent=aux->parent;
                    }
                }else{ //si el hijo esta a la derecha
                    if(aux->data<aux->parent->data){ // si el nodo a borrar es menor que el padre
                        aux->parent->left=aux->right; // el apuntador del lado izquierdo del padre va a ser igual a derecha del hijo
                        aux->right->parent=aux->parent;
                    }else{            // si el nodo a borrar es mayor o igual que el padre, es el d la derecha
                        aux->parent->right=aux->right; 
                        aux->right->parent=aux->parent;
                    }
                }
                aux=nullptr;// Nodo root igual a nullptr
                delete aux; // borro el nodo
                return true; 
            }else if (numb==2){ // Nodo con 2 hijos
                TNode<T>* auxTwo=aux->left;
                while(auxTwo->right!=nullptr){ // Buscamos el nodo más grande del lado izquierdo
                    auxTwo=auxTwo->right;
                }
                if(auxTwo->left!=nullptr){
                    auxTwo->parent->right=auxTwo->left; //si el nodo tiene hijo menor toma su lugar
                    auxTwo->left->parent=auxTwo->parent;
                }else{
                    auxTwo->parent->right=nullptr; //si esta solo, el papa se queda sin right
                }
                //empiezo a cambiar pointers del a borrar
                if(aux->parent!=nullptr){
                    if(auxTwo->data<aux->parent->data){ // si el nodo a borrar es menor que el padre
                        aux->parent->left=auxTwo;
                    }else{            // si el nodo a borrar es mayor o igual que el padre
                        aux->parent->right=auxTwo; 
                    }
                }else{
                root = auxTwo;
                }
                auxTwo->left=aux->left; //paso valores d izq y derecha a nuevo aux
                auxTwo->right=aux->right;
                auxTwo->left->parent=auxTwo; //derecha y izq guardan auxTwo como parent
                auxTwo->right->parent=auxTwo;
                aux=nullptr;// Nodo root igual a nullptr
                delete aux; // borro el nodo
                return true;
                }
               

            



        } else {
            data < aux->data ? aux = aux->left : aux = aux->right;
        }
    }
    return false;

}

template<class T>
void BST<T>::printTree(TNode<T>* aux, int level) {
    if (aux != NULL) {
        printTree(aux->right,level+1);
        for (int i=0;i<level;i++) {
            cout << "  ";
        }
        cout << aux->data << endl;
        printTree(aux->left,level+1);
    }
}

template<class T>
void BST<T>::print() {
    if (!isEmpty()) {
        int level = 0;
        cout << endl;
        printTree(root, level);
        cout << endl;
    } else {
        cout << endl << "The BST is empty" << endl << endl;
    }
} 

template <class T>
bool BST<T>::isEmpty() {
    return root == nullptr;
}

template <class T>
int  BST<T>::whatLevelAmI(T data) {
    TNode<T>* aux = root;
    int count=0;
    // Recorremos el árbol para buscar data
    while (aux != nullptr) {
        // Validamos si data a igual aux->data
        if (aux->data == data) {
            while(aux->parent!=nullptr){
                count++;
                 aux = aux->parent;
            }
            return count;
        } else {
            data < aux->data ? aux = aux->left : aux = aux->right;
        }
    }
    // No lo encontramos
    return -1;

}


template <class T>
void BST<T>::visit(int index) {
    if (index==1){ 
        printPreOrder(root);
    }else if (index==2){
         cout<<"in orden"<<endl;
         printInorder(root);
    }else if (index==3){
         cout<<"post orden"<<endl;
         printPostOrder(root);
    }else if (index==4){
        /* code */
    }else{
        cout<<"opcion incorrecta"<<endl;
    }
}


template <class T>
void BST<T>::printInorder(TNode<T>* node){
    if (node == NULL)
        return;
    printInorder(node->left); //izq
    cout << node->data << " "; //imprimo
    printInorder(node->right); //derecha
}

template <class T>
void BST<T>::printPreOrder(TNode<T>* node){
    if (node == NULL)
        return;
    cout << node->data << " "; //imprimo
    printPreOrder(node->left); //izq
    printPreOrder(node->right); //derecha
}

template <class T>
void BST<T>::printPostOrder(TNode<T>* node){
    if (node == NULL)
        return;
    printPostOrder(node->left);//izq
    printPostOrder(node->right);//der
    cout << node->data << " "; //imprimo
}



template <class T>
void BST<T>::ancestors(T data) {
    TNode<T>* aux = root;
    bool found = false;
    while (aux != nullptr) {
        if (aux->data == data) {
            found = true;
            break; 
        } else {
            data < aux->data ? aux = aux->left : aux = aux->right;
        }
    }
    if (found) { //solo si es true
        while (aux->parent != nullptr) {
            aux = aux->parent;
            cout << aux->data;
            if (aux->parent != nullptr) { //evito imprimir <- extra
                cout << " <- ";
            }
        }
        cout << endl;
    } else {
        cout << "no se encontro "<< data << endl;
    }
}

template <class T>
void BST<T>::height() {
   int max= heightRecursiva(root);
    cout<<"altura es de "<<max<<endl;
   
}

template <class T>
int BST<T>::heightRecursiva(TNode<T>* node) {
    if (node == nullptr) {
        return 0; // si esta vacia es 0
    }

    int leftHeight = heightRecursiva(node->left);
    int rightHeight = heightRecursiva(node->right);

    // Return the maximum of left and right subtree heights, plus 1 for the current node
    return std::max(leftHeight, rightHeight) + 1;
}



#endif /* BST_h */