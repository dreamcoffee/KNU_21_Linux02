#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

#define _USE_MATH_DEFINES
#define N 4

void sinx_taylor(int num_elements, int terms, double* x, double* result) {
    int fd[2];

    pipe(fd);

    for (int i = 0; i < num_elements; i++) {
        pid_t pid = fork();
 
        if (pid == 0) {
            close(fd[0]); 

            double x_i = x[i];
            double value = x_i;                  
            double numer = x_i * x_i * x_i;      
            double denom = 6.0;                  
            int sign = -1;                       
            double result_i;

            for(int j=1; j<=terms; j++) {
                value += (double)sign * numer / denom;
                numer *= x_i * x_i;
                denom *= (2.0*(double)j+2.0) * (2.0*(double)j+3.0);
                sign *= -1;
            }
            result_i = value;

            write(fd[1], &i, sizeof(i));         
            write(fd[1], &result_i, sizeof(result_i)); 

            close(fd[1]);
            exit(0);      
        }
    }
    close(fd[1]); 

    for (int i = 0; i < num_elements; i++) {
	    wait(NULL);
    }
    
    for (int i = 0; i < num_elements; i++) {
	    int index;
	    double result_val;
		
	    read(fd[0], &index, sizeof(int));
	    read(fd[0], &result_val, sizeof(double));

	    result[index] = result_val; 
	}

    close(fd[0]);
}

int main() {
    double x[N] = {0.0, M_PI/6.0, M_PI/3.0, 0.134};
    double res[N];
    
    sinx_taylor(N, 3, x, res); 
    
    for(int i=0; i<N; i++) {
        printf("sin(%.2f) by Taylor series = %f\n", x[i], res[i]);
        printf("sin(%.2f) = %f\n", x[i], sin(x[i]));
    }
    
    return 0;
}
