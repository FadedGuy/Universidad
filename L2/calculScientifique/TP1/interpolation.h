
double base_lagrange(double x, int i, double *X, int n);
double eval_p_lagrange(double x, double *X, double *Y, int n);
void differences_divises(double *N, double *X, double *Y, int n);
double eval_p_dd(double x, double *N, double *X, int n);
double par_morceaux(double x, double *X, double *Y, int n);