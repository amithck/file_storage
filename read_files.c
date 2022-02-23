void read_files()
{
  char *files;
  FILE *fp=popen("ls","r");
  files=(char *)malloc(sizeof(fp));
  while(fgets(files,sizeof(fp),fp)!= NULL)
  {
    if(!(strcmp(files,"a.out")), && !(strcmp(files,"program.c")))
    {
      sort_queue[i]=files;
    }
  }
  pclose(fp);
  free(files);
}
