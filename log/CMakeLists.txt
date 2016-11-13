include_directories(
./
../
)

link_directories(

)


set(SRC_LIST
./logfile.h
./logfile.cpp
)

add_library(qiuan_log ${SRC_LIST})

target_link_libraries (qiuan_log)

