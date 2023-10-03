# CD Catalog XML to HTML 

#### Libraries used
* boost::property_tree

#### Building and Running
* `git clone https://github.com/nav-mohan/OpenText_NMohan`
* `cd OpenText_NMohan`
* `mkdir build && cd build`
* `cmake ..`
* `make`
* `./main ../archive/cd_catalog.xml index.html`


#### Notes
* There are two basic classes `XmlParser` and `HtmlBuilder`. 
* `XmlParser::LoadXml` is a throwing function. client code must catch it.
* `XmlParser::GetRoot` is a no except function. It returns a `bool` that client code must check before proceeding. 
* `XmlParser::IteratorCallback` is a `std::functional`. The client code sets this with a `lambda` that is tailored for a specific input xml. The `functional` returns a `bool` to indicate whether a row was valid.
* `XmlParser::GetAll()` and `XmlParser::GetNext()` call `IteratorCallback` after each iteration. In this specific client code i.e `main.cpp` the `IteratorCallback` is tailored for error-checking the input xml line by line. To use the `GetAll()` we must store all parsed values in a 2D `matrix`.
* `XmlParser::IsEnd` checks if we've reached the end of the current level tree.
* `HtmlBuilder::SetRoot` creates a new root node and sets the `iterator` to the root.
* `HtmlBuilder::Push` is used to push a child node at the `iterator`'s position.
* `HtmlBuilder::PushForward` is used to push a child node at the `iterator`'s position and progress the `iterator` down to the child. To return to the parent use `HtmlBuilder::GoBack`.
* `HtmlBuilder::history_` is a `std::stack<ptree::iterator>` for storing iterator position of parent when executing `HtmlBuilder::PushForward`.
* `HtmlBuilder::PushLeaf` pushes a leaf node at the `iterator`'s position.
* A `std::vector` of length 6 is used by the client code as a temporary storge of values that were parsed by `XmlParser`. This allows the client code to perform error checks and drop any invalid rows before the `HtmlBuilder` appends nodes. 

#### Tests
* The code was tested on 4 `XML` files which are included in the `archive/` folder
* `cd_catalog.xml` is a valid `XML` and the code parses it entirely.
* `error1.xml` is a malformed `XML`. The client code exits early in this case.
* `error2.xml` has a valid `XML` schema but one of it's rows is not indexed by a `<CD>` tag. This row is dropped silently by the client code.
* `error3.xml` has a valid `XML` schema but one of the rows has a different column `<RELEASE_YEAR>` instead of `<YEAR>`. This row is dropped silently by the client code. 

#### Alternative ideas
* When building the output `HTML` table, every node in the tree is a `boost::property_tree::ptree`. Extending upon this base node class to make a doubly-linked node is an alternative to using a `std::stack<ptree::iterator>` but for trees that are not deeply nested, a tree full of double-linked nodes would consume more memory than using a `std::stack`. The drawback to my approach of using a `std::stack` is that the client code must remember to call `HtmlBuilder::GoBack` correctly. 
* For a simple tree like this, it is easier and more performant to use `std::regex`. But it would be difficult to correctly handle a malformed `XML`.


#### Further
* we could overload `PushForward(const char*, ptree)`
* we could overload `Push(const char*)`


#### References
* https://theboostcpplibraries.com/boost.propertytree
* https://www.boost.org/doc/libs/1_83_0/doc/html/property_tree/accessing.html
* https://stackoverflow.com/questions/45366768/getting-boost-property-tree-parent-node
* https://en.cppreference.com/w/cpp/filesystem/file_status
* https://en.cppreference.com/w/cpp/filesystem/exists
* https://en.cppreference.com/w/cpp/container/stack

