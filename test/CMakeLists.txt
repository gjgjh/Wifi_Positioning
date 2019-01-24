add_executable(KNN_example KNN_example.cpp)
target_link_libraries(KNN_example ${THIRD_PARTY_LIBS})

add_executable(wifiPositioning wifiPositioning.cpp)
target_link_libraries(wifiPositioning ${THIRD_PARTY_LIBS} mylibs)