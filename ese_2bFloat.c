#include <stdio.h>
#include <math.h>


int main(){


    float h=1;
//stampa per una serie di denominatori h su ogni riga (h, f'(1+h)/e(1))
//il rapporto tra la derivata calcolata (come FLOAT) ed il suo valore corretto (come DOUBLE)

    for(int i=0;i<100;i++){
      //  printf("\nh=e-%d -- ",i);
        printf("%4.3e %4.3e\n", h ,(expf(1+h)-expf(1))/h / exp(1));
        h/=1.7;
    }

    return 0;
}

