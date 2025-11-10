Dual Core Potentiometer

📌 Deskripsi
Percobaan ini menunjukkan bagaimana ESP32-S3 menjalankan dua task secara paralel pada dua core berbeda menggunakan FreeRTOS:
| Core   | Fungsi                                      |
| ------ | ------------------------------------------- |
| Core 0 | Membaca nilai potensiometer secara realtime |
| Core 1 | Menampilkan status sistem setiap 3 detik    |

🧠 Fitur Sistem
| Core   | Task      | Fungsi                                             |
| ------ | --------- | -------------------------------------------------- |
| Core 0 | Core0Task | Membaca potensiometer dan menampilkan nilai analog |
| Core 1 | Core1Task | Mencetak status sistem secara periodik             |

🛠️ Hardware Setup
| Komponen      | Pin ESP32-S3      | Mode                   |
| ------------- | ----------------- | ---------------------- |
| Potensiometer | GPIO 4            | Analog Input           |
| 3.3V          | Potensiometer VCC | Power                  |
| GND           | Potentiometer GND | Ground                 |
| ESP32-S3 USB  | —                 | Power + Serial Monitor |

▶️ Langkah Percobaan
| No | Langkah             | Hasil Diharapkan                                         |
| -: | ------------------- | -------------------------------------------------------- |
|  1 | Upload program      | Serial monitor aktif                                     |
|  2 | Putar potensiometer | Nilai analog berubah realtime                            |
|  3 | Cek log Core 0      | Tampil nilai potensiometer setiap ~200 ms                |
|  4 | Cek log Core 1      | Pesan “System Running Smoothly” tiap 3 detik             |
|  5 | Validasi multicore  | Log menunjukkan **Core 0** & **Core 1** berjalan paralel |

🎥 Video Demo
Gdrive: https://drive.google.com/drive/folders/1-IQlojRIvyesS60SiTbj_doWpA2G7N0t?usp=sharing