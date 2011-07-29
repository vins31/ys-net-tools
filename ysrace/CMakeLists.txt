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
    #   ../../ys_proto/src/*
    #../../ys_proto/include/*
)

#Déclaration de l'exécutable
add_executable(
	ysrace
	${source_files}
)

target_link_libraries(
        ysrace
        _ys_proto
        _checkpoint_check
        pthread
)
