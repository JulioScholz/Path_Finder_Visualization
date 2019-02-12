#include "Cabeçalho.h"
#include "Principal.h"

int main(int argc, char *argv[]) {

	Principal Path_Finder;

	if(Path_Finder.inicializar() == 0)
		Path_Finder.executar();
	return EXIT_SUCCESS;
}
