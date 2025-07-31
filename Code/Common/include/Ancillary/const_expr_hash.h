/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef sitkConstexprHashMap_h
#define sitkConstexprHashMap_h

#include <array>
#include <utility>
#include <optional>
#include <stdexcept>
#include <algorithm>
#include <string_view>
#include <type_traits>
#include <cstdint>
#include <type_traits>

namespace itk::simple::detail
{
/**
 * \class ConstexprHash
 * \brief A constexpr-compatible hash function for common types
 *
 * This provides hash functions that work in constexpr contexts for
 * commonly used types like integers, strings, and pairs.
 *
 * The algorithm implements the FNV-1a hash function, which is simple and effective for many use cases.
 */
struct ConstexprHash
{
  // FNV-1a hash constants
  static constexpr std::size_t FNV_PRIME = 1099511628211ULL;
  static constexpr std::size_t FNV_OFFSET_BASIS = 14695981039346656037ULL;

  // Hash for integral types
  template <typename T>
  constexpr std::enable_if_t<std::is_integral_v<T>, std::size_t>
  operator()(T value, std::size_t hash = FNV_OFFSET_BASIS) const noexcept
  {

    // Process each byte without using reinterpret_cast
    for (std::size_t i = 0; i < sizeof(T); ++i)
    {
      // Extract each byte using shifting and masking
      auto byte = static_cast<unsigned char>((value >> (i * 8)) & 0xFF);
      hash ^= static_cast<std::size_t>(byte);
      hash *= FNV_PRIME;
    }
    return hash;
  }

  // Hash for string_view
  constexpr std::size_t
  operator()(std::string_view str, std::size_t hash = FNV_OFFSET_BASIS) const noexcept
  {

    for (char c : str)
    {
      hash ^= static_cast<std::size_t>(c);
      hash *= FNV_PRIME;
    }

    return hash;
  }

  // Hash for string literals
  template <std::size_t N>
  constexpr std::size_t
  operator()(const char (&str)[N], std::size_t hash = FNV_OFFSET_BASIS) const noexcept
  {
    return (*this)(std::string_view(str, N - 1), hash); // N-1 to exclude null terminator
  }

  // Hash for char* (not constexpr but provided for convenience)
  std::size_t
  operator()(const char * str, std::size_t hash = FNV_OFFSET_BASIS) const noexcept
  {
    return (*this)(std::string_view(str), hash);
  }

  // Hash for pairs
  template <typename T1, typename T2>
  constexpr std::size_t
  operator()(const std::pair<T1, T2> & p) const noexcept
  {
    auto hash = (*this)(p.first);
    return (*this)(p.second, hash);
  }

  // Hash for tuples using std::apply and fold expression
  template <typename... Args>
  constexpr std::size_t
  operator()(const std::tuple<Args...> & t) const noexcept
  {
    std::size_t hash = FNV_OFFSET_BASIS;
    std::apply([&hash, this](const auto &... elems) { ((hash = (*this)(elems, hash)), ...); }, t);
    return hash;
  }
};

// Converts image dimension and pixel ID pair to a dense index to be used as a key in the hash map.
struct DimensionPixelHash
{
  static constexpr size_t NumberOfPixelTypes = typelist2::length<InstantiatedPixelIDTypeList>::value;
  // Hash for a pair of dimension and pixel ID
  template <typename T>
  constexpr std::size_t
  operator()(const std::pair<unsigned int, T> & p) const noexcept
  {
    return (p.first - 1) * NumberOfPixelTypes + static_cast<std::size_t>(p.second);
  }
};

/**
 * \class ConstexprHashMap
 * \brief A constexpr compatible hash map using std::array for storage
 *
 * This class provides a simplified interface similar to std::unordered_map
 * that can be used in constexpr contexts. It uses linear probing for collision
 * resolution and a fixed-size std::array for storage.
 *
 * \tparam Key The key type for the map
 * \tparam Value The value type for the map
 * \tparam MaxSize The maximum number of elements the map can hold
 * \tparam Hash The hash function type (defaults to ConstexprHash which is constexpr-compatible)
 */
template <typename Key, typename Value, std::size_t MaxSize, typename Hash = ConstexprHash>
class ConstexprHashMap
{
public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<Key, Value>;
  using size_type = std::size_t;
  using hasher = Hash;

private:
  // Actual storage is twice MaxSize to help with collision resolution
  static constexpr std::size_t StorageSize = MaxSize * 2;

  // Storage type that can represent either a key-value pair or an empty slot
  struct Slot
  {
    bool       occupied{ false };
    value_type data;

    constexpr Slot() noexcept {}
    constexpr Slot(const key_type & k, const mapped_type & v) noexcept
      : occupied(true)
      , data(k, v)
    {}

    // Add copy constructor - direct initialization of all members
    constexpr Slot(const Slot & other) noexcept
      : occupied(other.occupied)
      , data(other.data)
    {}

    // Add move constructor - direct initialization of all members
    constexpr Slot(Slot && other) noexcept
      : occupied(other.occupied)
      , data(std::move(other.data))
    {}

    // Explicitly define constexpr assignment operators - use std::pair's copy constructor instead of assignment
    constexpr Slot &
    operator=(const Slot & other) noexcept
    {
      if (this != &other)
      {
        occupied = other.occupied;
        data = value_type(other.data.first, other.data.second); // Reconstruct the pair instead of assigning
      }
      return *this;
    }

    constexpr Slot &
    operator=(Slot && other) noexcept
    {
      if (this != &other)
      {
        occupied = other.occupied;
        data = value_type(other.data.first, other.data.second); // Move construct
      }
      return *this;
    }
  };

  // The hash table storage
  std::array<Slot, StorageSize> slots{};
  std::size_t                   element_count = 0;

  // Hash function
  [[nodiscard]] constexpr std::size_t
  hash(const key_type & key) const
  {
    return hasher{}(key) % StorageSize;
  }

  // Find index for a key or the first empty slot
  [[nodiscard]] constexpr std::size_t
  find_index(const key_type & key) const
  {
    std::size_t idx = hash(key);
    std::size_t original_idx = idx;

    do
    {
      if (!slots[idx].occupied || slots[idx].data.first == key)
      {
        return idx;
      }
      idx = (idx + 1) % StorageSize;
    } while (idx != original_idx);

    // This should never happen if MaxSize < StorageSize
    throw std::overflow_error("Hash map is full. Current size: " + std::to_string(element_count));
  }

public:
  // Default constructor
  constexpr ConstexprHashMap() noexcept = default;

  // Copy constructor
  constexpr ConstexprHashMap(const ConstexprHashMap & other) noexcept
    : slots{}
    , element_count(other.element_count)
  {
    // Copy each slot individually to ensure constexpr compatibility
    for (std::size_t i = 0; i < StorageSize; ++i)
    {
      slots[i] = other.slots[i];
    }
  }

  // Copy assignment operator
  constexpr ConstexprHashMap &
  operator=(const ConstexprHashMap & other) noexcept
  {
    if (this != &other)
    {
      // Copy each slot individually to ensure constexpr compatibility
      for (std::size_t i = 0; i < StorageSize; ++i)
      {
        slots[i] = other.slots[i];
      }
      element_count = other.element_count;
    }
    return *this;
  }

  // Move constructor
  constexpr ConstexprHashMap(ConstexprHashMap && other) noexcept
    : slots{}
    , element_count(other.element_count)
  {
    // Move each slot individually to ensure constexpr compatibility
    for (std::size_t i = 0; i < StorageSize; ++i)
    {
      slots[i] = std::move(other.slots[i]);
    }
    other.element_count = 0;
  }

  // Move assignment operator
  constexpr ConstexprHashMap &
  operator=(ConstexprHashMap && other) noexcept
  {
    if (this != &other)
    {
      // Move each slot individually to ensure constexpr compatibility
      for (std::size_t i = 0; i < StorageSize; ++i)
      {
        slots[i] = std::move(other.slots[i]);
      }
      element_count = other.element_count;
      other.element_count = 0;
    }
    return *this;
  }

  // Constructor from an initializer list
  constexpr ConstexprHashMap(std::initializer_list<value_type> init)
  {
    for (const auto & [k, v] : init)
    {
      insert(k, v);
    }
  }

  // Check if a map contains key
  [[nodiscard]] constexpr bool
  contains(const key_type & key) const
  {
    std::size_t idx = find_index(key);
    return slots[idx].occupied && slots[idx].data.first == key;
  }

  // Insert a key-value pair
  constexpr std::pair<size_type, bool>
  insert(const key_type & key, const mapped_type & value)
  {
    if (element_count >= MaxSize)
    {
      throw std::overflow_error("Maximum map capacity reached");
    }

    std::size_t idx = find_index(key);
    if (slots[idx].occupied)
    {
      if (slots[idx].data.first == key)
      {
        // Key already exists, update value
        slots[idx].data.second = value;
        return { idx, false };
      }
    }
    else
    {
      // New key, insert
      slots[idx] = Slot(key, value);
      ++element_count;
      return { idx, true };
    }

    return { idx, false };
  }

  // Access or insert value for a key
  constexpr mapped_type &
  operator[](const key_type & key)
  {
    std::size_t idx = find_index(key);
    if (!slots[idx].occupied)
    {
      if (element_count >= MaxSize)
      {
        throw std::overflow_error("Maximum map capacity reached");
      }
      slots[idx] = Slot(key, mapped_type{});
      ++element_count;
    }
    return slots[idx].data.second;
  }


  // Access value for key (const version)
  [[nodiscard]] constexpr const mapped_type &
  at(const key_type & key) const
  {
    std::size_t idx = find_index(key);
    if (!slots[idx].occupied || slots[idx].data.first != key)
    {
      throw std::out_of_range("Key not found");
    }
    return slots[idx].data.second;
  }

  // Access value for key (non-const version)
  [[nodiscard]] constexpr mapped_type &
  at(const key_type & key)
  {
    std::size_t idx = find_index(key);
    if (!slots[idx].occupied || slots[idx].data.first != key)
    {
      throw std::out_of_range("Key not found");
    }
    return slots[idx].data.second;
  }


  // Remove key-value pair
  constexpr bool
  erase(const key_type & key)
  {
    std::size_t idx = find_index(key);
    if (!slots[idx].occupied || slots[idx].data.first != key)
    {
      return false;
    }

    // Mark slot as unoccupied
    slots[idx].occupied = false;
    --element_count;

    // Re-hash elements that might be affected by this removal
    std::size_t next_idx = (idx + 1) % StorageSize;
    while (slots[next_idx].occupied)
    {
      key_type &    k = slots[next_idx].data.first;
      mapped_type & v = slots[next_idx].data.second;

      // Mark current slot as unoccupied
      slots[next_idx].occupied = false;
      --element_count;

      // Re-insert the key-value pair
      insert(k, v);

      next_idx = (next_idx + 1) % StorageSize;
    }

    return true;
  }

  // Clear the map
  constexpr void
  clear() noexcept
  {
    for (auto & slot : slots)
    {
      slot.occupied = false;
    }
    element_count = 0;
  }

  // Number of elements in the map
  [[nodiscard]] constexpr size_type
  size() const noexcept
  {
    return element_count;
  }

  // Check if map is empty
  [[nodiscard]] constexpr bool
  empty() const noexcept
  {
    return element_count == 0;
  }

  // Maximum number of elements that can be stored
  [[nodiscard]] constexpr size_type
  max_size() const noexcept
  {
    return MaxSize;
  }

  // Current load factor as a decimal value
  [[nodiscard]] constexpr double
  load_factor() const noexcept
  {
    return static_cast<double>(element_count) / static_cast<double>(StorageSize);
  }

  // Calculate the maximum number of keys for any hash in the map
  [[nodiscard]] constexpr size_type
  max_load_factor() const noexcept
  {
    // Count collisions per hash value
    std::array<size_type, StorageSize> collision_counts{};

    for (size_type i = 0; i < StorageSize; ++i)
    {
      if (slots[i].occupied)
      {
        // Calculate original hash for this key
        size_type original_hash = hash(slots[i].data.first);
        // Increment the collision count for the original hash index
        ++collision_counts[original_hash];
      }
    }

    // Find the maximum number of collisions
    size_type max_collisions = *std::max_element(collision_counts.begin(), collision_counts.end());

    return max_collisions;
  }

  // Iterator implementation - base template
  template <bool IsConst>
  class iterator_impl
  {
  private:
    using HashMapType = std::conditional_t<IsConst, const ConstexprHashMap, ConstexprHashMap>;
    HashMapType * map;
    std::size_t   index;

    // Find the next occupied slot
    constexpr void
    find_next_occupied()
    {
      while (index < StorageSize && !map->slots[index].occupied)
      {
        ++index;
      }
    }

  public:
    // Standard iterator typedefs
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::conditional_t<IsConst, const std::pair<Key, Value>, std::pair<Key, Value>>;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;

    // Constructors
    constexpr iterator_impl() noexcept
      : map(nullptr)
      , index(0)
    {}

    constexpr iterator_impl(HashMapType * m, std::size_t idx) noexcept
      : map(m)
      , index(idx)
    {
      find_next_occupied();
    }

    // Iterator operations
    constexpr iterator_impl &
    operator++() noexcept
    {
      if (index < StorageSize)
      {
        ++index;
        find_next_occupied();
      }
      return *this;
    }

    constexpr iterator_impl
    operator++(int) noexcept
    {
      iterator_impl tmp = *this;
      ++(*this);
      return tmp;
    }

    constexpr reference
    operator*() const noexcept
    {
      return map->slots[index].data;
    }

    constexpr pointer
    operator->() const noexcept
    {
      return &(map->slots[index].data);
    }

    // Comparison operators
    constexpr bool
    operator==(const iterator_impl & other) const noexcept
    {
      return map == other.map && index == other.index;
    }

    constexpr bool
    operator!=(const iterator_impl & other) const noexcept
    {
      return !(*this == other);
    }

    // Allow conversion from non-const to const iterator
    template <bool IsConst2 = IsConst, typename = std::enable_if_t<IsConst2>>
    constexpr iterator_impl(const iterator_impl<false> & other) noexcept
      : map(other.map)
      , index(other.index)
    {}
  };

  // Type aliases for iterator types
  using iterator = iterator_impl<false>;
  using const_iterator = iterator_impl<true>;

  // Iterator methods
  [[nodiscard]] constexpr iterator
  begin() noexcept
  {
    return iterator(this, 0);
  }

  [[nodiscard]] constexpr const_iterator
  begin() const noexcept
  {
    return const_iterator(this, 0);
  }

  [[nodiscard]] constexpr const_iterator
  cbegin() const noexcept
  {
    return const_iterator(this, 0);
  }

  [[nodiscard]] constexpr iterator
  end() noexcept
  {
    return iterator(this, StorageSize);
  }

  [[nodiscard]] constexpr const_iterator
  end() const noexcept
  {
    return const_iterator(this, StorageSize);
  }

  [[nodiscard]] constexpr const_iterator
  cend() const noexcept
  {
    return const_iterator(this, StorageSize);
  }
  /**\brief Find element by key; returns end() if not found */
  [[nodiscard]] constexpr iterator
  find(const key_type & key) noexcept
  {
    size_type idx = find_index(key);
    if (slots[idx].occupied && slots[idx].data.first == key)
    {
      return iterator(this, idx);
    }
    return end();
  }
  /**\brief Find element by key (const); returns cend() if not found */
  [[nodiscard]] constexpr const_iterator
  find(const key_type & key) const noexcept
  {
    size_type idx = find_index(key);
    if (slots[idx].occupied && slots[idx].data.first == key)
    {
      return const_iterator(this, idx);
    }
    return cend();
  }
};

} // namespace itk::simple::detail

#endif // sitkConstexprHashMap_h
