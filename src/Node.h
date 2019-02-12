#pragma once
#include "Cabeçalho.h"
class Node
{
public:
	Node();
	~Node();
private:
	Node* Pai;
	bool verificado;
	int pos_x;
	int pos_y;
	int status;
	int f_cost;
	int g_cost;
	int h_cost;
public:
	Node* get_pai() {
		return Pai;
	}
	void set_pai(Node* ptr) {
		Pai = ptr;
	}
	const bool get_verificado()const {
		return verificado;
	}
	void set_verificado(const bool recebido) {
		verificado = recebido;
	}
	const int get_h_cost()const {return h_cost;}
	void set_h_cost(const int recebido) {h_cost = recebido;}
	const int get_g_cost()const {return g_cost;}
	void set_g_cost(const int recebido) {g_cost = recebido;}
	const int get_f_cost()const {return f_cost;}
	void set_f_cost() {f_cost = get_g_cost()+get_h_cost();}
	void calcula_G();
	void calcula_H(int x, int y);
	const int get_x()const;
	const int get_y()const;
	void set_x(const int recebido);
	void set_y(const int recebido);
	const int get_status()const;
	void set_status(const int recebido);
	void desenhar();
};

