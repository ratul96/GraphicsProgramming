#pragma once
#pragma once
#include"GameObject.h"
class Tree :public GameObject
{
public:
	Tree();
	~Tree();
	void Update(float deltaTS);
private:
	float scale = 1.1;
};
