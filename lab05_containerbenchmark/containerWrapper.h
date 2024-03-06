#ifndef CONTAINER_WRAPPER_H
#define CONTAINER_WRAPPER_H

/** @file containerWrapper.h
 *  @mainpage Porownanie wydajnosci kontenerow standardowych:
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
____________________________________________________________________________________

## Do rozwazenia dla zaawansowanych:
1. Gdzie by sie przydal std::optional?
2. Co by nam dala pula pamieci?
3. Zachecam do poeksperymentowania z typem `value_type` i z rozmiarem i ilością elementow - czy cos to zmienia?
4. Dlaczego `pop_front` z biblioteki standardowej zwraca `void`?
5. Jaka jest różnica czy dziedziczymy po kontenerze czy go agregujemy?
6. Jest też biblioteka benchmark załączona i podpięta, po implementacji można przełączyć konfiguracje i porównać wyniki.
____________________________________________________________________________________
## Uwaga:
1. Zachecam do uzywania czego sie da z biblioteki standardowej (np. `std::sort()`).
2. Metody większe niż 1-linijkowe powinny być zadeklarowane w klasie,
   zdefiniowane poza klasą w pliku zrodlowym.
3. Obiekty typów klasowych powinny być w miarę możliwości przekazywane
   w argumentach funkcji przez referencję do stalej,
4. Proszę stosować słówko "const" w odpowiednich miejscach.
5. W pliku naglowkowym prosze nie wlaczac dodatkowych naglowkow typu:
   <iostream>, <algorithm> - takie rzeczy powinny byc w pliku zrodlowym
6. Prosze aby w pliku naglowkowym nie bylo `using namespace std;`, w zrodlowym moze.
7. Testy nie testuja przypadkow wyjatkowych, ale jak ktos umie warto zabezpieczyc metody
   na dziwne uzycie.
8. W kodzie mogą być fragmenty -niespodzianki.

Mozna tworzyc dowolna ilosc metod pomocniczych, jednakze aby byly one prywatne.
____________________________________________________________________________________
## Punktacja:
Liczy sie przejście testów, aczkolwiek dobrze jakby tez nie bylo warningow i wyciekow pamieci
**/

#include <vector>
#include <list>
#include <deque>
#include <cstddef> // std::size_t
#include <cstdint> // std::int64_t

/*#define UNIMPLEMENTED_DEFAULT_CONSTRUCTOR
#define UNIMPLEMENTED_CONSTRUCTOR_COPYING_FROM_ARRAY
#define UNIMPLEMENTED_PUSH_BACK
#define UNIMPLEMENTED_PUSH_FRONT
#define UNIMPLEMENTED_INSERT
#define UNIMPLEMENTED_AT
#define UNIMPLEMENTED_SORT
#define UNIMPLEMENTED_ERASE
#define UNIMPLEMENTED_COUNT
#define UNIMPLEMENTED_FIND
#define UNIMPLEMENTED_POP_FRONT
#define UNIMPLEMENTED_POP_BACK*/


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

/// @brief Klasa ktora nic nie robi - aby sie kompilowalo
class LazyContainerWrapper: IContainerWrapper
{
public:
    LazyContainerWrapper() = default;
    LazyContainerWrapper(const value_type /*elements*/[], std::size_t /*N*/) {}

    void push_back(const value_type& /*element*/) override {}
    void push_front(const value_type& /*element*/) override {}

    void insert(const value_type& /*element*/, std::size_t /*position*/) override {}

    std::size_t size() const override { return {}; }

    value_type& at(std::size_t /*position*/) override
    {
        static value_type zero{};
        return zero;
    }

    void sort() override {}

    void erase(std::size_t /*position*/) override {}

    value_type count() const override { return {}; }
    std::size_t find(const value_type& /*needle*/) const override { return {}; }

    value_type pop_front() override { return {}; }
    value_type pop_back() override { return {}; }
};

/// @brief Wrapper do std::vector
class VectorWrapper : public IContainerWrapper
{
public:
    VectorWrapper() = default;
    VectorWrapper(const value_type* elements, size_t size);
    ~VectorWrapper() override;

    void push_back(const value_type& element) override;
    void push_front(const value_type& element) override;
    void insert(const value_type& element, size_t position) override;
    void erase(size_t position) override;

    size_t size() const override;
    value_type& at(size_t position) override;

    void sort() override;
    value_type count() const override;
    size_t find(const value_type& needle) const override;
    value_type pop_back() override;
    value_type pop_front() override;
private:
    std::vector<value_type> impl_;
};

/// @brief Wrapper do std::vector, ktory dokonuje pre-allokacji w konstruktorze


/// @brief Wrapper do std::list


/// @brief Wrapper do std::deque


/// @brief Alias typu, ktory bedzie podlegac testom
using ContainerWrapper = VectorWrapper;

#endif // CONTAINER_WRAPPER_H
