void read_files()
{
  char *elements;
  FILE *fp=popen("ls","r");
  elements=(char *)malloc(sizeof(fp));
  while(fgets(elements,sizeof(fp),fp)!= NULL)
  {
    printf("%s",elements);
    int loc=-1;
    for(int i=0;elements[i]!='\n';i++)
    {
      if(elements[i]=='.')
      {
        loc=i;
      }
    }
    printf("%d\n",loc);
  }
  pclose(fp);
  free(elements);
}
