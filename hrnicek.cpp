#include <iostream>
#include <stdexcept>
#include <vector>

class Surovina{
     private:
     unsigned int mnozstvi; //všechny suroviny jsou v ml šmejdi
     public:
     Surovina(unsigned int mnozstvi):mnozstvi(mnozstvi){}
     virtual std::string getInfo() const=0;
     virtual ~Surovina()=default;
     unsigned int getMnozstvi() const {return mnozstvi;}
};

class Hrníček{
     private:
     int max_kapacita;
     std::vector<Surovina> obsah;
};

class TypMléka{
private:
 std::string typ;
 explicit TypMléka(std::string typ):typ(typ){}
public:
     const std::string& getTyp() const {return typ;}
     //moje mlíčka na výběr
     static const TypMléka& KRAVSKÉ(){
          static const TypMléka k = TypMléka("kravské");
          return k;
     };
     static const TypMléka& POLSKÉ(){
          static const TypMléka p = TypMléka("polské");
          return p;
     };
     static const TypMléka& OVESNÉ(){
          static const TypMléka o = TypMléka("ovesné");
          return o;
     };
     static const TypMléka& SOJOVÉ(){
          static const TypMléka s = TypMléka("sojové");
          return s;
     };
     bool operator==(const TypMléka& jine_mleko) const 
     {
          return typ==jine_mleko.typ;
     }
};

class TypKafe{
private:
 std::string typ;
 explicit TypKafe(std::string typ):typ(typ){}
public:
     const std::string& getTyp() const {return typ;}
     //moje kafíčka na výběr
     static const TypKafe& ARABICA(){
          static const TypKafe a=TypKafe("arabica");
          return a;
     };
     static const TypKafe& ROBUSTA(){
          static const TypKafe r=TypKafe("robusta");
          return r;
     };
     static const TypKafe& LIBERICA(){
          static const TypKafe l=TypKafe("liberica");
          return l;
     };
     static const TypKafe& EXCELSA(){
          static const TypKafe e=TypKafe("excelsa");
          return e;
     };
     bool operator==(const TypKafe& jine_kafe) const 
     {
          return typ==jine_kafe.typ;
     }
};

class Mléko: public Surovina{
private:
     TypMléka typ;
public:
     Mléko(unsigned int mnozstvi, const TypMléka& typ):Surovina(mnozstvi), typ(typ){}
     std::string getInfo() const override{
          return "Mléko je typu: "+typ.getTyp()+" a množství je: "+std::to_string(getMnozstvi())+"ml";
     }
};

class Kava: public Surovina{
public:
     Kava(unsigned int mnozstvi):Surovina(mnozstvi){}
     std::string getInfo() const override{
          return "Kávy je : "+std::to_string(getMnozstvi())+"ml";
     }

};

int main(){
Mléko m(100, TypMléka::KRAVSKÉ());
}