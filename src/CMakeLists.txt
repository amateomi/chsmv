include_directories(pieces)

file(GLOB HEADERS *.h pieces/*.h)
file(GLOB SOURCES *.cc pieces/*.cc)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
