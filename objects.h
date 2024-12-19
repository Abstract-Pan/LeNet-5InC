#include <stdlib.h>

typedef struct kernel{
    double* weight;
    double* delta_weight;
    void(*kernel_deinit)(struct kernel* this);
}Kernel;

typedef struct map{
    double* data;
    double* error;
    double bias;
    void(*map_deinit)(struct map* this);
}Map;

typedef struct layer{
    int map_width;
    int map_height;
    int map_count;
    Map** map;
    
    int kernel_width;
    int kernel_height;
    int kernel_count;
    Kernel** kernel;
    void(*layer_deinit)(struct layer* this);
    void(*layer_kernel_rand_init)(struct layer* this);
    void(*print_kernel)(struct layer* this);
}Layer;

void kernel_deinit(Kernel* this);

void map_deinit(Map* this);

void layer_deinit(Layer* this);

double rand_double();

void layer_kernel_rand_init(Layer* this);

Kernel* kernel_init(int width,int height);

Map* map_init(int width,int height);

Layer* layer_init(int map_height,int map_width,int map_count,int kernel_height,int kernel_width,int kernel_count);
