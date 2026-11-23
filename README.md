## Git Branch Workflow

Repository ini menggunakan sistem branching untuk menjaga kestabilan kode dan memisahkan proses pengembangan setiap anggota.

### Branch Structure

| Branch | Fungsi |
|---|---|
| `main` | Versi final yang sudah stabil dan lolos pengujian. |
| `local` | Branch integrasi dan pengujian seluruh fitur sebelum masuk ke `main`. |
| `dev/*` | Branch pribadi untuk pengembangan masing-masing anggota. |

## Pembagian tugas tiga anggota

| Anggota | File yang dikerjakan | Tugas utama |
|---|---|---|
| Anggota 1 | `src/main.cpp`, `src/game/Game.cpp`, `src/game/Input.cpp` | Menyusun program utama, menu, perhitungan skor, tampilan terminal, dan input keyboard |
| Anggota 2 | `src/dino/Dino.cpp` | Membuat dino: lompat, jongkok, animasi lari, dan area tabrakan dino |
| Anggota 3 | `src/environment/Environment.cpp`, `src/obstacles/Obstacle.cpp` | Membuat latar dan tanah bergerak serta rintangan kaktus/burung beserta tabrakan |

### Development Flow

Alur pengembangan wajib mengikuti urutan berikut:

```text
Personal Branch (nama-anggota/*)
          |
          v
       local
          |
          v
   Testing & Review
          |
          v
        Main
```

### Branch Rules

1. `main` hanya berisi kode yang sudah stabil dan lolos pengujian.
2. Developer wajib mengerjakan tugas melalui personal branch masing-masing.
3. Setiap perubahan dari personal branch harus melalui Pull Request menuju `local`.
4. Seluruh fitur harus diuji dan diintegrasikan terlebih dahulu di `local`.
5. Setelah seluruh pengujian berhasil, perubahan `local` dapat diajukan melalui Pull Request menuju `main`.
6. Dilarang melakukan Pull Request langsung dari personal branch menuju `main`.
7. Dilarang melakukan commit atau push langsung ke `main`.
8. Penggabungan ke `main` hanya dilakukan setelah mendapatkan persetujuan dan dinyatakan aman.

### Important

`main` merupakan branch produksi atau versi final project.

`local` merupakan satu-satunya jalur integrasi menuju `main`.

Pastikan seluruh perubahan telah melalui proses review, integrasi, dan testing di `local` sebelum diajukan ke `main`.
