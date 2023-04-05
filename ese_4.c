/*Studio dell'instabilita' numerica di ln(x) per x->1 usando le funzioni log1pf e log1p.
Confronto float-double in termini di errore relativo per un for-loop x->x/2 partendo da:
1) x=1.f
2) x=0.1f
*/

#include <stdio.h>
#include <math.h>           //libreria con le funzioni necessarie
#include <stdlib.h>

//Function declaration
float accurateLog(float,float,int);
double relative_error(float, double);

int main(){
    int N=50, j=0;                              //numero di iterazioni
    float xf1 = 1.f, xf2 = 0.1f;                //0.1 non esatto in binario
	double xd1 = 1.0, xd2 = 0.1;
    float error_value = 7e-1f;                  //a tentativi

    FILE *fp_dev, *fp_dat;	                    //puntatore a file dove vengono salvati i dati per plot
	fp_dev = fopen("Data_deviazione.dat", "w"); //!!! dati per il plot
    fp_dat = fopen("Data_check.dat", "w");      //file di controllo

	for (int i=1; i<=N; i++){
        j++;                                    //contatore di iterazione, necessario per la funzione accurateLog

        //valutazione della funzione ln(x) nelle varie casistiche
        double dlog1 = log1p(1.0+xd1);
        float flog1 = log1pf(1.f+xf1);
        double dlog2 = log1p(1.0+xd2);
        float flog2 = log1pf(1.f+xf2);
        float func_flog1 = accurateLog(1.f+xf1,-1,j);      //-1 per essere sicuro di non maggiorare l'errore
        float func_flog2 = accurateLog(1.f+xf2,-1,j);
        float flogf1 = logf(1.f+xf1);           //dove mi aspetto l'instabilita' numerica
        float flogf2 = logf(1.f+xf2); 

        fprintf(fp_dat, "%4.15e \t %4.6e \t %4.6e \t %4.15e \t %4.15e \t %4.6e \t %4.6e \t %4.15e \t %4.6e \t %4.6e \n",
                    xd1,flogf1,flog1,dlog1,xd2,flogf2,flog2,dlog2,func_flog1,func_flog2);

        //calcolo degli errori relativi rispetto al riferimento float
        double err_1 = relative_error(flogf1,dlog1);
        double err_2 = relative_error(flogf2,dlog2);
        double err_3 = relative_error(flog1,dlog1);
        double err_4 = relative_error(flog2,dlog2);
        double err_5 = relative_error(func_flog1,dlog1);
        double err_6 = relative_error(func_flog2,dlog2);

        float max_func_flog1 = accurateLog(1.f+xf1,error_value,j);      //-1 e' sostituito dall'error_value per la stima
        float max_func_flog2 = accurateLog(1.f+xf2,error_value,j);
        double err_7 = relative_error(max_func_flog1,dlog1);
        double err_8 = relative_error(max_func_flog2,dlog2);

        fprintf(fp_dev, "%4.15e \t %4.15e \t %4.15e \t %4.15e \t %4.15e \t %4.15e \t %4.15e \t %4.15e \t %4.15e \t %4.15e \n",
                    xd1,err_1,err_3,err_5,xd2,err_2,err_4,err_6,err_7,err_8);       

		xd1 /= 2.0;
        xd2 /= 2.0;
		xf1 = (float)xd1;           //cast esplicito per avere xd: uguali parametri di partenza	
        xf2 = (float)xd2;
	}
    fclose(fp_dev);
    fclose(fp_dat);

	return 0;
}

/*funzione che implementa l'equazione data nella scheda, il parametro y corrisponde alla costante di maggiorazione 
della parentesi*/
float accurateLog(float x, float y, int n){
    float z = logf(1.f + x) / ((1.f + x) - 1.f);

	if (1.f + x == 1.f){
		return x;
	}
	else if( y > z )
	{
		return x*y;                 //maggiorazione dell'errore con una costante
	}
	else{
        if (y != -1){
            printf("Sottostima dell'errore! Iterazione %d, %4.6e\n",n,z);       //print di controllo
        }
		return x*z;
	}
}

//calcolo dell'errore relativo della variabile float rispetto alla double
double relative_error(float sol_float, double sol_double){
    double error;
    error = fabs(sol_float - sol_double) / fabs(sol_double);          //fabs opera in double
    return error;
}