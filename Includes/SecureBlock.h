#pragma once

#include <cstring>
#include "types.h"

template<typename T>
class SecureAllocator
{
public:
    using value_type = T;
    using size_type = size_t;
    using pointer = value_type*;

public:
    SecureAllocator() = default;

    pointer Allocate(size_type num)
    {
        if(num == 0)
            return nullptr;

        return new T[num];
    }

    pointer Reallocate(pointer ptr, size_type oldSize, size_type newSize)
    {
        if(oldSize == newSize)
        {
            return ptr;
        }
        else if(oldSize > newSize)
        {
            Deallocate(ptr + newSize, oldSize - newSize);
            return ptr;
        }
        else
        {
            pointer new_ptr = Allocate(newSize);
            std::memcpy(new_ptr, ptr, oldSize * sizeof(T));
            Deallocate(ptr, oldSize);

            return new_ptr;
        }
    }

    void Deallocate(void* ptr, size_type num)
    {
        std::memset(ptr, 0, num * sizeof(T));
        delete[] (T*) ptr;
    }
};

template<typename _SecBlock>
class SecureBlockIterator
{
public:
    using value_type = _SecBlock::value_type;
    using pointer = value_type*;
    using reference = &value_type;

public:
    SecureBlockIterator(pointer ptr) : m_Ptr(ptr){}

    SecureBlockIterator& operator++() { m_Ptr++; return *this; }

    SecureBlockIterator operator++(int) { SecureBlockIterator iterator = *this; ++(*this); return iterator; }

    SecureBlockIterator& operator--() { m_Ptr--; return *this; }

    SecureBlockIterator operator--(int) { SecureBlockIterator iterator = *this; --(*this); return iterator; }

    reference operator[](int index) { return *(m_Ptr[index]); }

    pointer operator->() { return m_Ptr; }

    reference operator*() { return *m_Ptr; }

    bool operator==(const SecureBlockIterator& other) { return m_Ptr == other.m_Ptr; }

    bool operator!=(const SecureBlockIterator& other) { return !(*this == other); }

private:
    pointer m_Ptr;
};

template<typename T>
class SecureBlock
{
public:
    using value_type = T;
    using Iterator = SecureBlockIterator<SecureBlock<T>>;

public:

    explicit SecureBlock(size_t Size=0)
        : m_Size(Size) { m_Data = m_Alloc.Allocate(m_Size); }

    SecureBlock(const SecureBlock<T>& Other)
        : m_Size(Other.m_Size)
    {
        m_Data = m_Alloc.Allocate(m_Size);
        std::memcpy(m_Data, Other.m_Data, m_Size * sizeof(T));
    }

    SecureBlock(const T* data, size_t size)
        : m_Size(size)
    {
        m_Data = m_Alloc.Allocate(m_Size);
        
        if(data)
            std::memcpy(m_Data, data, m_Size * sizeof(T));
        else
            std::memset(m_Data, 0, m_Size * sizeof(T));
    }

    ~SecureBlock() { m_Alloc.Deallocate(m_Data, m_Size); }

    size_t Size() const { return m_Size; }

    Iterator Begin() { return Iterator(m_Data); }

    Iterator End() { return Iterator(m_Data + m_Size); }

    operator const void *() const { return m_Data;}
    operator void *() { return m_Data; }

    const T* operator+(size_t offset) const { return m_Data + offset; }
    T* operator+(size_t offset) { return m_Data + offset; }

    const T& operator[](size_t index) const { return m_Data[index]; }
    T& operator[](size_t index) { return m_Data[index]; }

    const T* data() const { return m_Data; }
    T* data() { return m_Data; }

    bool IsEmpty() const { return m_Size == 0; }

    void Reallocate(size_t newSize) { m_Data = m_Alloc.Reallocate(m_Data, m_Size, newSize); m_Size = newSize; }
    void CleanReallocate(size_t newSize) { Reallocate(newSize); memset(m_Data, 0, m_Size * sizeof(T)); }

    void Grow(size_t count)
    {
        m_Data = m_Alloc.Reallocate(m_Data, m_Size, m_Size + count);
        m_Size += count;
    }

    void CleanGrow(size_t count)
    {
        m_Data = m_Alloc.Reallocate(m_Data, m_Size, m_Size + count);
        std::memset(m_Data + m_Size, 0, count * sizeof(T));
        m_Size += count;
    }

    

private:
    SecureAllocator<T> m_Alloc;
    T* m_Data;
    size_t m_Size;
};