# Install script for directory: /home/guang/work/Pandora/ExampleContent

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/guang/work/Pandora/ExampleContent")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntimex" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libExampleContent.so.03.00.02"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libExampleContent.so.03.00"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libExampleContent.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/home/guang/work/Pandora/ExampleContent/lib:/home/guang/work/Pandora/PandoraSDK/lib:/home/guang/work/Pandora/PandoraMonitoring/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/guang/work/Pandora/ExampleContent/build/lib/libExampleContent.so.03.00.02"
    "/home/guang/work/Pandora/ExampleContent/build/lib/libExampleContent.so.03.00"
    "/home/guang/work/Pandora/ExampleContent/build/lib/libExampleContent.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libExampleContent.so.03.00.02"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libExampleContent.so.03.00"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libExampleContent.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/guang/work/Pandora/PandoraSDK/lib:/home/guang/work/Pandora/PandoraMonitoring/lib::::::::::::::::::::::::::::::::::::::::::::"
           NEW_RPATH "/home/guang/work/Pandora/ExampleContent/lib:/home/guang/work/Pandora/PandoraSDK/lib:/home/guang/work/Pandora/PandoraMonitoring/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/guang/work/Pandora/ExampleContent/include/" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/PandoraExample" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/PandoraExample")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/PandoraExample"
         RPATH "/home/guang/work/Pandora/ExampleContent/lib:/home/guang/work/Pandora/PandoraSDK/lib:/home/guang/work/Pandora/PandoraMonitoring/lib:/home/guang/Downloads/root-6.14.02/builddir/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES "/home/guang/work/Pandora/ExampleContent/build/bin/PandoraExample")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/PandoraExample" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/PandoraExample")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/PandoraExample"
         OLD_RPATH "/home/guang/work/Pandora/PandoraSDK/lib:/home/guang/work/Pandora/PandoraMonitoring/lib:/home/guang/Downloads/root-6.14.02/builddir/lib:/home/guang/work/Pandora/ExampleContent/build/lib:"
         NEW_RPATH "/home/guang/work/Pandora/ExampleContent/lib:/home/guang/work/Pandora/PandoraSDK/lib:/home/guang/work/Pandora/PandoraMonitoring/lib:/home/guang/Downloads/root-6.14.02/builddir/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/PandoraExample")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/guang/work/Pandora/ExampleContent/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
