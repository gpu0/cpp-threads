## README

### ch02.1

for ```void operator()() const``` you cannot change the value of members. So, you use ```void operator()()```
Make sure the data and std::thread object is not evicted before finishing the thread. The book suggests to use
RAII technique (Resource Acquisition Is Initialization). (Check ch02.3.cpp)

In C++, the compiler automatically generates the default constructor, copy constructor, copy-assignment operator, and destructor for a type if it does not declare its own. These functions are known as the special member functions, and they are what make simple user-defined types in C++ behave like structures do in C. That is, you can create, copy, and destroy them without any additional coding effort. C++11 brings move semantics to the language and adds the move constructor and move-assignment operator to the list of special member functions that the compiler can automatically generate. [Derived from MSDN page].

1. If any constructor is explicitly declared, then no default constructor is automatically generated.
2. If a virtual destructor is explicitly declared, then no default destructor is automatically generated.
3. If a move constructor or move-assignment operator is explicitly declared, then:

	No copy constructore is automatically generated.
	No copy-assignment operator is automatically generated.

4. If a copy constructor, copy-assignment operator, move constructor, move-assignment operator or destructor is explicitly declared, then:

	No move constructor is automatically generated.
	No move-assignment operator is automatically generated.


When a function is exited, the objects are destroyed in reverse order.

std::thread object is not copyable.

The passed arguments to thread constructor are copied to a local thread storage location. If you pass a reference to thread constructor, its value is read and not updated.
To get thread update the variable, the reference can be passed by using ```std::ref(variable)```.


