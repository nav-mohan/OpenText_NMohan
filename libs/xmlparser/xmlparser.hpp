#if !defined(XMLPARSER_HPP)
#define XMLPARSER_HPP

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

class XmlParser
{
private:
    boost::property_tree::ptree tree_;
    boost::property_tree::ptree::iterator it_;

public:
    XmlParser(){};
    ~XmlParser(){};
    void LoadXml(const char * input_xml_filename);
};

#endif // XMLPARSER_HPP