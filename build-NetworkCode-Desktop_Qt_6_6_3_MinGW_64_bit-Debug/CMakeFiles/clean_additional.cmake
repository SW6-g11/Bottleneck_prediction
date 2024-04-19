# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\NetworkCode_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\NetworkCode_autogen.dir\\ParseCache.txt"
  "NetworkCode_autogen"
  )
endif()
