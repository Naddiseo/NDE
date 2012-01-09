# NDE Scripting Language

A simple C subset that will integrate into the NDE game engine.


#### Resources

https://idlebox.net/2007/flex-bison-cpp-example/


## Built in types
* Integer
* Unsigned Integer
* Float
* String
* Vector
* Void
* Boolean
 
## Reserved words:

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
* event
* trigger

## What events are

Events in NDES are procedures that can be executed asynchronously, 
that is, they can be run in their own threads. Events that are to
be executed in their own thread are called with the trigger keyword,
which marks them as running in their own thread. Events that are called
without the trigger keyword are not run in their own thread.

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
        
        
	    event void onclick() { 
	    	this.myfloat = 1;
	    }
    }
    

    void main() {
        int a = 4, b;
        uint c = a;
        b = c+1 << a;

        MyDerivedClass cls();

        float foo = cls.myfloat >= 0 ? 1.0 : 2.0;

        string msg = cls.getHello("?");
        
        trigger cls.onclick();
	
    }

