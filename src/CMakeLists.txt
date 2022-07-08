set(HEADERS
        square.h)
set(SOURCES
        chsmv.cc square.cc)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
