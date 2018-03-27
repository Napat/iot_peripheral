
สามารถดู api ของ esp8266 ได้ที่ [link](https://github.com/esp8266/Arduino/blob/master/doc/libraries.rst#esp-specific-apis)

ตัวอย่างการเรียกใช้งาน specific api เพื่อช่วยในการ debug โปรแกรม
```
    Serial.printf("Sketch use/free/total %d/%d/%d\n", ESP.getSketchSize(), ESP.getFreeSketchSpace(), ESP.getSketchSize()+ESP.getFreeSketchSpace());
    Serial.printf("Flash size %d Bytes\n", ESP.getFlashChipRealSize());
    Serial.printf("FreeHeap Free %d\n", ESP.getFreeHeap());
```

About FlashChip
-----
`ESP.getFlashChipId()` จะคืนค่าตัวเลขฐาน 16 ออกมาเช่น 0x1620c2  
วิธีการอ่านค่าให้อ่านจากหลังมาหน้า จะได้เป็น "c2 20 16": [Manufacturer ID] [Flash Type] [Density]  
ตัวอย่างเช่น
```
        ID EF 40 13: EF=WINBOND    ,Chip W25Q40     40=type   13=Density 512_kB,
        ID EF 40 16: EF=WINBOND    ,Chip W25Q32     40=type   16=Density 4_MB,  board: NodemcuV.2
        ID C8 40 13: C8=GIGADEVICE ,Chip GD25Q40    40=type   13=Density 512_kB,
        ID E0 40 16: E0=BergMicro  ,Chip ??         40=type   16=Density 4_MB,
        ID c2 20 16: C2=Macronix   ,Chip MX25L3233F 20=type   16=Density 4_MB,  board: esp12F devkit v3
```
