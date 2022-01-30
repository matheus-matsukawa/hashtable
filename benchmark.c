#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

char *str_gen()
{
  int str_length = 3 + (rand() % 8);

  char *str = malloc(sizeof(char) * str_length);

  for (int i = 0; i < str_length; i++)
  {
    str[i] = 'a' + (rand() % 26);
  }

  return str;
}

int runTest(char *keys[TABLE_SIZE], ht_t *ht, unsigned int threshold, unsigned int start)
{
  for (int i = start; i < threshold; i++)
  {
    keys[i] = str_gen();
    char *value = str_gen();
    ht_set(ht, keys[i], value);
    free(value);
  }
  unsigned int indexes[50];
  for (int i = 0; i < 50; i++)
  {
    indexes[i] = rand() % threshold;
  }

  // Cronometra o tempo de acesso de 50 chaves aleatórias
  struct timeval begin, end;
  int result = 0;
  gettimeofday(&begin, NULL);
  for (int i = 0; i < 50; i++)
  {
    char *test = ht_get(ht, keys[indexes[i]]);
  }
  gettimeofday(&end, NULL);

  result = end.tv_usec - begin.tv_usec;
  return result;
}

int main()
{
  ht_t *ht = ht_create();
  FILE *output = NULL;
  char writeToFile;
  printf("Deseja gerar um CSV com os resultados compatível com o google sheets?\n");
  printf("OBS: um arquivo benchmark.csv sera gerado, caso exista, sobreescrito: (S/n)\n");
  scanf(" %c", &writeToFile);

  if (writeToFile != 'n' && writeToFile != 'N')
  {
    output = fopen("./benchmark.csv", "w+");
    fputs("Ocupacao,Tempo(usec)\n", output);
  }

  char *keys[TABLE_SIZE];
  int results[10];
  float percent = 0.05;
  printf("Tempo de acesso:\n");

  for (int i = 0; i < 10; i++)
  {
    unsigned int threshold = TABLE_SIZE * percent;
    long int start = (percent - 0.1) > 0 ? (percent - 0.1) * TABLE_SIZE : 0;
    results[i] = runTest(keys, ht, threshold, start);

    printf("%0.2f da capacidade máxima da tabela: %ld microsegundos\n", percent, results[i]);
    if (output)
    {
      char printToFile[100];
      sprintf(printToFile, "%0.2f,%d\n", percent, results[i]);
      fputs(printToFile, output);
    }
    percent += 0.1;
  }
  if (output)
  {
    fclose(output);
    printf("\nCSV gerado com sucesso\n");
  }

  return 0;
}