#include "Sun.h"

Sun ::Sun(void)
{
}

Sun::~Sun(void)
{
}

bool Sun::createSun(long double mass)
{
	sunMass = mass;

	return true;
}

bool Sun::setSunMass(long double mass)
{
	sunMass = mass;

	return true;
}

long double Sun::getSunMass()
{
	return sunMass;
}

void Sun::destroySun()
{
}

char* Sun::getShowString()
{
	return "I am the destroyer.";
}