/*
 * splay.h
 *
 *  Created on: 18/10/2021
 *      Author: Jordana Betancourt Menchaca A01707434
 */

#ifndef SplayTree_H_
#define SplayTree_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T> class SplayTree;

template <class T>
class Node {
private:
	T value;
	Node *left, *right, *parent;

	Node<T>* succesor();
	Node<T>* rot_right(Node<T>*);
	Node<T>* rot_left(Node<T>*);

public:
	Node(T);
	Node(T, Node<T>*, Node<T>* ,Node<T>*);

    //Implementaciones 
	Node<T>* add(T);
    Node<T>* remove(T);
	Node<T>* find(T);
	
    //Extras
	void removeChilds();
	void inorder(std::stringstream&) const;
	void print_tree(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	Node<T>* splay(Node<T>*, Node<T>*);

	friend class SplayTree<T>;
};

/*
 * Node Constructors 
 *
 * @param T val
 * @return Node<T>
 * 
*/
template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)
	: value(val), left(le), right(ri), parent(p) {}


//Add
/*
 * add 
 *
 * @param T val
 * @return Node<T>
 * 
*/
template <class T>
Node<T>* Node<T>::add(T val) {
    //Si el valor del nodo a insertar es menor que el valor de la raíz 
	if (val < value) {
        //Se inserta en la izquierda
		if (left != 0) {
			return left->add(val);
		} else {
            //Si la izquierda es null, se crea un nuevo nodo
			left = new Node<T>(val);
			left->parent = this;
			return left;
		}
        //Si el valor del nodo a insertar es mayor que el valor de la raíz 
	} else {
		if (right != 0) {
            //Se inserta en la derecha 
			return right->add(val);
		} else {
            //Si la derecha es null, se crea un nuevo nodo
			right = new Node<T>(val);
			right->parent = this;
			return right;
		}
	}
}

/*
 * find
 *
 * @param T val
 * @return Node<T>
 * 
*/
template <class T>
Node<T>* Node<T>::find(T val) {
    //Si el valor de la raíz es el valor que se busca se retorna
	if (val == value) {
		return this;
        //Si el valor es menor que el de la raíz recorremos hacía la izquierda
	} else if (val < value) {
		if (left != 0)
		 	return left->find(val);
		else
			return this;
        //Si el valor es mayor que el de la raíz recorremos hacía la derecha
	} else {
		if (right != 0)
		 	return right->find(val);
		else
			return this;
	}
}

template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;

	le = left;
	ri = right;

	if (right->left == 0) {
		right = right->right;
		ri->right = 0;
		return ri;
	}

	Node<T> *parent, *child;
	parent = right;
	child = right->left;
	while (child->left != 0) {
		parent = child;
		child = child->left;
	}
	parent->left = child->right;
	child->right = 0;
	return child;
}


/*
 * remove
 *
 * @param T val
 * @return Node<T>
 * 
*/
template <class T>
Node<T>* Node<T>::remove(T val) {
	Node<T> *succ, *old;
    //Para recorrer hacia la izquierda
	if (val < value) {
		if (left != 0) {
			if (left->value == val) {
				old = left;
				if(old->left != 0 && old->right != 0){ // Cuando hay dos hijos
					succ = left->succesor();
					if (succ != 0) {
						succ->left = old->left;
						succ->right = old->right;
						succ->parent = old->parent;
						if(succ->left)
							succ->left->parent = succ;
						if(succ->right)
							succ->right->parent = succ;
					}
					left = succ;
				} else if (old->right != 0){ // Solo un hijo en la dereha
					old->right->parent = left->parent;
					left = old->right;

				} else if (old->left != 0){ // Solo un hijo en la izquierda
					old->left->parent = left->parent;
					left = old->left;
				} else {  // Cuando es una hoja
					left = 0;
				}
				delete old;
				return this;
			} else {
				return left->remove(val);
			}
		}
        //Para recorrer hacia la derecha
	} else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				if(old->left != 0 && old->right != 0){ // Cuando tiene dos hijos
					succ = right->succesor();
					if (succ != 0) {
						succ->left = old->left;
						succ->right = old->right;
						succ->parent = old->parent;
						if(succ->left)
							succ->left->parent = succ;
						if(succ->right)
							succ->right->parent = succ;
					}
					right = succ;
				} else if (old->right != 0){ // Un hijo a la derecha
					old->right->parent = right->parent;
					right = old->right;

				} else if (old->left != 0){ // Un hijo a la izquierda
					old->left->parent = right->parent;
					right = old->left;
				} else {  // hoja
					right = 0;
				}
				delete old;
				return this;
			} else {
				return right->remove(val);
			}
		}
	}
	return this; // Para que no dé un warning de return
}


/*
 * removeChilds
 *
 * @param 
 * @return 
 * 
 */
template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

/*
 * rot_right
 *
 * @param Node<T> *
 * @return Node<T> *
 * 
 */
template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
	Node<T> *y = x->left;
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	y->right = x;
	// Enlazamos y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// Hacemos un enlace del padre de x a y
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

/*
 * rot_left
 *
 * @param Node<T> *
 * @return Node<T> *
 * 
 */
template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
	Node<T> *y = x->right;
	x->right = y->left;
	if(y->left)
		y->left->parent = x;
	y->left = x;
	// enlace de y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// hace enlace del padre de x a y
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

/*
 * splay
 *
 * @param Node<T> *root, Node<T> *x
 * @return Node<T> *
 * 
 */
template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
    //Mientas x siga teniendo un nodo padre
	while(x->parent != 0){
		if(x->parent->value == root->value){
			if(x->parent->left && x->parent->left->value == x->value){
				rot_right(x->parent);
			}else{
				rot_left(x->parent);
			}
		}else{
			Node<T>*p = x->parent; // Padre
			Node<T>*g = p->parent; // Abuelo
			if(p->left && g->left &&
				x->value == p->left->value && p->value == g->left->value){
				rot_right(g);
				rot_right(p);
			}else if(p->right && g->right &&
				x->value == p->right->value && p->value == g->right->value){
				rot_left(g);
				rot_left(p);
			}else	if(p->left && g->right &&
				x->value == p->left->value && p->value == g->right->value){
				rot_right(p);
				rot_left(g);
			}else{
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}

/*
 * print_tree
 *
 * @param stringstream
 * @return 
 * 
 */
template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << value;
		aux << " parent " << parent->value;
	}else
		aux << "\n root " << value;
	if (left != 0)
		aux << " left " << left->value;
	if (right != 0)
		aux << " right " << right->value;
	aux << "\n";

	if (left != 0) {
		left->print_tree(aux);
	}
	if (right != 0) {
		right->print_tree(aux);
	}
}

/*
 * inorder
 *
 * @param stringstream
 * @return
 * 
 */
template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

/*
 * preorder
 *
 * @param stringstream
 * @return
 * 
 */
template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
class SplayTree {
private:
	Node<T> *root;
    int tam;

public:
	SplayTree();
	~SplayTree();
	bool empty() const;
    //Implementaciones
	void add(T);
	bool find(T);
	void remove(T);
	void removeAll();
    int size();
    //Métodos para imprimir el árbol
	std::string inorder() const;
	std::string print_tree() const;
	std::string preorder() const;
};

/*
 * SplayTree Constructor Default
 *
 * @param 
 * @return 
 * 
*/
template <class T>
SplayTree<T>::SplayTree() : root(0), tam(0) {}

/*
 * SplayTree Destructor
 *
 * @param 
 * @return 
 * 
*/
template <class T>
SplayTree<T>::~SplayTree() {
	removeAll();
}

/*
 * empty
 *
 * @param 
 * @return bool
 * 
*/
template <class T>
bool SplayTree<T>::empty() const {
	return (root == 0);
}

//Add
/*
 * add 
 *
 * @param T val
 * @return 
 * 
*/
template<class T>
void SplayTree<T>::add(T val) {

    //Si existe más de un nodo en el árbol
	if (root != 0) {
			Node<T>* added = root->add(val);
			root = root->splay(root,added);
    //Si no existen nodos
	} else {
		root = new Node<T>(val);
	}
    // Aumentamos el tamaño en uno
    tam ++;
}


//Remove
/*
 * remove
 *
 * @param T val
 * @return 
 * 
*/
template <class T>
void SplayTree<T>::remove(T val) {
	if (root != 0) {
        //Si el valor a eliminar es el nodo de la raíz
		if (val == root->value) {
            //Al no tener padre ni abuelo tenemos que encontrar su sucesor
			Node<T> *succ = root->succesor();
			if (succ != 0) {
					succ->left = root->left;
					succ->right = root->right;
					succ->parent = 0;
					if(succ->left)
						succ->left->parent = succ;
					if(succ->right)
						succ->right->parent = succ;
			}
            //Colocamos a su sucesor como la nueva raíz 
			delete root;
			root = succ;
        //De otra forma (Que el nodo con el valor a eliminar tenga Padre y/o abuelo)
		} else {
            //Creamos un nodo que llama a la función remove de clase Nodo<T>
			Node<T>* p = root->remove(val);
            //Acomodamos el árbol con splay
			root = root->splay(root,p);
		}
	}
    //Decrementamos el tamaño en uno
    tam --;
}

//Find
/*
 * find
 *
 * @param T val
 * @return bool
 * 
*/
template <class T>
bool SplayTree<T>::find(T val){
    //Si hay al menos un elemento en root
	if (root != 0) {
        //Llamamos a find de clase Node<T>
		Node<T>* found = root->find(val);
		root = root->splay(root,found);
		return (root->value == val);
    //Si no, directamente false
	} else {
		return false;
	}
}

//Size
/*
 * size
 *
 * @param 
 * @return int
 * 
*/
template <class T>
int SplayTree<T>::size(){
    return tam;

}

/*
 * removeAll
 *
 * @param 
 * @return 
 * 
*/
template <class T>
void SplayTree<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
    tam = 0;
}

//Métodos para imprimir el árbol
/*
 * print_tree
 *
 * @param 
 * @return string
 * 
*/
template <class T>
std::string SplayTree<T>::print_tree() const {
	std::stringstream aux;

	aux << "\n ================================ ";
	if (!empty()) {
		root->print_tree(aux);
	}
	aux << " ================================ \n";
	return aux.str();
}

/*
 * inorder
 *
 * @param 
 * @return string
 * 
*/
template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

/*
 * preorder
 *
 * @param 
 * @return string
 * 
*/
template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}


#endif /* SplayTree_H_ */
