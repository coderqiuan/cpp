include_directories(
./
)

link_directories(

)

set(SRC_LIST
./baseutil.h
./singleton.h

./fileutil.h
./fileutil.cpp

./timestamp.h
./timestamp.cpp
)

add_library(qiuan_base ${SRC_LIST})

target_link_libraries (qiuan_base)

