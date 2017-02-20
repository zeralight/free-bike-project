#ifndef DBTOOLS_HPP
#define DBTOOLS_HPP

#include <iostream>
#include <cstring>

#include <tulip/Node.h>
#include <tulip/StringProperty.h>
#include <tulip/DoubleProperty.h>
#include <tulip/IntegerProperty.h>
#include <tulip/BooleanProperty.h>

//#include "Entity.hpp"

#define N_TYPES 4

/* List of acceptable types for the attributes */

#define INT int
#define DOUBLE double
#define BOOL bool
#define STRING std::string
// DATE à rajouter pourquoi pas ?

/* 
 * List of acceptable constraints for the attributes 
 * They can be combined using the | operator
 */
#define NONE 0 
#define UNIQUE 1 << 0
#define NOT_NULL 1 << 1

/*
 * Direction options
 */
enum directionValues {
  IN,
  OUT,
  INOUT
};

typedef directionValues direction;

class Entity;
class Relation;


template <class T>
struct TlpProp;

template <>
struct TlpProp<INT> {
  typedef tlp::IntegerProperty type;
};

template <>
struct TlpProp<DOUBLE> {
  typedef tlp::DoubleProperty type;
};

template <>
struct TlpProp<BOOL> {
  typedef tlp::BooleanProperty type;
};

template <>
struct TlpProp<STRING> {
  typedef tlp::StringProperty type;
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

  friend Entity;
  friend Relation;
  
public:
  virtual std::string getLabel() const =0;
  virtual int getConstraints() const =0;
  virtual std::string getTypeName() const =0;
  virtual void getProperty(void **) const =0;
  virtual void getValue(void *) const =0;

  virtual void setLabel(const std::string &) =0;
  virtual void setValue(const void *) =0;
 
  virtual Attribute * clone() const =0;
  virtual bool isEqual(tlp::node &) const =0;
  virtual bool isEqual(tlp::edge &) const =0;
  virtual void print() const =0;

  virtual Attribute * operator=(const Attribute *) =0;
  
protected:
  virtual void setConstraints(int) =0;
  virtual void setTypeName(const std::string &) =0;
  virtual void setProperty(const void *) =0;
  virtual void setProperty(const Attribute *) =0;
  virtual void setNodeValue(tlp::node &) const =0;
  virtual void setEdgeValue(tlp::edge &) const =0;
  virtual void set(const void *) =0;
};


/*
 * Example of instanciation
 * @code
 * Attribute * attr = new Attr<INT>("age", 42);
 * @endcode
 */
template <class T>
class Attr : public virtual Attribute {
  std::string label;
  std::string typeName;
  int constraints;
  
  T value;
  typename TlpProp<T>::type * prop;

public:
  Attr(const std::string &label);
  Attr(const std::string &label, T value);
  //Attr(const std::string &label, t_constr constraints);

  std::string getLabel() const;
  int getConstraints() const;
  std::string getTypeName() const;
  void getProperty(void **) const;
  void getValue(void * dst) const;

  void setLabel(const std::string &newLabel);
  void setValue(const void * value);

  Attribute * clone() const;
  bool isEqual(tlp::node &n) const;
  bool isEqual(tlp::edge &e) const;
  void print() const;

  Attribute * operator=(const Attribute * attr);

private:
  void setConstraints(int newConstraints);
  void setTypeName(const std::string &newTypeName);
  void setProperty(const void * prop);
  void setProperty(const Attribute * attr);
  void setNodeValue(tlp::node &n) const ;
  void setEdgeValue(tlp::edge &e) const ;
  void set(const void * value);
  
  void init();
};


/* Implémentation des templates */
/**********************************************************************/

template <class T>
Attr<T>::Attr (const std::string &label) {
  this->init(); // deux objets créés ? -> utiliser méthode privée plutot
  this->label = label;
  this->constraints = NONE;
}

template <class T>
Attr<T>::Attr (const std::string &label, T value) {
  this->init();
  this->label = label;
  this->value = value;
  this->constraints = NONE;
}

/*
template <class T>
Attr<T>::Attr (const std::string &label, t_constr constraints) {
  Attr();
  this->label = label;
  this->constraints = constraints;
}
*/

template <class T>
Attribute * Attr<T>::operator=(const Attribute * attr) {
  this->label = attr->getLabel();
  attr->getValue(&(this->value));
  this->constraints = attr->getConstraints();
  this->typeName = attr->getTypeName();
  return this;
}

template <class T>
std::string Attr<T>::getLabel() const {
  return this->label;
}

template <class T>
int Attr<T>::getConstraints() const{
  return this->constraints;
}

template <class T>
std::string Attr<T>::getTypeName() const {
  return this->typeName;
}

template <class T>
void Attr<T>::getProperty(void ** dst) const {
  typename TlpProp<T>::type ** _dst = (typename TlpProp<T>::type **) dst;
  *_dst = this->prop;
}

template <class T>
void Attr<T>::getValue(void * dst) const {
  T * _dst = (T *) dst;
  *_dst = this->value;
}

template <class T>
void Attr<T>::setLabel(const std::string &newLabel) {
  this->label = newLabel;
}

template <class T>
void Attr<T>::setConstraints(int newConstraints) {
  this->constraints = newConstraints;
}

template <class T>
void Attr<T>::setTypeName(const std::string &newTypeName) {
  this->typeName = newTypeName;
}

template <class T>
void Attr<T>::setValue(const void * newValue) {
  const T * _newValue = (T *) newValue;
  this->value = *_newValue;
}

template <class T>
void Attr<T>::setNodeValue(tlp::node &n) const {
  this->prop->setNodeValue(n, this->value);
}

template <class T>
void Attr<T>::setEdgeValue(tlp::edge &e) const {
  this->prop->setEdgeValue(e, this->value);
}

template <class T>
void Attr<T>::setProperty(const void * prop) {
  this->prop = (typename TlpProp<T>::type *) prop;
}

template <class T>
void Attr<T>::setProperty(const Attribute * attr) {
  attr->getProperty((void **) &(this->prop));
}

template <class T>
void Attr<T>::set(const void * value) {
  T _value = *((T *) value);
  this->prop->setAllNodeValue(_value);
}

template <class T>
Attribute * Attr<T>::clone() const {
  Attr<T> * tmp = new Attr<T>(this->label);
  tmp->setConstraints(this->constraints);
  tmp->setTypeName(this->typeName);
  tmp->setValue(&(this->value));
  return tmp;
}

template <class T>
bool Attr<T>::isEqual(tlp::node &n) const {
  return (this->value == this->prop->getNodeValue(n));
}

template <class T>
bool Attr<T>::isEqual(tlp::edge &e) const {
  return (this->value == this->prop->getEdgeValue(e));
}

template <class T>
void Attr<T>::print() const {
  std::cout << "== " + this->label + " ==" << std::endl;
  std::cout << "type\t\t" + this->typeName << std::endl;
  std::cout << "constraints\t\t" + this->constraints << std::endl;
  std::cout << "value\t\t";
  std::cout << this->value;
  std::cout << std::endl;
}

#endif //DBTOOLS_HPP
