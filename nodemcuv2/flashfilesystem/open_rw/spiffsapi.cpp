
#include "spiffsapi.h"

void spiffsapi_init(void)
{
    // mount fs
    SPIFFS.begin();
}

String spiffsapi_tree(void)
{
    String str = "";
    Dir dir = SPIFFS.openDir("/");
    while (dir.next())
    {
        str += dir.fileName();
        str += " size: ";
        str += dir.fileSize();
        str += "\r\n";
    }
    //Serial.println("----------------");
    //Serial.println(str);
    return str;
}

bool spiffsapi_isfileexits(char* fpath)
{
    return SPIFFS.exists(fpath);
}
