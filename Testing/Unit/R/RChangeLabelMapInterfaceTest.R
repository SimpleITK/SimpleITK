## Test R std::map<double,double> interface for ChangeLabel filters
## Tests has_key, get, set, del methods on the ChangeMap member

library(SimpleITK)

cat("Testing ChangeLabel Filter ChangeMap Interface\n\n")

filter <- ChangeLabelImageFilter()
cmap <- filter$GetChangeMap()

# Test 1: has_key on empty map
if (cmap$has_key(1.0)) {
  stop("FAILED: has_key(1.0) should return FALSE on empty map")
}
cat("Test 1: has_key() on empty map - OK\n")

# Test 2: set() adds entries
cmap$set(1.0, 10.0)
cmap$set(2.0, 20.0)
cmap$set(3.0, 30.0)
cat("Test 2: set() adds entries - OK\n")

# Test 3: has_key() after set
for (k in c(1.0, 2.0, 3.0)) {
  if (!cmap$has_key(k)) {
    stop(paste("FAILED: has_key(", k, ") should return TRUE after set()"))
  }
}
cat("Test 3: has_key() after set - OK\n")

# Test 4: get() retrieves correct values
expected <- list("1"=10.0, "2"=20.0, "3"=30.0)
for (k in c(1.0, 2.0, 3.0)) {
  val <- cmap$get(k)
  exp <- expected[[as.character(as.integer(k))]]
  if (val != exp) {
    stop(paste("FAILED: get(", k, ") returned", val, "expected", exp))
  }
}
cat("Test 4: get() retrieves correct values - OK\n")

# Test 5: del() removes an entry
cmap$del(2.0)
if (cmap$has_key(2.0)) {
  stop("FAILED: has_key(2.0) should return FALSE after del()")
}
if (!cmap$has_key(1.0) || !cmap$has_key(3.0)) {
  stop("FAILED: other keys should still exist after del(2.0)")
}
cat("Test 5: del() removes an entry - OK\n")

# Test 6: get() on non-existent key throws
error_caught <- FALSE
tryCatch({
  cmap$get(99.0)
  stop("FAILED: get() on non-existent key should throw an error")
}, error = function(e) {
  error_caught <<- TRUE
})
if (!error_caught) {
  stop("FAILED: get() should throw on non-existent key")
}
cat("Test 6: get() on non-existent key throws error - OK\n")

# Test 7: del() on non-existent key throws
error_caught <- FALSE
tryCatch({
  cmap$del(99.0)
  stop("FAILED: del() on non-existent key should throw an error")
}, error = function(e) {
  error_caught <<- TRUE
})
if (!error_caught) {
  stop("FAILED: del() should throw on non-existent key")
}
cat("Test 7: del() on non-existent key throws error - OK\n")

# Test 8: round-trip SetChangeMap / GetChangeMap
filter$SetChangeMap(cmap)
cmap2 <- filter$GetChangeMap()
if (!cmap2$has_key(1.0) || !cmap2$has_key(3.0)) {
  stop("FAILED: round-trip SetChangeMap/GetChangeMap lost entries")
}
if (cmap2$has_key(2.0)) {
  stop("FAILED: round-trip SetChangeMap/GetChangeMap kept deleted entry 2")
}
cat("Test 8: SetChangeMap / GetChangeMap round-trip - OK\n")


lmfilter <- ChangeLabelLabelMapFilter()
lmap <- lmfilter$GetChangeMap()

# Test 9: has_key on empty map
if (lmap$has_key(5.0)) {
  stop("FAILED: has_key(5.0) should return FALSE on empty map")
}
cat("Test 9: has_key() on empty map - OK\n")

# Test 10: set / has_key / get / del
lmap$set(5.0, 50.0)
if (!lmap$has_key(5.0)) {
  stop("FAILED: has_key(5.0) should return TRUE after set()")
}
val <- lmap$get(5.0)
if (val != 50.0) {
  stop(paste("FAILED: get(5.0) returned", val, "expected 50.0"))
}
lmap$del(5.0)
if (lmap$has_key(5.0)) {
  stop("FAILED: has_key(5.0) should return FALSE after del()")
}
cat("Test 10: set / has_key / get / del sequence - OK\n")

# Test 11: round-trip for ChangeLabelLabelMapFilter
lmap$set(7.0, 70.0)
lmap$set(8.0, 80.0)
lmfilter$SetChangeMap(lmap)
lmap2 <- lmfilter$GetChangeMap()
if (!lmap2$has_key(7.0) || !lmap2$has_key(8.0)) {
  stop("FAILED: round-trip SetChangeMap/GetChangeMap lost entries")
}
if (lmap2$get(7.0) != 70.0 || lmap2$get(8.0) != 80.0) {
  stop("FAILED: round-trip SetChangeMap/GetChangeMap returned wrong values")
}
cat("Test 11: SetChangeMap / GetChangeMap round-trip - OK\n")

cat("\n")
cat("All tests passed\n")
