#ifndef MATRIX_H
#define MATRIX_H

/** @file simpleString.h
@brief Klasa do operowania na tekscie `SimpleString`:
Proszę o napisanie klasy `SimpleString` opakowujacej dynamicznie allokowana tablice znakow.
Klasa ta powinna zawierac (jako protected):
- skladowa statyczna: `std::size_t instances_` liczaca aktualnie zyjace instancje
- sugerowana skladowa: `char* data_` wskazująca na dynamicznie zaalokowany obszar z tekstem
- sugerowana skladowa: `std::size_t size_` zawierajaca informacje ile znakow trzyma aktualny tekst
- sugerowana skladowa: `std::size_t capacity_` zawierajaca informacje ile znakow pomiesci aktualny bufor bez realokazji

### Poza skladowymi prosze o zaimplementowanie nastepujacych metod:
1. Metody stale `size()`, `capacity()`, `data()` ktore zwroca powyzsze skladowe
    1. size() ma zwracac rozmiar bez znaku konca tekstu
    2. Prosze o napisanie metody stalej `c_str()`, ktora zwroci zawartosc skladowej `data_`,
       ale zakonczona znakiem konca tekstu. W razie problemow mozna uzyc `mutable`.
    3. Jeśli gettery definiujemy w pliku nagłówkowym to możemy jako typ zwracany zastosować `auto`
2. Konstruktor bezargumentowy
    - wszystkie ustawienia na liście inicjalizacyjnej
    - standard dopuszcza `new char[0];`
3. Konstruktor przyjmujący tekst i dokonujący jego "głęboką" kopię, czyli:
   ```SimpleString(const char* text);```
4. Konstruktor kopiujący, wykonujący "głęboką" kopię, czyli:
   ```SimpleString(const SimpleString& text);```
5. Destruktor zwalniający pamięć
6. Metode statyczna `instances()`, ktora zwroci powyzszą skladowa statyczna
7. Proszę o napisanie metody `assign(const char* new_text)` ustawiajacej nowa zawartosc,
   dokonującej głębokiej kopii
    1. **Prosze pamietac aby zwolnic stara pamiec!**
8. Prosze o napisanie metody `equal_to`, ktora przyjmie drugi SimpleString
   i sprawdzi czy zawieraja to samo.
    1. Funkcja ta powinna przyjmowac jeszcze argument `bool case_sensitive=true`
       w oparciu o ktory porownanie bedzie ignorowac lub nie wielkosc znakow.
       1. Można się posiłkować: [tolower](https://en.cppreference.com/w/cpp/string/byte/tolower)
       2. Osoby bardziej zaawansowane mogą zaszaleć z `std::equal`.
9. Prosze o napisanie metody `append`, ktora przyjmuje drugi SimpleString,
    a po jej zawolaniu jego zawartosc zostanie dodana do zawartosci `this`.
10. Proszę o zdefiniowanie metody `SimpleString substr(size_t pos = 0, size_t count = npos) const`,
    która wykona kopię tekstu aktualnego tekstu od zadanej pozycji o podanej ilości znaków
    (ale jak tekst jest krótszy to krótszej)
11. Proszę o zdefiniowanie metody `int compare() const`, która będzie porównywała dwa teksty, w następujący sposób:
    - jeśli są równe to aby zwróciła 0
    - jeśli pierwszy tekst jest mniejszy to aby zwróciła wartość ujemną
    - w przeciwnym razie wartość dodatnią
    - funkcja powinna przyjmować dodatkowy argument `bool case_sensitive=true`
      w oparciu o ktory porownanie bedzie ignorowac lub nie wielkosc znakow.
12. Proszę zdefiniować konstruktor przenoszący. On powinien przenieść zawartość,
    ale obiekt źródłowy powinien się nadawać do użytku (czyli być w stanie jak po zawołaniu konstruktora domyślnego).
    - Jak sprytnie użyjemy `std::exchange` to możemy załatwić sprawę na liście inicjalizacyjnej.
    1. Testy próbują użyć konstruktora przenoszącego, co się stanie jak go nie zdefiniujemy i dlaczego?

____________________________________________________________________________________
### Uwaga1: Nie wolno uzywac:
`std::string` ani `std::string_view` ani innych specjalizacji `std::basic_string<...>`!

### Uwaga2: Prosze upewnic sie, ze nie ma wyciekow pamieci.
Za wycieki pamięci punkty będą odejmowane
____________________________________________________________________________________
### Prosze po zaimplementowaniu przypatrzyc sie dokumentacji
`std::string` i porownac metody z `SimpleString`.
Warto docenic, ze mamy `std::string` a wiec sami nie musimy sie bawic z pamiecią!

____________________________________________________________________________________
Informacje jak czytać testy znajdują się w materiale [wideo](https://banbye.com/watch/v_DRmDq00a5guj), a w nagraniu:
1. Co mamy zrobić?
2. Co chcemy zyskać robiąc to zadanie?
3. Dlaczego metody się tak nazywają - `std::string`
4. Czego oczekuje wykładowca do egzaminu.
5. Co ja do kolokwium.
6. Konstruktory - co mają robić
6. Typ `std::string_view`
7. Omówienie testów - co trzeba zrobić aby jakieś zaczęły działać, własne operatory `new[]` i `delete[]`, cytaty motywacyjne

____________________________________________________________________________________
## Do rozwazenia dla zaawansowanych:
1. Zaimplementowac copy-on-write - wtedy mozna te sugerowane skladowe zastapic.
2. W ktorych sytuacjach wygodnie byloby przeciazyc operatory?
3. Do czego jest `std::string_view`?
4. `std::string` ma definicje typu `value_type` - co nam to daje?
5. Prosze o zdefiniowanie metody `void load(std::istream& is)` (lub operator>>),
   ktora wczyta tekst dowolnej dlugosci z klawiatury
6. Jak zrobic metode `assign` aby uniknac niepotrzebnych alokacji i deallokacji pamieci?
7. Jak zrobic metody `assign` i `append` aby byly odporne na wyrzucenie wyjatku?
8. Jak wszystko zadziala mozna uzyc `std::unique_ptr`
____________________________________________________________________________________
## Uwaga:
1. Wszystkie atrybuty powinny być prywatne, konstruktory i metody - publiczne
2. Metody większe niż 1-linijkowe powinny być zadeklarowane w klasie,
   zdefiniowane poza klasą w pliku zrodlowym
3. Obiekty typów klasowych powinny być w miarę możliwości przekazywane
   w argumentach funkcji przez referencję do stalej,
4. Proszę stosować słówko "const" w odpowiednich miejscach.
5. W pliku zrodlowym prosze nie wlaczac dodatkowych naglowkow typu:
   <iostream>, <algorithm> - takie rzeczy powinny byc w pliku zrodlowym
6. Prosze aby w pliku naglowkowym nie bylo `using namespace std;`, w zrodlowym moze.
7. Mozna korzystac z metod z `<cstring>`.
8. Sugeruję pisać porządnie, czyli deklaracje metod w pliku nagłówkowym, definicje w źródłowym
w argumentach funkcji przez referencję, proszę też stosować słówko "const" w odpowiednich miejscach.
Metody wspólne dla wszystkich klas jako statyczne. Jeśli zwracamy stałą czasu kompilacji aby była to metoda `constexpr`.
9. Sugeruję unikać metod niestandardowych (bobot działa na Linuxie, metody z windowsa nie zadziałają).
10. Jaka jest roznica miedzy `delete` a `delete []`?

Mozna tworzyc dowolna ilosc metod pomocniczych, jednakze aby byly one prywatne.

[Bardziej szczegółowe informacje jak pisać programy w ładnym stylu](https://programowaniec.wordpress.com/2017/11/09/czego-sie-czepiam/) dla zaawansowanych.

____________________________________________________________________________________
## Ocenianie:
1. Ocenia [Bobot](https://gitlab.com/agh-courses/bobot), na ten moment w następujący sposób:
   1. Kompilacja nadesłanego rozwiązania - bez tego zero punktów. Bobot pracuje na Linuxie, używa kompilatora `g++`.
   2. Uruchamianie testów - za każdy test, który przejdzie są punkty, ale mogą być odjęte w kolejnych krokach.
   3. Jeśli program się wywala na którymś z testów (to się pojawia często u osób pracujących na Windowsie - ten system pozwala pisać po nie-swojej pamięci, Linux nie pozwala) lub jest timeout - wtedy będzie przyznane tyle punktów ile przechodzi testów **minus karne punkty**.
   4. Jest odpalane narzędzie [valgrind](https://valgrind.org/), które sprawdza czy umiemy obsługiwać pamięć w praktyce - jeśli nie to **minus punkt**.
   5. Odpalane są też inne narzędzia takie jak [cppcheck](http://cppcheck.net/), czy [fawfinde](https://dwheeler.com/flawfinder/) i inne. One nie odejmują punktów, no ale mają pomóc w pisaniu porządnych programów. Nie olewajmy tego.
   6. Antyplagiat - za wykrycie plagiatu (jest specjalne narzędzie) otrzymuje się 0 punktów. Wysyłajmy więc swoje!
**/

#include <cstddef> // std::size_t

class SimpleString
{
protected:
    unsigned int size_;
    unsigned int capacity_;
    char* data_;
    static int instances_;
    bool case_sensitive=true;
    char* buffer_;
    char* buff_;

public:
    unsigned int size() const;
    unsigned int capacity()const;
    const char * data() const;

    const char * c_str() const;

    SimpleString();

    SimpleString(const char* text);

    SimpleString(const SimpleString& text);

    ~SimpleString();

    static int instances();

    void assign(const char* new_text);

    bool equal_to(const SimpleString& text, bool case_sensitive=true)const;

    void append(const SimpleString& text);

    SimpleString substr(size_t pos = 0, size_t count = std::string::npos)const;

    int compare(const SimpleString& text, bool case_sensitive=true) const;

    SimpleString(SimpleString&& obj);
};


#endif // MATRIX_H
