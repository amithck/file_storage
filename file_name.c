#include<stdio.h>
#include<stdlib.h>
void main()
{
  char *test;
  FILE *fp=popen("ls","r");
  test=(char *)malloc(sizeof(fp));
  while(fgets(test,sizeof(fp),fp)!= NULL)
  {
    printf("%s",test);
    int loc=-1;
    for(int i=0;test[i]!='\n';i++)
    {
      if(test[i]=='.')
      {
        loc=i;
      }
    }
    printf("%d\n",loc);
  }
  pclose(fp);
  free(test);
}
