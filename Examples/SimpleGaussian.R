library(SimpleITK)

library() # lists the packages that are installed here.
search()  # lists the packages that are currently loaded.
loadedNamespaces() # lists the packages that are in namespaces.
ls()      # lists the symbols defined so far

filename <- "lenna.png"
reader <- ImageFileReader()
