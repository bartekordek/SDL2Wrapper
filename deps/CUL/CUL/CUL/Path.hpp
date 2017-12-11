#pragma once
#include <CUL/CUL.hpp>
#include <string>
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4251)
#endif
namespace CUL
{
	namespace FS
	{
		class CULLib_API Path
		{
		public:
			Path();
			Path( const Path& path );
			Path( const std::string& path );
			virtual ~Path();

			Path& operator=( const std::string& path );

			const std::string& getPath()const;
			const std::string& getExtension()const;
			const std::string& getBaseName()const;
			const std::string& getDir()const;

			const bool exists()const;

			static const std::string& getDirSeparator();
		protected:
		private:
			void preparePaths();
			std::string fullPath;
			std::string extension;
			std::string baseName;
			std::string dir;

			static std::string directorySeparator;
			static std::string extensionSeparator;
		};

		Path operator+( const Path& l, const std::string& r );
		Path operator+( const Path& l, const Path& r );
	}
}
#if _MSC_VER
#pragma warning( push )
#endif