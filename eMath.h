#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


/*********************************************/
//This library was created for personal usage//
//            by 31v1nm4rk                   //
/********************************************/

#define PI 3.1415926535897932

typedef struct eVector{
  double* data;
  int length;
}eVector;

typedef struct eMatrix{
  eVector* data;
  int rows;
  int cols;
}eMatrix;

typedef struct eComplex{
	double re;
	double im;
}eComplex;

/*************************************/
//Basic operations matrix and vectors//
/************************************/
void init_vector(eVector* v,int nelems);
void init_matrix(eMatrix* m,int rows,int cols);
void create_vector(eVector *v,double* data,int nelems);
void print_vector(eVector v);
void create_matrix(eMatrix *m,double** data,int rows,int cols);
void print_matrix(eMatrix m);
void random_vector(eVector *v);
void random_matrix(eMatrix *m);
void ones_matrix(eMatrix *m);
void eye_matrix(eMatrix *m);
void sum_vector(eVector* ans,eVector a,eVector b);
void sum_matrix(eMatrix* ans,eMatrix a,eMatrix b);
void dif_vector(eVector* ans,eVector a,eVector b);
void dif_matrix(eMatrix* ans,eMatrix a,eMatrix b);
void mul_num_vector(eVector* ans,double num,eVector b);
void mul_num_matrix(eMatrix* ans,double num,eMatrix b);
void mul_matrix(eMatrix* ans,eMatrix a,eMatrix b);
void dot_vector(double *ans,eVector a,eVector b);
void dot_matrix(eMatrix *ans,eMatrix a,eMatrix b);
void trans_matrix(eMatrix *ans,eMatrix a);
void norm_vector(double *ans,eVector v);
void LU_fact_matrix(eMatrix *L,eMatrix *U,eMatrix a);
void QR_fact_matrix(eMatrix *Q,eMatrix *R,eMatrix a);
void det_matrix(double *ans,eMatrix m);
void load_matrix(eMatrix *out,char* dir,int rows,int cols);
void load_vector(eVector *out,char* dir,int length);
void save_vector(char* dir,eVector v);
void save_matrix(char* dir,eMatrix m);
void str_2_vector(eVector *ans,char* s,int length);
void str_2_matrix(eMatrix *ans,char* s,int rows,int cols);
void solve_linear_system(eVector* ans,eMatrix A,eVector b);
void inv_matrix(eMatrix* ans,eMatrix m);
void eigen_matrix(eMatrix* e_vectors,eVector* e_values,eMatrix m,int N);

/************/
//Statistics//
/************/

void average_data(double *ans,eVector v);
void std_dev_data(double *ans,eVector v);
void least_square_data(eVector *ans,eVector x,eVector y);
void gaussian_dist(double *ans,double avg,double std_dev,double x);

/**********/
//Calculus//
/*********/

void diff_function(double* ans,void fun_f(double*,double),double x0,double h);
void integrate_function(double *ans,void fun_f(double*,double),double x_0,double x_1,int N);

/*********************************/
//Ordinary differential equations//
/********************************/

void ode_solver(eVector *data,void fun_ode(double *,double*,int),double* init_cond,int n_var,int N);

/*********/
//Complex//
/********/ 

void print_complex(eComplex c1);
void sum_complex(eComplex *ans,eComplex c1,eComplex c2);
void dif_complex(eComplex *ans,eComplex c1,eComplex c2);
void prod_complex(eComplex *ans,eComplex c1,eComplex c2);
void conjugate_complex(eComplex *ans,eComplex c1);
void norm_complex(double *ans,eComplex c1);
void exp_complex(eComplex *ans, eComplex c1);
void fft(eComplex **ans,eComplex *data,int N);