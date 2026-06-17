## Test R Elastix ParameterMap interface methods: has_key, get, set, del
## These methods enable proper map item access in R, similar to Lua/Python

library(SimpleITK)

# Test using Elastix ParameterMap (std::map<string, VectorString>)
cat("Testing R Elastix ParameterMap Interface Methods\n")
cat("===============================================\n\n")

# Create an ElastixImageFilter and get a default parameter map
elastixImageFilter <- ElastixImageFilter()
parameterMap <- elastixImageFilter$GetDefaultParameterMap("translation")

# Test 1: has_key() method
if (!parameterMap$has_key("Transform")) {
  stop("FAILED: has_key('Transform') should return TRUE")
}
if (parameterMap$has_key("NonExistentKey123")) {
  stop("FAILED: has_key('NonExistentKey123') should return FALSE")
}
cat("Test 1: has_key() method - OK\n")


# Test 2: get() method
transform_value <- parameterMap$get("Transform")
if (!is.vector(transform_value) || length(transform_value) == 0) {
  stop("FAILED: get('Transform') did not return a valid vector")
}
if (transform_value[1] != "TranslationTransform") {
  stop(paste("FAILED: Expected TranslationTransform but got", transform_value[1]))
}
cat("Test 2: get() method - OK\n")


# Test 3: set() method
test_value <- c("TestValue1", "TestValue2")
parameterMap$set("TestKeyForSet", test_value)
if (!parameterMap$has_key("TestKeyForSet")) {
  stop("FAILED: Key 'TestKeyForSet' not found after set()")
}
retrieved_value <- parameterMap$get("TestKeyForSet")
if (!all(retrieved_value == test_value)) {
  stop("FAILED: Retrieved value does not match what was set")
}
cat("Test 3: set() method - OK\n")


# Test 4: del() method
if (!parameterMap$has_key("TestKeyForSet")) {
  stop("FAILED: TestKeyForSet should exist before deletion")
}
parameterMap$del("TestKeyForSet")
if (parameterMap$has_key("TestKeyForSet")) {
  stop("FAILED: TestKeyForSet still exists after deletion")
}
cat("Test 4: del() method - OK\n")


# Test 5: Multiple operations in sequence
for (i in 1:3) {
  key <- paste0("SequentialKey", i)
  value <- c(paste0("Value", i, "_1"), paste0("Value", i, "_2"))
  parameterMap$set(key, value)
}
for (i in 1:3) {
  if (!parameterMap$has_key(paste0("SequentialKey", i))) {
    stop("FAILED: Not all sequential keys exist")
  }
}
for (i in 1:3) {
  key <- paste0("SequentialKey", i)
  val <- parameterMap$get(key)
  expected <- c(paste0("Value", i, "_1"), paste0("Value", i, "_2"))
  if (!all(val == expected)) {
    stop(paste("FAILED: Value mismatch for", key))
  }
}
for (i in 1:3) {
  parameterMap$del(paste0("SequentialKey", i))
}
for (i in 1:3) {
  if (parameterMap$has_key(paste0("SequentialKey", i))) {
    stop(paste("FAILED: SequentialKey", i, "still exists after deletion"))
  }
}
cat("Test 5: Sequential operations - OK\n")


# Test 6: Error handling
error_caught <- FALSE
tryCatch({
  parameterMap$get("NonExistentKey")
  stop("FAILED: get() on non-existent key should throw an error")
}, error = function(e) {
  error_caught <<- TRUE
})
if (!error_caught) {
  stop("FAILED: get() should throw on non-existent key")
}

error_caught <- FALSE
tryCatch({
  parameterMap$del("NonExistentKey")
  stop("FAILED: del() on non-existent key should throw an error")
}, error = function(e) {
  error_caught <<- TRUE
})
if (!error_caught) {
  stop("FAILED: del() should throw on non-existent key")
}
cat("Test 6: Error handling - OK\n")

cat("\n")
cat("All tests passed\n")
