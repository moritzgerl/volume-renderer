#include <transferfunction/TransferFunction.h>

#include <algorithm>
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
    size_t insertIndex = m_numActivePoints;
    for (size_t j = 0; j < m_numActivePoints; ++j)
    {
        if (m_controlPoints[j].value > value)
        {
            insertIndex = j;
            break;
        }
    }

    // Shift existing points to make room for the new point
    for (size_t j = m_numActivePoints; j > insertIndex; --j)
    {
        m_controlPoints[j] = m_controlPoints[j - 1];
    }

    // Interpolate color from surrounding points
    glm::vec3 newColor = glm::vec3(0.5f);
    if (insertIndex > 0 && insertIndex < m_numActivePoints)
    {
        // Between two points
        const auto& p0 = m_controlPoints[insertIndex - 1];
        const auto& p1 = m_controlPoints[insertIndex + 1];
        const float t = (value - p0.value) / (p1.value - p0.value);
        newColor = glm::mix(p0.color, p1.color, t);
    }
    else if (insertIndex == 0 && m_numActivePoints > 0)
    {
        // Before the first point
        newColor = m_controlPoints[1].color;
    }
    else if (insertIndex == m_numActivePoints && m_numActivePoints > 0)
    {
        // After the last point
        newColor = m_controlPoints[insertIndex - 1].color;
    }

    // Insert the new point at the correct position
    m_controlPoints[insertIndex].value = value;
    m_controlPoints[insertIndex].color = newColor;
    m_controlPoints[insertIndex].opacity = opacity;

    ++m_numActivePoints;
}

void TransferFunction::RemovePoint(size_t index)
{
    std::shift_left(m_controlPoints.begin() + index, m_controlPoints.begin() + m_numActivePoints, 1);
    --m_numActivePoints;
}