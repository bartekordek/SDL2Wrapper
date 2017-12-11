#pragma once
#include "CUL.hpp"
#include "IIterator.hpp"
#include "Path.hpp"

#include <memory>

namespace CUL
{
	namespace FS
	{
		class CULLib_API IFile
		{
		public:
			IFile();
			IFile( const std::string& fPath );
			virtual ~IFile();

			static std::shared_ptr<IFile> createFile( const Path& path );

			virtual Path* getPath() = 0;

			virtual const bool exists()const = 0;
			virtual const bool isBinary()const = 0;

			virtual void load() = 0;
			virtual void unload() = 0;
			virtual void reload() = 0;

			virtual const IIterator<std::string>* begin()const = 0;
			virtual const IIterator<std::string>* end()const = 0;

			virtual const IIterator<std::string>* firstLine()const = 0;
			virtual const IIterator<std::string>* lastLine()const = 0;

			virtual IIterator<std::string>* getIt() = 0;
		protected:
		private:
			IFile( const IFile& file ) = default;
		};
	}
}