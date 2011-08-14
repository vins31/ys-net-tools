cmake_minimum_required(VERSION 2.6)
		
#Configuration du projet
project(ys-sndmsg)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})

include_directories(include ../../ys_proto/include)

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
	ys-sndmsg
	${source_files}
)

if (FORCE_CPU STREQUAL "32bits")
    add_definitions(                        -m32)
    set(CMAKE_EXE_LINKER_FLAGS                "${CMAKE_EXE_LINKER_FLAGS} -m32")
    set(CMAKE_SHARED_LIBRARY_C_FLAGS        "${CMAKE_SHARED_LIBRARY_C_FLAGS} -m32")
    set(CMAKE_SHARED_LIBRARY_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CXX_FLAGS} -m32")

    target_link_libraries(ys-sndmsg _ys_proto32)
    set_target_properties(ys-sndmsg PROPERTIES OUTPUT_NAME "ys-sndmsg32")
else (FORCE_CPU STREQUAL "32bits")
    target_link_libraries(ys-sndmsg _ys_proto)
endif (FORCE_CPU STREQUAL "32bits") 

