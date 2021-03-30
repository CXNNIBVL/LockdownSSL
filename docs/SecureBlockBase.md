# SecureBlockBase\<T, A>

***

## Description
Base class for [FixedSizeSecureBlock](./FixedSizeSecureBlock.md) and [SecureBlock](./SecureBlock.md).

* Templated  with `template<typename T, class A>`
  * `A` The Allocator
  * `using value_type = T`
  * `using pointer = value_type*`
  * `using reference = value_type&`
  * `using Iterator = `[`SecureBlockIterator`](./SecureBlockIterator.md)`<value_type>`

***

## Public Members

### Constructors

| Constructor | Parameters | Description |
| --- | --- | --- |
| `explicit SecureBlockBase(size_t Size=0)` | `Size` The size of the block | Requests `Size` from `m_Alloc` and sets all the contents to zero |
| `SecureBlockBase(size_t Size, T val)` | `Size` The size of the block <br/> `val` the value to fill the block with | Requests `Size` from `m_Alloc` and sets athe contents to `val` |
| `SecureBlockBase(const SecureBlockBase<T, A>& Other)` | `Other` Another SecureBlockBase of type `T` and Allocator `A` | Creates a SecureBlockBase from another SecureBlockBase |
| `SecureBlockBase(const T* data, size_t size)` | `data` pointer to `T`s <br/> `size` The size of the `data` pointer | Creates a SecureBlockBase from a pointer. If `data` is a `nullptr` then `m_Data` will be zeroized. |

### Functions

| Function | Parameters | Description |
| --- | --- | --- |
| `~SecureBlockBase()` | &nbsp; | Deallocates `m_Data` |
| `size_t Size() const` | &nbsp; | Returns the size of the block |
| `Iterator begin()` | &nbsp; | Returns an `Iterator` to the start of `m_Data` |
| `Iterator end()` | &nbsp; | Returns an `Iterator` to `m_Data + m_Size + 1` |
| `const pointer Data()` | &nbsp; | Returns a `const` pointer to `m_Data` |
| `pointer Data()` | &nbsp; | Returns a pointer to `m_Data` |
| `bool IsEmpty() const` | &nbsp; | Returns `true` if `m_Size == 0` |
| `virtual void AssignPtr(const T* data, size_t len)` | `data` pointer to `T`s <br/> `len` Length of `data` | No default implementation. |
| `template<class Al> void AssignBlock(const SecureBlockBase<T,Al>& other)` | `Al` an arbitrary Allocator <br/> `other` A SecureBlockBase of type `T` and Allocator `Al` | Copies the contents of `other`. Internally calls `AssignPtr(other.Data(), other.Size())` |
| `template<class Al> bool operator==(const SecureBlockBase<T,Al>& other) const` | `Al` An Arbitrary Allocator <br/> `other` A SecureBlockBase of type `T` and Allocator `Al` | Compares `m_Size` and the contents of `m_Data` to those of `other` |
| `template<class Al> bool operator!=(const SecureBlockBase<T,Al>& other) const` | `Al` An Arbitrary Allocator <br/> `other` A SecureBlockBase of type `T` and Allocator `Al` | The inverse of `operator==` |
| `const pointer operator+(size_t offset) const` | `offset` A pointer offset | Returns a `const pointer` to `m_Data + offset`  |
| `pointer operator+(size_t offset)` | `offset` A pointer offset | Returns a `pointer` to `m_Data + offset` |
| `const reference operator[](size_t index) const` | `index` The index | Returns a `const reference` to the value of `m_Data[index]` |
| `reference operator[](size_t index)` | `index` The index | Returns a `reference` to the value of `m_Data[index]` |
| `template<class Al> SecureBlockBase<T, A>& operator=(const SecureBlockBase<T,Al>& other)` | `Al` An arbitrary Allocator <br/> `other` A SecureBlockBase of type `T` and Allocator `Al` | Copies the contents of `other`. Internally calls `AssignBlock<Al>(other)` |

***

## Protected Members

### Variables

| Name | Type | Description |
| --- | --- | --- |
| `m_Alloc` | `A` | The Allocator |
| `m_Data` | `T*` | The Data pointer |
| `m_Size` | `size_t` | The size of the block |

***

## Usage
This Class is only intended for inheritance with [SecureBlock](./SecureBlock.md) and [FixedSizeSecureBlock](./FixedSizeSecureBlock.md).

***

Defined in [SecureBlock.h](https://github.com/FlyingRaijinMinato/LockdownSSL/blob/main/Includes/SecureBlock.h)