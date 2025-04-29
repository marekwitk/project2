#ifndef PASJANS_H
#define PASJANS_H

#include <vector>
#include <string>

struct Ruch {
    std::string skad;
    int ktora;
    std::string dokad;
};

struct StanGry {
    std::vector<std::vector<int>> plansza;
    std::vector<int> pola_docelowe;
    std::vector<int> pola_pomocnicze;
};

bool poprawne_pole(const std::string& s);
bool poprawna_kombinacja(const std::vector<int>& karty);
void wyczysc_ekran();
void tasowanie(std::vector<int>& talia);
void wyswietl_plansze_ascii(const std::vector<std::vector<int>>& plansza);
void wyswietla_pola_docelowe_i_pomocnicze(const std::vector<int>& pomocnicze, const std::vector<int>& docelowe);
Ruch pobierz_ruch_z_konsoli();
bool wykonanie_ruchu(Ruch ruch, std::vector<std::vector<int>>& plansza, std::vector<int>& pola_docelowe, std::vector<int>& pola_pomocnicze);
void rozstaw_talie_na_planszy(const std::vector<int>& talia, std::vector<std::vector<int>>& plansza);
void ekran_powitalny();

#endif // PASJANS_H
