#include "PathFinder.h"

PathFinder::PathFinder()
{
	lab = NULL;
	inicio = NULL;
	atual = NULL;
	aux = NULL;
	final = NULL;
	maze = NULL;
}

PathFinder::~PathFinder()
{

	Aberta.clear();
	Fechada.clear();
	Caminho.clear();

	
}
int PathFinder::setup(Labirinto * l)
{
	if (l == NULL || l->get_inicio() == NULL || l->get_fim() == NULL) {
		cout << "NULO1" << endl;
		return 1;
		
	}
	lab = l;
	inicio = l->get_inicio();
	if (inicio == NULL) {
		cout << "NULO2" << endl;
		return 1;
	}
	atual = l->get_inicio();
	if (atual == NULL){
		cout << "NULO3" << endl;
		return 1;
	}
	final = l->get_fim();
	if (final == NULL){
		cout << "NULO4" << endl;
		return 1;
}
	atual->calcula_G();
	atual->calcula_H(final->get_x(), final->get_y());
	atual->set_f_cost();
	maze = l->get_Maze();
	if (maze == NULL) {
		cout << "NULO5" << endl;
		return 1;
	}

	return 0;
}

void PathFinder::addAberta(Node * ptr)
{
	if (ptr != NULL) {
		Aberta.push_back(ptr);
	}
	
}

void PathFinder::addFechada(Node * ptr)
{
	
	if (ptr != NULL) {
		ptr->set_verificado(true);
		Fechada.push_back(ptr);
	}
}

Node * PathFinder::lowest_f_cost()
{
	Node* aux = NULL;
	list <Node*>::iterator it;

	for (it = Aberta.begin(); it != Aberta.end(); ++it) {
		if ((*it)->get_f_cost() < aux->get_f_cost()) {
			aux = *it;
		}
	}

	return aux;
}

void PathFinder::atualizaNode(Node * ptr, Node* atual, Node* final)
{
	addAberta(ptr);
	ptr->set_pai(atual);
	
	ptr->set_status(PASSOU);
	ptr->calcula_G();
	ptr->set_verificado(true);
	ptr->calcula_H(final->get_x(), final->get_y());
	ptr->set_f_cost();
	ptr->desenhar();
}

int PathFinder::findPath()
{
	Aberta.clear();
	Fechada.clear();
	Caminho.clear();
	bool isRunning = true;
	list <Node*>::iterator it;

	atual = inicio;
	int i = atual->get_y() / 20;
	int j = atual->get_x() / 20;
	long long int k = 0;

	addAberta(atual);
	while (isRunning) {
		if (i - 1 >= 0 ) {
			if (maze[i - 1][j]->get_verificado() == false && maze[i - 1][j]->get_status() != PAREDE && maze[i-1][j] != atual->get_pai()) {
				//cout << "entrou i-1" << endl;
				atualizaNode(maze[i - 1][j], atual, final);
			}
		}
		if(i+1 < lab->get_alt()) {
			if (maze[i+1][j]->get_verificado() == false && maze[i + 1][j]->get_status() != PAREDE && maze[i+1][j] != atual->get_pai()) {
				atualizaNode(maze[i + 1][j], atual, final);
			}
		}
		if (j - 1 >= 0) {
			if (maze[i][j-1]->get_verificado() == false && maze[i][j-1]->get_status() != PAREDE && maze[i][j-1] != atual->get_pai() ) {
				//cout << "entrou j-1" << endl;
				atualizaNode(maze[i][j-1], atual, final);
				
			}
		}
		if (j + 1 < lab->get_larg()) {
			if (maze[i][j+1]->get_verificado() == false && maze[i][j+1]->get_status() != PAREDE && maze[i][j+1] != atual->get_pai()) {
				//cout << "entrou J+1" <<  endl;
				atualizaNode(maze[i][j+1], atual, final);
				
			}
		}
		al_flip_display();
		addFechada(atual);
		

		for (it = Aberta.begin(); it != Aberta.end(); ++it) {
			if (*it == atual) {
				it = Aberta.erase(it);
				break;
			}
		}
		
		if (isEqual(atual, final)) {
			isRunning = false;
		}
		
		
		if (Aberta.empty()) {
			return 1;
		}
		else {
			
			Aberta.sort([](const Node* a, const Node* b) { return a->get_f_cost() < b->get_f_cost(); });
			atual = Aberta.front();
		
		}
		
		 i = atual->get_y() / 20;
		 j = atual->get_x() / 20;
		Sleep(20);
		
	}
	return 0;
}
void PathFinder::get_path() {
	Caminho.clear();
	cout << "AQUI" << endl;
	Node* pai = NULL;
	pai = final;
	pai->set_status(FINAL);
	pai = pai->get_pai();
	while (pai->get_pai() != NULL) {
		pai->set_status(-1);
		Caminho.push_front(pai);
		pai = pai->get_pai();
	}
	
		

	}

bool PathFinder::isEqual(Node * a, Node * b)
{
	if (a->get_x() == b->get_x() && a->get_y() == b->get_y()) {
		return true;
	}
	return false;
}

Node * PathFinder::get(list<Node*> lista, int i)
{
	int j = 0;
	list<Node*>::iterator it = lista.begin();
	cout << (*it)->get_x();
	while ( it != lista.end()) {
		++it;
		
		if (j >= i){
			break;
		}
		else
			j++;
	}
		return (*it);

}
	






