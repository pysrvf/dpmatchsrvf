#include <iostream>
#include "dpmatch.h"
using namespace std;

int main(int argc, char *argv[])
{
    clock_t start, finish;
    float duration;
    //Declaration of variables
    int vl_iNum_Shapes = 0;
    float a = 1.0;
    float b = 1.0;
    shape *s1 = NULL; shape *s2 = NULL;
//	params *v_pparams = NULL;
    float **Energy = nullptr;
    float *gamma_hat = nullptr;
    int i = 0;

    int n = 0;
    int T = 0;
    // Allocate q1 and q2 arrays of size n X T
    float *q1 = nullptr;
    float *q2 = nullptr;


    dpmatch dpmatchobj;
    FILE *vl_fpgamma = NULL;
    int vl_ishift = 0;
    if(argc != 3)
    {
        printf("\nError: Incorrect number of arguments\n");
        printf("Usage: %s <q function pair> <output match> \n \n",argv[0]);
        exit(1);
    }

    if (dpmatchobj.Read_q1_q2(argv[1], &q1, &q2, &n, &T))
    {
        start = clock();
        gamma_hat = dpmatchobj.match(n, T, q1, q2);
        finish = clock();
        duration = (float)(finish - start) / CLOCKS_PER_SEC;
        vl_fpgamma = fopen(argv[2],"wb");
        dpmatchobj.writegamma(vl_fpgamma,gamma_hat,T);
        fclose(vl_fpgamma);
        delete q1;
        delete q2;

    }

    return 0;
}
