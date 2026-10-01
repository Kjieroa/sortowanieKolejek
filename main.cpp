#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

// ============================================================
// WLASNA KOLEJKA - "WAGONIKI"
// ============================================================

struct kolejka
{
    int nr;
    kolejka* nastepny;
};

class uczen
{
    kolejka* poczatek;
    kolejka* koniec;

public:

    uczen()
    {
        poczatek = NULL;
        koniec = NULL;
    }

    // Dodawanie elementu na koniec kolejki
    void dodaj(int nr)
    {
        kolejka* nowy = new kolejka;

        nowy->nr = nr;
        nowy->nastepny = NULL;

        if (poczatek == NULL)
        {
            poczatek = nowy;
            koniec = nowy;
        }
        else
        {
            koniec->nastepny = nowy;
            koniec = nowy;
        }
    }

    // Usuwanie elementu z poczatku kolejki
    void usun()
    {
        if (poczatek == NULL)
            return;

        kolejka* temp = poczatek;
        poczatek = poczatek->nastepny;

        if (poczatek == NULL)
            koniec = NULL;

        delete temp;
    }

    // Usuwanie wszystkich elementow
    void wyczysc()
    {
        while (poczatek != NULL)
        {
            usun();
        }
    }

    ~uczen()
    {
        wyczysc();
    }
};


// ============================================================
// DRZEWO BINARNE
// ============================================================

struct Wezel
{
    int wartosc;
    Wezel* lewy;
    Wezel* prawy;
};

class Drzewo
{
private:

    Wezel* korzen;

    Wezel* dodaj(Wezel* wezel, int wartosc)
    {
        if (wezel == NULL)
        {
            Wezel* nowy = new Wezel;

            nowy->wartosc = wartosc;
            nowy->lewy = NULL;
            nowy->prawy = NULL;

            return nowy;
        }

        if (wartosc < wezel->wartosc)
        {
            wezel->lewy = dodaj(wezel->lewy, wartosc);
        }
        else
        {
            wezel->prawy = dodaj(wezel->prawy, wartosc);
        }

        return wezel;
    }

    void usunDrzewo(Wezel* wezel)
    {
        if (wezel == NULL)
            return;

        usunDrzewo(wezel->lewy);
        usunDrzewo(wezel->prawy);

        delete wezel;
    }

public:

    Drzewo()
    {
        korzen = NULL;
    }

    void dodaj(int wartosc)
    {
        korzen = dodaj(korzen, wartosc);
    }

    ~Drzewo()
    {
        usunDrzewo(korzen);
    }
};


// ============================================================
// FUNKCJA DO WYSWIETLANIA CZASU
// ============================================================

void pokazCzas(string nazwa, steady_clock::time_point start,
               steady_clock::time_point koniec)
{
    auto czas = duration_cast<microseconds>(koniec - start);

    cout << nazwa << ": "
         << czas.count()
         << " mikrosekund" << endl;
}


// ============================================================
// PROGRAM GLOWNY
// ============================================================

int main()
{
    const int N = 100000;

    cout << "=============================================\n";
    cout << "   POMIAR CZASU STRUKTUR DANYCH\n";
    cout << "=============================================\n\n";

    // --------------------------------------------------------
    // 1. LOSOWANIE LICZB
    // --------------------------------------------------------

    // Tablica przechowujaca 100000 wylosowanych liczb.
    // Liczby losujemy TYLKO RAZ.
    int liczby[N];

    srand(time(NULL));

    for (int i = 0; i < N; i++)
    {
        liczby[i] = rand();
    }

    cout << "Wylosowano " << N << " liczb.\n";
    cout << "Te same liczby beda uzywane w kazdym tescie.\n\n";


    // ========================================================
    // 2. ZWYKLA TABLICA
    // ========================================================

    cout << "---------------------------------------------\n";
    cout << "1. ZWYKLA TABLICA int\n";
    cout << "---------------------------------------------\n";

    int tablica[N];

    auto start = steady_clock::now();

    for (int i = 0; i < N; i++)
    {
        tablica[i] = liczby[i];
    }

    auto koniec = steady_clock::now();

    pokazCzas("Dodawanie do tablicy", start, koniec);


    // Sortowanie tablicy
    start = steady_clock::now();

    sort(tablica, tablica + N);

    koniec = steady_clock::now();

    pokazCzas("Sortowanie tablicy", start, koniec);


    // Dodanie kolejnych 100000 liczb
    // W zwyklej tablicy musimy miec wiecej miejsca.
    int tablica2[2 * N];

    for (int i = 0; i < N; i++)
    {
        tablica2[i] = tablica[i];
    }

    start = steady_clock::now();

    for (int i = 0; i < N; i++)
    {
        tablica2[N + i] = liczby[i];
    }

    koniec = steady_clock::now();

    pokazCzas("Dodanie kolejnych 100000 liczb", start, koniec);


    // ========================================================
    // 3. VECTOR
    // ========================================================

    cout << "\n---------------------------------------------\n";
    cout << "2. VECTOR\n";
    cout << "---------------------------------------------\n";

    vector<int> v;

    start = steady_clock::now();

    for (int i = 0; i < N; i++)
    {
        v.push_back(liczby[i]);
    }

    koniec = steady_clock::now();

    pokazCzas("Dodawanie do vectora", start, koniec);


    // Sortowanie vectora
    start = steady_clock::now();

    sort(v.begin(), v.end());

    koniec = steady_clock::now();

    pokazCzas("Sortowanie vectora", start, koniec);


    // Dodanie kolejnych 100000
    start = steady_clock::now();

    for (int i = 0; i < N; i++)
    {
        v.push_back(liczby[i]);
    }

    koniec = steady_clock::now();

    pokazCzas("Dodanie kolejnych 100000 liczb", start, koniec);


    // ========================================================
    // 4. KOLEJKA FIFO
    // ========================================================

    cout << "\n---------------------------------------------\n";
    cout << "3. KOLEJKA FIFO - queue\n";
    cout << "---------------------------------------------\n";

    queue<int> kolejkaFIFO;

    start = steady_clock::now();

    for (int i = 0; i < N; i++)
    {
        kolejkaFIFO.push(liczby[i]);
    }

    koniec = steady_clock::now();

    pokazCzas("Dodawanie do kolejki FIFO", start, koniec);


    // Usuwanie elementow
    start = steady_clock::now();

    while (!kolejkaFIFO.empty())
    {
        kolejkaFIFO.pop();
    }

    koniec = steady_clock::now();

    pokazCzas("Usuwanie z kolejki FIFO", start, koniec);


    // ========================================================
    // 5. STOS LIFO
    // ========================================================

    cout << "\n---------------------------------------------\n";
    cout << "4. STOS LIFO - stack\n";
    cout << "---------------------------------------------\n";

    stack<int> stos;

    start = steady_clock::now();

    for (int i = 0; i < N; i++)
    {
        stos.push(liczby[i]);
    }

    koniec = steady_clock::now();

    pokazCzas("Dodawanie do stosu", start, koniec);


    // Usuwanie elementow
    start = steady_clock::now();

    while (!stos.empty())
    {
        stos.pop();
    }

    koniec = steady_clock::now();

    pokazCzas("Usuwanie ze stosu", start, koniec);


    // ========================================================
    // 6. WLASNA KOLEJKA - "WAGONIKI"
    // ========================================================

    cout << "\n---------------------------------------------\n";
    cout << "5. WLASNA KOLEJKA - WAGONIKI\n";
    cout << "---------------------------------------------\n";

    uczen mojaKolejka;

    start = steady_clock::now();

    for (int i = 0; i < N; i++)
    {
        mojaKolejka.dodaj(liczby[i]);
    }

    koniec = steady_clock::now();

    pokazCzas("Dodawanie do wlasnej kolejki", start, koniec);


    // Usuwanie elementow
    start = steady_clock::now();

    for (int i = 0; i < N; i++)
    {
        mojaKolejka.usun();
    }

    koniec = steady_clock::now();

    pokazCzas("Usuwanie z wlasnej kolejki", start, koniec);


    // ========================================================
    // 7. DRZEWO BINARNE
    // ========================================================

    cout << "\n---------------------------------------------\n";
    cout << "6. DRZEWO BINARNE\n";
    cout << "---------------------------------------------\n";

    Drzewo drzewo;

    start = steady_clock::now();

    for (int i = 0; i < N; i++)
    {
        drzewo.dodaj(liczby[i]);
    }

    koniec = steady_clock::now();

    pokazCzas("Dodawanie do drzewa binarnego", start, koniec);


    // ========================================================
    // KONIEC
    // ========================================================

    cout << "\n=============================================\n";
    cout << "              KONIEC TESTOW\n";
    cout << "=============================================\n";

    cout << "\nZlozonosc podstawowych operacji:\n\n";

    cout << "Tablica:\n";
    cout << "  dostep       O(1)\n";
    cout << "  dodanie      O(1) - jesli jest wolne miejsce\n";
    cout << "  wyszukiwanie O(n)\n";
    cout << "  sortowanie   O(n log n)\n\n";

    cout << "Vector:\n";
    cout << "  dostep       O(1)\n";
    cout << "  push_back    O(1) srednio\n";
    cout << "  wyszukiwanie O(n)\n";
    cout << "  sortowanie   O(n log n)\n\n";

    cout << "Kolejka FIFO:\n";
    cout << "  dodawanie    O(1)\n";
    cout << "  usuwanie     O(1)\n\n";

    cout << "Stos LIFO:\n";
    cout << "  dodawanie    O(1)\n";
    cout << "  usuwanie     O(1)\n\n";

    cout << "Wlasna kolejka:\n";
    cout << "  dodawanie    O(1)\n";
    cout << "  usuwanie     O(1)\n\n";

    cout << "Drzewo binarne:\n";
    cout << "  dodawanie    O(log n) - dla zbalansowanego drzewa\n";
    cout << "  wyszukiwanie O(log n) - dla zbalansowanego drzewa\n";
    cout << "  najgorszy przypadek O(n)\n";

    return 0;
}
