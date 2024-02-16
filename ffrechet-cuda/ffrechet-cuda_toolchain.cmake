set(CMAKE_CUDA_HOST_COMPILER g++-10)
set(CMAKE_CUDA_ARCHITECTURES 75)

set(CMAKE_CXX_COMPILER g++-10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3 -D_GLIBCXX_ASSERTIONS=1 -fstack-protector-strong -fcf-protection=full -fstack-clash-protection -Werror -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wcast-qual -Wformat=2 -Wundef -Wshadow -Wcast-align -Wunused -Wnull-dereference -Wdouble-promotion -Wimplicit-fallthrough -Wextra-semi -Woverloaded-virtual -Wnon-virtual-dtor -Wold-style-cast -march=native -ffast-math")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--allow-shlib-undefined,--as-needed,-z,noexecstack,-z,relro,-z,now,-z,nodlopen")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--allow-shlib-undefined,--as-needed,-z,noexecstack,-z,relro,-z,now,-z,nodlopen")
