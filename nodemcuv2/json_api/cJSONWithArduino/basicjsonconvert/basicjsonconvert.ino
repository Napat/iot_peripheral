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

static void deserialize_jsonstr_to_cstruct(const char *jsonstr, buyitem_t *pbtime)
{

    cJSON *root = NULL;
    cJSON *monitor = NULL;

    cJSON *name, *type, *width, *height, *interlace_vga, *framerate;    

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
        strncpy(pbtime->name, name->valuestring, 30);
        Serial.printf("name = %s\r\n", pbtime->name);
    }
    else
    {
        Serial.printf("Error!! not found at line %d\n", __LINE__);
    }

    // type
    if (cJSON_IsString(type))
    {
        strncpy(pbtime->monitor.type, type->valuestring, 30);
        Serial.printf("type = %s\r\n", pbtime->monitor.type);
    }
    else
    {
        Serial.printf("Error!! not found at line %d\n", __LINE__);
    }

    // width
    if (cJSON_IsNumber(width))
    {
        pbtime->monitor.width = width->valueint;
        Serial.printf("width = %d\r\n", pbtime->monitor.width);
    }
    else
    {
        Serial.printf("Error!! not found at line %d\n", __LINE__);
    }

    // height
    if (cJSON_IsNumber(height))
    {
        pbtime->monitor.height = height->valueint;
        Serial.printf("height = %d\r\n", pbtime->monitor.height);
    }
    else
    {
        Serial.printf("Error!! not found at line %d\n", __LINE__);
    }

    // interlace_vga
    if (cJSON_IsBool(interlace_vga))
    {
        pbtime->monitor.interlace_vga = (interlace_vga->type == cJSON_True) ? true : false;
        Serial.printf("interlace_vga = %s\r\n", pbtime->monitor.interlace_vga ? "true" : "false");
    }
    else
    {
        Serial.printf("Error!! not found at line %d\n", __LINE__);
    }

    // framerate
    if (cJSON_IsNumber(framerate))
    {
        pbtime->monitor.framerate = framerate->valuedouble;
        Serial.printf("framerate = %lf\r\n", pbtime->monitor.framerate);
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

void serialize_cstruct_to_jsonstr(buyitem_t *btime, char **pjson_str)
{
  cJSON *root = NULL;
  cJSON *fmt = NULL;
  
  root = cJSON_CreateObject();
  cJSON_AddItemToObject(root, "name", cJSON_CreateString(btime->name));
  cJSON_AddItemToObject(root, "monitor", fmt = cJSON_CreateObject());
  cJSON_AddStringToObject(fmt, "type", btime->monitor.type);
  cJSON_AddNumberToObject(fmt, "width", btime->monitor.width);
  cJSON_AddNumberToObject(fmt, "height", btime->monitor.height);
  if(btime->monitor.interlace_vga)
  {
    cJSON_AddTrueToObject (fmt, "interlace_vga");
  }else
  {
    cJSON_AddFalseToObject (fmt, "interlace_vga");
  }
  cJSON_AddNumberToObject(fmt, "frame rate", btime->monitor.framerate);

  *pjson_str = cJSON_Print(root);   // auto allocate memory ** need to call cJSON_free() to free memory** 

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
    buyitem_t btime;
    char *json_str = NULL;

    //memset(json_str, 0, sizeof(json_str) / sizeof(json_str[0]));
    
    Serial.printf("\n# Deserialize json string to c struct-----------------------\n");
    deserialize_jsonstr_to_cstruct(jsonstr, &btime);
    
    Serial.printf("\n# Srialize c struct to json string-----------------------\n");
    serialize_cstruct_to_jsonstr(&btime, &json_str);
    Serial.printf("%s\n", json_str);
    
    Serial.printf("\n## Minify json string\n");
    cJSON_Minify(json_str);
    Serial.printf("%s\n", json_str);

    cJSON_free(json_str);
    jsonstr = NULL;
    
    delay(5000);
}
