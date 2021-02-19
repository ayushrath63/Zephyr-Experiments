# nanopb
add_custom_target(serial_pb make WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/serial_pb)
target_sources(app PRIVATE nanopb/pb_common.c)
target_sources(app PRIVATE nanopb/pb_decode.c)
target_sources(app PRIVATE nanopb/pb_encode.c)
target_sources(app PRIVATE src/serial_pb/simple.pb.c)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/serial_pb/)
