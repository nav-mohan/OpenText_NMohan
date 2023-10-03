# CD Catalog XML to HTML 

#### Libraries used
* boost::property_tree

#### References
* https://theboostcpplibraries.com/boost.propertytree
* https://www.boost.org/doc/libs/1_83_0/doc/html/property_tree/accessing.html
* https://stackoverflow.com/questions/45366768/getting-boost-property-tree-parent-node
* https://en.cppreference.com/w/cpp/filesystem/file_status
* https://en.cppreference.com/w/cpp/filesystem/exists
* https://en.cppreference.com/w/cpp/container/stack



#### Notes
* There are two basic classes `XmlParser` and `HtmlBuilder`. 
* `XmlParser::LoadXml` is a throwing function. client code must catch it.
* `XmlParser::GetRoot` is a no except function. It returns a `bool` that client code must check before proceeding. 
* `XmlParser::IteratorCallback` is a `std::functional` that client code can set for a specific input xml.
* `XmlParser::GetAll()` and `XmlParser::GetNext()` call `IteratorCallback` after each iteration. 
* `XmlParser::IsEnd` checks if we've reached the end of the current level tree.
* `HtmlBuilder::SetRoot` creates a new root node and sets the `iterator` to the root.
* `HtmlBuilder::Push` is used to push a child node at the `iterator`'s position.
* `HtmlBuilder::PushForward` is used to push a child node at the `iterator`'s position and progress the `iterator` down to the child. To return to the parent use `HtmlBuilder::GoBack`.
* `HtmlBuilder::history_` is a `std::stack<ptree::iterator>` for storing iterator position of parent when executing `HtmlBuilder::PushForward`.
* `HtmlBuilder::PushLeaf` pushes a leaf node at the `iterator`'s position.
* A `std::vector` of length 6 is used by the client code as a temporary storge of values that were parsed by `XmlParser`. This allows the client code to perform error checks and drop any invalid rows before the `HtmlBuilder` appends nodes. 


#### Alternative ideas
* Every node in the tree is a `boost::property_tree::ptree`. Extending upon this base node class to make a doubly-linked node is an alternative to using a `std::stack<ptree::iterator>` but for trees that are not deeply nested, a tree full of double-linked nodes would consume more memory than using a `std::stack`.  
* For a simple tree like this, it is easier and more performant to use `std::regex`. But it would be difficult to correctly handle a malformed `XML`.



#### Further
* we could overload `PushForward(const char*, ptree)`
* we could overload `Push(const char*)`