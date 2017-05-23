#ifndef LOGIC
#define LOGIC

#include <vector>
#include "Cylinder.h"

using namespace std;

class Logic {

	vector<Cylinder*> objs;
	vector<Cylinder*> newObjs;

public:
	Logic();
	~Logic();

	Cylinder* createNewCylinder();
	vector<Cylinder*> getObjects();
	vector<Cylinder*> getNewObjs();

	void clearNewObjs() {
		newObjs.clear();
	}
};

#endif LOGIC