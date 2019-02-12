#pragma once
#include "PathFinder.h"
class Principal
{
public:
	Principal();
	~Principal();
	int executar();
	int inicializar();
public:
	ALLEGRO_DISPLAY *tela;
	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_MOUSE_STATE   mouseState;
	ALLEGRO_EVENT_QUEUE *Fila_eventos;
	ALLEGRO_TIMER *frameTimer;
	ALLEGRO_EVENT evento;
	ALLEGRO_FONT* font;
private:
	PathFinder pathfinder;
	Labirinto lab;
	int altura;
	int largura;
	bool sair;
public:
	Labirinto* get_lab() {
		return &lab;
	}
	const int get_altura()const;
	const int get_largura()const;
	void set_largura(const int recebido);
	void set_altura(const int recebido);
	void mouse_calculator(const int tipo, int y, int x, Node*** aux_maze, int alt  , int larg);
	void ajuda();
};

