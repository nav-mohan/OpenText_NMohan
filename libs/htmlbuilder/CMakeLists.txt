message("BUILDING HtmlBuilder")

add_library(htmlbuilder htmlbuilder.cpp)
find_package(Boost REQUIRED COMPONENTS headers)
target_link_libraries(
    htmlbuilder
    Boost::headers
)