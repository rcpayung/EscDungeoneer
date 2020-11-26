#pragma once
#include "Item.h"

class Glyph : public Item {
private:
	GlyphType glyphtype;
public:
	Glyph();
	void render();
	void update();
	void handleEvents(SDL_Event* e);
	void clean();
	GlyphType getGType();
	void setGType(GlyphType type);
};

