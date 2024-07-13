//
// Created by Badi on 7/13/2024.
//

#include <iostream>

using namespace std;

struct Nodo {
    int dato;
    Nodo* left;
    Nodo* right;

    // Constructor
    Nodo(int dato) {
        this->dato = dato;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Nodo* raiz=nullptr;
    Nodo* insertarNodoAux(Nodo* nodo, int dato);
    Nodo* buscarNodoAux(Nodo* nodo, int dato);
    int heightAux(Nodo* nodo);
    Nodo* minimoAux(Nodo* nodo_raiz);
    bool esArbolAVLAux(Nodo* nodo);
public:
    void insertarNodo(int dato);
    Nodo* buscarNodo(int dato);
    int height();
    int minimo();
    int maximo();
    Nodo* Sucesor(int dato);
    bool esArbolAVL();
};

void BST::insertarNodo(int dato) {
    raiz = insertarNodoAux(raiz, dato);
}

// Función auxiliar para insertar un nodo en el árbol
Nodo* BST::insertarNodoAux(Nodo* nodo, int dato) {
    if (nodo == nullptr)
        return new Nodo(dato);

    if (dato < nodo->dato)
        nodo->left = insertarNodoAux(nodo->left, dato);
    else
        nodo->right = insertarNodoAux(nodo->right, dato);
    return nodo;
}

Nodo* BST::buscarNodo(int dato) {
    return buscarNodoAux(raiz, dato);
}

// Función auxiliar para buscar un nodo en el árbol
Nodo* BST::buscarNodoAux(Nodo* nodo, int dato) {
    if (nodo == nullptr || nodo->dato == dato)
        return nodo;

    if (dato < nodo->dato)
        return buscarNodoAux(nodo->left, dato);
    else
        return buscarNodoAux(nodo->right, dato);
}

int BST::height() {
    return heightAux(raiz);
}

int BST::heightAux(Nodo* nodo) {
    if (nodo == nullptr) {
        return -1;
    }
    return 1 + max(heightAux(nodo->left), heightAux(nodo->right));
}

Nodo* BST::minimoAux(Nodo* nodo_raiz){
    Nodo* nodo = nodo_raiz;
    while(nodo->left != nullptr){
        nodo = nodo->left;
    }
    return nodo;
}

int BST::minimo(){
    Nodo* nodo = raiz;
    while(nodo->left != nullptr){
        nodo = nodo->left;
    }
    return nodo->dato;
}

int BST::maximo(){
    Nodo* nodo = raiz;
    while(nodo->right != nullptr){
        nodo = nodo->right;
    }
    return nodo->dato;
}
Nodo* BST::Sucesor(int dato){
    Nodo* nodo = buscarNodo(dato);
    if(nodo == nullptr) // El dato no se encuentra en el arbol
        return nullptr;
    if(nodo->right != nullptr)
        return minimoAux(nodo->right);

    Nodo* sucesor = nullptr;
    Nodo* ancestro = raiz;

    while (ancestro != nodo){
        if(dato < ancestro->dato){
            sucesor = ancestro;
            ancestro = ancestro->left;
        }
        else
            ancestro = ancestro->right;
    }
    return sucesor;
}

bool BST::esArbolAVL(){
    return esArbolAVLAux(raiz);
}
bool BST::esArbolAVLAux(Nodo* nodo){
    if (nodo == nullptr)
        return true;

    int h1 = heightAux(nodo->left);
    int h2 = heightAux(nodo->right);
    if (abs(h1 - h2) > 1)
        return false;
    return esArbolAVLAux(nodo->left) and esArbolAVLAux(nodo->right);
}