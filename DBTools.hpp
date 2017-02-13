#ifndef DBTOOLS_HPP
#define DBTOOLS_HPP

#include <iostream>
#include <cstring>

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

//typedef int t_constr;


class Attribute {
public:
  virtual std::string getLabel() const =0;
  virtual int getConstraints() const =0;
  virtual std::string getTypeName() const =0;
  virtual void getValue(void *) const =0;
 
  virtual Attribute * clone() const =0;
  virtual Attribute * operator=(const Attribute *) =0;

  virtual void print() const =0;
  
protected:
  virtual void setLabel(const std::string &) =0;
  virtual void setConstraints(int) =0;
  virtual void setTypeName(const std::string &) =0;
  virtual void setValue(const void *) =0;
};


template <class T>
class Attr : public virtual Attribute {
  std::string label;
  std::string typeName;
  T value;
  int constraints;

private:
  Attr();

  void setLabel(const std::string &newLabel);
  void setConstraints(int newConstraints);
  void setTypeName(const std::string &newTypeName);
  void setValue(const void * newValue);

public:
  Attr(const std::string &label);
  Attr(const std::string &label, T value);
  //Attr(const std::string &label, t_constr constraints);

  Attribute * operator=(const Attribute * attr);

  std::string getLabel() const;
  int getConstraints() const;
  std::string getTypeName() const;
  void getValue(void * dst) const;

  Attribute * clone() const;

  void print() const;
};


/* Implémentation des templates */
/**********************************************************************/

template <class T>
Attr<T>::Attr (const std::string &label) {
  *this = Attr();
  std::cout << this->typeName << std::endl;
  this->label = label;
  this->constraints = NONE;
}

template <class T>
Attr<T>::Attr (const std::string &label, T value) {
  *this = Attr();
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
Attribute * Attr<T>::clone() const {
  Attr<T> * tmp = new Attr<T>();
  tmp->setLabel(this->label);
  tmp->setConstraints(this->constraints);
  tmp->setTypeName(this->typeName);
  tmp->setValue(&(this->value));
  return tmp;
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
