#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define PATH -1
#define CAMINHO 0
#define PAREDE 1
#define PASSOU 2
#define INICIO 3
#define FINAL 4

#define HORIZONTAL 0
#define VERTICAL 1


#define LARGURA_TELA 1200
#define ALTURA_TELA 600
#define FPS 30

using namespace std;