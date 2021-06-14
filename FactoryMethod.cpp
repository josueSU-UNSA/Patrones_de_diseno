#include<iostream>

// La interfaz de Producto declara las operaciones que deben implementar todos los productos concretos.
class Product {
 	public:
  		virtual ~Product() {}
  		virtual std::string Operation() const = 0;
};

// Concrete Products proporciona varias implementaciones de la interfaz del producto.
class ConcreteProduct1 : public Product {
 	public:
  		std::string Operation() const override {
    		return "{Resultado de ConcreteProduct1}";
  		}
};
class ConcreteProduct2 : public Product {
 	public:
  		std::string Operation() const override {
    		return "{Resultado de ConcreteProduct2}";
  		}
};

/*
La clase Creator declara factory method que se supone que devuelve un objeto de una clase de 
producto. Las subclases del Creator generalmente proporcionan la implementacion de este metodo.
*/
class Creator {
	/*Tenga en cuenta que el Creator tambien puede proporcionar alguna implementacion 
	predeterminada del método de fabrica.*/
 	public:
  		virtual ~Creator(){};
  		virtual Product* FactoryMethod() const = 0;
		/*
		Tambien tenga en cuenta que, a pesar de su nombre, la responsabilidad principal 
		del Creator es no crear productos. Por lo general, contiene alguna logica 
		empresarial central que	se basa en objetos Producto, devueltos por el metodo 
		de fabrica. Las subclases pueden cambiar indirectamente esa logica empresarial 
		anulando el método de fabrica y devolver un tipo de producto diferente.
		*/

    	std::string SomeOperation() const {
  		// Llama al metodo de fabrica para crear un objeto Producto.
   		Product* product = this->FactoryMethod();
    	// Ahora, usa el producto.
	    std::string result = "Creator: El mismo codigo del creador acaba de funcionar con " + product->Operation();
	    delete product;
	    return result;
	  	}
};

// Concrete Creators anula el metodo de fabrica para cambiar el tipo de producto resultante.
class ConcreteCreator1 : public Creator {
	/*
	Tenga en cuenta que la firma del metodo todavia utiliza el tipo de producto abstracto, 
	a pesar de que el producto concreto se devuelve realmente del metodo. Esto forma en 
	que el Creador puede permanecer independiente de clases concretas de productos.
	*/
	public:
	  	Product* FactoryMethod() const override {
	    	return new ConcreteProduct1();
	  	}
	};

class ConcreteCreator2 : public Creator {
	public:
	  	Product* FactoryMethod() const override {
	    	return new ConcreteProduct2();
	 	}
};

/*
El codigo del cliente funciona con una instancia de un creador concreto, aunque 
a traves de su interfaz base. Siempre que el cliente siga trabajando con el creador 
a traves de la interfaz base, puede pasarla a la subclase de cualquier creador.
*/
void ClientCode(const Creator& creator) {
    std::cout << "Client: No conozco la clase del creador, pero aun funciona.\n" << creator.SomeOperation() << std::endl;

}
 
//La aplicacion elige el tipo de creador en funcion de la configuracion o ambiente.
int main() {
  	std::cout << "App: lanzada con ConcreteCreator1.\n";
  	Creator* creator = new ConcreteCreator1();
	ClientCode(*creator);
	std::cout << std::endl;
	std::cout << "App: lanzada con ConcreteCreator2.\n";
	Creator* creator2 = new ConcreteCreator2();
	ClientCode(*creator2);
	
	delete creator;
	delete creator2;
	return 0;
}
