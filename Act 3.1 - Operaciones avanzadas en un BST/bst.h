/*
 * bst.h
 *
 *  Created on: 13/10/2021
 *      Author: Jordana Betancourt Menchaca
 */

#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T> class BST;

template <class T>
class Node {
private:
	T value;
	Node *left, *right;

	Node<T>* succesor();
    

public:
	Node(T);
	Node(T, Node<T>*, Node<T>*);
	void add(T);
	bool find(T);
	void remove(T);
	void removeChilds();
	std::string antesesor(T,Node<T>);
	//Implementaciones
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
    void postorder(std::stringstream&) const;
    void levelByLevel(int,std::stringstream&) const;
    int max_depth();
    void printAncestors(std::stringstream &aux,T val);

	friend class BST<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri)
	: value(val), left(le), right(ri) {}

template <class T>
void Node<T>::add(T val) {
	if (val < value) {
		if (left != 0) {
			left->add(val);
		} else {
			left = new Node<T>(val);
		}
	} else {
		if (right != 0) {
			right->add(val);
		} else {
			right = new Node<T>(val);
		}
	}
}

template <class T>
bool Node<T>::find(T val) {
	if (val == value) {
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else if (val > value) {
		return (right != 0 && right->find(val));
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


template <class T>
void Node<T>::remove(T val) {
	Node<T> * succ, *old;

	if (val < value) {
		if (left != 0) {
			if (left->value == val) {
				old = left;
				if(old->left != 0 && old->right != 0){
					succ = left->succesor();
					if (succ != 0) {
						succ->left = old->left;
						succ->right = old->right;
					}
					left = succ;
				} else if (old->right != 0){ // solo hijo der
						left = old->right;
				} else if (old->left != 0){ // solo hijo izq
						left = old->left;
				} else {
						left = 0;
				}
				delete old;
			} else {
				left->remove(val);
			}
		}
	} else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				if(old->left != 0 && old->right != 0){ // dos hijos sucesor
					succ = right->succesor();
					if (succ != 0) {
						succ->left = old->left;
						succ->right = old->right;
					}
					right = succ;
				} else if (old->right != 0){ // solo hijo der
					right = old->right;
				} else if (old->left != 0){ // solo hijo izq
					right = old->left;
				} else {  // hoja
					right = 0;
				}
					delete old;
			} else {
				right->remove(val);
			}
		}
	}
}


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

//Recorrido en indorder
/*
 * inorder
 *
 * @param stringstream &aux
 * @return 
 * 
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

//Recorrido en preorder
/*
 * preorden
 *
 * @param stringstream &aux
 * @return 
 * 
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

//Recorrido en postorder
/*
 * postorder
 *
 * @param stringstream &aux
 * @return 
 * 
 * 
*/
template <class T>
void Node<T>::postorder(std::stringstream &aux) const {
    	
	if (left != 0) {
		left->postorder(aux);
        aux<<" ";
	}
   	if (right != 0) {
		right->postorder(aux);
        aux<<" ";
	}
    aux << value;
}

//Recorrido en levelByLevel
/*
 * levelBylevel
 *
 * @param stringstream &aux
 * @return 
 * 
 * 
*/
template <class T>
void Node<T>::levelByLevel(int level_no,std::stringstream &aux) const {
    
	if (level_no == 1) {
        //Caso base, nos encontramos en la raíz del árbol
		//Para que no agregue espacio al final de toda la recursión
		if(aux.tellp() != 1){
			aux<< " ";
		}
        aux << value;
	    
    } 
	level_no --;
	
	//Para ver si existe otro nodo a la izquierda
	if (left != 0){
		left->levelByLevel( level_no ,aux);	
	}
	//Para ver si existe otro nodo a la derecha
	if (right != 0){
		right->levelByLevel(level_no,aux);		
	}	
       
}


/*
 * max_depth
 *
 * @param 
 * @return int
 * 
 * 
*/
template <class T>
int Node<T>::max_depth() {
    //Inicializamos en 1, ya que si solo se tiene la raíz (caso base)
    // su altura es 1
	int le =1 , ri = 1, level = 0;

    //Si en el apuntador izquierdo es diferente a 0
	if (left != 0)
        //A le le sumanos 1
		le = left->max_depth() + 1;
    //Si en el apuntador izquierdo es diferente a 0
	if (right != 0)
        //A ri le sumanos 1
		ri = right->max_depth() + 1;
    //Verificamos si izquierda o derecha tiene más niveles
	if(le > ri)
		level = le;
	else
		level = ri;
    //Regresamos el nivel
	return level;
}


/*
 * printAncestors
 *
 * @param stringstream, T
 * @return
 * 
 * 
*/
template <class T>
void Node<T>:: printAncestors(std::stringstream &aux,T val)
{
  
	if(val< value){
		if(left  != 0){
			if(aux.tellp() != 1){
			 aux << " ";
			}
			aux << value;
			left->printAncestors(aux,val);
		}
	}
	else if (val> value){
		if(right != 0){
			if(aux.tellp() != 1){
			 aux << " ";
			}
			aux << value;
			right->printAncestors(aux,val);
		}

	}

}


template <class T>
class BST {
private:
	Node<T> *root;

public:
	BST();
	~BST();
	bool empty() const;
	void add(T);
	bool find(T) const;
	void remove(T);
	void removeAll();
	std::string inorder() const;
	std::string preorder() const;
    std::string postorder() const;
    std::string levelByLevel() const;
    void print_level(Node<T>* ,int,std::stringstream &);
    std::string visit() const;
    int height();
    std::string ancestors(T);
    bool printAncestors(std::stringstream &aux,T, Node<T>*);
    int findLevel(Node<T>*, int, T );
    int whatlevelamI(T);
	void levelBy(int,std::stringstream&) const;
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template<class T>
void BST<T>::add(T val) {
	if (root != 0) {
		if (!root->find(val)) {
			root->add(val);
		}
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
void BST<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != 0) {
				succ->left = root->left;
				succ->right = root->right;
			}
			delete root;
			root = succ;
		} else {
			root->remove(val);
		}
	}
}

template <class T>
void BST<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool BST<T>::find(T val) const {
	if (root != 0) {
		return root->find(val);
	} else {
		return false;
	}
}

/*
 * inorder
 *
 * @param 
 * @return string
 * 
*/
template <class T>
std::string BST<T>::inorder() const {
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
std::string BST<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}
/*
 * postorder
 *
 * @param 
 * @return string
 * 
*/
template <class T>
std::string BST<T>::postorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}
/*
 * levelBylevel
 *
 * @param 
 * @return string
 * 
*/
template <class T>
std::string BST<T>::levelByLevel() const {
	std::stringstream aux;
    int level = root->max_depth();
	
	aux << "[";
	if (!empty()) {
        for (int i = 1; i <= level; i++) {
           root->levelByLevel(i, aux);
		   
        }

	}
	aux << "]";
	return aux.str();
}
/*
 * visit
 *
 * @param 
 * @return string
 * 
*/
template <class T>
std::string BST<T>::visit() const {
	std::stringstream aux;
    //Preorder
    aux << preorder();
    aux << "\n";

    //Inorder
    aux << inorder();
    aux << "\n";

    //Postorder
    aux << postorder();
    aux << "\n";

	//Level by level
    aux << levelByLevel();
    
	return aux.str();
}

//Para calcular la altura del árbol
/*
 * heigth
 *
 * @param 
 * @return int
 * 
*/
template <class T>
int BST<T>::height() {
    
   return root->max_depth();
     
}

/*
 * ancestors
 *
 * @param T
 * @return string
 * 
 * 
*/
template <class T>
std::string BST<T>:: ancestors(T val){
    std::stringstream aux;
    
	if (find(val) == true){
		aux << "[";
    	if (!empty()) {
			root->printAncestors(aux,val);
			
		}
		aux << "]";
	}
	else{
		aux << "[]";
	}
   
    return aux.str();
}

/*
 * findLevel
 *
 * @param Node<T>,int, T
 * @return int
 * 
*/
template <class T>
int BST<T>:: findLevel(Node<T>* root, int level, T val){
    
        if(root == NULL)
            return -1;
        if(root->value == val)
            return level;
        // Si es null o una hoja
        if(root->left == NULL && root->right == NULL)
            return -1;
        // Encontrar si el valor está en la izquierda o derecha del árbol
        int levelLeft = findLevel(root->left, level+1,val);
        int levelRight = findLevel(root->right, level+1,val);
        if(levelLeft == -1)
            return levelRight;
        else
            return levelLeft;
}

/*
 * whatlevelamI
 *
 * @param T val
 * @return int
 * 
*/
template <class T>
int BST<T>:: whatlevelamI(T val){
    //Tomamos al nivel de la raíz como 1
    int level = 1;
   
    return findLevel(root,level,val);
}


#endif /* BST_H_ */