# Laboratoria 8 i 9: Lista jedno-kierunkowa o unikalnych elementach obudowujące `double` i `std::string` w hierarchii + parser + rzutowanie + wyjątki
W zadaniu chodzi o to, żeby Państwo zrobili program od początku do końca, który coś robi jako całość. Tym czymś jest parser standardowego wyjścia odpowiadający na komendy. Coś na kształt notatnika z historią.
Drugim aspektem jest aby Państwo zaimplementowali listę jedno-kierunkową wraz z iteratorami.
Te dwa aspekty się łączą w jedną całość, dlatego też zadanie jest więc rozbite na dwa zajęcia.

### Do zrobienia:
1. Implementacja listy jedno-kierunkowej na kształt `std::forward_list`, z tymże trzymanymi w liście mają być wskaźniki do `Object*`.
   Nie wiedząc czegoś warto się przyjrzeć dokumentacji [std::forward_list](https://en.cppreference.com/w/cpp/container/forward_list) - starałem się zachować dużą zbieżność (ale musiałem coś trudnego dodać od siebie).
    1. Zaimplementuj konstruktor bezargumentowy, oraz metody `size()` i `empty()`, po ich zdefiniowaniu zakomentuj makro:
    `UNIMPLEMENTED_OBJECT_LIST_CONSTRUCTOR_SIZE_EMPTY_METHODS`
    2. Zaimplementuj metodę `push_front` dodającą nowy element na początek listy, po jej zaimplementowaniu zakomentuj makro:
    `UNIMPLEMENTED_PUSH_FRONT`
    3. Zaimplementuj metodę `pop_front` usuwającą pierwszy elemente na początek listy, po jej zaimplementowaniu zakomentuj makro:
    `UNIMPLEMENTED_POP_FRONT`
    4. Dopilnuj aby elementy już będące w liście nie były duplikowane.
       1. **Proszę się zastanowić jak to zrobić wydajnie, można mnie spytać na kolejnych zajęciach.**
    5. Zaimplementuj metodę `front` zwracającą element z początku listy, po jej zaimplementowaniu zakomentuj makro:
    `UNIMPLEMENTED_FRONT`
    6. Zaimplementuj metodę `clear` czyszczącą listę, po jej zaimplementowaniu zakomentuj makro:
    `UNIMPLEMENTED_CLEAR`
    7. Zaimplementuj metodę `reverse` odwracającą kolejność elementów w liście, po jej zaimplementowaniu zakomentuj makro:
    `UNIMPLEMENTED_REVERSE`
       - kiedyś na rozmowie kwalifikacyjnej dali mi takie zadanie na papierze
    8. Zaimplementuj `iterator`, bęcący klasą zagnieżdżoną naszej listy. Klasa powinna mieć zaimplementowane odpowiednie metody do obsługi iteratora (mogą być to puste implementacje, które jeszcze nie działają), po ich zdefiniowaniu zakomentuj makro:
    `UNIMPLEMENTED_ITERATOR_METHODS_AT_LEAST_EMPTY`
    9. Zaimplementuj powyższe metody jak należy, następnie zakomentuj makro `UNIMPLEMENTED_ITERATORS`.
    10. Zaimplementuj metodę `erase_after`, po jej zaimplementowaniu zakomentuj makro:
    `UNIMPLEMENTED_ERASE_AFTER`
    11. Zaimplementuj metodę `erase`, po jej zaimplementowaniu zakomentuj makro:
    `UNIMPLEMENTED_ERASE`
        1. Uwaga: `std::forward_list` nie posiada metody `erase()`, jak sądzisz, dlaczego?
    12. Zaimplementuj konstruktor kopiujący "głęboko"
    13. Zaimplementuj konstruktor przenoszący
    14. Zaimplementuj kopiujący operator przypisania
    15. Zaimplementuj przenoszący operator przypisania
2. Zaimplementuj klasę `StringObject` dziedziczącą po `Object` (też własnego autorstwa), posiadającą następujące metody:
    1. Konstruktor przyjmujący tekst.
    2. `operator==`
    3. Dodatkowe pola i metody konieczne do wykonania zadania
3. Program działający w następujący sposób:
    1. Komendy (format `komenda 1234...`, czyli spacja jest separatorem):
        - `add` tworzy obiekt, przykładowa linia:
           ```
           add IntObject:44
           add ComplexObject:33+11i
           add StringObject:Powodzenia z zadaniem!
           ```
           ten drugi to liczba zespolona, szczegóły jak jest wczytywana znajdują się w testach
        - `sum` - zwraca sumę dla podanego typu np.:
          ```
          sum DoubleObject
          ```
        - `get` - wyświetla element o danym odwrotnym indexie (zaczynając od 0, a odwrotny bo lista jednokierunkowa) np.

          ```
          get 1
          ```
        - `mul` - mnoży wszystkie elementy przez liczbę całkowitą np.
          ```
          mul 2
          ```
    2. Obsługiwane typu obiektów:
        - `StringObject` - on ma tekst np. `std::string`, **tylko ten typ jest używany w testach jednostkowych**
        - `IntObject` - obudowywuje `int`
        - `DoubleObject` - obudowywuje `double`
        - `ComplexObject` - obudowywuje `std::complex<int,int>`, ale może też agregować dwie liczby.
    3. Obsługa błędów:
        1. W razie podania niepoprawnej komendy powinien zostać wyświetlony komunikat o błędzie na `stderr`
        2. W razie braku wejścia do programu nic ma się nie dziać.
        3. W razie podania złego typu - również linijka o tym informująca na `stderr`
        4. W razie nie podania wymaganych argumentów - również linijka o tym informująca na `stderr`
    4. Wyświetlanie obiektów: `Typ(Wartość)` np.: `DoubleObject(2.000000)` lub `StringObject("Kazdy test, ktory przechodzi, to punkt za zadanie!")`
4. Proszę pamiętać:
    1. Lista przyjmuje obiekty alokowane na stercie (czyli też musi potem zwolnić pamięć)
    2. Jak ma być tworzony `ComplexObject` - proszę sprawdzić w plikach z testami.
    3. Nawet jak testy nie sprawdzają tego proszę podzielić kod porządnie na klasy.
5. [Filmik tłumaczący o co chodzi w paczce.](https://banbye.com/watch/v_yM2wFq9ymQ9O):
    1. Opis paczki, skąd pomysł, co chcę osiągnąć i czemu to uważam za ważne.
    2. Normalnie się nie robi tak z wskaźnikami bo robimy cache miss raz za razem
    3. Kilka słów [poziomach testowania](https://devenv.pl/poziomy-testow/) i o nowości w testach - `TEST_P`
    4. Budowanie paczki/przełączanie między testami.
    5. Biblioteka [boost](https://www.boost.org/).
    6. Wejście pod szablony
    7. [SOLID](https://en.wikipedia.org/wiki/SOLID)

## Uwagi:
1. Wykorzystajcie całą wiedzę jaką zdobyliśmy do tej pory + z ostatniego wykładu:
    - klasy
    - dziedziczenie
    - polimorfizm
    - przeciążanie operatorów
    - operatory konwersji
    - operatory strumienia
    - `std::shared_ptr`
    - praca na plikach źródłowych i nagłówkowych, [porządny styl programowania](https://programowaniec.wordpress.com/2017/11/09/czego-sie-czepiam/).
2. Dobre praktyki programistyczne w większości sprowadzają się do określenia: "ograniczenie zależności", dlatego proszę:
    - nie includować wszystkiego wszędzie, a zamiast tego gdzie się da proszę zastosować deklaracje
    - rozdzielamy na pliki źródłowe i nagłówkowe
3. Zaawansowani mogą napisać jeszcze klasę: `BigIntObject`, która będzie z założenia mogła przechowywać bardzo duże liczby całkowite. Można użyć implementacji: [jakiejś implementacji BigInt](https://github.com/sercantutar/infint).
4. Jakbyśmy chcieli ograniczyć wyświetlanie DoubleObject do 2 miejsc po przecinku to jak to zrobić?

## Ocenianie:
1. Ocenia [Bobot](https://gitlab.com/agh-courses/bobot), na ten moment w następujący sposób:
   1. Kompilacja nadesłanego rozwiązania - bez tego zero punktów. Bobot pracuje na Linuxie, używa kompilatora g++.
   2. Uruchamianie testów - za każdy test, który przejdzie są punkty, ale mogą być odjęte w kolejnych krokach.
   3. Jeśli program się wywala na którymś z testów (to się pojawia często u osób pracujących na Windowsie - ten system pozwala pisać po nie-swojej pamięci, Linux nie pozwala) lub jest timeout - wtedy będzie przyznane tyle punktów ile przechodzi testów **minus dwa za karę**.
   4. Jest odpalane narzędzie [valgrind](https://valgrind.org/), które sprawdza czy umiemy obsługiwać pamięć w praktyce - jeśli nie to **minus punkt**.
   5. Odpalane są też inne narzędzia takie jak [cppcheck](http://cppcheck.net/), czy [fawfinde](https://dwheeler.com/flawfinder/) i inne. One nie odejmują punktów, no ale mają pomóc w pisaniu porządnych programów. Nie olewajmy tego.
   6. Antyplagiat - za wykrycie plagiatu (jest specjalne narzędzie) otrzymuje się 0 punktów. Róbmy więc samemu!

## Dodatkowe plusy:
1. Za zaimplementowanie obsługi biblioteki BigInt
2. Za zrobienie listy dwu-kierunkowej z iteratorami dwukierunkowymi.

# Jak skonfigurować sobie pracę nad paczką:
W formie [wideo](https://banbye.com/watch/v_i79PoGIWrjRC) do poprzedniej paczki (link do projektu inny, reszta analogiczna).

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
    └── zaj8i9UniqueObjectList_and_parser           # directory containing exercises
        ├── CMakeLists.txt                          # CMake configuration file - the file is to open out project in our IDE
        ├── main.cpp                                # main file - here we can test out solution manually, but it is not required
        ├── object.h                                # base (and probably abstract) class for various types header
        ├── object.cpp                              # base (and probably abstract) class for various types source
        ├── objectlist.h                            # single-linked list of Object* to implement header
        ├── objectlist.cpp                          # single-linked list of Object* to implement source
        ├── README.md                               # this file
        ├── stringObject.h                          # class to agregate text header
        ├── stringObject.cpp                        # class to agregate text source
        ├── systemTests                             # here are system tests for exercise, inner CMakeLists.txt, GTest and boost libraries used by tests
        │   ├── CMakeLists.txt                      # iner CMake for tests - it is included by outter CMake
        │   ├── executableTests.cpp                 # files with tests for exercise
        │   ├── inputOutputData                     # files used by system tests (You can check what is expected output for specific input)
        │   │   ├── getByIndexComplexObject.in.txt
        │   │   ├── getByIndexComplexObject.out.txt
        │   │   ├── mulDifferentTypes.in.txt
        │   │   ├── mulDifferentTypes.out.txt
        │   │   ├── sumDoubleObject.in.txt
        │   │   ├── sumDoubleObject.out.txt
        │   │   ├── sumStringObject.in.txt
        │   │   ├── sumStringObject.out.txt
        │   │   ├── sumStringObjectWhenNoStringObject.in.txt
        │   │   └── sumStringObjectWhenNoStringObject.out.txt
        │   └── libs                                # directory containing boost library
        │       └── boost_1_81
        │           └── boost
        │               └── process                 # here is single sublibrary for boost, it is header-only sublibrary (no extra linker flags required, just include & go)
        └── unitTests                               # here are unit tests for exercise, inner CMakeLists.txt, GTest library used by tests
            ├── CMakeLists.txt
            ├── lib
            └── objectUniqueListTest.cpp
