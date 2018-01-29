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
