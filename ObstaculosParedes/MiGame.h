#pragma once

#include <vector>

#include "Game.h"
#include "Vehiculo.h"

//Identificadores para las imagenes(sf::Image) almacenadas
//en el mapa m_ManagerDeImagenes
enum IDImagen{VehiculoParticula};

//Clase principal del juego, contiene toda la estructura de juego
//Este objeto sera el responsable de:
//	-Crear la escena
//	-Dibujar la pantalla
//	-Actualizar el juego
class MiGame: public Game
{
private:

	MiGame();

	MiGame(const MiGame& cpy);

	MiGame& operator=(const MiGame& cpy);

	Vehiculo* m_pAutoFantastico;

	std::vector<EntidadEscena*>				Obstaculos;//Necesitamos estos para decirle cuales son los obstaculos
	std::vector<SteeringBehaviors::Pared*>	Paredes;   //Necesitamos estos para definir como son las paredes obstaculos
	std::vector<EntidadEscena*>				ParedesEscena;//Necesitamos estos para tener las paredes como objetos de Box2D y que se grafiquen

public:
	//Nos devuelve la unica instancia de la clase
	static MiGame* Singleton();

	~MiGame();

	//================================================
	/////////	Game Propiedades publicas	 /////////
	//================================================

	std::map<IDImagen,sf::Texture> m_ManagerDeImagenes;

	//================================================
	/////////////	 Game Metodos		 /////////////
	//================================================

	//Crea la escena
	virtual void CrearEscena();

	//Actualiza la escena
	virtual void Actualizar(const float dt);

	//Dibuja la escena
	virtual void Dibujar(const float dt);

	//Carga los recursos a usar
	virtual void LoadRecursos();
};