#include <iostream>
#include "helpers.hpp"
#include "xmlparser.hpp"

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

    XmlParser xmlparser;
    try
    {
        xmlparser.LoadXml(input_xml_filename);
    }
    catch(const std::exception& e)
    {
        fprintf(stderr, "Failed to load XML file %s\n",input_xml_filename);
        fprintf(stderr, "%s",e.what());
        exit(1);
    }

    bool validHead = xmlparser.SetHead("CATALOG");
    if(!validHead)
    {
        fprintf(stderr, "Node <CATALOG> not found in %s\n",input_xml_filename);
        exit(1);
    }
}