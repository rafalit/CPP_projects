#include <gtest/gtest.h>

#if __has_include("../PtrCStringVector.h")
    #include "../PtrCStringVector.h"
#elif __has_include("PtrCStringVector.h")
    #include "PtrCStringVector.h"
#else
    #error "File 'PtrCStringVector.h' not found!"
#endif

namespace
{
using namespace ::testing;

constexpr size_t MAX_TEXT_LENGTH = 350;

PtrCStringVector foo_1()
{
    PtrCStringVector v;
    for (int i = 0; i < 100000; i++) {
        v.push_back("ABC");
    }
    return v;
}
} // namespace


class PtrCStringVectorTester : public ::testing::Test
{
};

TEST_F(PtrCStringVectorTester, defaultConstructor_sizeOfEmptyContainerIsZero)
{
    constexpr size_t expectedSizeOfEmptyVector = 0;

    PtrCStringVector ptrCStringVector;
    ASSERT_EQ(expectedSizeOfEmptyVector, ptrCStringVector.size());
}

TEST_F(PtrCStringVectorTester, pushBack_sizeOfContainerIncreaseAfterCallingPushBack)
{
    // source: Sw. Jan Pawel II
    constexpr const char texts[][MAX_TEXT_LENGTH] =
    {
        "Przyszlosc zaczyna sie dzisiaj, nie jutro",
        "Musicie od siebie wymagac, nawet gdyby inni od was nie wymagali",
        "Najbardziej tworcza ze wszystkich prac jest praca nad soba, ktora pozwala odnajdywac urok mlodosci. Nie ma wiekszego bogactwa w narodzie nad swiatlych obywateli",
        "Czlowiek nie jest w stanie pracowac, gdy nie widzi sensu pracy, gdy sens ten przestaje byc dla niego przejrzysty, gdy zostaje mu niejako przesloniety. Praca ludzka stoi w posrodku calego zycia spolecznego. Poprzez nia ksztaltuje sie sprawiedliwosc i milosc spoleczna, jezeli cala dziedzina pracy rzadzi wlasciwy lad moralny",
        "Kazdy z was, mlodzi przyjaciele, znajduje tez w zyciu jakies swoje Westerplatte. Jakis wymiar zadan, ktore musi podjac i wypelnic. Jakas sluszna sprawe, o ktora nie mozna nie walczyc. Jakis obowiazek, powinnosc, od ktorej nie mozna sie uchylic. Nie mozna zdezerterowac"
    };
    constexpr size_t expectedSize = sizeof(texts) / sizeof(texts[0]);

    PtrCStringVector ptrCStringVector;
    for (auto text : texts)
    {
        ptrCStringVector.push_back(text);
    }
    ASSERT_EQ(expectedSize, ptrCStringVector.size());
}

TEST_F(PtrCStringVectorTester, arrayIndexingOperator_testsInTheSamePositionsAsPushed)
{
    // source: https://8segment.pl/polskie-przyslowia.php (polskie przyslowia):
    constexpr const char texts[][MAX_TEXT_LENGTH] =
    {
        "Bez pracy nie ma kolaczy",
        "Gdyby kozka nie skakala, to by nozki nie zlamala",
        "Bog pomaga temu, ktory sam rozwiazuje wlasne problemy",
        "Jak sobie poscielisz, tak sie wyspisz",
        "Prosta droga najkrotsza"
    };
    constexpr size_t expectedSize = sizeof(texts) / sizeof(texts[0]);

    PtrCStringVector ptrCStringVector;
    for (auto text : texts)
    {
        ptrCStringVector.push_back(text);
    }

    ASSERT_EQ(expectedSize, ptrCStringVector.size());
    for (size_t i=0; i < expectedSize; ++i)
    {
        ASSERT_STREQ(texts[i], ptrCStringVector[i]) << "index: " << i;
    }
}

TEST_F(PtrCStringVectorTester, arrayIndexingOperator_throwingExceptionWhenOutOfRange)
{
    // source: http://cytatybaza.pl/cytat/jest-tylko-jedno-dobro-wiedza-i-jedno-zlo.html (Sokrates):
    constexpr const char text[] = "Jest tylko jedno dobro: wiedza, i jedno zlo: ignorancja";
    constexpr size_t expectedSize = 1;

    PtrCStringVector ptrCStringVector;

    ASSERT_THROW(ptrCStringVector[0], std::out_of_range);

    ptrCStringVector.push_back(text);
    ASSERT_EQ(expectedSize, ptrCStringVector.size());
    ASSERT_STREQ(text, ptrCStringVector[0]);

    ASSERT_THROW(ptrCStringVector[expectedSize], std::out_of_range);
}

TEST_F(PtrCStringVectorTester, copyConstructor_textsDeeplyCopied)
{
    // source: https://pl.wikiquote.org/wiki/Terry_Pratchett
    constexpr const char texts[][MAX_TEXT_LENGTH] =
    {
        "Historia ma zwyczaj zmieniac ludzi, ktorzy mysla, ze ja zmieniaja",
        "A czym byliby ludzie bez milosci?\nGINACYM GATUNKIEM, odparl Smierc",
        "Gdyby porazka nie znala kary, sukces nie bylby nagroda",
        "Jesli nienormalne trwa dostatecznie dlugo, staje sie normalnym",
        "Cisza jest tylko brakiem halasu"
    };
    constexpr size_t expectedSize = sizeof(texts) / sizeof(texts[0]);

    PtrCStringVector ptrCStringVector;
    for (auto text : texts)
    {
        ptrCStringVector.push_back(text);
    }

    const PtrCStringVector ptrCStringVectorCopy(ptrCStringVector);
    ASSERT_EQ(expectedSize, ptrCStringVectorCopy.size());
    ASSERT_EQ(expectedSize, ptrCStringVector.size());

    for (size_t i=0; i < expectedSize; ++i)
    {
        ASSERT_STREQ(texts[i], ptrCStringVectorCopy[i]) << "index: " << i;
        ASSERT_STREQ(texts[i], ptrCStringVector[i]) << "index: " << i;
    }

    const PtrCStringVector ptrCStringVectorCopy2(ptrCStringVectorCopy);
    for (size_t i=0; i < expectedSize; ++i)
    {
        ASSERT_STREQ(texts[i], ptrCStringVectorCopy2[i]) << "index: " << i;
        ASSERT_STREQ(texts[i], ptrCStringVectorCopy[i]) << "index: " << i;
    }
}

TEST_F(PtrCStringVectorTester, assignmentOperator_copyingContainerDeeply)
{
    // source: https://www.cytaty.info/cyprian-kamil-norwid.htm (Cyprian Norwid)
    constexpr const char texts[][MAX_TEXT_LENGTH] =
    {
        "Ojczyzna to wielki zbiorowy obowiazek.",
        "Z karafki napic sie mozna, uscisnawszy ja za szyjke i przechyliwszy ku ustom, ale kto ze zrodla pije, musi ukleknac i pochylic czolo",
        "Oryginalnosc jest to sumiennosc w obliczu zrodel",
        "Polacy albowiem uzywaja powiedzenia nie ma co mowic wtedy, gdy jest bardzo wiele do mowienia",
        "Slowo jest ogien - milczenie jest lawa",
    };
    constexpr size_t expectedSize = sizeof(texts) / sizeof(texts[0]);
    constexpr size_t expectedSizeOfEmptyContainer = 0;

    PtrCStringVector ptrCStringVector;
    for (auto text : texts)
    {
        ptrCStringVector.push_back(text);
    }

    {
        PtrCStringVector ptrCStringVectorCopy;
        ASSERT_EQ(expectedSizeOfEmptyContainer, ptrCStringVectorCopy.size());

        ptrCStringVectorCopy = ptrCStringVector;
        ASSERT_EQ(expectedSize, ptrCStringVectorCopy.size());
        ASSERT_EQ(expectedSize, ptrCStringVector.size());

        for (size_t i=0; i < expectedSize; ++i)
        {
            ASSERT_STREQ(texts[i], ptrCStringVectorCopy[i]) << "index: " << i;
        }
    }
    for (size_t i=0; i < expectedSize; ++i)
    {
        ASSERT_STREQ(texts[i], ptrCStringVector[i]) << "index: " << i;
    }
}

TEST_F(PtrCStringVectorTester, assignmentOperator_assignmentCascadeAtOnceExpectingDeepCopyMultipleTimesEvenWithItselve)
{
    // source: https://quotepark.com/pl/autorzy/maksymilian-maria-kolbe/ (Sw. Maksymilian Maria Kolbe)
    constexpr const char texts[][MAX_TEXT_LENGTH] =
    {
        "Dobrze spelniac to co ode mnie zalezy, a dobrze znosic to, co ode mnie nie zalezy - oto jest cala doskonalosc i zrodlo prawdziwego szczescia na swiecie.",
        "Nie zmoga nas te cierpienia, tylko przetopia i zahartuja. Wielkich potrzeba ofiar naszych, aby okupic szczescie i pokojowe zycie tych, co po nas beda",
        "Najwieksza ofiara - to ofiara z wlasnej woli",
        "Zadnej prawdy nikt nie moze zmienic - moze tylko szukac jej, znalezc ja i uznac, by do niej zycie dostosowac",
        "Wiedza nadyma i o tyle jest pozyteczna, o ile sluzy milosci",
    };
    constexpr size_t expectedSize = sizeof(texts) / sizeof(texts[0]);

    PtrCStringVector ptrCStringVector, ptrCStringVectorCopy1, ptrCStringVectorCopy2;
    for (auto text : texts)
    {
        ptrCStringVector.push_back(text);
    }

    ptrCStringVector = ptrCStringVectorCopy1 = ptrCStringVectorCopy2 = ptrCStringVector;

    ASSERT_EQ(expectedSize, ptrCStringVectorCopy1.size());
    ASSERT_EQ(expectedSize, ptrCStringVectorCopy2.size());

    for (size_t i=0; i < expectedSize; ++i)
    {
        ASSERT_STREQ(texts[i], ptrCStringVectorCopy1[i]) << "index: " << i;
        ASSERT_STREQ(texts[i], ptrCStringVectorCopy2[i]) << "index: " << i;
    }
}

TEST_F(PtrCStringVectorTester, assignmentOperator_movingTextFromAnotherContainer)
{
    // source: http://www.wyszynski.psur.pl/cytaty.php
    constexpr const char texts[][MAX_TEXT_LENGTH] =
    {
        "Potrzeba w naszej Ojczyznie przykladu ofiary z siebie, aby czlowiek wspolczesny zapomnial o sobie, a myslal o drugich - o dobru rodziny, o wypelnieniu swego powolania i zadania zyciowego wobec innych, o dobru calego narodu.",
        "Kazda milosc musi byc probowana i doswiadczana. Ale gdy wytrwa, doczeka sie nagrody - zwycieskiej radosci",
        "Nie trzeba ogladac sie na innych, na tych lub owych, moze na politykow, zadajac od nich, aby sie odmienili. Kazdy musi zaczac od siebie, abysmy prawdziwie sie odmienili",
        "(...) szczesliwy czlowiek, ktory jest z siebie niezadowolony, bo to jest punkt wyjscia",
        R"(Tak czesto slyszymy zdanie: "Piekna i zaszczytna rzecza jest umrzec za Ojczyzne". Jednakze trudniej jest niekiedy zyc dla Ojczyzny. Mozna w odruchu bohaterskim oddac swoje zycie na polu walki, ale to trwa krotko. Wiekszym niekiedy bohaterstwem jest zyc, trwac, wytrzymac cale lata.)"
    };
    constexpr size_t expectedSize = sizeof(texts) / sizeof(texts[0]);
    constexpr size_t expectedSizeOfEmptyContainer = 0;

    PtrCStringVector ptrCStringVector;
    for (auto text : texts)
    {
        ptrCStringVector.push_back(text);
    }

    PtrCStringVector ptrCStringVectorCopy;
    ASSERT_EQ(expectedSize, ptrCStringVector.size());
    ASSERT_EQ(expectedSizeOfEmptyContainer, ptrCStringVectorCopy.size());

    ptrCStringVectorCopy = std::move(ptrCStringVector);
    ASSERT_EQ(expectedSizeOfEmptyContainer, ptrCStringVector.size());
    ASSERT_EQ(expectedSize, ptrCStringVectorCopy.size());

    for (size_t i=0; i < expectedSize; ++i)
    {
        ASSERT_STREQ(texts[i], ptrCStringVectorCopy[i]) << "index: " << i;
    }

    ASSERT_THROW(ptrCStringVector[0], std::out_of_range);
}

TEST_F(PtrCStringVectorTester, addOperator_expectReturningContainerContainingAllElementsFromAddedContainers)
{
    // source: https://www.cytaty.info/arystoteles.htm (Arystoteles):
    constexpr const char texts1[][MAX_TEXT_LENGTH] =
    {
        "Prawdziwa wiedza to znajomosc przyczyn.",
        "By zapragnac przyjazni nie potrzebujesz wiele czasu, lecz sama przyjazn jest owocem, ktory dojrzewa powoli.",
        "Prawdziwa sprawiedliwoscia jest przezyc to co sie uczynilo innym.",
    };
    constexpr size_t expectedSize1 = sizeof(texts1) / sizeof(texts1[0]);

    // source: https://www.cytaty.info/sokrates.htm (Sokrates):
    constexpr const char texts2[][MAX_TEXT_LENGTH] =
    {
        "Jemy, aby zyc, nie zyjemy, aby jesc",
        "Coz komu z tego, ze zjadl wszystkie rozumy, jesli nie ma wlasnego",
        "Puste worki nadyma wiatr, bezmyslnych ludzi - proznosc",
    };
    constexpr size_t expectedSize2 = sizeof(texts2) / sizeof(texts2[0]);

    constexpr size_t expectedSize = expectedSize1 + expectedSize2;

    PtrCStringVector ptrCStringVector1;
    for (auto text : texts1)
    {
        ptrCStringVector1.push_back(text);
    }

    PtrCStringVector ptrCStringVector2;
    for (auto text : texts2)
    {
        ptrCStringVector2.push_back(text);
    }

    const PtrCStringVector addedVectors = ptrCStringVector1 + ptrCStringVector2;
    ASSERT_EQ(expectedSize, addedVectors.size());

    for (size_t i=0; i < expectedSize1; ++i)
    {
        ASSERT_STREQ(texts1[i], addedVectors[i]) << "index: " << i;
    }

    for (size_t i=0; i < expectedSize2; ++i)
    {
        ASSERT_STREQ(texts2[i], addedVectors[i + expectedSize1]) << "index: " << i;
    }
}

TEST_F(PtrCStringVectorTester, bitAndOperator_expectReturningContainerContainingMergedTextsFromCorrespondingPositionsAddedContainers)
{
    constexpr const char texts1[][MAX_TEXT_LENGTH] =
    {
        "Anastazja",
        "Bonifia",
        "Cecylia"
    };
    constexpr size_t expectedSize1 = sizeof(texts1) / sizeof(texts1[0]);

    constexpr const char texts2[][MAX_TEXT_LENGTH] =
    {
        "Ambrozy",
        "Bazyli",
        "Cezary",
        "Dionizy",
        "Elohim"
    };
    constexpr size_t expectedSize2 = sizeof(texts2) / sizeof(texts2[0]);

    const size_t maxSize = std::max(expectedSize1, expectedSize2);
    const size_t minSize = std::min(expectedSize1, expectedSize2);

    PtrCStringVector ptrCStringVector1;
    for (auto text : texts1)
    {
        ptrCStringVector1.push_back(text);
    }

    PtrCStringVector ptrCStringVector2;
    for (auto text : texts2)
    {
        ptrCStringVector2.push_back(text);
    }

    const PtrCStringVector addedVectors = ptrCStringVector1 & ptrCStringVector2;
    ASSERT_EQ(maxSize, addedVectors.size());

    for (size_t i=0; i < minSize; ++i)
    {
        const auto concatedTexts = std::string(texts1[i]) + texts2[i];
        ASSERT_STREQ(concatedTexts.c_str(), addedVectors[i]) << "index: " << i;
    }

    for (size_t i=minSize; i < maxSize; ++i)
    {
        ASSERT_STREQ(texts2[i], addedVectors[i]) << "index: " << i;
    }
}


TEST_F(PtrCStringVectorTester, antytest1)
{
    PtrCStringVector v;
    for (int i = 0; i < 100000; i++)
    {
        size_t size = v.size();
        v.push_back("ABC");
        ASSERT_EQ(size + 1, v.size());
    }
}

TEST_F(PtrCStringVectorTester, antytest2)
{
    PtrCStringVector v = foo_1();
    for (int i = 0; i < 100000; i++)
    {
        ASSERT_STREQ(v[i], "ABC") << "index: " << i;
    }
}

static PtrCStringVector foo_2(PtrCStringVector v)
{
    for (int i = 0; i < 100000; i++)
    {
        v.push_back("CBA");
    }
    return v;
}

TEST_F(PtrCStringVectorTester, antytest3)
{
    PtrCStringVector v;
    for (int i = 0; i < 100000; i++)
    {
        v.push_back("ABC");
    }

    v = foo_2(v);
    for (int i = 0; i < 100000; i++)
    {
        ASSERT_STREQ(v[i], "ABC") << "index: " << i;
    }
    for (int i = 100000; i < 200000; i++)
    {
        ASSERT_STREQ(v[i], "CBA") << "index: " << i;
    }
}

TEST_F(PtrCStringVectorTester, antytest4)
{
    PtrCStringVector v;
    for (int i = 0; i < 100; i++)
    {
        v.push_back("ABC");
    }
    for(int i=0; i < 8; i++)
    {
        v=v+v;
    }
    ASSERT_EQ(v.size(),25600);
}

TEST_F(PtrCStringVectorTester, antytest5)
{
    PtrCStringVector v;
    for (int i = 0; i < 100; i++)
    {
        auto numberAsText = std::to_string(i);
        v.push_back(numberAsText.c_str());
    }
    ASSERT_NE(strcmp(v[0],v[99]),0);
}

TEST_F(PtrCStringVectorTester, antytest6)
{
    PtrCStringVector v;
    for (int i = 0; i < 200; i++)
    {
        v.push_back("A");
    }
    for (int i = 0; i < 8; i++)
    {
        v=v&v;
    }
    ASSERT_EQ(strlen(v[199]),256);
}

TEST_F(PtrCStringVectorTester, antytest7)
{
    PtrCStringVector v;
    for (int i = 0; i < 10000; i++)
    {
        std::string s;
        s.append(i,'a');
        v.push_back(s.c_str());
    }

    for (int i = 0; i < 10000; i++)
    {
        ASSERT_EQ(strlen(v[i]),i);
    }
}

TEST_F(PtrCStringVectorTester, antytest8)
{
    PtrCStringVector v,v1;
    for (int i = 0; i < 10000; i++)
    {
        std::string s(i,'a');
        v.push_back(s.c_str());
    }
    v1=v;
    for (int i = 0; i < 10000; i++)
    {
        ASSERT_EQ(strcmp(v[i],v1[i]),0);
    }
}

TEST_F(PtrCStringVectorTester, antytest9)
{
    PtrCStringVector v,v1;
    for (int i = 0; i < 10000; i++)
    {
        std::string s;
        s.append(i,'a');
        v.push_back(s.c_str());
    }
    v1=v;
    for (int i = 0; i < 10000; i++)
    {
        ASSERT_NE(v[i],v1[i]);
    }
}

TEST_F(PtrCStringVectorTester, antytest10)
{
    PtrCStringVector v;
    for (int i = 0; i < 10000; i++)
    {
        std::string s;
        s.append(i,'a');
        v.push_back(s.c_str());
    }
    PtrCStringVector v1(v);
    for (int i = 0; i < 10000; i++)
    {
        ASSERT_NE(v[i],v1[i]);
    }
}


#ifdef DOMJUDGE /// this is fot online judge system
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    GTEST_FLAG(print_time) = false;
    return RUN_ALL_TESTS();
}
#endif // DOMJUDGE
