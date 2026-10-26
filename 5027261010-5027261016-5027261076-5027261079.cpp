#include <iostream>
#include <string>
using namespace std;

struct pelanggan {
    string nama;
    string kategori;
    double pemakaianHarian[7];
    double totalPemakaian;
    double rataHarian;
    double estimasiBulanan;
    string hariTertinggi;
    double pemakaianTertinggi;
    string hariTerendah;
    double pemakaianTerendah;
    double tagihanAwal;
    double totalDiskon;
    double tagihanAkhir;
};

string days[7] = {
    "Senin", "Selasa", "Rabu", "Kamis",
    "Jumat", "Sabtu", "Minggu"
};

void inputUser(pelanggan inputCustomer[], int &jumlahPelanggan) {
    cout << "Masukkan jumlah pelanggan: ";
    cin >> jumlahPelanggan;

    if (jumlahPelanggan < 1 || jumlahPelanggan > 20) {
        cout << "ERROR: Jumlah pelanggan harus 1-20." << endl;
        jumlahPelanggan = 0;
    } else {
        cin.ignore(); 

        for (int i = 0; i < jumlahPelanggan; i++) {
            cout << "=== Pelanggan " << i+1 << " ===" << endl;
            cout << "Nama: ";
            getline(cin, inputCustomer[i].nama);

            cout << "Kategori (low-income/middle-income/high-income): ";
            cin >> inputCustomer[i].kategori;

            while (inputCustomer[i].kategori != "low-income" &&
                   inputCustomer[i].kategori != "middle-income" &&
                   inputCustomer[i].kategori != "high-income") {
                cout << "ERROR: Kategori tidak valid. Masukkan lagi." << endl;
                cout << "Kategori (low-income/middle-income/high-income): ";
                cin >> inputCustomer[i].kategori;
            }

            for (int j = 0; j < 7; j++) {
                cout << "Pemakaian " << days[j] << " (kWh): ";
                cin >> inputCustomer[i].pemakaianHarian[j];
            }

            cin.ignore(); // buang newline sisa sebelum getline pelanggan berikutnya
        }
    }
}

void totalPemakaian(pelanggan outputPemakaian[], int jumlahPelanggan) {
    for (int i = 0; i < jumlahPelanggan; i++) {
        outputPemakaian[i].totalPemakaian = 0;

        for (int j = 0; j < 7; j++) {
            outputPemakaian[i].totalPemakaian +=
                outputPemakaian[i].pemakaianHarian[j];
        }

        outputPemakaian[i].rataHarian =
            outputPemakaian[i].totalPemakaian / 7;

        outputPemakaian[i].estimasiBulanan =
            (outputPemakaian[i].totalPemakaian / 7) * 30;
        
        double maxPemakaian = outputPemakaian[i].pemakaianHarian[0];
        string maxHari = days[0];
        for (int k = 1; k < 7; k++) {
            if (outputPemakaian[i].pemakaianHarian[k] > maxPemakaian) {
                maxPemakaian = outputPemakaian[i].pemakaianHarian[k];
                maxHari = days[k];
            }
        }
        outputPemakaian[i].pemakaianTertinggi = maxPemakaian;
        outputPemakaian[i].hariTertinggi = maxHari;

        double minPemakaian = outputPemakaian[i].pemakaianHarian[0];
        string minHari = days[0];
        for (int k = 1; k < 7; k++) {
            if (outputPemakaian[i].pemakaianHarian[k] < minPemakaian) {
                minPemakaian = outputPemakaian[i].pemakaianHarian[k];
                minHari = days[k];
            }
        }
        outputPemakaian[i].pemakaianTerendah = minPemakaian;
        outputPemakaian[i].hariTerendah = minHari;
    }
}

void hitungTagihan(pelanggan outputTagihan[], int jumlahPelanggan) {
    for (int i = 0; i < jumlahPelanggan; i++) {
        double kwh = outputTagihan[i].estimasiBulanan; 
        //double kwh = outputTagihan[i].totalPemakaian; kalau 7 hari doang
        if (kwh <= 100) { 
            outputTagihan[i].tagihanAwal = kwh * 1000; 
        } else if (kwh <= 200) { 
            outputTagihan[i].tagihanAwal = 100000 + (kwh - 100) * 1500;
        } else {
            outputTagihan[i].tagihanAwal = 250000 + (kwh - 200) * 2000;
        }
        
        string kategoriPelanggan = outputTagihan[i].kategori;
        if (kategoriPelanggan == "low-income") {
            outputTagihan[i].totalDiskon = outputTagihan[i].tagihanAwal * 0.20;
        } else if (kategoriPelanggan == "middle-income") {
            outputTagihan[i].totalDiskon = outputTagihan[i].tagihanAwal * 0.10;
        } else {
            outputTagihan[i].totalDiskon = outputTagihan[i].tagihanAwal * 0.00;
        }
        outputTagihan[i].tagihanAkhir = outputTagihan[i].tagihanAwal - outputTagihan[i].totalDiskon;
    }
}

void outputUser(pelanggan outputCustomer[], int jumlahPelanggan) {
    cout << fixed;
    cout.precision(2);

    cout << "\n[ LAPORAN PEMAKAIAN LISTRIK ]" << endl;
    cout << "> Jumlah pelanggan : " << jumlahPelanggan << endl;

    for (int i = 0; i < jumlahPelanggan; i++) {
        int persentaseDiskon;

        if (outputCustomer[i].kategori == "low-income") {
            persentaseDiskon = 20;
        } else if (outputCustomer[i].kategori == "middle-income") {
            persentaseDiskon = 10;
        } else {
            persentaseDiskon = 0;
        }

        cout << "\n[ PELANGGAN " << i + 1 << " : "
             << outputCustomer[i].nama << " ]" << endl;
        cout << "> Kategori          : " << outputCustomer[i].kategori << endl;

        cout << "\n[ PEMAKAIAN ]" << endl;
        cout << "> Total 7 hari      : " << outputCustomer[i].totalPemakaian << " kWh" << endl;
        cout << "> Rata-rata harian  : " << outputCustomer[i].rataHarian << " kWh" << endl;
        cout << "> Estimasi bulanan  : " << outputCustomer[i].estimasiBulanan << " kWh" << endl;
        cout << "> Hari tertinggi    : " << outputCustomer[i].hariTertinggi
             << " (" << outputCustomer[i].pemakaianTertinggi << " kWh)" << endl;
        cout << "> Hari terendah     : " << outputCustomer[i].hariTerendah
             << " (" << outputCustomer[i].pemakaianTerendah << " kWh)" << endl;

        cout << "\n[ TAGIHAN ]" << endl;
        cout << "> Tagihan awal      : Rp" << outputCustomer[i].tagihanAwal << endl;
        cout << "> Diskon            : Rp" << outputCustomer[i].totalDiskon
             << " (" << persentaseDiskon << "%)" << endl;
        cout << "> Tagihan akhir     : Rp" << outputCustomer[i].tagihanAkhir << endl;
    }
}

int main() {
    pelanggan dataPelanggan[20];
    int jumlahPelanggan = 0;
    inputUser(dataPelanggan, jumlahPelanggan);
    if (jumlahPelanggan > 0) {
        totalPemakaian(dataPelanggan, jumlahPelanggan);
        hitungTagihan(dataPelanggan, jumlahPelanggan);
        outputUser(dataPelanggan, jumlahPelanggan);
    }
    return 0;
}