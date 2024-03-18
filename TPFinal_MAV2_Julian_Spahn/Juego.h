#pragma once
#include "Cuerpo.h"
#include "Canon.h"
#include "Colisiones.h"
class Juego {
public:
	Juego(Vector2i resolucion, std::string titulo);//constructor de la clase juego
	void set_cam();//seteamos la camara en las diferentes posiciones
	void s_phy();//inicializamos el mundo y los objetos dentro de él
	void s_i();//inicializamos las distintas imagenes
	void act_phy();//actualizamos las fisicas del mundo
	void ev();//manejamos los eventos del juego
	void draw();//dibujamos los elementos del juego
	void update();//actualizamos las coliciones
	void Loop();//loop del juego
	void UpdateRagdoll();//funcion para actualizar a los ragdolls (los lanza)
	void Start_game();//funcion que se encarga de cargar las fisicas, las imagenes, la camara y el loop en orden


private:

	RenderWindow* wdw1;//ventana
	Canon* cannon;//creamos el cañon
	View* cam1;//camara que enfocara la zona donde se jugara
	Vector2f moveCam;//movemos camara
	Vector2f moveObj;//movemos obj
	Event* evento;//instancia de la clase evento que utilizaremos para manejar los dicho eventos
	//elementos que sirven para controlar los fps, los frames de la camara y el tiempo que maneja el loop del juego
	Clock* reloj;
	Time* tiempo1;
	float fps, t_frame, t2;

	Time* tiempo;//time para controlar visualizacion de carteles informativos
	
	b2World* Mundo;//el mundo del juego
	
	//elementos para crear el piso
	b2Body* b_floor;
	b2BodyDef b_floor_def;
	b2Fixture* f_floor;
	b2FixtureDef f_floor_def;
	RectangleShape* fig_f_r;
	Cuerpo* Floor;
	
	//elementos para crear el techo
	b2Body* b_roof;
	b2BodyDef b_roof_def;
	b2Fixture* f_roof;
	b2FixtureDef f_roof_def;
	RectangleShape* fig_r_r;
	Cuerpo* Roof;

	//elementos para crear la caja
	b2Body* b_box;
	b2BodyDef b_box_def;
	b2Fixture* f_box;
	b2FixtureDef f_box_def;
	RectangleShape* fig_box_r;
	Cuerpo* Box;

	//elementos para crear el primer obstaculo
	b2Body* b_box_o;
	b2BodyDef b_box_o_def;
	b2Fixture* f_box_o;
	b2FixtureDef f_box_o_def;
	RectangleShape* fig_box_o_r;
	Cuerpo* Obstaculo;

	//elementos para crear el segundo obstaculo
	b2Body* b_box_o2;
	b2BodyDef b_box_o2_def;
	b2Fixture* f_box_o2;
	b2FixtureDef f_box_o2_def;
	RectangleShape* fig_box_o2_r;
	Cuerpo* Obstaculo2;

	//elementos para crear la primera lampara
	b2Body* b_box_p;
	b2BodyDef b_box_p_def;
	b2Fixture* f_box_p;
	b2FixtureDef f_box_p_def;
	RectangleShape* fig_box_p_r;
	Texture* Box_pen_text;
	Sprite* Box_pen_spr;
	SpriteRenderer* lamp;
	b2DistanceJointDef cablecito;
	b2DistanceJoint* cablecin;

	//elementos para crear la segunda lampara
	b2Body* b_box_p1;
	b2BodyDef b_box_p1_def;
	b2Fixture* f_box_p1;
	b2FixtureDef f_box_p1_def;
	RectangleShape* fig_box_p1_r;
	Texture* Box_pen_text1;
	Sprite* Box_pen_spr1;
	SpriteRenderer* lamp1;
	b2DistanceJointDef cablecito1;
	b2DistanceJoint* cablecin1;

	//elementos para crear la base estatica donde estara la caja objetivo
	b2Body* b_box_e;
	b2BodyDef b_box_e_def;
	b2Fixture* f_box_e;
	b2FixtureDef f_box_e_def;
	RectangleShape* fig_box_e_r;
	Cuerpo* estatico;

	int contador=0;//contador para saber la cantidad de ragdolls lanzados

	// booleano para activar ragdolls
	bool activar_ragdoll;

	//creamos los Ragdolls
	Ragdoll* Ragdolls[5];
	//elemento de la clase colisiones que nos ayudara a registrar las colisiones de objetos de box2d
	Colisiones* hay_colision = NULL;

	int level=0;//nivel actual
	bool gano_el_nivel = false;//booleano que me dice si gane el nivel
	//
	Texture* t_botones[7];//texturas de los botones y mensajes
	Sprite* s_botones[7];//sprites de los botones y mensajes

	Vector2i posicion;//posicion del raton
	Vector2f coordenada;//posicion del raton en coordenadas

	Texture* txFondo;//textura del fondo
	Sprite* spFondo;//sprite del fondo
	Texture* txFondo1;//textura del fondo
	Sprite* spFondo1;//sprite del fondo
};
