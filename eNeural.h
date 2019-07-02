#include "eMath.h"

typedef struct eLayer{
  eMatrix w;
  eMatrix i;
  eMatrix o;
  eMatrix e;
}eLayer;

typedef struct eANN{
  eLayer* net;
  int n_layers;
}eANN;
double sigmoid(double x);
void sigmoid_matrix(eMatrix* out,eMatrix x);
void create_layer(eLayer *l,int n_in_data,int n_out_data);
void forward_layer(eLayer* l,eMatrix in_data);
void backward_layer(eMatrix* err_prop,eLayer* l,eMatrix err_data);
void update_layer(eLayer* l,double alpha);
void create_net(eANN *n,int* str_net,int n_layers);
void forward_net(eANN *n,eMatrix in_data);
void backward_net(eANN *n,eMatrix err_data);
void update_net(eANN* n,double alpha);
void train_net(eANN* n,eMatrix in_data,eMatrix out_data,double alpha,int N);
