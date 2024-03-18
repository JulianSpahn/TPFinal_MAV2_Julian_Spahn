#include"Colisiones.h"

void Colisiones::BeginContact(b2Contact* contacto) {//funcion para saber cuando comienza la colision entre objetos del box2d
	b2FixtureUserData Cuerpo1 = contacto->GetFixtureA()->GetUserData();
	b2FixtureUserData Cuerpo2 = contacto->GetFixtureB()->GetUserData();
	if (!hubo_contacto) {
		if ((Cuerpo1.pointer == 2 && Cuerpo2.pointer == 1) || (Cuerpo1.pointer == 1 && Cuerpo2.pointer == 2)) {
			hubo_contacto = true;
		}
	}
}

void Colisiones::EndContact(b2Contact* contacto) {//funcion para saber cuando termina la colision entre objetos del box2d
	temporizador.restart();
}

