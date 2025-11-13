#include <transferfunction/TransferFunction.h>

#include <algorithm>
#include <array>
#include <execution>
#include <ranges>
#include <span>

namespace
{
    constexpr std::array<size_t, TransferFunctionConstants::textureSize> MakeTextureIndices()
    {
        std::array<size_t, TransferFunctionConstants::textureSize> indices{};
        std::ranges::copy(std::views::iota(size_t{0}, TransferFunctionConstants::textureSize), indices.begin());
        return indices;
    }

    constexpr auto textureIndices = MakeTextureIndices();

    unsigned char FloatToUnsignedByte(float value)
    {
        return static_cast<unsigned char>(glm::clamp(value, 0.0f, 1.0f) * 255.0f);
    }
} // anonymous namespace

size_t TransferFunction::GetNumActivePoints() const
{
    return m_numActivePoints;
}

void TransferFunction::SetNumActivePoints(size_t count)
{
    m_numActivePoints = std::min(count, TransferFunctionConstants::maxNumControlPoints);
}

void TransferFunction::IncrementNumActivePoints()
{
    if (m_numActivePoints < TransferFunctionConstants::maxNumControlPoints)
    {
        ++m_numActivePoints;
    }
}

const std::array<TransferFunctionControlPoint, TransferFunctionConstants::maxNumControlPoints>& TransferFunction::GetControlPoints() const
{
    return m_controlPoints;
}

std::array<TransferFunctionControlPoint, TransferFunctionConstants::maxNumControlPoints>& TransferFunction::GetControlPoints()
{
    return m_controlPoints;
}

const TransferFunctionControlPoint& TransferFunction::operator[](size_t index) const
{
    return m_controlPoints[index];
}

TransferFunctionControlPoint& TransferFunction::operator[](size_t index)
{
    return m_controlPoints[index];
}

const std::array<unsigned char, TransferFunctionConstants::textureDataSize>& TransferFunction::GetTextureData() const
{
    return m_textureData;
}

std::array<unsigned char, TransferFunctionConstants::textureDataSize>& TransferFunction::GetTextureData()
{
    return m_textureData;
}

void TransferFunction::UpdateTextureData()
{
    // For each texel, compute interpolated RGBA and write to texture data
    std::for_each(std::execution::par_unseq, textureIndices.begin(), textureIndices.end(), [this](size_t i)        
    {
        // Normalize texel index to [0, 1] range
        const float normalizedValue = static_cast<float>(i) / static_cast<float>(TransferFunctionConstants::textureSize - 1);

        // Find the two control points to interpolate between
        glm::vec4 rgba{0.0f, 0.0f, 0.0f, 0.0f};

        switch (m_numActivePoints)
        {
            case 0:
                // No control points: transparent black
                rgba = glm::vec4{0.0f, 0.0f, 0.0f, 0.0f};
                break;

            case 1:
                // Single control point: use its color/opacity everywhere
                rgba = glm::vec4{m_controlPoints[0].color, m_controlPoints[0].opacity};
                break;

            default:
            {
                // Find the segment containing normalizedValue
                // Control points should be sorted by value
                const auto activePoints = std::span{m_controlPoints.data(), m_numActivePoints};

                // Find the first control point with value >= normalizedValue
                auto upperIt = std::lower_bound(activePoints.begin(), activePoints.end(), normalizedValue,
                    [](const TransferFunctionControlPoint& cp, float value) { return cp.value < value; });

                if (upperIt == activePoints.begin())
                {
                    // Before first control point: use first control point's color
                    rgba = glm::vec4{m_controlPoints[0].color, m_controlPoints[0].opacity};
                }
                else if (upperIt == activePoints.end())
                {
                    // After last control point: use last control point's color
                    const size_t lastIndex = m_numActivePoints - 1;
                    rgba = glm::vec4{m_controlPoints[lastIndex].color, m_controlPoints[lastIndex].opacity};
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
