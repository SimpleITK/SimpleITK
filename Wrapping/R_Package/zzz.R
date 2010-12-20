.First.lib <- function(lib,pkg) {
  library.dynam("libSimpleITK.so",pkg,lib)
}
