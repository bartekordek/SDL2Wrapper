#pragma once
#include "CUL/IFile.hpp"
#include "CUL/Path.hpp"
#include "CUL/ListVector.hpp"
#include <vector>
#include <memory>
namespace CUL
{
	namespace FS
	{
		class FileRegularImpl: public IFile
		{
		public:
			FileRegularImpl();
			FileRegularImpl( const FileRegularImpl& file );
			FileRegularImpl( const std::string& path );
			virtual ~FileRegularImpl();

			Path* getPath() override;

			const bool exists()const override;
			const bool isBinary()const override;

			void reload() override;
			void load() override;
			void unload() override;

			const IIterator<std::string>* begin()const override;
			const IIterator<std::string>* end()const override;

			const IIterator<std::string>* firstLine()const override;
			const IIterator<std::string>* lastLine()const override;

			IIterator<std::string>* getIt() override;
		protected:
		private:
			Path path;
			std::unique_ptr < IList<std::string> > rows;
		};
	}
}