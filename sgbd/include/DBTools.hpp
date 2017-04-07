#ifndef DBTOOLS_HPP
#define DBTOOLS_HPP

///@cond USER

#include <iostream>
#include <string>

#include <tulip/Graph.h>
#include <tulip/Node.h>
#include <tulip/StringProperty.h>
#include <tulip/DoubleProperty.h>
#include <tulip/IntegerProperty.h>
#include <tulip/BooleanProperty.h>

/**
 * @brief Operator =
 **/
#define EQUAL 0

/**
 * @brief Operator !=
 **/
#define DIFFERENT 1

/* List of acceptable types for the attributes */

#define INT int
#define DOUBLE double
#define BOOL bool
#define STRING std::string

/*
union valContainer {
  INT _int;
  DOUBLE _double;
  BOOL _bool;
  STRING _string;
};
*/

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
class PatternImpl;

template <class T>
struct TlpProp;

/**
 * @brief This class is an interface for the use of Attribute objects. 
 * It provides a type / subtype relation between Attribute / Attr. 
 * It may necessarily be used in order to manipulate arrays of Attr objects.
 * 
 * Example of typical use :
 * @code
 * Attribute * tab[2] = {new Attr("firstname"), new Attr("name")};
 * @endcode
 **/
class Attribute {
  friend Entity;
  friend Relation;
  friend PatternImpl;
  friend void setAttrProperty(tlp::Graph *, Attribute *[], int);

protected:
  /** 
   * @brief Attribute's id
   **/
  std::string label;

  /**
   * @brief Constraint on the Attribute, UNIQUE for instance
   **/
  int constraints;

  /**
   * @brief Type of the Attribute
   **/
  std::string typeName;
  
public:
  virtual ~Attribute();
  std::string getLabel() const;
  int getConstraints() const;
  std::string getTypeName() const;
  virtual void getProperty(void **) const =0;
  virtual void getValue(void *) const =0;

  void setLabel(const std::string &);
  void setConstraints(int);
  virtual void setValue(const void *) =0;
 
  virtual Attribute * clone() const =0;
  virtual bool isEqual(tlp::node &) const =0;
  virtual bool isEqual(tlp::edge &) const =0;
  virtual void print() const =0;
  virtual std::string debug() const =0;
  void addConstraints(int);

  virtual Attribute * operator=(const Attribute *) =0;
  
protected:
  void setTypeName(const std::string &);
  virtual void setProperty(const void *) =0;
  virtual void setProperty(const Attribute *) =0;
  virtual void setProperty(tlp::Graph *) =0;
  virtual void setNodeValue(tlp::node &) const =0;
  virtual void setEdgeValue(tlp::edge &) const =0;
  virtual void getNodeValue(tlp::node &) =0;
  virtual void getEdgeValue(tlp::edge &) =0;
  virtual void set(const void *) =0;
};

/**
 * Example of instanciation
 * @code
 * Attribute * attr = new Attr<INT>("age", 42);
 * @endcode
 **/
template <class T>
class Attr : public Attribute {
  T value;
  typename TlpProp<T>::type * prop;

public:
  Attr(const std::string &label);
  Attr(const std::string &label, T value);
  virtual ~Attr();
  //Attr(const std::string &label, t_constr constraints);

  void getProperty(void **) const;
  void getValue(void * dst) const;

  void setValue(const void * value);

  Attribute * clone() const;
  bool isEqual(tlp::node &n) const;
  bool isEqual(tlp::edge &e) const;
  void print() const;
  std::string debug() const;

  Attribute * operator=(const Attribute * attr);

private:
  void setProperty(const void * prop);
  void setProperty(const Attribute * attr);
  void setProperty(tlp::Graph * g);
  void setNodeValue(tlp::node &n) const ;
  void setEdgeValue(tlp::edge &e) const ;
  void getNodeValue(tlp::node &n);
  void getEdgeValue(tlp::edge &e);
  void set(const void * value);
  
  void init();
};


template <class T>
T unserialize(const std::string &serializedValue, const std::string &format = "");

template <class T>
std::string serialize(const T &value);

Attribute * newAttr(const std::string &label, const std::string &typeName);
Attribute ** extendAttr(Attribute * attr[], int nAttrAct, int nAttrNew, bool dynAlloc);
void delAttr(Attribute * attr[], int nAttr);
void setAttrProperty(tlp::Graph * g, Attribute * attr[], int nAttr);

/* Template Implementation */
/**********************************************************************/

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

template <class T>
Attr<T>::Attr (const std::string &label) {
  this->init(); 
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


template <class T>
Attr<T>::~Attr () {}


template <class T>
Attribute * Attr<T>::operator=(const Attribute * attr) {
  this->label = attr->getLabel();
  attr->getValue(&(this->value));
  this->constraints = attr->getConstraints();
  this->typeName = attr->getTypeName();
  return this;
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
void Attr<T>::getNodeValue(tlp::node &n) {
  this->value = this->prop->getNodeValue(n);
}

template <class T>
void Attr<T>::getEdgeValue(tlp::edge &e) {
  this->value = this->prop->getEdgeValue(e);
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
void Attr<T>::setProperty(tlp::Graph * g) {
  this->prop = g->getProperty<typename TlpProp<T>::type>(this->label);
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
  tmp->setProperty(this->prop);
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
  std::cout << debug() << std::endl;
}


template <class T>
std::string Attr<T>::debug() const {
  std::string ret;
  
  ret = this->label;
  for (int i = 0 ; i < (32 - this->label.size()) ; i++)
    ret += " ";
  ret += this->typeName + "\t";
  ret += "cstr:" + std::to_string(this->constraints) + "\t";
  ret += "val:";
  ret += serialize(this->value);
  
  return ret;
}

///@endcond

#endif //DBTOOLS_HPP
