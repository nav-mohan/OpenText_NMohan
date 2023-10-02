// some helper functions

#include <iostream>
#include <filesystem>

namespace Helpers
{

// do some basic validation on the input file to reduce the chances of throwing an exception later on
const bool FileValidate(const char *filepath)
{
    const std::filesystem::path  fp(filepath);
    if(!std::filesystem::exists(fp))
    {
        fprintf(stderr,"%s does not exist\n",filepath);
        return false;
    }
    
    const uint filesize = std::filesystem::file_size(fp);
    if(!filesize)
    {
        fprintf(stderr,"%s is empty\n",filepath);
        return false;
    }

    const std::filesystem::file_status filestatus = std::filesystem::status(fp);
    if(!std::filesystem::is_regular_file(filestatus))
    {
        fprintf(stderr,"%s is not a regular file\n",filepath);
        return false;
    }
    return true;
}

const void PrintUsage(const char *execname)
{
    fprintf(stderr,"USAGE:   %s <INPUT_XML_FILE> <OUTPUT_HTML_FILE>\n",execname);
    fprintf(stderr,"EXAMPLE: %s ../archive/cd_catalog.xml ../archive/index.html\n",execname);
}

};
