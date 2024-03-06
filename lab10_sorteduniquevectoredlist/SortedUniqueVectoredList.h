#ifndef SORTED_UNIQUE_VECTORED_LIST_H
#define SORTED_UNIQUE_VECTORED_LIST_H

#include <cstddef>   // size_t
#include <string>


/** @file SortedUniqueVectoredList.h
 * @date 31 maja 2021
 * @brief W ramach kolokwium probnego trzeba zaimplementowac mechanizmy kilku kontenerow w jednym: vector, list, deque, set, string.
 * Szczegoly opisane sa w ramach metod klasy SortedUniqueVectoredList.
 * Do ponizszych metod **sa testy** w pliku @ref SortedUniqueVectoredListTests.cpp.
 * __Jest to kolokwium probne, ktorego zrobienie samodzielne daje duze szanse na zdanie prostrzego, aczkolwiek podobnego, kolokwium wlasciwego za tydzien__ **/


/** class SortedUniqueVectoredList
 * @brief Klasa SortedUniqueVectoredList, stanowiaca liste z glowa tablic dynamicznych trzymajacych teksty, ktore maja byc posortowane i unikalne.
 *        Bez obaw, nie musi byc optymalnie, schemat znajduje sie tutaj:
 *        @image html diagram.png
 *        @image latex diagram.png
 *        Jak widac w praktyce jest to lista z glowa wezlow @ref Bucket. Dodawane elementy sa jesli juz takowego nie ma, oraz sortowane.
 *        Kontener ten w razie braku miejsca tworzy nowy @ref Bucket i tam dodaje nowy element.
 *
 * @note Zmiany pliku naglowkowego nie powinny byc konieczne, prosze probowac zmienic jedynie w pliku zrodlowym @ref SortedUniqueVectoredList.cpp.
 *
 * @param size_ ilosc elementow w kontenerze, tworzac pusty ma byc 0, po kazdym zawolaniu push_back powinno byc o jeden wiecej
 * @param capacity_ ilosc zaallokowanej pamieci w kontenerze na elementy,
 *        wywolania push_back w razie potrzeby maja dokonac reallokacji powiekszajacej o jeden @ref Bucket, wtedy capacity jest zwiekszane o @ref Bucket::BUCKET_SIZE
 * @param bucketCount_ ilosc kubelkow
 * @param head wskaznik na pierwszy @ref Bucket (zwykły lub inteligentny wskaźnik)
 * @param tail wskaznik na pierwszy @ref Bucket (zwykły lub inteligentny wskaźnik) **/
class SortedUniqueVectoredList
{
public:
    /// opis w pliku @ref SortedUniqueVectoredList.cpp, jest to tzw. idiom PIMPL
    struct Bucket;

    /** @brief konstruktor domyslny, jego zadaniem jest ustawienie pol klasy na brak elementow **/
    SortedUniqueVectoredList() = default;

    /** @brief konstruktor kopiujacy, dokonujacy **gleboka kopie**, czyli nie tylko wskazniki maja byc skopiowane, ale cale kubelki
     *  @param source - kontener zrodkowy, z ktorego musza byc skopiowane wszystkie dane
     *  @note jak dobrze zaimplementujemy metode @ref SortedUniqueVectoredList::copy to wystarczy ja tutaj zawolac **/
    SortedUniqueVectoredList(const SortedUniqueVectoredList& source);

    /** @brief konstruktor przenoszacy, ktory cala zawartosc z innego kontenera przeniesie zostawiajac
     *  @param source - kontener zrodkowy, z ktorego musza byc przeniesione wszystkie dane
     *  @note kontener zrodlowy w stanie jak po zawolaniu konstruktora bezargumentowego
     *  @note jak dobrze zaimplementujemy metody @ref SortedUniqueVectoredList::move i @ref SortedUniqueVectoredList::free to warto je tutaj zawolac **/
    SortedUniqueVectoredList(SortedUniqueVectoredList&& source);

    /** @brief destruktor, ktory musi koniecznie zwolnic pamiec i inne zasoby
     *  @note jak dobrze zaimplementujemy metode @ref SortedUniqueVectoredList::free to wystarczy ja tutaj zawolac **/
    ~SortedUniqueVectoredList();

    /** @brief operator przypisania, ktory ma za zadanie skopiowac doglebnie tresc, analogicznie jak konstruktor kopiujacy \ref SortedUniqueVectoredList(const SortedUniqueVectoredList&)
     *  @note prosze sie upewnic, ze zadziala przypisanie na samego siebie: @code{.cpp}
           SortedUniqueVectoredList a;
           SortedUniqueVectoredList& b = a;
           a = b;
        @endcode
        @note prosze sie upewnic, ze zadziala przypisanie kaskadowe: @code{.cpp}
           SortedUniqueVectoredList a, b, c;
           a = b = c;
        @endcode
        @details Operator przypisania powinien **zwolnic pamiec** w razie potrzeby, aby nie dopuscic do wyciekow pamieci.
            Mozna uzyc [idiomu copy&swap](https://en.m.wikibooks.org/wiki/More_C%2B%2B_Idioms/Copy-and-swap). **/
    SortedUniqueVectoredList& operator=(const SortedUniqueVectoredList& another);

    /** @brief operator przypisania, ktory ma za zadanie przeniesc zawartosc z obiektu zrodlowego
     *  @note prosze sie upewnic, ze zadziala przypisanie na samego siebie: @code{.cpp}
           SortedUniqueVectoredList a;
           SortedUniqueVectoredList& b = a;
           a = std::move(b);
        @endcode
        @details Operator przypisania przenoszacy powinien **zwolnic dotychczasowa pamiec**, aby nie dopuscic do wyciekow pamieci.
            Powinien tez zostawic obiekt zrodlowy w stanie jak po zawolaniu konstruktora domyslnego.
            Jak dobrze zaimplementujemy @ref SortedUniqueVectoredList::move i @ref SortedUniqueVectoredList::free to warto je zawolac **/
    SortedUniqueVectoredList& operator=(SortedUniqueVectoredList&& another);

    /** @brief Metoda zwracajaca aktualnie posiadana ilosc elementow w kontenerze.
     *  @return wartosc `size_` **/
    auto size() const
    {
        return size_;
    }

    /** @brief Metoda zwracajaca informacje ile elementow zmiesci sie w kontenerze.
     *  @return wartosc `capacity_` **/
    auto capacity() const
    {
        return capacity_;
    }

    /** @brief Metoda zwracajaca informacje ile kubelkow jest obecnie zaallokowanych.
     *  @return wartosc `bucketCount_` **/
    auto bucket_count() const
    {
        return bucketCount_;
    }

    /** @brief metoda, ktora skopiuje podany tekst i umiesci na kontenerze, o ile takowego jeszcze nie ma.
     *         W razie braku miejsca kontener powinien zostac zwiekszony.
     *  @param text2Add - tekst do skopiowania doglebnie (na nowa dynamiczna pamiec)
     *  @post Dodany tekst zostanie skopiowany i umieszczony na koncu kontenera. W razie potrzeby powinien byc zaalokowany kolejny @ref Bucket.
     *  @note Nie musi byc optymalnie - mozna pojechac po calym kontenerze kazdorazowo i caly kontener sortowac po kazdym wstawieniu.
     *  @details Sugeruje przed wstawieniem elementu sprawdzic czy takowy jest juz w kontenerze. **/
    void insert(const std::string& value);

    /** @brief operator indeksowania, ktory otrzymawszy indeks zwroci referencje do tekstu znajdujacego sie na danej pozycji w kontenerze
     *  @param index elementu tekstowego w kontenerze
     *  @exception w razie podania
     *  @throw std::out_of_range w razie, gdy `index >= size_` **/
    std::string& operator[](size_t index);

    /** @brief operator indeksowania, podobny do powyzszego @ref operator[], ale zwraca `const string` i jest metoda stala **/
    const std::string& operator[](size_t index) const;

    /** @brief operator, ktory tworzy kontener zawierajacy wszystkie elementy z pierwszego kontenera, ktorych nie ma w kontenerze `another`
     *  @param another kontener, ktorego elementy maja byc usuniete z `this` o ile w nim sa
     *  @return Nowo-utworzony kontener zawierajacy wszystkie elementy z `*this`, ktorych nie ma w `another`
     *  @details Sugeruje utworzyc nowy kontener i wolac na nim @ref insert, dla elementow bedacych w this ale nie bedacych w `another` */
    SortedUniqueVectoredList operator-(const SortedUniqueVectoredList& another) const;

    /** @brief operator, ktory kazdy ze skladowanych tekstow `this` zwielokrotni wskazana ilosc razy
     *  @note jest to operator modyfikujacy obiekt na rzecz ktorego jest wywolywany
     *  @param howManyTimesMultiply ile razy kazdy tekst ma byc zwielokrotniony
     *  @return `*this` ze zwielokrotnionymi tekstami
     *  @details Przykladowo:  @code{.cpp}
           SortedUniqueVectoredList a;
           a.insert("HejHa");
           a *= 3;
           // a zawiera "HejHaHejHaHejHa"
           a *= 0;
           // a zawiera ""
        @endcode **/
    SortedUniqueVectoredList& operator*=(const size_t howManyTimesMultiply);

    /** @brief operator konwersji, ktory wszystkie teksty polaczy w jeden bez jakichkolwiek separatorow
     *  @return tekst zawierajacy wszystkie teksty **/
    explicit operator std::string() const;

    /** @brief Opcjonalne (nie ma na to testow): metoda usuwajacy element o danej wartosci **/
    void erase(const std::string& value);

    /** @brief Opcjonalne (nie ma na to testow) **/
    friend std::ostream& operator<<(std::ostream& stream, const SortedUniqueVectoredList& container);

protected:
    /** @brief metoda pomocnicza allokujaca nowy @ref Bucket na koncu listy (nowy @ref SortedUniqueVectoredList::tail)
     *  @note prosze pamietac o @ref SortedUniqueVectoredList::bucketCount_ @ref SortedUniqueVectoredList::capacity_ **/
    void allocate_new_bucket();

    /** @brief metoda pomocnicza zwalniajaca zasoby
     *  @note nie tylko @ref SortedUniqueVectoredList::head i @ref SortedUniqueVectoredList::tail powinny byc zwolnione, ale rowniez wszystko pomiedzy **/
    void free();

    /** @brief metoda pomocnicza przenoszaca zawartosc z obiektu zrodlowego na *this.
     *  @note nalezy pamietac o zwalnianiu zasobow **/
    void move(SortedUniqueVectoredList&& another);

    /** @brief metoda pomocnicza kopiujaca z obiektu zrodlowego na *this.
     *  @note nalezy pamietac o zwalnianiu zasobow **/
    void copy(const SortedUniqueVectoredList& other);

    /** @brief metoda pomocnicza zwracajaca informacje czy dany element jest juz w kontenerze.
     *  @details nie musi byc optymalna, moze isc sekwencyjnie po wszystkich elementach **/
    bool contains(const std::string& value) const;

    void sort_buckets();

private:
    Bucket *head = nullptr, *tail = nullptr;

    size_t bucketCount_{}, size_{}, capacity_{};
};


#endif // SORTED_UNIQUE_VECTORED_LIST_H
