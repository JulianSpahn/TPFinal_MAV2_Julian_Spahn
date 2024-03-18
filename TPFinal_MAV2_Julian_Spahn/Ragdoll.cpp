#include "Ragdoll.h"

Ragdoll::Ragdoll(Vector2f pos, b2World& World) {//constructor de los ragdolls
	b2PolygonShape b_Shape[6];

	b_Shape[0].SetAsBox(0.1, 0.1);
	b_Shape[1].SetAsBox(0.2, 0.4);
	b_Shape[2].SetAsBox(0.07, 0.3);
	b_Shape[3].SetAsBox(0.07, 0.3);
	b_Shape[4].SetAsBox(0.07, 0.4);
	b_Shape[5].SetAsBox(0.07, 0.4);

	b_rag_def[0].position = b2Vec2(pos.x, pos.y + 0.1f);
	b_rag_def[1].position = b2Vec2(pos.x, pos.y + 0.65f);
	b_rag_def[2].position = b2Vec2(pos.x + 0.32f, pos.y + 0.5f);
	b_rag_def[3].position = b2Vec2(pos.x - 0.32f, pos.y + 0.5f);
	b_rag_def[4].position = b2Vec2(pos.x + 0.09f,pos.y + 1.5f);
	b_rag_def[5].position = b2Vec2(pos.x - 0.09f, pos.y + 1.5f);


	for (int i = 0; i < 6; i++) {
		b_rag_def[i].type = b2_dynamicBody;
		b_rag[i] = World.CreateBody(&b_rag_def[i]);
		f_rag_def[i].shape = &b_Shape[i];
		f_rag_def[i].density = 1.f;
		f_rag_def[i].friction = 0.5f;
		f_rag_def[i].restitution = 0.1f;
		f_rag_def[i].userData.pointer = 1;
		f_rag[i] = b_rag[i]->CreateFixture(&f_rag_def[i]);
	}

	cable_def[0].Initialize(b_rag[0], b_rag[1], b2Vec2(b_rag[0]->GetPosition().x, b_rag[0]->GetPosition().y + 0.08), b2Vec2(b_rag[1]->GetPosition().x, b_rag[1]->GetPosition().y - 0.38));
	cable_def[1].Initialize(b_rag[1], b_rag[2], b2Vec2(b_rag[1]->GetPosition().x + 0.10, b_rag[1]->GetPosition().y - 0.38), b2Vec2(b_rag[2]->GetPosition().x, b_rag[2]->GetPosition().y - 0.28));
	cable_def[2].Initialize(b_rag[1], b_rag[3], b2Vec2(b_rag[1]->GetPosition().x - 0.10, b_rag[1]->GetPosition().y - 0.38), b2Vec2(b_rag[3]->GetPosition().x, b_rag[3]->GetPosition().y - 0.28));
	cable_def[3].Initialize(b_rag[1], b_rag[4], b2Vec2(b_rag[1]->GetPosition().x + 0.10, b_rag[1]->GetPosition().y + 0.38), b2Vec2(b_rag[4]->GetPosition().x, b_rag[4]->GetPosition().y - 0.28));
	cable_def[4].Initialize(b_rag[1], b_rag[5], b2Vec2(b_rag[1]->GetPosition().x + 0.10, b_rag[1]->GetPosition().y + 0.38), b2Vec2(b_rag[5]->GetPosition().x, b_rag[5]->GetPosition().y - 0.28));
	
	for (int i = 0; i < 5; i++) {
		cable_def[i].damping = 0.3f;
		cable_def[i].stiffness = 0.9f;
		cable_def[i].length = 0.00025f;
		cable_def[i].collideConnected = true;
		cable[i] = (b2DistanceJoint*)World.CreateJoint(&cable_def[i]);
	}

	for (int i = 0; i < 6; i++) {
		fig_b_r[i] = new RectangleShape;
	}

	fig_b_r[0]->setFillColor(Color::Magenta);
	fig_b_r[1]->setFillColor(Color::Green);
	fig_b_r[2]->setFillColor(Color::Red);
	fig_b_r[3]->setFillColor(Color::Blue);
	fig_b_r[4]->setFillColor(Color::Magenta);
	fig_b_r[5]->setFillColor(Color::Yellow);

	for (int i = 0; i < 6; i++)
	{
		Humano[i] = new Cuerpo(b_rag[i], fig_b_r[i]);
	}
}

void Ragdoll::Draw(RenderWindow* wdw) {//funcion para dibujar el ragdoll
	for (int i = 0; i < 6; i++) {
		Humano[i]->draw_h(wdw);
	}
}

void Ragdoll::ApplyForce(Vector2f posiciones) {//funcion para aplicarle fuerza al ragdoll
	for (int i = 0; i < 6; i++) {
		b_rag[i]->ApplyForceToCenter(b2Vec2(posiciones.x * 30, posiciones.y * 30), false);
	}
}

Vector2f Ragdoll::GetPosition(int i) {//funcion para obtener la posicion del ragdoll
	Vector2f RagdollPos = Vector2f(fig_b_r[i]->getPosition());
	return RagdollPos;
}

void Ragdoll::UpdatePositions() {//funcion para actualizar la posicion del ragdoll
	for (int i = 0; i < 6; i++) {
		fig_b_r[i]->setPosition(b_rag[i]->GetPosition().x, b_rag[i]->GetPosition().y);
		fig_b_r[i]->setRotation(b_rag[i]->GetAngle() * 180 / 3.14f);
	}
}