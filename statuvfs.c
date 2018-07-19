#include <arpa/inet.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disk.h"

int main(int argc, char *argv[]) {
  //   printf("HI\n");
  superblock_entry_t sb;
  int i;
  char *imagename = NULL;
  FILE *f;
  int *fat_data;

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--image") == 0 && i + 1 < argc) {
      imagename = argv[i + 1];
      i++;
    }
  }

  if (imagename == NULL) {
    fprintf(stderr, "usage: statuvfs --image <imagename>\n");
    exit(1);
  }

  if ((f = fopen(imagename, "rb")) != NULL) {
    fread(&sb, sizeof(sb), 1, f);
    fclose(f);
  }

  // char str[80] = "This is - www.tutorialspoint.com - website";
  const char s[2] = "/";
  char *token;
  char *name;

  /* get the first token */
  token = strtok(imagename, s);

  /* walk through other tokens */
  while (token != NULL) {
    //   printf(" %s\n", token);
    name = token;
    token = strtok(NULL, s);
  }

  printf("%s (%s)\n", sb.magic, name);
  printf("-------------------------------------------------\n");
  printf("Bsz\tBcnt\tFATst\tFATcnt\tDIRst\tDIRcnt\n");
  printf("%hu\t%d\t%d\t%d\t%d\t%d\t\n", ntohs(sb.block_size),
         ntohl(sb.num_blocks), ntohl(sb.fat_start), ntohl(sb.fat_blocks),
         ntohl(sb.dir_start), ntohl(sb.dir_blocks));

  return 0;
}
