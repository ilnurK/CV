'''Вопрос №1
На языке Python написать алгоритм(функцию) определения четности целого
числа, который будет аналогичен нижеприведенному по функциональности,
но отличен по своей сути. Объяснить плюсы и минусы обеих реализаций.

Пример:

def isEven(value):
      return value % 2 == 0
'''


from typing import List, Any, Optional
from typing_extensions import Self


def isEvenLesta(value: int) -> bool:
    """Returns true if value is even

    + Быстрее производительность
    - Хуже читаемость

    Parameters
    ----------
    value : int
        Value need to check

    Returns
    -------
    bool
        The parity status
    """

    return (value >> 1) << 1 == value


if __name__ == "__main__":
    def isEven(value):
        return value % 2 == 0

    print("task1 start")
    assert (isEven(2) == isEvenLesta(2))
    assert (isEven(0) == isEvenLesta(0))
    assert (isEven(1) == isEvenLesta(1))
    assert (isEven(-11) == isEvenLesta(-11))
    assert (isEven(231) == isEvenLesta(231))
    assert (isEven(3310) == isEvenLesta(3310))
    print("task1 end\n")

'''Вопрос №2
На языке Python написать минимум по 2 класса реализовывающих
циклический буфер FIFO. Объяснить плюсы и минусы каждой реализации.

Оценивается:

Полнота и качество реализации
Оформление кода
Наличие сравнения и пояснения по быстродействию
'''


class ListQueue:
    """List based queue adapter class

    Attributes
    ----------
    self.__data: List[Any]
        Encapsulated container
    """

    def __init__(self, *args):
        """ListQueue class initialization

        Parameters
        ----------
        *args
            Initialization value list
        """

        self.__data: List[Any] = []
        for arg in args:
            self.add(arg)

    def add(self, value: Any):
        """Adds value to queue

        Parameters
        ----------
        value : Any
            The new container value
        """

        self.__data.append(value)

    def pop(self):
        """Returns the first element of container and removes it

        Returns
        -------
        Any
            The contained value

        Raises
        ------
        IndexError
            If container is empty
        """

        value = 0
        if self.__data:
            value = self.__data.pop(0)
        else:
            raise IndexError("empty queue")
        return value

    def show(self):
        """Show container's values"""
        print(*self.__data, sep=', ') if self.__data else None

    @property
    def size(self):
        """Getter for container size

        Returns
        -------
        int
            The size of container
        """

        return len(self.__data)


class FLQueue:
    """Forward list based queue adapter class

    Attributes
    ----------
    self.__head: Node
        The head of queue, the element that goes first
    self.__tail: Node
        The tail of queue, the element to which new value is added
    self.__size: int
        Size of queue
    """
    class Node:
        """Container base

        Attributes
        ----------
        self.value: Any
            The nodes value
        self.next: Node
            The next node in line
        """

        def __init__(self, value: Any):
            """Node class initialization

            Parameters
            ----------
            value : Any
                The nodes value
            """

            self.value = value
            self.next: Optional[Self] = None

    def __init__(self, *args):
        """FLQueue class initialization

        Parameters
        ----------
        *args
            Initialization value list
        """

        self.__size: int = 0
        self.__head: Optional[self.Node] = None
        self.__tail: Optional[self.Node] = None
        for arg in args:
            if not self.__head:
                self.__size += 1
                self.__head = self.Node(arg)
                self.__tail = self.__head
            else:
                self.add(arg)

    def add(self, value: Any):
        """Adds value to queue

        Parameters
        ----------
        value : Any
            The new container value
        """

        n = self.Node(value)
        if not self.__head:
            self.__head = n
            self.__tail = n
        else:
            if (self.__tail):
                self.__tail.next = n
            self.__tail = n
            self.__size += 1

    def pop(self):
        """Returns the first element of container and removes it

        Returns
        -------
        Any
            The contained value

        Raises
        ------
        IndexError
            If container is empty
        """

        temp = None
        if self.__size:
            temp = self.__head.value
            self.__head = self.__head.next
            self.__size -= 1
        else:
            raise IndexError("empty queue")
        return temp

    @property
    def size(self):
        """Getter for container size

        Returns
        -------
        int
            The size of container
        """

        return self.__size

    def show(self):
        """Show container's values"""
        cur = self.__head
        for i in range(self.__size):
            if i != self.__size - 1:
                print(cur.value, end=', ')
            else:
                print(cur.value)
            cur = cur.next


if __name__ == "__main__":
    import random as r
    from time import perf_counter
    from contextlib import contextmanager

    r.seed(1)

    @contextmanager
    def count_time(info: str = ""):
        start_time = perf_counter()
        yield
        end_time = perf_counter()
        counted_time = end_time - start_time
        print(f"{info}{counted_time * 1e3: .2f} ms")

    big_list = [r.randint(-100, 100) for _ in range(int(1e5))]

    print("task2 start")

    with count_time("ListQueue creation "):
        a = ListQueue(*big_list)

    with count_time("ForwardListQueue creation "):
        b = FLQueue(*big_list)

    assert (a.size == b.size)

    lst_a, lst_b = [], []
    with count_time("ListQueue deletion "):
        for i in range(a.size):
            lst_a.append(a.pop())

    with count_time("ForwardListQueue deletion "):
        for i in range(b.size):
            lst_b.append(b.pop())

    for i in range(a.size):
        assert (lst_a[i] == lst_b[i])

    print("task2 end\n")

"""ListQueue:
+: основан на стандартном List -> надежность
-: медленное удаление из-за необходимости передвигать оставшийся массив

FLQueue:
-: Необходимо много краевых юнит тестов для проверки надежности
+: За счет применения только одной ссылки - сокращаются затраты
на удаление элемента
"""


"""Вопрос №3
На языке Python предложить алгоритм, который быстрее всего
(по процессорным тикам) отсортирует данный ей массив чисел.
Массив может быть любого размера со случайным порядком чисел
(в том числе и отсортированным). Объяснить, почему вы считаете,
что функция соответствует заданным критериям.
"""


def LTimSort(array: List[int]):
    """Simplified TimSort, based on sorting small parts of array
    by insertion sort and apply to that parts merge sort,
    with gradually increasing that parts

    Parameters
    ----------
    array : List[int]
        Array to sort
    """

    def insert_sort(left: int, right: int):
        """A sorting method based on finding the correct index for each
        element from left to right, while moving larger elements to the
        left of the current one

        Parameters
        ----------
        left : int
            The leftmost index of array
        right : int
            The rightmost index of array
        """

        for i in range(left + 1, right):
            min = array[i]
            li = i - 1
            while li >= left and array[li] > min:
                array[li + 1] = array[li]
                li -= 1
            array[li + 1] = min

    def merge_sort(left: int, mid: int, right: int):
        """A sorting method based on collecting the smallest value from
        two other arrays obtained by partitioning the main array by
        left, middle, and right indices.

        Parameters
        ----------
        left : int
            The leftmost index of array
        mid : int
            The divider index
        right : int
            The rightmost index of array
        """

        arrleft = array[left:mid + 1]
        arrright = array[mid + 1:right + 1]

        idx = left
        l, r = 0, 0
        lsize, rsize = len(arrleft), len(arrright)
        while l < lsize and r < rsize:
            if arrleft[l] <= arrright[r]:
                array[idx] = arrleft[l]
                l += 1
            else:
                array[idx] = arrright[r]
                r += 1
            idx += 1

        while l < lsize:
            array[idx] = arrleft[l]
            l += 1
            idx += 1

        while r < rsize:
            array[idx] = arrright[r]
            r += 1
            idx += 1

    N: int = len(array)
    buck_size: int = 16

    for left in range(0, N, buck_size):
        right = min(left + buck_size, N)
        insert_sort(left, right)

    while buck_size < N:
        for left in range(0, N, buck_size * 2):
            mid = min(left + buck_size - 1, N - 1)
            right = min(left + 2 * buck_size - 1, N - 1)
            if mid < right:
                merge_sort(left, mid, right)

        buck_size *= 2


if __name__ == "__main__":
    from copy import copy

    print("task3 start")

    vec = copy(big_list)
    with count_time("LTimSort sort "):
        LTimSort(big_list)

    with count_time("std sort"):
        vec.sort()

    assert (len(vec) == len(big_list))
    for i in range(len(vec)):
        assert (big_list[i] == vec[i])

    print("task3 end")

"""
TimSort хорошо показывает себя на любых случайных данных благодаря
тому, что сортировка слиянием отрабывает на уже отсортированных данных,
за счет чего взятие нужного элемента в "слитый массив" происходит
за O(N). Так как подмассивы достаточно коротки - формирование
отсортированных кусочков происходит тоже быстро N/k * k ^ 2 = N * k,
а при k << N = O(N). Общая сложность O(N) + O(N) * log(N) = O(N) * log(N)
"""
