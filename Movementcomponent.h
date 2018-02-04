//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B
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
