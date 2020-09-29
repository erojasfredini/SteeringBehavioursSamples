#include "Persecutor.h"

#include "EstadoQuieto.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

Persecutor::Persecutor(Vehiculo* pPresa, const b2BodyDef& CuerpoDef, const b2FixtureDef& AdornoDef, float escala, sf::Texture* pTextura):
											Vehiculo(CuerpoDef, AdornoDef, escala, pTextura),
											m_pPresa(pPresa)
{
	//Empezamos la FSM en el EstadoQuieto
	m_MaquinaDeEstadoFinito.CambiarEstado(EstadoQuieto::Singleton());
}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//

std::string Persecutor::GetNombreEstadoActual()
{
	return m_MaquinaDeEstadoFinito.GetNombreEstadoActual();
}