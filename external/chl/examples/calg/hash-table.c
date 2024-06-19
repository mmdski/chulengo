#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libcalg.h>
#include <sds.h>

void
ch_sdsfree (void *ptr)
{
  sdsfree ((sds) ptr);
}

int
ch_sdseq (void *sds1, void *sds2)
{
  return sdscmp ((sds) sds1, (sds) sds2) == 0;
}

int
main (void)
{
  HashTable *str_hash_table_ptr = hash_table_new (&string_hash, &ch_sdseq);
  hash_table_register_free_functions (
      str_hash_table_ptr, &ch_sdsfree, &ch_sdsfree);

  // HashTableKey   key   = malloc (sizeof ("Hello"));
  // HashTableValue value = malloc (sizeof ("World"));
  // strcpy (key, "Hello");
  // strcpy (value, "World");
  sds key   = sdsnew ("Hello");
  sds value = sdsnew ("World");

  if (!hash_table_insert (str_hash_table_ptr, key, value))
    {
      fprintf (stderr, "Unable to insert key, value pair\n");
      return EXIT_FAILURE;
    }

  char *v = hash_table_lookup (str_hash_table_ptr, key);
  if (v != HASH_TABLE_NULL)
    printf ("v = %s\n", v);

  // if (!hash_table_remove (str_hash_table_ptr, "Hello"))
  //   printf ("Key not found\n");

  // free (value);

  hash_table_free (str_hash_table_ptr);

  return EXIT_SUCCESS;
}
