cmake_minimum_required(VERSION 2.6)
		
#Configuration du projet
project(ysrace)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})


find_package (Threads)

include_directories(include ../../ys_proto/include ../../checkpoint_check/include)

link_directories(lib/${CMAKE_BUILD_TYPE})

#Génération de la liste des fichiers sources
file(
	GLOB_RECURSE
	source_files
	src/*
	include/*
)

#Déclaration de l'exécutable
add_executable(
	ysrace
	${source_files}
)


if (FORCE_CPU STREQUAL "32bits")
    add_definitions(                        -m32)
    set(CMAKE_EXE_LINKER_FLAGS                "${CMAKE_EXE_LINKER_FLAGS} -m32")
    set(CMAKE_SHARED_LIBRARY_C_FLAGS        "${CMAKE_SHARED_LIBRARY_C_FLAGS} -m32")
    set(CMAKE_SHARED_LIBRARY_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CXX_FLAGS} -m32")

    target_link_libraries(ysrace _ys_proto32 _checkpoint_check32 pthread)
    set_target_properties(ysrace PROPERTIES OUTPUT_NAME "ysrace32")
else (FORCE_CPU STREQUAL "32bits")
    target_link_libraries(ysrace _ys_proto _checkpoint_check pthread) 
endif (FORCE_CPU STREQUAL "32bits") 

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
   message("Doing the Windows version!") 
   include_directories("/usr/i486-mingw32/include")
   set (LIBS ${LIBS}pthread)
   #target_link_libraries(ysrace pthread)
endif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
