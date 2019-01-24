add_library(mylibs wknn.cpp datasetPrepare.cpp
        testdataPrepare.cpp estimatePosition.cpp
        knn.cpp)

target_link_libraries(mylibs ${THIRD_PARTY_LIBS})

if(OpenCV_FOUND)
    message("OpenCV is found, visualizing will be enable")
    add_executable(visualizing visualizing.cpp)
    target_link_libraries(visualizing mylibs ${THIRD_PARTY_LIBS})
endif()