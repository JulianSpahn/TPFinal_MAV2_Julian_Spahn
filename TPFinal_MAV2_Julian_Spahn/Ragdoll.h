#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include"Box2D.h"
#include "Cuerpo.h"
#include <list>
using namespace sf;
using namespace std;

class Ragdoll {
private: 
	//elementos para crear a los ragdolls
	b2Body* b_rag[6];
	b2BodyDef b_rag_def[6];
	b2Fixture* f_rag[6];
	b2FixtureDef f_rag_def[6];
	RectangleShape* fig_b_r[6];
	Cuerpo* Humano[6];
	b2DistanceJoint* cable[5];
	b2DistanceJointDef cable_def[5];
public:
	Ragdoll(Vector2f pos, b2World& phyWorld);//constructor de los ragdolls
	void Draw(RenderWindow* wnd);//funcion para dibujar el ragdoll
	void ApplyForce(Vector2f posiciones);//funcion para aplicarle fuerza al ragdoll
	Vector2f GetPosition(int i);//funcion para obtener la posicion del ragdoll
	void UpdatePositions();//funcion para actualizar la posicion del ragdoll
};