

[EspExceptionDecoder](https://github.com/me-no-dev/EspExceptionDecoder)
-----
เป็น tool ที่ติดตั้งเพิ่มเติมลงบน Arduino IDE เพื่อใช้ช่วยเวลาโปรแกรมมีปัญหาและเกิดการแคลชขึ้น  
Exception จะถูกพ่นออกมาที่ Serial0 หรือก็คือ Serial Monitor ของ Arduino IDE นั่นเอง  
เมื่อป้อน exception ลงไปยัง EspExceptionDecoder แล้วเราก็จะรู้ว่า sourcecode บริเวณใดเกิดปัญหาขึ้น  

Installation
-----
1. ตรวจสอบ versions ของ Arduino IDE ว่าสามารถใช้งานได้
2. เข้าไปดาว์โหลด [tool](https://github.com/me-no-dev/EspExceptionDecoder/releases/latest)  
3. แตกไฟล์และติดตั้งไว้ที่ `C:\Users\Napat\Documents\Arduino\tools\EspExceptionDecoder\tool\EspExceptionDecoder.jar`  
4. Restart IDE

การใช้งาน
-----
เปิดโปรแกรม Arduino IDE และสั่งรันโปรแกรมแบบปกติ เมื่อเกิด Exception ขึ้น(จะได้รับ exception code มาทาง Serial port)  
ให้ copy และไปวางไว้ที่เมนู Tools > ESP Exception Decoder ก็จะมี result ขึ้นมาให้ตรวจสอบ   
