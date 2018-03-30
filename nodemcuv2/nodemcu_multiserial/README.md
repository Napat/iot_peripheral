
Software serial สำหรับ nodemcu(esp8266) จำเป็นจะต้องติดตั้งเพิ่มเติม โดยให้เซิด libs ว่า `SoftwareSerial by Peter Lerup`
ก็จะสามารถใช้งานบน nodemcu ได้เหมือนกับบนบอด arduino ทั่วๆไป 
เพียงแต่มีข้อควรระวังในขั้นตอนการ developer บ้างเล็กน้อยหากต้อง dev ร่วมกันหลายๆบอด 

CAUTION
-----------------------

#### Issue
SoftwareSerial.h มีหลาย Libs ใช้ชื่อเดียวกัน
1.SoftwareSerial(formerly "NewSoftSerial")
2.SoftwareSerial(formerly "EspSoftwareSerial")

Compiler ของ arduino uno สับสนไฟล์ header SoftwareSerial.h เมื่อมีการติดตั้ง SoftwareSerial by Peter Lerup(for esp8266) 
เมื่อ compile arduino uno แล้วไปใช้ lib ผิดตัว

#### Solve 
- การใช้ software serial บน arduino hardware มาตรฐานเช่น UNO, MEGA อาจจะไปใช้ AltSoftSerial แทนไปก่อน
- ลบ SoftwareSerial by Peter Lerup(for esp8266) ออกไปก่อนหากจะใช้ SoftwareSerial สำหรับ arduino มาตรฐาน(NewSoftSerial)

#### Ref
- NewSoftSerial library by Mikal Hart: https://www.arduino.cc/en/Reference/SoftwareSerial
- EspSoftwareSerial by Peter Lerup https://github.com/plerup/espsoftwareserial
- AltSoftSerial for arduino https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
- https://microstor.blogspot.com/2017/03/software-serial-arduino-vs-nodemcu.html

#### Issue
1. EspSoftwareSerial ไม่เป็น full duplex อย่างสมบูรณ์แบบ อาจจะเกิด issue ในกรณีที่ใช้การรับส่งพร้อมๆกันในบัสที่รับ/ส่งข้อมูลพร้อมกันได้ 
ปัญหานี้ไม่น่าเป็นห่วงนักบนบัสที่โปรโตคอลรับ/ส่ง แบบ master/slave ที่สามารถควบคุม timeslot การรับส่งข้อมูลได้ 
แต่บนบัสที่รับส่งพร้อมๆกัน รวมถึงใช้หลายๆ serial port ในเวลาเดียวกันอาจเกิดปัญหาข้อมูลผิดพลาด 
ควรไปแก้ไขที่ hardware และการ design จะดีกว่า 

2. การใช้งาน EspSoftwareSerial ไม่สามารถใช้งานได้ทุก gpio นะ หากดูจาก [sourcecode](https://github.com/plerup/espsoftwareserial/blob/master/SoftwareSerial.cpp)  
จะเห็นว่า ขาที่ใช้ได้คือ GPIO 0,1,2,3,4,5,12,13,14,15 เท่านั้น ขาอื่นจะไม่สามารถใช้งานได้
```
# SoftwareSerial.cpp
...
// As the Arduino attachInterrupt has no parameter, lists of objects
// and callbacks corresponding to each possible GPIO pins have to be defined
SoftwareSerial *ObjList[MAX_PIN+1];

void ICACHE_RAM_ATTR sws_isr_0() { ObjList[0]->rxRead(); };
void ICACHE_RAM_ATTR sws_isr_1() { ObjList[1]->rxRead(); };
void ICACHE_RAM_ATTR sws_isr_2() { ObjList[2]->rxRead(); };
void ICACHE_RAM_ATTR sws_isr_3() { ObjList[3]->rxRead(); };
void ICACHE_RAM_ATTR sws_isr_4() { ObjList[4]->rxRead(); };
void ICACHE_RAM_ATTR sws_isr_5() { ObjList[5]->rxRead(); };
// Pin 6 to 11 can not be used
void ICACHE_RAM_ATTR sws_isr_12() { ObjList[12]->rxRead(); };
void ICACHE_RAM_ATTR sws_isr_13() { ObjList[13]->rxRead(); };
void ICACHE_RAM_ATTR sws_isr_14() { ObjList[14]->rxRead(); };
void ICACHE_RAM_ATTR sws_isr_15() { ObjList[15]->rxRead(); };

static void (*ISRList[MAX_PIN+1])() = {
      sws_isr_0,
      sws_isr_1,
      sws_isr_2,
      sws_isr_3,
      sws_isr_4,
      sws_isr_5,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      NULL,
      sws_isr_12,
      sws_isr_13,
      sws_isr_14,
      sws_isr_15
};
...
```

หากต้องการต่อพ่วง serial port มากกว่านี้อีก คงต้องหา hardware พวก serial port expander เช่น [Serial Port Expander ของ AtlasScientific](https://www.atlas-scientific.com/product_pages/components/port_expander.html) มาใช้งานแล้วแหละ 

