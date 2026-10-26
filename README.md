# Sistem Konsumsi dan Penagihan Listrik (Kasus B)

Project Mata Kuliah Algoritma dan Pemrograman (ATP) menggunakan bahasa C++. Program ini dirancang untuk mencatat konsumsi listrik rumah tangga selama 7 hari dan menghitung tagihan secara otomatis[cite: 1].

## Fitur Program
- **Input & Validasi Pelanggan:** Mencatat maksimal 20 pelanggan beserta validasi kategori (`low-income`, `middle-income`, `high-income`) dan pemakaian harian dari Senin hingga Minggu[cite: 1].
- **Statistik Pemakaian (`totalPemakaian`):** Menghitung total pemakaian 7 hari, rata-rata harian, estimasi pemakaian bulanan (30 hari), serta mendeteksi hari dengan pemakaian tertinggi dan terendah[cite: 1].
- **Perhitungan Tarif Progresif & Diskon (`hitungTagihan`):** Menghitung tagihan awal secara berjenjang dan memotong diskon sesuai kategori pelanggan (20%, 10%, atau 0%)[cite: 1].
- **Laporan (`outputUser`):** Menampilkan rincian pemakaian dan tagihan akhir setiap pelanggan[cite: 1].
