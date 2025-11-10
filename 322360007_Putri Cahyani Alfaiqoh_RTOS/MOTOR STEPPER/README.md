Dual Core Stepper

📘 Deskripsi
Percobaan ini menunjukkan penggunaan dua core ESP32-S3 untuk menjalankan task paralel menggunakan FreeRTOS pada aplikasi kontrol motor stepper.

Program menggunakan 2 task:
| Task        | Core | Fungsi                                | Keterangan                        |
| ----------- | ---: | ------------------------------------- | --------------------------------- |
| TaskStepper |    1 | Menjalankan pergerakan stepper terus  | `stepper.run()` berjalan smooth   |
| TaskButton  |    0 | Membaca tombol & mengganti arah motor | Toggle arah & kirim target posisi |
Motor stepper bergerak maju–mundur antara posisi 0 hingga 800 step setiap kali tombol ditekan.

🔌 Mapping Hardware
| Perangkat            | Pin ESP32-S3 | Mode     | Dikendalikan oleh |
| -------------------- | -----------: | -------- | ----------------- |
| Step Pulse (STEP)    |      GPIO 18 | Output   | Core 1 (Stepper)  |
| Step Direction       |      GPIO 19 | Output   | Core 1 (Stepper)  |
| Step Enable          |      GPIO 20 | Output   | Core 1 (Stepper)  |
| Tombol Input         |      GPIO 12 | Input PU | Core 0 (Button)   |
| Motor Stepper Driver | A4988/Driver | ---      | Pergerakan motor  |

🧪 Langkah Percobaan
| No | Langkah                    | Hasil yang Diharapkan                   |
| -: | -------------------------- | --------------------------------------- |
|  1 | Upload program ke ESP32-S3 | Serial menampilkan log sistem           |
|  2 | Tekan tombol               | Arah motor berubah kanan ⇄ kiri         |
|  3 | Amati motor                | Motor bergerak ke 800 lalu kembali ke 0 |
|  4 | Buka Serial Monitor        | Muncul teks `>> Kanan` / `<< Kiri`      |

🧠 Penjelasan Kerja
Core 1 berjalan sebagai motor controller loop, memastikan stepper bergerak halus.
Core 0 menangani pembacaan tombol dan perubahan arah.
Output posisi stepper dijaga agar tidak negatif (rentang 0–800).

🎥 Video Demo
GDrive: https://drive.google.com/drive/folders/10E2MjZ-j4uZHOnst5GjtNRwvEUt9bqUG?usp=sharing 
Dual Core Stepper

📘 Deskripsi
Percobaan ini menunjukkan penggunaan dua core ESP32-S3 untuk menjalankan task paralel menggunakan FreeRTOS pada aplikasi kontrol motor stepper.

Program menggunakan 2 task:
| Task        | Core | Fungsi                                | Keterangan                        |
| ----------- | ---: | ------------------------------------- | --------------------------------- |
| TaskStepper |    1 | Menjalankan pergerakan stepper terus  | `stepper.run()` berjalan smooth   |
| TaskButton  |    0 | Membaca tombol & mengganti arah motor | Toggle arah & kirim target posisi |
Motor stepper bergerak maju–mundur antara posisi 0 hingga 800 step setiap kali tombol ditekan.

🔌 Mapping Hardware
| Perangkat            | Pin ESP32-S3 | Mode     | Dikendalikan oleh |
| -------------------- | -----------: | -------- | ----------------- |
| Step Pulse (STEP)    |      GPIO 18 | Output   | Core 1 (Stepper)  |
| Step Direction       |      GPIO 19 | Output   | Core 1 (Stepper)  |
| Step Enable          |      GPIO 20 | Output   | Core 1 (Stepper)  |
| Tombol Input         |      GPIO 12 | Input PU | Core 0 (Button)   |
| Motor Stepper Driver | A4988/Driver | ---      | Pergerakan motor  |

🧪 Langkah Percobaan
| No | Langkah                    | Hasil yang Diharapkan                   |
| -: | -------------------------- | --------------------------------------- |
|  1 | Upload program ke ESP32-S3 | Serial menampilkan log sistem           |
|  2 | Tekan tombol               | Arah motor berubah kanan ⇄ kiri         |
|  3 | Amati motor                | Motor bergerak ke 800 lalu kembali ke 0 |
|  4 | Buka Serial Monitor        | Muncul teks `>> Kanan` / `<< Kiri`      |

🧠 Penjelasan Kerja
Core 1 berjalan sebagai motor controller loop, memastikan stepper bergerak halus.
Core 0 menangani pembacaan tombol dan perubahan arah.
Output posisi stepper dijaga agar tidak negatif (rentang 0–800).

🎥 Video Demo
GDrive: https://drive.google.com/drive/folders/10E2MjZ-j4uZHOnst5GjtNRwvEUt9bqUG?usp=sharing 
