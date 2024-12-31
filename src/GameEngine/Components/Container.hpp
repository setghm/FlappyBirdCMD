#pragma once

#include <vector>
#include <functional>
#include "GameObject.hpp"

typedef std::function<void(GameObject* item, int index)> ContainerForEachCallback;
typedef std::function<bool(GameObject* item)> ContainerFilterCallback;

class Container : public GameObject {
private:
	std::vector<GameObject*> children;
public:
	Container() : GameObject() {}

	/*
	* When the object is deleted, all its children are deleted too.
	*/
	~Container();

	/*
	* Draws all the object's children on the screen.
	*/
	virtual void draw(void) override;

	/*
	* Updates all the object's children.
	*/
	virtual void update(double delta_time) override;

	/*
	* Process an input event on each of the object's children.
	*/
	virtual void input(InputEvent* event) override;

	/*
	* Execute a function on each children.
	*/
	virtual void forEach(ContainerForEachCallback callback);

	/*
	* Adds a game object pointer and its ownership to this object,
	* so you don't need to remove it manually.
	*/
	void addChild(GameObject* child);

	/*
	* Removes a game object and its ownership, so you need to remove it
	* manually.
	*/
	GameObject* removeChild(GameObject* child);

	/*
	* Filter all the child objects that satisfies the given predicate.
	*/
	std::vector<GameObject*> filter(ContainerFilterCallback callback);

	/*
	* Deletes all the child objects.
	*/
	void clear(void);

	// Accessors.

	/*
	* Get a reference to the children vector.
	*/
	std::vector<GameObject*>& getChildren(void) { return children; }
};

