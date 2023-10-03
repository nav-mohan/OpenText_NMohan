#if !defined(HTMLBUILDER_HPP)
#define HTMLBUILDER_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <stack>

class HtmlBuilder
{
private:
    boost::property_tree::ptree tree_;
    boost::property_tree::ptree::iterator it_;
    std::stack<boost::property_tree::ptree::iterator> history_;

public:
    HtmlBuilder(){}
    ~HtmlBuilder(){}
    void SetRoot(const char *tag);
    void Push(const char *tag, boost::property_tree::ptree node);
    void PushForward(const char *tag);
    void PushLeaf(const char *tag, const char *value);
    void GoBack();
    void WriteHtml(const char *output_filename);

};

#endif // HTMLBUILDER_HPP
