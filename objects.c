#include <stdlib.h>
#include <stdio.h>
#include "objects.h"

void kernel_deinit(Kernel* this)
{
    free(this->weight);
    free(this->delta_weight);
    free(this);
}

void map_deinit(Map* this)
{
    free(this->data);
    free(this->error);
    free(this);
}

void layer_deinit(Layer* this)
{
    for(int i = 0; i < this->map_count;i++){
        this->map[i]->map_deinit(this->map[i]);
    }
    for(int i = 0; i < this->kernel_count;i++){
        this->kernel[i]->kernel_deinit(this->kernel[i]);
    }
    free(this);
}

double rand_double()
{
    return 2000*(((double)rand()/RAND_MAX)-0.5);
}

void layer_kernel_rand_init(Layer* this)
{
    for(int i = 0;i < this->kernel_count;i++){
        for(int j = 0;j < this->kernel_width*this->kernel_height;j++){
            this->kernel[i]->weight[j] = rand_double();
        }
    }
}

void print_kernel(Layer* this)
{
    for(int i = 0;i < this->kernel_count;i++){
        printf("\nkernel:%d\n",i);
        for(int j = 0;j < this->kernel_height;j++){
            for(int k = 0;k < this->kernel_width;k++){
                printf("%.2f\t",this->kernel[i]->weight[j*this->kernel_width+k]);
            }
            printf("\n");
        }
    }
}

void print_map(Layer* this)
{

}

Kernel* kernel_init(int width,int height)
{
    Kernel* this = malloc(sizeof(Kernel));
    this->weight = malloc(width*height*sizeof(double));
    this->delta_weight = malloc(width*height*sizeof(double));
    this->kernel_deinit = &kernel_deinit;
    return this;
}

Map* map_init(int width,int height)
{
    Map* this = malloc(sizeof(Map));
    this->data = malloc(width*height*sizeof(double));
    this->error = malloc(width*height*sizeof(double));
    this->map_deinit = &map_deinit;
    return this;
}

Layer* layer_init(int map_height,int map_width,int map_count,int kernel_height,int kernel_width,int kernel_count)
{
    Layer* this = malloc(sizeof(Layer));
    this->map_height = map_height;
    this->map_width = map_width;
    this->map_count = map_count;
    this->kernel_height = kernel_height;
    this->kernel_width = kernel_width;
    this->kernel_count = kernel_count;
    this->map = malloc(map_count*sizeof(Map*));
    for(int i = 0;i < map_count;i++){
        this->map[i] = map_init(map_width,map_height);
    }
    this->kernel = malloc(kernel_count*sizeof(Kernel*));
    for(int i = 0;i < kernel_count;i++){
        this->kernel[i] = kernel_init(kernel_width,kernel_height);
    }
    this->layer_deinit = &layer_deinit;
    this->layer_kernel_rand_init = &layer_kernel_rand_init;
    this->print_kernel = &print_kernel;
    return this;
}


