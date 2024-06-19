#include <stdio.h>
#include <string.h>

#include <parson.h>

int
main (void)
{
  JSON_Value *schema    = json_parse_string ("{\"name\":\"\"}");
  JSON_Value *user_data = json_parse_file ("user_data.json");
  char        buf[256];
  const char *name = NULL;
  if (user_data == NULL || json_validate (schema, user_data) != JSONSuccess)
    {
      puts ("Enter your name:");
      scanf ("%s", buf);
      user_data = json_value_init_object ();
      json_object_set_string (json_object (user_data), "name", buf);
      json_serialize_to_file (user_data, "user_data.json");
    }
  name = json_object_get_string (json_object (user_data), "name");
  printf ("Hello, %s.", name);
  json_value_free (schema);
  json_value_free (user_data);
  return 0;
}
