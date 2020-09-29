#pragma once

#include "Estado.h"

//Estado que lo que hace es interceptar a su presa usando comportamientos de control
//Si la presa se aleja a mas de una distancia cambia de estado a EstadoQuieto
class EstadoAtacar: public Estado
{
	private:
		EstadoAtacar();

		EstadoAtacar(const EstadoAtacar& cpy);

		EstadoAtacar& operator=(const EstadoAtacar& cpy);
		
	public:
		virtual ~EstadoAtacar();

		//Nos devuelve la unica instancia de la clase
		static EstadoAtacar* Singleton();

		virtual void Entrar(EntidadBase* pEntidad);

		virtual void Ejecutar(EntidadBase* pEntidad);

		virtual void Salir(EntidadBase* pEntidad);
};