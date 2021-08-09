___pybind11 exercise___       

1.  __compile__ makefile cmake python settools      
2.  for brevity, all code examples assume that the following two lines arre present:    
    ```
    #include <pybind11/pybind11.h>
    namespace py = pybind11;
    ```c++
    some features may require additional headers, but it doesn't matter.    
3.  code:     
    ```
    #include <pybind11/pybind11.h>

    int add(int i, int j) {
      return i + j;
    }

    PYBIND11_MODULE(example, m) {
      m.doc() = "pybind11 example plugin"; // optional module docstring
      m.def("add", &add, "A function which adds two numbers");
    } 
    ```c++
    this code is for simplicity, put this function and the binding code into a file. The PYBIND11_MODULE() macro creates a function that will be called when an import statement is issued from with Python. The module name(example) is given as the first macro argument(it should no be in quotes). The second argument(m) defines a variable of type `py::module` which is the main interface for creating bindings. the method `module::def` generates binding code that exposes the add() function to Python.     
