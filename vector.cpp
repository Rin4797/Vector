#include "vector.h"

void Vector::Reallocate(Vector::SizeType new_size) {
    if (new_size <= capacity_) {
        return;
    }
    SizeType new_capacity = capacity_;
    if (new_capacity == 0) {
        new_capacity = 1;
    }
    while (new_size > new_capacity) {
        new_capacity *= 2;
    }
    ValueType* new_pointer_begin = new ValueType[new_capacity];
    std::copy(pointer_begin_, pointer_begin_ + size_, new_pointer_begin);
    delete[] pointer_begin_;
    pointer_begin_ = new_pointer_begin;
    capacity_ = new_capacity;
}

void Vector::Reserve(SizeType new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    ValueType* new_pointer_begin = new ValueType[new_capacity];
    std::copy(pointer_begin_, pointer_begin_ + size_, new_pointer_begin);
    delete[] pointer_begin_;
    pointer_begin_ = new_pointer_begin;
    capacity_ = new_capacity;
}

void Vector::InitVector(size_t size) {
    size_ = 0;
    capacity_ = 0;
    pointer_begin_ = nullptr;
    Reserve(size);
    size_ = size;
}

Vector::Vector() {
    size_ = 0;
    capacity_ = 0;
    pointer_begin_ = nullptr;
}

Vector::Vector(size_t size) {
    InitVector(size);
    for (SizeType id = 0; id < size_; ++id) {
        pointer_begin_[id] = 0;
    }
}

Vector::Vector(std::initializer_list<ValueType> list) {
    InitVector(list.size());
    ValueType* pnt = pointer_begin_;
    for (const auto& element : list) {
        *pnt = element;
        pnt++;
    }
}

Vector::Vector(const Vector& other) {
    InitVector(other.Size());
    std::copy(other.pointer_begin_, other.pointer_begin_ + other.size_, pointer_begin_);
}

Vector& Vector::operator=(const Vector& other) {
    ClearArray();
    size_ = 0;
    capacity_ = 0;
    InitVector(other.Size());
    std::copy(other.pointer_begin_, other.pointer_begin_ + other.size_, pointer_begin_);
    return *this;
}

void Vector::ClearArray() {
    delete[] pointer_begin_;
    pointer_begin_ = nullptr;
}

void Vector::Clear() {
    size_ = 0;
}

Vector::~Vector() {
    ClearArray();
}

Vector::SizeType Vector::Size() const {
    return size_;
}

Vector::SizeType Vector::Capacity() const {
    return capacity_;
}

Vector::ValueType& Vector::operator[](size_t position) {
    return pointer_begin_[position];
}

Vector::ValueType Vector::operator[](size_t position) const {
    return pointer_begin_[position];
}

void Vector::PushBack(const ValueType& new_element) {
    Reallocate(size_ + 1);
    *(pointer_begin_ + size_) = new_element;
    size_++;
}
void Vector::PopBack() {
    size_--;
}

const Vector::ValueType* Vector::Data() const {
    return pointer_begin_;
}

void Vector::Swap(Vector& other) {
    std::swap(other.size_, size_);
    std::swap(other.capacity_, capacity_);
    std::swap(other.pointer_begin_, pointer_begin_);
}

Vector::Iterator Vector::begin() {
    return Iterator(pointer_begin_);
}

Vector::Iterator Vector::end() {
    return Iterator(pointer_begin_ + static_cast<DifferenceType>(size_));
}

Vector::Iterator Vector::Begin() {
    return begin();
}

Vector::Iterator Vector::End() {
    return end();
}

bool Vector::operator==(const Vector& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (SizeType i = 0; i < size_; ++i) {
        if ((*this)[i] != other[i]) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

std::strong_ordering Vector::operator<=>(const Vector& other) const {
    for (SizeType i = 0; i < size_ && i < other.size_; ++i) {
        if ((*this)[i] != other[i]) {
            return (*this)[i] <=> other[i];
        }
    }
    return size_ <=> other.size_;
}

Vector::Iterator::Iterator() {
    id_ = nullptr;
}

Vector::Iterator::Iterator(Vector::ValueType* pointer) {
    id_ = pointer;
}

Vector::ValueType& Vector::Iterator::operator*() const {
    return *id_;
}

Vector::ValueType* Vector::Iterator::operator->() const {
    return id_;
}

Vector::Iterator& Vector::Iterator::operator=(Vector::Iterator other) {
    id_ = other.id_;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator++() {
    ++id_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator new_iterator(id_);
    ++(*this);
    return new_iterator;
}

Vector::Iterator& Vector::Iterator::operator--() {
    --id_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator--(int) {
    Iterator new_iterator(id_);
    --(*this);
    return new_iterator;
}

Vector::Iterator Vector::Iterator::operator+(Vector::DifferenceType shift) {
    Iterator res(id_ + shift);
    return res;
}

Vector::DifferenceType Vector::Iterator::operator-(Vector::Iterator other) {
    return id_ - other.id_;
}
Vector::Iterator& Vector::Iterator::operator+=(Vector::DifferenceType shift) {
    id_ += shift;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator-=(Vector::DifferenceType shift) {
    return *this += (-shift);
}

bool Vector::Iterator::operator==(const Vector::Iterator& other) const {
    return id_ == other.id_;
}

bool Vector::Iterator::operator!=(const Vector::Iterator& other) const {
    return !(*this == other);
}

std::strong_ordering Vector::Iterator::operator<=>(const Vector::Iterator& other) const {
    return id_ <=> other.id_;
}
