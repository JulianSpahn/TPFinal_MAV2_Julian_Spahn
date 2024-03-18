#pragma once
#include <Box2D.h>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Ragdoll.h"
#include "SpriteRenderer.h"
using namespace sf;

class Canon
{
private:
	friend class Juego;
	// elementos para crear el ca��n
	b2Body* b_canon;
	b2BodyDef b_canon_def;
	b2Fixture* f_canon;
	b2FixtureDef f_canon_def;
	// Forma del ca��n
	RectangleShape* fig_c_r;
	// Textura y sprite
	Texture* t_cannon;
	Sprite* s_cannon;
	SpriteRenderer* cannon;
public:
	Canon(b2World* world, const b2Vec2& position);//constructor del ca�on
	void S_T();//funcion para inicializar las texturas
	void draw(RenderWindow* wndw);//funcion para dibujar el ca�on
	void Update(RenderWindow* wnd);//funcion con la que actualizamos el ca�on
	int GetXPosition();//obtenemos posicion en x para luego usarla al axtualizar la posicion del ca�on
	int GetYPosition();//obtenemos posicion en y para luego usarla al axtualizar la posicion del ca�on
};