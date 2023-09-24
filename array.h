#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include <algorithm>

template <typename T>
class arr {
    private:
        int size;
        T *data;

    public:
        arr();
        arr(unsigned int size_);
        arr(std::initializer_list<T>);
        arr(const arr &obj);
        ~arr();
        T& operator[](unsigned int);
        arr operator+(const arr&) const;
        arr& operator+=(const arr&);
        arr& operator=(const arr&);
        void input();
        void rndfill(int, int);
        void add(T);
        void pop(unsigned int = 1);
        void resize(unsigned int);
        void insert(const arr&, unsigned int);
        T max() const;
        T min() const;
        T sum() const;
        void sort();
        T search(T, int = 0, int = -1) const;
        int lenght() const;
        void print();
        template <typename U>
        friend std::istream& operator>>(std::istream&, arr<U>&);
        template <typename U>
        friend std::ostream& operator<<(std::ostream&, const arr<U>&);
};

template <typename T>
arr<T>::arr() : size(0), data(nullptr) {}

template <typename T>
arr<T>::arr(unsigned int size_) : size(size_), data(new T[size_]) {}

template <typename T>
arr<T>::arr(std::initializer_list<T> list) : size(list.size()), data(new T[size]) {
    std::copy(list.begin(), list.end(), data);
}

template <typename T>
arr<T>::arr(const arr &obj) : size(obj.size), data(new T[size]) {
    std::copy(obj.data, obj.data + size, data);
}

template <typename T>
arr<T>::~arr() { delete[] data; }

template <typename T>
T& arr<T>::operator[](unsigned int index) { return data[index]; }

template <typename T>
arr<T> arr<T>::operator+(const arr &obj) const {
    arr result(*this);
    result.insert(obj, result.size);
    return result;
}

template <typename T>
arr<T>& arr<T>::operator+=(const arr &obj) {
    *this = *this + obj;
    return *this;
}

template <typename T>
arr<T>& arr<T>::operator=(const arr &obj) {
    size = obj.size;
    delete[] data;
    data = new T[size];
    std::copy(obj.data, obj.data + size, data);
    return *this;
}

template <typename T>
void arr<T>::input() {
    for(int i = 0; i < size; i++) std::cin >> data[i];
}

template <typename T>
void arr<T>::rndfill(int low, int high) {
    for(int i = 0; i < size; i++) {
        data[i] = low + rand()%(high - low + 1);
    }
}

template <typename T>
void arr<T>::add(T num) {
    T *new_data = new T[size + 1];
    std::copy(data, data + size, new_data);
    new_data[size] = num;
    delete[] data;
    data = new_data;
    size++;
}

template <typename T>
void arr<T>::pop(unsigned int n) {
    size -= n;
    T *new_data = new T[size];
    std::copy(data, data + size, new_data);
    delete[] data;
    data = new_data;
}

template <typename T>
void arr<T>::resize(unsigned int size) {
    T *new_data = new T[size];
    std::copy(data, data + size, new_data);
    if(size > this->size) std::fill(new_data + this->size, new_data + size, 0);
    delete[] data;
    data = new_data;
    this->size = size;
}

template <typename T>
void arr<T>::insert(const arr &obj, unsigned int pos) {
    T *new_data = new T[size + obj.size];
    std::copy(data, data + size, new_data);
    std::copy(data + pos, data + size, new_data + pos + obj.size);
    std::copy(obj.data, obj.data + obj.size, new_data + pos);
    delete[] data;
    data = new_data;
    size += obj.size;
}

template <typename T>
T arr<T>::max() const{
    int m = data[0];
    for (int i = 0; i < size; i++) if(data[i] > m) m = data[i];
    return m;
}

template <typename T>
T arr<T>::min() const{
    int m = data[0];
    for (int i = 0; i < size; i++) if(data[i] < m) m = data[i];
    return m;
}

template <typename T>
T arr<T>::sum() const{
    int s = 0;
    for (int i = 0; i < size; i++) s += data[i];
    return s;
}

template <typename T>
void arr<T>::sort() {
    T key;
    int low, high, mid;
    for(int i = 1; i < size; i++) {
        key = data[i]; low = 0; high = i - 1;
        while (low <= high) {
            mid = (high + low) / 2;
            if (key < data[mid]) high = mid - 1;
            else low = mid + 1;
        }
        for (int j = i - 1; j >= low; j--) data[j + 1] = data[j];
        data[low] = key;
    }
}

template <typename T>
T arr<T>::search(T item, int left, int right) const {
    if(right == -1) right = size;
    if (right >= left) {
        int mid = left + (right - left) / 2;
        if (data[mid] == item) return mid;
        if (data[mid] > item) return search(item, left, mid - 1);
        return search(item, mid + 1, right);
    }
    return -1;
}

template <typename T>
int arr<T>::lenght() const { return size; }

template <typename T>
void arr<T>::print() {
    for(int i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}

template <typename T>
std::istream& operator>>(std::istream& in, arr<T>& obj) {
    for(int i = 0; i < obj.size; i++) {
        in >> obj.data[i];
    }
    return in;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const arr<T>& obj) {
    for(int i = 0; i < obj.size; i++) {
        out << obj.data[i] << " ";
    }
    out << "\n";
    return out;
}

#endif // ARRAY_H
