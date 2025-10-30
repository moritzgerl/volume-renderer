#include <textures/TextureUnitMapping.h>

#include <glad/glad.h>

#include <map>

namespace Constants
{
    const std::map<GLenum, unsigned int> glEnumToUnsignedInt =
    {
        { GL_TEXTURE0, 0},
        { GL_TEXTURE1, 1},
        { GL_TEXTURE2, 2},
        { GL_TEXTURE3, 3},
        { GL_TEXTURE4, 4},
        { GL_TEXTURE5, 5},
        { GL_TEXTURE6, 6},
        { GL_TEXTURE7, 7},
        { GL_TEXTURE8, 8},
        { GL_TEXTURE9, 9},
        { GL_TEXTURE10, 10},
        { GL_TEXTURE11, 11},
        { GL_TEXTURE12, 12},
        { GL_TEXTURE13, 13},
        { GL_TEXTURE14, 14},
        { GL_TEXTURE15, 15},
    };
}

unsigned int TextureUnitMapping::GLenumToUnsignedInt(GLenum textureUnit)
{
    if (Constants::glEnumToUnsignedInt.contains(textureUnit))
    {
        return Constants::glEnumToUnsignedInt.at(textureUnit);
    }
    else
    {
        return 0;
    }
}
