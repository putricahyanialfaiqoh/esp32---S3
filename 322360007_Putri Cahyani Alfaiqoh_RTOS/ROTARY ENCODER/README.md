Dual-Core Rotary Encoder

📌 Deskripsi
Percobaan ini menggunakan ESP32-S3 dual-core untuk membaca rotary encoder dan push button secara paralel menggunakan FreeRTOS.
| Core   | Task        | Fungsi                            |
| ------ | ----------- | --------------------------------- |
| Core 0 | TaskEncoder | Membaca rotary encoder (CLK & DT) |
| Core 1 | TaskButton  | Membaca tombol push (SW encoder)  |

🛠️ Hardware Setup
| Komponen           | Pin ESP32-S3 | Mode          |
| ------------------ | ------------ | ------------- |
| Rotary Encoder CLK | GPIO 15      | Input Pull-Up |
| Rotary Encoder DT  | GPIO 16      | Input Pull-Up |
| Rotary Encoder SW  | GPIO 17      | Input Pull-Up |
| Power              | 3.3V & GND   | —             |

📎 Koneksi Encoder
| Encoder Pin | Fungsi      | ESP32-S3 Pin |
| ----------- | ----------- | ------------ |
| CLK         | Channel A   | GPIO 15      |
| DT          | Channel B   | GPIO 16      |
| SW          | Push Button | GPIO 17      |
| +           | VCC         | 3.3V         |
| GND         | Ground      | GND          |

🧠 Cara Kerja Sistem
Core 0 membaca sinyal rotary encoder:
Putar CW → nilai meningkat
Putar CCW → nilai menurun
Core 1 memonitor tombol encoder
Tekan tombol → nilai bertambah
Setiap perubahan ditampilkan pada Serial Monitor secara realtime

▶️ Langkah Percobaan
| No | Langkah              | Hasil yang Diharapkan                |
| -: | -------------------- | ------------------------------------ |
|  1 | Upload program       | Serial tampilkan pesan task start    |
|  2 | Putar encoder CW/CCW | Nilai bertambah / berkurang          |
|  3 | Tekan tombol         | Nilai bertambah                      |
|  4 | Buka Serial Monitor  | Terlihat output dari Core 0 & Core 1 |

🎥 Video Demo
Gdrive: https://drive.google.com/drive/folders/1xHsLUh8lWJG1qjUEWygBUBDPuTShIQ0_?usp=sharing
