#include "xmlparser.hpp"

void XmlParser::LoadXml(const char * input_xml_filename)
{
    boost::property_tree::read_xml(input_xml_filename,tree_);
}