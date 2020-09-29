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

		m_pAutoFantastico->GetSteeringBehaviors().ArribarOn();
		//podriamos establecer m_pAutoFantastico->GetSteeringBehaviors().m_PosObjetivo a la posicion
		//a arribar una vez, pero en vez de eso en este ejemplo le daremos cada frame la posicion a arribar
		//sea la posicion del mouse
}

void MiGame::Actualizar(const float dt)
{
	//////////////////////////////////////////////////
	//////     ACTUALIZANDO EL VEHICULO     //////////
	//////////////////////////////////////////////////

		//En este caso todas las vueltas le decimos que la posicion a arribar sea la del mouse
		m_pAutoFantastico->GetSteeringBehaviors().m_PosObjetivo = sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

		m_pAutoFantastico->Actualizar(dt);

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

	m_Window.display();
}

void MiGame::LoadRecursos()
{
	if( !m_ManagerDeImagenes[IDImagen::VehiculoParticula].loadFromFile("Recursos\\Vehiculo2.png") )
			exit(0);
}