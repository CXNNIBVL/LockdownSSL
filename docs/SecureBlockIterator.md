# SecureBlockIterator\<T>

***

## Description
A bare bones Iterator over a pointer

* Templated  with `template<typename T>`
  * `using value_type = T`
  * `using pointer = value_type*`
  * `using reference = value_type&`

***

## Public Members

### Constructors

| Constructor | Parameters | Description |
| --- | --- | --- |
| `SecureBlockIterator(pointer ptr)` | `ptr` pointer to a block of memory | Constructs an Iterator from a `pointer` |

### Functions

| Function | Parameters | Description |
| --- | --- | --- |
| `SecureBlockIterator& operator++() ` | &nbsp; | Increments the pointer address |
| `SecureBlockIterator operator++(int)` | &nbsp; | Increments the current pointer position's value |
| `SecureBlockIterator& operator--()` | &nbsp; | Decrements the pointer address |
| `SecureBlockIterator operator--(int)` | &nbsp; | Decrements the current pointer position's value |
| `reference operator[](int index)` | `index` the index to look up | Returns the value pointed to by the current pointer + index |
| `pointer operator->()` | &nbsp; | Returns the memory address of the current pointer |
| `reference operator*()` | &nbsp; | Returns the current pointers value |
| `bool operator==(const SecureBlockIterator& other)` | `other` Another SecureBlockIterator | Compares the memory addresses |
| `bool operator!=(const SecureBlockIterator& other)` | `other` Another SecureBlockIterator | Returns the inverse of `operator==` |

***

## Usage
This Class is only intended for use with [SecureBlockBase](./SecureBlockBase.md). In no way is it an STL compatible Iterator!

***

Defined in [SecureBlock.h](https://github.com/FlyingRaijinMinato/LockdownSSL/blob/main/Includes/SecureBlock.h)