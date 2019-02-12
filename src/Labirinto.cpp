#include "Labirinto.h"



Labirinto::Labirinto()
{
	altura = 0;
	largura = 0;
	alt = 0;
	larg = 0;
	Maze = NULL;
	inicio = NULL;
	fim = NULL;

}


Labirinto::~Labirinto()
{
	limpar();
	delete[] inicio;
	inicio = NULL;
	delete[] fim;
	fim = NULL;
}


const int Labirinto::get_altura()const
{
	return altura;
}


const int Labirinto::get_largura()const
{
	return largura;
}


void Labirinto::set_largura(const int recebido)
{
	largura = recebido;
}


void Labirinto::set_altura(const int recebido)
{
	altura = recebido;
}

const int Labirinto::get_alt()const
{
	return alt;
}


const int Labirinto::get_larg()const
{
	return larg;
}


void Labirinto::set_larg(const int recebido)
{
	larg = recebido;
}


void Labirinto::set_alt(const int recebido)
{
	alt = recebido;
}



void Labirinto::limpar() {
	int i = 0, j = 0;
	for (i = 0; i < get_alt(); i++) {
		for (j = 0; j < get_larg(); j++) {
			delete Maze[i][j];
		}
		delete Maze[i];
	}
	delete[] Maze;
	Maze = NULL;
}


void Labirinto::desenhar() {
	int i = 0, j = 0;
	
	 for (i = 0; i < get_alt(); i++) {
			for (j = 0; j < get_larg(); j++) {
				Maze[i][j]->desenhar();
			}
		}

}

void Labirinto::gerar(int tipo)
{

	srand(time(NULL));
	int i = 0, j = 0;

	if (get_largura() % 20 != 0) {
		set_larg((get_largura() - (get_largura() % 20)) / 20);
	}
	else {
		set_larg(get_largura() / 20);
	}
	if (get_altura() % 20 != 0) {
		set_alt((get_altura() - (get_altura() % 20)) / 20);
	}
	else {
		set_alt(get_altura() / 20);
	}
	
	Maze = new Node**[get_alt()];
	for (int i = 0; i < get_alt(); i++)
		Maze[i] = new Node*[get_larg()];

	Node *ptr = NULL;
	if (tipo != 0) {
		for (i = 0; i < get_alt(); i++) {
			for (j = 0; j < get_larg(); j++) {
				ptr = new Node;
				if (rand() % 9 > 2) {
					ptr->set_status(0);
					ptr->set_verificado(false);
				}
				else {
					ptr->set_status(1);
					ptr->set_verificado(true);
				}
				ptr->set_x(j * 20);
				ptr->set_y(i * 20);
				if (ptr != NULL) {
					Maze[i][j] = ptr;
				}
				ptr = NULL;
			}
		}
	}
	else {
		for (i = 0; i < get_alt(); i++) {
			for (j = 0; j < get_larg(); j++) {
				ptr = new Node;
				ptr->set_status(0);
				ptr->set_x(j * 20);
				ptr->set_y(i * 20);
				ptr->set_verificado(false);
				if (ptr != NULL) {
					Maze[i][j] = ptr;
				}
				ptr = NULL;
			}
		}
	}
}

void Labirinto::resetar(int tipo)
{
	int i = 0, j = 0;
	if (tipo == 0 ) {
		for (i = 0; i < get_alt(); i++) {
			for (j = 0; j < get_larg(); j++) {
				Maze[i][j]->set_status(0);
				Maze[i][j]->set_verificado(false);
			}
		}
	}
	else if (tipo == 2) {
		for (i = 0; i < get_alt(); i++) {
			for (j = 0; j < get_larg(); j++) {
				Maze[i][j]->set_status(1);
				Maze[i][j]->set_verificado(true);
			}
		}
	}
	else if (tipo == 1) {
		for (i = 0; i < get_alt(); i++) {
			for (j = 0; j < get_larg(); j++) {
				if (rand() % 9 > 2) {
					Maze[i][j]->set_status(0);
					Maze[i][j]->set_verificado(false);
				}
				else {
					Maze[i][j]->set_status(1);
					Maze[i][j]->set_verificado(true);
				}
			}
		}
	}
	else if (tipo == 3) {
		for (i = 0; i < get_alt(); i++) {
			for (j = 0; j < get_larg(); j++) {
				if (Maze[i][j]->get_verificado() && Maze[i][j]->get_status()== PASSOU) {
					Maze[i][j]->set_status(0);
					Maze[i][j]->set_verificado(false);
				}
			}
		}
	}
	else if (tipo == 4) {
		labirinto_recursivo();
	}

}
bool Labirinto::get_orientation(int al, int lar) {
	int alet;
	if (lar < al)
		return HORIZONTAL;
	else if (al < lar)
		return VERTICAL;
	else {
		alet = rand() % 2;
		cout << alet <<endl;
		return alet;
	}
		
}


void Labirinto::labirinto_recursivo() {

	paredes_externas();
		int ent = entrada();
		paredes_internas(true, 1, larg - 2, 1, alt - 2, ent);
}

void Labirinto::paredes_externas() {
	for (int i = 0; i < alt; i++) {
		if (i == 0 || i == (alt - 1)) {
			for (int j = 0; j < larg; j++) {
				Maze[i][j]->set_status(PAREDE);
				Maze[i][j]->set_verificado(true);
			}
		}
		else {
			Maze[i][0]->set_status(PAREDE);
			Maze[i][0]->set_verificado(true);
			Maze[i][larg - 1]->set_status(PAREDE);
			Maze[i][larg - 1]->set_verificado(true);
		}
	}
}

	int Labirinto::entrada() {
		int x = randomNumber(1, alt - 1);
		Maze[alt-1][x]->set_status(FINAL);
		set_fim(Maze[alt - 1][x]);
		Maze[alt-1][x]->set_verificado(false);
		return x;
	}

	void Labirinto::paredes_internas(bool h,int minX,int maxX,int minY,int maxY,int gate) {
		if (h) {
			
			if (maxX - minX < 2) {
				return;
			}
			desenhar();
			al_flip_display();
			Sleep(10);
			int y = (int)(randomNumber(minY, maxY) / 2) * 2;
			paredes_horizontais(minX, maxX, y);

			paredes_internas(!h, minX, maxX, minY, y - 1, gate);
			paredes_internas(!h, minX, maxX, y + 1, maxY, gate);
			
		}
		else {
			if (maxY - minY < 2) {
				return;
			}
			desenhar();
			al_flip_display();
			Sleep(20);
			int x =(int)(randomNumber(minX, maxX) / 2) * 2;
			paredes_verticais(minY, maxY, x);

			paredes_internas(!h, minX, x - 1, minY, maxY, gate);
			paredes_internas(!h, x + 1, maxX, minY, maxY, gate);
			
		}
	}

	void Labirinto::paredes_horizontais(int minX, int maxX, int y) {
		int hole = (int)(randomNumber(minX, maxX) / 2) * 2 + 1;

		for (int i = minX; i <= maxX; i++) {
			if (i == hole) {
				Maze[y][i]->set_status(CAMINHO);
				Maze[y][i]->set_verificado(false);

			}
			else {
				Maze[y][i]->set_status(PAREDE);
				Maze[y][i]->set_verificado(true);
			}
		}
	}

	void Labirinto::paredes_verticais(int minY,int maxY,int x) {
		int hole = (int)(randomNumber(minY, maxY) / 2) * 2 + 1;

		for (int i = minY; i <= maxY; i++) {
			if (i == hole) {
				Maze[i][x]->set_status(CAMINHO);
				Maze[i][x]->set_verificado(false);
			}
			else {
				Maze[i][x]->set_status(PAREDE);
				Maze[i][x]->set_verificado(true);
			}
		}
	}

	int Labirinto::randomNumber(int min,int max) {
		return rand() % (max - min + 1) + min;
	}

