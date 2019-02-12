#include "Node.h"



Node::Node()
{
	Pai = NULL;
	pos_x = 0;
	pos_y = 0;
	status = 0;
	verificado = false;
}


Node::~Node()
{
	//Pai = NULL;
	
}


void Node::calcula_G()
{
	if (Pai != NULL) {
		g_cost = Pai->get_g_cost() + 1;
	}
	else {
		g_cost = 0;
	}
}

void Node::calcula_H(int x, int y)
{
	h_cost = (int)pow( pow((pos_x - x), 2) + pow((pos_y - y), 2), 0.5);
}

const int Node::get_x()const
{
	return pos_x;
}


const int Node::get_y() const
{
	return pos_y;
}


void Node::set_x(const int recebido)
{
	pos_x = recebido;
	return;
}


void Node::set_y(const int recebido)
{
	pos_y = recebido;
	return;
}


const int Node::get_status()const
{
	return status;
}


void Node::set_status(const int recebido)
{
	status = recebido;
	if (recebido == 1) {
		verificado = true;
	}
	return;
}

void Node::desenhar() {
	if (get_status() == CAMINHO)
		al_draw_filled_rectangle(get_x(), get_y(), get_x() + 19, get_y() + 19, al_map_rgb(255, 255, 255));
	else if (get_status() == PATH) {
		al_draw_filled_rectangle(get_x(), get_y(), get_x() + 19, get_y() + 19, al_map_rgb(180, 00, 180));
	}
	else if (get_status() == PAREDE) {
		al_draw_filled_rectangle(get_x(), get_y(), get_x() + 19, get_y() + 19, al_map_rgb(0, 0, 0));
	}
	else if (get_status() == PASSOU) {
		al_draw_filled_rectangle(get_x(), get_y(), get_x() + 19, get_y() + 19, al_map_rgb(50, 50, 255));
	}
	else if (get_status() == FINAL) {
		al_draw_filled_rectangle(get_x(), get_y(), get_x() + 19, get_y() + 19, al_map_rgb(255, 30, 30));
	}
	else if (get_status() == INICIO) {
		al_draw_filled_rectangle(get_x(), get_y(), get_x() + 19, get_y() + 19, al_map_rgb(50, 255, 50));
	}
	

}
