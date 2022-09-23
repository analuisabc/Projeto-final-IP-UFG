#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poly.h"

int findGrau(char *str){
    int i = 0, j = 0, count;
    char *num = NULL;
    double grau, grau_mais;
    int tam = strlen(str), retorno;

    num = (char*) calloc(99, sizeof(char));

    grau_mais = -1; // sempre vai ser menor que os graus inseridos
    for ( i = 0; str[i] != '\0'; i++){
        count = (i+1);
        if(str[i] != '^') continue;
        else if (str[i] == '^'){

            for(;;){
                if (str[count] == '+' || str[count] == '-') break;
                if (str[count] == '\0') break;

                num[j] = str[count];
                j++;
                count++;
            }
            j = 0;
            
            grau = atoi(num); 

            if(grau_mais < grau){
                grau_mais = grau;
                continue;
            }
            
        }  
    }
    free(num);
    retorno = grau_mais;
    return (retorno);

}
void coef_full(double coef[], char *str){
    int i = 0, count = 0, m = 0, u;
    char armazem[101];
    double coefi;
    int exp, tam;

    tam = strlen(str);
    for(i = 0; i < tam; i++) {
        if (str[i] == 'x') {
            count = (i-1); m = 0;
            while(1) {
                if (count < 0) { //para nao acabar em indice negativo acidentalmente
                    count++; 
                    break;
                }

                if (str[count] == '+') break;
                else if (str[count] == '-') break;
                else count--;
            }
            while(1) {
                if(str[count] == 'x') break;
                else {
                armazem[m] = str[count];
                count++; m++;
                }
            }
            armazem[m] = '\0';
            coefi = atof(armazem);

            if (coefi == 0) continue;
            else {
                u = (i+2); m = 0;
                while(1) {
                    if (str[u] == '\0') break;
                    else if(str[u] == '+' || str[u] == '-') break;
                    else {
                    armazem[m] = str[u];

                    m++;
                    u++;
                    }
                }
                armazem[m] = '\0';
                exp = atoi(armazem); // basicamente atof mas para inteiros
                /*
                Encaminhar os coeficientes de modo a seguir os respectivos indices:
                */
                coef[exp] = coefi;
            }
        }
    } 
}
int add_poly(Poly* p1, double answer[], int i, int k){
    int X, t;

    if(p1[i].p <= p1[k].p){
        X = p1[k].p;
        for(t = 0; t <= p1[i].p; t++){
            answer[t] = p1[i].coef[t] + p1[k].coef[t];
        }
        t = (p1[i].p + 1);
        while (1){
            if(p1[i].p == p1[k].p) break;
            if(t > X)break;
            answer[t] = p1[k].coef[t];

            t++;
        }
        goto END;
    }

    if (p1[i].p > p1[k].p){
        X = p1[i].p;
        for (t = 0; t <= p1[k].p; t++){
            answer[t] = (p1[i].coef[t] + p1[k].coef[t]); 
        }
        t = (p1[k].p + 1);
        while (t <= X){
            answer[t] = p1[i].coef[t];
            t++;
        }
    }
    END:
    return X;
}
int minus_poly(Poly* p1, double answer[], int i, int k){
    int X, t;

    if (p1[i].p <= p1[k].p){
        X = p1[k].p;
        for(t = 0; t <= p1[i].p; t++){
            answer[t] = p1[i].coef[t] - p1[k].coef[t];
        }
        t = (p1[i].p + 1);
        while (1){
            if (t > X) break;
            else{
                answer[t] = -p1[k].coef[t];
                if(answer[t] == -0){
                    answer[t] = (answer[t])*(-1);
                }
            }
            t++;
        }
        goto END;
    }

    if(p1[i].p > p1[k].p){
        X = p1[i].p;
        for(t = 0; t <= p1[k].p; t++){
            answer[t] = p1[i].coef[t] - p1[k].coef[t];
        }
        t = (p1[k].p + 1);
        while (1){
            if(t > X) break;
            answer[t] = p1[i].coef[t];
            t++;
        }
    }   
    END:
    return X;
}
void print_answer(int X, double answer[]){
    int j, k;

    /*Acrescentando o caso para quando o resultado for 0
    Devo imprimir 0x^0:*/
    j = 0;
    while (j <= X){
        k = answer[j];
        if (k != 0) goto END;
        j++;
    }
    printf("0.00x^0");
    return;

    END:
    j = 0;
    while (j <= X){
        if (j == 0){
            if (answer[j] > 0){
                printf("%.2lfx^%d", answer[j], j);
            } 
        } else if (j > 0){
            if (answer[j] > 0){
                printf("+%.2lfx^%d", answer[j], j);
            } 
        }
        if (0 > answer[j]){
            printf("%.2lfx^%d", answer[j], j);
        }  
        j++;
    }
}
Poly create_poly(int i){
    Poly aux;
    char nome[101], conteudo[1001];
    int tam, l;

    scanf("%[^:]%*c%*c %[^\n]%*c", nome, conteudo); // me livrando do caracter do espaço

    tam = strlen(nome);
    aux.id = (char *) calloc(tam+1, sizeof(char));
    strcpy(aux.id, nome);

    aux.p = findGrau(conteudo);
    l = aux.p + 1;
    aux.coef = (double *) calloc(l, sizeof(double));
    coef_full(aux.coef, conteudo);

    return aux;
    free(aux.id);
    free(aux.coef);
}





