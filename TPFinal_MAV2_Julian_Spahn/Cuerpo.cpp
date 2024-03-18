#include "Cuerpo.h"

Cuerpo::Cuerpo(b2Body* c, RectangleShape* f) {//constructor de la clase cuerpo (para objetos que no llevan sprite)
	b_humano = c;
	f_humano = f;
	posicion = b_humano->GetPosition();

	dimenciones.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	dimenciones.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);

	for (b2Fixture* i = b_humano->GetFixtureList(); i; i = i->GetNext()) {
		dimenciones = i->GetAABB(0);
	}
	
	f_humano->setSize({ dimenciones.GetExtents().x * 2, dimenciones.GetExtents().y * 2 });
	f_humano->setOrigin(f_humano->getSize().x / 2.f, f_humano->getSize().y / 2.f);
	f_humano->setPosition(posicion.x, posicion.y);
};

void Cuerpo::draw_h(RenderWindow* wdw1) {//funcion para dibujar los objetos
	posicion = b_humano->GetPosition();
	f_humano->setPosition(posicion.x, posicion.y);
	f_humano->setRotation(rad_a_gra(b_humano->GetAngle()));
	wdw1->draw(*f_humano);
}


float Cuerpo::rad_a_gra(float rad) {//funcion para convertir readianes a grados
	return rad * 100.0 / 3.14;
}

