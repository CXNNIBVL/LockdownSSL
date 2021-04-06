# FixedSizeSecureAllocator\<T, S>

***

## Description
Allocator, providing stack based secure memory allocation and deallocation.

* Templated  with `template<typename T, size_t S>`
  * `S` Size of the Buffer  
  * `using value_type = T`
  * `using size_type = size_t`
  * `using pointer = value_type*`

***

## Public Members

### Constructors

| Constructor | Parameters | Description |
| --- | --- | --- |
| `FixedSizeSecureAllocator() = default` | &nbsp; | Default Constructor |

### Functions

| Function | Parameters | Description |
| --- | --- | --- |
| `pointer Allocate(size_type num)` | `num` Number of elements to allocate | Returns a `pointer` to the stack based memory |
|`pointer Reallocate(pointer ptr, size_type oldSize, size_type newSize)` | `ptr` the old pointer <br/> `oldSize` the old size <br/> `newSize` the new size | Reallocates the old `ptr` to fit `newSize` <br/> if `newSize < oldSize` then the remaining indices are zeorized |
| `void Deallocate(void* ptr, size_type num)` | `ptr` the pointer to deallocate <br/> `num` size of the pointer | Zeroizes the stack array |

***

## Usage
This Class is only intended for use in [FixedSizeSecureBlock](./FixedSizeSecureBlock.md). In no way is it an STL compatible allocator!

***

Defined in [SecureBlock.h](https://github.com/FlyingRaijinMinato/LockdownSSL/blob/main/Includes/SecureBlock.h)