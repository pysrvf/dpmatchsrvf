#include <stdlib.h>
#include <time.h>
#include <math.h>
//#include <cblas.h>
#include <iostream>
#include <vector>
#include "dpmatch.h"
using namespace std;

/*
float InnerProduct(float *h1, float *f1, float *h2, float *f2, params *v_pparams, float *v_pfPhi)
{
	int i = 0;
	int T = v_pparams->m_T;
	
	float del = (float) 1 / ( T );
	float val = 0;
	for(i = 0; i < T; i ++) 
	{
		val = val + 	v_pparams->a * h1[i] * h2[i] * exp(v_pfPhi[i]) * del + \
				v_pparams->b * f1[i] * f2[i] * exp(v_pfPhi[i]) * del;
	}
	return val;
}
*/

/*
bool Read_Theta_fn(char *v_szFileName,shape **v_pshape1,shape **v_pshape2,float *v_fa, float *v_fb)
{
	// Open the Dir_Fn file to read the array of Direction functions

	FILE *vl_fpDir_Fn = NULL;
	vl_fpDir_Fn = fopen(v_szFileName,"rb");
	int vl_iNum_Shapes = 0;
	if( vl_fpDir_Fn == NULL)
	{
		printf("\nError: %s File not Found\n",v_szFileName);
		return false;
	}
	int vl_iT = 0;
	size_t vl_readsize = 0;

	vl_readsize = fread(&vl_iNum_Shapes,sizeof(vl_iNum_Shapes),1,vl_fpDir_Fn);
	vl_readsize = fread(&vl_iT,sizeof(vl_iT),1,vl_fpDir_Fn);
	vl_readsize = fread(v_fa,sizeof(float),1,vl_fpDir_Fn);
	vl_readsize = fread(v_fb,sizeof(float),1,vl_fpDir_Fn);
		
	*v_pshape1 = new shape(vl_iT);	
	*v_pshape2 = new shape(vl_iT);
	
	float *vect = new float[vl_iT];		
	
	vl_readsize = fread(vect,sizeof(float),vl_iT,vl_fpDir_Fn);
	copy(vl_iT,vect,(*v_pshape1)->m_pfTheta);
	vl_readsize = fread(vect,sizeof(float),vl_iT,vl_fpDir_Fn);
	copy(vl_iT,vect,(*v_pshape2)->m_pfTheta);	
	fclose(vl_fpDir_Fn);
	
	delete [] vect;
	return true;
}
*/

/*
bool Read_f1_f2(char *v_szFileName,func *v_pshape1, func *v_pshape2)
{
	FILE *vl_fpDir_Fn = NULL;
	vl_fpDir_Fn = fopen(v_szFileName,"rb");	
	if( vl_fpDir_Fn == NULL)
	{
		printf("\nError: %s File not Found\n",v_szFileName);
		return false;
	}
	size_t vl_readsize = 0;
    int n = 0;
    vl_readsize = fread(&vl_iNum_Shapes,sizeof(vl_iNum_Shapes),1,vl_fpDir_Fn);
    vl_readsize = fread(&n,sizeof(n),1,vl_fpDir_Fn);	
	vl_readsize = fread(&vl_iT,sizeof(vl_iT),1,vl_fpDir_Fn);
	
	v_pshape1 = new func(vl_iT);	
	v_pshape2 = new func(vl_iT);

	float *vect = new float[vl_iT];		
	
	vl_readsize = fread(vect,sizeof(float),vl_iT,vl_fpDir_Fn);
	copy(vl_iT,vect,(*v_pshape1)->m_v11);
	
	
}
*/


dpmatch::dpmatch()
{
//    v_pshape1 = nullptr;
//    v_pshape1 = nullptr;

}

dpmatch::dpmatch(int dim, int siz)
{
//    v_pshape1 = new shape(dim,siz);
//    v_pshape2 = new shape(dim,siz);
}


dpmatch::~dpmatch()
{
//    delete v_pshape1;
//    delete v_pshape2;
}

float * dpmatch::create_array_new2(int n, int T)
{
    float *arr = new float [n * T];
    return arr;
}


float ** dpmatch::create_array(int n, int T)
{
    float **arr = new float *[n];
    for (int i = 0; i < n; i ++)
        arr[i] = new float [T];
    return arr;
}

void dpmatch::delete_array(float **arr, int n)
{
    for (int i = 0; i < n; i ++)
        delete arr[i];
    delete arr;
    arr = nullptr;
}

void dpmatch::print_array(float *arr, int n, int T)
{
    std::cout << "n = " << n << " T = " << T << "\n";
    cout.flush();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < T; j++)
            std::cout << arr[i*T + j] << " ";
        std::cout << "\n";
    }
}

void dpmatch::print_vector(float *arr, int T)
{
    for (int j = 0; j < T; j++)
        cout << arr[j] << " ";
    cout << "\n";
}

bool dpmatch::Read_q1_q2_deprecate(char *v_szFileName, float ***q1, float ***q2, int *n, int *T)
{
    FILE *vl_fpDir_Fn = NULL;
    vl_fpDir_Fn = fopen(v_szFileName,"rb");
    int vl_iNum_Shapes = 0;
    if( vl_fpDir_Fn == NULL)
    {
        printf("\nError: %s File not Found\n",v_szFileName);
        return false;
    }
    int vl_iT = 0;
    size_t vl_readsize = 0;
    int vl_n = 0;

    vl_readsize = fread(&vl_iNum_Shapes,sizeof(vl_iNum_Shapes),1,vl_fpDir_Fn);
    vl_readsize = fread(&vl_n,sizeof(vl_n),1,vl_fpDir_Fn);

    vl_readsize = fread(&vl_iT,sizeof(vl_iT),1,vl_fpDir_Fn);

    *q1 = create_array(vl_n, vl_iT);
    *q2 = create_array(vl_n, vl_iT);

    float *vect = new float[vl_iT];

    for (int i =0; i < vl_n; i++)
        vl_readsize = fread((*q1)[i],sizeof(float),vl_iT,vl_fpDir_Fn);

    for (int i =0; i < vl_n; i++)
        vl_readsize = fread((*q2)[i],sizeof(float),vl_iT,vl_fpDir_Fn);

    *n = vl_n;
    *T = vl_iT;
    fclose(vl_fpDir_Fn);

    delete [] vect;
    return true;
}


bool dpmatch::Read_q1_q2(char *v_szFileName, float **q1, float **q2, int *n, int *T)
{
    FILE *vl_fpDir_Fn = NULL;
    vl_fpDir_Fn = fopen(v_szFileName,"rb");
    int vl_iNum_Shapes = 0;
    if( vl_fpDir_Fn == NULL)
    {
        printf("\nError: %s File not Found\n",v_szFileName);
        return false;
    }
    int vl_iT = 0;
    size_t vl_readsize = 0;
    int vl_n = 0;

    vl_readsize = fread(&vl_iNum_Shapes,sizeof(vl_iNum_Shapes),1,vl_fpDir_Fn);
    vl_readsize = fread(&vl_n,sizeof(vl_n),1,vl_fpDir_Fn);

    vl_readsize = fread(&vl_iT,sizeof(vl_iT),1,vl_fpDir_Fn);

    *q1 = create_array_new2(vl_n, vl_iT);
    *q2 = create_array_new2(vl_n, vl_iT);

    vl_readsize = fread((*q1),sizeof(float),vl_n * vl_iT,vl_fpDir_Fn);
    vl_readsize = fread((*q2),sizeof(float),vl_n * vl_iT,vl_fpDir_Fn);

    *n = vl_n;
    *T = vl_iT;
    fclose(vl_fpDir_Fn);

    return true;

}


bool dpmatch::Read_q1_q2_old(char *v_szFileName, shape **s1, shape **s2)
{
	FILE *vl_fpDir_Fn = NULL;
	vl_fpDir_Fn = fopen(v_szFileName,"rb");
	int vl_iNum_Shapes = 0;
	if( vl_fpDir_Fn == NULL)
	{
		printf("\nError: %s File not Found\n",v_szFileName);
		return false;
	}
	int vl_iT = 0;
	size_t vl_readsize = 0;
        int n = 0;
    
    vl_readsize = fread(&vl_iNum_Shapes,sizeof(vl_iNum_Shapes),1,vl_fpDir_Fn);
    vl_readsize = fread(&n,sizeof(n),1,vl_fpDir_Fn);

	vl_readsize = fread(&vl_iT,sizeof(vl_iT),1,vl_fpDir_Fn);
	
	*s1 = new shape(n,vl_iT);
	*s2 = new shape(n,vl_iT);
	float *vect = new float[vl_iT];		
	
	for (int i =0; i < n; i++)
	{
		vl_readsize = fread(vect,sizeof(float),vl_iT,vl_fpDir_Fn);
		copy(vl_iT,vect, (*s1)->arr[i]);
	}

	for (int i =0; i < n; i++)
	{
		vl_readsize = fread(vect,sizeof(float),vl_iT,vl_fpDir_Fn);
		copy(vl_iT,vect, (*s2)->arr[i]);
	}
	fclose(vl_fpDir_Fn);
	
	delete [] vect;
	return true;
}


bool dpmatch::Read_X1_X2(char *v_szFileName, shape **s1, shape **s2)
{
	FILE *vl_fpDir_Fn = NULL;
	vl_fpDir_Fn = fopen(v_szFileName,"rb");
	int vl_iNum_Shapes = 0;
	if( vl_fpDir_Fn == NULL)
	{
		printf("\nError: %s File not Found\n",v_szFileName);
		return false;
	}
	int vl_iT = 0;
	size_t vl_readsize = 0;
        int n = 0;
    
    vl_readsize = fread(&vl_iNum_Shapes,sizeof(vl_iNum_Shapes),1,vl_fpDir_Fn);
    vl_readsize = fread(&n,sizeof(n),1,vl_fpDir_Fn);

	vl_readsize = fread(&vl_iT,sizeof(vl_iT),1,vl_fpDir_Fn);
	
	*s1 = new shape(n,vl_iT);
	*s2 = new shape(n,vl_iT);
	float *vect = new float[vl_iT];		
	
	for (int i =0; i < n; i++)
	{
		vl_readsize = fread(vect,sizeof(float),vl_iT,vl_fpDir_Fn);
		copy(vl_iT,vect, (*s1)->arr[i]);
	}

	for (int i =0; i < n; i++)
	{
		vl_readsize = fread(vect,sizeof(float),vl_iT,vl_fpDir_Fn);
		copy(vl_iT,vect, (*s2)->arr[i]);
	}
	fclose(vl_fpDir_Fn);
	
	delete [] vect;
	return true;
}



bool dpmatch::Read_v1_v2(char *v_szFileName, shape **v_pshape1, shape **v_pshape2, float *v_fa, float *v_fb)
{
	// Open the Dir_Fn file to read the array of Direction functions

	FILE *vl_fpDir_Fn = NULL;
	vl_fpDir_Fn = fopen(v_szFileName,"rb");
	int vl_iNum_Shapes = 0;
	if( vl_fpDir_Fn == NULL)
	{
		printf("\nError: %s File not Found\n",v_szFileName);
		return false;
	}
	int vl_iT = 0;
	size_t vl_readsize = 0;
        int n = 0;
        vl_readsize = fread(&vl_iNum_Shapes,sizeof(vl_iNum_Shapes),1,vl_fpDir_Fn);
        vl_readsize = fread(&n,sizeof(n),1,vl_fpDir_Fn);

	vl_readsize = fread(&vl_iT,sizeof(vl_iT),1,vl_fpDir_Fn);

//	cout << n << endl;	
	*v_pshape1 = new shape(n,vl_iT);	
	*v_pshape2 = new shape(n,vl_iT);

	float *vect = new float[vl_iT];		
	

	
	
	
	
	vl_readsize = fread(vect,sizeof(float),vl_iT,vl_fpDir_Fn);
	copy(vl_iT,vect,(*v_pshape1)->m_v11);
	vl_readsize = fread(vect,sizeof(float),vl_iT,vl_fpDir_Fn);
	copy(vl_iT,vect,(*v_pshape1)->m_v12);

        if(n == 3)
        {
            vl_readsize = fread(vect,sizeof(float),vl_iT,vl_fpDir_Fn);
            copy(vl_iT,vect,(*v_pshape1)->m_v13);
        
        }

                
	vl_readsize = fread(vect,sizeof(float),vl_iT,vl_fpDir_Fn);
	copy(vl_iT,vect,(*v_pshape2)->m_v11);
	vl_readsize = fread(vect,sizeof(float),vl_iT,vl_fpDir_Fn);
	copy(vl_iT,vect,(*v_pshape2)->m_v12);

        if(n == 3)
        {
            vl_readsize = fread(vect,sizeof(float),vl_iT,vl_fpDir_Fn);
            copy(vl_iT,vect,(*v_pshape2)->m_v13);
           
        }

	fclose(vl_fpDir_Fn);
	
	delete [] vect;

	return true;
}



float dpmatch::Match_Coords_depracate(shape *v_pshape1, shape *v_pshape2, float *gamma, float **Energy)
{
//    int Nbrs[][2] = {{0 ,0},{0, 1},{ 1, 0},{ 1, 2},{ 2, 1},{ 0, 2},{ 2, 0},{ 0, 3},{ 2, 3},{ 3 ,2},{ 3 ,2},{ 0, 4},{ 1, 4}, \
    { 2, 4},{ 3, 4},{ 4, 3},{ 4, 2},{ 4, 1},{ 4, 0} };
//    int Nbrs[][2] = {{1 ,1},{1, 2},{ 2, 1},{ 2, 3},{ 3, 2},{ 1, 3},{ 3, 1},{1, 4},{ 3, 4},{4 ,3},{ 4,1},{ 1, 5},{ 2, 5}, \
    { 3, 5},{ 4, 5},{5, 4},{ 5, 3},{5, 2},{ 5, 1},{1,6},{5,6},{6,5},{6,1},{1,7},{2,7},{3,7},{4,7},{5,7},{6,7}, \
		{4,10}, {4,30}, {4,40}, {4,50}, {5,50},{6,50},{8,50},{10,50},{15,50},{20,50},{25,50},{30,50},{35,50},{40,50}    };

// drastic
//     int Nbrs[][2] = \
//     {{1, 1},{1, 2},{2, 1},{2, 3},{3, 2},{1, 3},{3, 1},{1, 4},{3, 4},{4, 3},{4, 1},{1, 5},{2, 5},{3, 5},{4, 5}, \
//      {5, 4},{5, 3},{5, 2},{5, 1},{1, 6},{5, 6},{6, 5},{6, 1},{1, 7},{2, 7},{3, 7},{4, 7},{5, 7},{6, 7},{1, 6},\
//      {1, 7},{1, 8},{1, 9},{1, 10},{7, 1},{8, 1},{9, 1},{10, 1},{1, 20}, {2, 20},{3, 30},\
//
//     };
//     const int NBR_SIZ = 41;
//


// 	int Nbrs[][2] = {{1, 1}, {1, 2}, {2, 1}, {2, 3}, {3, 2},{ 1, 3},{ 3, 1}, {1, 4}, {3, 4}, {4, 3}, {4, 1}, {1, 5}, {5, 1}, {2, 5}, {3, 5}, {4, 5} };
// 	const int NBR_SIZ = 16;


// 	const int Nbrs[][2] = {
// 	{  1,  1 }, {  1,  2 }, {  1,  3 }, {  1,  4 }, {  1,  5 }, {  1,  6 }, {  1,  7 }, {  1,  8 }, {  1,  9 }, {  1, 10 },
// 	{  2,  1 }, {  2,  3 }, {  2,  5 }, {  2,  7 }, {  2,  9 }, {  3,  1 }, {  3,  2 }, {  3,  4 }, {  3,  5 }, {  3,  7 },
// 	{  3,  8 }, {  3, 10 }, {  4,  1 }, {  4,  3 }, {  4,  5 }, {  4,  7 }, {  4,  9 }, {  5,  1 }, {  5,  2 }, {  5,  3 },
// 	{  5,  4 }, {  5,  6 }, {  5,  7 }, {  5,  8 }, {  5,  9 }, {  6,  1 }, {  6,  5 }, {  6,  7 }, {  7,  1 }, {  7,  2 },
// 	{  7,  3 }, {  7,  4 }, {  7,  5 }, {  7,  6 }, {  7,  8 }, {  7,  9 }, {  7, 10 }, {  8,  1 }, {  8,  3 }, {  8,  5 },
// 	{  8,  7 }, {  8,  9 }, {  9,  1 }, {  9,  2 }, {  9,  4 }, {  9,  5 }, {  9,  7 }, {  9,  8 }, {  9, 10 }, { 10,  1 },
// 	{ 10,  3 }, { 10,  7 }, { 10,  9 }
// };
// 	const int NBR_SIZ = 63;

// 	const int Nbrs[][2] = {
// 	{  1,  1 }, {  1,  2 }, {  1,  3 }, {  1,  4 }, {  1,  5 }, {  1,  6 },
// 	{  2,  1 }, {  2,  3 }, {  2,  5 }, {  2,  7 },
// 	{  3,  1 }, {  3,  2 }, {  3,  4 }, {  3,  5 }, {  3,  7 },
//     {  4,  1 }, {  4,  3 }, {  4,  5 }, {  4,  7 },
//     {  5,  1 }, {  5,  2 }, {  5,  3 },	{  5,  4 }, {  5,  6 }, {  5,  7 },
//     {  6,  1 }, {  6,  5 }, {  6,  7 }
//     };
//
// 	const int NBR_SIZ = 28;
//


// 	int Nbrs[][2] = {{1, 1}, {1, 2}, {2, 1}, {2, 3}, {3, 2},{ 1, 3},{ 3, 1}, {1, 4}, {3, 4}, {4, 3}, {4, 1}};
// 	const int NBR_SIZ = 11;
//
    int Nbrs[][2] = {{1, 1}, {1, 2}, {2, 1}, {2, 3}, {3, 2},{ 1, 3},{ 3, 1}};
    const int NBR_SIZ = 7;


    int NumPlot = 15;
    float shfx = 0.2;
    float shfy = 0.2;
    int N = 0;
    N = v_pshape1->m_iT;
    int i = 0;
    int j = 0;
    int Num = 0;
    float CandE[NBR_SIZ];
    int k = 0,l = 0;
    float minCandE = 10000;
    int minCandE_idx = 0;
    float **Path_x = NULL;
    float **Path_y = NULL;
    float cost = 0;
    Path_x = (float **)malloc(N*sizeof(float *));  // This is Path(i,j,1) in Match.m
    Path_y = (float **)malloc(N*sizeof(float *));  // This is Path(i,j,2) in Match.m

    float *x = NULL;
    float *y = NULL;
    float *xnew = NULL;
    float *ynew = NULL;
    x = (float *)malloc(N*sizeof(float));
    y = (float *)malloc(N*sizeof(float));
    float *xx1 = (float *) malloc(N*sizeof(float) );

    xnew = (float *)malloc(N*sizeof(float));
    ynew = (float *)malloc(N*sizeof(float));

    int cnt = 0;
    Energy = (float **)malloc(N*sizeof(float *));

    for(i = 0;i < N;i ++)
    {
        Energy[i] = (float *)calloc(N,sizeof(float));
        Path_x[i] = (float *)calloc(N,sizeof(float));
        Path_y[i] = (float *)calloc(N,sizeof(float));
        //Forming energies associated with different paths
        Energy[0][i] = 5000000;
        Energy[i][0] = 5000000;
    }

/*		for(i = 1; i < N ; i ++)
    {
            Energy[0][i] = 5;
            Energy[i][0] = 5;
    }*/
    Energy[0][0] = 0;
    xx1[0] = 0;
    printf("\n");
    for(i = 1 ; i < N; i ++)
    {
        printf("%d ",i);
        fflush(stdout);
        for(j = 1; j < N ; j ++)
        {
            minCandE = 10000;
            for(Num = 0; Num < NBR_SIZ; Num ++)
            {
                k = i - Nbrs[Num][0];
                l = j - Nbrs[Num][1];
                if(k >= 0 && l >= 0)
                {
                    CandE[Num] = Energy[k][l] + Match_Cost_Coords_depracate(v_pshape1, v_pshape2,k,l,i,j);
                }
                else
                {
                    CandE[Num] = 10000;
                }
                if(CandE[Num] < minCandE )
                {
                    minCandE = CandE[Num];
                    minCandE_idx = Num;
                }
                Energy[i][j] = minCandE;

                Path_x[i][j] = i - Nbrs[minCandE_idx][0];
                Path_y[i][j] = j - Nbrs[minCandE_idx][1];
            }
        }
        xx1[i] = (float ) i/(N - 1);
    }

    x[0] = N-1; y[0] = N-1;
    while ( x[cnt] > 0 )
    {
        i = (int) y[cnt];
        j = (int) x[cnt];
        y[cnt + 1] = Path_x[i] [j]  ;
        x[cnt + 1] = Path_y[i] [j] ;
        cnt ++;
    }
//     printf("\n%d\n",cnt);

    for (i = 0; i < cnt; i ++)
    {
        xnew[i] = (x[cnt-i-1] -x[cnt-1] )/(x[0] - x[cnt - 1]);
        ynew[i] = (y[cnt-i-1] -y[cnt-1] )/(y[0] - y[cnt - 1]);
    }

    xnew[cnt-1] = 1;
    ynew[cnt-1] = 1;
    xnew[0] = 0;
    ynew[0] = 0;

    linint(xnew, ynew, cnt, xx1, gamma, N);
//		cost = Cost_Group_Action_By_Gamma(v_pshape1->m_pfPhi, v_pshape1->m_pfTheta,  \
                    v_pshape2->m_pfPhi, v_pshape2->m_pfTheta, gamma, N,a,b);

    cost = 0;
    for(i = 0;i < N;i ++)
    {
        free(Energy[i]);
        free(Path_x[i]);
        free(Path_y[i]);
    }

    free(Path_x);
    free(Path_y);
    free(Energy);

    free(x);
    free(y);
    free(xx1);
    free(xnew);
    free(ynew);




    return cost;
}

float dpmatch::match_deprecate(int n, int T, float **q1, float **q2, float *gamma)
{
    // n is the dimension
    // T is the size (num of points along the shape)

    float **Energy = NULL;

    int Nbrs[][2] = {{1, 1}, {1, 2}, {2, 1}, {2, 3}, {3, 2},{ 1, 3},{ 3, 1}};
    const int NBR_SIZ = 7;


    int NumPlot = 15;
    float shfx = 0.2;
    float shfy = 0.2;
    int i = 0;
    int j = 0;
    int Num = 0;
    float CandE[NBR_SIZ];
    int k = 0,l = 0;
    float minCandE = 10000;
    int minCandE_idx = 0;
    float **Path_x = NULL;
    float **Path_y = NULL;
    float cost = 0;
    Path_x = (float **)malloc(T*sizeof(float *));  // This is Path(i,j,1) in Match.m
    Path_y = (float **)malloc(T*sizeof(float *));  // This is Path(i,j,2) in Match.m

    float *x = NULL;
    float *y = NULL;
    float *xnew = NULL;
    float *ynew = NULL;
    x = (float *)malloc(T*sizeof(float));
    y = (float *)malloc(T*sizeof(float));
    float *xx1 = (float *) malloc(T*sizeof(float) );

    xnew = (float *)malloc(T*sizeof(float));
    ynew = (float *)malloc(T*sizeof(float));

    int cnt = 0;
    Energy = (float **)malloc(T*sizeof(float *));

    for(i = 0;i < T;i ++)
    {
        Energy[i] = (float *)calloc(T,sizeof(float));
        Path_x[i] = (float *)calloc(T,sizeof(float));
        Path_y[i] = (float *)calloc(T,sizeof(float));
        //Forming energies associated with different paths
        Energy[0][i] = 5000000;
        Energy[i][0] = 5000000;
    }

/*		for(i = 1; i < N ; i ++)
    {
            Energy[0][i] = 5;
            Energy[i][0] = 5;
    }*/
    Energy[0][0] = 0;
    xx1[0] = 0;
//    printf("\n");
    for(i = 1 ; i < T; i ++)
    {
//            printf("%d ",i);
        fflush(stdout);
        for(j = 1; j < T ; j ++)
        {
            minCandE = 10000;
            for(Num = 0; Num < NBR_SIZ; Num ++)
            {
                k = i - Nbrs[Num][0];
                l = j - Nbrs[Num][1];
                if(k >= 0 && l >= 0)
                {
                    CandE[Num] = Energy[k][l] + DPcost_deprecate(q1, q2,n, T, k,l,i,j);
                }
                else
                {
                    CandE[Num] = 10000;
                }
                if(CandE[Num] < minCandE )
                {
                    minCandE = CandE[Num];
                    minCandE_idx = Num;
                }
                Energy[i][j] = minCandE;

                Path_x[i][j] = i - Nbrs[minCandE_idx][0];
                Path_y[i][j] = j - Nbrs[minCandE_idx][1];
            }
        }
        xx1[i] = (float ) i/(T - 1);
    }

    x[0] = T-1; y[0] = T-1;
    while ( x[cnt] > 0 )
    {
        i = (int) y[cnt];
        j = (int) x[cnt];
        y[cnt + 1] = Path_x[i] [j]  ;
        x[cnt + 1] = Path_y[i] [j] ;
        cnt ++;
    }
//     printf("\n%d\n",cnt);

    for (i = 0; i < cnt; i ++)
    {
        xnew[i] = (x[cnt-i-1] -x[cnt-1] )/(x[0] - x[cnt - 1]);
        ynew[i] = (y[cnt-i-1] -y[cnt-1] )/(y[0] - y[cnt - 1]);
    }

    xnew[cnt-1] = 1;
    ynew[cnt-1] = 1;
    xnew[0] = 0;
    ynew[0] = 0;

    linint(xnew, ynew, cnt, xx1, gamma, T);
//		cost = Cost_Group_Action_By_Gamma(v_pshape1->m_pfPhi, v_pshape1->m_pfTheta,  \
                    v_pshape2->m_pfPhi, v_pshape2->m_pfTheta, gamma, N,a,b);

    cost = 0;
    for(i = 0;i < T;i ++)
    {
        free(Energy[i]);
        free(Path_x[i]);
        free(Path_y[i]);
    }

    free(Path_x);
    free(Path_y);
    free(Energy);

    free(x);
    free(y);
    free(xx1);
    free(xnew);
    free(ynew);

    return cost;
}

float* dpmatch::match(int n, int T, float *q1, float *q2)
{
    // n is the dimension
    // T is the size (num of points along the shape)

    float **Energy = NULL;

//    int Nbrs[][2] = {{1, 1}, {1, 2}, {2, 1}, {2, 3}, {3, 2},{ 1, 3},{ 3, 1}};
//    const int NBR_SIZ = 7;

    const int Nbrs[][2] = {
            {  1,  1 }, {  1,  2 }, {  1,  3 }, {  1,  4 }, {  1,  5 }, {  1,  6 }, {  1,  7 }, {  1,  8 }, {  1,  9 }, {  1, 10 },
            {  2,  1 }, {  2,  3 }, {  2,  5 }, {  2,  7 }, {  2,  9 }, {  3,  1 }, {  3,  2 }, {  3,  4 }, {  3,  5 }, {  3,  7 },
            {  3,  8 }, {  3, 10 }, {  4,  1 }, {  4,  3 }, {  4,  5 }, {  4,  7 }, {  4,  9 }, {  5,  1 }, {  5,  2 }, {  5,  3 },
            {  5,  4 }, {  5,  6 }, {  5,  7 }, {  5,  8 }, {  5,  9 }, {  6,  1 }, {  6,  5 }, {  6,  7 }, {  7,  1 }, {  7,  2 },
            {  7,  3 }, {  7,  4 }, {  7,  5 }, {  7,  6 }, {  7,  8 }, {  7,  9 }, {  7, 10 }, {  8,  1 }, {  8,  3 }, {  8,  5 },
            {  8,  7 }, {  8,  9 }, {  9,  1 }, {  9,  2 }, {  9,  4 }, {  9,  5 }, {  9,  7 }, {  9,  8 }, {  9, 10 }, { 10,  1 },
            { 10,  3 }, { 10,  7 }, { 10,  9 }
    };
    const int NBR_SIZ = 63;
//    std::cout << "NBR_SIZ = " << NBR_SIZ << " ";

    int NumPlot = 15;
    float shfx = 0.2;
    float shfy = 0.2;
    int i = 0;
    int j = 0;
    int Num = 0;
    float CandE[NBR_SIZ];
    int k = 0,l = 0;
    float minCandE = 10000;
    int minCandE_idx = 0;
    float **Path_x = NULL;
    float **Path_y = NULL;
    float cost = 0;
    Path_x = (float **)malloc(T*sizeof(float *));  // This is Path(i,j,1) in Match.m
    Path_y = (float **)malloc(T*sizeof(float *));  // This is Path(i,j,2) in Match.m

    float *x = NULL;
    float *y = NULL;
    float *xnew = NULL;
    float *ynew = NULL;
    x = (float *)malloc(T*sizeof(float));
    y = (float *)malloc(T*sizeof(float));
    float *xx1 = (float *) malloc(T*sizeof(float) );

    xnew = (float *)malloc(T*sizeof(float));
    ynew = (float *)malloc(T*sizeof(float));

    int cnt = 0;
    Energy = (float **)malloc(T*sizeof(float *));

    for(i = 0;i < T;i ++)
    {
        Energy[i] = (float *)calloc(T,sizeof(float));
        Path_x[i] = (float *)calloc(T,sizeof(float));
        Path_y[i] = (float *)calloc(T,sizeof(float));
        //Forming energies associated with different paths
        Energy[0][i] = 5000000;
        Energy[i][0] = 5000000;
    }

/*		for(i = 1; i < N ; i ++)
    {
            Energy[0][i] = 5;
            Energy[i][0] = 5;
    }*/
    Energy[0][0] = 0;
    xx1[0] = 0;
//    printf("\n");
    for(i = 1 ; i < T; i ++)
    {
//            printf("%d ",i);
        fflush(stdout);
        for(j = 1; j < T ; j ++)
        {
            minCandE = 10000;
            for(Num = 0; Num < NBR_SIZ; Num ++)
            {
                k = i - Nbrs[Num][0];
                l = j - Nbrs[Num][1];
                if(k >= 0 && l >= 0)
                {
                    CandE[Num] = Energy[k][l] + DPcost(q1, q2,n, T, k,l,i,j);
                }
                else
                {
                    CandE[Num] = 10000;
                }
                if(CandE[Num] < minCandE )
                {
                    minCandE = CandE[Num];
                    minCandE_idx = Num;
                }
                Energy[i][j] = minCandE;

                Path_x[i][j] = i - Nbrs[minCandE_idx][0];
                Path_y[i][j] = j - Nbrs[minCandE_idx][1];
            }
        }
        xx1[i] = (float ) i/(T - 1);
    }

    x[0] = T-1; y[0] = T-1;
    while ( x[cnt] > 0 )
    {
        i = (int) y[cnt];
        j = (int) x[cnt];
        y[cnt + 1] = Path_x[i] [j]  ;
        x[cnt + 1] = Path_y[i] [j] ;
        cnt ++;
    }
//     printf("\n%d\n",cnt);

    for (i = 0; i < cnt; i ++)
    {
        xnew[i] = (x[cnt-i-1] -x[cnt-1] )/(x[0] - x[cnt - 1]);
        ynew[i] = (y[cnt-i-1] -y[cnt-1] )/(y[0] - y[cnt - 1]);
    }

    xnew[cnt-1] = 1;
    ynew[cnt-1] = 1;
    xnew[0] = 0;
    ynew[0] = 0;
    float* gamma = new float [T];
    linint(xnew, ynew, cnt, xx1, gamma, T);
//		cost = Cost_Group_Action_By_Gamma(v_pshape1->m_pfPhi, v_pshape1->m_pfTheta,  \
                    v_pshape2->m_pfPhi, v_pshape2->m_pfTheta, gamma, N,a,b);

    cost = 0;
    for(i = 0;i < T;i ++)
    {
        free(Energy[i]);
        free(Path_x[i]);
        free(Path_y[i]);
    }

    free(Path_x);
    free(Path_y);
    free(Energy);

    free(x);
    free(y);
    free(xx1);
    free(xnew);
    free(ynew);

    return(gamma);
}

float dpmatch::DPcost_deprecate(float **q1, float **q2, int n, int T, int k, int l, int i, int j)
{
    int x;
    float y;
    int y1,y2;
    float slope = 0;
    float E,E1,E2;
    float f;
    float vec11, vec12, vec21, vec22,vec23;

    E1 = 0; E2 = 0;
    E = 0;
    slope =(float ) ( i - k)/(j - l);
//	printf("slope1 %f\n",slope);
    if (slope == 0)
        printf("\nslope zero\n");
    float *vecarray = NULL;
    vecarray = (float *)malloc(n * sizeof(float));

    for(x = l; x <= j ; x ++)
    {
        y = k + (x - l) * slope;
        y1 = (int )floorf(y);
        y2 = (int )ceilf(y);
        f = y - y1;
        for (int kk = 0; kk < n; kk++)
        {
            vecarray[kk] = (f*q2[kk][y2] + (1 - f)*q2[kk][y1])*sqrt(slope);
            E2 = E2 + (q1[kk][x] - vecarray[kk])*(q1[kk][x] - vecarray[kk]);
        }
    }
    E = E2/T;
    //cout << E << " ";
    free(vecarray);
    vecarray = NULL;
    return E;
}

float dpmatch::DPcost(float *q1, float *q2, int n, int T, int k, int l, int i, int j)
{
    int x;
    float y;
    int y1,y2;
    float slope = 0;
    float E,E1,E2;
    float f;
    float vec11, vec12, vec21, vec22,vec23;

    E1 = 0; E2 = 0;
    E = 0;
    slope =(float ) ( i - k)/(j - l);
//	printf("slope1 %f\n",slope);
    if (slope == 0)
        printf("\nslope zero\n");
    float *vecarray = NULL;
    vecarray = (float *)malloc(n * sizeof(float));

    for(x = l; x <= j ; x ++)
    {
        y = k + (x - l) * slope;
        y1 = (int )floorf(y);
        y2 = (int )ceilf(y);
        f = y - y1;
        for (int kk = 0; kk < n; kk++)
        {
            vecarray[kk] = (f*q2[kk*T + y2] + (1 - f)*q2[kk*T + y1])*sqrt(slope);
            E2 = E2 + (q1[kk*T + x] - vecarray[kk])*(q1[kk*T + x] - vecarray[kk]);
        }
    }
    E = E2/T;
    //cout << E << " ";
    free(vecarray);
    vecarray = NULL;
    return E;
}

float dpmatch::MatchQ(shape *v_pshape1, shape *v_pshape2, float *gamma, float **Energy)
{
//    int Nbrs[][2] = {{0 ,0},{0, 1},{ 1, 0},{ 1, 2},{ 2, 1},{ 0, 2},{ 2, 0},{ 0, 3},{ 2, 3},{ 3 ,2},{ 3 ,2},{ 0, 4},{ 1, 4}, \
    { 2, 4},{ 3, 4},{ 4, 3},{ 4, 2},{ 4, 1},{ 4, 0} };
//    int Nbrs[][2] = {{1 ,1},{1, 2},{ 2, 1},{ 2, 3},{ 3, 2},{ 1, 3},{ 3, 1},{1, 4},{ 3, 4},{4 ,3},{ 4,1},{ 1, 5},{ 2, 5}, \
    { 3, 5},{ 4, 5},{5, 4},{ 5, 3},{5, 2},{ 5, 1},{1,6},{5,6},{6,5},{6,1},{1,7},{2,7},{3,7},{4,7},{5,7},{6,7}, \
		{4,10}, {4,30}, {4,40}, {4,50}, {5,50},{6,50},{8,50},{10,50},{15,50},{20,50},{25,50},{30,50},{35,50},{40,50}    };
   
// drastic  
//     int Nbrs[][2] = \
//     {{1, 1},{1, 2},{2, 1},{2, 3},{3, 2},{1, 3},{3, 1},{1, 4},{3, 4},{4, 3},{4, 1},{1, 5},{2, 5},{3, 5},{4, 5}, \
//      {5, 4},{5, 3},{5, 2},{5, 1},{1, 6},{5, 6},{6, 5},{6, 1},{1, 7},{2, 7},{3, 7},{4, 7},{5, 7},{6, 7},{1, 6},\
//      {1, 7},{1, 8},{1, 9},{1, 10},{7, 1},{8, 1},{9, 1},{10, 1},{1, 20}, {2, 20},{3, 30},\
// 
//     };
//     const int NBR_SIZ = 41;
//     
    
    
// 	int Nbrs[][2] = {{1, 1}, {1, 2}, {2, 1}, {2, 3}, {3, 2},{ 1, 3},{ 3, 1}, {1, 4}, {3, 4}, {4, 3}, {4, 1}, {1, 5}, {5, 1}, {2, 5}, {3, 5}, {4, 5} };
// 	const int NBR_SIZ = 16;
	

// 	const int Nbrs[][2] = {
// 	{  1,  1 }, {  1,  2 }, {  1,  3 }, {  1,  4 }, {  1,  5 }, {  1,  6 },
// 	{  2,  1 }, {  2,  3 }, {  2,  5 }, {  2,  7 },
// 	{  3,  1 }, {  3,  2 }, {  3,  4 }, {  3,  5 }, {  3,  7 },
//     {  4,  1 }, {  4,  3 }, {  4,  5 }, {  4,  7 },
//     {  5,  1 }, {  5,  2 }, {  5,  3 },	{  5,  4 }, {  5,  6 }, {  5,  7 },
//     {  6,  1 }, {  6,  5 }, {  6,  7 }
//     };
//
// 	const int NBR_SIZ = 28;
//


// 	int Nbrs[][2] = {{1, 1}, {1, 2}, {2, 1}, {2, 3}, {3, 2},{ 1, 3},{ 3, 1}, {1, 4}, {3, 4}, {4, 3}, {4, 1}};
// 	const int NBR_SIZ = 11;
// 
	int Nbrs[][2] = {{1, 1}, {1, 2}, {2, 1}, {2, 3}, {3, 2},{ 1, 3},{ 3, 1}};
	const int NBR_SIZ = 7;


    int NumPlot = 15;
    float shfx = 0.2;
    float shfy = 0.2;
    int N = 0;
    N = v_pshape1->m_iT;
    int i = 0;
    int j = 0;
    int Num = 0;
    float CandE[NBR_SIZ];
    int k = 0,l = 0;
    float minCandE = 10000;
    int minCandE_idx = 0;
    float **Path_x = NULL;
    float **Path_y = NULL;
    float cost = 0;
    Path_x = (float **)malloc(N*sizeof(float *));  // This is Path(i,j,1) in Match.m
    Path_y = (float **)malloc(N*sizeof(float *));  // This is Path(i,j,2) in Match.m

    float *x = NULL; 
    float *y = NULL;
    float *xnew = NULL; 
    float *ynew = NULL;
    x = (float *)malloc(N*sizeof(float));
    y = (float *)malloc(N*sizeof(float));
    float *xx1 = (float *) malloc(N*sizeof(float) );	

    xnew = (float *)malloc(N*sizeof(float));
    ynew = (float *)malloc(N*sizeof(float));

    int cnt = 0;
    Energy = (float **)malloc(N*sizeof(float *));

    for(i = 0;i < N;i ++)
    {
            Energy[i] = (float *)calloc(N,sizeof(float));	
            Path_x[i] = (float *)calloc(N,sizeof(float));	
            Path_y[i] = (float *)calloc(N,sizeof(float));	
            //Forming energies associated with different paths
            Energy[0][i] = 5000000;	
            Energy[i][0] = 5000000;
    }

/*		for(i = 1; i < N ; i ++)
    {
            Energy[0][i] = 5;	
            Energy[i][0] = 5;
    }*/
    Energy[0][0] = 0;
    xx1[0] = 0;
//    printf("\n");
    for(i = 1 ; i < N; i ++)
    {
//            printf("%d ",i);
            fflush(stdout);
            for(j = 1; j < N ; j ++)
            {
                    minCandE = 10000;
                    for(Num = 0; Num < NBR_SIZ; Num ++)
                    {
                            k = i - Nbrs[Num][0];
                            l = j - Nbrs[Num][1];
                            if(k >= 0 && l >= 0)
                            {
                                    CandE[Num] = Energy[k][l] + Match_CostQ(v_pshape1, v_pshape2,k,l,i,j);
                            }
                            else
                            {
                                    CandE[Num] = 10000;
                            }
                            if(CandE[Num] < minCandE )
                            {
                                    minCandE = CandE[Num];
                                    minCandE_idx = Num;	
                            }
                            Energy[i][j] = minCandE;

                            Path_x[i][j] = i - Nbrs[minCandE_idx][0];
                            Path_y[i][j] = j - Nbrs[minCandE_idx][1];		
                    }
            }	
            xx1[i] = (float ) i/(N - 1);				
    }

    x[0] = N-1; y[0] = N-1;
    while ( x[cnt] > 0 )
    {
            i = (int) y[cnt];
            j = (int) x[cnt];
            y[cnt + 1] = Path_x[i] [j]  ;
            x[cnt + 1] = Path_y[i] [j] ;
            cnt ++;
    }
//     printf("\n%d\n",cnt);

    for (i = 0; i < cnt; i ++)
    {
            xnew[i] = (x[cnt-i-1] -x[cnt-1] )/(x[0] - x[cnt - 1]);
            ynew[i] = (y[cnt-i-1] -y[cnt-1] )/(y[0] - y[cnt - 1]);
    }

    xnew[cnt-1] = 1;
    ynew[cnt-1] = 1;
    xnew[0] = 0;
    ynew[0] = 0;

    linint(xnew, ynew, cnt, xx1, gamma, N);
//		cost = Cost_Group_Action_By_Gamma(v_pshape1->m_pfPhi, v_pshape1->m_pfTheta,  \
                    v_pshape2->m_pfPhi, v_pshape2->m_pfTheta, gamma, N,a,b);

    cost = 0;				
    for(i = 0;i < N;i ++)
    {
            free(Energy[i]);
            free(Path_x[i]);
            free(Path_y[i]);
    }

    free(Path_x);	
    free(Path_y);
    free(Energy);

    free(x);
    free(y);
    free(xx1);
    free(xnew);
    free(ynew);




    return cost;
}

/*

float MatchPaths(shape *v_pshape1, shape *v_pshape2,float a, float b , float *gamma, float **Energy)
{
    //int Nbrs[][2] = {{0 ,0},{0, 1},{ 1, 0},{ 1, 2},{ 2, 1},{ 0, 2},{ 2, 0},{ 0, 3},{ 2, 3},{ 3 ,2},{ 3 ,2},{ 0, 4},{ 1, 4}, \
    { 2, 4},{ 3, 4},{ 4, 3},{ 4, 2},{ 4, 1},{ 4, 0} };
    int Nbrs[][2] = {{1 ,1},{1, 2},{ 2, 1},{ 2, 3},{ 3, 2},{ 1, 3},{ 3, 1},{1, 4},{ 3, 4},{4 ,3},{ 4,1},{ 1, 5},{ 2, 5}, \
    { 3, 5},{ 4, 5},{5, 4},{ 5, 3},{5, 2},{ 5, 1},{1,6},{5,6},{6,5},{6,1},{1,7},{2,7},{3,7},{4,7},{5,7},{6,7} };
    const int NBR_SIZ = 29;
    int NumPlot = 15;
    float shfx = 0.2;
    float shfy = 0.2;
    int N = 0;
    N = v_pshape1->m_iT;
    int i = 0;
    int j = 0;
    int Num = 0;
    float CandE[NBR_SIZ];
    int k = 0,l = 0;
    float minCandE = 10000;
    int minCandE_idx = 0;
    float **Path_x = NULL;
    float **Path_y = NULL;
    float cost = 0;
    Path_x = (float **)malloc(N*sizeof(float *));  // This is Path(i,j,1) in Match.m
    Path_y = (float **)malloc(N*sizeof(float *));  // This is Path(i,j,2) in Match.m

    float *x = NULL; 
    float *y = NULL;
    float *xnew = NULL; 
    float *ynew = NULL;
    x = (float *)malloc(N*sizeof(float));
    y = (float *)malloc(N*sizeof(float));
    float *xx1 = (float *) malloc(N*sizeof(float) );	

    xnew = (float *)malloc(N*sizeof(float));
    ynew = (float *)malloc(N*sizeof(float));

    int cnt = 0;
    Energy = (float **)malloc(N*sizeof(float *));

    for(i = 0;i < N;i ++)
    {
            Energy[i] = (float *)calloc(N,sizeof(float));	
            Path_x[i] = (float *)calloc(N,sizeof(float));	
            Path_y[i] = (float *)calloc(N,sizeof(float));	
            //Forming energies associated with different paths
            Energy[0][i] = 5;	
            Energy[i][0] = 5;
    }


    Energy[0][0] = 0;
    xx1[0] = 0;
    for(i = 1 ; i < N; i ++)
    {
            for(j = 1; j < N ; j ++)
            {
                    minCandE = 10000;
                    for(Num = 0; Num < NBR_SIZ; Num ++)
                    {
                            k = i - Nbrs[Num][0];
                            l = j - Nbrs[Num][1];
                            if(k >= 0 && l >= 0)
                            {
                                    CandE[Num] = Energy[k][l] + Match_CostPaths(v_pshape1, v_pshape2,k,l,i,j,a ,b);
                            }
                            else
                            {
                                    CandE[Num] = 10000;
                            }
                            if(CandE[Num] < minCandE )
                            {
                                    minCandE = CandE[Num];
                                    minCandE_idx = Num;	
                            }
                            Energy[i][j] = minCandE;

                            Path_x[i][j] = i - Nbrs[minCandE_idx][0];
                            Path_y[i][j] = j - Nbrs[minCandE_idx][1];		
                    }
            }	
            xx1[i] = (float ) i/(N - 1);				
    }

    x[0] = N-1; y[0] = N-1;
    while ( x[cnt] > 0 )
    {
            i = (int) y[cnt];
            j = (int) x[cnt];
            y[cnt + 1] = Path_x[i] [j]  ;
            x[cnt + 1] = Path_y[i] [j] ;
            cnt ++;
    }

    for (i = 0; i < cnt; i ++)
    {
            xnew[i] = (x[cnt-i-1] -x[cnt-1] )/(x[0] - x[cnt - 1]);
            ynew[i] = (y[cnt-i-1] -y[cnt-1] )/(y[0] - y[cnt - 1]);
    }

    xnew[cnt-1] = 1;
    ynew[cnt-1] = 1;
    xnew[0] = 0;
    ynew[0] = 0;

    linint(xnew, ynew, cnt, xx1, gamma, N);
//		cost = Cost_Group_Action_By_Gamma(v_pshape1->m_pfPhi, v_pshape1->m_pfTheta,  \
                    v_pshape2->m_pfPhi, v_pshape2->m_pfTheta, gamma, N,a,b);

    cost = 0;				
    for(i = 0;i < N;i ++)
    {
            free(Energy[i]);
            free(Path_x[i]);
            free(Path_y[i]);
    }

    free(Path_x);	
    free(Path_y);
    free(Energy);

    free(x);
    free(y);
    free(xx1);
    free(xnew);
    free(ynew);




    return cost;
}

 */

float dpmatch::Match_Cost_Coords_depracate(shape *v_ps1, shape *v_ps2, int k, int l, int i, int j)
{
    int x;
    float y;
    int y1,y2;
    float slope = 0;
    float E,E1,E2;
    float f;
    float vec11, vec12, vec21, vec22,vec23;

    E1 = 0; E2 = 0;
    E = 0;
    slope =(float ) ( i - k)/(j - l);
//	printf("slope1 %f\n",slope);
    if (slope == 0)
        printf("\nslope zero\n");
    float *vecarray = NULL;
    vecarray = (float *)malloc(v_ps1->m_n * sizeof(float));

    for(x = l; x <= j ; x ++)
    {
        y = k + (x - l) * slope;
        y1 = (int )floorf(y);
        y2 = (int )ceilf(y);
        f = y - y1;
        for (int kk = 0; kk < v_ps1->m_n; kk++)
        {
            vecarray[kk] = (f*v_ps2->arr[kk][y2] + (1 - f)*v_ps2->arr[kk][y1]);
            E2 = E2 + (v_ps1->arr[kk][x] - vecarray[kk])*(v_ps1->arr[kk][x] - vecarray[kk]);
        }
    }
    E = E2/(v_ps1->m_iT);
    //cout << E << " ";
    free(vecarray);
    vecarray = NULL;
    return E;

}

float dpmatch::Match_CostQ(shape *v_ps1, shape *v_ps2, int k, int l, int i, int j)
{
	int x;
	float y;
	int y1,y2;
	float slope = 0;
	float E,E1,E2;
	float f;
	float vec11, vec12, vec21, vec22,vec23;
	
	E1 = 0; E2 = 0;
	E = 0;
	slope =(float ) ( i - k)/(j - l);
//	printf("slope1 %f\n",slope);
	if (slope == 0)
		printf("\nslope zero\n");
    float *vecarray = NULL;
    vecarray = (float *)malloc(v_ps1->m_n * sizeof(float));

	for(x = l; x <= j ; x ++)
	{
            y = k + (x - l) * slope;
            y1 = (int )floorf(y);
            y2 = (int )ceilf(y);
            f = y - y1;
            for (int kk = 0; kk < v_ps1->m_n; kk++)
            {
                vecarray[kk] = (f*v_ps2->arr[kk][y2] + (1 - f)*v_ps2->arr[kk][y1])*sqrt(slope);
                E2 = E2 + (v_ps1->arr[kk][x] - vecarray[kk])*(v_ps1->arr[kk][x] - vecarray[kk]);
            }
    }
	E = E2/(v_ps1->m_iT);
	//cout << E << " ";
	free(vecarray);
    vecarray = NULL;
	return E;
        
}



float dpmatch::L2_Costfn(float *v_Phi1, float *v_Theta1, float *v_Phi2, float *v_Theta2, int T, float v_a , float v_b)
{
	int i = 0;
	float tmp_phi = 0;
	float tmp_theta = 0;
	float cost = 0;
	for(i = 0; i < T; i ++)
	{
		cost = cost + (v_Phi1[i] - v_Phi2[i]) * (v_Phi1[i] - v_Phi2[i])  /  
						+ (v_Theta1[i] - v_Theta2[i]) * (v_Theta1[i] - v_Theta2[i]);
	}
	return cost;
}


float dpmatch::norm(float *v_pfArray, int v_ilen)
{
	float normval = 0;
	for(int i = 0; i < v_ilen; i ++)
	{
		normval += v_pfArray[i]*v_pfArray[i];
	}
	normval = sqrt(normval);
		
	return normval;
}

bool dpmatch::writegamma(FILE *vl_fpDirFn, float *gamma, int T)
{
    size_t bytes_written;
    if( vl_fpDirFn == NULL)
    {
        printf("\nError: File cannot be opened for appending");
        return false;
    }
    bytes_written = fwrite((void*)&T,sizeof(int),1,vl_fpDirFn);
    bytes_written = fwrite((void*)gamma,sizeof(float),T,vl_fpDirFn);
    if(bytes_written == T)
        return true;
    else
        return false;
}

bool dpmatch::WriteGamma_deprecate(FILE *vl_fpDirFn , float *gamma, int shift, shape *s2)
{
	size_t bytes_written;
	int N = s2->m_iT;
	if( vl_fpDirFn == NULL)
	{
		printf("\nError: File cannot be opened for appending");
		return false;
	}
	bytes_written = fwrite((void*)&N,sizeof(int),1,vl_fpDirFn);
	bytes_written = fwrite((void*)&shift,sizeof(int),1,vl_fpDirFn);
	bytes_written = fwrite((void*)gamma,sizeof(float),N,vl_fpDirFn);
	bytes_written = fwrite((void*)s2->m_pfPhi,sizeof(float),N,vl_fpDirFn);	
	bytes_written = fwrite((void*)s2->m_pfTheta,sizeof(float),N,vl_fpDirFn);
	//printf("\nbytes written %d",bytes_written);
	if(bytes_written == N)
		return true;
	else
		return false;
}

bool dpmatch::WriteGammaV(FILE *vl_fpDirFn , float *gamma, int shift, shape *s2)
{
	size_t bytes_written;
	int N = s2->m_iT;
	if( vl_fpDirFn == NULL)
	{
		printf("\nError: File cannot be opened for appending");
		return false;
	}
	bytes_written = fwrite((void*)&N,sizeof(int),1,vl_fpDirFn);
//	bytes_written = fwrite((void*)&shift,sizeof(int),1,vl_fpDirFn);
	bytes_written = fwrite((void*)gamma,sizeof(float),N,vl_fpDirFn);
//	bytes_written = fwrite((void*)s2->m_pfPhi,sizeof(float),N,vl_fpDirFn);	
//	bytes_written = fwrite((void*)s2->m_pfTheta,sizeof(float),N,vl_fpDirFn);
	//printf("\nbytes written %d",bytes_written);
	if(bytes_written == N)
		return true;
	else
		return false;
}

void dpmatch::linint(float *xnew, float *ynew, int cnt, float *xx, float *yy, int n)
{
	int i = 0;
	int idx = 0;
	//Assume xnew and xx are sorted. 
	//Find the interval where xx[0] is located
	float m = 0;
	for (i = 0; i < n; i ++)
	{
		while(idx < cnt - 1)
		{
			if(xx[i] >= xnew[idx] && xx[i] <= xnew[idx+1] )
			{
				yy[i] = ynew[idx] + (xx[i] - xnew[idx]) *( ynew[idx+1] - ynew[idx] ) / ( xnew[idx+1] - xnew[idx] );
				break;
			}
			else if ( xx[i] <= xnew[idx+1] )
			{
				// Need to extrapolate
				// Use the slope 	of points corresponding to idx and idx + 1
				m = (ynew[idx+1]  - ynew[idx])/(xnew[idx+1]  - xnew[idx]);
				yy[i] = ynew[idx] + m * ( xx[i] - xnew[idx]);
				break;
			}
			else if(xx[i] >= xnew[cnt-1] )
			{
				//This is beyond the boundary of xnew
				// Need to extrapolate
				// Use the slope 	of points corresponding to cnt -1 and cnt -2
				m = (ynew[cnt-1]  - ynew[cnt-2])/(xnew[cnt-1]  - xnew[cnt-2]);
				yy[i] = ynew[cnt - 1] + m * ( xx[i] - xnew[cnt-1]);			
				break;
			}
			else 
				idx ++;
			}
		}
}

void dpmatch::spline(float *x, float *y, int n, float yp1, float ypn, float *y2)
{
	int i,k;
	float p,qn,sig,un,*u;
	
	u = (float *)malloc(n*sizeof(float));
	if (yp1 > 0.99e20) 
		y2[1]=u[1]=0.0;
	else 
	{ 
		y2[1] = -0.5;
		u[1]=(3.0/(x[2]-x[1]))*((y[2]-y[1])/(x[2]-x[1])-yp1);
	}

	
	for (i=2;i<=n-1;i++) 
	{ 
		sig=(x[i]-x[i-1])/(x[i+1]-x[i-1]);
		p=sig*y2[i-1]+2.0;
		y2[i]=(sig-1.0)/p;
		u[i]=(y[i+1]-y[i])/(x[i+1]-x[i]) - (y[i]-y[i-1])/(x[i]-x[i-1]);
		u[i]=(6.0*u[i]/(x[i+1]-x[i-1])-sig*u[i-1])/p;

	}

	if (ypn > 0.99e30) 
		qn=un=0.0; 
	else 
	{ 
		qn=0.5;
		un=(3.0/(x[n]-x[n-1]))*(ypn-(y[n]-y[n-1])/(x[n]-x[n-1]));
	}

	y2[n]=(un-qn*u[n-1])/(qn*y2[n-1]+1.0);
	for (k=n-1;k>=1;k--) 
	{
		y2[k]=y2[k]*y2[k+1]+u[k]; 
	}
	free(u);
}

void dpmatch::splint(float *xa, float *ya, float *y2a, int n, float x, float *y)
{
	int klo,khi,k;
	float h,b,a;

	klo=1;
	khi=n;
	while (khi-klo > 1) 
	{
		k=(khi+klo) >> 1;
		if (xa[k] > x) 
			khi=k;
		else
			klo=k;
		h=xa[khi]-xa[klo];
		if (h == 0.0) 
			printf("\n Bad xa input to routine splint\n ");
		a=( xa[khi]-x)/h;
		b=(x-xa[klo])/h;
		*y=a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]+(b*b*b-b)*y2a[khi])*(h*h)/6.0;

	}
}


void dpmatch::copy(int T, float *src, float *dest)
{
	for(int i = 0; i < T; i++)
	{
		dest[i] = src[i];
	}
	
}

void dpmatch::print_int(int T)
{
    std::cout << "This is dpmatch " << T <<".\n";
}


shape::shape()
{


}

shape::shape( int v_iT)
{
    m_pfPhi = (float *)malloc(v_iT*sizeof(float));
    m_pfTheta = (float *)malloc(v_iT*sizeof(float));
    m_v11 = (float *)malloc(v_iT*sizeof(float));
    m_v12 = (float *)malloc(v_iT*sizeof(float));
    m_v13 = (float *)malloc(v_iT*sizeof(float));
    m_iT = v_iT;

}

shape::shape(int n, int v_iT)
{
    m_pfPhi = (float *)malloc(v_iT*sizeof(float));
    m_pfTheta = (float *)malloc(v_iT*sizeof(float));
    m_v11 = (float *)malloc(v_iT*sizeof(float));
    m_v12 = (float *)malloc(v_iT*sizeof(float));
    if(n == 3)
        m_v13 = (float *)malloc(v_iT*sizeof(float));
    m_iT = v_iT;
    m_n = n;

    arr = (float **)malloc(n * sizeof(float *));
    for (int i=0; i<n; i++)
        arr[i] = (float *)malloc(v_iT * sizeof(int));

}

shape::shape(shape &s2)
{
    m_pfPhi = (float *)malloc(s2.m_iT*sizeof(float));
    m_pfTheta = (float *)malloc(s2.m_iT*sizeof(float));

    m_iT = s2.m_iT;
    if(m_pfPhi != NULL && m_pfTheta != NULL)
    {
        for(int i = 0; i < s2.m_iT; i ++)
        {
            m_pfPhi[i] = s2.m_pfPhi[i];
            m_pfTheta[i] = s2.m_pfTheta[i];
        }
    }
}
shape::shape(int v_iT,float *v_pfPhi, float *v_pfTheta)
{
    m_pfPhi = (float *)malloc(v_iT*sizeof(float));
    m_pfTheta = (float *)malloc(v_iT*sizeof(float));


    copy(v_iT,v_pfPhi,m_pfPhi);
    copy(v_iT,v_pfTheta,m_pfTheta);
    m_iT = v_iT;
}

//Overloading the assignment operator
shape& shape::operator = (const shape &s)
{
    if(this == &s)		// To prevent assignment to itself
        return *this;
    delete m_pfPhi;
    delete m_pfTheta;

    m_iT = s.m_iT;
    m_pfPhi = new float[m_iT];
    m_pfTheta = new float[m_iT];
    for(int i = 0; i < m_iT; i ++)
    {
        m_pfPhi[i] = s.m_pfPhi[i];
        m_pfTheta[i] = s.m_pfTheta[i];
    }
    return *this;
}

void shape::create(int v_iT)
{
    m_pfPhi = (float *)calloc(v_iT,sizeof(float));
    m_pfTheta = (float *)calloc(v_iT,sizeof(float));
    m_iT = v_iT;
}

void shape::create(int v_iT,float *v_Phi, float *v_Theta)
{
    m_pfPhi = (float *)calloc(v_iT,sizeof(float));
    m_pfTheta = (float *)calloc(v_iT,sizeof(float));
    copy(v_iT,v_Phi,m_pfPhi);
    copy(v_iT,v_Theta,m_pfTheta);
    m_iT = v_iT;
}

void shape::Initialize(int v_iT,float *v_Phi, float *v_Theta)  //Assumes already created  shape object
{
    copy(v_iT,v_Phi,m_pfPhi);
    copy(v_iT,v_Theta,m_pfTheta);
    m_iT = v_iT;
}


float shape::L2_Costfn(shape & s2)
{
    int i = 0;
    float tmp_phi = 0;
    float tmp_theta = 0;
    float cost = 0;
    for(i = 0; i < m_iT; i ++)
    {
//		cost = cost + pow(m_pfPhi[i] - s2.m_pfPhi[i],2) + pow(m_pfTheta[i] - s2.m_pfTheta[i],2);
        cost = cost + (m_pfPhi[i] - s2.m_pfPhi[i])*(m_pfPhi[i] - s2.m_pfPhi[i]) + (m_pfTheta[i] - s2.m_pfTheta[i])*(m_pfTheta[i] - s2.m_pfTheta[i]);
    }
    return cost;
}

void shape::copy(int T, float *src, float *dest)
{
    for(int i = 0; i < T; i++)
    {
        dest[i] = src[i];
    }
}


shape::~shape()
{
    free(m_pfPhi);
    free(m_pfTheta);
    for (int i=0; i<m_n; i++)
        free(arr[i]);
    free(arr);

}
