
double integrationPtMilieu(double (*f)(double), double a, double b);
double integrationPtMilieuComposite(double (*f)(double), double a, double b, int N);
double integrationTrapezeComposite(double (*f)(double), double a, double b, int N);
double integrationSimpson(double (*f)(double), double a, double b, int N);