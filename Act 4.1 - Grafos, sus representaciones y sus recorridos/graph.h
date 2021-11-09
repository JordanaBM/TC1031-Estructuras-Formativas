/*
*  autor: Benjamin Valdes Aguirre y Jordana Betancourt Menchaca A01707434
*  fecha: 9 de noviembre de 2021
*  programa: act 4.1 Implementacion Grafos
*  desc: estos programas son soluciones parciales a algunos de
*  las actividades planteadas en el curso TC1031
*
*
*  Extiende este archivo para completar tu solución.
*/

#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;


class Graph {
private:
		int edgesList;
		int aux;
		int edgesMat;
		int nodes;
    vector<int> *adjList;
		int *adjMatrix;
		//vector<Type> *vect = new vector<Type>

public:
		void loadGraphMat(string, int, int);
		Graph(int);
		Graph();
		void addEdgeAdjMatrix(int, int);
		void addEdgeAdjList(int,int);
		string printAdjMat();
		string printAdjList();
		string printAdjMat_clean();
		bool contains(list<int>, int);
		void sortAdjList();
		//Implementaciones
		void loadGraphList(string, int, int);
		//DFS
		string DFS(int, int);
		void dfsHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&,std::stringstream &aux);
		//BFS
		string BFS(int, int);
		void bfsHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&,std::stringstream &aux);
		//Print
		string print_visited(list<int>);
		string print_path(vector<vector<int>>&,int ,int);

};

/*
 * loadGraphMat 
 *
 * @param string,int, int
 * @return void
 * 
*/
void Graph::loadGraphMat(string name, int m, int n){
	adjMatrix = new int [m*n];
	nodes = m;
	for (int i = 0; i < m*n; i++)
		adjMatrix[i] = 0;
		string line;
		ifstream lee (name);
		int u, v;
		if (lee.is_open()){
			while (getline(lee, line)){
				u = stoi(line.substr(1,1));
				v = stoi(line.substr(4,1));
				addEdgeAdjMatrix(u,v);
			}
			lee.close(); // Closes the file
		} else {
			cout << "Unable to open file";
		}
}

//Implementación
/*
 * loadGraphList
 *
 * @param string,int, int
 * @return Node<T>
 * 
*/
void Graph:: loadGraphList (string name, int m, int n){
	nodes = m;
	adjList = new vector<int>[nodes];
	for (int i = 0; i < m; i++)
		aux = 0;
		string line;
		ifstream lee (name);
		int u, v;
		if (lee.is_open()){
			while (getline(lee, line)){
				// Stoi cambia de string a int
				u = stoi(line.substr(1,1));
				v = stoi(line.substr(4,1));
				addEdgeAdjList(u,v);
			}
			lee.close(); // Closes the file
		} else {
			cout << "Unable to open file";
		}
}

/*
 * Graph
 *
 * @param 
 * @return Graph
 * 
*/
Graph::Graph() {
	edgesList = edgesMat = 0;
}

/*
 * Graph
 *
 * @param int
 * @return Graph
 * 
*/
Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		//Llenamos toda la matriz de 0
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

/*
 * addEdgeAdjMatrix
 *
 * @param int, int
 * @return 
 * 
*/
void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

/*
 * addEdgeAdjList
 *
 * @param int, int
 * @return 
 * 
*/
void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

/*
 * printAdjList
 *
 * @param
 * @return string
 * 
*/
string Graph::printAdjList(){
	//Ciclo para acomodar la lista de menor a mayor
	for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(),adjList[i].end());
	//Ciclo para agregar al aux los elementos de la lista
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}

/*
 * printAdjMat
 *
 * @param
 * @return string
 * 
*/
string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

/*
 * printAdjMat_clean
 *
 * @param
 * @return string
 * 
*/
string Graph::printAdjMat_clean(){
	stringstream aux;
	aux << "\n nodes \t|";
	for (int i = 0; i < nodes; i++){
			aux << "\t" << i ;
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
			aux << "__________";
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
		 aux << i << "\t|";
	   for (int j = 0; j < nodes; j++){
			 aux << "\t" << adjMatrix[i*nodes+j];
		 }
	   aux << "\n";
  }
	return aux.str();
}

//Implementación
/*
 * DFS
 *
 * @param int, int
 * @return string
 * 
*/
string Graph::DFS(int start, int goal){
		std::stringstream aux;
		stack <int> st; //Pila
		list <int> visited; //Nodos visitados
		vector <vector<int>> paths(nodes, vector<int>(1, -1)); //Recorrido
		st.push(start);
		dfsHelper(start, goal, st, visited, paths,aux);
		aux << " ";
		aux << print_path(paths, start, goal);
	return aux.str();
}

/*
 * dfsHelper
 *
 * @param int,int,vector,vector,vector<vector>,stringstream
 * @return 
 * 
*/
void Graph::dfsHelper(int current,
		int goal,
		stack<int> &st,
		list<int> &visited,
		vector<vector<int>> &paths,
		std::stringstream &aux){

		//Si el actual es al que quiero llegar imprimo todos los nodos visitados
		if(current == goal){
			aux << print_visited(visited);
		//Si está vacío no hay nodos
		} else if(st.empty()){
			aux << " node not found";
		//De otra forma 
		}	else {
			//.top() nos devuelve una referencia al elemento superior del stack
			current = st.top();
			//.pop() Elimina el último elemento agregado al stack
			st.pop();
			//Colocamos en visitado el nodo que estaba en el top del stack
			visited.push_back(current);
			//Recorremos toda la lista de nodos hasta el current size
			for(int  i = 0; i < adjList[current].size(); i++)
			//Si no está en visitado lo agregamos al stack
				if(!contains(visited, adjList[current][i])){
					st.push(adjList[current][i]);
					paths[adjList[current][i]][0] = current;
				}
			dfsHelper(current, goal, st, visited, paths,aux);
		}
}

//Implementación
/*
 * BFS
 *
 * @param int, int
 * @return string
 * 
*/
string Graph::BFS(int start, int goal){
	std::stringstream aux;
	queue <int> qu;
	list <int> visited;
    vector <vector<int>> paths(nodes, vector<int>(0));
	qu.push(start);
 	bfsHelper(start, goal, qu, visited, paths,aux);
	aux << " ";
	aux << print_path(paths, start, goal);
	return aux.str();
}

/*
 * bfsHelper
 *
 * @param int,int,vector,vector,vector<vector>,stringstream
 * @return 
 * 
*/
void Graph::bfsHelper(int current,
	int goal,
	queue<int> &qu,
	list<int> &visited,
	vector<vector<int>> &paths,
	std::stringstream &aux){
		//Si el actual es al que quiero llegar imprimo todos los nodos visitados
		if(current == goal){
			aux << print_visited(visited);
		//Si está vacío no hay nodos
		} else if(qu.empty()){
			aux << " node not found";
		//De otra forma
		}	else {
			//.front() Devuelve la referencia del siguiente nodo de la lista
			current = qu.front();
			// .pop() elimina el elemento siguiente de la lista
			qu.pop();
			//Se agrega el siguiente elemento como ya visitado
			visited.push_back(current);
			//Recorremos toda la lista de nodos hasta el current size
			for(int  i = 0; i < adjList[current].size(); i++)
			//Si no está en visitado lo agregamos al queue
				if(!contains(visited, adjList[current][i])){
					qu.push(adjList[current][i]);
				//Agrego al path como llegué a ese número
					paths[adjList[current][i]].push_back(current);
				}
			bfsHelper(current, goal, qu, visited, paths,aux);
		}
}


/*
 * print_visited
 *
 * @param list
 * @return string
 * 
*/
string Graph::print_visited(list<int> q){
	std::stringstream aux;
	aux << "visited:";
	while (!q.empty()){
    aux << " " << q.front();
    q.pop_front();
  }
  return aux.str();
}

/*
 * print_path
 *
 * @param vector<vector>,int,int
 * @return string
 * 
*/
string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	std::stringstream aux;
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	aux << "path:";
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
  }
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top();
		reverse.pop();
  }
  return aux.str();
}

/*
 * contains
 *
 * @param list,int
 * @return bool
 * 
*/
bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}

#endif /* Graph_H_ */
