project(Bindings.Sofa.Tests)

####################################################################################################
### Module dependencies
####################################################################################################
if (NOT TARGET SofaPython3)
  find_package(SofaPython3 QUIET)
  if(NOT SofaPython3_FOUND)
    message("-- PythonModule_Sofa_test is disabled because 'SofaPython3' is missing or not activated.")
    return()
  endif()
endif()

message("-- PythonModule_Sofa_test is enabled.")

set(CMAKE_CXX_STANDARD 17)
set(PYBIND11_CPP_STANDARD -std=c++17)

####################################################################################################
### Building
####################################################################################################
set(HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Binding_BaseObject_MockComponent.h
)

set(SOURCE_FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/PythonModule_Sofa_test.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/Binding_BaseObject_MockComponent.cpp
)

set(PYTHON_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Components/Components.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/BaseData.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Base.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/BaseObject.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Controller.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/ForceField.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/DataEngine.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/MyRestShapeForceField.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/PythonRestShapeForceField.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/BaseLink.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Helper/Message.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Types/RGBAColor.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Types/Vec3.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Types/BoundingBox.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Simulation/Node.py
    ${CMAKE_CURRENT_SOURCE_DIR}/bench_datacontainer.py
    ${CMAKE_CURRENT_SOURCE_DIR}/bench_node.py
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmark.py
    ${CMAKE_CURRENT_SOURCE_DIR}/dataaccess.py
  )

find_package(SofaGTestMain REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${PYTHON_FILES})
target_link_libraries(${PROJECT_NAME} SofaGTestMain SofaPython3::Plugin SofaPython3::Bindings.Sofa SofaPython3::Bindings.SofaTypes SofaPython3::Bindings.SofaRuntime)
target_compile_definitions(${PROJECT_NAME} PRIVATE "PYTHON_TESTFILES_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/\"")

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

