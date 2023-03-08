PKG_CPPFLAGS='-Xclang -fopenmp' PKG_LIBS=-lomp R CMD INSTALL myPackage
CPPFLAGS += -Xclang -fopenmp
LDFLAGS += -lomp
export CC := clang
export CXX := $(CC)++
#export CC := /usr/local/opt/llvm/bin/clang
#export CXX := $(CC)++
LDFLAGS += -L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib
CPPFLAGS += -I/usr/local/opt/llvm/include -I/usr/local/opt/llvm/include/c++/v1/
ifeq ($(shell brew info llvm 2>&1 | grep -c "Built from source on"), 1)
#we are using a homebrew clang, need new flags
LDFLAGS += -L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib
CPPFLAGS += -I/usr/local/opt/llvm/include -I/usr/local/opt/llvm/include/c++/v1/
endif
-:
	@curl -O https://mac.r-project.org/openmp/openmp-12.0.1-darwin20-Release.tar.gz
	@sudo tar fvxz openmp-12.0.1-darwin20-Release.tar.gz -C /
	@codesign -d -vv /usr/local/lib/libomp.dylib
	@type -P brew && brew install llvm || echo
	@type -P apt-get && apt-get install llvm || echo "install llvm"
	@type -P apt-get && apt-get install clang-15 lldb-15 lld-15 || echo "install clang-15 lldb-15 lld-15"