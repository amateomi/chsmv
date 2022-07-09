set(HEADERS
        square.h move.h piece.h board.h)
set(SOURCES
        chsmv.cc square.cc move.cc piece.cc board.cc)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
