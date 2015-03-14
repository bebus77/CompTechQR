#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
  FILE* fp = NULL;

  /* Read the input. */
  fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    perror("Failed to open input.txt");
    exit(EXIT_FAILURE);
  }
    
  fclose(fp);

  return 0;
}