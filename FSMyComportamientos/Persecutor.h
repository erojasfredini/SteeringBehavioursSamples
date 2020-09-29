#pragma once

#include <string>
#include "Vehiculo.h"

class Persecutor: public Vehiculo
{
	private:
		//A quien cazara
		Vehiculo *m_pPresa;

	public:
		friend class EstadoQuieto;
		friend class EstadoAtacar;

		Persecutor(Vehiculo* pPresa, b2BodyDef& CuerpoDef, const b2FixtureDef& AdornoDef, float escala, sf::Texture* pTextura);

		std::string GetNombreEstadoActual();
};