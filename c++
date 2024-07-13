#include <iostream>
using namespace std;

template<typename T>
class Array {
private:
    T* data;
    int size;
    int capacity;

public:
    Array() : data(nullptr), size(0), capacity(0) {}

    ~Array() {
        if (data) {
            delete[] data;
        }
    }

    Array(const Array& other) : size(other.size), capacity(other.capacity) {
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            if (data) {
                delete[] data;
            }
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    int GetSize() const {
        return size;
    }

    void SetSize(int newSize, int grow = 1) {
        if (newSize <= capacity) {
            size = newSize;
        } else {
            int newCapacity = capacity + grow;
            while (newSize > newCapacity) {
                newCapacity += grow;
            }
            T* newData = new T[newCapacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            size = newSize;
            capacity = newCapacity;
        }
    }

    int GetUpperBound() const {
        return size - 1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
        if (size < capacity) {
            T* newData = new T[size];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = size;
        }
    }

    void RemoveAll() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    T GetAt(int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        } else {
            throw out_of_range("Index out of range");
        }
    }

    void SetAt(int index, const T& value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        } else {
            throw out_of_range("Index out of range");
        }
    }

    T& operator[](int index) {
        if (index >= 0 && index < size) {
            return data[index];
        } else {
            throw out_of_range("Index out of range");
        }
    }

    void Add(const T& element, int grow = 1) {
        if (size >= capacity) {
            SetSize(size + 1, grow);
        } else {
            data[size++] = element;
        }
    }

    void Append(const Array& other) {
        int newSize = size + other.size;
        if (newSize > capacity) {
            int newCapacity = capacity;
            while (newSize > newCapacity) {
                newCapacity += 1;
            }
            T* newData = new T[newCapacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            for (int i = 0; i < other.size; ++i) {
                newData[size + i] = other.data[i];
            }
            delete[] data;
            data = newData;
            size = newSize;
            capacity = newCapacity;
        } else {
            for (int i = 0; i < other.size; ++i) {
                data[size + i] = other.data[i];
            }
            size = newSize;
        }
    }

    T* GetData() const {
        return data;
    }

    void InsertAt(int index, const T& element) {
        if (index >= 0 && index <= size) {
            if (size >= capacity) {
                SetSize(size + 1);
            }
            for (int i = size; i > index; --i) {
                data[i] = data[i - 1];
            }
            data[index] = element;
            ++size;
        } else {
            throw out_of_range("Index out of range");
        }
    }

    void RemoveAt(int index, int count = 1) {
        if (index >= 0 && index < size && count > 0) {
            if (index + count > size) {
                count = size - index;
            }
            for (int i = index; i < size - count; ++i) {
                data[i] = data[i + count];
            }
            size -= count;
        } else {
            throw out_of_range("Index out of range");
        }
    }
};
