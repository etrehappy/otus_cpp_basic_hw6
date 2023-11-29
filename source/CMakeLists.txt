cmake_minimum_required(VERSION 3.26)

project(containers)

add_executable(containers 
	main.cpp		main.h
	u_vector.ipp		u_vector.h
	u_list.cpp		u_list.h
	u_forward_list.cpp	u_forward_list.h
)

set_target_properties(containers PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)