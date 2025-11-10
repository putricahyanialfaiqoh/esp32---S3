Dual-Core Servo Control

📌 Deskripsi
Percobaan ini menunjukkan bagaimana ESP32-S3 menjalankan dua task servo secara paralel pada dua core berbeda menggunakan FreeRTOS.
| Core   | Task         | Fungsi                                              |
| ------ | ------------ | --------------------------------------------------- |
| Core 0 | TaskServoCW  | Memutar servo searah jarum jam (0° → 180°)          |
| Core 1 | TaskServoCCW | Memutar servo berlawanan arah jarum jam (180° → 0°) |

🛠️ Hardware Setup
| Core   | Task         | Fungsi                                              |
| ------ | ------------ | --------------------------------------------------- |
| Core 0 | TaskServoCW  | Memutar servo searah jarum jam (0° → 180°)          |
| Core 1 | TaskServoCCW | Memutar servo berlawanan arah jarum jam (180° → 0°) |

📎 Koneksi Servo
| Servo Kabel | Warna        | ESP32-S3 |
| ----------- | ------------ | -------- |
| Sinyal      | Kuning/Putih | GPIO 15  |
| VCC         | Merah        | 5V       |
| GND         | Hitam/Coklat | GND      |

🧠 Cara Kerja Sistem
Core 0 mengirim perintah posisi servo naik bertahap
Core 1 mengirim perintah posisi servo turun bertahap
Task berjalan parallel sehingga servo tampak bergerak maju-mundur tidak linear

▶️ Langkah Percobaan
| No | Langkah                | Hasil Diharapkan                                   |
| -: | ---------------------- | -------------------------------------------------- |
|  1 | Upload program         | Pesan task muncul di Serial Monitor                |
|  2 | Servo bergerak         | Gerak maju-mundur                                  |
|  3 | Perhatikan gerak servo | Gerakan tidak smooth karena 2 core saling override |
|  4 | Serial Monitor         | Log `Core 0` & `Core 1` bergantian                 |

🎥 Video Demo
Gdrive: https://drive.google.com/drive/folders/1xxA0_UCxWb_t9nFO6QF-OKTMf1O4tiRF?usp=sharing 