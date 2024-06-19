#ifndef CH_RAS_H_
#define CH_RAS_H_
#include <stdlib.h>

#define CH_RAS_LINE_MAX_CHARS 82
#define CH_ERR_MSG_CHARS 121

typedef struct
{
  size_t length;
  size_t pos;
  size_t line_no;
  char   contents[];
} ChFileContents;

typedef struct _ChRASGeomReach ChRASGeomReach;
struct _ChRASGeomReach
{
  char            river_name[17];
  char            reach_name[18];
  ChRASGeomReach *next;
};

typedef struct
{
  char            title[61];
  ChRASGeomReach *reach;
} ChRASGeom;

typedef enum
{
  kChRASNodeXS     = 1,
  kChRASNodeBridge = 3
} ChRASNodeType;

typedef struct
{
  ChRASNodeType type;
  char          rm[9];
  double        length_l;
  double        length_ch;
  double        length_r;
} ChRASNode;

void ch_cpy_err_msg (char *dst);

ChFileContents *ch_ras_file_read (FILE *f);
ChRASGeom      *ch_ras_geom_parse (ChFileContents *fc_ptr);
void            ch_ras_geom_free (ChRASGeom *geom);

#endif
