#include <transferfunction/TransferFunctionTextureUpdater.h>

#include <gui/GuiUpdateFlags.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <transferfunction/TransferFunction.h>
#include <transferfunction/TransferFunctionControlPoint.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <algorithm>
#include <execution>
#include <ranges>
#include <span>


namespace
{
    constexpr std::array<size_t, TransferFunctionConstants::textureSize> MakeTextureIndices()
    {
        std::array<size_t, TransferFunctionConstants::textureSize> indices{};
        std::ranges::copy(std::views::iota(size_t{ 0 }, TransferFunctionConstants::textureSize), indices.begin());
        return indices;
    }

    constexpr auto textureIndices = MakeTextureIndices();

    unsigned char FloatToUnsignedByte(float value)
    {
        return static_cast<unsigned char>(glm::clamp(value, 0.0f, 1.0f) * 255.0f);
    }
}

TransferFunctionTextureUpdater::TransferFunctionTextureUpdater(
    GuiUpdateFlags& guiUpdateFlags,
    TransferFunction& transferFunction,
    Texture& transferFunctionTexture
)
    : m_textureData{}
    , m_guiUpdateFlags{ guiUpdateFlags }
    , m_transferFunction{ transferFunction }
    , m_transferFunctionTexture{ transferFunctionTexture }
{
    UpdateTextureData();
    UpdateTexture();
}

void TransferFunctionTextureUpdater::Update()
{
    if (m_guiUpdateFlags.transferFunctionChanged)
    {
        UpdateTextureData();
        UpdateTexture();
        // TODO don't reset flag here
        m_guiUpdateFlags.transferFunctionChanged = false;
    }
}

void TransferFunctionTextureUpdater::UpdateTextureData()
{
    const size_t numActivePoints = m_transferFunction.GetNumActivePoints();
    const auto& controlPoints = m_transferFunction.GetControlPoints();

    // For each texel, compute interpolated RGBA and write to texture data
    std::for_each(std::execution::par_unseq, textureIndices.begin(), textureIndices.end(), [&](size_t i)
    {
        // Normalize texel index to [0, 1] range
        const float normalizedValue = static_cast<float>(i) / static_cast<float>(TransferFunctionConstants::textureSize - 1);

        // Find the two control points to interpolate between
        glm::vec4 rgba{0.0f, 0.0f, 0.0f, 0.0f};

        switch (numActivePoints)
        {
            case 0:
                // No control points: transparent black
                rgba = glm::vec4{0.0f, 0.0f, 0.0f, 0.0f};
                break;

            case 1:
                // Single control point: use its color/opacity everywhere
                rgba = glm::vec4{controlPoints[0].color, controlPoints[0].opacity};
                break;

            default:
            {
                // Find the segment containing normalizedValue
                // Control points should be sorted by value
                const auto activePoints = std::span{controlPoints.data(), numActivePoints};

                // Find the first control point with value >= normalizedValue
                auto upperIt = std::lower_bound(activePoints.begin(), activePoints.end(), normalizedValue,
                    [](const TransferFunctionControlPoint& cp, float value) { return cp.value < value; });

                if (upperIt == activePoints.begin())
                {
                    // Before first control point: use first control point's color
                    rgba = glm::vec4{controlPoints[0].color, controlPoints[0].opacity};
                }
                else if (upperIt == activePoints.end())
                {
                    // After last control point: use last control point's color
                    const size_t lastIndex = numActivePoints - 1;
                    rgba = glm::vec4{controlPoints[lastIndex].color, controlPoints[lastIndex].opacity};
                }
                else
                {
                    // Between two control points: interpolate
                    auto lowerIt = upperIt - 1;
                    const TransferFunctionControlPoint& lower = *lowerIt;
                    const TransferFunctionControlPoint& upper = *upperIt;

                    // Calculate interpolation factor
                    const float t = (normalizedValue - lower.value) / (upper.value - lower.value);

                    // Linear interpolation
                    const glm::vec3 interpolatedColor = glm::mix(lower.color, upper.color, t);
                    const float interpolatedOpacity = glm::mix(lower.opacity, upper.opacity, t);

                    rgba = glm::vec4{interpolatedColor, interpolatedOpacity};
                }
                break;
            }
        }

        // Write RGBA to texture data
        const size_t baseIndex = i * 4;
        m_textureData[baseIndex + 0] = FloatToUnsignedByte(rgba.r);
        m_textureData[baseIndex + 1] = FloatToUnsignedByte(rgba.g);
        m_textureData[baseIndex + 2] = FloatToUnsignedByte(rgba.b);
        m_textureData[baseIndex + 3] = FloatToUnsignedByte(rgba.a);
    });
}

void TransferFunctionTextureUpdater::UpdateTexture()
{
    m_transferFunctionTexture = Texture(
        TextureId::TransferFunction,
        m_transferFunctionTexture.GetTextureUnitEnum(),
        static_cast<unsigned int>(TransferFunctionConstants::textureSize),
        GL_RGBA,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        m_textureData.data()
    );
}
