// Stabilita' soluzioni dell'equazione quadratica a*x^2+b*x+c = 0 nel limite b^2 >> 4a*c.
// Si evidenzia il problema al variare del segno di b per x_1, x_2 (vedi scheda) con variabili float.
// + confronto con variabile double per stima dell'errore relativo

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Function declaration
float solution_F(float, float, float, int);
double solution_D(double, double, double, int);
float stableSolution_F(float, float, float, int);
double relative_error(float, double);

int main(){
    int N=400;                         //numero di iterazioni
    double rate = 0.125/2;             //rate di incremento del parametro b

    //parametri del problema a) con b>0 (soluzioni x_1, x_2 negative) e b<0 (soluzioni positive)
    float af = 1.f, bf = 3.f, cf = 1.f;     
    double ad = 1, bd = 3, cd = 1;

    double rapp, err_1, err_2, err_3, err_4;        //coefficienti che valutano b^2/4ac e differenza float-double
    double err_5, err_6, err_7, err_8; 
    float xf_1, xf_2, xfs_1, xfs_2;                 //coerenti con le formule nella scheda dell'esercizio (vedi segni)
    double xd_1, xd_2;
    float mxf_1, mxf_2, mxfs_1, mxfs_2;             //soluzioni analoghe ma con b negativo
	double mxd_1, mxd_2;

	FILE *fp_fl, *fp_db, *fp_dev, *fp_stableFloat;	//puntatori a file dove vengono salvati i dati per plot
	fp_fl = fopen("Data_float.dat", "w");           //dati di controllo
    fp_db = fopen("Data_double.dat", "w");
    fp_stableFloat = fopen("Data_stablefloat.dat","w");
    fp_dev = fopen("Data_deviazione.dat", "w");	    // !!! dove vado a vedere la stabilita' in float
    
    for (int i=1; i<=N; i++){
        rapp = pow(bd,2) / (4*ad*cd);               //variabile x del plot

        //calcolo delle soluzioni noti i parametri del problema
		xf_1= solution_F(af, bf, cf, 1);
        xf_2= solution_F(af, bf, cf, 2);
        mxf_1= solution_F(af, -bf, cf, 1);
        mxf_2= solution_F(af, -bf, cf, 2);
        fprintf(fp_fl, "%4.6e \t %4.6e \t %4.6e \t %4.6e \t %4.6e\n",bf,xf_1,xf_2,mxf_1,mxf_2);
        //print di controllo, xf_1=mxf_2 e xf_2=mxf_1

		xd_1 = solution_D(ad, bd, cd, 1);
        xd_2 = solution_D(ad, bd, cd, 2);
        mxd_1 = solution_D(ad, -bd, cd, 1);
        mxd_2 = solution_D(ad, -bd, cd, 2);
        fprintf(fp_db, "%4.15e \t %4.15e \t %4.15e \t %4.15e \t %4.15e\n",bd,xd_1,xd_2,mxd_1,mxd_2);
        //print di controllo, xd_1=mxd_2 e xd_2=mxd_1

		xfs_1 = stableSolution_F(af, bf, cf, 1);
        xfs_2 = stableSolution_F(af, bf, cf, 2);
        mxfs_1 = stableSolution_F(af, -bf, cf, 1);
        mxfs_2 = stableSolution_F(af, -bf, cf, 2);
        fprintf(fp_stableFloat, "%4.6e \t %4.6e \t %4.6e \t %4.6e \t %4.6e\n",bf,xfs_1,xfs_2,mxfs_1,mxfs_2); 
        //print di controllo

        err_1 = relative_error(xf_1,xd_1);
        err_2 = relative_error(xf_2,xd_2); 
        err_3 = relative_error(mxf_1,mxd_1);
        err_4 = relative_error(mxf_2,mxd_2); 
        err_5 = relative_error(xfs_1,xd_1);
        err_6 = relative_error(xfs_2,xd_2);
        err_7 = relative_error(mxfs_1,mxd_1);
        err_8 = relative_error(mxfs_2,mxd_2); 

        fprintf(fp_dev, "%4.15e \t %4.15e \t %4.15e \t %4.15e \t %4.15e \t %4.15e \t %4.15e \t %4.15e \t %4.15e \n",
                    rapp, err_1, err_2, err_3, err_4, err_5, err_6, err_7, err_8);

        bd *= pow(2,rate);                              //incremento di b e di conseguenza di rapp
        bf = (float)bd;                                 //cast esplicito per avere bf: uguali parametri di partenza	
    }
    fclose(fp_fl);
    fclose(fp_db);
    fclose(fp_dev);
    fclose(fp_stableFloat);
		
	return 0;
}

//Soluzioni eq. quadratica con variabili float: x1 e x2.
float solution_F(float a, float b, float c, int sol_type){
	if (sol_type == 1){
		return (-b + sqrtf(powf(b,2) - 4*a*c)) / (2*a);
	}
	else if (sol_type == 2){
        return (-b - sqrtf(powf(b,2) - 4*a*c)) / (2*a);
    }
    else{
		printf("Errore! Soluzione float non selezionata correttamente.");
        return 0;
	}
}

//Soluzioni eq. quadratica con variabili double: x1 e x2.
double solution_D(double a, double b, double c, int sol_type){
	if (sol_type == 1){
		return (-b + sqrt(pow(b,2) - 4*a*c)) / (2*a);
	}
	else if (sol_type == 2){
        return (-b - sqrt(pow(b,2) - 4*a*c)) / (2*a);
    }
    else{
		printf("Errore! Soluzione double non selezionata correttamente.");
        return 0;
	}
}

//Soluzioni stabile eq. quadratica con variabili float: x1 e x2.
float stableSolution_F(float a, float b, float c, int sol_type){
	if (sol_type == 1){
		return (2*c) / (-b - sqrtf(powf(b,2) - 4*a*c));
	}
	else if (sol_type == 2){
		return (2*c) / (-b + sqrtf(powf(b, 2) - 4*a*c));
	}
    else{
		printf("Errore! Soluzione double non selezionata correttamente.");
        return 0;
	}
}

//Calcolo dell'errore relativo della variabile float rispetto alla double.
double relative_error(float sol_float, double sol_double){
    double error;
    error = fabs(sol_float - sol_double) / fabs(sol_double);    //fabs opera in double
    return error;
}

