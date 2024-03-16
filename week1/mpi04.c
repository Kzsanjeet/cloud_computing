#include <stdio.h>

int main(int argc, char **argv)
{
  int i, c;
  int nstart=1, nfinish=10000; 
  printf("%s : Prime numbers between %d and %d are :\n", 
         argv[0], nstart, nfinish);
  for(i=nstart; i<=nfinish; i++)
  { 
    for(c=2; c<=i-1; c++)
    {
      if ( i%c==0 )
        break;
    }
    if ( c==i ) 
      printf("%s : %d\n",argv[0], i);
  }
  return 0;
}
