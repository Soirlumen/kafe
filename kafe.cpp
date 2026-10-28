#include <iostream>
#include <stdexcept>

struct DruhKávy{
    unsigned int ARABICA=0;
    unsigned int ROBUSTA=0;
    unsigned int LIBERICA=0;
    unsigned int EXCELSA=0;
    unsigned int SELENIUM82=0;
    unsigned int soucet()const{
        return ARABICA+ROBUSTA+LIBERICA+EXCELSA+SELENIUM82;
    }
}; //myšleno jako díly jednotlivých druhů, třeba 2ku1ku0ku0 nevim

class Kafe{
    protected:
        DruhKávy druh;
    public:
    Kafe(DruhKávy k):druh(k) {
        if (k.soucet()==0) {
            throw std::invalid_argument("Tak hele tam není žádné kafe");
        }
    }
    virtual ~Kafe()=default;
    virtual void vypij()=0;
    DruhKávy get_druh()const{
        return druh;
    }
    void poměr_druhů() const{
        unsigned int součet=get_druh().soucet();
        std::cout<<"\nV kávě je: \n";
        auto vypiš=[součet](const char*název,int množství){
            if (množství>0){
                std::cout<< " " << název <<": "
                << množství << "/" << součet <<"\n";
            }
        };
    vypiš("Arabica", druh.ARABICA);
    vypiš("Robusta", druh.ROBUSTA);
    vypiš("Liberica", druh.LIBERICA);
    vypiš("Excelsa", druh.EXCELSA);
    vypiš("Selenium 82", druh.SELENIUM82);
    }
};

class Kapučíno:public Kafe{
    public:
    using Kafe::Kafe;    
    void vypij()override{
            std::cout<<"piju kapučíííno=)";
        }
};

class Amerikáno:public Kafe{
    private:
        unsigned int mnozstvi_vody;
    public:
    Amerikáno(DruhKávy dr, int voda):Kafe(dr),mnozstvi_vody(voda){}
    void vypij()override{
            std::cout<<"piju amerikáno s " << get_mnozstvi_vody() << " ml vody=).";
        }
        unsigned int get_mnozstvi_vody()const{
            return mnozstvi_vody;
        }
};

class Espresso:public Kafe{
    public:
        using Kafe::Kafe;
        void vypij()override{
            std::cout<<"piju depresso:(";
        }
};

class DekorujuKafe:public Kafe{
    private:
    static Kafe* kontrola_kafíčka(Kafe* k) {
        if (k == nullptr) {
            throw std::invalid_argument("Chyba dekorátoru: Nelze dekorovat prázdné kafe!");
        }
        return k; 
    }
    protected:
        Kafe *kafíčko;
    public:
        DekorujuKafe(Kafe *k):Kafe(kontrola_kafíčka(k)->get_druh()), kafíčko(k) {
        }
        void vypij()override{
            kafíčko->vypij();
        }
        virtual ~DekorujuKafe() {
            delete kafíčko;
    }
};

class SCukrem : public DekorujuKafe{
    private:
        unsigned int množství;
    public:
        SCukrem(Kafe* k, unsigned int m) : DekorujuKafe(k), množství(m) {}
        void vypij()override{
            std::cout<<"do kafe hodím " <<get_množství()<< " ks kostek cukru a potom ";
            kafíčko->vypij();
        }
        unsigned int get_množství()const{
            return množství;
        }
};

class SMlíkem:public DekorujuKafe{
    private:
        unsigned int množství;
    public:
        SMlíkem(Kafe* k, unsigned int m) : DekorujuKafe(k), množství(m) {}
        void vypij()override{
            std::cout<<"do kafe naliju " <<get_množství()<< " ml mléka a potom ";
            kafíčko->vypij();
        }
        unsigned int get_množství()const{
            return množství;
        }
};

class SeSkořicí:public DekorujuKafe{
private:
    public:
    SeSkořicí(Kafe* k) : DekorujuKafe(k) {}
        void vypij()override{
            std::cout<<"na kafe nasypu skořici a potom ";
            kafíčko->vypij();
        }
};


class SeSušenkou:public DekorujuKafe{
private:
    public:
    SeSušenkou(Kafe* k) : DekorujuKafe(k) {}
        void vypij()override{
            kafíčko->vypij();
            std::cout<<" Jo a dám si k tomu sušenku";
            
        }
};

int main(){
    DruhKávy meow;
    meow.ARABICA=1;
    meow.EXCELSA=2;
    meow.SELENIUM82=10000;
    Kafe* kf=new SeSušenkou(new SCukrem(new SMlíkem(new Amerikáno(meow,2), 100), 2));
    kf->vypij();
    kf->poměr_druhů();
    delete kf;
}