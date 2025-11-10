Dual Core 3 LED
📘 Deskripsi
Percobaan ini menunjukkan penggunaan dua core ESP32-S3 untuk menjalankan task secara paralel menggunakan FreeRTOS.

Program ini memiliki 2 task:
| Task        |   Core | LED                           | Pola Blink              | Keterangan                  |
| ----------- | -----: | ----------------------------- | ----------------------- | --------------------------- |
| Task Core 0 | Core 0 | LED2 (GPIO 5)                 | ±300 ms                 | Blink cepat                 |
| Task Core 1 | Core 1 | LED1 (GPIO 4) & LED3 (GPIO 6) | Bergantian tiap ±500 ms | Kedua LED bergantian ON/OFF |

🔌 Mapping Hardware 
| Perangkat | Pin ESP32-S3 | Mode   | Dikendalikan Oleh |
| --------- | -----------: | ------ | ----------------- |
| LED1      |       GPIO 4 | Output | Core 1            |
| LED2      |       GPIO 5 | Output | Core 0            |
| LED3      |       GPIO 6 | Output | Core 1            |

🧪 Langkah Percobaan
| No | Langkah                        | Hasil yang Diharapkan                                                    |
| -: | ------------------------------ | ------------------------------------------------------------------------ |
|  1 | Upload program ke ESP32-S3     | Serial Monitor menampilkan log FreeRTOS                                  |
|  2 | Amati LED2 (GPIO 5)            | LED2 berkedip cepat (±300 ms) — Core 0                                   |
|  3 | Amati LED1 & LED3 (GPIO 4 & 6) | LED1 & LED3 bergantian setiap ±500 ms — Core 1                           |
|  4 | Buka Serial Monitor            | Terdapat log `[Core 0]` dan `[Core 1]` menunjukkan task berjalan paralel |

🎥 Video Demo
Gdrive: https://drive.google.com/drive/folders/1zJugp3nYugUQ3zeaDMXNZDKSGXHxg3_M?usp=sharing