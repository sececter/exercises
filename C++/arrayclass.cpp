#include <iostream> 
#include <iomanip> 
#include <stdexcept> 
using namespace std; 
 
template <typename T> 
class Array 
{ 
  private: 
    T* elements;                           // Array of type T 
    size_t size;                           // Number of elements in the array 
 
  public: 
    explicit Array(size_t arraySize);      // Constructor 
    Array(const Array& theArray);          // Copy Constructor 
    ~Array();                              // Destructor 
    T& operator[](size_t index);             // Subscript operator 
    const T& operator[](size_t index) const; // Subscript operator 
    Array& operator=(const Array& rhs);              // Assignment operator 
}; 
 
// Constructor 
template <typename T>                      // This is a template with parameter T 
Array<T>::Array(size_t arraySize) : size(arraySize) 
{ 
  elements = new T[size]; 
} 
 
// Copy Constructor 
template <typename T> 
Array<T>::Array(const Array& theArray) { 
  size = theArray.size; 
  elements = new T[size]; 
  for(int i = 0 ; i < size ; i++) 
    elements[i] = theArray.elements[i]; 
} 
 
// Destructor 
template <typename T> 
Array<T>::~Array() 
{ 
  delete[] elements; 
} 
 
// Subscript operator 
template <typename T> 
T& Array<T>::operator[](size_t index) 
{ 
  if(index < 0 || index >= size) 
    throw std::out_of_range(index < 0 ? "Negative index" : "Index too large"); 
 
  return elements[index]; 
} 
 
// Subscript operator for const objects 
template <typename T> 
const T& Array<T>::operator[](size_t index) const 
{ 
  if(index < 0 || index >= size) 
    throw std::out_of_range(index < 0 ? "Negative index" : "Index too large"); 
 
  return elements[index]; 
} 
 
// Assignment operator 
template <typename T> 
Array<T>& Array<T>::operator=(const Array& rhs) 
{ 
  if(&rhs == this)                            // If lhs == rhs 
    return *this;                             //  just return lhs 
 
  if(elements)                                // If lhs array exists 
    delete[]elements;                         // then release the free store memory 
 
  size = rhs.size; 
  elements = new T[rhs.size]; 
  for(int i = 0 ; i < size ; i++) 
    elements[i] = rhs.elements[i]; 
} 
 
class Box 
{ 
  public: 
    Box(double lengthValue = 1.0, double widthValue = 1.0, double heightValue = 1.0); 
 
    // Function to show the volume of an object 
    void showVolume() const; 
 
    // Function to calculate the volume of a Box object 
    virtual double volume() const; 
 
    // Get values of data members 
    double getLength() const { return length; } 
    double getWidth() const { return width; } 
    double getHeight() const { return height; } 
 
  protected: 
    double length; 
    double width; 
    double height; 
}; 
Box::Box(double lvalue, double wvalue, double hvalue) : 
                                  length(lvalue), width(wvalue), height(hvalue) {} 
 
void Box::showVolume() const { 
  cout << "Box usable volume is " << volume() << endl; 
} 
 
double Box::volume() const { 
  return length * width * height; 
} 
 
int main() 
{ 
  const int doubleCount = 50; 
  Array<double> values(doubleCount);        // Class constructor instance created 
 
  try 
  { 
    for(int i = 0 ; i < doubleCount ; i++) 
      values[i] = i + 1;                    // Member function instance created 
 
    cout << endl << "Sums of pairs of elements:"; 
    int lines = 0; 
    for(int i = doubleCount - 1 ; i >= 0 ; i--) 
      cout << (lines++ % 5 == 0 ? "\n" : "") 
           << std::setw(5) << values[i] + values[i - 1]; 
  } 
  catch(const std::out_of_range& ex) 
  { 
    cout << endl <<"out_of_range exception object caught! " << ex.what(); 
  } 
 
  try 
  { 
    const int boxCount = 10; 
    Array<Box> boxes(boxCount);             // Template instance created 
    for(int i = 0 ; i <= boxCount ; i++) 
      cout << endl << "Box volume is " << boxes[i].volume(); // Member instance created 
  } 
  catch(const std::out_of_range& ex) 
  { 
    cout << endl << "out_of_range exception object caught! " << ex.what(); 
  } 
 
  cout << endl; 
  return 0; 
}  


