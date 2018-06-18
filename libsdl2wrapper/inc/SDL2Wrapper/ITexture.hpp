#pragma once
#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "CUL/Math/Vector3D.hpp"
#include "CUL/Path.hpp"
namespace SDL2W
{
    using Vector3Dd = CUL::Math::Vector3Dd;
    using Path = CUL::FS::Path;
    //using WindowsList = std::map
    class SDL2WAPI ITexture
    {
    public:
        ITexture();
        virtual ~ITexture();
        virtual const Vector3Dd& getSize()const = 0;
        virtual const Path& getPath()const = 0;

    protected:
    private:
    };
}