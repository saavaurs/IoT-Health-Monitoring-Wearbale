# IoT Health Monitoring Wearable

Proyek ini adalah sistem pemantauan kesehatan berbasis IoT yang diimplementasikan menggunakan bahasa pemrograman C++. Sistem ini dirancang untuk wearable device yang dapat memantau parameter kesehatan pengguna secara real-time.

## Fitur
- Memantau data kesehatan seperti detak jantung, SpO2 (jumlah Oksigen), dan Sleep Tracker (Accelemeter).
- Pengiriman data hasil monitoring ke platform IoT Blynk dan Wokwi Simulator untuk dianalisis atau dipantau secara jarak jauh.
- Menggunakan sensor yang terintegrasi dengan mikrokontroler ESP32-S3 DevKitC-1.

## Teknologi
- **Bahasa:** C++
- **Perangkat:** ESP32-S3 DevKitC-1, Blynk Cloud, OLED Display (SSD1306), MPU6050, Potensiometer, Pushbutton, LED.
- **Koneksi:** Komunikasi data menggunakan protokol IoT WiFi.

## Struktur Proyek
- Seluruh kode sumber ditulis dalam C++.
- File utama dan file pendukung dikelompokkan sesuai fungsinya, seperti pembacaan sensor, pengolahan data, dan pengiriman data.

## Cara Menggunakan
1. Pastikan perangkat keras (mikrokontroler dan sensor) sudah terpasang dengan benar.
2. Upload program C++ ke mikrokontroler menggunakan IDE yang sesuai (misal: Arduino IDE jika menggunakan board Arduino).
3. Hubungkan perangkat ke jaringan (WiFi) sesuai dengan pengaturan pada kode.
4. Data kesehatan akan dikirimkan ke platform IoT yang telah ditentukan.

## Catatan
- Konfigurasi sensor dan jenis platform IoT dapat disesuaikan dengan kebutuhan.
- Pastikan library C++ yang diperlukan sudah terinstal pada lingkungan pengembangan.
