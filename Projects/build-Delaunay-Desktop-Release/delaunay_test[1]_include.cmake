if(EXISTS "C:/Users/aless/Desktop/RepProgetto/Progetto_PCS_2023/Projects/build-Delaunay-Desktop-Release/delaunay_test[1]_tests.cmake")
  include("C:/Users/aless/Desktop/RepProgetto/Progetto_PCS_2023/Projects/build-Delaunay-Desktop-Release/delaunay_test[1]_tests.cmake")
else()
  add_test(delaunay_test_NOT_BUILT delaunay_test_NOT_BUILT)
endif()
