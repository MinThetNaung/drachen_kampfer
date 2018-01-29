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
