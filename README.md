# 🌡️ DHT11 Serial Data Logger & SQLite Database

[![Arduino](https://img.shields.io/badge/Hardware-Arduino-00979D?style=flat-for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Python](https://img.shields.io/badge/Software-Python%203.x-3776AB?style=flat-for-the-badge&logo=python&logoColor=white)](https://www.python.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-for-the-badge)](https://opensource.org/licenses/MIT)

[TR] Bu proje, **Arduino (DHT11 + I2C LCD)** kullanarak sıcaklık ve nem verilerini okur, ekranlar ve seri port üzerinden bir **Python** betiğine aktarır. Python betiği ise bu verileri **DB Browser for SQLite** ile oluşturulan bir veritabanına kaydeder.

[EN] This project reads temperature and humidity data using an **Arduino (DHT11 + I2C LCD)** and sends it over the serial port to a **Python** script, which parses and logs the data into a **SQLite** database created via **DB Browser for SQLite**.

---

## 🇹🇷 Türkçe Kullanım Kılavuzu

### 🛠️ Kurulum ve Adımlar

Projenin sorunsuz çalışabilmesi için adımları **tam olarak sırasıyla** uygulayınız:

1. **Veritabanının Hazırlanması (DB Browser for SQLite):**
   - **DB Browser for SQLite** programını indirin ve kurun.
   - Programı açıp yeni bir veritabanı oluşturun ve adını `database.db` koyun.
   - İçerisinde **`dht11`** adında bir tablo ve bu tablonun altında **`temperature`** (INTEGER) adında bir sütun oluşturun.
   - ⚠️ **ÇOK ÖNEMLİ:** Tabloyu oluşturduktan sonra üst menüdeki **"Changes Committed" (Değişiklikleri Kaydet)** butonuna mutlaka basın ve programı kapatın. *(Aksi takdirde Python kilitlenme hatası alacaktır.)*

2. **Arduino Kodunun Yüklenmesi:**
   - Devre bağlantılarını yapın (DHT11 + I2C LCD).
   - Arduino IDE üzerinden `DHT sensor library`, `hd44780` ve `Wire` kütüphanelerini yükleyin.
   - Arduino kodunu karta yükleyin. LCD ekranda sıcaklık değerinin göründüğünden emin olun.

3. **Python Betiğinin Çalıştırılması:**
   - Gerekli kütüphaneyi yükleyin:
     ```bash
     pip install pyserial
     ```
   - Python kodundaki `database.db` dosya yolunu ve seri port adını (örneğin `COM3`) kendi bilgisayarınıza göre düzenleyin.
   - Kodları çalıştırın:
     ```bash
     python python_logger.py
     ```

---

## 🇬🇧 English User Guide

### 🛠️ Setup & Instructions

To ensure smooth operation, follow the steps in the **exact order**:

1. **Database Setup (DB Browser for SQLite):**
   - Download and install **DB Browser for SQLite**.
   - Create a new database and name it `database.db`.
   - Create a table named **`dht11`** with a column named **`temperature`** (INTEGER).
   - ⚠️ **CRITICAL:** Click the **"Write Changes" / "Commit Changes"** button in the top menu and close the application. *(Otherwise, Python will encounter a database lock error.)*

2. **Uploading Arduino Code:**
   - Set up the circuit hardware (DHT11 + I2C LCD).
   - Install `DHT sensor library`, `hd44780`, and `Wire` libraries via Arduino IDE.
   - Upload the Arduino sketch to the board. Verify temperature readings on the LCD screen.

3. **Running the Python Script:**
   - Install the required library:
     ```bash
     pip install pyserial
     ```
   - Adjust the `database.db` file path and serial port name (e.g., `COM3`) in the Python script.
   - Execute the script:
     ```bash
     python python_logger.py
     ```

---

## 🔄 Çalışma Mantığı / System Architecture

```text
[DHT11 Sensor] ──> [Arduino + LCD] ──(Serial / COM3)──> [Python Script] ──> [SQLite database.db]
