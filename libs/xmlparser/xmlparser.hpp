#if !defined(XMLPARSER_HPP)
#define XMLPARSER_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <functional>

class XmlParser
{
private:
    boost::property_tree::ptree tree_;
    boost::property_tree::ptree::const_iterator it_;
    boost::property_tree::ptree::const_iterator end_;

public:
    XmlParser(){};
    ~XmlParser(){};
    void LoadXml(const char * input_xml_filename);
    bool GetRoot(const char *head) noexcept;
    std::function<bool(boost::property_tree::ptree::const_iterator it)>IteratorCallback;
    void GetAll();
    bool IsEnd() const;
    bool GetNext();

};

#endif // XMLPARSER_HPP