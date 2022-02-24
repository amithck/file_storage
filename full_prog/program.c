#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define MALLOC(p,s,t)\
if(!(p=(t)malloc(s))){\
printf("INSUFFICIENT MEMORY");\
exit(1);}

char sort_queue[1000][1000];
char music[][15]={".3gp",".aa",".aac",".aax",".act",".aiff",".alac",".amr",".ape",".au",".awb",".dss",".dvf",".flac",".gsm",".iklax",".ivs",".m4a",".m4b",".m4p",".mmf",".mp3",".mpc",".msv",".nmf",".ogg",".opus",".rm",".rf64",".sln",".tta",".voc",".vox",".wav",".wma",".wv",".webm",".8svx",".cda"};
char exec[][15]={".apk",".sk",".ahk",".jar",".run",".xbe",".cmd",".ipa",".exe",".oxe",".bin",".workflo",".8ck",".bin",".elf",".air",".xap",".bat",".scr",".app",".ac",".gadget",".appimage",".u3p",".widget",".com",".out",".pif",".xlm",".gpe",".73k",".cgi",".ex_",".script",".rxe",".scb",".paf.exe",".scar",".xex",".command",".tcp",".action",".nexe",".acc",".coffee",".epk",".ebs2",".celx",".hta",".isu",".rfu",".fxp",".ecf",".ps1",".89k",".xbap",".rbf",".plsc",".ex4",".fas",".actc",".icd",".vxp",".ws",".dld",".cof",".ear",".x86_64",".phar",".acr",".mlx",".m3g",".vpm",".jsx",".a6p",".wsh",".mcr",".vbs",".ex_",".zl9",".js",".server",".caction",".pex",".x86",".ba_",".rpj",".dek",".a7r",".iim",".jsf","plx",".vlx",".pwc",".pyc",".mel",".ms",".exe1",".mm",".exe",".applescript",".snap",".ex5",".paf",".mcr",".ebm",".prg",".frs",".rgs",".frs",".vbscript",".hms",".otm",".bms",".e_e",".uvm",".scpt",".spr",".mrc",".sct",".widget",".wiz",".csh",".ebs",".fpi",".mxe",".cyw",".pyo",".mrp",".gs",".osx",".azw2",".prg",".fky",".xqt",".fas",".actm",".kix",".app",".seed",".vexe",".kx",".arscript",".rox",".cel",".tms",".app",".n",".vbe",".tiapp",".ezs",".thm",".udf",".beam",".ms",".wpm",".dmc",".ls",".mac",".xys",".esh",".msl",".scptd",".shortcut",".prc",".mhm",".wpk",".s2a",".rfs",".sca",".cheat",".wsf",".jsc",".qit",".es",".lo",".rbx",".ds",".mem",".eham",".ebacmd",".upx",".mam",".dxl",".ksh",".ham",".btm",".ygh",".gpu",".sapk",".vdo",".mio",".ipf",".exopc",".sbs",".hpf",".ita",".asb",".mcr",".sts",".gm9",".prg",".qpx",".mamc",".atmx",".ezt",".ore",".smm",".ncl",".pvd"};
char doc[][15]={".doc",".docm",".docx",".dotm",".dotx",".htm",".html",".mht",".mhtml",".odt",".pdf",".rtf",".txt",".wps",".xml",".xps",".csv",".dbf",".dif",".ods",".prn",".slk",".xla",".xlam",".xls",".xlsb",".xlsm",".xlsx",".xlt",".xltm",".xltx",".xlw",".odp",".pot",".potm",".potx",".ppa",".ppam",".pps",".ppsm",".ppsx",".ppt",".pptm",".pptx",".thmx",".emf"};


int sizeq=0;

struct file_tree
{
  char data[1000];
  struct file_tree *child;
  struct file_tree *sibling;
};
typedef struct file_tree *NODE;

NODE head;

void main()
{
  MALLOC(head,sizeof(struct file_tree),NODE);
}

void read_files()
{
  char *files;
  FILE *fp=popen("ls","r");
  files=(char *)malloc(sizeof(fp));
  while(fgets(files,sizeof(fp),fp)!= NULL)
  {
    if(!(strcmp(files,"a.out")), && !(strcmp(files,"program.c")))
    {
      sort_queue[sizeq]=files;
      sizeq++;
    }
  }
  pclose(fp);
  free(files);
}

void extension()
{
  char ext[15];
  int loc;
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
  int size_doc=sizeof(doc)/sizeof(doc[0]);
  int size_img=sizeof(img)/sizeof(img[0]);
  int size_vid=sizeof(doc)/sizeof(vid[0]);
  
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
  music_node->data="Music";

  music_node->sibling=exec_node;
  exec_node->data="Executable";

  exec_node->sibling=vid_node;
  vid_node->data="Videos";

  vid_node->sibling=img_node;
  img_node->data="Images";

  img_node->sibling=doc_node;
  doc_node->data="Documents";

  doc_node->sibling=un_node;
  un_node->data="Unclassified";
}

void add_tree(char name[],char type[])
{
  NODE cur;
  cur=head->child;
  while(!(strcmp(cur->data,type)))
  {
    cur=cur->sibling;
  }
  cur=cur->child;
  while(cur!=NULL)
  {
    cur=cur->sibling;
  }
  MALLOC(cur,sizeof(struct file_tree),NODE);
  strcpy(cur->data,name);
}
