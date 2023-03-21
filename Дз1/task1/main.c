#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Input e = ");
    double e;
    scanf("%lf", &e);
    double x, x0, xt;
    printf("x = ");

    while(scanf("%lf",&x)){
        x0 = 1;
        xt = (x0+x/x0)/2;
        while((x0 - xt) >= e || (xt - x0) >= e){
            x0 = xt;
            xt = (x0+x/x0)/2;
        }
        printf("sqrt(%lf) = %lf\n", x, xt);
        printf("sqrt(%.2lf) = %.2lf\n", x, xt);
        printf("sqrt(%f) = %f\n", x, xt);
        printf("sqrt(%.2f) = %.2f\n", x, xt);
        printf("sqrt(%g) = %g\n", x, xt);
        printf("sqrt(%.10g) = %.10g\n", x, xt);
        printf("sqrt(%e) = %e\n", x, xt);

        printf("x = ");;
    }

    return 0;
}
