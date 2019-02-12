#pragma once
#include"Node.h"
class Labirinto
{
public:
	Labirinto();
	~Labirinto();
private:
	Node*** Maze;
	Node* inicio;
	Node* fim;
	int largura;
	int altura;
	int alt;
	int larg;
public:
	Node*** get_Maze()const { return Maze; }
	Node* get_inicio()const { return inicio; }
	Node* get_fim()const { return fim; }
	void set_inicio(Node* ptr) {
		if (ptr != NULL) {
			if (inicio == NULL){
				inicio = ptr;
			}
			else {
				inicio->set_status(0);
				inicio = ptr;
			}
		}
	}
	void set_fim(Node* ptr) {
		if (ptr != NULL) {
			if (fim == NULL) {
				fim = ptr;
			}
			else {
				fim->set_status(0);
				fim = ptr;
			}
		}
	}
	void labirinto_recursivo();
	void paredes_externas();
	int entrada();
	void paredes_internas(bool h,int minX, int maxX, int minY, int maxY, int gate);
	void paredes_horizontais(int minX,int maxX,int y);
	void paredes_verticais(int minY,int maxY,int x);
	int randomNumber(int min,int  max);
	bool get_orientation(int al,int lar);
	const int get_altura()const;
	const int get_largura()const;
	void set_largura(const int recebido);
	void set_altura(const int recebido);
	const int get_alt()const;
	const int get_larg()const;
	void set_larg(const int recebido);
	void set_alt(const int recebido);
	void limpar();
	void desenhar();
	void gerar(int tipo);
	void resetar(int tipo);
};

