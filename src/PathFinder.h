#pragma once
#include "Labirinto.h"
class PathFinder
{
public:
	PathFinder();
	~PathFinder();
private:
	list <Node*> Aberta;
	list <Node*> Fechada;
	list <Node*> Caminho;
	Labirinto* lab;
	Node*** maze;
	Node* inicio;
	Node* atual;
	Node* final;
	Node* aux;
	
public:
	int setup(Labirinto *lab);
	void addAberta(Node* ptr);
	void addFechada(Node* ptr);
	Node* lowest_f_cost();
	int findPath();
	void atualizaNode(Node * ptr, Node* atual, Node* final);
	void get_path();
	bool isEqual(Node *a, Node *b);
	Node* get(list <Node*> lista, int i);

};

