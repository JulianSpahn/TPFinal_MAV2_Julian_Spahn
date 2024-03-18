#pragma once
#include"Box2D.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class SFMLRenderer : public b2Draw {
private:
	RenderWindow *wnd;

public:
	// Constructor
	SFMLRenderer(RenderWindow *window);
	~SFMLRenderer(void);

	// Recibe los c�digos de colores
	inline Color box2d2SFMLColor(const b2Color &_color);
	
	// Dibuja pol�gono
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	
	// Dibuja pol�gono s�lido
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	
	// Dibuja c�rculo
	void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override;
	
	// Dibuja c�rculo s�lido
	void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override;
	
	// Dibuja segmento
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
	
	// Dibuja los elementos que recibe y los transforma
	void DrawTransform(const b2Transform& xf) override;
	
	// Dibuja punto
	void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;
	
	// Dibuja las letras
	void DrawString(float x, float y, const char* string, ...);

	// Dibuja coordenadas
	void DrawAABB(b2AABB* aabb, const b2Color& color);
	
};