//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B
#pragma once
class HealthComponent
{
public:
	void update();
	int getchealth();
	void setchealth(int i);
	int getmhealth();
	void setmhealth(int i);
private:
	int currenthealth;
	int maxhealth;
	bool isalive = true;
};
