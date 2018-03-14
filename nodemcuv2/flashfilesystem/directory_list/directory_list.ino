#include <FS.h>   //Include File System Headers

String spiffs_tree(){
  String str = "";
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
      str += dir.fileName();
      str += " size: ";
      str += dir.fileSize();
      str += "\r\n";
  }
  //Serial.println("----------------");
  //Serial.println(str); 
  return str; 
}

void setup() {
  Serial.begin(115200);

  // mount fs
  SPIFFS.begin();

  Serial.println("----------------");
  String str = spiffs_tree();
  Serial.println(str); 
  
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
