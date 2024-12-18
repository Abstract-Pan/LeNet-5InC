#include <stdio.h>
#include <stdlib.h>
#include "img_read.h"

char char_sets[9] =" ./*?#%@"; 
/*typedef struct FileSession{*/
    /*unsigned int number;*/
    /*unsigned int width;*/
    /*unsigned int height;*/
    /*unsigned int dimensions;*/
    /*FILE* fp;*/
    /*unsigned char* buffer;*/
    /*void(*session_deinit)(struct FileSession* this);*/
    /*int(*get_pic)(struct FileSession* this,int index);*/
    /*int(*get_label)(struct FileSession* this,int index);*/
    /*void(*print_pic)(struct FileSession* this);*/
/*}file_session;*/

void edian_convert(unsigned int* in)
{
    unsigned int buffer=0;
    buffer += (*in&(unsigned int)0x000000FF)<<24;
    buffer += (*in&(unsigned int)0x0000FF00)<<8;
    buffer += (*in&(unsigned int)0x00FF0000)>>8;
    buffer += (*in&(unsigned int)0xFF000000)>>24;
    *in = buffer;
}

void session_deinit(struct FileSession* this)
{
    fclose(this->fp);
    free(this->buffer);
    free(this);
}

int get_pic(struct FileSession* this,int index)
{
    if(index>=this->number)return -1;
    int offset = 4+4*this->dimensions+index*this->width*this->height;
    fseek(this->fp,offset,SEEK_SET);
    fread(this->buffer,1,this->height*this->width,this->fp);
    return 0;
}

int get_label(file_session* this,int index)
{
    if(index>=this->number)return -1;
    int offset = 4+4*this->dimensions+index;
    fseek(this->fp,offset,SEEK_SET);
    fread(this->buffer,1,1,this->fp);
    return 0;
}

void print_pic(struct FileSession* this)
{
    for(int i = 0;i < this->height;i++){
        for(int j = 0;j < this->width;j++){
            printf("%c ",char_sets[this->buffer[i*this->width+j]/32]);
        }
        printf("\n");
    }
}

file_session* session_init(const char* filename)
{
    file_session* this = malloc(sizeof(file_session));
    this->fp = fopen(filename,"rb");
    unsigned char temp_char;
    unsigned int temp_int;
    fseek(this->fp,3,SEEK_CUR);
    fread(&temp_char,1,1,this->fp);
    this->dimensions = (unsigned int)temp_char;
    fread(&temp_int,4,1,this->fp);
    edian_convert(&temp_int);
    this->number = temp_int;
    fread(&temp_int,4,1,this->fp);
    edian_convert(&temp_int);
    this->width = temp_int;
    fread(&temp_int,4,1,this->fp);
    edian_convert(&temp_int);
    this->height = temp_int;
    if(this->dimensions > 2)
        this->buffer = malloc(this->width*this->height*sizeof(unsigned char));
    else
        this->buffer = malloc(sizeof(unsigned char));
    this->session_deinit = &session_deinit;
    this->get_pic = &get_pic;
    this->print_pic = &print_pic;
    this->get_label = &get_label;
    return this;
}

/*int main()*/
/*{*/
 /*file_session* session = session_init("./t10k-labels-idx1-ubyte");*/
 /*session->get_label(session,1);*/
    /*printf("%u\n",*session->buffer);*/
 /*session->session_deinit(session);*/
 /*return 0;*/
/*}*/
