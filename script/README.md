# NDE Scripting Language

A simple C subset that will integrate into the NDE game engine.

### Built in types
* Integer
* Unsigned Integer
* Float
* String
* Vector
* Void
* Boolean
 
### Reserved words:

* int
* uint
* float
* string
* vector
* bool
* void
* return
* if
* while
* for
* break
* continue
* class

	class MyClass {
		float myfloat = 0.0;
		string hello = "Foo";
		
		string getHello() {
			return this.hello;
		}
	}
	
	class MyDerivedClass : MyClass {
		string getHello(string suffix = "!") {
			return "World" + suffix;
		}
	}
	
    void main() {
    	int a = 4, b;
    	uint c = a;
    	b = c+1 << a;
    	
    	MyDerivedClass cls();
    	
    	float foo = cls.myfloat >= 0 ? 1.0 : 2.0;
    	
    	string msg = cls.getHello("?");
    	
    }

