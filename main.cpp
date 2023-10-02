#include <iostream>
#include "helpers.hpp"
#include "xmlparser.hpp"
#include <optional>

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

    std::string title, artist, company, country, price, year;
    std::optional<std::string> opt_title, opt_artist, opt_company, opt_country, opt_price, opt_year;
    auto iteratorCallback = [&](boost::property_tree::ptree::const_iterator it){
        if((*it).first == "CD")
        {
            auto opt_title = (*it).second.get_optional<std::string>("TITLE");
            auto opt_artist = (*it).second.get_optional<std::string>("ARTIST");
            auto opt_company = (*it).second.get_optional<std::string>("COMPANY");
            auto opt_country = (*it).second.get_optional<std::string>("COUNTRY");
            auto opt_price = (*it).second.get_optional<std::string>("PRICE");
            auto opt_year = (*it).second.get_optional<std::string>("YEAR");
            if( 
                opt_title.is_initialized() && opt_artist.is_initialized() && 
                opt_company.is_initialized() && opt_country.is_initialized() && 
                opt_price.is_initialized() && opt_year.is_initialized()
            )
            {
                title = opt_title.get();
                artist = opt_artist.get();
                company = opt_company.get();
                country = opt_country.get();
                price = opt_price.get();
                year = opt_year.get();
                fprintf(stdout, "%s %s %s %s %s %s\n",title.c_str(),artist.c_str(),company.c_str(),country.c_str(),price.c_str(),year.c_str());
            }
            else 
            {
                std::cerr << "***** MISSING COLUMN ***** " << std::endl;
            }
        }
        else 
        {
            std::cerr << "***** NOT A CD *****" << std::endl;
        }
    };
    xmlparser.IteratorCallback = std::move(iteratorCallback);

    // xmlparser.GetAll();
    while(!xmlparser.IsEnd())
        xmlparser.GetNext();
}