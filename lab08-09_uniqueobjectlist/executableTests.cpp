#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <filesystem>

#include <boost/process/child.hpp>
#include <boost/process/io.hpp>

#include <gtest/gtest.h>

namespace
{
using namespace std;
using namespace ::testing;

struct ProgramOutputs
{
    std::vector<std::string> linesOfStdout_, linesOfStderr_;
    int exitCode_ {};
};

std::vector<std::string> readLinesOfFile(const string& filename);
std::string lines2Text(const std::vector<std::string>& lines);
std::filesystem::path getPathToIOTestFiles();

std::unique_ptr<boost::process::child> createSubprocessObject(const std::string& command, const std::string& inputFilePath, const std::string& inputText,
                                                              boost::process::ipstream& stdoutStream, boost::process::ipstream& stderrStream);
ProgramOutputs readOutputFromProcess(std::unique_ptr<boost::process::child>& c, boost::process::ipstream& stdoutStream, boost::process::ipstream& stderrStream);

ProgramOutputs runCommandReturningOutput(const std::string& command, const std::string& inputFilePath={}, const std::string& inputText={})
{
    using namespace std::chrono_literals;
    using namespace boost::process;

    ipstream stdoutStream, stderrStream;

    std::unique_ptr<child> c = createSubprocessObject(command, inputFilePath, inputText, stdoutStream, stderrStream);
    if (!c->wait_for(2s))
    {
        c->terminate();
        throw std::runtime_error("!Program was working too long, terminated!");
    }

    return readOutputFromProcess(c, stdoutStream, stderrStream);
}

std::unique_ptr<boost::process::child> createSubprocessObject(const std::string& command, const std::string& inputFilePath, const std::string& inputText,
                                                              boost::process::ipstream& stdoutStream, boost::process::ipstream& stderrStream)
{
    using namespace std::chrono_literals;
    using namespace boost::process;

    if (inputFilePath.empty() && inputText.empty())
    {
        return make_unique<child>(command, std_out > stdoutStream, std_err > stderrStream);
    }
    else if (inputFilePath.size())
    {
        return make_unique<child>(command, std_out > stdoutStream, std_err > stderrStream, std_in < inputFilePath);
    }
    else //if (inputText.size())
    {
        opstream stdinStream;
        stdinStream << inputText << endl;
        stdinStream.close();
        return make_unique<child>(command, std_out > stdoutStream, std_err > stderrStream, std_in < stdinStream);
    }
}

ProgramOutputs readOutputFromProcess(std::unique_ptr<boost::process::child>& c, boost::process::ipstream& stdoutStream, boost::process::ipstream& stderrStream)
{
    ProgramOutputs outputs;

    std::string line;
    while (stdoutStream && std::getline(stdoutStream, line) && !line.empty())
    {
        outputs.linesOfStdout_.emplace_back(std::move(line));
    }
    while (stderrStream && std::getline(stderrStream, line) && !line.empty())
    {
        outputs.linesOfStderr_.emplace_back(std::move(line));
    }

    c->wait();

    outputs.exitCode_ = c->exit_code();

    return outputs;
}

std::pair<std::string, string> getPairOfIOTestFilesForBasename(const std::string& baseFilename)
{
    auto basePath = getPathToIOTestFiles();
    auto inputFileBasename = baseFilename + ".in.txt";
    auto outputFileBasename = baseFilename + ".out.txt";

    auto inputFilePath = basePath / inputFileBasename;
    auto outputFilePath = basePath / outputFileBasename;

    if (std::filesystem::exists(inputFilePath) && std::filesystem::exists(outputFilePath))
    {
        return {inputFilePath, outputFilePath};
    }
    throw std::runtime_error("!Files '" + inputFilePath.string() + "', or '" + outputFilePath.string() + "' do not exist!");
}
std::filesystem::path getPathToIOTestFiles()
{
#ifdef CMAKE_CURRENT_SOURCE_DIR
    auto parentPath = std::filesystem::path(CMAKE_CURRENT_SOURCE_DIR);
#else
    auto parentPath = std::filesystem::path(__FILE__).parent_path();
#endif

    auto path2IoTestFiles = parentPath / "inputOutputData";
    if (std::filesystem::exists(path2IoTestFiles))
    {
        return path2IoTestFiles;
    }
    throw std::runtime_error("!Path '" + path2IoTestFiles.string() + "' does not exist!");
}

std::vector<std::string> readLinesOfFile(const string& filename)
{
    ifstream file(filename);
    if (!file)
    {
        throw std::invalid_argument("!Can not open file: " + filename);
    }
    std::vector<std::string> lines;

    std::string line;
    while (file && std::getline(file, line) && !line.empty())
    {
        lines.emplace_back(std::move(line));
    }
    return lines;
}

std::string lines2Text(const std::vector<std::string>& lines)
{
    std::string text;
    for (const auto& line : lines)
    {
        text += line + '\n';
    }
    return text;
}

void printLinesOfText(const std::vector<std::string>& lines)
{
    for (size_t i=0; i < lines.size(); ++i)
    {
        std::cout << i << ":" << lines[i] << '\n';
    }
}
} // namespace


struct CommandsParserSystemTester : ::testing::TestWithParam<std::string>
{
    std::string binaryPath;

    void SetUp() override
    {
#ifndef COMMANDS_PARSER_PATH
        ADD_FAILURE() << "CMake variable 'COMMANDS_PARSER_PATH' not defined!";
#else
        if (! std::filesystem::exists(COMMANDS_PARSER_PATH))
        {
            ADD_FAILURE() << "Binary '" << COMMANDS_PARSER_PATH << "' does not exists!";
        }
        binaryPath = COMMANDS_PARSER_PATH;
#endif
    }
};

TEST_F(CommandsParserSystemTester, executingOurProgramWithoutAnyInput_expectedNoOutput)
{
    const auto output = runCommandReturningOutput(binaryPath);

    ASSERT_EQ(0, output.linesOfStderr_.size());
    ASSERT_EQ(0, output.linesOfStdout_.size());   
    ASSERT_EQ(0, output.exitCode_);
}

TEST_F(CommandsParserSystemTester, testInvalidCommand)
{
    constexpr auto expectedLinesOfStderrOutput = 1;

    /// ponizszy "cytat" usłyszałem od pewnego programisty, proszę nie traktować go jako pewnika, bardziej jako sucharek:
    const auto inputText = "say Python is language for lazy C++ programmers, but Javascript is language for lazy Python programmers";
    const auto output = runCommandReturningOutput(binaryPath, /*inputFile=*/{}, inputText);
    ASSERT_EQ(0, output.linesOfStdout_.size())
            << "expectedNoOutput, but realOutput:\n"
            << lines2Text(output.linesOfStdout_);
    ASSERT_EQ(expectedLinesOfStderrOutput, output.linesOfStderr_.size());
    ASSERT_EQ(0, output.exitCode_);
}

TEST_P(CommandsParserSystemTester, testVariousScenariosUsingInputAndOutputFiles)
{
    const auto [inputFile, expectedOutputFile] = getPairOfIOTestFilesForBasename(GetParam());
    const auto expectedOutputFileLines = readLinesOfFile(expectedOutputFile);

    const auto output = runCommandReturningOutput(binaryPath, inputFile);
    ASSERT_EQ(expectedOutputFileLines.size(), output.linesOfStdout_.size())
            << "expectedOutput:\n"
            << lines2Text(readLinesOfFile(expectedOutputFile)) << '\n'
            << "realOutput:\n"
            << lines2Text(output.linesOfStdout_);
    ASSERT_EQ(0, output.linesOfStderr_.size()) << "unexpected stderror output:\n"
                                               << lines2Text(output.linesOfStderr_);
    ASSERT_EQ(0, output.exitCode_);

    for (size_t lineIndex=0; lineIndex < expectedOutputFileLines.size(); ++lineIndex)
    {
        ASSERT_EQ(expectedOutputFileLines[lineIndex], output.linesOfStdout_[lineIndex])
                << "indexOfLine=" << lineIndex << ", source file: " << inputFile << ", expected output file: " << expectedOutputFile;
    }
}

INSTANTIATE_TEST_SUITE_P(CommandsParserSystemTester,
                         CommandsParserSystemTester,
                         testing::Values("sumStringObject",
                                         "sumDoubleObject",
                                         "mulDifferentTypes",
                                         "getByIndexComplexObject"));

/* TEST_P(CommandsParserSystemTester, testVariousScenariosUsingInputAndOutputFiles) jest zamiast poniższych:
TEST_F(CommandsParserSystemTester, addingManyTypesThenSumOfStrings_expectedSumOfStringsPrinted)
{
    const auto [inputFile, expectedOutputFile] = getPairOfIOTestFilesForBasename("sumStringObject");
    const auto expectedOutputFileLines = readLinesOfFile(expectedOutputFile);

    const auto output = runCommandReturningOutput(binaryPath, inputFile);
    ASSERT_EQ(expectedOutputFileLines.size(), output.linesOfStdout_.size());
    ASSERT_EQ(0, output.linesOfStderr_.size());
    ASSERT_EQ(0, output.exitCode_);

    for (size_t lineIndex=0; lineIndex < expectedOutputFileLines.size(); ++lineIndex)
    {
        ASSERT_EQ(expectedOutputFileLines[lineIndex], output.linesOfStdout_[lineIndex])
                << "indexOfLine=" << lineIndex << ", source file: " << inputFile << ", expected output file: " << expectedOutputFile;
    }
}

TEST_F(CommandsParserSystemTester, addingManyTypesThenSumOfDoubles_expectedSumOfDoublesPrinted)
{
    const auto [inputFile, expectedOutputFile] = getPairOfIOTestFilesForBasename("sumDoubleObject");
    const auto expectedOutputFileLines = readLinesOfFile(expectedOutputFile);

    const auto output = runCommandReturningOutput(binaryPath, inputFile);
    ASSERT_EQ(expectedOutputFileLines.size(), output.linesOfStdout_.size());
    ASSERT_EQ(0, output.linesOfStderr_.size());
    ASSERT_EQ(0, output.exitCode_);

    for (size_t lineIndex=0; lineIndex < expectedOutputFileLines.size(); ++lineIndex)
    {
        ASSERT_EQ(expectedOutputFileLines[lineIndex], output.linesOfStdout_[lineIndex])
                << "indexOfLine=" << lineIndex << ", source file: " << inputFile << ", expected output file: " << expectedOutputFile;
    }
}

TEST_F(CommandsParserSystemTester, multiplyAllObjectsThenSum_expectedSumDoubledOfAllTypes)
{
    const auto [inputFile, expectedOutputFile] = getPairOfIOTestFilesForBasename("mulDifferentTypes");
    const auto expectedOutputFileLines = readLinesOfFile(expectedOutputFile);

    const auto output = runCommandReturningOutput(binaryPath, inputFile);
    ASSERT_EQ(expectedOutputFileLines.size(), output.linesOfStdout_.size());
    ASSERT_EQ(0, output.linesOfStderr_.size());
    ASSERT_EQ(0, output.exitCode_);

    for (size_t lineIndex=0; lineIndex < expectedOutputFileLines.size(); ++lineIndex)
    {
        ASSERT_EQ(expectedOutputFileLines[lineIndex], output.linesOfStdout_[lineIndex])
                << "indexOfLine=" << lineIndex << ", source file: " << inputFile << ", expected output file: " << expectedOutputFile;
    }
}

TEST_F(CommandsParserSystemTester, sumStringObjectWhenNoStringObject_expectedNoOutput)
{
    const auto [inputFile, expectedOutputFile] = getPairOfIOTestFilesForBasename("sumStringObjectWhenNoStringObject");
    const auto expectedOutputFileLines = readLinesOfFile(expectedOutputFile);

    const auto output = runCommandReturningOutput(binaryPath, inputFile);
    ASSERT_EQ(expectedOutputFileLines.size(), output.linesOfStdout_.size());
    ASSERT_EQ(0, output.linesOfStderr_.size());
    ASSERT_EQ(0, output.exitCode_);

    for (size_t lineIndex=0; lineIndex < expectedOutputFileLines.size(); ++lineIndex)
    {
        ASSERT_EQ(expectedOutputFileLines[lineIndex], output.linesOfStdout_[lineIndex])
                << "indexOfLine=" << lineIndex << ", source file: " << inputFile << ", expected output file: " << expectedOutputFile;
    }
}
*/
