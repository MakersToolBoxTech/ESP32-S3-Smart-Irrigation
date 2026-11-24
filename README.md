# 🌱 ESP32-S3 Smart Irrigation System

## 📸 Smart Irrigation Circuit

![ESP32-S3 Smart Irrigation Circuit](Screenshot%202569-11-24%20073644.png)

### Automatic Watering System | Maker's Tool Box

🇹🇭 **ระบบจำลองการรดน้ำต้นไม้อัตโนมัติด้วย ESP32-S3**

🇬🇧 **Smart Farm Automatic Watering System Using ESP32-S3**

---

## 📖 เกี่ยวกับโครงการ | About This Project

โครงการนี้พัฒนาขึ้นโดย **Maker's Tool Box** เพื่อศึกษาการเขียนโปรแกรมควบคุมระบบรดน้ำต้นไม้อัตโนมัติด้วย ESP32-S3 ผ่านโปรแกรมจำลองวงจร Wokwi

This project demonstrates an automatic irrigation control system using ESP32-S3 and the Wokwi simulator.

ระบบจะจำลองการเปลี่ยนแปลงความชื้นในดิน และควบคุมสถานะปั๊มน้ำตามค่าความชื้นที่กำหนด

## ⚙️ คุณสมบัติ | Features

- ✅ ESP32-S3 Microcontroller
- ✅ Automatic Soil Moisture Simulation
- ✅ Moisture Updates Every 5 Seconds
- ✅ Automatic Pump ON/OFF Control
- ✅ LCD 16x2 I2C Display
- ✅ Relay Module
- ✅ LED Pump Status Indicator
- ✅ Serial Monitor Output

## 💧 หลักการทำงาน | How It Works

ระบบเริ่มต้นด้วยค่าความชื้นจำลอง 65%

ค่าความชื้นจะเปลี่ยนทุก 5 วินาที

**เงื่อนไขควบคุมปั๊มน้ำ**

- Soil Moisture < 35% → Pump ON
- Soil Moisture > 55% → Pump OFF

เมื่อปั๊มหยุดทำงาน ความชื้นจำลองจะค่อย ๆ ลดลง

เมื่อปั๊มทำงาน ความชื้นจำลองจะค่อย ๆ เพิ่มขึ้น

ระบบจะทำงานวนซ้ำโดยอัตโนมัติ

## 🔧 Hardware Simulation

| Component | ESP32-S3 GPIO |
|---|---|
| Relay Module | GPIO5 |
| Pump Status LED | GPIO6 |
| LCD SDA | GPIO8 |
| LCD SCL | GPIO9 |

อุปกรณ์ทั้งหมดใช้สำหรับจำลองการทำงานใน Wokwi

## 📂 Project Files

**sketch.ino**

Arduino Source Code สำหรับควบคุมระบบรดน้ำอัตโนมัติ

**diagram.json**

แผนผังวงจร ESP32-S3 สำหรับ Wokwi

**README.md**

รายละเอียดและคู่มือการทดลองโครงการ

## 🚀 How to Run

1. เปิดเว็บไซต์ Wokwi
2. สร้างโปรเจกต์ ESP32-S3 ใหม่
3. คัดลอกโค้ดจาก `sketch.ino` ไปยังโปรเจกต์
4. คัดลอกข้อมูลจาก `diagram.json` ไปยังไฟล์วงจร
5. กด Start Simulation
6. สังเกตค่าความชื้นบน LCD และสถานะปั๊มน้ำ

โครงการใช้ไลบรารี `Wire.h` ที่มาพร้อม Arduino Framework

## ⚠️ Important Note

โครงการนี้เป็นระบบจำลองเพื่อการศึกษา

ค่าความชื้นถูกสร้างด้วยซอฟต์แวร์ ไม่ได้อ่านจากเซนเซอร์จริง และยังไม่มีการควบคุมปั๊มน้ำจริง

การนำไปใช้งานกับอุปกรณ์จริงจำเป็นต้องเพิ่มเซนเซอร์ วงจรขับปั๊ม แหล่งจ่ายไฟ และระบบป้องกันที่เหมาะสม

## 👨‍💻 Developed By

**Maker's Tool Box**

Electronics | ESP32 | Arduino | Robotics | AI | IoT | Smart Farm | 3D Printing

**GitHub:** MakersToolBoxTech

เรียนรู้ ทดลอง และสร้างสิ่งประดิษฐ์ไปด้วยกัน

---

© 2026 Maker's Tool Box
