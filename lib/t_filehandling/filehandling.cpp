#include "filehandling.h"

void readfile(unsigned char **buffer,unsigned long int *filelength, const char *filename){
     FILE *fh;
     fh =  fopen(filename, "rb");
     if(fh == NULL){return;}//error

     fseek(fh, 0, SEEK_END);
     *filelength = ftell(fh);
     fseek(fh, 0, SEEK_SET);
     
     *buffer = (unsigned char *) malloc(*filelength+1); //endline
     fread(*buffer, *filelength,1, fh); 
     *(*buffer+*filelength) = 0; //end
     fclose(fh); 
}


void writefile(char *buffer,unsigned long int buflen, const char *filename){

     FILE *fh;
     fh =  fopen(filename, "wb");
     if(fh == NULL){return;}//error
     fseek(fh, 0, SEEK_SET);
     fwrite(buffer, buflen, 1, fh); 
     fclose(fh); 
}
