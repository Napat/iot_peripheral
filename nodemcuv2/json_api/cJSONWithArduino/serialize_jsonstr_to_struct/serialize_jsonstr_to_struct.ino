#include "cJSON.h"
#include <string.h>
#include <stdlib.h>

// Example: Create json string
// {
//     "name": "ASUS (\"Monitor\") MX34VQ",
//     "monitor": {
//         "type":           "IPS",
//         "width":         3440,
//         "height":        1440,
//         "interlace_vga":   false,
//         "frame rate":    100
//     }
// }

typedef struct monitor_s
{
    char type[30];
    int width;
    int height;
    bool interlace_vga;
    double framerate;
} monitor_t;

typedef struct buyitem_s
{
    char name[30];
    monitor_t monitor;
} buyitem_t;

static void serialize_jsonstr_to_cstruct()
{

    cJSON *root = NULL;
    cJSON *monitor = NULL;

    cJSON *name, *type, *width, *height, *interlace_vga, *framerate;
    buyitem_t btime;

    const char *jsonstr = "{"
                          "    \"name\": \"ASUS (\\\"Monitor\\\") MX34VQ\","
                          "    \"monitor\": {"
                          "        \"type\":          \"IPS\","
                          "        \"width\":          3440,"
                          "        \"height\":         1440,"
                          "        \"interlace_vga\":    false,"
                          "        \"frame rate\":     100"
                          "    }"
                          "}";

    Serial.printf("%s\n", jsonstr);

    root = cJSON_Parse(jsonstr);
    monitor = cJSON_GetObjectItemCaseSensitive(root, "monitor");

    name = cJSON_GetObjectItemCaseSensitive(root, "name");
    type = cJSON_GetObjectItemCaseSensitive(monitor, "type");
    width = cJSON_GetObjectItemCaseSensitive(monitor, "width");
    height = cJSON_GetObjectItemCaseSensitive(monitor, "height");
    interlace_vga = cJSON_GetObjectItemCaseSensitive(monitor, "interlace_vga");
    framerate = cJSON_GetObjectItemCaseSensitive(monitor, "frame rate");

    // name
    if (cJSON_IsString(name))
    {
        strncpy(btime.name, name->valuestring, 30);
        Serial.printf("name = %s\r\n", btime.name);
    }
    else
    {
        Serial.printf("Error!! not found at line %d\n", __LINE__);
    }

    // type
    if (cJSON_IsString(type))
    {
        strncpy(btime.monitor.type, type->valuestring, 30);
        Serial.printf("type = %s\r\n", btime.monitor.type);
    }
    else
    {
        Serial.printf("Error!! not found at line %d\n", __LINE__);
    }

    // width
    if (cJSON_IsNumber(width))
    {
        btime.monitor.width = width->valueint;
        Serial.printf("width = %d\r\n", btime.monitor.width);
    }
    else
    {
        Serial.printf("Error!! not found at line %d\n", __LINE__);
    }

    // height
    if (cJSON_IsNumber(height))
    {
        btime.monitor.height = height->valueint;
        Serial.printf("height = %d\r\n", btime.monitor.height);
    }
    else
    {
        Serial.printf("Error!! not found at line %d\n", __LINE__);
    }

    // interlace_vga
    if (cJSON_IsBool(interlace_vga))
    {
        btime.monitor.interlace_vga = (interlace_vga->type == cJSON_True) ? true : false;
        Serial.printf("interlace_vga = %s\r\n", btime.monitor.interlace_vga ? "true" : "false");
    }
    else
    {
        Serial.printf("Error!! not found at line %d\n", __LINE__);
    }

    // framerate
    if (cJSON_IsNumber(framerate))
    {
        btime.monitor.framerate = framerate->valuedouble;
        Serial.printf("framerate = %lf\r\n", btime.monitor.framerate);
    }
    else
    {
        Serial.printf("Error!! not found at line %d\n", __LINE__);
    }

    // free everything associate with root
    // The exception is cJSON_PrintPreallocated, where return to the caller that has full responsibility of the buffer. */
    cJSON_Delete(root);
    root = NULL;
}
void setup()
{
    Serial.begin(9600);
}

void loop()
{
    serialize_jsonstr_to_cstruct();
    Serial.printf("------------------------\n");
    delay(5000);
}
