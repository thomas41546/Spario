#include "debug.h"
void Dappendfile(unsigned char *buffer,unsigned long int buflen, const char *filename){
     FILE *fh;
     fh =  fopen(filename, "ab");
     if(fh == NULL){return;}//error
     fseek(fh, 0, SEEK_SET);
     fwrite(buffer, buflen, 1, fh); 
     fclose(fh); 
}

void Debug(const char *error){
  char output [80+strlen((const char*)error)+2];
  time_t rawtime;
  struct tm * timeinfo;
  char timebuffer[80];
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  strftime (timebuffer,80,"%c: ",timeinfo);
  sprintf(output,"%s%s\r\n",timebuffer,error);
  Dappendfile((unsigned char *)output,strlen((const char*)output), "debug.log");
}
void DebugMsg(const char *error){
  Debug(error);
  //MessageBox (0, error, "DEBUG", MB_ICONHAND);
}
