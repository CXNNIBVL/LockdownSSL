# FixedSizeSecureBlock\<T, S>

***

## Description
Container type with stack based secure memory Allocation and Deallocation

* Templated  with `template<typename T, size_t S=0>`
  * `S` Size of the stack array.

***

## Inheritance

| Class | Mode | Links |
| --- | --- | --- |
| `SecureBlockBase<T, FixedSizeSecureAllocator<T, S>>` | `public` | [SecureBlockBase](./SecureBlockBase.md) <br/> [FixedSizeSecureAllocator](./FixedSizeSecureAllocator.md) |

***

## Public Members

### Constructors

| Constructor | Parameters | Description |
| --- | --- | --- |
| `FixedSizeSecureBlock()` | &nbsp; | Default Constructor |
| `FixedSizeSecureBlock(T val)` | `val` the value to fill the block with | Fills the block with `val` |
| `FixedSizeSecureBlock(const FixedSizeSecureBlock<T, S>& Other)` | `Other` Another FixedSizeSecureBlock of type `T` and size `S` | Creates a FixedSizeSecureBlock from another FixedSizeSecureBlock |

### Functions

| Function | Parameters | Description |
| --- | --- | --- |
| `void AssignPtr(const T* data, size_t len) override` | `data` A pointer to `T`s <br/> `len` length of `data` | Copies maximum `S` of `data` into the block |

***

Defined in [SecureBlock.h](https://github.com/FlyingRaijinMinato/LockdownSSL/blob/main/Includes/SecureBlock.h)