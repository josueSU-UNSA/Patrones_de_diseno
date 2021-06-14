#include <iostream>
#include <conio.h>
using namespace std;
//Cada prroducto distinto de un familia de productos debe tener una interfaz básica ,todas las variantes del producto deben tener esta interfaz
class AbstractProductoA {
 public:
  virtual ~AbstractProductoA(){};
  virtual string UsefulFunctionA() const = 0;
};
//Los productos concretes son creados por los Factorys concretes
class ConcreteProductoA1 : public AbstractProductoA {
 public:
  string UsefulFunctionA() const override {
    return "El resultado del producto A1.";
  }
};
class ConcreteProductoA2 : public AbstractProductoA {
  string UsefulFunctionA() const override {
    return "El resultado del producto A2.";
  }
};
//Aqui esta la interfaz base de otro producto.Todos estos pueden interactuar entre si ,pero la interacción adecuada es posible entre productos de una misma variante concrete 
class AbstractProductoB {
  //El producto B es independiente por sus metodos al anterior producto
 public:
  virtual ~AbstractProductoB(){};
  virtual string UsefulFunctionB() const = 0;
  //El producto B puede colaborar con el producto A , ya que el Abstract factory nos ayuda a garantizar que todos los productos sean de la misma variante lo que los hace compatibles
  
  virtual string AnotherUsefulFunctionB(const AbstractProductoA &collaborator) const = 0;
};
//Los productos Concrete son creados por sus respectivos Concrete Factories.

class ConcreteProductoB1 : public AbstractProductoB {
 public:
  string UsefulFunctionB() const override {
    return "El resultado del producto B1.";
  }
  //La variante, Producto B1, solo puede funcionr correctamente con la variante Producto A1. Pero, acepta cualquier instancia del AbstractProductoA como argumento
  string AnotherUsefulFunctionB(const AbstractProductoA &collaborator) const override {
    const string result = collaborator.UsefulFunctionA();
    return "El resultado del B1 colaborando con ( " + result + " )";
  }
};

class ConcreteProductoB2 : public AbstractProductoB {
 public:
  string UsefulFunctionB() const override {
    return "El resultado of del producto B2.";
  }
  //La variant Producto B2, solo funciona correctamente con la variante Producto A2. Pero, acepta una instancia de AbstractProductoA como argumento
  string AnotherUsefulFunctionB(const AbstractProductoA &collaborator) const override {
    const string result = collaborator.UsefulFunctionA();
    return "El resultado del B2 colaborando con ( " + result + " )";
  }
};
class AbstractFactory {
 public:
  virtual AbstractProductoA *crearProductoA() const = 0;
  virtual AbstractProductoB *crearProductoB() const = 0;
};
class ConcreteFactory1 : public AbstractFactory {
 public:
  AbstractProductoA *crearProductoA() const override {
    return new ConcreteProductoA1();
  }
  AbstractProductoB *crearProductoB() const override {
    return new ConcreteProductoB1();
  }
};
//Cada Factory Concrete tiene un correspondiente variante producto .
class ConcreteFactory2 : public AbstractFactory {
 public:
  AbstractProductoA *crearProductoA() const override {
    return new ConcreteProductoA2();
  }
  AbstractProductoB *crearProductoB() const override {
    return new ConcreteProductoB2();
  }
};
void ClientCode(const AbstractFactory &factory) {
  const AbstractProductoA *product_a = factory.crearProductoA();
  const AbstractProductoB *product_b = factory.crearProductoB();
  cout << product_b->UsefulFunctionB() << "\n";
  cout << product_b->AnotherUsefulFunctionB(*product_a) << "\n";
  delete product_a;
  delete product_b;
}

int main() {
  cout << "Cliente: Probando el codigo cliente con el primer tipo factory :"<<endl;
  ConcreteFactory1 *f1 = new ConcreteFactory1();
  ClientCode(*f1);
  delete f1;
  cout << endl;
  cout << "Cliente: Probando el codigo cliente con el segundo tipo factory :"<<endl;
  ConcreteFactory2 *f2 = new ConcreteFactory2();
  ClientCode(*f2);
  delete f2;
  getch();
  return 0;
}