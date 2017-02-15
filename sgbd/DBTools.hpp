#ifndef DBTOOLS_HPP
#define DBTOOLS_HPP

#include <iostream>
#include <cstring>

#include <tulip/StringProperty.h>
#include <tulip/DoubleProperty.h>
#include <tulip/IntegerProperty.h>
#include <tulip/BooleanProperty.h>

#define N_TYPES 4

/* List of acceptable types for the attributes */
enum db_types {
  INT,
  DOUBLE,
  BOOL,
  STRING
};

/*
#define INT int
#define DOUBLE double
#define BOOL bool
#define STRING std::string
*/
// DATE à rajouter pourquoi pas ?

/* 
 * List of acceptable constraints for the attributes 
 * They can be combined using the | operator
 */
#define NONE 0 
#define UNIQUE 1 << 0
#define NOT_NULL 1 << 1

//typedef int t_constr;

template <int T>
struct Type;

template <>
struct Type<INT> {
  typedef tlp::IntegerProperty propType;
  typedef int type;
};

template <>
struct Type<DOUBLE> {
  typedef tlp::DoubleProperty propType;
  typedef double type;
};

template <>
struct Type<BOOL> {
  typedef tlp::BooleanProperty propType;
  typedef bool type;
};

template <>
struct Type<STRING> {
  typedef tlp::StringProperty propType;
  typedef std::string type;
};


/*
 * @brief This class is an interface for the use of Attribute objects. 
 * It provides a type / subtype relation between Attribute / Attr. 
 * It may necessarily be used in order to manipulate arrays of Attr objects.
 * 
 * Example of typical use :
 * @code
 * Attribute * tab[2] = {new Attr("firstname"), new Attr("name")};
 * @endcode
 */
class Attribute {
public:
  virtual std::string getLabel() const =0;
  virtual int getConstraints() const =0;
  virtual std::string getTypeName() const =0;
  virtual void getValue(void *) const =0;
 
  virtual Attribute * clone() const =0;
  virtual Attribute * operator=(const Attribute *) =0;

  virtual void print() const =0;

  virtual void setProperty(void *) =0;
  virtual void set(const void *) =0;
  
protected:
  virtual void setLabel(const std::string &) =0;
  virtual void setConstraints(int) =0;
  virtual void setTypeName(const std::string &) =0;
  virtual void setValue(const void *) =0;
};


/*
 * Example of instanciation
 * @code
 * Attribute * attr = new Attr<INT>("age", 42);
 * @endcode
 */
template <int T>
class Attr : public virtual Attribute {
  std::string label;
  std::string typeName;
  int constraints;

  typename Type<T>::type value;
  typename Type<T>::propType * prop;

private:
  void setLabel(const std::string &newLabel);
  void setConstraints(int newConstraints);
  void setTypeName(const std::string &newTypeName);
  void setValue(const void * newValue);

public:
  Attr(const std::string &label);
  Attr(const std::string &label, typename Type<T>::type value);
  //Attr(const std::string &label, t_constr constraints);

  
  Attribute * operator=(const Attribute * attr);

  std::string getLabel() const;
  int getConstraints() const;
  std::string getTypeName() const;
  void getValue(void * dst) const;

  void setProperty(void *);
  void set(const void *);

  Attribute * clone() const;

  void print() const;

private:
  void init();
};


/* Implémentation des templates */
/**********************************************************************/

template <int T>
Attr<T>::Attr (const std::string &label) {
  this->init(); // deux objets créés ? -> utiliser méthode privée plutot
  this->label = label;
  this->constraints = NONE;
}

template <int T>
Attr<T>::Attr (const std::string &label, typename Type<T>::type value) {
  this->init();
  this->label = label;
  this->value = value;
  this->constraints = NONE;
}

/*
template <int T>
Attr<T>::Attr (const std::string &label, t_constr constraints) {
  Attr();
  this->label = label;
  this->constraints = constraints;
}
*/

template <int T>
Attribute * Attr<T>::operator=(const Attribute * attr) {
  this->label = attr->getLabel();
  attr->getValue(&(this->value));
  this->constraints = attr->getConstraints();
  this->typeName = attr->getTypeName();
  return this;
}

template <int T>
std::string Attr<T>::getLabel() const {
  return this->label;
}

template <int T>
int Attr<T>::getConstraints() const{
  return this->constraints;
}

template <int T>
std::string Attr<T>::getTypeName() const {
  return this->typeName;
}

template <int T>
void Attr<T>::getValue(void * dst) const {
  typename Type<T>::type * _dst = (typename Type<T>::type *) dst;
  *_dst = this->value;
}

template <int T>
void Attr<T>::setLabel(const std::string &newLabel) {
  this->label = newLabel;
}

template <int T>
void Attr<T>::setConstraints(int newConstraints) {
  this->constraints = newConstraints;
}

template <int T>
void Attr<T>::setTypeName(const std::string &newTypeName) {
  this->typeName = newTypeName;
}

template <int T>
void Attr<T>::setValue(const void * newValue) {
  const typename Type<T>::type * _newValue = (typename Type<T>::type *) newValue;
  this->value = *_newValue;
}

template <int T>
void Attr<T>::setProperty(void * prop) {
  this->prop = (typename Type<T>::propType *) prop;
}

template <int T>
void Attr<T>::set(const void * value) {
  typename Type<T>::type _value = *((typename Type<T>::type *) value);
  this->prop->setAllNodeValue(_value);
}

template <int T>
Attribute * Attr<T>::clone() const {
  Attr<T> * tmp = new Attr<T>(this->label);
  tmp->setConstraints(this->constraints);
  tmp->setTypeName(this->typeName);
  tmp->setValue(&(this->value));
  return tmp;
}

template <int T>
void Attr<T>::print() const {
  std::cout << "== " + this->label + " ==" << std::endl;
  std::cout << "type\t\t" + this->typeName << std::endl;
  std::cout << "constraints\t\t" + this->constraints << std::endl;
  std::cout << "value\t\t";
  std::cout << this->value;
  std::cout << std::endl;
}

#endif //DBTOOLS_HPP
