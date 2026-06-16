// SWIG's R backend does not define %swig_map_methods, so std::map
// instantiations lack get/set/del/has_key. This file adds them,
// mirroring Lua's std_map.i approach.
//
// Must be included before any %template instantiation of std::map.

%extend std::map {
  mapped_type get(const key_type& key) throw (std::out_of_range) {
    auto i = $self->find(key);
    if (i != $self->end())
      return i->second;
    else
      throw std::out_of_range("key not found");
  }
  void set(const key_type& key, const mapped_type& x) {
    (*$self)[key] = x;
  }
  void del(const key_type& key) throw (std::out_of_range) {
    auto i = $self->find(key);
    if (i != $self->end())
      $self->erase(i);
    else
      throw std::out_of_range("key not found");
  }
  bool has_key(const key_type& key) {
    auto i = $self->find(key);
    return i != $self->end();
  }
}
