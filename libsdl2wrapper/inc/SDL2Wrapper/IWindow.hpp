#pragma once
#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "CUL/Path.hpp"
#include "CUL/CUL.hpp"
#include "CUL/Math/XYPosition.hpp"
#include "CUL/Math/Size.hpp"
#include "SDL2Wrapper/IObject.hpp"
#include <string>
#include <memory>
namespace SDL2W
{
	class SDL2WrapperAPI IWindow
	{
	public:
		IWindow(
			const CUL::Position2DI& pos,
			const CUL::Size<unsigned>& size,
			const std::string& name );
		IWindow( const IWindow& wind );
		IWindow() = delete;

		virtual std::shared_ptr<IObject> createObject(
			const CUL::FS::Path& path,
			const IObject::Type type = IObject::Type::SPRITE )const = 0;

		virtual void renderNext() = 0;
		virtual void clear() = 0;

		IWindow& operator=( const IWindow& window );

		const CUL::Position2DI& getPos()const;
		void setPos( const CUL::Position2DI& pos );

		const CUL::Size<unsigned>& getSize()const;
		void setSize( const CUL::Size<unsigned>& size );

		const std::string& getName()const;
		void setName( const std::string& name );

		virtual void refreshScreen() = 0;
		virtual void renderAllObjects() = 0;

		virtual ~IWindow();
	protected:
	private:
		CUL::Position2DI position;
		CUL::Size<unsigned> m_size;
		std::string name;
	};
}