# Porównanie podstawowych kontenerów w C++
W zadaniu chodzi o to, aby porównać kontenery standardowe, zgłębić różnicę między nimi, poczytać i poeksperymentować.
Pewne wymagane operacje są dostarczane przez dany kontener, ale nie wszystkie, warto się zastanowić dlaczego.

## Treść do wykonania:
---------
Klasa-wrapper ma zaimplementowac metody, ktore zawiera klasa abstrakcyjna IContainerWrapper.
Implementujac kazda z metod nalezy zakomentować odpowiadajace im stale preprocesora.
Dzieki temu kolejne testy beda przechodzic.

Zaleznie od uzywanego pod spodem kontenera (który można dziedziczyć prywatnie lub agregować)
bedziemy mieli dostepne rozne metody, czesc metod do zaimplementowania mozna
w sposob przezroczysty przekazac do wykonania uzywanemu kontenerowi,
ktory dana metode juz ma zaimplementowana.
Jednakze czesc metod nie jest zaimplementowana, do tego trzeba juz uzyc internetu.

Odsylam do [dokumentacji standardowych kontenerow](https://en.cppreference.com/w/cpp/container),
oraz do [artykulu robiacego benchmark](https://baptiste-wicht.com/posts/2017/05/cpp-containers-benchmark-vector-list-deque-plf-colony.html).

Jako treść-sugestia co zaimplementować jest klasa:
```c++
/// @brief Klasa abstrakcyjna `IContainerWrapper`, wszystkie metody czysto virtualne powinny być zaimplementowane
class IContainerWrapper
{
public:
    using value_type = std::int64_t;

    virtual ~IContainerWrapper() = 0;

    virtual void push_back(const value_type& element) = 0;
    virtual void push_front(const value_type& element) = 0;

    /// @brief metoda mająca za zadanie wstawienie elementu we wskazanej pozycji.
    /// Proszę zwrócić uwagę, że kontenery standardowe przyjmują iterator a nie pozycję liczbowo.
    /// Trzeba więc sobie przesunąć iterator na początek o zadaną ilość pozycji
    virtual void insert(const value_type& element, std::size_t position) = 0;

    virtual std::size_t size() const = 0;

    virtual value_type& at(std::size_t position) = 0;

    /// @brief metoda mająca za zadanie posortowanie wszystkich elementów
    /// Kontenery standardowe za wyjątkiem list takiej nie mają
    virtual void sort() = 0;

    virtual void erase(std::size_t position) = 0;

    /// @brief metoda mająca za zadanie zwrócenie sumy wszystkich elementów
    /// Kontenery standardowe takiej nie mają, za wyjątkiem kontenerów asocjacyjnych
    virtual value_type count() const = 0;

    /// @brief metoda mająca za zadanie pozycji znalezionego elementu lub maksymalnej wartości typu `size_t`
    /// Kontenery standardowe takiej nie mają, za wyjątkiem kontenerów asocjacyjnych
    virtual std::size_t find(const value_type& needle) const = 0;

    /// @brief metody mające za zadanie usunąć element z początku/końca i go zwrócić.
    /// Proszę zwrócić uwagę, że kontenery standardowe nie zwracają usuniętego elementu, dlaczego?
    virtual value_type pop_front() = 0;
    virtual value_type pop_back() = 0;
};
```
Dzięki zastosowaniu dziedziczenia po tej klasie kompilator będzie nam przypominał jakie metody mamy zaimplementować, z jakimi argumentami itp.

## Mamy do wyboru którą klasę chcemy zaimplementować:
1. `VectorWrapper` - klasa wszystkie metody implementuje przy pomocy typu `std::vector<IContainerWrapper::value_type>`
2. `VectorPreallocatedWrapper` - jw. ale dokonuje pre-allokacji w konstruktorze na milion elementów
3. `ListWrapper` - klasa wszystkie metody implementuje przy pomocy typu `std::list<IContainerWrapper::value_type>` - tego nie radzę wrzucać na Bobota, można się nie doczekać na wyniki
4. `DequeWrapper` - klasa wszystkie metody implementuje przy pomocy typu `std::deque<IContainerWrapper::value_type>`

Po wyborze, którą klasę zaimplementować należy przestawić przezwisko typu na odpowiedni wrapper kontenera:
```
using ContainerWrapper = LazyContainerWrapper;
```

____________________________________________________________________________________
## Do rozwazenia dla zaawansowanych:
1. Gdzie by sie przydal std::optional?
2. Co by nam dala pula pamieci?
3. Zachecam do poeksperymentowania z typem `value_type` i z rozmiarem i ilością elementow - czy cos to zmienia?
4. Dlaczego `pop_front` z biblioteki standardowej zwraca `void`?
5. Jaka jest różnica czy dziedziczymy po kontenerze czy go agregujemy?
6. Jest też biblioteka benchmark załączona i podpięta, po implementacji można przełączyć konfiguracje i porównać wyniki.

____________________________________________________________________________________
Informacje jak czytać testy znajdują się w materiale [wideo](https://banbye.com/watch/v__449lemFZDAa), a w nagraniu:
1. Co chcemy zrobić?
2. Co chcemy zyskać robiąc to zadanie?
3. Po co to dziedziczenie.
4. Co powinienem zaimplementować.
5. Benchmark i ich uruchamianie (konfiguracja `container_benchmark`)
6. Testy nie testują scenariuszy skrajnych (poza tym, że to milion elementów) typu ściąganie elementu gdy nie ma, dostęp do elementu poza zakresem.

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
10. Zachecam do uzywania czego sie da z biblioteki standardowej (np. `std::sort()`).
11. Prosze aby w pliku naglowkowym nie bylo `using namespace std;`, w zrodlowym moze.
12. Testy nie testuja przypadkow wyjatkowych, ale jak ktos umie warto zabezpieczyc metody
   na dziwne uzycie.
13. W kodzie mogą być fragmenty -niespodzianki.


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
____________________________________________________________________________________
## Najczestrze pytania/błędy/problemy:
1. Czekam na sugestie...

____________________________________________________________________________________
# Pytania po implementacji ćwiczenia:
1. Czego ważnego dla mnie się dzisiaj nauczyłem/nauczyłam?

____________________________________________________________________________________
# Zadania, na aktywność do pokazania na następnych zajęciach 
Jest to aktywność za zajęcia gdzie została zadana niniejsza paczka, więc jak ktoś ma już 2 punkty 
to nie dostanie dodatkowych punktów, niemniej jednak zachęcam aby sobie sprawdzić.
1. Proszę o dodatkowe implementacje dla pozostałych kontenerów i porównanie czasu poszczególnych testów. [1p]
2. Jak ktoś zaimplementuje jeszcze dodatkowo dla kontenera [plf::colony](https://github.com/mattreecebentley/plf_colony) - to jeden plik nagłówkowy. [1p]

____________________________________________________________________________________
# Jak skonfigurować sobie pracę nad paczką:
W formie [wideo](https://banbye.com/watch/v_i79PoGIWrjRC) - jest to instrukcja dla innej paczki (z innego kierunku), ale kroki są analogiczne.
Również jak przy pomocy CLiona obslugiwać gita i gitlaba ([wideo](https://banbye.com/watch/v_nNPin8m9LKqn)).

**Alternatywnie poniżej jest to spisane w kolejnej sekcji**
____________________________________________________________________________________
## Grading (section copied from Mateusz Ślażyński, of course he agreed):

* [ ] Make sure, you have a **private** group
  * [how to create a group](https://docs.gitlab.com/ee/user/group/#create-a-group)
* [ ] Fork this project into your private group
  * [how to create a fork](https://docs.gitlab.com/ee/user/project/repository/forking_workflow.html#creating-a-fork)
* [ ] Add @bobot-is-a-bot as the new project's member (role: **maintainer**)
  * [how to add an user](https://docs.gitlab.com/ee/user/project/members/index.html#add-a-user)

## How To Submit Solutions

1. [ ] Clone repository: `git clone` (clone only once the same repository):

    ```bash
    git clone <repository url>
    ```
2. [ ] Solve the exercises
3. [ ] Commit your changes

    ```bash
    git add <path to the changed files>
    git commit -m <commit message>
    ```
4. [ ] Push changes to the gitlab main branch

    ```bash
    git push -u origin main
    ```

The rest will be taken care of automatically. You can check the `GRADE.md` file for your grade / test results. Be aware that it may take some time (up to one hour) till this file. Details can be found in `./logs/` directory where You can check compilation results, tests logs etc.

## Project Structure

    .
    ├── lab5ContainerBenchmark              # directory containing exercises
    │   ├── CMakeLists.txt                  # CMake configuration file - the file is to open out project in our IDE
    │   ├── containerWrapper.h              # file to declare methods of choosen wrapper
    │   ├── containerWrapper.cpp            # file to define longer methods
    │   ├── Dockerfile                      # this file contains instructions how to run tests in embedded Ubuntu
    │   ├── main.cpp                        # main file - here we can test out solution manually, but it is not required
    │   ├── README.md                       # this file
    │   ├── benchmark                       # here are benchmarks for exercise, inner CMakeLists.txt, GBenchmark library used by benchmarks
    │   │   ├── CMakeLists.txt
    │   │   ├── containerBenchmark.cpp
    │   │   └── lib
    │   └── tests                           # here are tests for exercise, inner CMakeLists.txt, GTest library used by tests
    │       ├── CMakeLists.txt              # inner CMake for tests - it is included by outter CMake
    │       ├── containerWrapperTests.cpp
    │       └── lib                         # directory containing GTest library
