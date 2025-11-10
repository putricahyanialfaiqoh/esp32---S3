Dual Core PushButton

📌 Deskripsi
Percobaan ini menunjukkan bagaimana ESP32-S3 menangani input dan output secara paralel menggunakan dua core:
| Core   | Task       | Fungsi                                                |
| ------ | ---------- | ----------------------------------------------------- |
| Core 0 | TaskButton | Membaca tombol + debounce                             |
| Core 1 | TaskLED    | Menyalakan/mematikan LED berdasarkan flag dari Core 0 |

🛠️ Hardware Setup
| Komponen    | Pin ESP32-S3 | Mode            |
| ----------- | ------------ | --------------- |
| Push Button | GPIO 15      | Input (Pull-up) |
| LED         | GPIO 5       | Output          |


▶️ Langkah Percobaan
| No | Langkah                    | Hasil yang Diharapkan                        |
| -: | -------------------------- | -------------------------------------------- |
|  1 | Upload program ke ESP32-S3 | Serial menampilkan “task started”            |
|  2 | Tekan tombol               | Core 0 mendeteksi input & debounce           |
|  3 | Amati LED                  | LED toggle ON/OFF setiap kali tombol ditekan |
|  4 | Cek Serial Monitor         | Log dari **Core 0** & **Core 1** muncul      |

🎥 Video Demo
Gdrive: https://drive.google.com/drive/folders/1l86TyPkNUZNA6bz5GUtfGsD7UbBDtODY?usp=sharing 