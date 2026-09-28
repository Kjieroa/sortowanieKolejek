#include <iostream>
#include <fstream>

using namespace std;

//pojedynczy fragment kolejki
struct kolejka
{
    int nr;
    kolejka* nastepny;
};

//klasa przechowujaca kolejke
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

//dodawanie nowego elementu na koniec kolejki
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

//wypisywanie kolejki
    void wypisz()
    {
        kolejka* temp=poczatek;

        if(temp==NULL)
        {
            cout<<" jest pusta"<<endl;
            return;
        }

        while(temp!=NULL)
        {
            cout<<temp->nr << " ";
            temp=temp->nastepny;
        }

        cout<<endl;
    }

//wczytywanie danych z pliku
    void wczytaj(string nazwaPliku)
    {
        ifstream plik(nazwaPliku);

        if(!plik)
        {
            cout<<"plik nie zostal wczytany"<<endl;
            return;
        }
        int liczba;
        while(plik>>liczba)
        {
            dodaj(liczba);
        }
        plik.close();
        cout<<"dane zostaly wczytane"<<endl;
    }

//sortowanie babelkowe
    void sortuj()
    {
        if(poczatek==NULL || poczatek->nastepny==NULL)
        {
            return;
        }
        bool zamiana;
        do
        {
            zamiana=false;
            kolejka* temp=poczatek;
            while(temp->nastepny!=NULL)
            {
                if(temp->nr>temp->nastepny->nr)
                {
                    int pomocnicza=temp->nr;
                    temp->nr = temp->nastepny->nr;
                    temp->nastepny->nr=pomocnicza;
                    zamiana = true;
                }
                temp=temp->nastepny;
            }

        }while(zamiana);

        cout<<"posortowano"<<endl;
    }

//zapisywanie kolejki do pliku
    void zapisz(string nazwaPliku)
    {
        ofstream plik(nazwaPliku);

        if(!plik)
        {
            cout<<"plik nie zostal wczytany"<<endl;
            return;
        }

        kolejka* temp=poczatek;

        while(temp!=NULL)
        {
            plik<<temp->nr << " ";
            temp=temp->nastepny;
        }

        plik.close();

        cout<<"kolejka jest zapisana"<<endl;
    }
};



int main()
{
    uczen uczniowie;

    int wybor;

    do
    {
        cout<<endl;
        cout<<"1-wczytaj z pliku"<<endl;
        cout<<"2-sortuj bubble sort"<<endl;
        cout<<"3-wypisz kolejke"<<endl;
        cout<<"4-zapisz do pliku"<<endl;
        cout<<"0-wyjscie"<<endl;
        cout<<"Wybor: ";
        cin>>wybor;

        switch (wybor)
        {
            case 1:
                uczniowie.wczytaj("dane.txt");
                break;

            case 2:
                uczniowie.sortuj();
                break;

            case 3:
                cout << "Kolejka ";
                uczniowie.wypisz();
                break;

            case 4:
                uczniowie.zapisz("wynik.txt");
                break;

            case 0:
                cout<<"koniec programu"<<endl;
                break;

            default:
                cout<<"nieprawidlowy wybor"<<endl;

           }
    }while(wybor != 0);

    return 0;
}
