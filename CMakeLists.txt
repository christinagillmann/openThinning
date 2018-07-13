cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0020)
	cmake_policy(SET CMP0020 NEW)
endif()

project(OpenThinning)

find_package(VTK REQUIRED)

set(CPP_FILES Source/main.cpp Source/Volume.cpp)
file(GLOB   H_FILES Source/*.h  )

include(${VTK_USE_FILE})

add_executable(OpenThinning ${CPP_FILES} ${H_FILES})

target_link_libraries(OpenThinning ${VTK_LIBRARIES})

option(WITH_ITK "Build ITK example" OFF)
if(WITH_ITK)
	find_package(ITK REQUIRED)
	include(${ITK_USE_FILE})

	add_executable(OpenThinning_ITK Source/main_itk.cpp)
	target_link_libraries(OpenThinning_ITK ${ITK_LIBRARIES})
endif()
