#pragma once
#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "CUL/Math/Vector3D.hpp"
#include "CUL/Path.hpp"
namespace SDL2W
{
    using Vector3Du = CUL::Math::Vector3Du;
    using Path = CUL::FS::Path;
    class SDL2WrapperAPI ITexture
    {
    public:
        ITexture();
        virtual ~ITexture();
        virtual const Vector3Du& getSize()const = 0;
        virtual const Path& getPath()const = 0;
    protected:
    private:
    };
}