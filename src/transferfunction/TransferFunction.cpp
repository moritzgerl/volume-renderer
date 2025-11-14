#include <transferfunction/TransferFunction.h>

#include <algorithm>
#include <ranges>
#include <glm/glm.hpp>

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

void TransferFunction::AddPoint(float value, float opacity)
{
    // Find the insertion position to keep points sorted by value
    auto pointIndices = std::views::iota(size_t{0}, m_numActivePoints);
    auto it = std::ranges::find_if(pointIndices, [&](size_t index) {
        return m_controlPoints[index].value > value;
    });

    size_t insertionIndex = (it != pointIndices.end()) ? *it : m_numActivePoints;

    // Interpolate color from surrounding points
    glm::vec3 newColor = glm::vec3(0.5f);
    if (insertionIndex > 0 && insertionIndex < m_numActivePoints)
    {
        // Between two points
        const auto& p0 = m_controlPoints[insertionIndex - 1];
        const auto& p1 = m_controlPoints[insertionIndex + 1];
        const float t = (value - p0.value) / (p1.value - p0.value);
        newColor = glm::mix(p0.color, p1.color, t);
    }
    else if (insertionIndex == 0 && m_numActivePoints > 0)
    {
        // Before the first point
        newColor = m_controlPoints[1].color;
    }
    else if (insertionIndex == m_numActivePoints && m_numActivePoints > 0)
    {
        // After the last point
        newColor = m_controlPoints[insertionIndex - 1].color;
    }

    // Shift existing points to make room for the new point
    std::shift_right(m_controlPoints.begin() + insertionIndex, m_controlPoints.begin() + m_numActivePoints + 1, 1);

    // Insert the new point at the correct position
    m_controlPoints[insertionIndex].value = value;
    m_controlPoints[insertionIndex].color = newColor;
    m_controlPoints[insertionIndex].opacity = opacity;

    ++m_numActivePoints;
}

void TransferFunction::RemovePoint(size_t index)
{
    std::shift_left(m_controlPoints.begin() + index, m_controlPoints.begin() + m_numActivePoints, 1);
    --m_numActivePoints;
}