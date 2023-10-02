#include <iostream>
#include "helpers.hpp"

// usage: main input.xml output.html
int main(int argc, char *argv[])
{
    if(argc < 3) 
    {
        Helpers::PrintUsage(argv[0]);
        exit(1);
    }
    const char *input_xml_filename = argv[1];
    const char *output_html_filename = argv[2];
    
    bool file_is_valid = Helpers::FileValidate(input_xml_filename);
    if(!file_is_valid) exit(1);


}