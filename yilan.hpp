#ifndef Yilan_hpp
#define Yilan_hpp
#include <vector>

class Nokta 
{
    public:
        int x;
        int y;
};

enum Yon {DUR=0, SOL, SAG, YUKARI, ASAGI};

class Yilan 
{
    private: 
        Nokta kafa;
        std::vector<Nokta> kuyruk;
        Yon suankiYon;
    
    public:
        
        Yilan(int baslangicX, int baslangicY);

        
        void HareketEt();
        void YonDegistir(Yon);
        void Buyu();
        bool CarpismaVarMi(int genislik, int yukseklik, const std::vector<Nokta>& engeller);

        Nokta getKafa() const {return kafa;}
        const std::vector<Nokta>& getKuyruk() const {return kuyruk;}
};

#endif