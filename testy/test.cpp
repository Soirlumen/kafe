#include "catch_amalgamated.hpp"
#include "../hrnicek.hpp"

// Samotný test
TEST_CASE("Testovani funkce getInfo", "[info]") {
    Mléko m(100, TypMléka::KRAVSKÉ());
    REQUIRE(m.getInfo() == "Mléko je typu: kravské a množství je: 100ml");
}
TEST_CASE("Nalijeme do hrníčku mléko", "[nalit]"){
    Hrníček h(200);
    std::unique_ptr<Surovina> m = std::make_unique<Mléko>(100, TypMléka::KRAVSKÉ());
    h.pridejSurovinu(std::move(m));
    REQUIRE(h.getObsahVelikost() == 1);
    }