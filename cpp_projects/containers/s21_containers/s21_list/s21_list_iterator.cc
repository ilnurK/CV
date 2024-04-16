#include "s21_list.h"

template <typename T>
s21::List<T>::ListIterator::ListIterator()
    : m_node(nullptr), last_node(nullptr) {}

template <typename T>
s21::List<T>::ListIterator::ListIterator(typename s21::List<T>::Node* node)
    : m_node(node), last_node(nullptr) {}

template <typename T>
s21::List<T>::ListIterator::ListIterator(typename s21::List<T>::Node* node,
                                         typename s21::List<T>::Node* last_node)
    : m_node(node), last_node(last_node) {}

template <typename T>
s21::List<T>::ListIterator::ListIterator(const_iterator it)
    : m_node(it.m_node), last_node(it.last_node) {}

template <typename T>
typename s21::List<T>::ListIterator::reference
s21::List<T>::ListIterator::operator*() {
  if (m_node) return m_node->data;
  throw std::out_of_range("limit reached");
}

template <typename T>
typename s21::List<T>::ListIterator::pointer
s21::List<T>::ListIterator::operator->() const {
  if (m_node) return &(m_node->data);
  throw std::out_of_range("limit reached");
}

template <typename T>
typename s21::List<T>::ListIterator& s21::List<T>::ListIterator::operator++() {
  if (m_node != nullptr) m_node = m_node->next;
  return *this;
}

template <typename T>
typename s21::List<T>::ListIterator s21::List<T>::ListIterator::operator++(
    int) {
  ListIterator num(*this);
  ++(*this);
  return num;
}

template <typename T>
typename s21::List<T>::ListIterator& s21::List<T>::ListIterator::operator--() {
  if (m_node)
    m_node = m_node->previous;
  else
    m_node = last_node;
  return *this;
}

template <typename T>
typename s21::List<T>::ListIterator s21::List<T>::ListIterator::operator--(
    int) {
  ListIterator num(*this);
  --(*this);
  return num;
}

template <typename T>
bool s21::List<T>::ListIterator::operator==(const ListIterator& other) const {
  return m_node == other.m_node;
}

template <typename T>
bool s21::List<T>::ListIterator::operator!=(const ListIterator& other) const {
  return !(*this == other);
}

//------------------------------------------------ListConstIterator-----------------------------------------------------------

template <typename T>
s21::List<T>::ListConstIterator::ListConstIterator()
    : m_node(nullptr), last_node(nullptr) {}

template <typename T>
s21::List<T>::ListConstIterator::ListConstIterator(
    typename s21::List<T>::Node* node)
    : m_node(node), last_node(nullptr) {}

template <typename T>
s21::List<T>::ListConstIterator::ListConstIterator(
    typename s21::List<T>::Node* node, typename s21::List<T>::Node* last_node)
    : m_node(node), last_node(last_node) {}

template <typename T>
s21::List<T>::ListConstIterator::ListConstIterator(iterator it)
    : m_node(it.m_node), last_node(it.last_node) {}

template <typename T>
typename s21::List<T>::ListConstIterator::reference
s21::List<T>::ListConstIterator::operator*() {
  if (m_node) return m_node->data;
  throw std::out_of_range("limit reached");
}

template <typename T>
typename s21::List<T>::ListConstIterator::pointer
s21::List<T>::ListConstIterator::operator->() const {
  if (m_node) return &(m_node->data);
  throw std::out_of_range("limit reached");
}

template <typename T>
typename s21::List<T>::ListConstIterator&
s21::List<T>::ListConstIterator::operator++() {
  if (m_node) m_node = m_node->next;
  return *this;
}

template <typename T>
typename s21::List<T>::ListConstIterator
s21::List<T>::ListConstIterator::operator++(int) {
  ListConstIterator num(*this);
  ++(*this);
  return num;
}

template <typename T>
typename s21::List<T>::ListConstIterator&
s21::List<T>::ListConstIterator::operator--() {
  if (m_node)
    m_node = m_node->previous;
  else {
    m_node = last_node;
  }
  return *this;
}

template <typename T>
typename s21::List<T>::ListConstIterator
s21::List<T>::ListConstIterator::operator--(int) {
  ListConstIterator num(*this);
  --(*this);
  return num;
}

template <typename T>
bool s21::List<T>::ListConstIterator::operator==(
    const ListConstIterator& other) const {
  return m_node == other.m_node;
}

template <typename T>
bool s21::List<T>::ListConstIterator::operator!=(
    const ListConstIterator& other) const {
  return !(*this == other);
}
