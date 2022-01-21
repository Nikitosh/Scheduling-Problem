# Install script for directory: /Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX/headers" TYPE FILE FILES "/Users/nikitapodguzov/Programming/Contests/BiaTech/build/OpenXLSX/OpenXLSX/OpenXLSX-Exports.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX/headers" TYPE FILE FILES
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLCell.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLCellIterator.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLCellRange.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLCellReference.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLCellValue.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLColor.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLColumn.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLCommandQuery.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLConstants.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLContentTypes.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLDateTime.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLDocument.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLException.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLFormula.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLIterator.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLProperties.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLRelationships.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLRow.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLRowData.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLSharedStrings.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLSheet.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLWorkbook.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLXmlData.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLXmlFile.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLXmlParser.hpp"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/headers/XLZipArchive.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenXLSX" TYPE FILE FILES "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/OpenXLSX.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/nikitapodguzov/Programming/Contests/BiaTech/build/output/libOpenXLSX.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenXLSX.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenXLSX.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenXLSX.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/OpenXLSX/OpenXLSX/OpenXLSXConfig.cmake"
    "/Users/nikitapodguzov/Programming/Contests/BiaTech/build/OpenXLSX/OpenXLSX/OpenXLSX/OpenXLSXConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake"
         "/Users/nikitapodguzov/Programming/Contests/BiaTech/build/OpenXLSX/OpenXLSX/CMakeFiles/Export/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES "/Users/nikitapodguzov/Programming/Contests/BiaTech/build/OpenXLSX/OpenXLSX/CMakeFiles/Export/lib/cmake/OpenXLSX/OpenXLSXTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenXLSX" TYPE FILE FILES "/Users/nikitapodguzov/Programming/Contests/BiaTech/build/OpenXLSX/OpenXLSX/CMakeFiles/Export/lib/cmake/OpenXLSX/OpenXLSXTargets-noconfig.cmake")
  endif()
endif()

