# CMakeLists Generating Xcode Project with OpenMP Support
This repository contains a CMakeLists.txt that can generate Xcode projects where the open source LLVM compiler (instead of the default Clang on Mac OS) is used for compilation, with OpenMP support. It generally follows [this post](http://antonmenshov.com/2017/09/09/clang-openmp-setup-in-xcode/) by Menshov for integration, where the sample code included is also borrowed from his post.

## Usage
1. Install the open source LLVM compiler with [Homebrew](https://brew.sh), with `brew install llvm` command in a terminal.
2. Download and install [CMake GUI](https://cmake.org/download/).
3. Point the source code to the folder containing this CMakeLists.txt, and use a subdirectory (say, "build", for example) to build the binaries.
4. Configure using Xcode generator. The CMakeLists.txt will use `/usr/local/opt/llvm` as the default root directory for the compiler. If Homebrew has installed the compiler into somewhere else, this root directory should be changed correspondingly.
5. Generate and open the Xcode project under the subdirectory to build the binaries.

## Screenshots
![Select Xcode as the generator]
(/screenshots/xcode_generator.jpg)

![CMake GUI after configured]
(/screenshots/cmake_gui.jpg)

![OpenMP can be used with the open source LLVM compiler under Xcode 10 and MacOS 10.14]
(/screenshots/cmake_gui.jpg)