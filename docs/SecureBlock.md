# SecureBlock\<T>

***

## Description
Container type with secure memory Allocation and Deallocation

* Templated  with `template<typename T>`

***

## Inheritance

| Class | Mode | Links |
| --- | --- | --- |
| `SecureBlockBase<T, SecureAllocator<T>>` | `public` | [SecureBlockBase](./SecureBlockBase.md) <br/> [SecureAllocator](./SecureAllocator.md) |

***

## Public Members

### Constructors

| Constructor | Parameters | Description |
| --- | --- | --- |
| `explicit SecureBlock(size_t Size=0)` | `Size` The size of the block | Requests `Size` from `m_Alloc` and sets all the contents to zero |
| `SecureBlock(size_t Size, T val)` | `Size` The size of the block <br/> `val` the value to fill the block with | Requests `Size` from `m_Alloc` and sets athe contents to `val` |
| `SecureBlock(const SecureBlock<T>& Other)` | `Other` Another SecureBlock of type `T` | Creates a SecureBlock from another SecureBlock |
| `SecureBlock(const T* data, size_t size)` | `data` pointer to `T`s <br/> `size` The size of the `data` pointer | Creates a SecureBlock from a pointer. If `data` is a `nullptr` then `m_Data` will be zeroized. |
| `SecureBlock(SecureBlock<T>&& Other)` | `Other` Rvalue reference of another SecureBlock of type `T` | Moves `Other` into the new Block |

### Functions

| Function | Parameters | Description |
| --- | --- | --- |
| `void Resize(size_t newSize)` | `newSize` The new size | Resizes the block to fit `newSize` |
| `void CleanResize(size_t newSize)` | `newSize` The new size | Resizes the block to fit `newSize` and zeroizes the entire buffer |
| `void Grow(size_t count)` | `count` The count of elements to be added | Increases the blocks size by `count` |
| `void CleanGrow(size_t count)` | `count` The count of elements to be added | Increases the blocks size by `count` and zeroizes the added indices |
| `void AssignPtr(const T* data, size_t len) override` | `data` A pointer to `T`s <br/> `len` length of `data` | Resizes the block to fit `len` and copies `data`  |
| `SecureBlock<T>& operator=(SecureBlock<T>&& Other)` | `Other` Rvalue reference of another SecureBlock of type `T` | Moves `Other` into the Block |

***

Defined in [SecureBlock.h](https://github.com/FlyingRaijinMinato/LockdownSSL/blob/main/Includes/SecureBlock.h)