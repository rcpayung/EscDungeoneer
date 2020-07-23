#pragma once
#include "ItemSlot.h"
class GlyphSlot : public ItemSlot {
private:
	GlyphType glyphtype = GlyphType::UNSET;
public:
	GlyphSlot(int x, int y, int w, int h);
	void update();
	void render();
	void clean();
	void setItem(Item* item) override;
	void handleEvents(SDL_Event* e);
	GlyphType getGType();
	void setGlyphType(GlyphType t);
};

