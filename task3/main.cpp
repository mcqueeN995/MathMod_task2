#include <iostream>

class A1 {
protected:
    int a1;
public:
    A1(int n = 0) {
        this->a1 = n;
        std::cout << "assign a value to a variable a1 : " << n << std::endl;
    }
    virtual void print() {
        std::cout << "A1" << std::endl;
    }
    virtual void show() {
        std::cout << "variable in A1: a1(" << a1 << ")" << std::endl;
    }
};

class A2 {
protected:
    int a2;
public:
    A2(int n = 0) {
        this->a2 = n;
        std::cout << "assign a value to a variable a2 : " << n << std::endl;
    }
    virtual void print() {
        std::cout << "A2" << std::endl;
    }
    virtual void show() {
        std::cout << "variable in A2: a2(" << a2 << ")" << std::endl;
    }
};

class A3 {
protected:
    int a3;
public:
    A3(int n = 0) {
        this->a3 = n;
        std::cout << "assign a value to a variable a3 : " << n << std::endl;
    }
    virtual void print() {
        std::cout << "A3" << std::endl;
    }
    virtual void show() {
        std::cout << "variable in A3: a3(" << a3 << ")" << std::endl;
    }
};

class B1 : virtual public A1, public A2, public A3 {
protected:
    int b1;
public:
    B1(int n = 0) : A1(n), A2(n), A3(n) {
        this->b1 = n;
        std::cout << "assign a value to a variable b1 : " << n << std::endl;
    }
    virtual void print() override {
        std::cout << "B1" << std::endl;
    }
    virtual void show() override {
        std::cout << "variables in B1: ";
        std::cout << "a1(" << a1 << ") ";
        std::cout << "a2(" << a2 << ") ";
        std::cout << "a3(" << a3 << ") ";
        std::cout << "b1(" << b1 << ")" << std::endl;
    }
};

class B2 : virtual public A1, public A2, public A3 {
protected:
    int b2;
public:
    B2(int n = 0) : A1(n), A2(n), A3(n) {
        this->b2 = n;
        std::cout << "assign a value to a variable b2 : " << n << std::endl;
    }
    virtual void print() override {
        std::cout << "B2" << std::endl;
    }
    virtual void show() override {
        std::cout << "variables in B2: ";
        std::cout << "a1(" << a1 << ") ";
        std::cout << "a2(" << a2 << ") ";
        std::cout << "a3(" << a3 << ") ";
        std::cout << "b2(" << b2 << ")" << std::endl;
    }
};

class C1 : virtual public B1, public B2 {
protected:
    int c1;
public:
    C1(int n = 0) : A1(n), B1(n), B2(n) {
        this->c1 = n;
        std::cout << "assign a value to a variable c1 : " << n << std::endl;
    }
    virtual void print() override {
        std::cout << "C1" << std::endl;
    }
    virtual void show() override {
        std::cout << "variables in C1: ";
        std::cout << "b1(" << b1 << ") ";
        std::cout << "b2(" << b2 << ") ";
        std::cout << "c1(" << c1 << ")" << std::endl;
    }
};

int main() {

  A1 a1(1);
  a1.print();
  a1.show();
  std::cout << std::endl;

  A2 a2(2);
  a2.print();
  a2.show();
  std::cout << std::endl;

  A3 a3(3);
  a3.print();
  a3.show();
  std::cout << std::endl;


  B1 b1(4);
  b1.print();
  b1.show();
  std::cout << std::endl;

  B2 b2(5);
  b2.print();
  b2.show();
  std::cout << std::endl;

  C1 c1(6);
  c1.print();
  c1.show();
  std::cout << std::endl;


  A1* base_ptr = &a1;
  base_ptr->print();
  base_ptr->show();
  std::cout << std::endl;

  base_ptr = static_cast<B1*>(&b1);
  base_ptr->print();
  base_ptr->show();
  std::cout << std::endl;

  base_ptr = static_cast<C1*>(&c1);
  base_ptr->print();
  base_ptr->show();
  std::cout << std::endl;

  return 0;
}


