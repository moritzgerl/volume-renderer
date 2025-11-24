#include <transferfunction/InterpolateTransferFunction.h>

#include <algorithm>
#include <cstddef>


namespace
{
    float CatmullRom(float t, float p0, float p1, float p2, float p3)
    {
        const auto t2 = t * t;
        const auto t3 = t2 * t;
        return 0.5f * ((2.0f * p1) +
            (-p0 + p2) * t +
            (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2 +
            (-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t3);
    }
} // anonymous namespace

glm::vec4 InterpolateTransferFunction(
    float normalizedValue,
    std::span<const TransferFunctionControlPoint> activePoints
)
{
    const auto numActivePoints = activePoints.size();

    switch (numActivePoints)
    {
        case 0:
            // No control points: transparent black
            return glm::vec4{0.0f, 0.0f, 0.0f, 0.0f};

        case 1:
            // Single control point: use its color/opacity everywhere
            return glm::vec4{activePoints[0].color, activePoints[0].opacity};

        default:
        {
            // Find the first control point with value >= normalizedValue
            auto upperIt = std::lower_bound(activePoints.begin(), activePoints.end(), normalizedValue,
                [](const TransferFunctionControlPoint& cp, float value) { return cp.value < value; });

            if (upperIt == activePoints.begin())
            {
                // Before first control point: use first control point's color/opacity
                return glm::vec4{activePoints[0].color, activePoints[0].opacity};
            }
            else if (upperIt == activePoints.end())
            {
                // After last control point: use last control point's color/opacity
                const auto lastIndex = numActivePoints - 1;
                return glm::vec4{activePoints[lastIndex].color, activePoints[lastIndex].opacity};
            }
            else
            {
                // Between two control points: interpolate
                const auto lowerIt = upperIt - 1;
                const auto lowerIndex = std::distance(activePoints.begin(), lowerIt);
                const auto upperIndex = std::distance(activePoints.begin(), upperIt);

                const auto& lower = *lowerIt;
                const auto& upper = *upperIt;

                // Calculate linear interpolation factor
                const auto t = (normalizedValue - lower.value) / (upper.value - lower.value);

                // Linear interpolation for color
                const auto interpolatedColor = glm::mix(lower.color, upper.color, t);

                // Catmull-Rom spline interpolation for opacity
                // Get control points with edge extrapolation
                const auto& p0 = (lowerIndex == 0) ? activePoints[0] : activePoints[lowerIndex - 1];
                const auto& p1 = lower;
                const auto& p2 = upper;
                const auto& p3 = (upperIndex + 1 >= numActivePoints) ? activePoints[upperIndex] : activePoints[upperIndex + 1];

                const auto interpolatedOpacity = CatmullRom(t, p0.opacity, p1.opacity, p2.opacity, p3.opacity);

                return glm::vec4{interpolatedColor, interpolatedOpacity};
            }
        }
    }
}
