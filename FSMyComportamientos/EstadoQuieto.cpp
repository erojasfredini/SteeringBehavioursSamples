#include "EstadoQuieto.h"
#include "EstadoAtacar.h"
#include "Persecutor.h"

#include <iostream>

#include "MiGame.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

EstadoQuieto::EstadoQuieto(): Estado("EstadoQuieto")
{}

EstadoQuieto::EstadoQuieto(const EstadoQuieto& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
}

EstadoQuieto& EstadoQuieto::operator=(const EstadoQuieto& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
	return *this;
}

EstadoQuieto::~EstadoQuieto()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//


EstadoQuieto* EstadoQuieto::Singleton()
{
	static EstadoQuieto instancia;
	return &instancia;
}

void EstadoQuieto::Entrar(EntidadBase* pEntidad)
{
	Persecutor* pPersecutor = dynamic_cast<Persecutor*>(pEntidad);
	std::cout<<"Entro a EstadoQuieto"<<std::endl;
}

void EstadoQuieto::Ejecutar(EntidadBase* pEntidad)
{
	Persecutor* pPersecutor = dynamic_cast<Persecutor*>(pEntidad);
	FSM& vahiculoFSM = pEntidad->GetFSM();

	sf::Vector2f dist = pPersecutor->GetPosicion()- pPersecutor->m_pPresa->GetPosicion();
	if( sqrt(dist.x*dist.x+dist.y*dist.y) < 400 )//Si el enemigo esta muy cerca cambia de estado para atacar
	{
		vahiculoFSM.CambiarEstado(EstadoAtacar::Singleton());
		return;
	}
}

void EstadoQuieto::Salir(EntidadBase* pEntidad)
{
	Persecutor* pPersecutor = dynamic_cast<Persecutor*>(pEntidad);
}