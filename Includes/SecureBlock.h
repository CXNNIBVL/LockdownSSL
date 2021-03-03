#pragma once

#include <cstring>
#include "types.h"

#define ALLOCATOR_TYPES using value_type = T;\
                        using size_type = size_t;\
                        using pointer = value_type*;

template<typename T>
class SecureAllocator
{
public:
    ALLOCATOR_TYPES

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

template<typename T, size_t S>
class FixedSizeSecureAllocator
{
public:
    ALLOCATOR_TYPES

public:

    FixedSizeSecureAllocator() = default;

    pointer Allocate(size_type num)
    {
        if(num <= S)
            return m_Arr;

        return nullptr;
    }

    pointer Reallocate(pointer ptr, size_type oldSize, size_type newSize)
    {
        if (ptr == m_Arr && newSize <= S)
        {
            if (oldSize > newSize)
                memset(ptr + newSize, 0, (oldSize - newSize) * sizeof(T));

            return ptr;
        }

        return nullptr;
    }

    void Deallocate(void* ptr, size_type num)
    {
        if(ptr == m_Arr)
            std::memset(ptr, 0, num * sizeof(T));
    }

private:
    T m_Arr[S];
};

template<typename T>
class SecureBlockIterator
{
public:
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;

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

template<typename T, class A>
class SecureBlockBase
{
public:
    using value_type = T;
    using Iterator = SecureBlockIterator<value_type>;

public:

    explicit SecureBlockBase(size_t Size=0)
        : m_Size(Size) { m_Data = m_Alloc.Allocate(m_Size); }

    SecureBlockBase(const SecureBlockBase<T, A>& Other)
        : m_Size(Other.m_Size)
    {
        m_Data = m_Alloc.Allocate(m_Size);
        std::memcpy(m_Data, Other.m_Data, m_Size * sizeof(T));
    }

    SecureBlockBase(const T* data, size_t size)
        : m_Size(size)
    {
        m_Data = m_Alloc.Allocate(m_Size);
        
        if(data)
            std::memcpy(m_Data, data, m_Size * sizeof(T));
        else
            std::memset(m_Data, 0, m_Size * sizeof(T));
    }

    ~SecureBlockBase() { m_Alloc.Deallocate(m_Data, m_Size); }

    size_t Size() const { return m_Size; }

    Iterator begin() { return Iterator(m_Data); }

    Iterator end() { return Iterator(m_Data + m_Size); }

    const T* Data() const { return m_Data; }
    T* Data() { return m_Data; }

    bool IsEmpty() const { return m_Size == 0; }

    bool operator==(const SecureBlockBase<T, A>& other) const
    {
        return m_Size == other.m_Size && std::memcmp(m_Data, other.m_Data, m_Size * sizeof(T)) == 0;
    }

    bool operator!=(const SecureBlockBase<T, A>& other) const
    {
        return !operator==(other);
    }

    const T* operator+(size_t offset) const { return m_Data + offset; }
    T* operator+(size_t offset) { return m_Data + offset; }

    const T& operator[](size_t index) const { return m_Data[index]; }
    T& operator[](size_t index) { return m_Data[index]; }

    SecureBlockBase<T, A>& operator=(const SecureBlockBase<T, A>& other)
    {
        Assign(other);
        return *this;
    }

protected:
    A m_Alloc;
    T* m_Data;
    size_t m_Size;
};

template<typename T>
class SecureBlock : public SecureBlockBase<T, SecureAllocator<T>>
{
public:

    explicit SecureBlock(size_t Size=0) : SecureBlockBase<T, Alloc>(Size) {}

    SecureBlock(const SecureBlock<T>& Other) : SecureBlockBase<T, Alloc>(Other) {}

    SecureBlock(const T* Data, size_t Size) : SecureBlockBase<T, Alloc>(Data, Size) {}

    void Resize(size_t newSize) { this->m_Data = this->m_Alloc.Reallocate(this->m_Data, this->m_Size, newSize); this->m_Size = newSize; }

    void Grow(size_t count)
    {
        this->m_Data = this->m_Alloc.Reallocate(this->m_Data, this->m_Size, this->m_Size + count);
        this->m_Size += count;
    }

    void CleanGrow(size_t count)
    {
        this->m_Data = this->m_Alloc.Reallocate(this->m_Data, this->m_Size, this->m_Size + count);
        std::memset(this->m_Data + this->m_Size, 0, count * sizeof(T));
        this->m_Size += count;
    }

    void New(size_t newSize)
    {
        this->m_Data = this->m_Alloc.Reallocate(this->m_Data, this->m_Size, newSize);
        this->m_Size = newSize;
        std::memset(this->m_Data, 0, this->m_Size * sizeof(T));
    }

    void Assign(const T* data, size_t len)
    {
        New(len);
        std::memcpy(this->m_Data, data, len * sizeof(T));
    }

    void Assign(const SecureBlock<T>& other)
    {
        Assign(other.m_Data, other.m_Size);
    }

private:
    using Alloc = SecureAllocator<T>;
};

template<typename T, size_t S=0>
class FixedSizeSecureBlock : public SecureBlockBase<T, FixedSizeSecureAllocator<T, S>>
{
public:
    explicit FixedSizeSecureBlock() : SecureBlockBase<T, Alloc>(S) {}

    void Assign(const T* data, size_t len)
    {
        if(len <= S)
        {
            std::memcpy(this->m_Data, data, len * sizeof(T));
            return;
        }

        std::memcpy(this->m_Data, data, S * sizeof(T));
    }

    void Assign(const FixedSizeSecureBlock<T, S>& other)
    {
        Assign(other.m_Data, other.m_Size);
    }

private:
    using Alloc = FixedSizeSecureAllocator<T, S>;
};