#include <iostream>
#include <type_traits>
#include <gtest/gtest.h>

#include "../user.h"
#include "../linux.h"


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

struct LinuxTester : public ::testing::Test
{
    static constexpr const char* defaultDistribution = "Ubuntu";
};

TEST_F(LinuxTester, defaultConstructor)
{
    CoutBufferSentinel coutSentinel; // to catch std::cout

    Linux linux;

    const auto expectedOutputFromConstructor = string("+") + defaultDistribution + '\n';

    ASSERT_EQ(defaultDistribution, linux.distribution());
    ASSERT_EQ(expectedOutputFromConstructor, coutSentinel.getText());
}

TEST_F(LinuxTester, constructorWithSingleArgument)
{
    CoutBufferSentinel coutSentinel; // to catch std::cout

    constexpr const char* distribution = "Manjaro";

    Linux linux(distribution);

    const auto expectedOutputFromConstructor = string("+") + distribution + '\n';

    ASSERT_EQ(distribution, linux.distribution());
    ASSERT_EQ(expectedOutputFromConstructor, coutSentinel.getText());
}

TEST_F(LinuxTester, destructor)
{
    CoutBufferSentinel coutSentinel; // to catch std::cout

    {
        Linux linux;

        coutSentinel.clearText();
    }

    const auto expectedOutputFromDestructor = string("~") + defaultDistribution + '\n';

    ASSERT_EQ(expectedOutputFromDestructor, coutSentinel.getText());
}

TEST_F(LinuxTester, addSingleUser_expectedUserIdReturned)
{
    CoutBufferSentinel coutSentinel; // to catch std::cout

    Linux linux;

    constexpr const char* username = "admin";
    constexpr const char* userpassword = "admin1";

    constexpr std::size_t expectedUserId = 0;

    ASSERT_EQ(expectedUserId, linux.add_user(username, userpassword));
}

TEST_F(LinuxTester, user_expectedNewlyAddedUserReturned)
{
    CoutBufferSentinel coutSentinel; // to catch std::cout

    Linux linux;

    constexpr const char* username = "admin";
    constexpr const char* userpassword = "admin1";

    const User expectedUser{username, userpassword};

    auto userId = linux.add_user(username, userpassword);

    ASSERT_EQ(expectedUser, linux.user(userId));
}

TEST_F(LinuxTester, userHomeDirectory_expectedCorrectUserHomeDirectoryReturned)
{
    CoutBufferSentinel coutSentinel; // to catch std::cout

    Linux linux;

    constexpr const char* username = "admin";
    constexpr const char* userpassword = "admin1";

    auto userId = linux.add_user(username, userpassword);

    const auto expectedHomeDirectory = string("/home/") + username + "/";

    ASSERT_EQ(expectedHomeDirectory, linux.user_home_directory(userId));
}

TEST_F(LinuxTester, instanceConstructionAndDestruction_expectedOpenSourceSympathizersChanges)
{
    CoutBufferSentinel coutSentinel; // to catch std::cout

    { // increasing by default constructor
        const auto openSourceSympathizersBeforeTest = Linux::open_source_sympathizers();

        Linux linux;

        ASSERT_EQ(openSourceSympathizersBeforeTest + 1, Linux::open_source_sympathizers());
    }

    { // increasing by constructor
        const auto openSourceSympathizersBeforeTest = Linux::open_source_sympathizers();

        Linux linux("unknown");

        ASSERT_EQ(openSourceSympathizersBeforeTest + 1, Linux::open_source_sympathizers());
    }

    { // increasing by constructor then decreasing by destructor
        const auto openSourceSympathizersBeforeTest = Linux::open_source_sympathizers();
        {
            Linux linux [[maybe_unused]];
        }
        ASSERT_EQ(openSourceSympathizersBeforeTest, Linux::open_source_sympathizers());
    }

    { // dynamic memory allocated object
        const auto openSourceSympathizersBeforeTest = Linux::open_source_sympathizers();
        std::unique_ptr<Linux>();
        ASSERT_EQ(openSourceSympathizersBeforeTest, Linux::open_source_sympathizers());
    }
}

TEST_F(LinuxTester, characterType_definedInsideClass)
{
    CoutBufferSentinel coutSentinel; // to catch std::cout

    Linux linux;

    constexpr bool characterTypeIsChar = std::is_same_v<char, Linux::character_type>;
    ASSERT_TRUE(characterTypeIsChar);
    //        ASSERT_TRUE(std::is_same_v<char, Linux::character_type>);  <- this does not compiles
}

TEST_F(LinuxTester, testOptionalGraphicEnvironment)
{
    #ifndef __cpp_lib_optional
        ADD_FAILURE() << "Functions to handle 'graphic_environment' not implemented";
    #else
        CoutBufferSentinel coutSentinel; // to catch std::cout

        Linux linux;

        ASSERT_FALSE(linux.graphic_environment()); // not initialised

        constexpr const char* expectedGraphicEnvironment = "KDE";
        linux.set_graphic_environment(expectedGraphicEnvironment);

        ASSERT_EQ(expectedGraphicEnvironment, linux.graphic_environment().value());
    #endif
}
