int ledState = LOW;

unsigned long previousMillis = 0;
const long interval = 1000;

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        if (ledState == LOW)
            ledState = HIGH; // Note that this switches the LED *off*
        else
            ledState = LOW; // Note that this switches the LED *on*
        digitalWrite(LED_BUILTIN, ledState);

        // debug
        Serial.printf("Sketch use/free/total %d/%d/%d\n", ESP.getSketchSize(), ESP.getFreeSketchSpace(), ESP.getSketchSize() + ESP.getFreeSketchSpace());
        Serial.printf("Flash size %d Bytes\n", ESP.getFlashChipRealSize());
        Serial.printf("FreeHeap Free %d\n", ESP.getFreeHeap());
        Serial.printf("Chip ID %x\n", ESP.getChipId());
        Serial.printf("FlashChip ID/sdkSize/Size %x/%d/%d\n", ESP.getFlashChipId(), ESP.getFlashChipSize(), ESP.getFlashChipRealSize());

        Serial.printf("+++++++++++++++++++++++\n");
        /*
        * https://github.com/esp8266/Arduino/blob/master/cores/esp8266/Esp.cpp
        *
        * ESP.getFlashChipId() return 0x1620c2, you need to reverse reading -> "c2 20 16": [Manufacturer ID] [Flash Type] [Density]
        *
        ID EF 40 13: EF=WINBOND    ,W25Q40     40=type   13=Density 512_kB=  4M-bit
        ID EF 40 16: EF=WINBOND    ,W25Q32     40=type   16=Density 4_MB=    32M-bit
        ID C8 40 13: C8=GIGADEVICE ,GD25Q40    40=type   13=Density 512_kB=  4M-bit
        ID E0 40 16: E0=BergMicro  ,           40=type   16=Density 4_MB=    32M-bit
        ID c2 20 16: C2=Macronix   ,MX25L3233F 20=type   16=Density 4_MB=    32M-bit, board: esp12F devkit v3
        */
    }
}