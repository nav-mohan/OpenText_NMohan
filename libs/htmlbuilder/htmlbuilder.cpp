#include "htmlbuilder.hpp"

void HtmlBuilder::SetRoot(const char *tag)
{
    boost::property_tree::ptree root;
    tree_.put_child(tag,root);
    it_ = tree_.get_child("").begin(); // iterator is at root
}

// this appends a child to the current iterator
void HtmlBuilder::Push(const char *tag, boost::property_tree::ptree node)
{
    it_->second.push_back(std::make_pair(tag,node));
}

// this appends a child and moves the iterator down to the child
void HtmlBuilder::PushForward(const char *tag)
{
    const boost::property_tree::ptree::iterator x = it_;
    history_.push(x);
    boost::property_tree::ptree newnode;
    it_ = it_->second.push_back(std::make_pair(tag,newnode));
}

void HtmlBuilder::PushLeaf(const char *tag, const char *value)
{
    boost::property_tree::ptree leafnode;
    leafnode.put_value(value);
    Push(tag,leafnode);
}

void HtmlBuilder::GoBack()
{
    if(history_.empty()) return;
    auto parent = history_.top();
    history_.pop();
    it_ = parent;
}

void HtmlBuilder::WriteHtml(const char *output_filename)
{
    boost::property_tree::write_xml(output_filename,tree_);
}