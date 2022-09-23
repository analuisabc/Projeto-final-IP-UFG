typedef struct polynomio {
	char *id;       // string com o nome do polinômio
	int p;          // grau do polinômio
	double *coef;   // vetor de coeficientes do polinômio
} Poly;

void print_answer(int X, double answer[]);
void coef_full(double coef[], char *str);
int add_poly(Poly* p1, double answer[], int i, int k);
int minus_poly(Poly* p1, double answer[], int i, int k);
int findGrau(char *str);
Poly create_poly(int i);