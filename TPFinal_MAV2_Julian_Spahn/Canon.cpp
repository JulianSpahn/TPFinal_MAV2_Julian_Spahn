#include "Canon.h"

Canon::Canon(b2World* world, const b2Vec2& position) {//constructor del cañon
	// Creando el cañon
	b_canon_def.type = b2_staticBody;
	b_canon_def.position = position;
	b_canon = world->CreateBody(&b_canon_def);

	b2PolygonShape canon;
	canon.SetAsBox(0.8f, 0.8f);

	f_canon_def.shape = &canon;
	f_canon_def.density = 1.f;
	f_canon_def.restitution = 0.1f;
	f_canon_def.friction = 0.3f;

	f_canon = b_canon->CreateFixture(&f_canon_def);
}
void Canon::S_T() {//funcion para inicializar las texturas
	// cargamos textura
	t_cannon = new Texture;
	t_cannon->loadFromFile("Assets/newcanon.png");
	//cargamos sprite
	s_cannon = new Sprite;
	s_cannon->setTexture(*t_cannon);
	//creamos el shape
	fig_c_r = new RectangleShape(Vector2f(0.8f, 0.8f));
	//unimos el sprite con el body del cañon
	cannon = new SpriteRenderer(b_canon, s_cannon);
}
void Canon::draw(RenderWindow* wndw) {//funcion para dibujar el cañon
	cannon->Draw(wndw);
}

void Canon::Update(RenderWindow* wnd) {//funcion con la que actualizamos el cañon
	Vector2i mousePos;
	Vector2f mousePosCoord;
	mousePos = Mouse::getPosition(*wnd);
	mousePosCoord = wnd->mapPixelToCoords(mousePos);
	b_canon->SetTransform(b_canon->GetPosition(), atan2f(mousePosCoord.y - b_canon->GetPosition().y, mousePosCoord.x - b_canon->GetPosition().x));
}

int Canon::GetXPosition() {//obtenemos posicion en x para luego usarla al axtualizar la posicion del cañon
	return b_canon->GetPosition().x;
}

int Canon::GetYPosition() {//obtenemos posicion en y para luego usarla al axtualizar la posicion del cañon
	return b_canon->GetPosition().y;
}