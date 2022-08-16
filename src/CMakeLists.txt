include_directories(pieces)

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cc)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
