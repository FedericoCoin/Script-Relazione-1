#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
	float xf=1;

	while (1.0f + xf != 1.0f)
	{
		xf /=2;
	}
	cout << "Errore float: "<< setprecision(8) << xf<< endl;
	cout << "Rappesentazione binaria: 0.";
	for (int i = 0; i < 25;i++)
	{
		xf *= 2.0f;
		if (xf > 1.0f)
		{
			cout << "1";
			xf -= 1.0f;
		}
		else
		{
			cout << "0";
		}
		
	}
	cout << endl;
	double xd = 1;
	while (1.0d + xd != 1.0d)
	{
		xd /= 2.0d;
	}
	cout << "Errore double: " << setprecision(8) << xd << endl;
	cout << "Rappesentazione binaria: 0.";
	for (int i = 0; i < 54; i++)
	{
		xd *= 2.0d;
		if (xd > 1.0d)
		{
			cout << "1";
			xd -= 1.0d;
		}
		else
		{
			cout << "0";
		}

	}
	cout << endl;
	long double xl = 1;
	while (1.0l + xl != 1.0l)
	{
		xl /= 2.0l;

	}
	cout << "Errore long: " << setprecision(8) << xl << endl;
	return 0;
}