Kolejka w C++

Program w języku C++ implementujący kolejkę za pomocą listy jednokierunkowej. Program umożliwia wczytywanie liczb z pliku, sortowanie ich metodą Bubble Sort, wyświetlanie kolejki oraz zapisanie wyniku do pliku.

Funkcjonalności

Program posiada menu umożliwiające:

Wczytanie danych z pliku

Sortowanie kolejki metodą Bubble Sort

Wyświetlenie elementów kolejki

Zapisanie kolejki do pliku

Zakończenie programu

Jak działa program?

Kolejka jest zbudowana przy użyciu struktury:

struct kolejka
{
    int nr;
    kolejka* nastepny;
};


Każdy element przechowuje:

nr – liczbę całkowitą,

nastepny – wskaźnik na kolejny element kolejki.

Klasa uczen przechowuje dwa wskaźniki:

kolejka* poczatek;
kolejka* koniec;


poczatek wskazuje pierwszy element kolejki, a koniec ostatni.

Dostępne operacje
Dodawanie elementu

Metoda:

void dodaj(int nr)


dodaje nowy element na koniec kolejki.

Wczytywanie z pliku

Metoda:

void wczytaj(string nazwaPliku)


odczytuje liczby całkowite z pliku i dodaje je kolejno do kolejki.

Domyślnie program korzysta z pliku:

dane.txt


Przykładowa zawartość:

8 3 15 1 9 4 2

Sortowanie

Metoda:

void sortuj()


sortuje elementy kolejki rosnąco za pomocą algorytmu Bubble Sort.

Przykład:

Przed sortowaniem:
8 3 15 1 9 4 2

Po sortowaniu:
1 2 3 4 8 9 15

Wyświetlanie kolejki

Metoda:

void wypisz()


wyświetla wszystkie elementy kolejki w kolejności ich występowania.

Zapisywanie do pliku

Metoda:

void zapisz(string nazwaPliku)


zapisuje zawartość kolejki do pliku.

Domyślnie wynik zapisywany jest w:

wynik.txt

Uruchomienie

Do uruchomienia programu potrzebny jest kompilator C++, np. g++.

Kompilacja
g++ main.cpp -o kolejka

Uruchomienie

Linux / macOS:

./kolejka


Windows:

kolejka.exe

Przykładowe użycie

Po uruchomieniu programu pojawi się menu:

1-wczytaj z pliku
2-sortuj bubble sort
3-wypisz kolejke
4-zapisz do pliku
0-wyjscie
Wybor:


Przykładowy przebieg:

Wybor: 1
dane zostaly wczytane

Wybor: 3
Kolejka 8 3 15 1 9 4 2

Wybor: 2
posortowano

Wybor: 3
Kolejka 1 2 3 4 8 9 15

Wybor: 4
kolejka jest zapisana

Struktura projektu
projekt/
├── main.cpp
├── dane.txt
├── wynik.txt
└── README.md


wynik.txt jest tworzony przez program po wybraniu opcji zapisu.

Wykorzystane elementy C++

Projekt wykorzystuje:

strukturę struct,

klasy,

wskaźniki,

dynamiczną alokację pamięci (new),

listę jednokierunkową,

kolejkę,

pliki (ifstream, ofstream),

instrukcję switch,

pętlę do while,

algorytm Bubble Sort.

Autor

Projekt edukacyjny wykonany w języku C++.
