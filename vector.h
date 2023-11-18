#ifndef vector_H
#define vector_H
#include <iostream>
#include <algorithm>
#include <cmath>

template <class T>
class vector {

    public:
        typedef T* iterator;
        vector();
        vector(size_t);
        vector(std::initializer_list<T>);
        vector(const vector&);
        ~vector();
        iterator begin() const;
        iterator end() const;
        T& operator[](size_t);
        vector operator+(const vector&) const;
        vector& operator+=(const vector&);
        vector& operator=(const vector&);
        void rndfill(int, int);
        void add(const T&);
        void pop(size_t);
        void pop(iterator);
        void pop();
        void resize(size_t);
        void clear();
        void insert(const vector&, size_t);
        T max() const;
        T min() const;
        T sum() const;
        void sort();
        size_t search(T) const;
        size_t get_size() const;
        size_t get_capacity() const;
        template <class U>
        friend std::istream& operator>>(std::istream&, vector<U>&);
        template <class U>
        friend std::ostream& operator<<(std::ostream&, const vector<U>&);

    private:
        size_t capacity;
        size_t size;
        iterator data;

        size_t allocate(size_t);
};

template <class T>
size_t vector<T>::allocate(size_t size) {
    size_t new_capacity = pow(2, ceil(log2(size)));
    T *new_data = new T[new_capacity];
    std::copy(begin(), end(), new_data);
    delete[] data;
    capacity = new_capacity;
    data = new_data;
    return new_capacity;
}

template <class T>
vector<T>::vector() : capacity(8), size(0), data(new T[capacity]) {}

template <class T>
vector<T>::vector(size_t size) : capacity(pow(2, ceil(log2(size)))), size(size), data(new T[capacity]) {}

template <class T>
vector<T>::vector(std::initializer_list<T> list) : capacity(pow(2, ceil(log2(list.size())))), size(list.size()), data(new T[capacity]) {
    std::copy(list.begin(), list.end(), data);
}

template <class T>
vector<T>::vector(const vector &obj) : capacity(obj.capacity), size(obj.size), data(new T[capacity]) {
    std::copy(obj.begin(), obj.end(), data);
}

template <class T>
vector<T>::~vector() { delete[] data; }

template <class T>
typename vector<T>::iterator vector<T>::begin() const { return data; };

template <class T>
typename vector<T>::iterator vector<T>::end() const { return (data + size); };

template <class T>
T& vector<T>::operator[](size_t index) {
    try {
        if(index >= size) throw std::overflow_error("Stack overflow");
        return data[index];
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return data[capacity - 1];
}

template <class T>
vector<T> vector<T>::operator+(const vector &obj) const {
    vector result(*this);
    result.insert(obj, result.size);
    return result;
}

template <class T>
vector<T>& vector<T>::operator+=(const vector &obj) {
    *this = *this + obj;
    return *this;
}

template <class T>
vector<T>& vector<T>::operator=(const vector &obj) {
    capacity = obj.capacity;
    size = obj.size;
    delete[] data;
    data = new T[capacity];
    std::copy(obj.begin(), obj.end(), data);
    return *this;
}

template <class T>
void vector<T>::rndfill(int low, int high) {
    if(typeid(T) == typeid(int)) {
        for(size_t i = 0; i < size; i++) {
            data[i] = low + rand()%(high - low + 1);
        }
    }
}

template <class T>
void vector<T>::add(const T& num) {
    if(size + 1 > capacity) allocate(size + 1);
    data[size] = num;
    size++;
}

template <class T>
void vector<T>::pop(size_t n) {
    try {
        if(n >= size) throw std::underflow_error("Stack overflow");
        std::copy(data + n + 1, end(), data + n);
        data[size] = {};
        size--;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

template <class T>
void vector<T>::pop(iterator p) {
    try {
        if(p > end()) throw std::overflow_error("Stack overflow");
        if(p < begin()) throw std::underflow_error("Stack underflow");
        std::copy(p + 1, end(), p);
        data[size] = {};
        size--;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

template <class T>
void vector<T>::pop() {
    try {
        if(size == 0) throw std::underflow_error("Stack underflow");
        std::copy(begin(), end()-1, begin());
        data[size] = {};
        size--;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

template <class T>
void vector<T>::resize(size_t size) {
    if(size > capacity) allocate(size);
    for (size_t i = this->size; i < size; i++) {
        data[i] = {};
    }
    this->size = size;
}

template <class T>
void vector<T>::clear() {
    resize(0);
}

template <class T>
void vector<T>::insert(const vector &obj, size_t pos) {
    try {
        if(size + obj.size < pos) throw std::overflow_error("Stack overflow");
        if(size + obj.size > capacity) allocate(size + obj.size);
        std::copy(data + pos, end(), data + pos + obj.size);
        std::copy(obj.begin(), obj.end(), data + pos);
        size += obj.size;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

template <class T>
T vector<T>::max() const {
    T m = data[0];
    for (size_t i = 0; i < size; i++) if(data[i] > m) m = data[i];
    return m;
}

template <class T>
T vector<T>::min() const {
    T m = data[0];
    for (size_t i = 0; i < size; i++) if(data[i] < m) m = data[i];
    return m;
}

template <class T>
T vector<T>::sum() const {
    T s = data[0];
    for (size_t i = 1; i < size; i++) s += data[i];
    return s;
}

template <class T>
void vector<T>::sort() {
    T key;
    size_t low, high, mid;
    for(size_t i = 1; i < size; i++) {
        key = data[i]; low = 0; high = i - 1;
        while (low <= high) {
            mid = (high + low) / 2;
            if (key < data[mid]) high = mid - 1;
            else low = mid + 1;
        }
        for (size_t j = i - 1; j >= low; j--) data[j + 1] = data[j];
        data[low] = key;
    }
}

template <class T>
size_t vector<T>::search(T item) const {
    for(size_t i = 0; i < size; i++) {
        if(data[i] == item) return i;
    }
    return -1;
}

template <class T>
size_t vector<T>::get_size() const { return size; }

template <class T>
size_t vector<T>::get_capacity() const { return capacity; }

template <class T>
std::istream& operator>>(std::istream& in, vector<T>& obj) {
    for(size_t i = 0; i < obj.size; i++) {
        in >> obj.data[i];
    }
    return in;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const vector<T>& obj) {
    for(size_t i = 0; i < obj.size; i++) {
        out << obj.data[i] << " ";
    }
    out << "\n";
    return out;
}

#endif // vector_H
