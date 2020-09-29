#include "MiGame.h"

using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));

	MiGame::Singleton()->Iniciar();

	return 0;
}


