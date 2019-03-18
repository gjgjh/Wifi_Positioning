add_library(wifiposition utils.cpp strategy.cpp wifiposition.cpp)
target_link_libraries(wifiposition ${THIRD_PARTY_LIBS})

if(OpenCV_FOUND)
    message("OpenCV is found, visualizing will be enable")
    add_library(visualizing visualizing.cpp)
    target_link_libraries(visualizing wifiposition ${THIRD_PARTY_LIBS})
endif()