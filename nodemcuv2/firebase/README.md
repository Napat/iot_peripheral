
# Firebase Realtime Database

Firebase Realtime Database ถูกสร้างมาเพื่อทำตัวเป็นตัวกลางในการเชื่อมต่ออุปกรณ์ต่างๆเข้าด้วยกันโดยที่นักพัฒนาไม่ต้องเสียเวลาในการพัฒนา backend server ในรูปแบบดั้งเดิมซึ่งใช้เวลาและสกิลในการพัฒนาสูง
บริการของ firebase ไม่ดีมีเพียงเฉพาะ Realtime Database เท่านั้นแต่ยังให้บริการ Hosting, Authentication, Storage, Function รวมถึงบริการอื่นๆเช่น ML Kit เป็นต้น
ซึ่งบริการเหล่านี้ช่วยส่งเสริมให้บริการ Realtime Database ที่เป็นศูนย์กลางให้มีความสามารถที่สูงขึ้นๆนั่นเอง

## จุดเด่นของ Firebase

เป็นระบบที่สามารถติดต่อเข้าถึงหรืออัปเดทข้อมูลได้แบบเรียลไทม์และง่ายดายไม่ว่าจะโดยการใช้ API หรือ library ที่ทาง Firebase community ได้เตรียมไว้ให้ในหลายๆภาษา หลายๆแฟลตฟอร์ม หรือสำหรับแฟลตฟอร์มใดๆที่ไม่มีไลบารี่ให้ใช้งาน สามารถติดต่อผ่านโปรโตคอล HTTP/HTTPs มาตรฐานนลักษณะของ REST API เพื่อร้องขอข้อมูล (GET Method) หรือส่งข้อมูล (PUT Method) เข้าไปยัง Firebase ได้เลย

## ESP8266-Arduino

การใช้งาน ESP8266 บน Arduino platform กับ firebase นั้นมีคนทำ library **NOT official** มาให้ใช้งานชื่อ [firebase-arduino](https://github.com/FirebaseExtended/firebase-arduino) ซึ่งอาจจะต้อง Note ไว้เลยว่า library นี้ **NOTE stable** แต่ก็เพียงพอที่สำหรับเลเวลเพื่อการเรียนรู้ concept ของ firebase แล้ว
Dependencies หรือ libraries ที่จำเป็นต้องติดตั้งอยู่อีกสองตัวหากจะนำมาใช้บน esp8266
สรุป library ที่ต้องติดตั้งมีดังนี้

- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
- [ESP8266 Core SDK](https://github.com/esp8266/Arduino)
- [firebase-arduino](https://github.com/FirebaseExtended/firebase-arduino)

การติดตั้ง firebase-arduino ให้ใช้วิธี download zip มาจาก gihub นะ

## Core feature issue

นับจากเวลาที่เขียนอยู่ firebase-arduino library นี้มี issue ที่ควรระวังเพราะเป็น core feature อยู่
ใครที่ใช้ library นี้อย่างเป็นเรื่องเป็นราวจะต้องติดตาม issue ดังกล่าวให้ดีๆ
- https://github.com/FirebaseExtended/firebase-arduino/issues/380
- https://github.com/FirebaseExtended/firebase-arduino/issues/224
