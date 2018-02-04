//  Module:             Gameplay Programming
//  Assignment1:        Drachen kamper
//  Student Name:       Bryan Boh, Naing Ye Yint Zaw, Min Thet Naung
//  Student Number:     S10171537F, S10167279K, S10167248B
#include "Healthcomponent.h"

void HealthComponent::update()
{
	if (currenthealth <= 0)
		isalive = false;

}

int HealthComponent::getchealth()
{
	return currenthealth;
}

void HealthComponent::setchealth(int i)
{
	currenthealth = i;
}

int HealthComponent::getmhealth()
{
	return maxhealth;
}

void HealthComponent::setmhealth(int i)
{
	maxhealth = i;
}
