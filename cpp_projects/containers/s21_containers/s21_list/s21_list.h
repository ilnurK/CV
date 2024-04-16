#ifndef SRC_S21_CONTAINERS_LIST_S21_LIST_H_
#define SRC_S21_CONTAINERS_LIST_S21_LIST_H_
#include <algorithm>  // Include for min
#include <deque>  // Для использования deque_type::value_type для функции max_size()
#include <initializer_list>  // для инцилизации в List(std::initializer_list<value_type> const &items);
#include <limits>  // Для использования std::numeric_limits для для функции max_size()
#include <memory>  // Для использования __node_alloc_traits для для функции max_size()
#include <stdexcept>

namespace s21 {
template <typename T>
class List {
 public:
  // Определение типа элемента контейнера
  using value_type = T;
  // Определение типа ссылки на элемент контейнера
  using reference = T &;
  // Определение типа константной ссылки на элемент контейнера
  using const_reference = const T &;
  // Определение типа размера контейнера
  using size_type = size_t;
  // #include <deque>
  using deque_type = std::deque<T>;

 private:
  struct Node {
    T data;
    Node *next = nullptr;
    Node *previous = nullptr;
  };
  Node *head;
  Node *tail;
  size_type size_list;

 public:
  class ListIterator;
  class ListConstIterator;
  // псевдонимы
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  class ListIterator {
   public:
    using reference = T &;
    using pointer = T *;
    ListIterator();
    ListIterator(const_iterator it);
    ListIterator(typename s21::List<T>::Node *node);
    ListIterator(typename s21::List<T>::Node *node,
                 typename s21::List<T>::Node *last_node);

    reference operator*();
    pointer operator->() const;
    ListIterator &operator++();
    ListIterator operator++(int);
    ListIterator &operator--();
    ListIterator operator--(int);
    bool operator==(const ListIterator &other) const;
    bool operator!=(const ListIterator &other) const;

   private:
    Node *m_node;
    Node *last_node;
    friend class List;
  };

  class ListConstIterator {
   public:
    using reference = const T &;
    using pointer = const T *;

    ListConstIterator();
    ListConstIterator(iterator it);
    ListConstIterator(typename s21::List<T>::Node *node);
    ListConstIterator(typename s21::List<T>::Node *node,
                      typename s21::List<T>::Node *last_node);

    reference operator*();
    pointer operator->() const;
    ListConstIterator &operator++();
    ListConstIterator operator++(int);
    ListConstIterator &operator--();
    ListConstIterator operator--(int);
    bool operator==(const ListConstIterator &other) const;
    bool operator!=(const ListConstIterator &other) const;

   private:
    Node *m_node;
    Node *last_node;
    friend class List;
  };

 public:
  // возвращает итератор, указывающий на первый элемент
  iterator begin() const noexcept;
  // возвращает итератор, указывающий на первый элемент
  const_iterator cbegin() const noexcept;
  // возвращает итератор, указывающий на последний элемент
  iterator end() const noexcept;
  // возвращает итератор, указывающий на последний элемент
  const_iterator cend() const noexcept;
  // возвращает константный итератор, указывающий на первый элемент
  const_reference front() const;
  // возвращает константный итератор, указывающий на последний элемент
  const_reference back() const;

  // Базовый конструктор инициализирует объект класса List
  List() noexcept;
  // Базовый деструктор
  ~List() noexcept;
  // Конструктор создает список определенного размера,
  // или с элементами определенного значения, или с определенным allocator, или
  // в качестве копии какого-либо другого списка
  List(size_type n);
  // Конструктор list создает список на основе переданного списка инициализации.
  List(std::initializer_list<value_type> const &items);
  // Конструктор копирования создает новый список на основе переданного списка,
  // используя копирование
  List(const List &l);
  // Конструктор перемещения создает новый список на основе переданного списка,
  // используя перемещение
  List(List &&l) noexcept;

  // Перемещает элементы из переданного списка в новый список
  List &operator=(List &&l);
  List &operator=(const List &other);
  // Очищает список, удаляет все их элементы
  void clear() noexcept;
  // Список пуст? true - уеп, false - нет
  bool empty() const noexcept;
  // Максимальный размер списка
  size_type max_size() const noexcept;
  // текущий размер списка
  size_type size() const noexcept;
  // вставка элемента со значение value в место pos
  iterator insert(iterator pos, const_reference value);
  const_iterator insert(const_iterator pos, const_reference value);
  // добавляет элемент значения value в конец списка
  void push_back(const_reference value);
  // добавляет элемент значения value в начало списка
  void push_front(const_reference value);
  // удаляет последний элемент
  void pop_back();
  // удаляет первый элемент в списке
  void pop_front();
  // удвляет элмент, указанный итератором pos
  void erase(iterator pos);
  void erase(const_iterator pos);
  // обмен содержимого списков
  void swap(List &other) noexcept;
  // объединение двух списков
  void merge(List &other);
  // вставляет один список в другой с позиции pos
  void splice(const_iterator pos, List &other);
  void splice(iterator pos, List &other);
  // инвертирование порядка элементов
  void reverse() noexcept;
  // удаление идущих подряд дубликатов
  void unique() noexcept;
  // сортировка по возрастанию
  void sort() noexcept;

  // вставляет n элементов args, начиная с позиции pos
  template <typename... Args>
  ListIterator insert_many(ListConstIterator pos, Args &&...args);
  template <typename... Args>
  ListIterator insert_many(ListIterator pos, Args &&...args);

  // вставляет n элементов args в конец списка
  template <typename... Args>
  void insert_many_back(Args &&...args);

  // вставляет n элементов args в начало списка
  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  // обнуляет поля
  void InitializeEmptyList(s21::List<T> &node_empty) noexcept;
};
}  // namespace s21

#include "s21_list.cc"
#include "s21_list_iterator.cc"
#endif  // SRC_S21_CONTAINERS_LIST_S21_LIST_H_
