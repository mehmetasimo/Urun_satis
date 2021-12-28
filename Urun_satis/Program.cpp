/****************************************************************************
** computer equipment dealer selling database management system 
****************************************************************************/

#include <iostream>							// Cok sayida iliskili dosya kullanimi icin proje tanitim dosyasinda yer alan kutuphaneler eklendi.
#include <iomanip>							// Satirlar arasi islem komutu kullanimi icin eklenmistir.
#include <fstream>							// Dosyalar uzerinde islem yapilmasi icin eklenmistir.
#include <string>							  // Dosyada veri islemleri string tipindeki elemanlarla yapilacagi icin eklenmistir.
#include <stdio.h>
#include <windows.h>						// Renkli komut satirlari kullanimi icin eklendi.


using namespace std;

bool urun_kontrol(string urunKodu);			// Programda kullanılan fonksiyonların prototipleri tanımlandı.
bool firma_kontrol(string firmaNo);
bool siparis_kontrol(string siparisNo);
void urun_ekle();
void urun_arama(string urunKodu);
void urun_listele();
void urun_duzeltme(string urunKodu);
void urun_sil(string urunKodu);
void musteri_ekle();
void musteri_ara(string firmaNo);
void musteri_duzeltme(string firmaNo);
void musteri_silme(string firmaNo);
void siparis_olustur();
void siparis_arama(string siparisNo);
void siparis_sil(string siparisNo);
void siparis_duzelt(string siparisNo);
void siparis_rapor();

enum RENKLER		// Renkli satir kullanimi icin eklendi.
{
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15,
};

int secim;

struct urungirisi											// Urun girisinin saklanacagi yapi parametreleri yer almaktadir.
{
	string urunKodu, urunAd, uretici, temin, uretimTarihi, fiyat, fiyatOzel, kdv, stok;
} urun;

struct firmagirisi											// Firma girisinin saklanacagi yapi parametreleri yer almaktadir.
{
	string no, ad, tel, sorumlu, kategori, adres;
} firma;

struct siparisgiris											// Siparis listesinde saklanacak yapi parametreleri yer almaktadir.
{
	string tutar, tarih, adet, alan, numara;
} siparis;

void menu()													// Secim menüsü için void() fonksiyonu uzerinde yapilmaktadir.
{
	string urunKodu;
	string firmaNo;
	string musteriNo;
	string siparisNo;
	urunKodu = "";
	firmaNo = "";
	musteriNo = "";
	siparisNo = "";
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	cout << "1. Urun Ekleme"	<< setw(49)	<< "10. Siparis Olustur" << endl;
	cout << "2. Urun Arama"		<< setw(48)	<< "11. Siparis Arama" << endl;
	cout << "3. Urun Listeleme" << setw(44) << "12. Siparis Silme" << endl;
	cout << "4. Urun Duzeltme"	<< setw(48)	<< "13. Siparis Duzeltme" << endl;
	cout << "5. Urun Silme"		<< setw(52)	<< "14. Siparis Raporlama" << endl;
	cout << "6. Musteri Ekle"	<< endl;
	cout << "7. Musteri Arama"	 << endl;
	cout << "8. Musteri Duzeltme" << endl;
	cout << "9. Musteri Silme" << setw(40) << "15. Cikis..." << endl;
	cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREEN);
	cout << "Seciminiz: "; cin >> secim;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	
	switch (secim)
			{
			case 1:
				urun_ekle();
				break;
			case 2:
				cout << "Urun arama \nUrun Kodu: "; cin >> urunKodu;
				urun_arama(urunKodu);
				break;
			case 3:
				urun_listele();
				break;
			case 4:
				cout << "Urun duzeltme \nUrun Kodu: "; cin >> urunKodu;
				urun_duzeltme(urunKodu);
				break;
			case 5:
				cout << "Urun silme \nUrun Kodu: "; cin >> urunKodu;
				urun_sil(urunKodu);
				break;
			case 6:
				musteri_ekle();
				break;
			case 7:
				cout << "Musteri arama \nMusteri No: "; cin >> firmaNo;
				musteri_ara(firmaNo);
				break;
			case 8:
				cout << "Musteri duzeltme \nMusteri No: "; cin >> firmaNo;
				musteri_duzeltme(firmaNo);
				break;
			case 9:
				cout << "Musteri silme \nMusteri No: "; cin >> firmaNo;
				musteri_silme(firmaNo);
				break;
			case 10:
				siparis_olustur();
				break;
			case 11:
				cout << "Siparis arama \nSiparis No: "; cin >> siparisNo;
				siparis_arama(siparisNo);
				break;
			case 12:
				cout << "Siparis sil \nSiparis No: "; cin >> siparisNo;
				siparis_sil(siparisNo);
				break;
			case 13:
				cout << "Siparis duzeltme \nSiparis No: "; cin >> siparisNo;
				siparis_duzelt(siparisNo);
				break;
			case 14:
				siparis_rapor();
				break;
			case 15:
				break;
			default: cout << "Boyle bir islem bulunmamaktadir. Lutfen gecerli bir islem deneyin!\a" << endl;
				break;
			}
	
}

bool urun_kontrol(string urunKodu)							// Urun kayit bilgisi sorgulamasi yapan fonksiyondur.
{
	bool kontrol = 0;										// urunKodu bilgisi kayitli degilse 0 degeri kalir, urun varsa deger 1 olur.
	ifstream dosyaoku;
	dosyaoku.open("urun.txt");

	while (!dosyaoku.eof())
	{
		dosyaoku >> urun.urunKodu >> urun.urunAd >> urun.uretici >> urun.temin 
				 >> urun.uretimTarihi >> urun.fiyat >> urun.fiyatOzel >> urun.kdv >> urun.stok;

		if (urun.urunKodu == urunKodu)
		{
			kontrol = 1;
		}
	}
	return kontrol;
}

bool firma_kontrol(string firmaNo)							// Firma bilgileri ile ilgili islem yapilacaginda cagirilan firma kontrol fonksiyonudur.
{
	bool kontrol = 0;										// Baslangicta 0 degerini almaktadir. Firma kayitli ise 1 degeri alır.
	ifstream dosyaoku;
	dosyaoku.open("cari.txt");

	while (!dosyaoku.eof())
	{
		dosyaoku >> firma.no >> firma.ad >> firma.tel >> firma.sorumlu >> firma.kategori >> firma.adres;

		if (firma.no == firmaNo)
		{
			kontrol = 1;
		}
	}
	return kontrol;
}

bool siparis_kontrol(string siparisNo)						// Siparis kaydi olusturulacaginda cagirilan kontrol fonksiyonudur, essiz deger alir.
{
	bool kontrol = 0;										// Baslangicta 0 degerini almaktadir. Siparis mevcut ise 1 degeri alır.
	ifstream dosyaoku;
	dosyaoku.open("liste.txt");

	while (!dosyaoku.eof())
	{
		dosyaoku >> siparis.numara >> urun.urunKodu >> siparis.adet >> siparis.tarih;
		

		if (siparis.numara == siparisNo)
		{
			kontrol = 1;
		}
	}
	return kontrol;
}

void urun_ekle()											// Programa urun eklenmesini ve bu urunu dosya uzerine kaydetmeyi saglayan fonksiyondur.
{
	string urunKodu;
	ofstream dosyayaz;
	dosyayaz.open("urun.txt",ios::out|ios::in|ios::app);

	cout << "Urun ekle \nUrun Kodu............: "; cin >> urunKodu;

	if (urun_kontrol(urunKodu) == 1)						// Kayit kontrol fonksiyonu cagirilarak urun kaydi sorgulanmaktadir.
	{
		cout << "Bu urun koduna sahip bir urun bulunmaktadir!\n";
	}

	else
	{
		urun.urunKodu = urunKodu;
		cout << "Urun adi.............: "; cin >> urun.urunAd;
		cout << "Urunun ureticisi.....: "; cin >> urun.uretici;
		cout << "Temin suresi.........: "; cin >> urun.temin;
		cout << "Uretim tarihi........: "; cin >> urun.uretimTarihi;
		cout << "Urun fiyati (genel)..: "; cin >> urun.fiyat;
		cout << "Urun fiyati (ozel)...: "; cin >> urun.fiyatOzel;
		cout << "KDV orani............: "; cin >> urun.kdv;
		cout << "Stok adedi...........: "; cin >> urun.stok;
		dosyayaz << urun.urunKodu << setw(20) << urun.urunAd << setw(20) << urun.uretici << setw(20) << urun.temin << setw(20) << urun.uretimTarihi 
				 << setw(20) << urun.fiyat << setw(20) << urun.fiyatOzel << setw(20) << urun.kdv << setw(20) << urun.stok << "\n";
	
		cout << "Urun eklendi!\n";
	}
	dosyayaz.close();
}

void urun_arama(string urunKodu)							// Dosyada kayitli urunun kod numarasina gore aranmasini saglamaktadir.
{
	ifstream dosyaoku;
	dosyaoku.open("urun.txt", ios::app);					// Yalnizca okuma yapilacak sekilde dosya acilmistir.

	if (urun_kontrol(urunKodu) == 0)						// Urun kontrol fonksiyonu ile kayit sorgulanir.
	{
		cout << "Kayit bulunamadi.\n";
	}
	else
	{
		if (urun_kontrol(urunKodu) == 1)					// Aranan koda sahip bir urun varsa okuma islemi baslatilir.
		{
			// Dosya icinde yer alan son satir cagirildiginda iki defa ekrana yazdirilmamasi icin dosyaoku komutu while icerisinde cagirilmistir.
			while (dosyaoku >> urun.urunKodu >> urun.urunAd >> urun.uretici >> urun.temin >> urun.uretimTarihi >> urun.fiyat >> urun.fiyatOzel >> urun.kdv >> urun.stok)
			{
				if (urun.urunKodu == urunKodu)
				{
					cout << "Urun adi.............: " << urun.urunAd << endl;
					cout << "Urunun ureticisi.....: " << urun.uretici << endl;
					cout << "Temin suresi.........: " << urun.temin << endl;
					cout << "Uretim tarihi........: " << urun.uretimTarihi << endl;
					cout << "Urun fiyati (genel)..: " << urun.fiyat << endl;
					cout << "Urun fiyati (ozel)...: " << urun.fiyatOzel << endl;
					cout << "KDV orani............: " << urun.kdv << endl;
					cout << "Stok adedi...........: " << urun.stok << endl;
				}
				
			}
		}
	}
	dosyaoku.close();
}

void urun_listele()											// Dosyada yer alan urunleri gosteren fonksiyondur.
{
	ifstream dosyaoku;
	dosyaoku.open("urun.txt", ios::app);

	cout << "-Urun Kodu-" << setw(20) << "-Urun adi-" << setw(20) << "-Uretici-" << setw(20) << "-Temin suresi-" << setw(20) << "-Uretim tarihi-" << setw(20) 
		 << "-Fiyat-" << setw(20) << "-Ozel fiyat-" << setw(20) << "-KDV-" << setw(20) << "-Stok miktari-\n";
	while (dosyaoku >> urun.urunKodu >> urun.urunAd >> urun.uretici >> urun.temin >> urun.uretimTarihi >> urun.fiyat >> urun.fiyatOzel >> urun.kdv >> urun.stok)
	{
		cout << setw(10) << urun.urunKodu << setw(20) << urun.urunAd << setw(20) << urun.uretici << setw(20) << urun.temin << setw(20) 
			 << urun.uretimTarihi << setw(20) << urun.fiyat << setw(20) << urun.fiyatOzel << setw(20) << urun.kdv << setw(20) << urun.stok << "\n";
	}
	dosyaoku.close();
}

void urun_duzeltme(string urunKodu)							// Urun kaydinin  istenen urun uzerinde duzenlenmesini saglayan fonksiyondur.
{
	ifstream dosyaoku;
	ofstream dosyayaz;
	dosyaoku.open("urun.txt");
	dosyayaz.open("urun_duzenle.txt", ios::app);

	bool kontrol = 0;

	if (urun_kontrol(urunKodu) == 0)						// Kayit kontrol fonksiyonu cagirilarak urun kaydi sorgulanir.
	{
		cout << "Boyle bir urun bulunamadi!\n\a";
	}
	else
	{
		kontrol = 1;
		while (dosyaoku >> urun.urunKodu >> urun.urunAd >> urun.uretici >> urun.temin >> urun.uretimTarihi >> urun.fiyat >> urun.fiyatOzel >> urun.kdv >> urun.stok)
		{
			if (urun.urunKodu == urunKodu)
			{
				cout << "Urun kodu............: " << urun.urunKodu <<  "\nUrun adi.............: " << urun.urunAd 
					 << "\nUrunun ureticisi.....: " << urun.uretici << "\nTemin suresi.........: " << urun.temin 
					 << "\nUretim tarihi........: " << urun.uretimTarihi << "\nUrun fiyati (genel)..: " 
					 << urun.fiyat << "\nUrun fiyati (ozel)...: " << urun.fiyatOzel << "\nKDV orani............: "
					 << urun.kdv << "\nStok adedi...........: " << urun.stok << "\n\nYeni bilgiler;\n";

				cout << "Urun adi.............: "; cin >> urun.urunAd;
				cout << "Urunun ureticisi.....: "; cin >> urun.uretici;
				cout << "Temin suresi.........: "; cin >> urun.temin;
				cout << "Uretim tarihi........: "; cin >> urun.uretimTarihi;
				cout << "Urun fiyati (genel)..: "; cin >> urun.fiyat;
				cout << "Urun fiyati (ozel)...: "; cin >> urun.fiyatOzel;
				cout << "KDV orani............: "; cin >> urun.kdv;
				cout << "Stok adedi...........: "; cin >> urun.stok;
					
				dosyayaz << urun.urunKodu << setw(20) << urun.urunAd << setw(20) << urun.uretici << setw(20) << urun.temin << setw(20) 
						 << urun.uretimTarihi << setw(20) << urun.fiyat << setw(20) << urun.fiyatOzel << setw(20) << urun.kdv << setw(20) << urun.stok << "\n";
			}
			else
			{ 
				dosyayaz << urun.urunKodu << setw(20) << urun.urunAd << setw(20) << urun.uretici << setw(20) << urun.temin << setw(20)
						 << urun.uretimTarihi << setw(20) << urun.fiyat << setw(20) << urun.fiyatOzel << setw(20) << urun.kdv << setw(20) << urun.stok << "\n";
			}
		}
		dosyaoku.close();
		dosyayaz.close();

		if (kontrol == 1)					// Dosya uzerinde degisiklik yapildiysa kaydin tutulmasini saglamaktadir.
		{
			remove("urun.txt");
			rename("urun_duzenle.txt", "urun.txt");
			cout << "Urun bilgileri guncellendi!\n";
		}
		else
		{
			remove("urun_duzenle.txt");
		}
	}
}

void urun_sil(string urunKodu)								// Secilen urunun kaydini silen fonksiyon.
{
	ifstream dosyaoku;
	ofstream dosyayaz;
	dosyaoku.open("urun.txt");
	dosyayaz.open("gecici_urun.txt", ios::app);

	bool degisim_kontrol = 0;								// Dosya uzerinde degisim yapilma durumunu kontrol eder, degisim yapildinda deger 1 olarak degistirilir. 

	if (urun_kontrol(urunKodu) == 0)						// Urun kontrol fonksiyonuyla urunun kaydi sorgulanir.
	{
		cout << "Boyle bir urun kodu bulunamadi!\n";
	}
	else
	{
		degisim_kontrol = 1;
		while (dosyaoku >> urun.urunKodu >> urun.urunAd >> urun.uretici >> urun.temin >> urun.uretimTarihi >> urun.fiyat >> urun.fiyatOzel >> urun.kdv >> urun.stok)
		{
			if (urun.urunKodu != urunKodu)
			{
				dosyayaz << urun.urunKodu << setw(20) << urun.urunAd << setw(20) << urun.uretici << setw(20) << urun.temin << setw(20)
					<< urun.uretimTarihi << setw(20) << urun.fiyat << setw(20) << urun.fiyatOzel << setw(20) << urun.kdv << setw(20) << urun.stok << "\n";
			}
		}
	}
	dosyaoku.close();
	dosyayaz.close();

	if (degisim_kontrol == 1)								// Dosya uzerinde degisiklik yapildiysa eski dosya silinir, gecici dosyanin adi degistirilir.
	{
		remove("urun.txt");
		rename("gecici_urun.txt", "urun.txt");
		cout << "Kayit silindi!\n";
	}
	else
	{
		remove("gecici_urun.txt");
	}
}

void musteri_ekle()											// Cari dosyasina musteri eklemek icin bu fonksiyon kullanilir. 
{
	string firmaNo;
	ofstream dosyayaz;
	dosyayaz.open("cari.txt", ios::app);

	cout << "Firma ekle \nFirma No..............: "; cin >> firmaNo;

	if (firma_kontrol(firmaNo) == 1)						// Firma kontrol fonksiyonu vasitasiyla firma kaydi sorgulanir.
	{
		cout << "Bu numaraya sahip bir firma bulunmaktadir!\n\a";
	}

	else
	{
		firma.no = firmaNo;
		cout << "Firma adi.............: "; cin >> firma.ad;
		cout << "Firma telefonu........: "; cin >> firma.tel;
		cout << "Firma sorumlusu.......: "; cin >> firma.sorumlu;
		cout << "Musteri kategorisi....: "; cin >> firma.kategori;
		cout << "Firma adresi..........: "; cin >> firma.adres;
		dosyayaz << firma.no << setw(20) << firma.ad << setw(20) << firma.tel << setw(20) << firma.sorumlu << setw(20) << firma.kategori << setw(20) << firma.adres << "\n";
		cout << "Firma eklendi!\n";
	}
	dosyayaz.close();
}

void musteri_ara(string firmaNo)							// Musteri aramasi yapmak icin bu fonksiyon kullanilir. 
{
	ifstream dosyaoku;
	dosyaoku.open("cari.txt", ios::app);

	if (firma_kontrol(firmaNo) == 0)						// Firma kontrol fonksiyonu cagirilir ve urun kaydi sorgulanir.
	{
		cout << "Kayit bulunamadi.\n";
	}
	else
	{
		if (firma_kontrol(firmaNo) == 1)
		{
			while (dosyaoku >> firma.no >> firma.ad >> firma.tel >> firma.sorumlu >> firma.kategori >> firma.adres)
			{
				if (firma.no == firmaNo)
				{
					cout << "Firma adi.............: " << firma.ad << endl;
					cout << "Firma telefonu........: " << firma.tel << endl;
					cout << "Firma sorumlusu.......: " << firma.sorumlu << endl;
					cout << "Musteri kategorisi....: " << firma.kategori << endl;
					cout << "Firma adresi..........: " << firma.adres << endl;
				}
			}
		}
	}
	dosyaoku.close();
}

void musteri_duzeltme(string firmaNo)						// Musteriler uzerinde duzenleme yapilmasini saglayan fonksiyondur.
{
	ifstream dosyaoku;
	ofstream dosyayaz;
	dosyaoku.open("cari.txt");
	dosyayaz.open("cari_duzenle.txt", ios::app);

	bool kontrol = 0;

	if (firma_kontrol(firmaNo) == 0) 
	{
		cout << "Boyle bir firma bulunamadi!\n\a";
	}
	else
	{
		kontrol = 1;
		while (dosyaoku >> firma.no >> firma.ad >> firma.tel >> firma.sorumlu >> firma.kategori >> firma.adres)
		{
			if (firma.no == firmaNo)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTCYAN);
				cout << firma.no << " numarali firma uzerinde degisiklik yapilacaktir!\n" << "\nFirma Adi.............: " << firma.ad << "\nFirma Telefonu........: " << firma.tel << "\nFirma Sorumlusu.......: " << firma.sorumlu << "\nFirma Kategorisi......: " << firma.kategori << "\nFirma Adresi..........: " << firma.adres << "\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

				cout << "Firma adi.............: "; cin >> firma.ad;
				cout << "Firma telefonu........: "; cin >> firma.tel;
				cout << "Firma sorumlusu.......: "; cin >> firma.sorumlu;
				cout << "Musteri kategorisi....: "; cin >> firma.kategori;
				cout << "Firma adresi..........: "; cin >> firma.adres;
				dosyayaz << firma.no << setw(20) << firma.ad << setw(20) << firma.tel << setw(20) << firma.sorumlu << setw(20) << firma.kategori << setw(20) << firma.adres << "\n";

			}
			else
			{
				dosyayaz << firma.no << setw(20) << firma.ad << setw(20) << firma.tel << setw(20) << firma.sorumlu << setw(20) << firma.kategori << setw(20) << firma.adres << "\n";
			}

		}
		dosyaoku.close();
		dosyayaz.close();

		if (kontrol == 1)									// Dosya uzerinde degisiklik yapildiginda gecici dosyanin ismini degistirerek kaydeder, ilk dosyayi siler.
		{
			remove("cari.txt");
			rename("cari_duzenle.txt", "cari.txt");
			cout << "Musteri bilgileri guncellendi!\n";
		}
		else
		{
			remove("cari_duzenle.txt");
		}

	}
}

void musteri_silme(string firmaNo)							// Dosyada yer alan firma kaydinin silinmesini saglayan fonksiyondur.
{
	ifstream dosyaoku;
	ofstream dosyayaz;
	dosyaoku.open("cari.txt");
	dosyayaz.open("gecici_cari.txt", ios::app);

	bool degisim_kontrol = 0;								// Dosya uzerinde degisim yapilma durumunu kontrol eder, degisim yapildinda deger 1 olarak degistirilir. 

	if (firma_kontrol(firmaNo) == 0)						// Firma kontrol fonksiyonu cagirilarak firma kaydir sorgulanir.
	{
		cout << "Boyle bir firma kodu bulunamadi!\n\a";
	}
	else
	{
		degisim_kontrol = 1;
		while (dosyaoku >> firma.no >> firma.ad >> firma.tel >> firma.sorumlu >> firma.kategori >> firma.adres)
		{
			if (firma.no != firmaNo)
			{
				dosyayaz << firma.no << setw(20) << firma.ad << setw(20) << firma.tel << setw(20) << firma.sorumlu << setw(20) << firma.kategori << setw(20) << firma.adres << "\n";
			}
		}
	}
	dosyaoku.close();
	dosyayaz.close();

	if (degisim_kontrol == 1)								// Dosya icinde bir kayit silindiyse dosya ismi degistirilir ve gecici dosya silinir.
	{
		remove("cari.txt");
		rename("gecici_cari.txt", "cari.txt");
		cout << "Kayit silindi!\n";
	}
	else
	{
		remove("gecici_cari.txt");
	}
}

void siparis_olustur()
{
	string firmaNo;
	string urunKodu;
	string siparisNo;
	ifstream dosyaoku;
	ofstream dosyayaz, dosyayazliste;
	dosyaoku.open("urun.txt");
	dosyayaz.open("siparis.txt", ios::app);
	dosyayazliste.open("liste.txt", ios::app);

	cout << "Siparis Olusturma\n Siparis No: "; cin >> siparisNo;

	if (siparis_kontrol(siparisNo) == 1)
	{
		cout << "Bu numarada bir siparis vardir, lutfen yeni siparis numarasi giriniz;\n";
	}
	else
	{
		cout << "Firma numarasi........: "; cin >> firmaNo;

		if (firma_kontrol(firmaNo) == 0)
	{
		cout << "Kayit bulunamadi. Yeni firma kaydi olusturun;\n";
		musteri_ekle();
	}
		
		siparis.numara = siparisNo;
		firma.no = firmaNo;
		cout << "Siparis tarihi........: "; cin >> siparis.tarih;
		cout << "Siparis tutari........: "; cin >> siparis.tutar;
		cout << "Urun kodu.............: "; cin >> urunKodu;
		
		if (urun_kontrol(urunKodu) == 0)
	{
		cout << "Kayit bulunamadi. Yeni urun kaydi olusturun;\n";
		urun_ekle();
	}
		
		cout << "Urun adedi............: "; cin >> siparis.adet;
		cout << "Siparisi alan.........: "; cin >> siparis.alan;
	

		dosyayaz << firma.no << setw(20) << siparis.tarih << setw(20) << siparis.tutar << setw(20)
				 << urunKodu << setw(20) << siparis.adet << setw(20) << siparis.alan << setw(20) << siparis.numara << "\n";

		dosyayazliste << siparis.numara << setw(20) << urun.urunKodu << setw(20) << siparis.adet << setw(20) << siparis.tarih << "\n";
		
		cout << "Siparis olusturuldu\n";
	}
	dosyayaz.close();
	dosyayazliste.close();
	dosyaoku.close();
}

void siparis_arama(string siparisNo)							// Siparis aramasi yapmak icin bu fonksiyon kullanilir. 
{
	ifstream dosyaoku;
	dosyaoku.open("liste.txt", ios::app);

	if (siparis_kontrol(siparisNo) == 0)						// Siparis kontrol fonksiyonu cagirilir ve siparis kaydi sorgulanir.
	{
		cout << "Kayit bulunamadi.\n";
	}
	else
	{
		if (siparis_kontrol(siparisNo) == 1)
		{
			while (dosyaoku >> siparis.numara >> urun.urunKodu >> siparis.adet >> siparis.tarih)
			{
				if (siparis.numara == siparisNo)
				{
					cout << "Siparis numarasi......: " << siparis.numara << endl;
					cout << "Urun kodu.............: " << urun.urunKodu << endl;
					cout << "Siparis adedi.........: " << siparis.adet << endl;
					cout << "Siparis tarihi........: " << siparis.tarih << endl;
				}
			}
		}
	}
	dosyaoku.close();
}

void siparis_sil(string siparisNo)						// Dosyada yer alan siparis kaydinin silinmesini saglayan fonksiyondur.
{
	ifstream dosyaoku;
	ofstream dosyayaz;
	dosyaoku.open("liste.txt");
	dosyayaz.open("gecici_liste.txt", ios::app);

	bool degisim_kontrol = 0;								// Dosya uzerinde degisim yapilma durumunu kontrol eder, degisim yapildinda deger 1 olarak degistirilir. 

	if (siparis_kontrol(siparisNo) == 0)						// Siparis kontrol fonksiyonu cagirilarak siparis kaydir sorgulanir.
	{
		cout << "Boyle bir siparis bulunamadi!\n\a";
	}
	else
	{
		degisim_kontrol = 1;
		while (dosyaoku >> siparis.numara >> urun.urunKodu >> siparis.adet >> siparis.tarih)
		{
			if (siparis.numara != siparisNo)
			{
				dosyayaz << siparis.numara << setw(20) << urun.urunKodu << setw(20) << siparis.adet << setw(20) << siparis.tarih << "\n";
			}
		}
	}
	dosyaoku.close();
	dosyayaz.close();

	if (degisim_kontrol == 1)								// Dosya icinde bir kayit silindiyse dosya ismi degistirilir ve gecici dosya silinir.
	{
		remove("liste.txt");
		rename("gecici_liste.txt", "liste.txt");
		cout << "Kayit silindi!\n";
	}
	else
	{
		remove("gecici_liste.txt");
	}
}

void siparis_duzelt(string siparisNo)						// Siparis duzeltme fonksiyonudur, siparis numarasi degistirilemez.
{
	ifstream dosyaoku;
	ofstream dosyayazliste;
	ofstream dosyayaz;
	dosyaoku.open("siparis.txt");
	dosyayazliste.open("liste_duzenle.txt", ios::app);
	dosyayaz.open("siparis_duzenle.txt", ios::app);

	bool kontrol = 0;

	if (siparis_kontrol(siparisNo) == 0)
	{
		cout << "Boyle bir siparis bulunamadi!\n\a";
	}
	else
	{
		kontrol = 1;
		while (dosyaoku >> firma.no >> siparis.tarih >> siparis.tutar >> urun.urunKodu >> siparis.adet >> siparis.alan >> siparis.numara)
		{
			if (siparis.numara == siparisNo)
			{
				cout << siparisNo << " numarali siparis uzerinde degisiklik yapilacaktir!\n" 
					<< "\nFirma numarasi........: " << firma.no << "\nSiparis tarihi........: " << siparis.tarih << "\nSiparis tutari........: " << siparis.tutar 
					<< "\nUrun kodu.............: " << urun.urunKodu << "\nSiparis adedi.........: " << siparis.adet << "\nSiparisi alan.........: " << siparis.alan 
					<< "\nSiparis numarasi......: " << siparis.numara <<"\nYeni siparis bilgileri;\n";

				cout << "Firma numarasi........: "; cin >> firma.no;
				cout << "Siparis tarihi........: "; cin >> siparis.tarih;
				cout << "Siparis tutari........: "; cin >> siparis.tutar;
				cout << "Urun kodu.............: "; cin >> urun.urunKodu;
				cout << "Siparis adedi.........: "; cin >> siparis.adet;
				cout << "Siparisi alan.........: "; cin >> siparis.alan;
				
				dosyayaz << firma.no << setw(20) << siparis.tarih << setw(20) << siparis.tutar << setw(20) << urun.urunKodu << setw(20) << siparis.adet 
						 << setw(20) << siparis.alan << setw(20) << siparis.numara << "\n";

				dosyayazliste << siparis.numara << setw(20) << urun.urunKodu << setw(20) << siparis.adet << setw(20) << siparis.tarih << "\n";
			}
			else
			{
				dosyayaz << firma.no << setw(20) << siparis.tarih << setw(20) << siparis.tutar << setw(20) << urun.urunKodu << setw(20) << siparis.adet
						 << setw(20) << siparis.alan << setw(20) << siparis.numara << "\n";

				dosyayazliste << siparis.numara << setw(20) << urun.urunKodu << setw(20) << siparis.adet << setw(20) << siparis.tarih << "\n";
			}

		}
		dosyaoku.close();
		dosyayaz.close();
		dosyayazliste.close();

		if (kontrol == 1)									// Dosya uzerinde degisiklik yapildiginda gecici dosyanin ismini degistirerek kaydeder, ilk dosyayi siler.
		{
			remove("siparis.txt");
			remove("liste.txt");
			rename("siparis_duzenle.txt", "siparis.txt");
			rename("liste_duzenle.txt", "liste.txt");
			cout << "Siparis bilgileri guncellendi!\n";
		}
		else
		{
			remove("siparis_duzenle.txt");
			remove("liste_duzenle");
		}
	}
	
}

void siparis_rapor()
{
	ifstream dosyaoku;
	dosyaoku.open("liste.txt", ios::app);

	cout << "-Siparis numarasi-" << setw(20) << "-Urun kodu-" << setw(20) << "-Siparis adedi-" << setw(20) << "-Siparis tarihi-\n";
	while (dosyaoku >> siparis.numara >> urun.urunKodu >> siparis.adet >> siparis.tarih)
	{
		cout << setw(10) << siparis.numara << setw(20) << urun.urunKodu << setw(20) << siparis.adet << setw(20) << siparis.tarih << "\n";
	}
	dosyaoku.close();
}

int main()
{
	while (secim != 15)
	{
		system("cls");
		menu();
		system("pause");
	}
	return 0;
}
