#pragma once
#include <GL/glew.h>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <vector>
using namespace std;


enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

struct Glyph {
	GLuint texture;
	float depth;
	Vertex topLeft;
	Vertex topRight;
	Vertex bottomLeft;
	Vertex bottomRight;
};

class RenderBatch {
public:
	RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) :
		offset(Offset),
		numVertices(NumVertices),
		texture(Texture) {}              //constructor
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();
	void init();

	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
	void renderBatch();

private:
	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();
	static bool compareFrontToback(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);

	GLuint _vbo;
	GLuint _vao;

	GlyphSortType _sortType;

	vector<Glyph*> _glyphs;
	vector<RenderBatch> _renderBatches;
};
