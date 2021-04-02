#pragma once

#include <cstring>
#include <initializer_list>

#include "lockdownssl/types.h"

namespace LockdownSSL
{
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

            pointer p = new T[num];
            std::memset(p, 0, num * sizeof(T));

            return p;
        }

        pointer Reallocate(pointer ptr, size_type oldSize, size_type newSize)
        {
            if(oldSize == newSize)
            {
                return ptr;
            }
        
            pointer new_ptr = Allocate(newSize);
            std::memcpy(new_ptr, ptr, (oldSize > newSize ? newSize : oldSize) * sizeof(T));
            Deallocate(ptr, oldSize); 

            return new_ptr;
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
        using value_type = T;
        using size_type = size_t;
        using pointer = value_type*;

    public:

        FixedSizeSecureAllocator() = default;

        pointer Allocate(size_type num)
        {
            return m_Arr;
        }

        pointer Reallocate(pointer ptr, size_type oldSize, size_type newSize)
        {
            if (ptr == m_Arr && newSize <= S && newSize < oldSize)
                std::memset(ptr + newSize, 0, (oldSize - newSize) * sizeof(T));

            return ptr;
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

        pointer operator+(int i) { return m_Ptr + i;}

        SecureBlockIterator& operator--() { m_Ptr--; return *this; }

        SecureBlockIterator operator--(int) { SecureBlockIterator iterator = *this; --(*this); return iterator; }

        reference operator[](int index) { return m_Ptr[index]; }

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
        using pointer = value_type*;
        using reference = value_type&;
        using Iterator = SecureBlockIterator<value_type>;

    public:

        explicit SecureBlockBase(size_t Size=0)
            : m_Size(Size) 
        {
            m_Data = m_Alloc.Allocate(m_Size);
            std::memset(m_Data, 0, m_Size * sizeof(T));
        }

        SecureBlockBase(size_t Size, T val)
            : m_Size(Size)
        {
            m_Data = m_Alloc.Allocate(m_Size);
            
            for(auto it = begin(); it != end(); it++)
                *it = val;
        }

        SecureBlockBase(const SecureBlockBase<T, A>& Other)
            : m_Size(Other.m_Size)
        {
            m_Data = m_Alloc.Allocate(m_Size);

            if(Other.Data())
                std::memcpy(m_Data, Other.Data(), m_Size * sizeof(T));
            else
                std::memset(m_Data, 0, m_Size * sizeof(T));
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

    public:

        ~SecureBlockBase() { m_Alloc.Deallocate(m_Data, m_Size); }

        size_t Size() const { return m_Size; }

        Iterator begin() { return Iterator(m_Data); }

        Iterator end() { return Iterator(m_Data + m_Size); }

        const pointer Data() const { return m_Data; }
        pointer Data() { return m_Data; }

        bool IsEmpty() const { return m_Size == 0; }

        virtual void AssignPtr(const T* data, size_t len) = 0;

        template<class Al>
        void AssignBlock(const SecureBlockBase<T,Al>& other) { AssignPtr(other.Data(), other.Size()); }

        template<class Al>
        bool operator==(const SecureBlockBase<T,Al>& other) const
        {
            return m_Size == other.Size() && std::memcmp(m_Data, other.Data(), m_Size * sizeof(T)) == 0;
        }

        template<class Al>
        bool operator!=(const SecureBlockBase<T,Al>& other) const { return !operator==(other); }

        const pointer operator+(size_t offset) const { return m_Data + offset; }
        pointer operator+(size_t offset) { return m_Data + offset; }

        const reference operator[](size_t index) const { return m_Data[index]; }
        reference operator[](size_t index) { return m_Data[index]; }

        template<class Al>
        SecureBlockBase<T, A>& operator=(const SecureBlockBase<T,Al>& other)
        {
            AssignBlock<Al>(other);
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

        SecureBlock(size_t Size, T val) : SecureBlockBase<T,Alloc>(Size, val) {}

        SecureBlock(const SecureBlock<T>& Other) : SecureBlockBase<T, Alloc>(Other) {}

        SecureBlock(const T* Data, size_t Size) : SecureBlockBase<T, Alloc>(Data, Size) {}

        SecureBlock(std::initializer_list<T> const & List) : SecureBlockBase<T, Alloc>(List.size())
        {
            std::memcpy(this->m_Data, List.begin(), this->m_Size * sizeof(T));
        }

        SecureBlock(SecureBlock<T>&& Other)
        {
            this->m_Data = Other.m_Data;
            this->m_Size = Other.m_Size;
            Other.m_Data = nullptr;
            Other.m_Size = 0;
        }

    public:

        void Resize(size_t newSize) { this->m_Data = this->m_Alloc.Reallocate(this->m_Data, this->m_Size, newSize); this->m_Size = newSize; }

        void CleanResize(size_t newSize)
        {
            Resize(newSize);
            std::memset(this->m_Data, 0, this->m_Size * sizeof(T));
        }

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

        void AssignPtr(const T* data, size_t len) override
        {
            if(data && data != this->m_Data)
            {
                Resize(len);
                std::memcpy(this->m_Data, data, len * sizeof(T));
            }
        }

        SecureBlock<T>& operator=(SecureBlock<T>&& Other)
        {
            if(this != &Other)
            {
                this->m_Alloc.Deallocate(this->m_Data, this->m_Size);

                this->m_Size = Other.m_Size;
                this->m_Data = Other.m_Data;

                Other.m_Size = 0;
                Other.m_Data = nullptr;
            }

            return *this;
        }

    private:
        using Alloc = SecureAllocator<T>;
    };

    template<typename T, size_t S=0>
    class FixedSizeSecureBlock : public SecureBlockBase<T, FixedSizeSecureAllocator<T, S>>
    {
    public:
        FixedSizeSecureBlock() : SecureBlockBase<T, Alloc>(S) {}

        FixedSizeSecureBlock(T val) : SecureBlockBase<T,Alloc>(S, val) {}

        FixedSizeSecureBlock(const FixedSizeSecureBlock<T, S>& Other) : SecureBlockBase<T, Alloc>(Other) {}

    public:

        void AssignPtr(const T* data, size_t len) override
        {
            if(data && data != this->m_Data)
                std::memcpy(this->m_Data, data, (len <= S ? len : S) * sizeof(T));
        }

    private:
        using Alloc = FixedSizeSecureAllocator<T, S>;
    };
}