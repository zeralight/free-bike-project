#ifndef DBTOOLS_HPP
#define DBTOOLS_HPP

/* List of acceptable types for the attributes */
#define DOUBLE "double"
#define BOOLEAN "bool"
#define INT "int"
#define STRING "string"
#define DATE "date"

/* 
 * List of acceptable constraints for the attributes 
 * They can be combined using the | operator
 */
#define UNIQUE 1 << 0
#define NOT_NULL 1 << 1

template <class T>
struct AttrValue {
  std::string label;
  T value;

  AttrValue (std::string label, T value);
};


struct AttrType {
  std::string label;
  std::string type;

  AttrType (std::string label, std::string type);
  AttrType (std::string label, std::string type, int constraints);
};


template <class T>
struct Attr {
  std::string label;
  std::string type;
  T value;

  Attr (std::string label, std::string type, T value);
}
  

#endif DBTOOLS_HPP
