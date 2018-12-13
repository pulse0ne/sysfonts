#include <stdbool.h>

typedef struct _FontDescription {
    char *name;
    char *path;
    char *family;
    char *style;
    int weight;
    int width;
    bool italic;
    bool monospace;
} FontDescription;

typedef struct _FontList {
    int length;
    FontDescription **fonts;
} FontList;