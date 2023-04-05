#include <iostream>
#include <cmath>
#include <iomanip>
#include "Esercitazione.h"
using namespace std;

int main()
{
	//Calcolo variabili adimensionali
	double pi = 3.141592653589793;
	double hc = 197.327;
    double Mnc = 939.565;
    double Mpc = 938.272;
    double Vo = 38.5;
    double R = 1.93;
    double v = (Vo*2*Mnc*Mpc*pow(R,2))/(pow(hc,2)*(Mpc+Mnc));
	cout << v << endl;
    double lambda = (pow(hc,2)*(Mpc+Mnc))/(2*Mnc*Mpc*pow(R,2));
	//Calcolo condizione=0 con tre algoritmi diversi
	double e = Bisezione(condizione, 0, 0, 2, 1e-8, &v);
	cout<<"Soluzione tramite metodo di bisezione: "<<setprecision(8)<<Bisezione(condizione,0,0,2,1e-8,&v)<<endl;
	cout<<"Soluzione tramite metodo delle secanti: "<<setprecision(8)<<Secanti(condizione,0,0,1,1e-8,&v)<<endl;
	cout<<"Soluzione tramite metodo Newton-Raphson: "<<setprecision(8)<<Newton_Raphson(condizione,0,2,1e-6,1e-8,&v)<<endl;
	cout<<"Energia stato legato: "<<-e*lambda<<" MeV"<<endl;
	//Modifico Vo
	Vo=27.4;
	//Nuovo valore di v
	v = (Vo*2*Mnc*Mpc*pow(R,2))/(pow(hc,2)*(Mpc+Mnc));
	//cout<<v<<endl;
	//In questo caso non esistono soluzioni legate,infatti
	cout <<"condizione(0)= " << condizione(0, &v) << endl;
	//Determino il minimo valore di v per avere uno stato legato
	double intervallo[2];
	intervallo[0]= Newton_Raphson(cotsqrt, 0, 1, 1e-6, 1e-8, NULL);
	//Cerco il valore di v in cui func=0 è positivo
	while (condizione(0, &v) < 1)
	{
		v ++;
	}
	//Determino il massimo valore di v per avere uno stato legato
	intervallo[1]= Newton_Raphson(cotsqrt, 0, v, 1e-6, 1e-8, NULL);
	v = intervallo[1];
	cout<<"Il sistema ha un solo stato legato per intevalli di v tra "<<intervallo[0]<<" e " <<intervallo[1]<<endl;
	
	cout << "Il sistema ha un solo stato legato per intevalli di kR tra ";
	cout << sqrt(intervallo[0]) << " e " << sqrt(intervallo[1] - Newton_Raphson(condizione, 0, 14,1e-6, 1e-8, &v)) << endl;

	//Torno allo stato iniziale
	Vo = 38.5;
	v = (Vo * 2 * Mnc * Mpc * pow(R, 2)) / (pow(hc, 2) * (Mpc + Mnc));
	//Definisco i parametri di integrazione
	double alpha = sqrt(v - e),beta=2*sqrt(e);
	cout << "Alfa: " << alpha << ",Beta: " << beta << endl;
	//Calcolo analiticamente il rapporto tra le costanti B/A
	double c = (sin(alpha) * exp(beta / 2));
	//Verifico che in x=1 ci sia l'eguaglianza
	double Norm2 = (IntegraleSimpson(FuncA, 0, 1,1000, &alpha) + pow(c, 2)*((1/(beta))-IntegraleSimpson(FuncC, 0, 1,1000, &beta)));
    cout <<"Norma^2: " << Norm2 << endl;
	
    //Calcolo del valore di aspettazione del raggio quadratico medio
	double x2 = (IntegraleSimpson(FuncB, 0, 1, 1000, &alpha) + pow(c, 2)*((2 / pow(beta, 3)) - IntegraleSimpson(FuncD, 0, 1,1000, &beta)))/(Norm2*pow(R,2));
    cout <<"<x^2> :" << x2 << endl;
	cout << "<r^2> :" << x2*(pow(R, 2)) << endl;
	
	
	return 0;

}

