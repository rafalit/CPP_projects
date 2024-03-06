#include <iostream>
#include <type_traits>
#include <gtest/gtest.h>

#include "../user.h"
#include "../windows.h"

namespace
{
using namespace std;
using namespace ::testing;

struct CoutBufferSentinel
{
    std::streambuf *oldCoutBuffer = nullptr;
    std::ostringstream newBuffer;

    CoutBufferSentinel()
    {
        oldCoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(newBuffer.rdbuf());
    }

    ~CoutBufferSentinel()
    {
        std::cout.rdbuf(oldCoutBuffer);
    }

    auto getText() const
    {
        return newBuffer.str();
    }

    void clearText()
    {
        newBuffer.str("");
    }
};
} // namespace

struct WindowsTester : public ::testing::Test
{
    static constexpr const char* defaultVersion = "11";
};

TEST_F(WindowsTester, defaultConstructor)
{
    #ifdef UNIMPLEMENTED_WINDOWS_CLASS
        ADD_FAILURE() << "Function not implemented";
    #else
        CoutBufferSentinel coutSentinel; // to catch std::cout

        Windows windows;

        const auto expectedOutputFromConstructor = string("Windows ") + defaultVersion + '\n';

        ASSERT_EQ(defaultVersion, windows.version());
        ASSERT_EQ(expectedOutputFromConstructor, coutSentinel.getText());
    #endif
}

TEST_F(WindowsTester, constructorWithSingleArgument)
{
    #ifdef UNIMPLEMENTED_WINDOWS_CLASS
        ADD_FAILURE() << "Function not implemented";
    #else
        CoutBufferSentinel coutSentinel; // to catch std::cout

        constexpr const char* version = "7";

        Windows windows(version);

        const auto expectedOutputFromConstructor = string("Windows ") + version + '\n';

        ASSERT_EQ(version, windows.version());
        ASSERT_EQ(expectedOutputFromConstructor, coutSentinel.getText());
    #endif
}

TEST_F(WindowsTester, addSingleUser_expectedUserIdReturned)
{
    #ifdef UNIMPLEMENTED_WINDOWS_CLASS
        ADD_FAILURE() << "Function not implemented";
    #else
        CoutBufferSentinel coutSentinel; // to catch std::cout

        Windows windows;

        constexpr const char* username = "admin";
        constexpr const char* userpassword = "admin1";

        constexpr std::size_t expectedUserId = 0;

        ASSERT_EQ(expectedUserId, windows.add_user(username, userpassword));
    #endif
}

TEST_F(WindowsTester, user_expectedNewlyAddedUserReturned)
{
    #ifdef UNIMPLEMENTED_WINDOWS_CLASS
        ADD_FAILURE() << "Function not implemented";
    #else
        CoutBufferSentinel coutSentinel; // to catch std::cout

        Windows windows;

        constexpr const char* username = "admin";
        constexpr const char* userpassword = "admin1";

        const User expectedUser{username, userpassword};

        auto userId = windows.add_user(username, userpassword);

        ASSERT_EQ(expectedUser, windows.user(userId));
    #endif
}

TEST_F(WindowsTester, userHomeDirectory_expectedCorrectUserHomeDirectoryReturned)
{
    #ifdef UNIMPLEMENTED_WINDOWS_CLASS
        ADD_FAILURE() << "Function not implemented";
    #else
        CoutBufferSentinel coutSentinel; // to catch std::cout

        Windows windows;

        constexpr const char* username = "admin";
        constexpr const char* userpassword = "admin1";

        auto userId = windows.add_user(username, userpassword);

        const auto expectedHomeDirectory = string("C:\\Users\\") + username;

        ASSERT_EQ(expectedHomeDirectory, windows.user_home_directory(userId));
    #endif
}

TEST_F(WindowsTester, instanceConstructionAndDestruction_expectedOpenSourceSympathizersChanges)
{
    #ifdef UNIMPLEMENTED_WINDOWS_CLASS
        ADD_FAILURE() << "Function not implemented";
    #else
        CoutBufferSentinel coutSentinel; // to catch std::cout

        { // increasing by default constructor
            const auto openSourceSympathizersBeforeTest = Windows::activated_systems();

            Windows windows;

            ASSERT_EQ(openSourceSympathizersBeforeTest + 1, Windows::activated_systems());
        }

        { // increasing by constructor
            const auto openSourceSympathizersBeforeTest = Windows::activated_systems();

            Windows windows("unknown");

            ASSERT_EQ(openSourceSympathizersBeforeTest + 1, Windows::activated_systems());
        }

        { // dynamic memory allocated object
            const auto openSourceSympathizersBeforeTest = Windows::activated_systems();
            std::make_unique<Windows>();
            ASSERT_EQ(openSourceSympathizersBeforeTest + 1, Windows::activated_systems());
        }
    #endif
}

TEST_F(WindowsTester, characterType_definedInsideClass)
{
    #ifdef UNIMPLEMENTED_WINDOWS_CLASS
        ADD_FAILURE() << "Function not implemented";
    #else
        CoutBufferSentinel coutSentinel; // to catch std::cout

        Windows windows;

        constexpr bool characterTypeIsChar = std::is_same_v<wchar_t, Windows::character_type>;
        ASSERT_TRUE(characterTypeIsChar);
//        ASSERT_TRUE(std::is_same_v<wchar_t, windows::character_type>);  <- this does not compiles
    #endif
}
