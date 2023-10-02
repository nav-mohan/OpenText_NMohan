#include "xmlparser.hpp"

void XmlParser::LoadXml(const char * input_xml_filename)
{
    boost::property_tree::read_xml(input_xml_filename,tree_);
}

bool XmlParser::SetHead(const char *head) noexcept
{
    boost::optional<boost::property_tree::ptree&> treehead = tree_.get_child_optional(head);
    
    if(!treehead.is_initialized()) return false;

    it_ = treehead->begin();
    end_ = treehead->end();
    return true;
}

void XmlParser::GetAll()
{
    while(it_ != end_)
    {
        IteratorCallback(it_);
        it_++;
    }
    return;
}