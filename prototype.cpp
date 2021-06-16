#include<iostream>
#include<conio.h>
#include<vector>
using namespace std;

// Patrón de diseño de prototipos
//
// Intención: le permite copiar objetos existentes sin hacer que su código dependa de
// sus clases.

enum Type {
  PROTOTYPE_1 = 0,
  PROTOTYPE_2
};

/**
  * La clase de ejemplo que tiene capacidad de clonación. Veremos cómo los valores de campo
  * con diferentes tipos se clonará.
**/

class Prototype {
 protected:
  string prototype_name_;
  float prototype_field_;

 public:
  Prototype() {}
  Prototype(string prototype_name)
      : prototype_name_(prototype_name) {
  }
  virtual ~Prototype() {}
  virtual Prototype *Clone() const = 0;
  virtual void Method(float prototype_field) {
    this->prototype_field_ = prototype_field;
    std::cout << "Call Method from " << prototype_name_ << " with field : " << prototype_field << std::endl;
  }
};

/**
  * ConcretePrototype1 es una subclase de prototipo e implementa el método de clonación
  * En este ejemplo, todos los miembros de datos de la clase Prototype están en la pila. Si usted
  * tener punteros en sus propiedades, por ejemplo: String * name_, necesitará
  * implementar el Copy-Constructor para asegurarse de tener una copia profunda del
  * método de clonación
**/

class ConcretePrototype1 : public Prototype {
 private:
  float concrete_prototype_field1_;

 public:
  ConcretePrototype1(string prototype_name, float concrete_prototype_field)
      : Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field) {
  }

/**
    * Observe que el método Clone devuelve un puntero a un nuevo ConcretePrototype1
    * réplica. entonces, el cliente (que llama al método clon) tiene la responsabilidad
    * para liberar ese recuerdo. Si tienes conocimiento de puntero inteligente, tal vez prefieras
    * utilice puntero_unico aquí.
**/

  Prototype *Clone() const override {
    return new ConcretePrototype1(*this);
  }
};

class ConcretePrototype2 : public Prototype {
 private:
  float concrete_prototype_field2_;

 public:
  ConcretePrototype2(string prototype_name, float concrete_prototype_field)
      : Prototype(prototype_name), concrete_prototype_field2_(concrete_prototype_field) {
  }
  Prototype *Clone() const override {
    return new ConcretePrototype2(*this);
  }
};

/**
  * En PrototypeFactory tienes dos prototipos de hormigón, uno para cada hormigón
  * clase de prototipo, por lo que cada vez que desee crear una viñeta, puede utilizar la
  * los existentes y clonarlos.
**/

class PrototypeFactory {
 private:
  std::unordered_map<Type, Prototype *, std::hash<int>> prototypes_;

 public:
  PrototypeFactory() {
    prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1 ", 50.f);
    prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2 ", 60.f);
  }

/* Tenga cuidado de liberar toda la memoria asignada. Nuevamente, si tiene punteros inteligentes *, será mejor usarlo aquí. */

  ~PrototypeFactory() {
    delete prototypes_[Type::PROTOTYPE_1];
    delete prototypes_[Type::PROTOTYPE_2];
  }

  /**
   * Observe aquí que solo necesita especificar el tipo de prototipo que
    *quieres y el método creará a partir del objeto con este tipo.
   **/
  Prototype *CreatePrototype(Type type) {
    return prototypes_[type]->Clone();
  }
};

void Client(PrototypeFactory &prototype_factory) {
  std::cout << "Let's create a Prototype 1\n";

  Prototype *prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
  prototype->Method(90);
  delete prototype;

  std::cout << "\n";

  std::cout << "Let's create a Prototype 2 \n";

  prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
  prototype->Method(10);

  delete prototype;
}

int main() {
  PrototypeFactory *prototype_factory = new PrototypeFactory();
  Client(*prototype_factory);
  delete prototype_factory;

  return 0;
}
