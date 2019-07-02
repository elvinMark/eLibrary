#include "eNeural.h"

double sigmoid(double x){
  return 1.0/(1 + exp(-x));
}
void sigmoid_matrix(eMatrix* out,eMatrix x){
  int i,j;
  init_matrix(out,x.rows,x.cols);
  for(i=0;i<x.rows;i++){
    for(j=0;j<x.cols;j++){
      out->data[i].data[j] = sigmoid(x.data[i].data[j]);
    }
  }
}
void create_layer(eLayer *l,int n_in_data,int n_out_data){
  eMatrix w;
  init_matrix(&w,n_in_data,n_out_data);
  random_matrix(&w);
  l->w = w;
}
void forward_layer(eLayer *l,eMatrix in_data){
  l->i = in_data;
  eMatrix aux;
  dot_matrix(&aux,in_data,l->w);
  sigmoid_matrix(&(l->o),aux);
}
void backward_layer(eMatrix* err_prop,eLayer* l,eMatrix err_data){
  eMatrix aux;
  init_matrix(&aux,l->o.rows,l->o.cols);
  ones_matrix(&aux);
  dif_matrix(&aux,aux,l->o);
  mul_matrix(&aux,aux,l->o);
  mul_matrix(&aux,aux,err_data);
  l->e = aux;
  trans_matrix(err_prop,l->w);
  dot_matrix(err_prop,l->e,*err_prop);
}
void update_layer(eLayer* l,double alpha){
  eMatrix aux;
  trans_matrix(&aux,l->i);
  dot_matrix(&aux,aux,l->e);
  mul_num_matrix(&aux,alpha,aux);
  dif_matrix(&(l->w),l->w,aux);
}
void create_net(eANN* n,int* str_net,int n_layers){
  n->n_layers = n_layers;
  n->net = (eLayer*)malloc(sizeof(eLayer)*n_layers);
  int i;
  for(i=0;i<n_layers;i++){
    create_layer(&(n->net[i]),str_net[i],str_net[i+1]);
  }
}
void forward_net(eANN *n,eMatrix in_data){
  int i;
  eMatrix aux;
  aux = in_data;
  for(i=0;i<n->n_layers;i++){
    forward_layer(&(n->net[i]),aux);
    aux = n->net[i].o;
  }
}
void backward_net(eANN *n,eMatrix err_data){
  int i;
  eMatrix aux;
  aux = err_data;
  for(i=n->n_layers-1;i>=0;i--){
    backward_layer(&aux,&(n->net[i]),aux);
  }
}
void update_net(eANN* n,double alpha){
  int i;
  for(i=0;i<n->n_layers;i++){
    update_layer(&(n->net[i]),alpha);
  }
}
void train_net(eANN* n,eMatrix in_data,eMatrix out_data,double alpha,int N){
  int i;
  eMatrix aux;
  for(i=0;i<N;i++){
    forward_net(n,in_data);
    aux = n->net[n->n_layers-1].o;
    dif_matrix(&aux,aux,out_data);
    backward_net(n,aux);
    update_net(n,alpha);
  }
}

