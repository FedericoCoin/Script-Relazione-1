#include <iostream>
#include <cmath>
#include <iomanip>
#include "Esercitazione.h"
using namespace std;


int main()
{
	//Definisco le costanti
	double A=1.0,B=1.0,alpha=2,beta=0.5;
	//Soluzioni integrali (Calcolate analiticamente)
	double Sol[4]={(4-sin(4))/8,(32-12*cos(4)-21*sin(4))/192,2/sqrt(exp(1.0d)),26/sqrt(exp(1.0d))};
	//Derivate seconde in A
	double Der2[4]={5.229,9.63,0.25,2};
	//Derivate quarte in A
	double Der4[4]={83.66,214.658,0.0625,3};
	//Definisco l'errore: 1e-4 o 1e-6, a seconda della richiesta dell'esercizio
	double delta=1e-4;
	//Calcolo i rispettivi N per avere delta come errore massimo
	int NTrapezio[4], NSimpson[4];
	for(int i=0;i<4;i++)
	{
		NTrapezio[i]=(int)sqrt((1/(12*delta))*Der2[i]);
		if (NTrapezio[i] % 2 == 1)
		{
			NTrapezio[i] += 1;
		}
		NSimpson[i]=(int)pow((1/(180*delta))*Der4[i],0.25);
		if (NSimpson[i] % 2 == 1)
		{
			NSimpson[i] += 1;
		}
		cout <<Sol[i] << endl;

	}

	cout << "Integrale della funzione a: "<<endl;
	cout << "Tramite il metodo dei trapezi: ";
	cout << IntegraleTrapezio(FuncA, 0, A, NTrapezio[0], &alpha) << endl;
	cout << "Errore: " << Sol[0] - IntegraleTrapezio(FuncA, 0, A, NTrapezio[0], &alpha) << endl;
	cout << "Tramite il metodo Simpson: ";
	cout << IntegraleSimpson(FuncA, 0, A, NSimpson[0], &alpha) << endl;
	cout << "Errore: " << Sol[0] - IntegraleSimpson(FuncA, 0, A, NSimpson[0], &alpha) << endl;
	cout << "/////////" << endl;

	cout << "Integrale della funzione b: " << endl;
	cout << "Tramite il metodo dei trapezi: ";
	cout << IntegraleTrapezio(FuncB, 0, A, NTrapezio[1], &alpha) << endl;
	cout << "Errore: " << Sol[1] - IntegraleTrapezio(FuncB, 0, A, NTrapezio[1], &alpha) << endl;
	cout << "Tramite il metodo Simpson: ";
	cout << IntegraleSimpson(FuncB, 0, A, NSimpson[1], &alpha) << endl;
	cout << "Errore: " << Sol[1] - IntegraleSimpson(FuncB, 0, A, NSimpson[1], &alpha) << endl;
	cout << "/////////" << endl;

	cout << "Integrale della funzione c: " << endl;
	cout << "Tramite il metodo dei trapezi: ";
	cout << ((1 / beta) - IntegraleTrapezio(FuncC, 0, B, NTrapezio[2], &beta)) << endl;
	cout << "Errore: " << Sol[2] - ((1/beta)-IntegraleTrapezio(FuncC, 0, B, NTrapezio[2], &beta)) << endl;
	cout << "Tramite il metodo Simpson: ";
	cout <<  ((1 / beta) - IntegraleSimpson(FuncC, 0, B, NSimpson[2], &beta)) << endl;
	cout << "Errore: " << Sol[2] - ((1 / beta) - IntegraleSimpson(FuncC, 0, B, NSimpson[2], &beta)) << endl;
	cout << "/////////" << endl;

	cout << "Integrale della funzione d: " << endl;
	cout << "Tramite il metodo dei trapezi: ";
	cout << ((2 / pow(beta, 3)) - IntegraleTrapezio(FuncD, 0, A, NTrapezio[3], &beta)) << endl;
	cout << "Errore: " << Sol[3] - ((2/pow(beta,3))-IntegraleTrapezio(FuncD, 0, A, NTrapezio[3], &beta)) << endl;
	cout << "Tramite il metodo Simpson: ";
	cout << ((2 / pow(beta, 3)) - IntegraleSimpson(FuncD, 0, A, NSimpson[3], &beta)) << endl;
	cout << "Errore: " << Sol[3] - ((2 / pow(beta, 3)) - IntegraleSimpson(FuncD, 0, A, NSimpson[3], &beta)) << endl;
	cout << "/////////" << endl;
	return 0;
}

