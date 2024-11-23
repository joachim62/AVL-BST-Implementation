PS C:\Users\user\CLionProjects\untitled1> g++ -std=c++17 examples/grade_system.cpp -o grade_system
In file included from examples/grade_system.cpp:1:0:
examples/../include/BST.h: In instantiation of 'bool ds::BST<T>::contains(const T&) const [with T = Student]':
examples/grade_system.cpp:53:43:   required from here
examples/../include/BST.h:156:23: error: no match for 'operator==' (operand types are 'const Student' and 'Student')
             if (value == current->data) return true;
                 ~~~~~~^~~~~~~~~~~~~~~~
