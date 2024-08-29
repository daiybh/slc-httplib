in order to build this library with the testAPP and debug it .

we need do those steps:

* add '''option(build_test "build_testAPP" OFF)'''  into the CMakeList.txt
* add '''if(build_test)
    add_subdirectory(testapp)
endif()''' into the CMakeList.txt

* for sure we need a folder named testapp in the same folder of CMakeList.txt
* in testapp/CMAKeList.txt  we can add_executable , 
    the source files can be there or can be in test_package
* we need modify the conanfile.py
  * add options
  * add "cmake.configure(variables=variables)" in the build() method


after those, we also need execute a command
the build_test option default is off , so we need to add -o build_test=True

    conan build . -s build_type=Debug -o build_test=True

or

    conan install . --output-folder=build -s build_type=Debug --build=missing -o build_test=True


after those  we can debug /run the testApp in the IDE