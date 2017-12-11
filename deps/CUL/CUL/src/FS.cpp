#include "CUL/FS.hpp"
#include <boost/filesystem.hpp>
using namespace CUL;
using namespace FS;

FSApi::FSApi()
{
}


FSApi::~FSApi()
{
}

std::string FSApi::getCurrentDir()
{
    boost::filesystem::path full_path(boost::filesystem::current_path());
    return full_path.string();
}