#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<curses.h>
#include<ncurses.h>
#include<ctype.h>

#define MALLOC(p,s,t)\
if(!(p=(t)malloc(s))){\
printf("INSUFFICIENT MEMORY");\
exit(1);}

void read_files();
void extension();
void add_tree(char [],char []);
void sort(char [], int);
int search_engine(char []);
void create_base_tree();
void openfile(char[],char[]);
void search_display(WINDOW *,int);
void print_menu(WINDOW *,int);
void history(WINDOW *);
void printtree(WINDOW *,int);

char search_history[10][100];
char search_history2[10][100];
char search_found[100][100];
char search_found_loc[100][100];
int history_top=-1,search_num=0;

char sort_queue[1000][1000];
char music[][15]={".3gp",".aa",".aac",".aax",".act",".aiff",".alac",".amr",".ape",".au",".awb",".dss",".dvf",".flac",".gsm",".iklax",".ivs",".m4a",".m4b",".m4p",".mmf",".mp3",".mpc",".msv",".nmf",".ogg",".opus",".rm",".rf64",".sln",".tta",".voc",".vox",".wav",".wma",".wv",".webm",".8svx",".cda"};
char exec[][15]={".apk",".sk",".ahk",".jar",".run",".xbe",".cmd",".ipa",".exe",".oxe",".bin",".workflo",".8ck",".bin",".elf",".air",".xap",".bat",".scr",".app",".ac",".gadget",".appimage",".u3p",".widget",".com",".out",".pif",".xlm",".gpe",".73k",".cgi",".ex_",".script",".rxe",".scb",".paf.exe",".scar",".xex",".command",".tcp",".action",".nexe",".acc",".coffee",".epk",".ebs2",".celx",".hta",".isu",".rfu",".fxp",".ecf",".ps1",".89k",".xbap",".rbf",".plsc",".ex4",".fas",".actc",".icd",".vxp",".ws",".dld",".cof",".ear",".x86_64",".phar",".acr",".mlx",".m3g",".vpm",".jsx",".a6p",".wsh",".mcr",".vbs",".ex_",".zl9",".js",".server",".caction",".pex",".x86",".ba_",".rpj",".dek",".a7r",".iim",".jsf","plx",".vlx",".pwc",".pyc",".mel",".ms",".exe1",".mm",".exe",".applescript",".snap",".ex5",".paf",".mcr",".ebm",".prg",".frs",".rgs",".frs",".vbscript",".hms",".otm",".bms",".e_e",".uvm",".scpt",".spr",".mrc",".sct",".widget",".wiz",".csh",".ebs",".fpi",".mxe",".cyw",".pyo",".mrp",".gs",".osx",".azw2",".prg",".fky",".xqt",".fas",".actm",".kix",".app",".seed",".vexe",".kx",".arscript",".rox",".cel",".tms",".app",".n",".vbe",".tiapp",".ezs",".thm",".udf",".beam",".ms",".wpm",".dmc",".ls",".mac",".xys",".esh",".msl",".scptd",".shortcut",".prc",".mhm",".wpk",".s2a",".rfs",".sca",".cheat",".wsf",".jsc",".qit",".es",".lo",".rbx",".ds",".mem",".eham",".ebacmd",".upx",".mam",".dxl",".ksh",".ham",".btm",".ygh",".gpu",".sapk",".vdo",".mio",".ipf",".exopc",".sbs",".hpf",".ita",".asb",".mcr",".sts",".gm9",".prg",".qpx",".mamc",".atmx",".ezt",".ore",".smm",".ncl",".pvd"};
char doc[][15]={".doc",".docm",".docx",".dotm",".dotx",".htm",".html",".mht",".mhtml",".odt",".pdf",".rtf",".txt",".wps",".xml",".xps",".csv",".dbf",".dif",".ods",".prn",".slk",".xla",".xlam",".xls",".xlsb",".xlsm",".xlsx",".xlt",".xltm",".xltx",".xlw",".odp",".pot",".potm",".potx",".ppa",".ppam",".pps",".ppsm",".ppsx",".ppt",".pptm",".pptx",".thmx",".emf"};
char img[][15]={".jpg",".jpeg", ".jp2", ".exif", ".tiff", ".gif", ".bmp", ".png", ".ppm", ".pgm",".pbm", ".pnm", ".webp", ".hdr", ".heif", ".deep", ".drw", ".ecw", ".fits", ".flif",".ico", ".ilbm", ".img", ".jxl", ".jxr", ".nrrd", ".pam", ".pcx", ".pgf", ".plbm",".sgi", ".sid", ".tga", ".vicar", ".xisf", ".cd5", ".cpt", ".kra", ".mdp", ".pdn", ".psd",".psp", ".sai", ".xcf", ".cgm", ".rs-274x", ".svg", ".hpgl", ".hvif", ".naplps", ".odg",".qcc", ".amf", ".dgn", ".dwg", ".dxf", ".fit", ".hsf", ".iges", ".imml", ".ipa", ".jt", ".prc",".step", ".skp", ".stl", ".u3d", ".vrml", ".xaml", ".xgl", ".xvl", ".x3d", ".eps",".pict", ".wmf", ".swf", ".xaml", ".mpo", ".pns", ".jps"};
char vid[][15]={".webm", ".mkv", ".flv", ".vob", ".ogv", ".ogg", ".drc", ".gifv", ".mng", ".avi", ".mts",".m2ts", ".ts", ".mov", ".qt", ".wmv", ".yuv", ".rm", ".rmvb", ".viv", ".asf", ".amv", ".mp4",".m4p", ".m4v", ".mpg", ".mp2", ".mpeg", ".mpe", ".mpv", ".mpg", ".m2v", ".m4v", ".svi",".3gp", ".3gv",".v2", ".mxf", ".roq", ".nsv", ".flv", ".f4v", ".f4p", ".f4a", ".f4b"};


char op[4][15]={"Sort","Search","History","Exit"};


int sizeq=0;

struct file_tree
{
  char data[10000];
  struct file_tree *child;
  struct file_tree *sibling;
};
typedef struct file_tree *NODE;

NODE head;

int main()
{
  char search_ele[100];
  int flag=0;
  MALLOC(head,sizeof(struct file_tree),NODE);
  create_base_tree();
  read_files("initial");


  initscr();
  noecho();
  curs_set(0);

  int yMax,xMax,cen;
  cen=strlen("File Management System");
  cen=cen/2;
  getmaxyx(stdscr, yMax, xMax);
  WINDOW *win= newwin(yMax/2,xMax/2, yMax/4, xMax/4);

  cen=xMax/4-cen;
  box(win,0,0);
  keypad(win,true);
  print_menu(win,cen);
  int i=-1,max=4,x=0,z=-1;;

  int ch,ch1;
  while(ch=wgetch(win))
  {
begin:
    wclear(win);
    box(win,0,0);
    mvwprintw(win, 1, cen, "File Management System");
    if(ch==KEY_DOWN)
    {
      i=(i+1)%max;
      for(int j=0;j<max;j++)
      {
        if(i==j)
        {
          wattron(win,A_STANDOUT);
          mvwprintw(win, (j+2), 2, op[j]);
          wattroff(win,A_STANDOUT);
        }
        else
        {
          mvwprintw(win, (j+2), 2, op[j]);
        }
      }

    }
    else if(ch==KEY_UP)
    {
      i=(i-1);
      if(i<0)
        i=max-1;
      for(int j=0;j<max;j++)
      {
        if(i==j)
        {
          wattron(win,A_STANDOUT);
          mvwprintw(win, (j+2), 2, op[j]);
          wattroff(win,A_STANDOUT);
        }
        else
        {
          mvwprintw(win, (j+2), 2, op[j]);
        }
      }

    }
    else if(ch==10)
    {
      switch(i)
      {
        case 0:read_files("sort");
               extension();
               wclear(win);
               box(win,0, 0);
               mvwprintw(win, 1, 2, "Sorting Successful");
               printtree(win, yMax/2);
               print_menu(win,cen);
               i=-1;
               break;
        case 1:search_display(win,cen);
               i=-1;
               break;
        case 2:history(win);
               i=-1;
               print_menu(win,cen);
               break;
        case 3:goto exit;
               break;
        default:print_menu(win,cen);
      }
    }
    else 
    {
      mvwprintw(win, 1, cen, "File Management System");
      for(int j=0;j<max;j++)
      {
        if(i==j)
        {
          wattron(win,A_STANDOUT);
          mvwprintw(win, (j+2), 2, op[j]);
          wattroff(win,A_STANDOUT);
        }
        else
        {
          mvwprintw(win, (j+2), 2, op[j]);
        }
      }
    }
  }
exit:
  endwin();
}

void read_files(char action[])
{
  char files[1000];
  FILE *fp;
  if(!strcmp(action,"sort"))
  {
    fp=popen("ls","r");
    while(fgets(files,1000,fp)!= NULL)
    {
      if((strcmp(files,"a.out\n")) && (strcmp(files,"program.c\n")) && (strcmp(files,"Documents\n")) && (strcmp(files,"Executable\n")) && (strcmp(files,"Images\n")) && (strcmp(files,"Music\n")) && (strcmp(files,"Unclassified\n")) && (strcmp(files,"Videos\n")))
      {
        strcpy(sort_queue[sizeq],files);
        sizeq++;
      }
    }
    pclose(fp);
    return;
  }
  else
  {
    fp=popen("ls Music","r");
    while(fgets(files,1000,fp)!= NULL)
    {
      add_tree(files,"Music");
    }
    pclose(fp);
    fp=popen("ls Executable","r");
    while(fgets(files,1000,fp)!= NULL)
    {
      add_tree(files,"Executable");
    }
    pclose(fp);
    fp=popen("ls Images","r");
    while(fgets(files,1000,fp)!= NULL)
    {
      add_tree(files,"Images");
    }
    pclose(fp);
    fp=popen("ls Documents","r");
    while(fgets(files,1000,fp)!= NULL)
    {
      add_tree(files,"Documents");
    }
    pclose(fp);
    fp=popen("ls Videos","r");
    while(fgets(files,1000,fp)!= NULL)
    {
      add_tree(files,"Videos");
    }
    pclose(fp);
    fp=popen("ls Unclassified","r");
    while(fgets(files,1000,fp)!= NULL)
    {
      add_tree(files,"Unclassified");
    }
    pclose(fp);
  }
}

void extension()
{
  char ext[15];
  int loc;
  for(int i=0;i<sizeq;i++)
  {
    for(int j=0;j<strlen(sort_queue[i]);j++)
    {
      if(sort_queue[i][j]=='.')
      {
        loc=j;
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
  for(int i=0;i<strlen(ext);i++)
  {
    ext[i]=tolower(ext[i]);
  }
  char move_command[10000];
  char move_file[10000];
  strcpy(move_file,sort_queue[num]);
  strcpy(move_command,"mv ");
  int j=strlen(move_file);
  for(int i=0;i<j;i++)
  {
      if(move_file[i]==' ' || move_file[i]==')' || move_file[i]=='(')
      {
          int l=strlen(move_file);
          for(;l>=i;l--)
          {
            move_file[l+1]=move_file[l];
          }
          move_file[i]='\\';
          i++;
          j++;
      }
  }
  strcat(move_command,move_file);
  int s=strlen(ext);
  ext[s-1]='\0';
  int size_music=sizeof(music)/sizeof(music[0]);
  int size_exec=sizeof(exec)/sizeof(exec[0]);
  int size_doc=sizeof(doc)/sizeof(doc[0]);
  int size_img=sizeof(img)/sizeof(img[0]);
  int size_vid=sizeof(doc)/sizeof(vid[0]);
  s=strlen(move_command);
  move_command[s-1]='\0';
  
  for(int i=0;i<size_music;i++)
  {
    if(!(strcmp(ext,music[i])))
    {
      strcat(move_command," Music");
      system(move_command);
      add_tree(sort_queue[num],"Music");
      return;
    }
  }

  for(int i=0;i<size_exec;i++)
  {
    if(!(strcmp(ext,exec[i])))
    {
      strcat(move_command," Executable");
      system(move_command);
      add_tree(sort_queue[num],"Executable");
      return;
    }
  }

  for(int i=0;i<size_vid;i++)
  {
    if(!(strcmp(ext,vid[i])))
    {
      strcat(move_command," Videos");
      system(move_command);
      add_tree(sort_queue[num],"Videos");
      return;
    }
  }

  for(int i=0;i<size_img;i++)
  {
    if(!(strcmp(ext,img[i])))
    {
      strcat(move_command," Images");
      system(move_command);
      add_tree(sort_queue[num],"Images");
      return;
    }
  }

  for(int i=0;i<size_doc;i++)
  {
    if(!(strcmp(ext,doc[i])))
    {
      strcat(move_command," Documents");
      system(move_command);
      add_tree(sort_queue[num],"Documents");
      return;
    }
  }
  strcat(move_command," Unclassified");
  system(move_command);
  add_tree(sort_queue[num],"Unclassified");
}

void create_base_tree()
{
  NODE music_node,exec_node,doc_node,vid_node,img_node,un_node;

  MALLOC(music_node,sizeof(struct file_tree),NODE);
  MALLOC(exec_node,sizeof(struct file_tree),NODE);
  MALLOC(vid_node,sizeof(struct file_tree),NODE);
  MALLOC(img_node,sizeof(struct file_tree),NODE);
  MALLOC(doc_node,sizeof(struct file_tree),NODE);
  MALLOC(un_node,sizeof(struct file_tree),NODE);

  head->child=music_node;
  strcpy(music_node->data,"Music");

  music_node->sibling=exec_node;
  strcpy(exec_node->data,"Executable");

  exec_node->sibling=vid_node;
  strcpy(vid_node->data,"Videos");

  vid_node->sibling=img_node;
  strcpy(img_node->data,"Images");

  img_node->sibling=doc_node;
  strcpy(doc_node->data,"Documents");

  doc_node->sibling=un_node;
  strcpy(un_node->data,"Unclassified");
}

void add_tree(char name[],char type[])
{
  NODE cur;
  cur=head->child;
  while((strcmp(cur->data,type)))
  {
    cur=cur->sibling;
  }
  if(cur->child==NULL)
  {
    MALLOC(cur->child,sizeof(struct file_tree),NODE);
    strcpy(cur->child->data,name);;
  }
  else
  {
    cur=cur->child;
    while(cur->sibling!=NULL)
    {
      cur=cur->sibling;
    }
    MALLOC(cur->sibling,sizeof(struct file_tree),NODE);
    strcpy(cur->sibling->data,name);
  }
}

int search_engine(char search[])
{
  NODE cur,cur2;
  cur=head->child;
  int flag=0;
  int i,j,len;
start:
  i=0,j=0;
  if(cur->child!=NULL)
  {
    cur2=cur->child;
    while(true)
    {
      len=strlen(cur2->data);
      for(int x=0;x<len;x++)
      {
        if(search[j++]==cur2->data[i++])
        {
          if(search[j]=='\0')
          {
            int n;
            strcpy(search_found[search_num++],cur2->data);
            n=strlen(search_found[search_num-1]);
            search_found[search_num-1][n-1]='\0';
            strcpy(search_found_loc[search_num-1],cur->data);
            flag=1;
            break;
          }
        }
        else
        {
          j=0;
        }
      }
      if(cur2->sibling!=NULL)
      {
        cur2=cur2->sibling;
        i=0;
        j=0;
      }
      else 
      {
        break;
      } 
    }
  }
  if(cur->sibling!=NULL)
  {
    cur=cur->sibling;
    goto start;
  }
  else
  {
    return flag;
  }
}

void openfile(char open[],char loc[])
{
  int flag=0;
  char *ext;
  char open_cmd[1000];
  ext=strrchr(open,'.');
  int size_vid=sizeof(doc)/sizeof(vid[0]);
  for(int i=0;i<size_vid;i++)
  {
    if(!strcmp(ext,vid[i]) || !strcmp(ext,music[i]))
    {
      flag=1;
      strcpy(open_cmd,"vlc -q mymedia 2> /dev/null ");
      break;
    }
  }
  strcpy(search_history[++history_top],open);
  strcpy(search_history2[history_top],loc);
  if(flag==0)
  {
    strcpy(open_cmd,"open ");
  }
  char ele[10000];
  strcpy(ele,open);
  int j=strlen(ele);
  for(int i=0;i<j;i++)
  {
      if(ele[i]==' ' || ele[i]==')' || ele[i]=='(')
      {
          int l=strlen(ele);
          for(;l>=i;l--)
          {
            ele[l+1]=ele[l];
          }
          ele[i]='\\';
          i++;
          j++;
      }
  }
  strcat(open_cmd,loc);
  strcat(open_cmd,"/");
  strcat(open_cmd,ele);
  system(open_cmd);
  return;
}

void history(WINDOW *win)
{
  wclear(win);
  box(win,0,0);
  if(history_top>=0)
  {
    for(int i=history_top;i>=0;i--)
    {
      mvwprintw(win,i+1,2,"%s : %s",search_history[i],search_history2[i]);
    }
    wattron(win,A_STANDOUT);
    mvwprintw(win, history_top+2, 2, "Back");
    wattroff(win,A_STANDOUT);
  }
  else 
  {
    mvwprintw(win,1,2,"No history availible");
    wattron(win,A_STANDOUT);
    mvwprintw(win, 2, 2, "Back");
    wattroff(win,A_STANDOUT);
  }
  
  wgetch(win);
}

void search_display(WINDOW *win,int cen)
{
  int flag,x=0,ch,i=-1;
  char search_ele[100];
  echo();
  keypad(win,true);
  wclear(win);
  box(win,0,0);
  mvwprintw(win, 1, 2, "Enter search element:");
  mvwgetstr(win,2,2,search_ele);
  noecho();
  flag=search_engine(search_ele);
  wclear(win);
  box(win,0,0);
  if(flag==1)
  {
    mvwprintw(win, 1, 2, "ELEMENTS FOUND");
    for(x=0;x<search_num;x++)
    {
      mvwprintw(win, (x+2), 2, "%s : %s",search_found[x],search_found_loc[x]);
    }
    mvwprintw(win,x+2,2,"Cancel");
  }
  else 
  {
    mvwprintw(win, 1, 2, "NO ELEMENTS FOUND");
    mvwprintw(win,x+2,2,"Cancel");
  }
  strcpy(search_found[search_num],"Cancel");
  strcpy(search_found_loc[search_num],"");
  while(ch=wgetch(win))
  {
    if(ch==KEY_DOWN)
    {
      i=(i+1)%(search_num+2);
      if(i==0)
        i=1;
      for(int j=0;j<search_num+1;j++)
      {
        if(i==(j+1))
        {
          if(i==search_num+1)
          {
            wattron(win,A_STANDOUT);
            mvwprintw(win, (j+2), 2, "%s",search_found[j]);
            wattroff(win,A_STANDOUT);
          }
          else 
          {
            wattron(win,A_STANDOUT);
            mvwprintw(win, (j+2), 2, "%s : %s",search_found[j],search_found_loc[j]);
            wattroff(win,A_STANDOUT);
          }
        }
        else
        {
          if(j==search_num)
          {
            mvwprintw(win, (j+2), 2, "%s",search_found[j]);
          }
          else 
          {
            mvwprintw(win, (j+2), 2, "%s : %s",search_found[j],search_found_loc[j]);
          }
        }
      }

    }
    else if(ch==KEY_UP)
    {
      i=(i-1);
      if(i<1)
        i=search_num+1;
      for(int j=0;j<search_num+1;j++)
      {
        if(i==(j+1))
        {
          if(i==search_num+1)
          {
            wattron(win,A_STANDOUT);
            mvwprintw(win, (j+2), 2, "%s",search_found[j]);
            wattroff(win,A_STANDOUT);
          }
          else 
          {
            wattron(win,A_STANDOUT);
            mvwprintw(win, (j+2), 2, "%s : %s",search_found[j],search_found_loc[j]);
            wattroff(win,A_STANDOUT);
          }
        }
        else
        {
          if(j==search_num)
          {
            mvwprintw(win, (j+2), 2, "%s",search_found[j]);
          }
          else 
          {
            mvwprintw(win, (j+2), 2, "%s : %s",search_found[j],search_found_loc[j]);
          }
        }
      }

    }
    else if(ch==10)
    {
      if((i)>search_num)
      {
        goto end;
      }
      openfile(search_found[i-1],search_found_loc[i-1]);
    }
  }
end:
  print_menu(win,cen);
  search_num=0;
}

void print_menu(WINDOW *win,int cen)
{
  wclear(win);
  box(win,0,0);
  mvwprintw(win, 1, cen, "File Management System");
  mvwprintw(win, 2, 2, "Sort");
  mvwprintw(win, 3, 2, "Search");
  mvwprintw(win, 4, 2, "History");
  mvwprintw(win, 5, 2, "Exit");
}

void printtree(WINDOW *win,int yMax)
{
  NODE cur,cur2;
  int i=3,skip=0,len;
  char ele[10000];
  cur=head->child;
  while(true)
  {
    skip=0;
    wclear(win);
    box(win,0,0);
    mvwprintw(win, 1, 2,"Sorting Successful");
    mvwprintw(win,i++,2,"%s:-",cur->data);
    if(cur->child!=NULL)
    {
      cur2=cur->child;
      while(true)
      {
        if(i<yMax-1)
        {
          strcpy(ele,cur2->data);
          len=strlen(ele);
          ele[len]='\0';
          mvwprintw(win,i++,2,ele);
          if(cur2->sibling!=NULL)
          {
            cur2=cur2->sibling;
          }
          else 
          {
            i=3;
            wgetch(win);
            skip=1;
            goto next;
            break;
          }
        }
        else
        {
          i=3;
          wgetch(win);
          wclear(win);
          box(win,0,0);
          mvwprintw(win, 1, 2,"Sorting Successful");
          mvwprintw(win,i++,2,"%s:-",cur->data);
        }
      }
    }
    else 
    {
      next:
      if(cur->sibling!=NULL)
      {
        if(!skip)
        {
          wgetch(win);
        }
        i=3;
        cur=cur->sibling;
      }
      else 
      {
        break;
      }
    }
  }
}
