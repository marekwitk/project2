#include <vector>
#include <iostream>
#include <thread>
#include<algorithm>
#include<vector>
#include<string>
#include "pasjans.h"

int main() {
    std::vector<int> talia(52);
    std::vector<std::vector<int>> plansza(8);
    std::vector<int> pola_docelowe(4, -1);
    std::vector<int> pola_pomocnicze(4, -1);
    std::vector<StanGry> historia;

    for (int i = 0; i < 52; ++i) talia[i] = i;
    std::thread t(tasowanie, std::ref(talia)); t.join();
    rozstaw_talie_na_planszy(talia, plansza);

    while (true) {
        wyczysc_ekran();
        wyswietla_pola_docelowe_i_pomocnicze(pola_pomocnicze, pola_docelowe);
        wyswietl_plansze_ascii(plansza);

        Ruch ruch = pobierz_ruch_z_konsoli();

        if (ruch.skad == "exit") {
            std::cout << "Zakończono grę." << std::endl;
            break;
        }

        if (ruch.skad == "undo") {
            if (!historia.empty()) {
                auto stan = historia.back();
                historia.pop_back();
                plansza = stan.plansza;
                pola_docelowe = stan.pola_docelowe;
                pola_pomocnicze = stan.pola_pomocnicze;
                std::cout << "Cofnięto ruch." << std::endl;
            } else {
                std::cout << "Brak ruchów do cofnięcia." << std::endl;
            }
            continue;
        }

        historia.push_back({ plansza, pola_docelowe, pola_pomocnicze });

        if (!wykonanie_ruchu(ruch, plansza, pola_docelowe, pola_pomocnicze)) {
            std::cout << "Niepoprawny ruch, spróbuj jeszcze raz." << std::endl;
            historia.pop_back();
        }

    bool wygrana = true;
        for (int i = 0; i < 4; ++i) {
                int karta = pola_docelowe[i];
                if (karta==-1 || karta% 13 !=12)
                {
                    wygrana= false;
                    break;
                }
        }
        if (wygrana) {
            wyczysc_ekran();
            std::cout << " Gratulacje kocie, wygrałeś!" << std::endl;
            break;
        }
    }

    return 0;
}
