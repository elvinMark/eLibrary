#include "eMath.h"

void init_vector(eVector* v,int nelems){
  v->data = (double*) malloc(sizeof(double)*nelems);
  v->length = nelems;
}

void init_matrix(eMatrix* m,int rows,int cols){
  m->data = (eVector*) malloc(sizeof(eVector)*rows);
  int i;
  for(i=0;i<rows;i++){
    init_vector(&m->data[i],cols);
  }
  m->rows = rows;
  m->cols = cols;
}

void create_vector(eVector* v,double* data,int nelems){
  v->data = data;
  v->length = nelems;
}

void print_vector(eVector v){
  int i;
  printf("[");
  for(i=0;i<v.length;i++){
    printf("%lf ",v.data[i]);
  }
  printf("]\n");
}

void create_matrix(eMatrix* m,double** data,int rows,int cols){
  int i,j;
  eVector* v_data = (eVector*) malloc(sizeof(eVector)*rows);
  for(i=0;i<rows;i++){
    create_vector(v_data+i,data[i],cols);
  }
  m->data = v_data;
  m->rows = rows;
  m->cols = cols;
}

void print_matrix(eMatrix m){
  int i;
  printf("[\n");
  for(i=0;i<m.rows;i++){
    print_vector(m.data[i]);
  }
  printf("]\n");
}

void random_vector(eVector *v){
  srand(time(NULL));
  int i;
  for(i=0;i<v->length;i++){
    v->data[i] = rand()%1000/1000.0;
  }
}

void random_matrix(eMatrix *m){
  srand(time(NULL));
  int i,j;
  for(i=0;i<m->rows;i++){
    for(j=0;j<m->cols;j++){
      m->data[i].data[j] = rand()%1000/1000.0;
    }
  }
}

void ones_vector(eVector *v){
  int i;
  for(i=0;i<v->length;i++){
    v->data[i] = 1.0;
  }
}

void ones_matrix(eMatrix *m){
  int i,j;
  for(i=0;i<m->rows;i++){
    for(j=0;j<m->cols;j++){
      m->data[i].data[j] = 1.0;
    }
  }
}

void eye_matrix(eMatrix *m){
 int i,j;
  for(i=0;i<m->rows;i++){
    for(j=0;j<m->cols;j++){
      if(i==j)
        m->data[i].data[j] = 1.0;
      else
        m->data[i].data[j] = 0.0;
    }
  } 
}

void sum_vector(eVector* ans,eVector a,eVector b){
  int i;
  init_vector(ans,a.length);
  for(i=0;i<a.length;i++){
    ans->data[i] = a.data[i] + b.data[i];
  }
}

void sum_matrix(eMatrix* ans,eMatrix a,eMatrix b){
  int i,j;
  int rows=a.rows,cols=a.cols;
  init_matrix(ans,rows,cols);
  for(i=0;i<rows;i++){
    for(j=0;j<cols;j++){
      ans->data[i].data[j] = a.data[i].data[j] + b.data[i].data[j];
    }
  }
}

void dif_vector(eVector* ans,eVector a,eVector b){
  int i;
  init_vector(ans,a.length);
  for(i=0;i<a.length;i++){
    ans->data[i] = a.data[i] - b.data[i];
  }
}

void dif_matrix(eMatrix* ans,eMatrix a,eMatrix b){
  int i,j;
  int rows=a.rows,cols=a.cols;
  init_matrix(ans,rows,cols);
  for(i=0;i<rows;i++){
    for(j=0;j<cols;j++){
      ans->data[i].data[j] = a.data[i].data[j] - b.data[i].data[j];
    }
  }
}

void mul_num_vector(eVector *ans,double num,eVector a){
  int i;
  init_vector(ans,a.length);
  for(i=0;i<a.length;i++){
    ans->data[i] = num*a.data[i];
  }
}

void mul_num_matrix(eMatrix *ans,double num,eMatrix a){
  int i,j;
  int rows=a.rows,cols=a.cols;
  init_matrix(ans,rows,cols);
  for(i=0;i<rows;i++){
    for(j=0;j<cols;j++){
      ans->data[i].data[j] = num*a.data[i].data[j];
    }
  }
}

void mul_matrix(eMatrix* ans,eMatrix a,eMatrix b){
  int i,j;
  init_matrix(ans,a.rows,a.cols);
  for(i=0;i<a.rows;i++){
    for(j=0;j<a.cols;j++){
      ans->data[i].data[j] = a.data[i].data[j]*b.data[i].data[j];
    }
  }
}

void dot_vector(double* ans,eVector a,eVector b){
  int i;
  *ans = 0;
  for(i=0;i<a.length;i++){
    *ans = *ans + a.data[i]*b.data[i];
  }
}

void dot_matrix(eMatrix* ans,eMatrix a,eMatrix b){
  int i,j,k;
  init_matrix(ans,a.rows,b.cols);
  double s;
  for(i=0;i<a.rows;i++){
    for(j=0;j<b.cols;j++){
      s=0;
      for(k=0;k<a.cols;k++){
	s = s + a.data[i].data[k]*b.data[k].data[j];
      }
      ans->data[i].data[j] = s;
    }
  }
}

void trans_matrix(eMatrix* ans,eMatrix a){
  int i,j;
  init_matrix(ans,a.cols,a.rows);
  for(i=0;i<a.rows;i++){
    for(j=0;j<a.cols;j++){
      ans->data[j].data[i] = a.data[i].data[j];
    }
  }
}

void norm_vector(double *ans,eVector v){
  int i;
  *ans = 0;
  for(i=0;i<v.length;i++){
    *ans = *ans + v.data[i]*v.data[i];
  }
  *ans = sqrt(*ans);
}

void LU_fact_matrix(eMatrix *L,eMatrix *U,eMatrix a){
  init_matrix(L,a.rows,a.cols);
  init_matrix(U,a.rows,a.cols);
  int i,j,k;
  double s;
  for(i=0;i<a.rows;i++){
    U->data[i].data[i] = 1;
    for(k=i;k<a.rows;k++){
      s = 0;
      for(j=0;j<i;j++){
	s = s + L->data[k].data[j]*U->data[j].data[i];
      }
      L->data[k].data[i] = a.data[k].data[i] - s;
    }
    for(k=i+1;k<a.rows;k++){
      s = 0;
      for(j=0;j<i;j++){
	s = s + L->data[i].data[j]*U->data[j].data[k];
      }
      U->data[i].data[k] = (a.data[i].data[k] - s)/L->data[i].data[i];
    }
  }
}

void QR_fact_matrix(eMatrix *Q,eMatrix *R,eMatrix a){
  int i,j;
  eMatrix m;
  eVector z;
  double s;
  trans_matrix(&m,a);
  init_matrix(Q,a.rows,a.cols);
  init_matrix(R,a.rows,a.cols);
  init_vector(&z,a.rows);
  for(i = 0;i<a.rows;i++){
    Q->data[i] = m.data[i];
    for(j=0;j<i;j++){
      dot_vector(&s,Q->data[j],m.data[i]);
      mul_num_vector(&z,s,Q->data[j]);
      dif_vector(&Q->data[i],Q->data[i],z);
    }
    norm_vector(&R->data[i].data[i],Q->data[i]);
    mul_num_vector(&Q->data[i],1/R->data[i].data[i],Q->data[i]);
    for(j=0;j<i;j++){
      dot_vector(&R->data[j].data[i],Q->data[j],m.data[i]);
    }
  }
  trans_matrix(Q,*Q);
}

void det_matrix(double *ans,eMatrix m){
  eMatrix L,U;
  LU_fact_matrix(&L,&U,m);
  int i;
  *ans = 1;
  for(i=0;i<m.rows;i++){
    *ans = (*ans)*L.data[i].data[i];
  }
}

void str_2_vector(eVector *out,char* s,int length){
  init_vector(out,length);
  char *t;
  char dlims[3] = ", ";
  t = strtok(s,dlims);
  int i;
  for(i=0;i<length;i++){
    out->data[i] = atof(t);
    t = strtok(NULL,dlims);
  }
}

void str_2_matrix(eMatrix *out,char* s,int rows,int cols){
  init_matrix(out,rows,cols);
  char* t;
  char dlims[2] = ";";
  t = strsep(&s,dlims);
  int i,j;
  for(i=0;i<rows;i++){
    str_2_vector(&(out->data[i]),t,cols);
    t = strsep(&s,dlims);
  }
}

void load_vector(eVector *out,char* dir,int length){
  init_vector(out,length);
  FILE *f;
  f = fopen(dir,"r");
  char s[200];
  fgets(s,200,f);
  str_2_vector(out,s,length);
  fclose(f);
}
void load_matrix(eMatrix *out,char* dir,int rows,int cols){
  init_matrix(out,rows,cols);
  FILE *f;
  int i;
  f = fopen(dir,"r");
  char s[200];
  for(i=0;i<rows;i++){
    fgets(s,200,f);
    str_2_vector(&(out->data[i]),s,cols);
  }
  fclose(f);
}

void save_vector(char* dir,eVector v){
  int i;
  FILE* f;
  f = fopen(dir,"w");
  for(i=0;i<v.length;i++){
    fprintf(f,"%lf ",v.data[i]);
  }
  fprintf(f,"\n");
  fclose(f);
}

void save_matrix(char* dir,eMatrix m){
  int i,j;
  FILE* f;
  f = fopen(dir,"w");
  for(i=0;i<m.rows;i++){
    for(j=0;j<m.cols;j++){
      fprintf(f,"%lf ",m.data[i].data[j]);
    }
    fprintf(f,"\n");
  }
  fprintf(f,"\n");
  fclose(f);
}

void solve_linear_system(eVector* ans,eMatrix A,eVector b){
  eMatrix L,U;
  LU_fact_matrix(&L,&U,A);
  int i,j;
  double s;
  eVector z;
  init_vector(ans,b.length);
  init_vector(&z,b.length);
  for(i=0;i<b.length;i++){
    s = 0;
    for(j=0;j<i;j++){
      s = s + L.data[i].data[j]*z.data[j];
    }
    z.data[i] = (b.data[i] - s)/(L.data[i].data[j]);
  }
  for(i=b.length-1;i>=0;i--){
    s = 0;
    for(j=i+1;j<b.length;j++){
      s = s + U.data[i].data[j]*ans->data[j];
    }
    ans->data[i] = (z.data[i] - s);
  }
}

void inv_matrix(eMatrix* ans,eMatrix m){
  eMatrix L,U;
  int i,j,k;
  double s;
  eVector z;
  LU_fact_matrix(&L,&U,m);
  init_matrix(ans,m.rows,m.cols);
  init_vector(&z,m.rows);
  print_matrix(L);
  print_matrix(U);
  for(i=0;i<m.rows;i++){
    for(j=0;j<m.rows;j++){
      s = 0;
      for(k=0;k<j;k++){
        s = s + L.data[j].data[k]*z.data[k];
      }
      if(i==j){
        z.data[j] = (1 - s)/L.data[j].data[j];
      }
      else{
        z.data[j] = -s/L.data[j].data[j];
      }
    }
    for(j=m.rows-1;j>=0;j--){
      s = 0;
      for(k=j+1;k<m.cols;k++){
        s = s + U.data[j].data[k]*ans->data[k].data[i];
      }
      ans->data[j].data[i] = (z.data[j] - s);
    }
  }
}

void eigen_matrix(eMatrix* e_vectors,eVector* e_values,eMatrix m, int N){
  eMatrix Q,R;
  eMatrix A;
  int i;
  A = m;
  init_matrix(e_vectors,m.rows,m.cols);
  eye_matrix(e_vectors);
  init_vector(e_values,m.rows);
  for(i=0;i<N;i++){
    QR_fact_matrix(&Q,&R,A);
    dot_matrix(&A,R,Q);
    dot_matrix(e_vectors,*e_vectors,Q);
  }
  for(i=0;i<m.rows;i++)
    e_values->data[i] = A.data[i].data[i];
}

void average_data(double *ans,eVector v)
{
  *ans = 0;
  int i;
  for(i=0;i<v.length;i++){
    *ans = *ans + v.data[i];
  }
  *ans = (*ans)/v.length;
}

void std_dev_data(double *ans,eVector v){
  *ans = 0;
  int i;
  double avg;
  average_data(&avg,v);
  for(i=0;i<v.length;i++){
    *ans = *ans + (v.data[i]-avg)*(v.data[i]-avg);
  }
  *ans = sqrt((*ans)/v.length); 
}

void least_square_data(eVector *ans,eVector x,eVector y){
  eMatrix A;
  eVector b;
  init_matrix(&A,2,2);
  init_vector(&b,2);
  double sx=0,sy=0;
  int i;
  for(i=0;i<x.length;i++){
    sx = sx + x.data[i];
    sy = sy + y.data[i];
  }
  dot_vector(&(A.data[0].data[0]),x,x);
  dot_vector(&(b.data[0]),x,y);
  A.data[0].data[1] = sx;
  A.data[1].data[0] = sx;
  A.data[1].data[1] = x.length;
  b.data[1] = x.length;
  solve_linear_system(ans,A,b);
}

void gaussian_dist(double *ans,double avg,double std_dev,double x){
  *ans = (1/(sqrt(2*PI)*std_dev)) * exp(-(x-avg)*(x-avg)/(2*std_dev*std_dev));
}
