void read_files()
{
  char *files;
  FILE *fp=popen("ls","r");
  files=(char *)malloc(sizeof(fp));
  while(fgets(files,sizeof(fp),fp)!= NULL)
  {
    if(!(strcmp(sort_queue[i],"a.out")), && !(strcmp(sort_queue[i],"program.c")))
    {
      sort_queue[i]=files;
    }
  }
  pclose(fp);
  free(files);
}
