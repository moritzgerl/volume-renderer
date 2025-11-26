#include <buffers/MakeFrameBuffers.h>
#include <buffers/FrameBufferId.h>
#include <storage/ElementStorage.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <config/Config.h>
#include <glad/glad.h>

namespace
{
    const FrameBuffer& GetFrameBuffer(const std::vector<FrameBuffer>& frameBuffers, FrameBufferId frameBufferId)
    {
        auto frameBufferIter = std::find_if(frameBuffers.cbegin(), frameBuffers.cend(),
            [frameBufferId](const FrameBuffer& frameBuffer)
        {
            return frameBuffer.GetId() == frameBufferId;
        }
        );
        return *frameBufferIter;
    }

    FrameBuffer& GetFrameBuffer(std::vector<FrameBuffer>& frameBuffers, FrameBufferId frameBufferId)
    {
        auto frameBufferIter = std::find_if(frameBuffers.begin(), frameBuffers.end(),
            [frameBufferId](const FrameBuffer& frameBuffer)
        {
            return frameBuffer.GetId() == frameBufferId;
        }
        );
        return *frameBufferIter;
    }
}

namespace Factory
{
    std::vector<FrameBuffer> MakeFrameBuffers(const TextureStorage& textureStorage)
    {
        std::vector<FrameBuffer> frameBuffers =
        {
            { FrameBufferId::Default },
            { FrameBufferId::SsaoInput },
            { FrameBufferId::Ssao },
            { FrameBufferId::SsaoBlur }
        };

        auto& ssaoInputFrameBuffer = GetFrameBuffer(frameBuffers, FrameBufferId::SsaoInput);
        ssaoInputFrameBuffer.Bind();
        ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT0, textureStorage.GetElement(TextureId::SsaoPosition));
        ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT1, textureStorage.GetElement(TextureId::SsaoNormal));
        ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT2, textureStorage.GetElement(TextureId::SsaoAlbedo));
        ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT3, textureStorage.GetElement(TextureId::SsaoPointLightsContribution));
        unsigned int attachments[5] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4 };
        glDrawBuffers(5, attachments);
        ssaoInputFrameBuffer.AttachRenderBuffer(GL_DEPTH_ATTACHMENT, GL_DEPTH_COMPONENT, Config::windowWidth, Config::windowHeight);
        ssaoInputFrameBuffer.Check();
        ssaoInputFrameBuffer.Unbind();

        const auto& ssaoFrameBuffer = GetFrameBuffer(frameBuffers, FrameBufferId::Ssao);
        ssaoFrameBuffer.Bind();
        ssaoFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT0, textureStorage.GetElement(TextureId::Ssao));
        ssaoFrameBuffer.Check();
        ssaoFrameBuffer.Unbind();

        const auto& ssaoBlurFrameBuffer = GetFrameBuffer(frameBuffers, FrameBufferId::SsaoBlur);
        ssaoBlurFrameBuffer.Bind();
        ssaoBlurFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT0, textureStorage.GetElement(TextureId::SsaoBlur));
        ssaoBlurFrameBuffer.Check();
        ssaoBlurFrameBuffer.Unbind();

        return frameBuffers;
    }
}
