#include "MiGame.h"

#include <Box2D/Box2D.h>

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

MiGame::MiGame(): Game(sf::VideoMode(800,600,32), "Ejemplo: Basico Comportamientos", sf::Style::Titlebar|sf::Style::Close, sf::WindowSettings(24, 8, 0), 60)
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
	sf::Image* img = &m_ManagerDeImagenes[IDImagen::VehiculoParticula];
	float escala = 0.2f;

	b2BodyDef cuerpo;
	cuerpo.type        = b2BodyType::b2_dynamicBody;
	b2FixtureDef adorno;
	adorno.restitution = 0.0;
	adorno.isSensor    = false;
	adorno.friction    = 0.3f;
	adorno.density     = 0.01f;//Masa de 26.214399
	b2PolygonShape* pRectangulo = new b2PolygonShape();
	pRectangulo->SetAsBox(img->GetWidth()/2*escala, img->GetHeight()/2*escala, b2Vec2(0,0), 0);
	adorno.shape       = pRectangulo;

	cuerpo.position = b2Vec2(100, 100);
	cuerpo.angle    = 0;

	m_pAutoFantastico = new Vehiculo(cuerpo, adorno, escala, img);

	m_pAutoFantastico->m_FuerzaSteeringMax = 600;
	m_pAutoFantastico->m_VelocidadMax = 40;

	cuerpo.position = b2Vec2(300, 300);
	sf::Image* img2 = &m_ManagerDeImagenes[IDImagen::VehiculoParticulaCobarde];
	m_pAutoPresa = new Vehiculo(cuerpo, adorno, escala, img2);

	m_pAutoPresa->m_FuerzaSteeringMax = 600;
	m_pAutoPresa->m_VelocidadMax = 40;

	//////////////////////////////////////////////////
	////// ACTIVANDO LOS STEERING BEHAVIORS //////////
	//////////////////////////////////////////////////

		//este vehiculo persigue(intercepta)
		m_pAutoFantastico->GetSteeringBehaviors().InterceptarOn();
		m_pAutoFantastico->GetSteeringBehaviors().m_pPresa = m_pAutoPresa;//le decimos a quien intercepta(puntero)

		//este vehiculo huye(evade)
		m_pAutoPresa->GetSteeringBehaviors().EvadirOn();
		m_pAutoPresa->GetSteeringBehaviors().m_pAcechador = m_pAutoFantastico;//le decimos de quien huye(puntero)
}

void MiGame::Actualizar()
{
	float dt = Game::m_Window.GetFrameTime();

	const static sf::Input& input = m_Window.GetInput();

	//////////////////////////////////////////////////
	//////     ACTUALIZANDO LOS VEHICULO     //////////
	//////////////////////////////////////////////////

		m_pAutoFantastico->Actualizar(dt);

		m_pAutoPresa->Actualizar(dt);

	m_World.Step(m_dt, 10, 10);

	m_World.ClearForces();
}

void MiGame::Dibujar()
{
	float dt = Game::m_Window.GetFrameTime();

	m_Window.Clear();

	//////////////////////////////////////////////////
	//////      DIBUJANDO LOS VEHICULO       //////////
	//////////////////////////////////////////////////

		m_pAutoFantastico->Dibujar(m_Window);

		m_pAutoPresa->Dibujar(m_Window);

	m_Window.Display();
}

void MiGame::LoadRecursos()
{
	if( !m_ManagerDeImagenes[IDImagen::VehiculoParticula].LoadFromFile("Recursos\\Vehiculo2.png") )
			exit(0);

	if( !m_ManagerDeImagenes[IDImagen::VehiculoParticulaCobarde].LoadFromFile("Recursos\\VehiculoCobarde2.png") )
			exit(0);
}