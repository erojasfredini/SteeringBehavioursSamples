#pragma once

#include "Estado.h"

//Estado que lo unico que hace es quedarse haciendo nada hasta
//que el enemigo esta a menos de una determinada distancia,
//entonces cambia de estado a EstadoAtacar
class EstadoQuieto: public Estado
{
	private:
		EstadoQuieto();

		EstadoQuieto(const EstadoQuieto& cpy);

		EstadoQuieto& operator=(const EstadoQuieto& cpy);
		
	public:
		~EstadoQuieto();

		//Nos devuelve la unica instancia de la clase
		static EstadoQuieto* Singleton();

		virtual void Entrar(EntidadBase* pEntidad);

		virtual void Ejecutar(EntidadBase* pEntidad);

		virtual void Salir(EntidadBase* pEntidad);
};