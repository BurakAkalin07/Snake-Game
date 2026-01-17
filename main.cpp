#include <iostream>
#include "yilan.hpp"
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;


const int yukseklik = 20;
const int genislik = 40; 
const int engelSayisi = 10; 

int yemX;
int yemY;
int yuksekSkor = 0;
vector<Nokta> engeller; 

void RenkDegistir(int renkKodu)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), renkKodu);
}

void ImleciBasaAl()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
}

void ImleciGizle()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void YuksekSkoruOku()
{
    ifstream dosyaOku("skor.txt");
    if (dosyaOku.is_open())
    {
        dosyaOku >> yuksekSkor;
        dosyaOku.close();
    }
    else yuksekSkor = 0;
}

void YuksekSkoruKaydet(int anlikSkor)
{
    if (anlikSkor > yuksekSkor)
    {
        yuksekSkor = anlikSkor;
        ofstream dosyaYaz("skor.txt");
        if (dosyaYaz.is_open())
        {
            dosyaYaz << yuksekSkor;
            dosyaYaz.close();
        }
    }
}


void EngelleriOlustur(Yilan& yilan)
{
    engeller.clear(); 
    for(int i = 0; i < engelSayisi; i++)
    {
        Nokta yeniEngel;
        bool cakismaVar = true;

        while(cakismaVar)
        {
            cakismaVar = false;
            yeniEngel.x = rand() % genislik;
            yeniEngel.y = rand() % yukseklik;

            if (yeniEngel.x == yilan.getKafa().x && yeniEngel.y == yilan.getKafa().y) cakismaVar = true;
            if (yeniEngel.x == yemX && yeniEngel.y == yemY) cakismaVar = true;
            if (abs(yeniEngel.x - genislik/2) < 3 && abs(yeniEngel.y - yukseklik/2) < 3) cakismaVar = true;
        }
        engeller.push_back(yeniEngel);
    }
}


void GirisEkrani()
{
    system("cls");
    RenkDegistir(10); 
    cout << "\n\n";
    cout << "\t   __   __  ___   __      _______  __   __ \n";
    cout << "\t  |  | |  ||   | |  |    |   _   ||  | |  |\n";
    cout << "\t  |  |_|  ||   | |  |    |  |_|  ||   ||  |\n";
    cout << "\t  |       ||   | |  |    |       ||       |\n";
    cout << "\t  |_     _||   | |  |___ |       ||       |\n";
    cout << "\t    |___|  |___| |_______||___|___||__|___|\n\n";
    
    RenkDegistir(7); 
    cout << "\t\t   HOS GELDINIZ!\n\n";
    cout << "\t       Hareket: W, A, S, D\n";
    cout << "\t       Cikis:   X\n\n";
    
    RenkDegistir(8); 
    cout << "\t       Dikkat: 'X' isaretli bloklar ENGELDIR!\n\n";

    RenkDegistir(7);
    cout << "\t    Baslamak icin ENTER'a bas...";

    while (_getch() != 13);
    system("cls");
}

void Ciz(Yilan& yilan)
{
    ImleciBasaAl(); 

    RenkDegistir(7); 
    for(int a = 0; a < genislik + 2; a++) cout << "#";
    cout << endl;

    for (int i = 0; i < yukseklik; i++)
    {
        for (int j = 0; j < genislik; j++)
        {
            if (j == 0) { RenkDegistir(7); cout << "#"; } 

            else if (i == yilan.getKafa().y && j == yilan.getKafa().x)
            {
                RenkDegistir(10); cout << "O"; 
            }
            else if (i == yemY && j == yemX)
            {
                RenkDegistir(12); cout << "F"; 
            }
            else
            {
                bool doluMu = false;

               
                for (int k = 0; k < yilan.getKuyruk().size(); k++)
                {
                    if (yilan.getKuyruk()[k].x == j && yilan.getKuyruk()[k].y == i)
                    {
                        RenkDegistir(2); cout << "o"; 
                        doluMu = true;
                        break;
                    }
                }

                
                if (!doluMu)
                {
                    for(int e = 0; e < engeller.size(); e++)
                    {
                        if(engeller[e].x == j && engeller[e].y == i)
                        {
                            RenkDegistir(8); 
                            cout << "X"; 
                            doluMu = true;
                            break;
                        }
                    }
                }

                if (!doluMu) cout << " "; 
            }

            if (j == genislik - 1) { RenkDegistir(7); cout << "#"; } 
        }
        cout << endl;
    }

    RenkDegistir(7);
    for (int a = 0; a < genislik + 2; a++) cout << "#";
    cout << endl;
    
    RenkDegistir(14); 
    cout << "Skor: " << yilan.getKuyruk().size() * 10;
    RenkDegistir(11); 
    cout << "\tRekor: " << yuksekSkor << "      " << endl;
}

int main()
{
    srand(time(NULL));
    ImleciGizle();
    YuksekSkoruOku();

    bool programAcik = true;

    while (programAcik)
    {
        GirisEkrani(); 

        Yilan yilan(genislik / 2, yukseklik / 2);
        yemX = rand() % genislik;
        yemY = rand() % yukseklik;
        
        EngelleriOlustur(yilan);

        bool oyunDevamEdiyor = true;

        while (oyunDevamEdiyor)
        {
            Ciz(yilan);

            if (_kbhit()) 
            {
                char tus = _getch();
                switch (tus) 
                {
                case 'a': yilan.YonDegistir(SOL); break;
                case 'd': yilan.YonDegistir(SAG); break;
                case 'w': yilan.YonDegistir(YUKARI); break;
                case 's': yilan.YonDegistir(ASAGI); break;
                case 'x': oyunDevamEdiyor = false; programAcik = false; break; 
                }
            }

            yilan.HareketEt();

            if (yilan.getKafa().x == yemX && yilan.getKafa().y == yemY)
            {
                yilan.Buyu();
                
                bool yemEngelde = true;
                while(yemEngelde)
                {
                    yemEngelde = false;
                    yemX = rand() % genislik;
                    yemY = rand() % yukseklik;
                    for(auto engel : engeller) 
                        if(engel.x == yemX && engel.y == yemY) yemEngelde = true;
                }
            }

            if (yilan.CarpismaVarMi(genislik, yukseklik, engeller))
            {
                int sonSkor = yilan.getKuyruk().size() * 10;
                YuksekSkoruKaydet(sonSkor); 

                ImleciBasaAl();
                for(int k = 0; k < yukseklik + 3; k++) cout << endl;
                
                RenkDegistir(12); 
                cout << "\tOYUN BITTI! SKORUNUZ: " << sonSkor << endl;
                if(sonSkor >= yuksekSkor && sonSkor > 0) cout << "\tTEBRIKLER! YENI REKOR!" << endl;
                
                RenkDegistir(7);
                cout << "\tTekrar oynamak icin 'R', Cikis icin 'X' basin..." << endl;

                while (true)
                {
                    char secim = _getch();
                    if (secim == 'r' || secim == 'R') 
                    {
                        oyunDevamEdiyor = false; 
                        break; 
                    }
                    if (secim == 'x' || secim == 'X')
                    {
                        oyunDevamEdiyor = false;
                        programAcik = false; 
                        break;
                    }
                }
            }

            Sleep(150); 
        }
    }
    return 0;
}