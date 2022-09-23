#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "poly.h"

/*
Miniprojeto 2: calculadora polinomial

Os resultados sao impressos com duas casas 
decimais, conforme sugerido em sala
*/
int main(void){
    Poly *p1 = NULL;
    int n, m, i, j, aux, X, aux2, p;
    char a[31], b[31], signal;
    double *answer = NULL;

    scanf("%d%*c", &n); //número de polinomios a serem inseridos
    p1 = (Poly *) calloc(n, sizeof(Poly));
    for ( i = 0; i < n; i++){
        p1[i] = create_poly(i);
    }    

    scanf("%d%*c", &m); //número de operações entre polinomios
    aux2 = m;
    while (aux2--){
        scanf("%[^+-]%c%[^\n]%*c", a, &signal, b);

        for ( i = 0; i < n; i++){
            aux = strcmp(a, p1[i].id);
            if(aux == 0) break;
        }

        for ( j = 0; j < n; j++){
            aux = strcmp(b, p1[j].id);
            if(aux == 0) break;
        }

        answer = (double*) calloc(101, sizeof(double));

        switch (signal){ //identificar a operação a ser realizada
        case '+':
            X = add_poly(p1, answer, i, j);
            break;

        case '-':
            X = minus_poly(p1, answer, i, j);
            break;
        
        }

        print_answer(X, answer);
        printf("\n");
        

        free(answer);
        
    }
    
    for(i = 0; i < m; i++){
        free(p1[i].id);
    }

    for(i = 0; i < m; i++){
        free(p1[i].coef);
    }

    free(p1);

    return 0;
}