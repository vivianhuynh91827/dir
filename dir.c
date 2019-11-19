#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/dir.h>
#include <time.h>
#include "dir.h"

int print_files(DIR * d){
  int size = 0;
  printf("\nRegular files:\n");
  struct dirent * cur = readdir(d);
  while (cur){
    if (cur->d_type == 8){
      struct stat buff;
      int fd = stat(cur->d_name, &buff);
      size += buff.st_size;
      print_lsl(buff, 8);
      printf(" %ld %s\n", buff.st_size, cur->d_name);
    }
    cur = readdir(d);
  }
  return size;
}

void print_dir(DIR* d){
  struct dirent * cur = readdir(d);
  printf("Directories:\n");
  while(cur){
    if (cur->d_type == 4){
      struct stat buff;
      int fd = stat(cur->d_name, &buff);
      print_lsl(buff, 4);
      printf(" %ld %s\n", buff.st_size, cur->d_name);
    }
    cur = readdir(d);
  }
}
void print_lsl(struct stat info, int type){
  int perms = info.st_mode;
  perms = perms % 01000;
  // printf("%o\n", perms);
  int sep[3];
  sep[0] = perms / 0100;
  sep[1] = (perms % 0100) / 010;
  sep[2] = (perms % 010);
  //  printf("%d %d %d\n", sep[0], sep[1], sep[2] );
  if (type == 8){
    printf("-");
  }
  if (type == 4){
    printf("d");;
  }
  for (int i = 0; i<3; i ++){
    // printf("%o %s\n", sep[i], lsl);
    if(sep[i] - 4 >= 0){
      sep[i] -= 4;
      printf("r");
    }
    else{
      printf("-");;
    }
    // printf("%o %s\n", sep[i], lsl);
    if(sep[i] - 2 >= 0){
      sep[i] -= 2;
      printf("w");
    }
    else{
      printf("-");
    }
    // printf("%o %s\n", sep[i], lsl);
    if(sep[i] - 1 >= 0){
      sep[i] -= 1;
      printf("x");
    }
    else{
      printf("-");
    }
    // printf("%o %s\n", sep[i], lsl);
  }
}
int main(int argc, char * argv[]){
  printf("=====================================================================\n");
  char * name;
  if (argc == 1){
    printf("Please provide a directory:\n");
    char input[500];
    fgets(input, 500, stdin);
    input[strlen(input) - 1] = 0;
    name = input;
  }
  else {
    char input[500];
    strcpy(input, argv[1]);
    name = input;
  }
  DIR * d;
  d = opendir(name);
  if (!d){
    printf("Opening Directory errno: %d\n Error: %s \n",errno, strerror(errno));
    printf("===================================================================\n");
    return 0;
  }
  int size = 0;
  printf("\nStatistics for directory: %s\n", name);
  print_dir(d);
  closedir(d);
  d = opendir(name);
  if (!d){
    printf("Opening Directory errno: %d\n Error: %s \n",errno, strerror(errno));
    printf("===================================================================\n");
    return 0;
  }
  size = print_files(d);
  closedir(d);
  if(size >= 1073741824){printf("Total directory size: %d GB\n", size / 1073741824);}
  else if(size >= 1048576){printf("Total directory size: %d MB\n", size / 1048576);}
  else if(size >= 1024){printf("Total directory size: %d KB\n", size / 1024);}
  else{printf("Total directory size: %d B \n", size);}
  printf("=====================================================================\n");
  return 0;
}
