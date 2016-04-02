#
# Copyright (C) 2015, Yeolar
#

set(FOLLY_IO_SRCS
    FsUtil.cpp
)
add_library(folly_io OBJECT ${FOLLY_IO_SRCS})


install(FILES
    FsUtil.h
    DESTINATION include/folly/io
)
