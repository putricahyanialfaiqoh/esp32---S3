Dual Core Buzzer

📌 Deskripsi
Percobaan ini mendemonstrasikan penggunaan dua core ESP32-S3 untuk menghasilkan pola bunyi buzzer berbeda secara paralel:
| Core   | Tugas         | Frekuensi | Pola Bunyi         |
| ------ | ------------- | --------: | ------------------ |
| Core 0 | Buzzer lambat |    800 Hz | 0.5s ON / 0.5s OFF |
| Core 1 | Buzzer cepat  |   1200 Hz | 0.2s ON / 0.2s OFF |


🛠️ Hardware Setup
| Komponen      | Pin ESP32-S3 | Mode   |
| ------------- | -----------: | ------ |
| Active Buzzer |      GPIO 13 | OUTPUT |


▶️ Langkah Percobaan
| No | Step                        | Expected Result                                  |
| -: | --------------------------- | ------------------------------------------------ |
|  1 | Upload program ke ESP32-S3  | Serial Monitor menampilkan log                   |
|  2 | Dengarkan buzzer            | Terdengar dua pola bunyi: cepat & lambat         |
|  3 | Perhatikan log untuk Core 0 | Output 800 Hz setiap 0.5 detik                   |
|  4 | Perhatikan log untuk Core 1 | Output 1200 Hz setiap 0.2 detik                  |
|  5 | Validasi multicore          | Log menunjukkan task berjalan di Core 0 & Core 1 |

🎥 Video Demo
Gdrive: https://drive.google.com/drive/folders/1K_wdP9ttsc-NksF2BDL43nwUQEU0aomJ?usp=sharing