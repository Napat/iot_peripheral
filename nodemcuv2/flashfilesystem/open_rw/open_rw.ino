
#include "spiffsapi.h"

#define FILE_AUTH   "/dat/auth.conf"
File fd_auth;
bool auth_exist = false;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  spiffsapi_init();

  auth_exist = spiffsapi_isfileexits(FILE_AUTH);

  if (!auth_exist)
  {
    Serial.println(FILE_AUTH);
    Serial.println("File doesn't exist yet. Creating it");

    // Open for writing
    File fd_auth = SPIFFS.open(FILE_AUTH, "w");
    if (!fd_auth) 
    {
      Serial.println("File creation failed");
    }
    
    // Set default auth values, two lines in key/value style with end-of-line characters,.
    fd_auth.println("ssid=wifi_Floor_6_2.4GHz");
    fd_auth.println("password=1234567890");  
    fd_auth.close();
  }

  Serial.println("+++++++++++++++++++++++++++");
  String str = spiffsapi_tree();
  Serial.println(str);

  // Open for reading
  fd_auth = SPIFFS.open(FILE_AUTH, "r"); 
}

void loop() 
{
  static uint8_t cnt = 0;

  Serial.print(cnt);
  Serial.println("--------------------------");

  if( (cnt != 3) && (cnt < 5) )
  {
    // reset file pointer
    fd_auth.seek(0, SeekSet);
    
    // Iterate the file line by line
    while (fd_auth.available())
    {
      String line;      
      line = fd_auth.readStringUntil('\n');
      Serial.println(line);
    }
  }else if (cnt == 3)
  {
    SPIFFS.remove(FILE_AUTH);
  }else if (cnt == 5)
  {
    Serial.println("close fd.");
    fd_auth.close();
  }else{
    Serial.print(".");
  }

  cnt++;
  delay(1000);
}
