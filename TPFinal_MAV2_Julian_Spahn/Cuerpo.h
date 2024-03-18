#pragma once
#include"SFML/Graphics.hpp"
#include"Box2D.h"

using namespace sf;
using namespace std;

class Cuerpo {
public:
	Cuerpo(b2Body* b, RectangleShape* f);//constructor de la clase cuerpo, usado para cuerpos que no llevan imagen
	void draw_h(RenderWindow* wdw1);//funcion para dibujar
	float rad_a_gra(float rad);//conversor de radianes a grados
	
private:
	//elementos para crear el cuerpo
	b2Body* b_humano;
	RectangleShape* f_humano;
	//elementos para regular las dimenciones y la posicion del cuerpo
	b2AABB dimenciones;
	b2Vec2 posicion;
};