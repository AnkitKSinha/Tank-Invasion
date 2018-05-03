#include<math.h>

float proheight(float velocity, float angle)
{
	float radian=3.14592 * angle/180;
	return (( pow(velocity,2) * pow(sin(radian), 2) )/(19.6));
}

float prorange(float velocity, float angle)
{
	float radian=3.14592 * angle/180;
	return (( pow(velocity,2) * sin(2*radian) )/(9.8));
}

float protime(float velocity,float angle)
{
	float radian=3.14592 * angle/180;
	return ( (2*velocity*sin(radian))/(9.8));
}
float proycord(float velocity, float angle, float xcord)
{
	float radian=3.14592 * angle/180;
	return ( tan(radian)*xcord )-( 9.8*pow(xcord,2) /( 2*pow(velocity,2)*pow(cos(radian),2) ) );
}


