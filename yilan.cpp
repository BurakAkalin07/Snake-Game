#include "yilan.hpp"
#include <vector>


using namespace std; 


Yilan::Yilan(int baslangicX, int baslangicY)
{
    kafa.x = baslangicX;
    kafa.y = baslangicY;
    suankiYon = DUR; 

    kuyruk.push_back({baslangicX - 1, baslangicY});
}

void Yilan::HareketEt()
{
    if (suankiYon == DUR) return;

    
    for (int a = kuyruk.size() - 1; a > 0; a--)
    {
        kuyruk[a] = kuyruk[a - 1];
    }
    kuyruk[0] = kafa;

    
    switch (suankiYon)
    {
    case YUKARI: kafa.y--; break;
    case ASAGI:  kafa.y++; break;
    case SOL:    kafa.x--; break;
    case SAG:    kafa.x++; break;
    default: break;
    }
}

void Yilan::YonDegistir(Yon yeniYon)
{
    if (suankiYon == YUKARI && yeniYon == ASAGI) return;
    if (suankiYon == ASAGI && yeniYon == YUKARI) return;
    if (suankiYon == SOL && yeniYon == SAG) return;
    if (suankiYon == SAG && yeniYon == SOL) return;

    suankiYon = yeniYon;
}

void Yilan::Buyu()
{
    kuyruk.push_back({-1, -1});
}

bool Yilan::CarpismaVarMi(int genislik, int yukseklik, const std::vector<Nokta>& engeller)
{
   
    if (kafa.x < 0 || kafa.x >= genislik) return true;
    if (kafa.y < 0 || kafa.y >= yukseklik) return true;

    
    for (int i = 0; i < kuyruk.size(); i++)
    {
        if (kafa.x == kuyruk[i].x && kafa.y == kuyruk[i].y)
            return true; 
    }

    
    for (int i = 0; i < engeller.size(); i++)
    {
       
        if (kafa.x == engeller[i].x && kafa.y == engeller[i].y)
            return true;
    }

    return false;
}