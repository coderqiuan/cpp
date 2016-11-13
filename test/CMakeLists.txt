include_directories(
./
../
)

link_directories(

)

set(SRC_LIST
./main.cpp
)

add_executable(qiuan_test ${SRC_LIST})

if(APPLE)
target_link_libraries(qiuan_test qiuan_base qiuan_log)
elseif(LINUX)
target_link_libraries(qiuan_test qiuan_base qiuan_log)
endif()
