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

target_link_libraries(qiuan_test qiuan_base qiuan_log)

