#include "GlyphSlot.h"

GlyphSlot::GlyphSlot(int x, int y, int w, int h) : ItemSlot(x, y, w, h, GameManager::scale) {
	this->setAllowedItemType(ItemType::GLYPH);
}

void GlyphSlot::update() {
	__super::update();
}

void GlyphSlot::render() {
	__super::render();
	__super::renderItem();
}

void GlyphSlot::clean() {
	__super::clean();
}

void GlyphSlot::setItem(Item* item) {
	if (item == nullptr) {
		this->item = nullptr;
		return;
	}
	if (item->getType() == ItemType::GLYPH) {
		this->item = item;
		return;
	}
	else {
		printf("Item %s not a glyph\n", item->getName().c_str());
	}
}

void GlyphSlot::handleEvents(SDL_Event* e) {
	__super::handleEvents(e);
}

GlyphType GlyphSlot::getGType() {
	return this->glyphtype;
}
void GlyphSlot::setGlyphType(GlyphType t) {
	this->glyphtype = t;
}