#include "EstadoAtacar.h"
#include "EstadoQuieto.h"
#include "Persecutor.h"

#include <iostream>

#include "MiGame.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

EstadoAtacar::EstadoAtacar(): Estado("EstadoAtacar")
{}

EstadoAtacar::EstadoAtacar(const EstadoAtacar& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
}

EstadoAtacar& EstadoAtacar::operator=(const EstadoAtacar& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
	return *this;
}

EstadoAtacar::~EstadoAtacar()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//


EstadoAtacar* EstadoAtacar::Singleton()
{
	static EstadoAtacar instancia;
	return &instancia;
}

void EstadoAtacar::Entrar(EntidadBase* pEntidad)
{
	Persecutor* pPersecutor = dynamic_cast<Persecutor*>(pEntidad);

	std::cout<<"Entro a EstadoAtacar"<<std::endl;

	pPersecutor->GetSteeringBehaviors().InterceptarOn();//Activamos el comportamiento
	pPersecutor->GetSteeringBehaviors().m_pPresa = pPersecutor->m_pPresa;//Establecemos la presa
}

void EstadoAtacar::Ejecutar(EntidadBase* pEntidad)
{
	Persecutor* pPersecutor = dynamic_cast<Persecutor*>(pEntidad);
	FSM& persecutorFSM = pEntidad->GetFSM();

	sf::Vector2f dist = pPersecutor->GetPosicion()- pPersecutor->m_pPresa->GetPosicion();
	if( sqrt(dist.x*dist.x+dist.y*dist.y) > 400 )//Si el enemigo esta muy lejos cambia de estado para quedarse quieto
	{
		persecutorFSM.CambiarEstado(EstadoQuieto::Singleton());
		return;
	}
}

void EstadoAtacar::Salir(EntidadBase* pEntidad)
{
	Persecutor* pPersecutor = dynamic_cast<Persecutor*>(pEntidad);

	pPersecutor->GetSteeringBehaviors().InterceptarOff();
}