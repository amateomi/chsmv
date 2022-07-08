set(HEADERS
        square.h move.h)
set(SOURCES
        chsmv.cc square.cc move.cc)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
