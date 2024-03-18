#include "Juego.h"


Juego::Juego(Vector2i resolucion, std::string titulo) {//constructor de la clase juego
	fps = 60;
	t_frame = 1 / 60.f;
	t2 = 0;
	wdw1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	wdw1->setFramerateLimit(fps);
	evento = new Event;
	reloj = new Clock;
	tiempo1 = new Time;
	tiempo = new Time;
	Start_game();
}

void Juego::Start_game() {//funcion que se encarga de cargar las fisicas, las imagenes, la camara y el loop en orden
	s_phy();
	s_i();
	set_cam();
	Loop();
}

void Juego::set_cam() {//seteamos la camara en las diferentes posiciones que necesitamos
	if (level == 0 || level == 1) {
		cam1 = new View({ 5.f,3.f }, { 10.f,10.f });
		cam1->move(45.f, 90.f);
		wdw1->setView(*cam1);
	}
	if (level > 1) {
		cam1 = new View({ 5.f,3.f }, { 10.f,10.f });
		cam1->move(45.f+ moveCam.x, 90.f);
		wdw1->setView(*cam1);
	}
}

void Juego::s_phy() {//inicializamos el mundo y los objetos dentro de él

	Mundo = new b2World(b2Vec2(0.f, 9.81f));//ceamos el mundo
	cannon = new Canon(Mundo, b2Vec2(46.f + moveCam.x, 97.f));//creamos el cañon
	cannon->S_T();//cargamos texturas del cañon
	hay_colision = new Colisiones;//creamo la instancia del colisionador
	Mundo->SetContactListener(hay_colision);//seteamos el colisionadir

	//piso
	b_floor_def.type = b2_staticBody;
	b_floor_def.position = b2Vec2(50.f + moveCam.x, 100.f);
	b_floor = Mundo->CreateBody(&b_floor_def);
	b2PolygonShape floor;
	floor.SetAsBox(50.f,2.5f);
	f_floor_def.shape = &floor;
	f_floor_def.restitution = 0.f;
	f_floor_def.density = 1.f;
	f_floor_def.friction = 0.3f;
	f_floor = b_floor->CreateFixture(&f_floor_def);
	fig_f_r = new RectangleShape;
	fig_f_r->setFillColor(Color::Yellow);
	Floor = new Cuerpo(b_floor, fig_f_r);

	//techo
	b_roof_def.type = b2_staticBody;
	b_roof_def.position = b2Vec2(50.f + moveCam.x, 85.6f);
	b_roof = Mundo->CreateBody(&b_roof_def);
	b2PolygonShape roof;
	roof.SetAsBox(50.f, 2.5f);
	f_roof_def.shape = &roof;
	f_roof_def.restitution = 0.f;
	f_roof_def.density = 1.f;
	f_roof_def.friction = 0.3f;
	f_roof = b_roof->CreateFixture(&f_roof_def);
	fig_r_r = new RectangleShape;
	fig_r_r->setFillColor(Color::Green);
	Roof = new Cuerpo(b_roof, fig_r_r);

	//caja
	b_box_def.type = b2_dynamicBody;
	b_box_def.position = b2Vec2(52.5f+ moveObj.x, 96.f);
	b_box = Mundo->CreateBody(&b_box_def);
	b2PolygonShape caja;
	caja.SetAsBox(.25f, .5f);
	f_box_def.shape = &caja;
	f_box_def.restitution = 0.f;
	f_box_def.density = 1.f;
	f_box_def.friction = 0.3f;
	f_box_def.userData.pointer = 2;
	f_box = b_box->CreateFixture(&f_box_def);
	fig_box_r = new RectangleShape;
	fig_box_r->setFillColor(Color::Blue);
	Box = new Cuerpo(b_box, fig_box_r);

	//caja_pendulo
	b_box_p_def.type = b2_dynamicBody;
	b_box_p_def.position = b2Vec2(50.f, 89.f);
	b_box_p = Mundo->CreateBody(&b_box_p_def);
	b2PolygonShape caja_pen;
	caja_pen.SetAsBox(.5f, .75f);
	f_box_p_def.shape = &caja_pen;
	f_box_p_def.restitution = 0.f;
	f_box_p_def.density = 1.f;
	f_box_p_def.friction = 0.3f;
	f_box_p = b_box_p->CreateFixture(&f_box_p_def);
	b_box_p->SetFixedRotation(true);
	Box_pen_text = new Texture;
	Box_pen_text->loadFromFile("Assets/Lamp2.png");
	Box_pen_spr = new Sprite;
	Box_pen_spr->setTexture(*Box_pen_text);
	lamp = new SpriteRenderer(b_box_p, Box_pen_spr);
	fig_box_p_r = new RectangleShape;
	fig_box_p_r->setFillColor(Color::Red);
	fig_box_p_r->setRotation(b_box_p->GetAngle() * 180 / b2_pi);

	//caja_pendulo1
	b_box_p1_def.type = b2_dynamicBody;
	b_box_p1_def.position = b2Vec2(50.f +33.f, 92.f);
	b_box_p1 = Mundo->CreateBody(&b_box_p1_def);
	b2PolygonShape caja_pen1;
	caja_pen1.SetAsBox(.5f, .75f);
	f_box_p1_def.shape = &caja_pen1;
	f_box_p1_def.restitution = 0.f;
	f_box_p1_def.density = 1.f;
	f_box_p1_def.friction = 0.3f;
	f_box_p1 = b_box_p1->CreateFixture(&f_box_p1_def);
	b_box_p1->SetFixedRotation(true);
	Box_pen_text1 = new Texture;
	Box_pen_text1->loadFromFile("Assets/Lamp2.png");
	Box_pen_spr1 = new Sprite;
	Box_pen_spr1->setTexture(*Box_pen_text1);
	lamp1 = new SpriteRenderer(b_box_p1, Box_pen_spr1);
	fig_box_p1_r = new RectangleShape;
	fig_box_p1_r->setFillColor(Color::Red);
	fig_box_p1_r->setRotation(b_box_p1->GetAngle() * 180 / b2_pi);

	//obstaculo
	b_box_o_def.type = b2_staticBody;
	b_box_o_def.position = b2Vec2(50.f +moveObj.x, 94.48f+ moveObj.y);
	b_box_o = Mundo->CreateBody(&b_box_o_def);
	b2PolygonShape obstaculo;
	obstaculo.SetAsBox(.25f, 3.f);
	f_box_o_def.shape = &obstaculo;
	f_box_o_def.restitution = 0.f;
	f_box_o_def.density = 1.f;
	f_box_o_def.friction = 0.3f;
	f_box_o = b_box_o->CreateFixture(&f_box_o_def);
	fig_box_o_r = new RectangleShape;
	fig_box_o_r->setFillColor(Color::Cyan);
	Obstaculo = new Cuerpo(b_box_o, fig_box_o_r);

	//obstaculo2
	b_box_o2_def.type = b2_staticBody;
	b_box_o2_def.position = b2Vec2(50.f + moveObj.x, 85.f + moveObj.y);
	b_box_o2 = Mundo->CreateBody(&b_box_o2_def);
	b2PolygonShape obstaculo2;
	obstaculo2.SetAsBox(.25f, 3.f);
	f_box_o2_def.shape = &obstaculo2;
	f_box_o2_def.restitution = 0.f;
	f_box_o2_def.density = 1.f;
	f_box_o2_def.friction = 0.3f;
	f_box_o2 = b_box_o2->CreateFixture(&f_box_o2_def);
	fig_box_o2_r = new RectangleShape;
	fig_box_o2_r->setFillColor(Color::Cyan);
	Obstaculo2 = new Cuerpo(b_box_o2, fig_box_o2_r);

	//caja estatica
	b_box_e_def.type = b2_staticBody;
	b_box_e_def.position = b2Vec2(52.5f+ moveObj.x, 97.f);
	b_box_e = Mundo->CreateBody(&b_box_e_def);
	b2PolygonShape caja_estatica;
	caja_estatica.SetAsBox(.5f, .25f);
	f_box_e_def.shape = &caja_estatica;
	f_box_e_def.restitution = 0.f;
	f_box_e_def.density = 1.f;
	f_box_e_def.friction = 1.f;
	f_box_e = b_box_e->CreateFixture(&f_box_e_def);
	fig_box_e_r = new RectangleShape;
	fig_box_e_r->setFillColor(Color::Black);
	estatico = new Cuerpo(b_box_e, fig_box_e_r);

	//joint para hacer el primer pendulo
	cablecito.Initialize(b_roof, b_box_p, b2Vec2(b_roof->GetPosition().x, b_roof->GetPosition().y + 0.5f), b2Vec2(b_box_p->GetPosition().x, b_box_p->GetPosition().y));
	cablecito.damping = 0.3f;
	cablecito.collideConnected = true;
	cablecin = (b2DistanceJoint*)Mundo->CreateJoint(&cablecito);

	//joint para hacer el segundo pendulo
	cablecito1.Initialize(b_roof, b_box_p1, b2Vec2(b_roof->GetPosition().x, b_roof->GetPosition().y + 0.5f), b2Vec2(b_box_p1->GetPosition().x, b_box_p1->GetPosition().y));
	cablecito1.damping = 0.3f;
	cablecito1.collideConnected = true;
	cablecin1 = (b2DistanceJoint*)Mundo->CreateJoint(&cablecito1);
	
}



void Juego::s_i() {//inicializamos las distintas imagenes
	//imagen del fondo de niveles
	txFondo = new Texture;
	txFondo->loadFromFile("Assets/palacio.jpg");
	spFondo = new Sprite;
	spFondo->setTexture(*txFondo);
	spFondo->setScale(0.03, 0.03);
	spFondo->setPosition(45+ moveCam.x, 88);

	//imagen del fondo del menu
	txFondo1 = new Texture;
	txFondo1->loadFromFile("Assets/logofondo.jpg");
	spFondo1 = new Sprite;
	spFondo1->setTexture(*txFondo1);
	spFondo1->setScale(0.0119, 0.025);
	spFondo1->setPosition(45 + moveCam.x, 88);

	//Boton para empezar el juego
	t_botones[0] = new Texture;
	t_botones[0]->loadFromFile("Assets/start1.png");
	s_botones[0] = new Sprite;
	s_botones[0]->setTexture(*t_botones[0]);
	s_botones[0]->setScale(0.003f, 0.003f);
	s_botones[0]->setPosition(49.25f, 91.f);

	//boton para salir del juego
	t_botones[1] = new Texture;
	t_botones[1]->loadFromFile("Assets/exit.png");
	s_botones[1] = new Sprite;
	s_botones[1]->setTexture(*t_botones[1]);
	s_botones[1]->setScale(0.004f, 0.004f);
	s_botones[1]->setPosition(49.2f +moveCam.x, 93.f);

	//titulo del juego
	t_botones[2] = new Texture;
	t_botones[2]->loadFromFile("Assets/RAGDOLL4.png");
	s_botones[2] = new Sprite;
	s_botones[2]->setTexture(*t_botones[2]);
	s_botones[2]->setScale(0.01f, 0.01f);
	s_botones[2]->setPosition(47.f + moveCam.x, 87.f);

	//imagen de nivel completado
	t_botones[3] = new Texture;
	t_botones[3]->loadFromFile("Assets/stage1.png");
	s_botones[3] = new Sprite;
	s_botones[3]->setTexture(*t_botones[3]);
	s_botones[3]->setScale(0.01f, 0.01f);
	s_botones[3]->setPosition(47.5f+ moveCam.x, 92.5f);

	//imagen de barra cargando el proximo nivel
	t_botones[4] = new Texture;
	t_botones[4]->loadFromFile("Assets/loadingnextlevel1.png");
	s_botones[4] = new Sprite;
	s_botones[4]->setTexture(*t_botones[4]);
	s_botones[4]->setScale(0.01f, 0.01f);
	s_botones[4]->setPosition(48.5f + moveCam.x, 90.f);

	//imagen de felicitaciones
	t_botones[5] = new Texture;
	t_botones[5]->loadFromFile("Assets/congrats1.png");
	s_botones[5] = new Sprite;
	s_botones[5]->setTexture(*t_botones[5]);
	s_botones[5]->setScale(0.01f, 0.01f);
	s_botones[5]->setPosition(47.f + moveCam.x, 91.f);

	//imagen de derrota
	t_botones[6] = new Texture;
	t_botones[6]->loadFromFile("Assets/you_lose.png");
	s_botones[6] = new Sprite;
	s_botones[6]->setTexture(*t_botones[6]);
	s_botones[6]->setScale(0.015f, 0.015f);
	s_botones[6]->setPosition(45.f + moveCam.x, 90.f);
}

void Juego::act_phy() {//actualizamos las fisicas del mundo
	Mundo->Step(t_frame, 8, 8);
	Mundo->ClearForces();
	Mundo->DebugDraw();
}

void Juego::ev() {//manejamos los eventos del juego
	while (wdw1->pollEvent(*evento))
	{
		//obtenemos posicion del mouse
		posicion = Mouse::getPosition(*wdw1);
		coordenada = wdw1->mapPixelToCoords(posicion);
		switch (evento->type) {
		case Event::Closed:
			exit(1);
			break;
		case Event::MouseMoved:
			//si nivel es = 1 o 2, actualizamos el cañon
			if (level == 1||level==2) {
				cannon->Update(wdw1);
			}
			
			break;
		case Event::MouseButtonPressed:
			if (level == 1||level==2) {
				//si nivel es = 1 o 2, actualizamos los ragdols
				UpdateRagdoll();
			}
			if (evento->mouseButton.button == Mouse::Button::Left && level==0) {
				if (s_botones[0]->getGlobalBounds().contains(coordenada.x, coordenada.y)) {//pulsando el primer boton, vamos al nivel 1
					level++;
				}
			}
			if (evento->mouseButton.button == Mouse::Button::Left && level == 0) {
				if (s_botones[1]->getGlobalBounds().contains(coordenada.x, coordenada.y)) {//pulsando el segundo boton, cerramos el juego
					wdw1->close();
				}
			}
			break;
		case Event::KeyPressed:
			if (evento->key.code == Keyboard::R) {//reiniciamos el juego al presionar R
				wdw1->close();
				new Juego({ 800, 600 }, "TPFinal_MAV2_Julian_Spahn");
			}
		}
	}
}

void Juego::draw() {//dibujamos los elementos del juego
	
	switch (level)
	{
		case 0:
			//dibujamos el menu
			wdw1->draw(*spFondo1);
			for (int i = 0; i < 3; i++) {
				wdw1->draw(*s_botones[i]);
				wdw1->draw(*s_botones[i]);
				wdw1->draw(*s_botones[i]);
			}
			break;
		case 1:
			//dibujamos el nivel 1
			wdw1->draw(*spFondo);
			Floor->draw_h(wdw1);
			Roof->draw_h(wdw1);
			Box->draw_h(wdw1);
			lamp->Draw(wdw1);
			Obstaculo->draw_h(wdw1);
			Obstaculo2->draw_h(wdw1);
			estatico->draw_h(wdw1);
			cannon->draw(wdw1);
			for (int i = 0; i < contador; i++) {
				if (!Ragdolls[i] || activar_ragdoll) {
					Ragdolls[i]->Draw(wdw1);
				}
			}
			if (gano_el_nivel==true && level == 1) {//mensajes si ganamos
				wdw1->draw(*s_botones[3]);
				wdw1->draw(*s_botones[4]);
				*tiempo = reloj->getElapsedTime();
			}
			if (contador >= 5 && gano_el_nivel == false) {//mensaje si perdemos
				wdw1->draw(*s_botones[6]);
			}
			break;
		case 2:
			//dibujamos el segundo nivel
			wdw1->draw(*spFondo);
			Floor->draw_h(wdw1);
			Roof->draw_h(wdw1);
			Box->draw_h(wdw1);
			lamp1->Draw(wdw1);
			Obstaculo->draw_h(wdw1);
			Obstaculo2->draw_h(wdw1);
			estatico->draw_h(wdw1);
			cannon->draw(wdw1);
			for (int i = 0; i < contador; i++) {
				if (!Ragdolls[i] || activar_ragdoll) {
					Ragdolls[i]->Draw(wdw1);
				}
			}
			if (contador >= 5 && gano_el_nivel == false) {//mensaje si perdemos
				wdw1->draw(*s_botones[6]);
			}
			break;
		case 3:
			//mensaje por ganar el juego
			wdw1->draw(*spFondo);
			wdw1->draw(*s_botones[5]);
			break;
		default:
		break;
	}
}

void Juego::update() {//actualizamos las coliciones

	if (hay_colision->hubo_contacto==true && contador <=5) {

		gano_el_nivel = true;
		if (tiempo->asSeconds() >= 15) {
			//movemos camara yobjetos
			moveCam.x = 33.f;
			moveCam.y = 4.f;
			moveObj.x = 31.5f;
			moveObj.y = 2.f;
			//incrementamos el nivel y reiniciamos el contador
			level++;
			contador = 0;
			//seteamos a false el booleano de ganar el nivel y reiniciamos el juego
			gano_el_nivel = false;
			Start_game();
		}

	}
}

void Juego::Loop() {//loop del juego
	while (wdw1->isOpen()) {
		*tiempo1 = reloj->getElapsedTime();
		if (t2 + t_frame < tiempo1->asSeconds()) {
			t2 = tiempo1->asSeconds();
			wdw1->clear();
			update();
			ev();
			act_phy();
			draw();
			wdw1->display();
		}
	}
}

void Juego::UpdateRagdoll() {//funcion para actualizar a los ragdolls (los lanza)
	//posicion del mouse
	Vector2i posiciones;
	Vector2f coordenadas;
	posiciones = Mouse::getPosition(*wdw1);
	coordenadas = wdw1->mapPixelToCoords(posiciones);
	if (level >= 0 && contador < 5) {
		activar_ragdoll = true;
		if (contador < 5) {
			//si el contador es menor a 5, creamos ragdolls y les aplicamos fuerza, luego incrementamos el contador 
			Ragdolls[contador] = new Ragdoll({ cannon->GetXPosition() + 0.1f , cannon->GetYPosition() - 1.5f }, *Mundo);
			Ragdolls[contador]->ApplyForce({ coordenadas.x - cannon->GetXPosition(), coordenadas.y - cannon->GetYPosition() });
			contador++;
		}
	}
}


