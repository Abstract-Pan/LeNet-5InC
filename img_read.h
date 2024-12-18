#include <stdio.h>
#include <stdlib.h>

extern char char_sets[9];

typedef struct FileSession{
    unsigned int number;
    unsigned int width;
    unsigned int height;
    unsigned int dimensions;
    FILE* fp;
    unsigned char* buffer;
    void(*session_deinit)(struct FileSession* this);
    int(*get_pic)(struct FileSession* this,int index);
    int(*get_label)(struct FileSession* this,int index);
    void(*print_pic)(struct FileSession* this);
}file_session;

void edian_convert(unsigned int* in);

void session_deinit(struct FileSession* this);

int get_pic(struct FileSession* this,int index);

int get_label(file_session* this,int index);

void print_pic(struct FileSession* this);

file_session* session_init(const char* filename);
