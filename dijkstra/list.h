#include <iostream>

#ifndef LIST_HEADER
#define LIST_HEADER

template <typename T>
class List {
    T *_values;
    int _last, _size;
    bool isFull();

    void increase();
    void decrease();
public:
    int find(T val);
    List(int size);
    List(const List &l);
    ~List();
    void append(T val);
    void remove(T value);
    void remove(int value);
    T getValueAt(int pos);
    void erase(T val);
    void toScreen();
    int getSize();
    T operator[](int pos);
    List operator=(const List& l);

};

template <typename T>
List<T>::List(int size) {
    _size = size;
    _last = 0;
    _values = new T[size];
}

template <typename T>
List<T>::List(const List &l) {
    _size = l._size;
    _last = l._last;
    _values = new T[_size];

    for (int i = 0; i < _last; i++){
        _values[i] = l._values[i];
    }
}

template <typename T>
List<T>::~List() {
    delete[] _values;
}

template <typename T>
T List<T>::getValueAt(int pos) {
    if (pos < 0 || pos >= _last)
        std::cout << "out of bounds";
    return _values[pos];
}

template <typename T>
void List<T>::append(T val) {
    if (isFull())
        increase();

    _values[_last] = val;
    _last += 1;
}

template <typename T>
void List<T>::remove(T value) {
    int pos = find(value);

    if (pos == -1)
        throw "ValueNotFoundException";

    for (; pos < _last -1; pos++)
        _values[pos] = _values[pos + 1];
    _last -= 1;

    if (_last < _size / 4)
        decrease();
}

template <typename T>
void List<T>::remove(int value){
    for (int pos = value; pos < _last -1; pos++)
        _values[pos] = _values[pos + 1];
    _last -= 1;

    if (_last < _size / 4)
        decrease();
}

template <typename T>
bool List<T>::isFull() {
    return _last == _size;
}

template <typename T>
void List<T>::increase() {
    T *tmp = new T[_size * 2];

    for (int i = 0; i < _size; i++)
        tmp[i] = _values[i];

    delete[] _values;
    _values = tmp;
    _size *= 2;
}

template <typename T>
void List<T>::toScreen() {
    for (int i = 0; i < _last; i++)
        std::cout << i << ": " << _values[i] << std::endl;
}

template <typename T>
int List<T>::find(T val) {
    for (int pos = 0; pos < _last; pos++)
        if (_values[pos] == val)
            return pos;
    return -1;
}

template <typename T>
void List<T>::decrease() {
    _size /= 2;
    T *tmp = new T[_size];

    for (int i = 0; i < _size; i++)
        tmp[i] = _values[i];
    delete[] _values;
    _values = tmp;
}

template <typename T>
void List<T>::erase(T val) {
    int pos = find(val);

    if (pos == -1)
        std::cout <<  "value not found";

    for (; pos < _last -1; pos++)
        _values[pos] = _values[pos + 1];
    _last -= 1;

    if (_last < _size / 4)
        decrease();
}

template <typename T>
int List<T>::getSize() {
    return _last;
}


template <typename T>
T List<T>::operator[](int pos) {
    return getValueAt(pos);
}


template <typename T>
List<T> List<T>::operator=(const List& l) {
    if (this != &l) {
        delete[] _values;

        _size = l._size;
        _last = l._last;
        _values = new T[_size];

        for (int i = 0; i < _last; i++)
            _values[i] = l._values[i];
    }
    return *this;
}


#endif