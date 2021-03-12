# SecureAllocator<T>

***

## Description
Allocator, providing secure memory allocation and deallocation.

* Templated  with `template<typename T>`
  * `using value_type = T`
  * `using size_type = size_t`
  * `using pointer = value_type*`

***

## Public Members

### Constructors
Constructor | Parameters | Description
--- | --- | ---
`SecureAllocator() = default;` | ~~XXXX~~ | Default Constructor

### Functions

Function | Parameters | Description
--- | --- | ---
`pointer Allocate(size_type num)` | `num` Number of elements to allocate | Allocates the requested size `num` and returns a `pointer`. If `num == 0`, then `Allocate` returns a `nullptr`
`pointer Reallocate(pointer ptr, size_type oldSize, size_type newSize)` | `ptr` the old pointer <br/> `oldSize` the old size <br/> `newSize` the new size | Reallocates the old `ptr` to fit `newSize` <br/> if `newSize <= oldSize` then the old pointer is returned
`void Deallocate(void* ptr, size_type num)` | `ptr` the pointer to deallocate <br/> `num` size of the pointer | Deallocates `num * sizeof(T)` bytes of the pointer

***

## Usage
This Class is only intended for use in [SecureBlock](./SecureBlock.md). In no way is it an STL compatible allocator!

***

Defined in [SecureBlock.h](https://github.com/FlyingRaijinMinato/LockdownSSL/blob/main/Includes/SecureBlock.h)