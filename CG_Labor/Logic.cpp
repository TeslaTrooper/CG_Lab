#include "Logic.h"

Logic::Logic() {

}

Logic::~Logic() {}

Cylinder* Logic::createNewCylinder() {
	Cylinder* obj = new Cylinder(0.05, 0.5);
	objs.push_back(obj);
	newObjs.push_back(obj);

	return obj;
}

vector<Cylinder*> Logic::getObjects() {
	return objs;
}

vector<Cylinder*> Logic::getNewObjs() {
	return newObjs;
}
