#pragma once

#include "../Addons/bytecolor_loader.hpp"
#include "../Types.hpp"
#include "GameObject.hpp"

class Image : public GameObject {
protected:
	ColorData data;

	bool flipped_y;
	bool flipped_x;

	Vector2 position;
public:
	/*
	* Creates a new image with empty data.
	*/
	Image(void);

	/*
	* Creates a new image from a ByteColorImage object.
	*/
	Image(ByteColorImage* image);

	/*
	* Drawn the image on the screen.
	*/
	virtual void draw(void) override;
	
	/*
	* Skip the implementation of update().
	*/
	virtual void update(double delta_time) override {}

	/*
	* Skip the implementation of input().
	*/
	virtual void input(InputEvent* event) override {}

	// Computed properties.

	/*
	* Calculate the left most side.
	*/
	double left(void) const { return position.x; }

	/*
	* Calculate the right most side.
	*/
	double right(void) const { return position.x + data.size.width; }

	/*
	* Calculate the top most side.
	*/
	double top(void) const { return position.y; }

	/*
	* Calculate the bottom most side.
	*/
	double bottom(void) const { return position.y + data.size.height; }

	// Accessors.

	/*
	* The current size of the sprite.
	*/
	Size2d getSize(void) const { return data.size; }

	/*
	* Width of the sprite in cells.
	*/
	double getWidth(void) const { return data.size.width; }

	/*
	* Height of the sprite in cells.
	*/
	double getHeight(void) const { return data.size.height; }

	/*
	* The color data of the sprite.
	*/
	const ColorData& getData(void) const { return data; }

	/*
	* Sets the color data, width and height from a ByteColorImage object.
	*/
	inline void setData(ByteColorImage* image) { data.colors = image->data; data.size.width = image->width; data.size.height = image->height; }

	/*
	* Flipped along X axis.
	*/
	bool isFlippedX(void) const { return flipped_x; }

	/*
	* Flip or restore along X axis.
	*/
	inline void setFlipX(bool flip) { flipped_x = flip; }

	/*
	* Flipped along Y axis.
	*/
	bool isFlippedY(void) const { return flipped_y; }

	/*
	* Flip or restore along Y axis.
	*/
	inline void setFlipY(bool flip) { flipped_y = flip; }

	/*
	* The color to ignore while painting on the screen.
	* By default, undefined.
	*/
	Color getColorKey(void) const { return data.color_key; }

	/*
	* Set color to ignore while painting on the screen.
	* By default, undefined.
	*/
	inline void setColorKey(Color value) { data.color_key = value; }

	/*
	* The current object position.
	*/
	Vector2 getPosition(void) const { return position; }

	/*
	* Horizontal position of the object in cells.
	*/
	double getX(void) const { return position.x; }

	/*
	* Vertical position of the object in cells.
	*/
	double getY(void) const { return position.y; }

	/*
	* Update the object position.
	*/
	inline void setPosition(double x, double y) { position.x = x; position.y = y; }
	inline void setPosition(Vector2 position) { this->position.x = position.x; this->position.y = position.y; }

	/*
	* Update the horizontal position.
	*/
	inline void setX(double x) { position.x = x; }

	/*
	* Update the vertical position.
	*/
	inline void setY(double y) { position.y = y; }
};

