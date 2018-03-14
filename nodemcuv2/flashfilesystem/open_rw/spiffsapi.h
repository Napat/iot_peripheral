
#ifndef __SPIFFAPI_H__
#define __SPIFFAPI_H__

#include <FS.h> //Include File System Headers

void spiffsapi_init(void);
String spiffsapi_tree(void);
bool spiffsapi_isfileexits(char *fpath);

#endif /* __SPIFFAPI_H__*/
