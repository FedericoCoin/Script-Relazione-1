#include <stdio.h>
#include <math.h>


int main(){

//stampa per una serie di denominatori h su ogni riga (h, f'(1+h)-e(1))
 //variabili FLOAT

    float h=1;

    for(int i=0;i<100;i++){

        printf("%4.3e %4.3e\n", h ,(expf(1+h)-expf(1))/h -expf(1));
        h/=1.7;
    }

    return 0;
}

