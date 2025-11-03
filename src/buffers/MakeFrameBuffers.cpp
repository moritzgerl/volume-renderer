#include <buffers/MakeFrameBuffers.h>
#include <buffers/FrameBufferId.h>
#include <storage/TextureStorage.h>
#include <textures/TextureId.h>
#include <config/Config.h>
#include <glad/glad.h>

namespace Factory
{
    std::vector<FrameBuffer> MakeFrameBuffers(const TextureStorage& textureStorage)
    {
        std::vector<FrameBuffer> frameBuffers;
        frameBuffers.reserve(4);

        FrameBuffer ssaoInputFrameBuffer(FrameBufferId::SsaoInput);
        ssaoInputFrameBuffer.Bind();
        ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT0, textureStorage.GetTexture(TextureId::SsaoPosition));
        ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT1, textureStorage.GetTexture(TextureId::SsaoLightSpacePosition));
        ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT2, textureStorage.GetTexture(TextureId::SsaoNormal));
        ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT3, textureStorage.GetTexture(TextureId::SsaoAlbedo));
        ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT4, textureStorage.GetTexture(TextureId::SsaoPointLightsContribution));
        ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT5, textureStorage.GetTexture(TextureId::SsaoStencil));
        unsigned int attachments[6] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5 };
        glDrawBuffers(6, attachments);
        ssaoInputFrameBuffer.AttachRenderBuffer(GL_DEPTH_ATTACHMENT, GL_DEPTH_COMPONENT, Config::windowWidth, Config::windowHeight);
        ssaoInputFrameBuffer.Check();
        ssaoInputFrameBuffer.Unbind();
        frameBuffers.push_back(std::move(ssaoInputFrameBuffer));
  
        FrameBuffer ssaoFrameBuffer(FrameBufferId::Ssao);
        ssaoFrameBuffer.Bind();
        ssaoFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT0, textureStorage.GetTexture(TextureId::Ssao));
        ssaoFrameBuffer.Check();
        ssaoFrameBuffer.Unbind();
        frameBuffers.push_back(std::move(ssaoFrameBuffer));

        FrameBuffer ssaoBlurFrameBuffer(FrameBufferId::SsaoBlur);
        ssaoBlurFrameBuffer.Bind();
        ssaoBlurFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT0, textureStorage.GetTexture(TextureId::SsaoBlur));
        ssaoBlurFrameBuffer.Check();
        ssaoBlurFrameBuffer.Unbind();
        frameBuffers.push_back(std::move(ssaoBlurFrameBuffer));

        FrameBuffer defaultFrameBuffer(FrameBufferId::Default);
        frameBuffers.push_back(std::move(defaultFrameBuffer));

        return frameBuffers;
    }
}
