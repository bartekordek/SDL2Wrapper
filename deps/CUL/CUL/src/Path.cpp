#include "CUL/Path.hpp"

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include <codecvt>

using namespace CUL;
using namespace FS;

std::string ws2s( const std::wstring& wstr );

#ifdef _WIN32
std::string Path::directorySeparator = std::string( "\\" );
#else
std::string Path::directorySeparator = std::string( "/" );
#endif
std::string Path::extensionSeparator = std::string( "." );

const std::string& Path::getDirSeparator()
{
	return extensionSeparator;
}

Path::Path()
{
	
}

Path::Path( const Path& path ): 
	fullPath( path.fullPath ),
	extension( path.extension ),
	baseName( path.baseName ),
	dir( path.dir )
{
}

Path::Path( const std::string& path ): fullPath(path)
{
	preparePaths();
}

Path::~Path()
{
	
}

Path& Path::operator=( const std::string& path )
{
	if( this->fullPath != path )
	{
		this->fullPath = path;
		preparePaths();
	}
	return *this;
}

const std::string& Path::getPath()const
{
	return this->fullPath;
}

const std::string& Path::getExtension()const
{
	return this->extension;
}

const std::string& Path::getBaseName()const
{
	return this->baseName;
}

const std::string& Path::getDir()const
{
	return this->dir;
}

void Path::preparePaths()
{
	boost::filesystem::path bPath( this->fullPath );
	this->baseName = ws2s( bPath.stem().c_str() );
	this->extension = ws2s( bPath.extension().c_str() );
	this->dir = ws2s( bPath.parent_path().c_str() );
}

std::string ws2s( const std::wstring& wstr )
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes( wstr );
}

const bool Path::exists() const
{
	const bool result = boost::filesystem::is_regular_file( this->fullPath );
	return result;
}

Path operator+( const Path& l, const std::string& r )
{
	Path result( l.getPath() + r );
	return result;
}

Path operator+( const Path& l, const Path& r )
{
	Path result( l.getPath() + r.getPath() );
	return result;
}