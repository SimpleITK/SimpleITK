#if SWIGPYTHON
// Make __str__ transparent by renaming ToString to __str__
%rename(__str__) ToString;
#endif
