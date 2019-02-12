#include "Principal.h"

Principal::Principal()
{
	altura = 0;
	largura = 0;
}


Principal::~Principal()
{
	al_destroy_display(tela);
	al_destroy_event_queue(Fila_eventos);
	al_destroy_timer(frameTimer);
	al_destroy_font(font);
	lab.~Labirinto();
	pathfinder.~PathFinder();
}


const int Principal::get_altura()const
{
	return altura;
}


const int Principal::get_largura()const
{
	return largura;
}


void Principal::set_largura(const int recebido)
{
	largura = recebido;
}


void Principal::set_altura(const int recebido)
{
	altura = recebido;
}


int Principal::inicializar()
{
	int alt = 0, larg = 0;
	cout << "\nINSIRA A LARGURA E A ALTURA DA TELA A SER GERADA\n" << "\nLARGURA: ";
	cin >> larg;
	cout << "\nALTURA: ";
	cin >> alt;
	set_altura(alt);
	set_largura(larg);
	system("pause");

	sair = false;
	if (!al_init())
		return EXIT_FAILURE;
	if (!al_install_keyboard())
		return EXIT_FAILURE;
	if (!al_install_mouse())
		return EXIT_FAILURE;
	if (!al_init_image_addon())
		return EXIT_FAILURE;
	if (!al_init_primitives_addon())
		return EXIT_FAILURE;
	if (!al_init_font_addon())
		return EXIT_FAILURE;
	
	Fila_eventos = NULL;
	frameTimer = NULL;
	font = al_create_builtin_font();

	if (larg % 20 != 0) {
		larg = (larg - (larg % 20));
	}
	if (alt % 20 != 0) {
		alt = (alt - (alt % 20));
	}

	al_set_new_display_flags( ALLEGRO_WINDOWED);
	tela = al_create_display(larg, alt);
	if (!tela)
		return EXIT_FAILURE;
	al_set_window_title(tela, "PATH FINDER");

	al_set_window_position(tela, 100, 0);

	Fila_eventos = al_create_event_queue();
	al_register_event_source(Fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(Fila_eventos, al_get_mouse_event_source());
	al_register_event_source(Fila_eventos, al_get_display_event_source(tela));
	frameTimer = al_create_timer(1.0 / FPS);
	al_register_event_source(Fila_eventos, al_get_timer_event_source(frameTimer));

	return EXIT_SUCCESS;
}
void Principal::ajuda() {
	switch (al_show_native_message_box(tela,
		"Controles",
		"Controles",
		"'ESC': Sair \n 'R': Labirinto aleatorio \n 'B' : Labirinto em branco \n 'F': Labirinto cheio de paredes \n 'Botao Esquerdo do Mouse' : Adiciona Paredes \n 'Botao Direito do Mouse'  : Adiciona caminho \n 'Esquerdo do mouse' + 'I' : Demarca o inicio \n 'Esquerdo do mouse' + 'O' : Demarca o fim", NULL,
		ALLEGRO_MESSAGEBOX_OK_CANCEL
		)) {

	case 0: 
		break;
	case 1: 
		break;
	case 2: 
		break;
	}
	return;
}

void Principal::mouse_calculator(const int tipo, int y , int x, Node*** aux_maze,int alt, int larg) {
	if (x < 0 || y < 0 || x > altura + 1 || y > largura + 1)
		return;
	if (x % 20 != 0) {
		x =( x - (x % 20)) / 20;
	}
	else {
		x = x / 20;
	}
	if (y % 20 != 0) {
		y = (y - (y % 20)) / 20;
	}
	else {
		y = y / 20;
	}

	if (x < alt && x >= 0 && y < larg && y >= 0) {
		if (tipo == 0) {
			aux_maze[x][y]->set_status(0);
			aux_maze[x][y]->set_verificado(false);
		}
		else if (tipo == 1) {
			aux_maze[x][y]->set_status(1);
			aux_maze[x][y]->set_verificado(true);
		}
		else if (tipo == 2) {
			aux_maze[x][y]->set_status(2);
			aux_maze[x][y]->set_verificado(false);
		}
		else if (tipo == 3) {
			lab.set_inicio(aux_maze[x][y]);
			aux_maze[x][y]->set_status(3);
			aux_maze[x][y]->set_verificado(false);
		}
		else if (tipo == 4) {
			lab.set_fim(aux_maze[x][y]);
			aux_maze[x][y]->set_status(4);
			aux_maze[x][y]->set_verificado(false);
		}
		cout << x << " - " << y << endl;
	}
}

int Principal::executar() 
{
	int i = 0,  j = 0, refresh =0;
	int encontrou;
	
	Node*** aux_maze = NULL;
	Node *aux = NULL;
	lab.set_largura(get_largura());
	lab.set_altura(get_altura());
	lab.gerar(0);
	aux_maze = lab.get_Maze();
	al_clear_to_color(al_map_rgb(75, 75, 75));
	lab.desenhar();
	al_flip_display();
	ajuda();

	al_start_timer(frameTimer);
	
	while (sair == false) {

		al_wait_for_event(Fila_eventos, &evento);

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			al_flush_event_queue(Fila_eventos);
			sair = true;
			break;
		}

		al_get_mouse_state(&mouseState);
		al_get_keyboard_state(&keyState);
		//cout << evento.mouse.x << " ---- " << evento.mouse.y << endl;
		if (mouseState.buttons & 1 && al_key_down(&keyState, ALLEGRO_KEY_I)) {
		//	cout << evento.mouse.x << " ---- " << evento.mouse.y << endl;
			mouse_calculator(INICIO, evento.mouse.x, evento.mouse.y, aux_maze, lab.get_alt(), lab.get_larg());
			continue;
		}
		else if (mouseState.buttons & 1 && al_key_down(&keyState, ALLEGRO_KEY_O)) {
		//	cout << evento.mouse.x << " ---- " << evento.mouse.y << endl;
			mouse_calculator(FINAL, evento.mouse.x, evento.mouse.y, aux_maze, lab.get_alt(), lab.get_larg());
			continue;
		}
		else if (mouseState.buttons & 1)
		{
		//	cout << evento.mouse.x << " ---- " << evento.mouse.y << endl;
			al_flush_event_queue(Fila_eventos);
			mouse_calculator(PAREDE, evento.mouse.x, evento.mouse.y, aux_maze, lab.get_alt(), lab.get_larg());
		}
		else if (mouseState.buttons & 2)
		{
		//	cout << evento.mouse.x << " ---- " << evento.mouse.y << endl;
			al_flush_event_queue(Fila_eventos);
			mouse_calculator(CAMINHO, evento.mouse.x, evento.mouse.y, aux_maze, lab.get_alt(), lab.get_larg());
		}
		if (evento.timer.source == frameTimer)
		{
			al_get_keyboard_state(&keyState);

			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
			{
				al_flush_event_queue(Fila_eventos);
				sair = true;
				break;
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_R))
			{
				al_flush_event_queue(Fila_eventos);
				lab.resetar(1);	
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_B))
			{
				al_flush_event_queue(Fila_eventos);
				lab.resetar(0);
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_F))
			{
				al_flush_event_queue(Fila_eventos);
				lab.resetar(2);
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_1))
			{
				al_flush_event_queue(Fila_eventos);
				lab.resetar(0);
				lab.resetar(4);
			}
			refresh++;
			if (al_key_down(&keyState, ALLEGRO_KEY_ENTER) && refresh > 5) {
				al_flush_event_queue(Fila_eventos);

				if (pathfinder.setup(&lab) == 0)
					encontrou = pathfinder.findPath();

				if (encontrou == 0) {
					pathfinder.get_path();
				}
				else if (encontrou == 1) {
					lab.resetar(3);
				}
				refresh = 0;
			}
			lab.desenhar();
			al_flip_display();
		}

	}
	return 0;
}
