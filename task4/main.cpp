#include <cstring>
#include <iostream>

class BaseString {
protected:
    char* buffer;
    size_t length;

    void allocate(const char* data, size_t len) {
        if (data && len > 0) {
            buffer = new char[len + 1];
            std::memcpy(buffer, data, len);
            buffer[len] = '\0';
            length = len;
        } else {
            buffer = new char[1];
            buffer[0] = '\0';
            length = 0;
        }
    }

public:
    BaseString(){
        buffer = nullptr;
        length = 0;
        allocate("", 0);
    }

    explicit BaseString(const char* str) {
        if (str) {
            length = std::strlen(str);
            allocate(str, length);
        } else {
            allocate("", 0);
        }
    }

    BaseString(const BaseString& other) {
        allocate(other.buffer, other.length);
    }
    virtual ~BaseString() {
        delete[] buffer;
    }

    BaseString& operator=(const BaseString& other) {
        if (this != &other) {
            delete[] buffer;
            allocate(other.buffer, other.length);
        }
        return *this;
    }
    size_t size() const {
      return length;
    }
    const char* c_str() const {
      return buffer;
    }

    BaseString operator+(const BaseString& other) const {
        BaseString result;
        result.length = length + other.length;
        result.buffer = new char[result.length + 1];
        std::strcpy(result.buffer, buffer);
        std::strcat(result.buffer, other.buffer);
        return result;
    }

    bool operator==(const BaseString& other) const {
        if (length != other.length) return false;
        return std::strcmp(buffer, other.buffer) == 0;
    }

    bool operator!=(const BaseString& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const BaseString& str) {
        os << str.buffer;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, BaseString& str) {
        char tmp[1024];
        is.getline(tmp, sizeof(tmp));
        str = BaseString(tmp);
        return is;
    }
};

class ChildString : public BaseString {
  public:
    ChildString() : BaseString(){}
    explicit ChildString(const char* str, int extra = 0) : BaseString(str){}
    ChildString(const ChildString& other) : BaseString(other){}
    virtual ~ChildString() {}
    int countSubstring(const char* substr) const {
        if (!substr || substr[0] == '\0') return 0;
        const size_t subLen = std::strlen(substr);
        if (subLen == 0 || subLen > length) return 0;

        int count = 0;
        const char* pos = buffer;
        while ((pos = std::strstr(pos, substr)) != nullptr) {
            count++;
            pos++;
        }
        return count;
    }
};


int main() {


    BaseString empty;
    BaseString hello("Hello");
    BaseString world("World");
    BaseString copy = hello;

    std::cout << "Empty: '" << empty << "' (" << empty.size() << " chars)" << std::endl;
    std::cout << "Hello: '" << hello << "' (" << hello.size() << " chars)" << std::endl;
    std::cout << "Copy: '" << copy << "' (copy of hello)" << std::endl;

    BaseString test;
    test = world;
    std::cout << "\nAfter assignment:\nTest: '" << test << "'" << std::endl;

    BaseString helloWorld = hello + BaseString(" ") + world;
    std::cout << "\nConcatenation:\n" << helloWorld << std::endl;

    std::cout << "\nComparison:\nhello == copy: " << (hello == copy) << "\nhello != world: " << (hello != world) << std::endl;


    ChildString s1("ababab");
    ChildString s2("aaaaa");
    ChildString s3("hello world");
    ChildString s4("test test test");

    std::cout << "\nCount substring:\n"
              << "1. 'ab' in 'ababab': " << s1.countSubstring("ab") << " (expected 3)\n"
              << "2. 'aaa' in 'aaaaa': " << s2.countSubstring("aaa") << " (expected 3)\n"
              << "3. 'xyz' in 'hello world': " << s3.countSubstring("xyz") << " (expected 0)\n"
              << "4. 'test' in 'test test test': " << s4.countSubstring("test") << " (expected 3)"
              << std::endl;

    return 0;
}