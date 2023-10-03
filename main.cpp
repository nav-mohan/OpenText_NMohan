#include <iostream>
#include <optional>
#include <vector>
#include <string>

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
    
    // Load the xml file
    XmlParser catalogparser;
    try
    {
        catalogparser.LoadXml(input_xml_filename);
    }
    catch(const std::exception& e)
    {
        fprintf(stderr, "Failed to load XML file %s\n",input_xml_filename);
        fprintf(stderr, "%s",e.what());
        exit(1);
    }

    bool validHead = catalogparser.GetRoot("CATALOG");
    if(!validHead)
    {
        fprintf(stderr, "Node <CATALOG> not found in %s\n",input_xml_filename);
        exit(1);
    }
    
    std::vector<std::string> column_headers{"TITLE","ARTIST","COMPANY","COUNTRY","PRICE","YEAR"};
    std::vector<std::string> row_values(6);

    auto catalogParserCallback = [&](boost::property_tree::ptree::const_iterator it) -> bool
    {
        if(it->first != "CD") return false; // NOT A <CD>

        for(int i = 0; i < column_headers.size(); i++)
        {
            auto opt_val = it->second.get_optional<std::string>(column_headers[i]);
            if(!opt_val.is_initialized()) return false; // missing column
            row_values[i] = std::move(opt_val.get());
        }
        return true;
    };
    catalogparser.IteratorCallback = std::move(catalogParserCallback);

}