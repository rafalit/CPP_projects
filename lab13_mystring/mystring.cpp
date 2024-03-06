#include "mystring.h"
using namespace std;

MyString::MyString() noexcept: size_(0), capacity_(initialBufferSize_), buffer_(new char[initialBufferSize_ + 1]) {
    buffer_[0] = '\0';
}
MyString::MyString(const char *text){
    buffer_ = new char[initialBufferSize_ + 1];
    buffer_[0] = '\0';
    size_ = 0;
    capacity_ = initialBufferSize_;
}

MyString::MyString(const MyString &text){
    size_ = text.size_;
    capacity_ = text.capacity_;
    buffer_ = new char[capacity_ + 1];
    strcpy(buffer_, text.buffer_);
}

void MyString::clear(){
    size_=0;
}

ostream& operator<<(std::ostream& os, const MyString &p){
    os<<p.buffer_;
    return os;
}

char& MyString::operator[](size_t index) {
    if(index>=size_){
        throw std::out_of_range("Index out of range");
    }
    return buffer_[index];
}

const char& MyString::operator[](size_t index) const {
    if(index>=size_){
        throw std::out_of_range("Index out of range");
    }
    return buffer_[index];
}

istream& operator>>(std::istream& is, MyString& p) {
    std::string temp;
    is >> temp;
    p = MyString(temp.c_str());
    return is;
}

void MyString::trim() {
    size_t first = 0;
    while (std::isspace(buffer_[first]))
        ++first;

    size_t last = size_ - 1;
    while (last > first && std::isspace(buffer_[last]))
        --last;

    size_ = last - first + 1;
    memmove(buffer_, buffer_ + first, size_ + 1);
}

MyString& MyString::operator+=(const MyString& other) {
    size_t newSize = size_ + other.size_;
    if (newSize > capacity_) {
        capacity_ = newSize + 1;
        char* newBuffer = new char[capacity_];
        strcpy(newBuffer, buffer_);
        delete[] buffer_;
        buffer_ = newBuffer;
    }
    strcat(buffer_, other.buffer_);
    size_ = newSize;
    return *this;
}
bool MyString::operator==(const MyString& other)const{
    return strcmp(buffer_, other.buffer_) == 0;
}

bool MyString::operator<(const MyString& other) const{
    return strcmp(buffer_, other.buffer_)<0;
}

set<MyString> MyString::getUniqueWords(const MyString& text){
    std::set<MyString> uniqueWords;
    std::string str(text.begin(), text.end());
    std::istringstream iss(str);

    std::string word;
    while (iss >> word) {
        uniqueWords.insert(MyString(word.c_str()));
    }

    return uniqueWords;
}
bool MyString::isPunctuation(char c) {
    return std::ispunct(static_cast<unsigned char>(c));
}

map<MyString, size_t> MyString::countWordsUsageIgnoringCases()const{
    map<MyString, size_t> wordCount;
    istringstream iss(buffer_);
    std::string word;
    while (iss >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), &MyString::isPunctuation), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        wordCount[MyString(word.c_str())]++;
    }

    return wordCount;
}

void MyString::toLower() {
    for (size_t i = 0; i < size_; ++i) {
        buffer_[i] = tolower(static_cast<unsigned char>(buffer_[i]));
    }
}
MyString& MyString::operator=(const MyString& other) {
    if (this == &other) {
        return *this;
    }

    delete[] buffer_;

    size_ = other.size_;
    capacity_ = other.capacity_;
    buffer_ = new char[capacity_];
    std::copy(other.buffer_, other.buffer_ + size_, buffer_);

    return *this;
}

////totalnie nie wiem co tu sie dzieje, ale jakos dziala
std::string MyString::generateRandomWord(size_t wordLength) {
    std::string randomWord;
    randomWord.reserve(wordLength);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis('A', 'Z');

    std::generate_n(std::back_inserter(randomWord), wordLength, [&dis, &gen]() {
        char c = static_cast<char>(dis(gen));
        return std::tolower(c);
    });

    return randomWord;
}

bool MyString::startsWith(const char* prefix) const {
    size_t prefixLength = strlen(prefix);
    if (size_ < prefixLength) {
        return false;
    }

    return strncmp(buffer_, prefix, prefixLength) == 0;
}

bool MyString::endsWith(const char* suffix) const {
    size_t suffixLength = strlen(suffix);
    if (size_ < suffixLength) {
        return false;
    }

    const char* suffixStart = buffer_ + (size_ - suffixLength);
    const char* suffixEnd = buffer_ + size_;
    const char* result = std::search(suffixStart, suffixEnd, suffix, suffix + suffixLength);

    return result != suffixEnd;
}

MyString& MyString::operator+=(char str) {
    size_t newSize = size_ + 1;
    if (newSize > capacity_) {
        capacity_ = newSize + 1;
        char* newBuffer = new char[capacity_];
        strcpy(newBuffer, buffer_);
        delete[] buffer_;
        buffer_ = newBuffer;
    }
    buffer_[size_] = str;
    buffer_[size_ + 1] = '\0';
    size_ = newSize;
    return *this;
}
const MyString MyString::separator_ = ", ";

MyString MyString::join(const std::vector<MyString>& strings) const
{
    MyString result;
    for (size_t i = 0; i < strings.size(); ++i)
    {
        result += strings[i];
        if (i != strings.size() - 1)
            result += separator_;
    }
    return result;
}
bool MyString::all_of(int (*predicate)(int)) const {
    for (size_t i = 0; i < size_; ++i) {
        if (!predicate(buffer_[i])) {
            return false;
        }
    }
    return true;
}