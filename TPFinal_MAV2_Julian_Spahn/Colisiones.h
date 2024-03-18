#pragma once
#include "box2d.h"
#include "Box2D.h"
#include <iostream>
#include "SFML/System.hpp"
using namespace std;
//using namespace sf;
class Colisiones : public b2ContactListener {
private:
	sf::Clock temporizador;//reloj
public:
	Colisiones() : hubo_contacto(false) {}//constructor vacio de la clase colisiones
	void BeginContact(b2Contact* contacto);//funcion para saber cuando inicia la colision entre objetos del box2d
	void EndContact(b2Contact* contacto);//funcion para saber cuando termina la colision entre objetos del box2d
	bool hubo_contacto = false;//booleano utilizado para saber si hubo contacto
};