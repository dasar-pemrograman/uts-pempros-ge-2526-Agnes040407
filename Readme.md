# M01 Warehouse Incident System

Sebuah perusahaan logistik mengalami masalah dalam pengelolaan gudang mereka. 
Selama ini, pencatatan barang dilakukan secara manual dan sering terjadi kesalahan:

- stok tidak akurat
- transaksi tidak tercatat dengan benar
- laporan sulit dilacak

Anda diminta untuk membangun sebuah sistem berbasis command-line menggunakan bahasa C 
untuk membantu perusahaan ini mengelola inventori secara lebih sistematis.

Program akan membaca perintah dari **standard input** dan menghasilkan output sesuai aturan.

---

## Ketentuan Umum

1. Program membaca input hingga menemukan:

   ```
   ---
   ```

2. Setiap perintah dipisahkan dengan karakter:

   ```
   #
   ```

3. Sistem harus:
   - konsisten (tidak boleh ada data rusak)
   - tahan terhadap input yang tidak valid
   - tidak berhenti ketika terjadi kesalahan

---

# Task 01: Register Incoming Goods (40 pts)

Gudang menerima barang dari supplier setiap hari. 
Setiap barang yang masuk harus dicatat.

## Format Perintah

```
receive#<id>#<name>#<quantity>#<price>
report
```

## Aturan

1. `receive` akan menambahkan barang baru ke sistem.
2. Setiap barang unik berdasarkan `id`.
3. Data yang disimpan:
   - id
   - name
   - quantity
   - price
4. `report` menampilkan semua barang sesuai urutan masuk.

## Format Output

```
id|name|quantity|price
```

---

## Contoh Input

```
receive#B001#Keyboard#10#150000
receive#B002#Mouse#5#50000
report
---
```

## Contoh Output

```
B001|Keyboard|10|150000.0
B002|Mouse|5|50000.0
```

---

# Task 02: Handling Shipment Errors (30 pts)

Masalah mulai muncul ketika terjadi pengiriman keluar barang.

Beberapa kasus yang sering terjadi:

- barang dijual melebihi stok
- barang tidak terdaftar
- jumlah transaksi tidak masuk akal

## Format Perintah

```
ship#<id>#<quantity>
restock#<id>#<quantity>
```

## Aturan

1. `ship` mengurangi stok barang.
2. `restock` menambah stok barang.
3. Jika:
   - barang tidak ditemukan → abaikan
   - quantity <= 0 → abaikan
   - stok tidak cukup → abaikan
4. Sistem **tidak boleh crash**.

---

## Contoh Input

```
receive#B001#Keyboard#10#150000
ship#B001#3
ship#B001#20
restock#B001#5
---
```

## Contoh Output

```
B001|Keyboard|12|150000.0
```

---

# Task 03: Audit Log System (30 pts)

Manajemen ingin mengetahui **apa yang sebenarnya terjadi di gudang**.

Setiap aktivitas harus tercatat agar dapat diaudit.

## Format Perintah

```
audit#<id>
```

## Format Log

```
log_id|type|quantity
```

## Aturan

1. Setiap operasi yang **berhasil** dicatat:
   - `receive`
   - `ship`
   - `restock`
2. ID log bersifat **global dan increment**.
3. `audit` menampilkan:
   - data barang
   - seluruh log terkait barang tersebut
4. Urutan log = urutan kejadian

---

## Contoh Input

```
receive#B001#Keyboard#10#150000
restock#B001#5
ship#B001#3
audit#B001
---
```

## Contoh Output

```
B001|Keyboard|12|150000.0
1|receive|10
2|restock|5
3|ship|3
```

---

# Tantangan Logika (WAJIB DIPAHAMI)

Soal ini bukan sekadar coding.

Anda harus memikirkan:

1. Bagaimana menyimpan banyak barang?
2. Bagaimana memastikan transaksi tidak merusak data?
3. Bagaimana memisahkan log antar barang?
4. Bagaimana menjaga ID log tetap global?
5. Bagaimana menangani input yang "tidak masuk akal"?

Jika anda hanya menulis kode tanpa memahami sistemnya, program anda akan gagal.

---

# Submission

Struktur folder:

```
src/
  main.c
changelog.txt
```

---

# Penilaian

| Task | Bobot |
|------|------|
| Task 01 | 40 |
| Task 02 | 30 |
| Task 03 | 30 |
| **Total** | **100** |

---

# Catatan Akhir

Perhatikan:

- format output HARUS sama persis
- kesalahan kecil → gagal di autograder
- solusi harus general, bukan hardcode

---
