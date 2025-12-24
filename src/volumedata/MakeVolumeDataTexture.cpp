#include <volumedata/MakeVolumeDataTexture.h>
#include <volumedata/VolumeData.h>

#include <glad/glad.h>

namespace Factory
{
    Texture MakeVolumeDataTexture(TextureId textureId, unsigned int textureUnit, const VolumeData::VolumeData& volumeData)
    {
        const auto& metadata = volumeData.GetMetadata();
        GLenum internalFormat;
        GLenum format;
        GLenum type;

        switch (metadata.GetBitsPerComponent())
        {
            case 8:
                type = GL_UNSIGNED_BYTE;
                switch (metadata.GetComponents())
                {
                    case 1:
                        internalFormat = GL_R8;
                        format = GL_RED;
                        break;
                    case 2:
                        internalFormat = GL_RG8;
                        format = GL_RG;
                        break;
                    case 3:
                        internalFormat = GL_RGB8;
                        format = GL_RGB;
                        break;
                    default:
                        internalFormat = GL_RGBA8;
                        format = GL_RGBA;
                        break;
                }
                break;
            case 16:
                type = GL_UNSIGNED_SHORT;
                switch (metadata.GetComponents())
                {
                    case 1:
                        internalFormat = GL_R16;
                        format = GL_RED;
                        break;
                    case 2:
                        internalFormat = GL_RG16;
                        format = GL_RG;
                        break;
                    case 3:
                        internalFormat = GL_RGB16;
                        format = GL_RGB;
                        break;
                    default:
                        internalFormat = GL_RGBA16;
                        format = GL_RGBA;
                        break;
                }
                break;
            default:
                type = GL_UNSIGNED_BYTE;
                internalFormat = GL_R8;
                format = GL_RED;
                break;
        }

        return Texture {
            textureId,
            textureUnit,
            metadata.GetWidth(),
            metadata.GetHeight(),
            metadata.GetDepth(),
            internalFormat,
            format,
            type,
            GL_LINEAR,
            GL_CLAMP_TO_EDGE,
            volumeData.GetDataPtr()
        };
    }
}
