#include "MiGame.h"

#include <Box2D/Box2D.h>

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

MiGame::MiGame(): Game(sf::VideoMode(800,600,32), "Ejemplo: Basico Comportamientos", sf::Style::Titlebar|sf::Style::Close, sf::ContextSettings(), 60)
{}

MiGame::~MiGame()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//

MiGame* MiGame::Singleton()
{
	static MiGame instancia;
	return &instancia;
}

void MiGame::CrearEscena()
{
	sf::Texture* img = &m_ManagerDeImagenes[IDImagen::VehiculoParticula];
	float escala = 0.2f;

	b2BodyDef cuerpo;
	cuerpo.type        = b2BodyType::b2_dynamicBody;
	b2FixtureDef adorno;
	adorno.restitution = 0.0f;
	adorno.isSensor    = false;
	adorno.friction    = 0.3f;
	adorno.density     = 0.01f;//Masa de 26.214399
	b2PolygonShape* pRectangulo = new b2PolygonShape();
	pRectangulo->SetAsBox(img->getSize().x/2*escala, img->getSize().y/2*escala, b2Vec2(0,0), 0);
	adorno.shape       = pRectangulo;

	cuerpo.position = b2Vec2(100, 100);
	cuerpo.angle    = 0;

	m_pAutoFantastico = new Vehiculo(cuerpo, adorno, escala, img);

	m_pAutoFantastico->m_FuerzaSteeringMax = 600;
	m_pAutoFantastico->m_VelocidadMax = 40;


	//////////////////////////////////////////////////
	////// ACTIVANDO LOS STEERING BEHAVIORS //////////
	//////////////////////////////////////////////////

		m_pAutoFantastico->GetSteeringBehaviors().EvadirParedesOn();
		m_pAutoFantastico->GetSteeringBehaviors().m_PesoEvadirParedes = 2.0f;// El valor por defecto es 1.0f, este escala el resultado
		m_pAutoFantastico->GetSteeringBehaviors().EvadirObstaculosOn();		 // de la fuerza de EvadirParedes
		m_pAutoFantastico->GetSteeringBehaviors().m_PesoEvadirObstaculos = 2.0f;// El valor por defecto es 1.0f, este escala el resultado
		m_pAutoFantastico->GetSteeringBehaviors().DeambularOn();				// de la fuerza de EvadirParedes


		// Descripcion de las paredes y asignacion a SteeringBehaviors: Paredes
		// SE VE MUCHO CODIGO PORQUE DEFINIMOS 4 PAREDES, PERO ES REPETITIVO LO QUE HACE

		//Pared de arriba
		cuerpo.type        = b2BodyType::b2_staticBody;
		adorno.restitution = 0.2f;
		adorno.isSensor    = false;
		adorno.friction    = 0.3f;
		adorno.density     = 0.01f;
		pRectangulo->SetAsBox(400, 10, b2Vec2(0.0f, 0.0f), 0);
		adorno.shape       = pRectangulo;

		cuerpo.position = b2Vec2(400, 0);
		cuerpo.angle    = 0;
		sf::RectangleShape* rectangulo = new sf::RectangleShape(sf::Vector2f(800.0f,  20.0f));
		rectangulo->setFillColor(sf::Color::Green);

		Paredes.push_back( new SteeringBehaviors::Pared(sf::Vector2f(0.0f, 1.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)) );
		ParedesEscena.push_back( new EntidadEscena(cuerpo, adorno, rectangulo) );

		//Pared de abajo
		cuerpo.position = b2Vec2(400, 600);

		Paredes.push_back( new SteeringBehaviors::Pared(sf::Vector2f(0.0f, -1.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)) );
		ParedesEscena.push_back( new EntidadEscena(cuerpo, adorno, new sf::RectangleShape(*rectangulo)) );

		//Pared de izquierda
		cuerpo.position = b2Vec2(0, 300);
		cuerpo.angle = 3.1415f/2.0f;

		Paredes.push_back( new SteeringBehaviors::Pared(sf::Vector2f(1.0f,0.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)) );
		ParedesEscena.push_back( new EntidadEscena(cuerpo, adorno, new sf::RectangleShape(*rectangulo)) );

		//Pared de derecha
		cuerpo.position = b2Vec2(800, 300);
		cuerpo.angle = 3.1415f/2.0f;

		Paredes.push_back( new SteeringBehaviors::Pared(sf::Vector2f(-1.0f,0.0f), sf::Vector2f(cuerpo.position.x, cuerpo.position.y)) );
		ParedesEscena.push_back( new EntidadEscena(cuerpo, adorno, new sf::RectangleShape(*rectangulo)) );

		m_pAutoFantastico->GetSteeringBehaviors().m_pParedes = &Paredes;

		// Obstaculos
		for(int i=0; i < 4 ; ++i)
		{
			cuerpo.type        = b2BodyType::b2_staticBody;
			adorno.restitution = 0.2;
			adorno.isSensor    = false;
			adorno.friction    = 0.3f;
			adorno.density     = 0.01f;//Masa de 45.32
			b2CircleShape* pCirculo = new b2CircleShape();
			pCirculo->m_radius = 40;
			adorno.shape       = pCirculo;

			cuerpo.position = b2Vec2((rand()/(float)RAND_MAX)*400+200, (rand()/(float)RAND_MAX)*400+100);
			cuerpo.angle    = 0;
			sf::Shape* circulo = new sf::CircleShape(pCirculo->m_radius);
			circulo->setFillColor(sf::Color::Green);

			Obstaculos.push_back( new EntidadEscena(cuerpo, adorno, circulo) );
		}
		m_pAutoFantastico->GetSteeringBehaviors().m_pObstaculos = &Obstaculos;
}

void MiGame::Actualizar(const float dt)
{
	//////////////////////////////////////////////////
	//////     ACTUALIZANDO EL VEHICULO     //////////
	//////////////////////////////////////////////////


		m_pAutoFantastico->Actualizar(dt);

		for(int i=0; i < Obstaculos.size() ; ++i)
			Obstaculos[i]->Actualizar(dt);

		for(int i=0; i < ParedesEscena.size() ; ++i)
			ParedesEscena[i]->Actualizar(dt);

	m_World.Step(m_dt, 10, 10);

	m_World.ClearForces();
}

void MiGame::Dibujar(const float dt)
{
	m_Window.clear();

	//////////////////////////////////////////////////
	//////      DIBUJANDO EL VEHICULO       //////////
	//////////////////////////////////////////////////

		m_pAutoFantastico->Dibujar(m_Window);

		for(int i=0; i < Obstaculos.size() ; ++i)
			Obstaculos[i]->Dibujar(m_Window);

		for(int i=0; i < ParedesEscena.size() ; ++i)
			ParedesEscena[i]->Dibujar(m_Window);

	m_Window.display();
}

void MiGame::LoadRecursos()
{
	if( !m_ManagerDeImagenes[IDImagen::VehiculoParticula].loadFromFile("Recursos\\Vehiculo2.png") )
			exit(0);
}