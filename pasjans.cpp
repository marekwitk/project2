#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <random>
#include <string>

using namespace std;

void wyczysc_ekran() {
    this_thread::sleep_for(chrono::milliseconds(2000));//spowolnienie by mozna bylo przeczytac ze ruch zly 
    system("cls");//czyszczenie ekranu
}

void tasowanie(vector<int>& talia) {//talia to vector 0-51
    random_device rd;//generator liczb losowych rd >>zmienna losowa
    mt19937 gen(rd()); //generator liczb losowych gen >> nazwa generatora 
    shuffle(talia.begin(), talia.end(), gen);//miesa elementry tali uzywa gen generatora losowego
}

vector<string> generuj_karte_ascii(string figura, string kolor) {
    vector<string> karta;

    if (kolor == "v") {
        if (figura == "10") {
            karta = {
                " _____ ",
                "|" + figura + " _ |",
                "|( v )|",
                "| \\ / |",
                "|  V  |",
                "|___" + figura + "|"
            };
        }
        else {
            karta = {
                " _____ ",
                "|" + figura + "_ _ |",
                "|( v )|",
                "| \\ / |",
                "|  V  |",
                "|____" + figura + "|"
            };
        }
    }
    else if (kolor == "^") {
        if (figura == "10") {
            karta = {
                " _____ ",
                "|" + figura + ".  |",
                "| /.\\ |",
                "|(_._)|",
                "|  |  |",
                "|___" + figura + "|"
            };
        }
        else {
            karta = {
                " _____ ",
                "|" + figura + " .  |",
                "| /.\\ |",
                "|(_._)|",
                "|  |  |",
                "|____" + figura + "|"
            };
        }
    }
    else if (kolor == "o") {
        if (figura == "10") {
            karta = {
                " _____ ",
                "|" + figura + "^  |",
                "| / \\ |",
                "| \\ / |",
                "|  V  |",
                "|___" + figura + "|"
            };
        }
        else {
            karta = {
                " _____ ",
                "|" + figura + " ^  |",
                "| / \\ |",
                "| \\ / |",
                "|  V  |",
                "|____" + figura + "|"
            };
        }
    }
    else if (kolor == "%") {
        if (figura == "10") {
            karta = {
                " _____ ",
                "|" + figura + "_  |",
                "| ( ) |",
                "|(_'_)|",
                "|  |  |",
                "|___" + figura + "|"
            };
        }
        else {
            karta = {
                " _____ ",
                "|" + figura + " _  |",
                "| ( ) |",
                "|(_'_)|",
                "|  |  |",
                "|____" + figura + "|"
            };
        }
    }

    return karta;
}

vector<string> karta_ascii(int n) {
    vector<string> figury = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    vector<string> kolory = { "v", "^", "o", "%" };

    int figura = n % 13;
    int kolor = n / 13;

    return generuj_karte_ascii(figury[figura], kolory[kolor]);
}

void rozstaw_talie_na_planszy(const vector<int>& talia, vector<vector<int>>& plansza) {
    int index = 0;
    for (int kol = 0; kol < 8; ++kol) {
        int ileKart = (kol < 4) ? 7 : 6;
        for (int i = 0; i < ileKart; ++i) {
            plansza[kol].push_back(talia[index++]);
        }
    }
}

void wyswietl_plansze_ascii(const vector<vector<int>>& plansza) {
    int max_wysokosc = 0;
    cout << "==KOL1=|==KOL2=|==KOL3=|==KOL4=|==KOL5=|==KOL6=|==KOL7=|==KOL8=|" << endl;
    for (const auto& kol : plansza)
        max_wysokosc = max(max_wysokosc, (int)kol.size());

    for (int wiersz = 0; wiersz < max_wysokosc; ++wiersz) {
        vector<vector<string>> rzad_kart;
        for (int kol = 0; kol < 8; ++kol) {
            if (wiersz < plansza[kol].size())
                rzad_kart.push_back(karta_ascii(plansza[kol][wiersz]));
            else
                rzad_kart.push_back(vector<string>(6, "       "));
        }

        for (int linia = 0; linia < 6; ++linia) {
            for (int kol = 0; kol < 8; ++kol) {
                cout << rzad_kart[kol][linia] << " ";
            }
            cout << endl;
        }
    }
}

void wyswietla_pola_docelowe_i_pomocnicze(const vector<int>& pomocnicze, const vector<int>& docelowe) {
    vector<vector<string>> karty;

    for (int i = 0; i < 4; ++i)
        karty.push_back(i < pomocnicze.size() && pomocnicze[i] != -1 ? karta_ascii(pomocnicze[i]) : vector<string>(6, "       "));
    for (int i = 0; i < 4; ++i)
        karty.push_back(docelowe[i] != -1 ? karta_ascii(docelowe[i]) : vector<string>(6, "       "));

    cout << "==POM1=|==POM2=|==POM3=|==POM4=|" << "|=CEL1=|==CEL2=|==CEL3=|==CEL4==" << endl;
    for (int linia = 0; linia < 6; ++linia) {
        for (const auto& karta : karty)
            cout << karta[linia] << " ";
        cout << endl;
    }
    cout << endl << "|=============================|" << endl;
}

/*struct Ruch {
    string skad;
    int ktora;
    string dokad;
};*/

bool poprawne_pole(const string& s) {
    if (s.size() < 4) return false;//jak input za ktotki to jest odrzucane
    string prefix = s.substr(0, 3);//wyciecie 3 znakow i zamienienie ich na prefix
    if (prefix != "KOL" && prefix != "POM" && prefix != "CEL") return false;//jezeli prefix to nie kol cel pom to zle
    if (prefix == "POM" || prefix == "CEL")//sekcja pom cel
    {
        try {
            int numer = stoi(s.substr(3));//konwersja stringa na inta
            return numer > 0 && numer <= 4;
        }
        catch (...) {//(...) cokolwiek co nie pasi 
            return false;
        }
    }

    if (prefix == "KOL")
    {
        try {
            int numer = stoi(s.substr(3));
            return numer > 0 && numer <= 8;
        }
        catch (...) {
            return false;
        }
    }
    return false;
}

Ruch pobierz_ruch_z_konsoli() {//funkcja zwracająca strukture ruch ktorey pobiera z konsoli 
    string skad, dokad;
    int ktora = 1;

    cout << "Z kad chcesz wziasc karte (np. KOL1, POM2 lub 'undo'/'exit'): ";
    cin >> skad;

    if (skad == "exit" || skad == "undo") return { skad, 0, "none" };//zwracamy strukture Ruch
    while (!poprawne_pole(skad)) {
        cout << "Niepoprawne pole. Sprobuj jeszcze raz: ";
        cin >> skad;
        if (skad == "exit" || skad == "undo") return { skad, 0, "none" };
    }

    cout << "Ktora karte od dolu chcesz wziasc?: ";
    while (!(cin >> ktora) || ktora <= 0) {
        cout << "Niepoprawna liczba. Sprobuj jeszcze raz: ";
        cin.clear();//resetuje blad wejscia
        cin.ignore(numeric_limits<streamsize>::max(), '\n');//pomijamy wszystko do konca lini
    }

    cout << "Gdzie chcesz dac karte (np. KOL3, CEL1, POM1): ";
    cin >> dokad;
    while (!poprawne_pole(dokad)) {
        cout << "Niepoprawne pole. Sprobuj jeszcze raz: ";
        cin >> dokad;
    }

    return { skad, ktora, dokad };
}

bool poprawna_kombinacja(const vector<int>& karty) {
    for (int i = 0; i < (int)karty.size() - 1; ++i) {
        int f1 = karty[i] % 13, f2 = karty[i + 1] % 13;
        int k1 = karty[i] / 13, k2 = karty[i + 1] / 13;
        if (!(f1 == f2 + 1 && (k1 + k2) % 2 == 1)) return false;
    }
    return true;
}

bool czy_mozna_polozyc(int karta_skad, int karta_dokad) {
    int f1 = karta_skad % 13, f2 = karta_dokad % 13;
    int k1 = karta_skad / 13, k2 = karta_dokad / 13;
    return f1 + 1 == f2 && (k1 + k2) % 2 == 1;
}

bool wykonanie_ruchu(Ruch ruch, vector<vector<int>>& plansza, vector<int>& pola_docelowe, vector<int>& pola_pomocnicze) {
    if (ruch.skad == "exit" || ruch.skad == "undo") return false;

    int skad_idx = stoi(ruch.skad.substr(3)) - 1;
    int dokad_idx = stoi(ruch.dokad.substr(3)) - 1;

    vector<int> temp_zrodlo;
    vector<int>* zrodlo = nullptr;
    vector<int>* cel = nullptr;

    if (ruch.skad.find("KOL") != string::npos) {
        zrodlo = &plansza[skad_idx];
    }
    else if (ruch.skad.find("POM") != string::npos) {
        if (pola_pomocnicze[skad_idx] == -1) return false;
        temp_zrodlo.push_back(pola_pomocnicze[skad_idx]);
        zrodlo = &temp_zrodlo;
    }
    else return false;

    if (ruch.dokad.find("KOL") != string::npos) {
        cel = &plansza[dokad_idx];
    }
    else if (ruch.dokad.find("POM") != string::npos) {
        if (pola_pomocnicze[dokad_idx] != -1) return false;

        if (ruch.ktora != 1 || zrodlo->empty()) return false;
        pola_pomocnicze[dokad_idx] = zrodlo->back();

        if (ruch.skad.find("POM") != string::npos)
            pola_pomocnicze[skad_idx] = -1;
        else
            zrodlo->pop_back();

        return true;
    }
    else if (ruch.dokad.find("CEL") != string::npos) {
        int karta = zrodlo->back();//ostatni element 
        if ((pola_docelowe[dokad_idx] == -1 && karta % 13 == 0) ||
            (pola_docelowe[dokad_idx] != -1 && karta == pola_docelowe[dokad_idx] + 1)) {

            pola_docelowe[dokad_idx] = karta;

            if (ruch.skad.find("POM") != string::npos)
                pola_pomocnicze[skad_idx] = -1;
            else
                zrodlo->pop_back();//usuwa ostatni element z wektora

            return true;
        }
        return false;
    }
    else return false;

    if (ruch.ktora > (int)zrodlo->size() || ruch.ktora <= 0) return false;

    vector<int> do_przeniesienia(zrodlo->end() - ruch.ktora, zrodlo->end());
    if (!poprawna_kombinacja(do_przeniesienia)) return false;

    if (cel->empty() || czy_mozna_polozyc(do_przeniesienia.front(), cel->back())) {
        cel->insert(cel->end(), do_przeniesienia.begin(), do_przeniesienia.end());
        zrodlo->erase(zrodlo->end() - ruch.ktora, zrodlo->end());

        if (ruch.skad.find("POM") != string::npos)
            pola_pomocnicze[skad_idx] = -1;

        return true;
    }

    return false;
}

/*struct StanGry {
    vector<vector<int>> plansza;
    vector<int> pola_docelowe;
    vector<int> pola_pomocnicze;
};

void ekran_powitalny() {
    wyczysc_ekran();
    cout << "===========================" << endl;
    cout << "     PASJANS FREECEL ASCII   " << endl;
    cout << "===========================" << endl;
    cout << "\nZasady gry:" << endl;
    cout << "1. Przenies wszystkie karty na pola CEL1-CEL4 rosnaco wg koloru zaczynajac od asa." << endl;
    cout << "2. Na kolumnach: malejaco, naprzemienne kolory." << endl;
    cout << "3. 4 pola pomocnicze (POM1-POM4) do przechowywania." << endl;
    cout << "4. Komendy: 'undo' (cofnij ruch), 'exit' (wyjscie)." << endl;
    cout << "\nNacisnij Enter, aby rozpoczac..." << endl;
    cin.ignore();
    cin.get();
}

int main() {
    vector<int> talia(52);
    vector<vector<int>> plansza(8);
    vector<int> pola_docelowe(4, -1);
    vector<int> pola_pomocnicze(4, -1);
    vector<StanGry> historia;

    ekran_powitalny();

    for (int i = 0; i < 52; ++i) talia[i] = i;
    thread t(tasowanie, ref(talia)); t.join();
    rozstaw_talie_na_planszy(talia, plansza);

    while (true) {
        wyczysc_ekran();
        wyswietla_pola_docelowe_i_pomocnicze(pola_pomocnicze, pola_docelowe);
        wyswietl_plansze_ascii(plansza);

        Ruch ruch = pobierz_ruch_z_konsoli();

        if (ruch.skad == "exit") {
            cout << "Zakończono grę." << endl;
            break;
        }

        if (ruch.skad == "undo") {
            if (!historia.empty()) {
                auto stan = historia.back();
                historia.pop_back();
                plansza = stan.plansza;
                pola_docelowe = stan.pola_docelowe;
                pola_pomocnicze = stan.pola_pomocnicze;
                cout << "Cofnięto ruch." << endl;
            }
            else {
                cout << "Brak ruchów do cofnięcia." << endl;
            }
            continue;
        }

        historia.push_back({ plansza, pola_docelowe, pola_pomocnicze });

        if (!wykonanie_ruchu(ruch, plansza, pola_docelowe, pola_pomocnicze)) {
            cout << "Niepoprawny ruch, spróbuj jeszcze raz." << endl;
            historia.pop_back();
        }

        bool wygrana = true;
        for (int i = 0; i < 4; ++i) {
            if (pola_docelowe[i] != 12 + 13 * i) {
                wygrana = false;
                break;
            }
        }
        if (wygrana) {
            wyczysc_ekran();
            cout << "🎉 Gratulacje! Wygrałeś grę FreeCell! 🎉" << endl;
            break;
        }
    }
    
    return 0;
}*/
