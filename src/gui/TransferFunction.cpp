#include <gui/TransferFunction.h>

TransferFunction::TransferFunction()
    : m_numActivePoints(0)
{
}

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
