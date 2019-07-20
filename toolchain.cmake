INCLUDE(CMakeForceCompiler)

# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER arm-owa4x-linux-gnueabihf-gcc)
SET(CMAKE_C_COMPILER   /Volumes/crosstool_owa4x/arm-owa4x-linux-gnueabihf/bin/arm-owa4x-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER /Volumes/crosstool_owa4x/arm-owa4x-linux-gnueabihf/bin/arm-owa4x-linux-gnueabihf-g++)


SET(CMAKE_C_FLAGS "-Wall -mthumb -mthumb-interwork -D_REENTRANT")
SET(CMAKE_SHARED_LINKER_FLAGS "-ldl -lpthread")

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH /Volumes/crosstool_owa4x/arm-owa4x-linux-gnueabihf/arm-owa4x-linux-gnueabihf/sysroot/usr/)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

