message("BUILDING XmlParser")

add_library(xmlparser xmlparser.cpp)
find_package(Boost REQUIRED COMPONENTS headers)
target_link_libraries(
    xmlparser
    Boost::headers
)