#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Vector2F.h"
#include "GameManager.h"
#include <iostream>
#include <vector>
#include <string>

enum positioning {
	V_TOP,
	V_MIDDLE,
	V_BOTTOM,
	H_LEFT,
	H_CENTER,
	H_RIGHT
};

class Text2D{
private:
	std::vector<SDL_Texture*> textures;
	std::vector<std::string> lines;
	int lineheight = 0;
	int width, height;
	int horiz, verti;
	int fontsize;
	SDL_Color currentColor;
	Vector2F position;
	TTF_Font* weight;
protected:
	static TTF_Font* bold;
	static TTF_Font* normal;
	static TTF_Font* italic;
	static TTF_Font* ibold;
public:
	/*
	* CONSTRUCTOR: Constructs the message into renderable pieces.
	* @ param message - message to be constructed. May contain things like fontweight
	* and font color supplied with attributes like so:
	* EXAMPLE: "<W = BOLD, C = GREEN>Hello World"
	* This Hello World would be bold and the color green. The color and font weight 
	* will be set until another attribute is created. Even on different lines.
	* @ param fontsize - message will be constructed with this fontsize. this is essentially
	* pixel height.
	*
	*/
	Text2D(std::string message, int fontsize);
	
	void render();
	void update();
	void clean();
	
	/*
	* Sets the vertical alignment of all lines based on their lineheights.
	* If the lineheight is not set (0) or the lineheight is the same as the height of the line,
	* nothing will happen.
	* @param verti - Enumeration of the position:
		* V_TOP (0) - Sets Vertical alignment of top.
		* V_MIDDLE (1) - sets vertical alignment of middle.
		* V_BOTTOM (2) - sets vertical alignment of bottom.
	* No return.
	*/
	void alignVertical(int verti);
	/*
	* Sets the horizontal alignment of all lines
	* @param horiz - Enumeration of the position:
		* H_LEFT (3) - Sets horizontal alignment of left.
		* H_CENTER (4) - Sets horizontal alignment of center.
		* H_RIGHT (5) - Sets horizontal alignment of right.
	* No return.
	*
	*/
	void alignHorizontal(int horiz);

	/*
	* Sets and gets the current position of the text. This only sets the x and y.
	* NOTE: keep in mind the way that setWidth(int width) works below. See below.
	* @setPosition 
		* @param x value, y value (both pixel)
	* @getPosition
		* @return a vector2F object containing x and y. See above variable position.
	*/
	void setPosition(int x, int y);
	Vector2F getPosition();

	/*
	* Returns the width of the text.
	* If the width variable equals zero, will return GameManager::SCREENWIDTH minus
	* the current x position of the text.
	* @return width variable. See above.
	*/
	int getWidth();

	/*
	* Sets the maximum width of the text. Allows for wrapping.
	* A width of 0 will have a maximum of GameManager::SCREENWIDTH.
	* NOTE: This will take into account the top left corner of the text when calculating.
	* @param width to set. This is a pixel value.
	* @return false if the width exceeds GameManager::SCREENWIDTH.
	*/
	bool setWidth(int width);

	/*
	* Gets the current line height as a pixel value.
	* @return the value of the lineheight variable. see above.
	*/
	int getLineHeight();

	/*
	* Sets the line height of the text components.
	* If no line height is set, a lineheight of fontsize *1.15 pixels is chosen. (1.15)
	* @param line height to set. This is a pixel value.
	* @return true if the lineheight is valid, false if the lineheight is invalid.
	* Invalid lineheights include too short compared with the fontsize or exceeding
	* double spacing (fontsize*2.00).
	*/
	bool setLineHeight(int lineheight);
	
	/*
	* Gets the maximum or existing summation of height of the text components.
	* @return the value of height variable. See above.
	*/
	int getHeight();

	/*
	* Sets the total maximum height of all text components.
	* Lines * lineheight may not exceed this value. If set to 0, there is no maximum.
	* @param height: Total height of all of the text that it needs to fit into.
	* No return value.
	*/
	void setHeight(int height);

	/*
	* Handles loading the textures of the text, handles multiple colors set in the text
	* as well as the font weight if there are changes. See text setup in constructor for info.
	* @param message - current line to texturize.
	* @param color - color to set the current line's text.
	* @return texture created from this function. See text setup in constructor for details.
	*/
	SDL_Texture* loadTexture(const char* message, SDL_Color color);

};

