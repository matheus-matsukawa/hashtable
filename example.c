#include "hashtable.h"

int main()
{
  ht_t *ht = ht_create();
  printf("\nAdiciona:\n");
  ht_set(ht, "foo", "bar");
  ht_set(ht, "foo1", "bar1");
  ht_set(ht, "foo2", "bar2");
  ht_dump(ht);

  printf("\nDeleta:\n");
  ht_del(ht, "foo1");
  ht_dump(ht);

  printf("\nBusca:\n");
  char *search = ht_get(ht, "foo");
  printf("%s\n\n", search);

  return 0;
}