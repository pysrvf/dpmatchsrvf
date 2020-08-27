//#include "params.h"
#include <cstdio>
#include <vector>

const float PI =  (float)3.14159265358979;

class shape;
class DPmatch {

public:

    DPmatch();

    DPmatch(int dim, int siz);

    ~DPmatch();

    bool Read_v1_v2(char *, shape **, shape **, float *, float *);

    bool Read_q1_q2_old(char *, shape **, shape **);

    bool Read_q1_q2_deprecate(char *, float ***, float ***, int *, int *);

    bool Read_q1_q2(char *, float **, float **, int *, int *);

    bool Read_X1_X2(char *, shape **, shape **);

    float match_deprecate(int n, int T, float **q1, float **q2, float *gamma);

    float* match(int n, int T, float *q1, float *q2);

    float DPcost_deprecate(float **q1, float **q2, int n, int T, int k, int l, int i, int j);

    float DPcost(float *q1, float *q2, int n, int T, int k, int l, int i, int j);

    float MatchQ(shape *, shape *, float *, float **);

    float Match_Coords_depracate(shape *, shape *, float *, float **);

    void copy(int T, float *src, float *dest);

    float Match_CostQ(shape *, shape *, int, int, int, int);

    float Match_Cost_Coords_depracate(shape *, shape *, int, int, int, int);

    float norm(float *v_pfArray, int v_ilen);

    bool writegamma(FILE *, float *, int T);

    bool WriteGamma_deprecate(FILE *, float *, int, shape *);

    bool WriteGammaV(FILE *, float *, int, shape *);

    void linint(float *xnew, float *ynew, int cnt, float *xx, float *yy, int n);

    void splint(float *xa, float *ya, float *y2a, int n, float x, float *y);

    void spline(float *x, float *y, int n, float yp1, float ypn, float *y2);

    float L2_Costfn(float *, float *, float *, float *, int , float ,float);

    float ** create_array(int n, int T);

    float * create_array_new2(int n, int T);

    void delete_array(float **arr, int n);

    void print_array(float *arr, int n, int T);

    void print_vector(float *arr, int T);

    void print_int(int T);

};


class shape
{
public:
    //Member variables
    float *m_pfPhi;
    float *m_pfTheta;
    float *m_v11;
    float *m_v12;
    float *m_v13;

    float **v;
    float *h;
    int m_iT;
    int m_n;
    //Member functions
    shape();//default constructor
    shape(int, int);
    shape(int);
    shape(int, float *,float *);
    shape(shape &);
    ~shape();
    shape& operator = (const shape &s);
    void create(int);
    void create(int, float *, float *);
    void Initialize(int ,float *, float *);
    float L2_Costfn(shape &);
    void copy(int T, float *, float *);
//		float arr[29696][239];
    float **arr;


    void Create_From_Coordinates(float *, float *,  int);
};
