/*
    ==============|Kelompok Three Musketeer|==============
    Nama Anggota Kelompok:
    - Join Valentino Tampubolon   (140810190020)
    - Muhammad Faishal Dienul Haq (140810190016)
    - Ridho Emir Fajar Alam       (140810190044)

    Nama Program    : StAK (Sistem Antrian Puskesmas)
    Tujuan Program  : Membuat proses pengambilan antrean dalam suatu puskesmas menjadi lebih efektif  dan efisien
*/
#include <iostream>
#include <iomanip>
#include <windows.h>

#define clear system("cls")
#define pause system("pause")
#define sleepy Sleep(250)

using namespace std;


struct Pasien{
    // data pada elemen queue
    string nama;
    int umur;
    // pointer menunjuk ke elemen berikutnya
    Pasien *next;
};
struct Queue{
    // pointer elemen terdepan dari queue
    Pasien *front;
    // pointer elemen belakang dari queue
    Pasien *back;
};
Queue Q;

void createQueue(Queue &Q);                      //membuat antrian baru
void createElement(Pasien *&new_element);       //pengisian value pada element baru
void enqueue(Queue &Q, Pasien *new_element);    //memasukan data pada urutan terakhir
void panggilQueue(Queue &Q,Pasien *result_element,string antrian);//mengeluarkan data pada urutan pertama
void traversal(Queue Q);   //menampilkan seluruh data
void editQueue(Queue &asal, Queue &tujuan, Pasien* &pCari, string &antrian);      //mengurutkan antrian menurut umur
void menuAntrianBaru(Queue &a, Queue &b, Queue &c, Pasien* new_element);          //menu untuk memilih antrian baru
void menuDaftarAntrian(Queue a, Queue b, Queue c);  // Menu untuk menampilkan daftar antrian yang ada
void menueditQueue(Queue &a, Queue &b, Queue &c, Pasien* &pCari);   // Menu untuk mengedit daftar antrian
void menuPanggilQueue(Queue &a, Queue &b, Queue &c, Pasien *result_element);    // Menu yang isinya daftar antrian yang ingin dipanggil
void buktiAntrian(string antrian, Pasien *&new_element);    // Menampilkan Bukti data sudah dimasukkan ke antrian

int main(){
    int pilihan;        // Untuk memilih pada Menu utama
    char pilihan2;      // untuk opsi "Memilih lagi ?"
    Queue lansia,umum,anak;                     //membuat variabel dari node Queue untuk antrian tertentu
    Pasien* pasienBaru, *pasienPanggil;         //membuat variabel dari node pasien untuk kondisi tertentu

    // Membuat wadah untuk Antrian Lansia, Anak dan Umum
    createQueue(lansia);                        
    createQueue(umum);
    createQueue(anak);

    // Menu Utama
    do{
    clear;
    cout <<"=========|StAK|=========\n";
    cout <<"1. Buat Antrian Baru\n";
    cout <<"2. Lihat Daftar Antrian\n";
    cout <<"3. Mengubah Antrian\n";
    cout <<"4. Memanggil Pasien\n";
    cout <<"5. Exit program\n";
    cout <<"------------------------------\nPilih (1-5):";cin >> pilihan;
    switch (pilihan)
    {
    case 1:                                                 //jika terpilih nomor 1
        clear;                                              //melakukan clearing screen
        menuAntrianBaru(lansia,anak,umum,pasienBaru);       //memanggil fungsi menuAntrianBaru untuk menambahkan data pada antrian tertentu
        break;
    case 2:                                                 //jika terpilih nomor 2
        clear;                                              //melakukan clearing screen
        menuDaftarAntrian(lansia,anak,umum);                //memanggil fungsi menuDaftarAntrian untuk melihat data yang ada dalam antrian tertentu
        break;
    case 3:                                                 //jika terpilih nomor 3
        clear;                                              //melakukan clearing screen
        menueditQueue(lansia,anak,umum, pasienBaru);        //memanggil menueditQueue untuk melakukan perubahan antrian    
        break;
    case 4:                                                 //jika terpilih nomor 4
        clear;                                              //melakukan clearing screen
        menuPanggilQueue(lansia,anak,umum,pasienPanggil);   //memanggil fungsi menuPanggilQueue untuk melakukan pemanggilan pasien dalam sebuah antrian
        break;
    case 5:                                                 //jika terpilih nomor 5
        cout << "Terimakasi telah menggunakan layanan StAK \n";
        exit(0);                                            //keluar dari program (program selesai)
        break;
    default:                                                //jika nomor yang dipilih tidak ada dalam menu 
        cout << "Input yang anda masukkan salah!\n";
        break;
    }
    cout << "Ingin melanjutkan program (Y/N)? ";cin >> pilihan2;    //input untuk memilih melanjutkan program atau tidak
    }while(pilihan2 == 'Y' || pilihan2 == 'y');                     //melakukan looping jika jawaban bernilai Y atau y

}

// membuat sebuah queue
void createQueue(Queue &Q){
    Q.front = NULL;
    Q.back = NULL;
}

// membuat elemen baru queue
void createElement(Pasien *&new_element){
    // mengalokasi memori tipe data element
    
    new_element = new Pasien;                                                //mendeklarasikan bahwa new_element sebagai node baru
    cout << "Masukkan Nama Pasien :";getline(cin>>ws, new_element->nama);    //melakukan input nama pasien
    cout << "Masukkan Umur Pasien :";cin >> new_element->umur;              //melakukan input umur pasien
    new_element -> next = NULL;                                             //menginisasi bahwa node selanjutnya masih kosong
}

//memasukan elemen ke queue
void enqueue(Queue &Q, Pasien *new_element){
     //kondisi jika queue masih kosong
    if(Q.front == NULL){
        Q.front = new_element;
        Q.back = new_element;
    }
    //kondisi jika queue tidak kosong
    else{
        Q.back -> next = new_element;
        Q.back = new_element;
    }
    
}

//mencetak elemen/isi sebuah queue
void traversal(Queue Q){
    int a = 1;                      // Membuat nomor Antrian
    //kondisi jika queue kosong
    if(Q.front == NULL){
        cout << "Antrian Kosong !" << endl;
    }
    //kondisi jika queue tidak kosong
    else{
        Pasien *trav = Q.front;
        for(int i=0; i<40; i++){
            cout <<"=";
        }
        cout << "\n|            Nama            |Umur| No |\n";
        for(int i=0; i<40; i++){
            cout <<"-";
        }
        cout << endl;
        while (trav != NULL){
            cout << setw(29)<< left << "| " + trav -> nama  << "|"<< setw(4) << left << trav -> umur << "| "<<setw(3) << a++ << "|" <<endl;
            trav = trav -> next;
        }
        for(int i=0; i<40; i++){
            cout <<"=";
        }
        cout << endl;
    }
}

// Mengedit Antrian
void editQueue(Queue &asal, Queue &tujuan, Pasien* &pCari, string &antrian){
    Pasien *tmp, *tmp1;
    Pasien *pSearch = asal.front;
    while(tmp1 != asal.back){
        // Mengubah Jika data yang ingin diubah ada di posisi paling awal
        if(pSearch -> nama == pCari -> nama && pSearch ->umur == pCari -> umur && pSearch == asal.front){
            tmp = new Pasien;                       //memnbuat node baru
            tmp -> nama = asal.front -> nama;       
            tmp -> umur = asal.front -> umur;       
            tmp -> next = NULL;
            enqueue(tujuan,tmp);                    //melakukan input queue atau perubahan yang dibuat
            asal.front = asal.front -> next;        
            cout << "Pemindahan antrian telah berhasil di lakukan\n";
            cout << "Bukti Antrian Sedang Diproses";
            buktiAntrian(antrian,tmp);              //mencetak bukti antrian
            
            tmp = NULL;
            break;
        }
        // Jika data ada di antara awal dan akhir antrian
        else if(pSearch -> nama == pCari -> nama && pSearch ->umur == pCari -> umur && pSearch != asal.back){
            tmp = NULL;                             
            tmp = new Pasien;                       //memnbuat node baru
            tmp -> nama = pSearch -> nama;
            tmp -> umur = pSearch -> umur;
            tmp -> next = NULL;
            tmp1 -> next = pSearch -> next;
            enqueue(tujuan,tmp);                    //melakukan input queue atau perubahan yang dibuat
            
            tmp = NULL;
            cout << "Pemindahan antrian telah berhasil di lakukan\n";
            cout << "Bukti Antrian Sedang Diproses";
            buktiAntrian(antrian,tmp);              //mencetak bukti antrian
            break;
        }
        // Jika data ada di akhir antrian
        else if(pSearch -> nama == pCari -> nama && pSearch ->umur == pCari -> umur && pSearch == asal.back){
            tmp = NULL;
            tmp = new Pasien;                       //memnbuat node baru
            tmp -> nama = asal.back -> nama;
            tmp -> umur = asal.back -> umur;
            tmp -> next = NULL;
            asal.back = tmp1;
            
            enqueue(tujuan,tmp);                    //melakukan input queue atau perubahan yang dibuat
            tmp = NULL;
            cout << "Pemindahan antrian telah berhasil di lakukan\n";
            cout << "Bukti Antrian Sedang Diproses";
            buktiAntrian(antrian,tmp);              //mencetak bukti antrian
            break;
        }
        // Untuk mengecek data yang digunakan di while
        else{
            if(pSearch == asal.back){
                cout <<"Nama yang dicari tidak ditemukan dalam antrian ini !\n";
                break;
            }else{
                tmp1 = pSearch;                 
                pSearch = pSearch -> next;      //akan mencari data yang sesuai dengan yang ada di antrian
            } 
        }
    }
}

// Bukti masuknya data ke antrian
void buktiAntrian(string antrian, Pasien *&new_element){
    Pasien *pBaru;
    pBaru = new Pasien;                     //membuat node baru
    pBaru -> nama = new_element -> nama;    
    pBaru -> umur = new_element -> umur;
    for(int i=0;i<4;i++){
        sleepy;     // Loading, dimana proses bukti diproses
        cout << ".";
    }
    cout << endl;
    pause;  // Menghentikan compile sementara
    clear;
    for(int i=0; i<35; i++){
            cout <<"=";
    }
    cout << endl;
    if(antrian == "Poli Lansia"){                                               //kondisi jika yang antrian dipilih poli lansia
        cout << setw(35)<< "|   Bukti Antrian  Poli Lansia    |\n";
    }else{                                                                      
        cout << setw(35)<< "|     Bukti Antrian " + antrian + "     |\n";
    }
    for(int i=0; i<35; i++){
        cout <<"-";
    }
    cout << endl;
    cout << setw(34) << left << "|Nama : " + pBaru -> nama << "|" << endl;      //mencetak nama pasien yang baru diinput
    cout << "|Umur : " << setw(26) << left << pBaru -> umur << "|" << endl;     //mencetak umur pasien yang baru diinput
    for(int i=0; i<35; i++){
        cout <<"=";
    }
    cout << endl << "Harap Bukti Antrian Disimpan dengan baik !\n";
}

// Memanggil Data pada antrian
void panggilQueue(Queue &Q,Pasien *result_element,string antrian){
    //kondisi jika queue kosong
    if(Q.front == NULL){
        cout << "Antrian Kosong!" << endl;
    }
    //kondisi jika queue tidak kosong
    else{
        cout << "Sedang melakukan proses memanggil pasien";
        for(int i=0;i<4;i++){
        sleepy;     // Loading, dimana proses bukti diproses
        cout << ".";
        }
        cout << endl;
        pause;  // Menghentikan compile sementara
        clear;
        for(int i=0; i<46; i++){
            cout <<"=";
        }
        cout << endl;
        if(antrian == "Poli Lansia"){
            cout <<"| Memanggil Pasien dalam antrian Poli Lansia |\n";
        }else{
            cout <<"|  Memanggil Pasien dalam antrian " + antrian + "  |\n";
        }
        for(int i=0; i<46; i++){
        cout <<"-";
        }
        cout << endl;
        result_element = Q.front;
        Q.front = Q.front -> next;
        cout << setw(45) << left << "|Nama : " + result_element -> nama << "|" << endl;
        cout << "|Umur : " << setw(37) << left << result_element -> umur << "|" << endl; 
        for(int i=0; i<46; i++){
        cout <<"=";
        }
        cout << endl << "Pemanggilan pasien berhasil !\n";
        result_element -> next = NULL;
    }
}

//menu untuk mengubah suatu antrian
void menueditQueue(Queue &a, Queue &b, Queue &c, Pasien* &pCari){
    int pilihan1,pilihan2;
    string antrian;
    cout <<"=========|StAK|=========\n";
    cout << "    -Edit Antrian-\n";
    cout <<"1. Poli Lansia\n";
    cout <<"2. Poli Anak\n";
    cout <<"3. Poli Umum\n";
    cout <<"------------------------\n";cout << "Pilih Antrian Asal(1-3) :";cin >> pilihan1;       
    switch (pilihan1)
    {
    case 1:                                             //jika yang dipilih nomor 1
    if(a.front == NULL && a.back == NULL){              //jika antrian kosong
        cout << "Antrian Kosong !" << endl;
    }else{                                              //jika antrian ada
        cout <<"=========|StAK|=========\n";
        cout << "    -Edit Antrian-\n"; 
        cout <<"1. Poli Anak\n";                    
        cout <<"2. Poli Umum\n";
        cout <<"------------------------\n";cout << "Pilih Antrian Yang dituju(1-3) :";cin >> pilihan2;
        switch (pilihan2)
        {
        case 1:
            clear;
            pCari=NULL;
            pCari = new Pasien;                         //membuat node baru
            cout << "----|Pemindahan antrian dari Poli lansia -> Poli Anak|----\n";
            cout << "Masukkan Data Diri Pasien yang akan dipindahkan\n";
            cout << "Masukkan Nama Pasien :";getline(cin>>ws, pCari->nama);     //memasukkan nama pasien yang ingin dipindahkan
            cout << "Masukkan Umur Pasien :";cin >> pCari->umur;                //memasukkan umur pasien yang ingin dipindahkan
            antrian = "Poli Anak";
            editQueue(a,b,pCari,antrian);                                       //masuk ke fungsi editqueue untuk memproses perubahan antrian
            break;
        case 2:
            clear;
            pCari = NULL;
            pCari = new Pasien;                         //membuat node baru
            cout << "----|Pemindahan antrian dari Poli lansia -> Poli Umum|----\n";
            cout << "Masukkan Data Diri Pasien yang akan dipindahkan\n";
            cout << "Masukkan Nama Pasien :";getline(cin>>ws, pCari->nama);     //memasukkan nama pasien yang ingin dipindahkan
            cout << "Masukkan Umur Pasien :";cin >> pCari->umur;                //memasukkan umur pasien yang ingin dipindahkan
            antrian = "Poli Umum";  
            editQueue(a,c,pCari,antrian);                                       //masuk ke fungsi editqueue untuk memproses perubahan antrian
            break;

        default:                                                               //jika nomor yang dipilih tidak ada dalam menu
            cout << "Input yang anda masukkan salah!\n";
            break;
        }
        
    }
    break;

    case 2:                                                                //jika yang dipilih nomor 2
    if(b.front == NULL && b.back == NULL){                                 //jika antrian kosong
        cout << "Antrian Kosong !" << endl;
    }else{                                                                  //jika antrian ada
        cout <<"=========|StAK|=========\n";
        cout << "    -Edit Antrian-\n";
        cout <<"1. Poli Lansia\n";
        cout <<"2. Poli Umum\n";
        cout <<"------------------------\n";cout << "Pilih Antrian Yang dituju(1-3) :";cin >> pilihan2;
        switch (pilihan2)
        {
        case 1:
            clear;
            pCari=NULL;
            pCari = new Pasien;                                             //membuat node baru
            cout << "----|Pemindahan antrian dari Poli Anak -> Poli Lansia|----\n";
            cout << "Masukkan Data Diri Pasien yang akan dipindahkan\n";
            cout << "Masukkan Nama Pasien :";getline(cin>>ws, pCari->nama);             //memasukkan nama pasien yang ingin dipindahkan
            cout << "Masukkan Umur Pasien :";cin >> pCari->umur;                        //memasukkan umur pasien yang ingin dipindahkan
            antrian = "Poli Lansia";
            editQueue(b,a,pCari,antrian);                                               //masuk ke fungsi editqueue untuk memproses perubahan antrian
            break;
        case 2:
            clear;
            pCari=NULL;                                         
            pCari = new Pasien;                                            //membuat node baru                 
            cout << "----|Pemindahan antrian dari Poli Anak -> Poli Umum|----\n";
            cout << "Masukkan Data Diri Pasien yang akan dipindahkan\n";
            cout << "Masukkan Nama Pasien :";getline(cin>>ws, pCari->nama);           //memasukkan nama pasien yang ingin dipindahkan
            cout << "Masukkan Umur Pasien :";cin >> pCari->umur;                      //memasukkan umur pasien yang ingin dipindahkan
            antrian = "Poli Umum";
            editQueue(b,c,pCari,antrian);                                             //masuk ke fungsi editqueue untuk memproses perubahan antrian
            break;      
        default:                                                                        //jika nomor yang dipilih tidak ada dalam menu
            cout << "Input yang anda masukkan salah!\n";
            break;
        }
        
    }
    break;

    case 3:                                                             //jika yang dipilih nomor 3
    if(c.front == NULL && c.back == NULL){                                   //jika antrian kosong
        cout << "Antrian Kosong !" << endl;
    }else{                                                              //jika antrian ada
        cout <<"=========|StAK|=========\n";
        cout << "    -Edit Antrian-\n";
        cout <<"1. Poli Lansia\n";
        cout <<"2. Poli Anak\n";
        cout <<"------------------------\n";cout << "Pilih Antrian Yang dituju(1-3) :";cin >> pilihan2;
        switch (pilihan2)
        {
        case 1:
            clear;
            pCari=NULL;
            pCari = new Pasien;                                          //membuat node baru
            cout << "----|Pemindahan antrian dari Poli Umum -> Poli Lansia|----\n";
            cout << "Masukkan Data Diri Pasien yang akan dipindahkan\n";
            cout << "Masukkan Nama Pasien :";getline(cin>>ws, pCari->nama);         //memasukkan nama pasien yang ingin dipindahkan
            cout << "Masukkan Umur Pasien :";cin >> pCari->umur;                    //memasukkan umur pasien yang ingin dipindahkan
            antrian = "Poli Lansia";
            editQueue(c,a,pCari,antrian);                                           //masuk ke fungsi editqueue untuk memproses perubahan antrian
            break;
        case 2:
            clear;
            pCari=NULL;
            pCari = new Pasien;                                             //membuat node baru
            cout << "----|Pemindahan antrian dari Poli Umum -> Poli Anak|----\n";
            cout << "Masukkan Data Diri Pasien yang akan dipindahkan\n";
            cout << "Masukkan Nama Pasien :";getline(cin>>ws, pCari->nama);         //memasukkan nama pasien yang ingin dipindahkan
            cout << "Masukkan Umur Pasien :";cin >> pCari->umur;                    //memasukkan umur pasien yang ingin dipindahkan
            antrian = "Poli Anak";
            editQueue(c,b,pCari,antrian);                                           //masuk ke fungsi editqueue untuk memproses perubahan antrian
            break;      
        default:                                                                     //jika nomor yang dipilih tidak ada dalam menu
            cout << "Input yang anda masukkan salah!\n";
            break;
        }
        
    }
    break;

    default:                                                      //jika nomor yang dipilih tidak ada dalam menu
        cout << "Input yang anda masukkan salah!\n";
        break;
    }
}

//menu untuk membuat antrian baru
void menuAntrianBaru(Queue &a, Queue &b, Queue &c, Pasien* new_element){
    int pilihan1;
    string antrian;
    Pasien* try_again;
    cout <<"=========|StAK|=========\n";
    cout << "    -Antrian Baru-\n";
    cout <<"1. Poli Lansia\n";
    cout <<"2. Poli Anak\n";
    cout <<"3. Poli Umum\n";
    cout <<"------------------------\n";cout << "Pilih(1-3) :";cin >> pilihan1;
    switch (pilihan1)
    {
    case 1:                                                         //jika yang terpilih nomor 1
        antrian = "Poli Lansia";
        createElement(new_element);
        while(new_element -> umur < 0){
            cout << "Gagal Menambah Antrian, silahkan masukkan umur >= 0\n";
            pause;  
            clear;
            cout << "Harap Masukkan Kembali Data Diri Pasien Yang Didaftarkan\n";
            createElement(new_element);
        }
        enqueue(a,new_element);                                   //melakukan proses input
        cout << "Pasien berhasil ditambahkan dalam Antrian Poli Lansia\n";
        cout << "Bukti Antrian Sedang Diproses";
        buktiAntrian(antrian,new_element);
        cout << endl << endl << "======|Daftar Antrian Poli Lansia|======\n";
        traversal(a);                         //mencetak bukti antrian
        break;                                 //membuat input pasien baru ke antrian tertentu
        

    case 2:                                                          //jika yang terpilih nomor 2
        antrian = "Poli Anak";
        createElement(new_element);                                 //membuat input pasien baru ke antrian tertentu
        while(new_element -> umur < 0){
            cout << "Gagal Menambah Antrian, silahkan masukkan umur >= 0\n";
            pause;  
            clear;
            cout << "Harap Masukkan Kembali Data Diri Pasien Yang Didaftarkan\n";
            createElement(new_element);
        }
        enqueue(b,new_element);                                   //melakukan proses input
        cout << "Pasien berhasil ditambahkan dalam Antrian Poli Anak\n";
        cout << "Bukti Antrian Sedang Diproses";
        buktiAntrian(antrian,new_element);
        cout << endl << endl << "======|Daftar Antrian Poli Anak|======\n";
        traversal(b);                         //mencetak bukti antrian
        break; 
    
    case 3:
        antrian = "Poli Umum";
        createElement(new_element);                               //membuat input pasien baru ke antrian tertentu
        while(new_element -> umur < 0){
            cout << "Gagal Menambah Antrian, silahkan masukkan umur >= 0\n";
            pause;  
            clear;
            cout << "Harap Masukkan Kembali Data Diri Pasien Yang Didaftarkan\n";
            createElement(new_element);
        }
        enqueue(c,new_element);                                   //melakukan proses input
        cout << "Pasien berhasil ditambahkan dalam Antrian Poli Umum\n";
        cout << "Bukti Antrian Sedang Diproses";
        buktiAntrian(antrian,new_element);
        cout << endl << endl << "======|Daftar Antrian Poli Umum|======\n";
        traversal(c);      

    default:                                                //jika nomor yang dipilih tidak ada dalam menu
        cout << "Input yang anda masukan salah!\n";
        break;
    }

}

//menu untuk melihat daftar antrian yang ingin dilihat
void menuDaftarAntrian(Queue a, Queue b, Queue c){
    int pilihan2;
    cout <<"=========|StAK|=========\n";
    cout << "   -Daftar Antrian-\n";
    cout <<"1. Poli Lansia\n";
    cout <<"2. Poli Anak\n";
    cout <<"3. Poli Umum\n";
    cout <<"------------------------------\nPilih sesuai kondisi :";cin>>pilihan2;
    switch (pilihan2)
    {
    case 1:                                             //jika terpilih nomor 1
        clear;
        cout << "====|Daftar Pasien Antrian Poli Lansia|====\n";
        traversal(a);                                   //mencetak antrian yang ada pada poli lansia
        break;
    case 2:                                             //jika terpilih nomor 1
        clear;
        cout << "====|Daftar Pasien Antrian Poli Anak|====\n";
        traversal(b);                                   //mencetak antrian yang ada pada poli anak
        break;
    case 3:                                             //jika terpilih nomor 1
        clear;
        cout << "====|Daftar Pasien Antrian Poli Umum|====\n";
        traversal(c);                                   //mencetak antrian yang ada pada poli umum
        break;
    default:                                            //jika nomor yang dipilih tidak ada dalam antrian
        cout << "Input yang anda masukan salah!\n";
        break;
    }
}

//menu untuk memanggil pasien yang ada dalam antrian tertentu
void menuPanggilQueue(Queue &a, Queue &b, Queue &c, Pasien *result_element){
    string antrian;
    int pilihan1;
    cout <<"=========|StAK|=========\n";
    cout << "    -Panggil Antrian-\n";
    cout <<"1. Poli Lansia\n";
    cout <<"2. Poli Anak\n";  
    cout <<"3. Poli Umum\n";
    cout <<"------------------------\n";cout << "Pilih Antrian (1-3) :";cin >> pilihan1;
    switch (pilihan1)
    {
    case 1:                                     //jika terpilih nomor 1
        antrian = "Poli Lansia";
        panggilQueue(a,result_element,antrian);         //melakukan proses panggil pasien yang ada pada poli lansia
        break;

    case 2:                                     //jika terpilih nomor 2
        antrian = "Poli Anak";
        panggilQueue(b,result_element,antrian);          //melakukan proses panggil pasien yang ada pada poli anak
        break;

    case 3:                                     //jika terpilih nomor 3
        antrian = "Poli Umum";
        panggilQueue(c,result_element,antrian);         //melakukan proses panggil pasien yang ada pada poli umum
        break;

    default:                                //jika nomor yang dipilih tidak ada dalam antrian
        cout << "Input yang anda masukkan salah!\n";
        break;
    }
}