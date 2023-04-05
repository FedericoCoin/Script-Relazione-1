#include <stdio.h>
#include <math.h>

/*
x : variabile funzione
par : vettore contenente i paramentri della funzione
npar : numero di parametri
Newton_Raphson : funzione che calcola la soluzione di func=y partendo dal valore xi,
                 dx e' l'accuratezza con cui calcola la derivata di f tramite differenza finita
                 (per variabili double intorno a 3e-8)
Secanti : funzione che calcola la soluzione di func=y partendo dai valori x0 e x1
Bisezione : funzione che calcola la soluzione di func=y partendo dai valori x0 e x1, la soluzione deve essere contenuta 
            in [x0,x1], tol e' la tolleranza della soluzione, per questo algoritmo abbiamo che l'errore sulla soluzione 
            e' - tol/2
*/

double function(double x, double* par, int npar){
	return 1 / (tan(sqrt(*par - x))) + sqrt(x) / sqrt(*par - x);
}

double FuncA(double x,double *par,int npar){
	return pow(sin(*par*x),2);
}

double FuncB(double x,double *par,int npar){
	return pow(x,2)*pow(sin(*par*x),2);
}

double FuncC(double x,double *par,int npar){
		return exp(-(*par)*x);
}

double FuncD(double x,double *par,int npar){
		return pow(x,2)*exp(-(*par)*x);
}

//derivata centrale (es.2)
double derivative(double (*func)(double,double*,int),double x,double dx,double *par,int npar){
		return (func(x + dx,par,npar) - func(x,par,npar)) / dx;
}

//a,b estremi di integrazione e res numero di divisioni dell'intervallo
double IntegraleTrapezio(double (*func)(double,double*,int),double a,double b,int res,double *par,int npar){
	double result = 0;
	double dx = (b-a)/res;              //divisione intervallo di integrazione, dx e' h
	double x = a;
	for (int i=1; i<res; i++){          //sommatoria da 1 a N-1
	    x += dx;
		result += dx * func(x,par,npar);
	}
	result += (dx/2) * (func(a,par,npar) + func(b,par,npar));
	return result;
}
//analogo a IntegraleTrapezio
double IntegraleSimpson(double (*func)(double,double*,int),double a,double b,int res,double *par,int npar){
	double result = func(a,par,npar) + func(b,par,npar);		//somma funzione valutata in a e b
	double x = a;
	double dx = (b-a)/res;										//divisione intervallo di integrazione, dx e' h
    for (int i=1; i<res; i++){									//sommatoria da 1 a N-1
        x += dx;		
		if (i % 2 == 0){										//termini pari
			result += func(x,par,npar) * 2;				
		}
		else{													//termini dispari
			result += func(x,par,npar) * 4;
		}
	}
	return result * dx/3;
}
double Newton_Raphson(double (*func)(double, double*, int), double y, double xi, double dx, double tol, double* par, int npar)
{
	double x = xi;
	while (abs(func(x, par, npar) - y) > tol)
	{
		x -= func(x, par, npar) / derivative(func, x, dx, par, npar);
		//cout<<setprecision(8)<<x<<endl;
	}
	return x;
}

double Secanti(double (*func)(double, double*, int), double y, double x0, double x1, double tol, double* par, int npar)
{
	while (abs(func(x1, par, npar) - y) > tol)
	{
		double x2 = x1;
		x1 -= ((x1 - x0) / (func(x1, par, npar) - func(x0, par, npar))) * func(x1, par, npar);
		x0 = x2;
		//cout<<setprecision(8)<<x0<<" "<<x1<<endl;
	}
	return x1;
}
double Bisezione(double (*func)(double, double*, int), double y, double x0, double x1, double tol, double* par, int npar)
{
	double x;
	while (abs(x1 - x0) > tol)
	{
		x = (x0 + x1) / 2;
		if (func(x, par, npar) - y <= 0)
		{
			x0 = x;
		}
		else
		{
			x1 = x;
		}
		//cout<<setprecision(8)<<x0<<" "<<setprecision(8)<<x1<<endl;
	}
	return x;
}
