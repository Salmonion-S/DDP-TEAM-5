## Git Branch Workflow

Repository ini menggunakan sistem branching untuk menjaga kestabilan kode dan memisahkan proses pengembangan setiap anggota.

### Branch Structure

| Branch | Fungsi |
|---|---|
| `main` | Versi final yang sudah stabil dan lolos pengujian. |
| `staging` | Branch integrasi dan pengujian seluruh fitur sebelum masuk ke `main`. |
| `dev/*` | Branch pribadi untuk pengembangan masing-masing anggota. |

### Development Flow

Alur pengembangan wajib mengikuti urutan berikut:

```text
Personal Branch (dev/*)
          |
          v
       Staging
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
3. Setiap perubahan dari personal branch harus melalui Pull Request menuju `staging`.
4. Seluruh fitur harus diuji dan diintegrasikan terlebih dahulu di `staging`.
5. Setelah seluruh pengujian berhasil, perubahan `staging` dapat diajukan melalui Pull Request menuju `main`.
6. Dilarang melakukan Pull Request langsung dari personal branch menuju `main`.
7. Dilarang melakukan commit atau push langsung ke `main`.
8. Penggabungan ke `main` hanya dilakukan setelah mendapatkan persetujuan dan dinyatakan aman.

### Important

`main` merupakan branch produksi atau versi final project.

`staging` merupakan satu-satunya jalur integrasi menuju `main`.

Pastikan seluruh perubahan telah melalui proses review, integrasi, dan testing di `staging` sebelum diajukan ke `main`.
