#include <stdio.h>
#include <stdlib.h>

int BUF_SIZE = 10;
char *FN = "./test.txt";
  
int my_strlen(char *str) {
  printf("my_strlen.\n");
  const char* ptr = str;
  while(*ptr!=0x00) {
    ++ptr;
  }
  return ptr-str;
}

char * my_fread(char *buf, int n, FILE *file) {
  printf("my_fread.\n");
  char *ptr = buf;
  char c;
  int i = 0;
  while((c = getc(file))!=-1 && i<n-1){
    *ptr = c;
    ++ptr;
    ++i;
  }
  *ptr = 0x00;
  return buf;
}

int my_fgets(char **lineptr, int *n, FILE *file){
  printf("my_fgets.\n");
  int n_read = 0;
  char c;

  //3bi. find newline
  while((c = getc(file))!=0x0a){
    ++n_read;
  }
  fseek(file,0,0); // back to the beginning.
  
  //3bii. if LINEPTR is NULL function allocates memory for lineptr. *N is set to size of buffer.
  //NOTE: N cannot be NULL.
  if(!*lineptr) {
    *lineptr = malloc(n_read);
    *n = n_read;
  }
  else {
    //3biii. LINEPTR is allocated but too small
    if(n_read > *n) {
      *lineptr = realloc(*lineptr,n_read);
      *n = n_read;
    }
    //3biii. LINEPTR is allocated and the right size.
    // don't have to do anything for that assuming n is correct.

  }

  my_fread(*lineptr,n_read,file);
  return n_read;
}


//!! This is for my own testing, not part of the assignment !!
int my_tests() {

  printf("Tests.");
  
  //1. my_strlen test
  char hw[] = "Hello World!\0";
  printf("%s : %d\n\n", hw, my_strlen(hw));

  //2. my_fread test
  FILE *f = fopen(FN,"r");
  char buf[BUF_SIZE];
  my_fread(buf,BUF_SIZE,f);
  printf("buf: %s %d\n\n",buf,buf[9]);
  fseek(f,0,0); //go back to the beginning.

  //3 my_fgets test
  char *lineptr = NULL;
  int *n = malloc(sizeof(int));
  printf("Lineptr = NULL.\n");
  printf("chars read = %d\n", my_fgets(&lineptr,n,f));
  printf("lineptr: %s\n\n",lineptr);
  fseek(f,0,0); //go back to the beginning.

  
  lineptr = malloc(1);
  printf("Lineptr too small.\n");
  printf("chars read = %d\n", my_fgets(&lineptr,n,f));
  printf("lineptr: %s\n\n",lineptr);
  fseek(f,0,0); //go back to the beginning.

  
  lineptr = malloc(BUF_SIZE*10);
  printf("Lineptr big enough.\n");  
  printf("chars read = %d\n", my_fgets(&lineptr,n,f));
  printf("lineptr: %s\n\n",lineptr);
  fseek(f,0,0); //go back to the beginning.
  
  return 0;
}

int main(int argc, char **argv) {
  //stdout unbuffered for debugging.
  setvbuf(stdout,NULL,_IONBF,0);
  
  printf("Main.\n\n");

  FILE *f = fopen(FN,"r");
  char *lineptr = NULL;
  int *n = malloc(sizeof(int));
  my_fgets(&lineptr,n,f);

  return 0;
}
