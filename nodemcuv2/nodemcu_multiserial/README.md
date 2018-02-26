
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
- การใช้ software serial บอด arduino มาตรฐานเช่น UNO อาจจะไปใช้ AltSoftSerial แทนไปก่อน
- ลบ SoftwareSerial by Peter Lerup(for esp8266) ออกไปก่อนหากจะใช้ SoftwareSerial สำหรับ arduino มาตรฐาน(NewSoftSerial)

#### Ref
- NewSoftSerial library by Mikal Hart: https://www.arduino.cc/en/Reference/SoftwareSerial
- EspSoftwareSerial by Peter Lerup https://github.com/plerup/espsoftwareserial
- AltSoftSerial for arduino https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
- https://microstor.blogspot.com/2017/03/software-serial-arduino-vs-nodemcu.html

#### Issue
ไม่เป็น full duplex อย่างสมบูรณ์แบบ อาจจะเกิด issue ในกรณีที่ใช้การรับส่งพร้อมๆกันในบัสที่รับ/ส่งข้อมูลพร้อมกันได้ 
ปัญหานี้ไม่น่าเป็นห่วงนักบนบัสที่โปรโตคอลรับ/ส่ง แบบ master/slave ที่สามารถควบคุมตัวรับตัวส่งได้ 
แต่บนบัสที่รับส่งพร้อมๆกัน รวมถึงใช้หลายๆ serial port ในเวลาเดียวกันอาจเกิดปัญหาข้อมูลผิดพลาดได้

