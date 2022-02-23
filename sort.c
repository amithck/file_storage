void extension()
{
  char ext[15];
  int loc;
  int sizeq=sizeof(sort_queue)/sizeof(sort_queue[0]);
  for(int i=0;i<sizeq;i++)
  {
    loc=-1;
    for(int j=0;sort_queue[i][j]!='\n';j++)
    {
      if(sort_queue[i][j]=='.')
      {
        loc=j;
        break;
      }
    }
    if(loc>0)
    {
      strncpy(ext,sort_queue[i]+loc,10);
      sort(ext,i);
    }
  }
}

void sort(char ext[],int num)
{
  char move_command[100]="mv ";
  strcat(move_command,sort_queue[num]);
  int size_music=sizeof(music)/sizeof(music[0]);
  int size_exec=sizeof(exec)/sizeof(exec[0]);
  for(int i=0;i<size_music;i++)
  {
    if(!(strcmp(ext,music[i])))
    {
      strcat(move_command," music");
      system(move_command);
      return;
    }
  }
  for(int i=0;i<size_exec;i++)
  {
    if(!(strcmp(ext,exec[i])))
    {
      strcat(move_command," exec");
      system(move_command);
      return;
    }
  }
}
