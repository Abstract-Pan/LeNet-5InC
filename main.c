#include "img_read.h"
#include "objects.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Layer* C1_Conv;
Layer* S2_Samp;
Layer* C3_Conv;
Layer* S4_Samp;
Layer* C5_Conn;
Layer* F6_FCon;
Layer* F7_FCon;
Layer* F8_Out;

void init_layers()
{
    C1_Conv = layer_init(32,32,1,5,5,6);
    C1_Conv->layer_kernel_rand_init(C1_Conv);
    S2_Samp = layer_init(28,28,6,2,2,6);
    S2_Samp->layer_kernel_rand_init(S2_Samp);
    C3_Conv = layer_init(14,14,6,5,5,16);
    C3_Conv->layer_kernel_rand_init(C3_Conv);
    S4_Samp = layer_init(10,10,16,2,2,16);
    S4_Samp->layer_kernel_rand_init(S4_Samp);
    C5_Conn = layer_init(5,5,16,5,5,120);
    C5_Conn->layer_kernel_rand_init(C5_Conn);
    F6_FCon = layer_init(1,1,120,1,1,84);
    F6_FCon->layer_kernel_rand_init(F6_FCon);
    F7_FCon = layer_init(1,1,84,1,1,10);
    F7_FCon->layer_kernel_rand_init(F7_FCon);
    F8_Out = layer_init(1,1,10,0,0,0);
}

void deinit_layers()
{
    C1_Conv->layer_deinit(C1_Conv);
    S2_Samp->layer_deinit(S2_Samp);
    C3_Conv->layer_deinit(C3_Conv);
    S4_Samp->layer_deinit(S4_Samp);
    C5_Conn->layer_deinit(C5_Conn);
    F6_FCon->layer_deinit(F6_FCon);
    F7_FCon->layer_deinit(F7_FCon);
    F8_Out ->layer_deinit(F8_Out );
}

void load_C1(file_session* session,int index)
{
    session->get_pic(session,index);    
    for(int i = 0;i < C1_Conv->map_height;i++){
        for(int j = 0;j < C1_Conv->map_width;j++){
            if(i < 2 || i >= 30 || j < 2 || j>= 30){
                C1_Conv->map[0]->data[i*C1_Conv->map_width+j]=0.0;
                continue;
            }
            double tmp = (double)session->buffer[(i-2)*session->width+(j-2)];
            C1_Conv->map[0]->data[i*C1_Conv->map_width+j]= tmp;
            /*printf("%.2f\t", C1_Conv->map[0]->data[i*C1_Conv->map_width+j]);*/
        }
        /*printf("\n");*/
    }
}

void C1_convolution_calculate(Layer* C1_input,Layer* C2_output)
{
    /*for(int i = 0;i < C1_input->kernel_count;i++){*/
        /*for(int j = 0;j < C1_input->*/
    
}

int main()
{
    srand(time(NULL));
    file_session* session = session_init("./train-images-idx3-ubyte");
    printf("%g\n",rand_double());
    init_layers();
    deinit_layers();
    return 0;
}
 
