#pragma once
//MovementComponent.h
class MovementComponent
{
public:
	void update();
private:
	int velocity_x;
	int velocity_y;
	VECTOR2 velocity;       // velocity
};
