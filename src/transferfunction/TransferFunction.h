#ifndef TRANSFER_FUNCTION_H
#define TRANSFER_FUNCTION_H

#include <transferfunction/TransferFunctionControlPoint.h>

#include <config/TransferFunctionConstants.h>

#include <array>

class TransferFunction
{
public:
    size_t GetNumActivePoints() const;
    void SetNumActivePoints(size_t count);
    void IncrementNumActivePoints();

    const std::array<TransferFunctionControlPoint, TransferFunctionConstants::maxNumControlPoints>& GetControlPoints() const;
    std::array<TransferFunctionControlPoint, TransferFunctionConstants::maxNumControlPoints>& GetControlPoints();

    const TransferFunctionControlPoint& operator[](size_t index) const;
    TransferFunctionControlPoint& operator[](size_t index);

    const std::array<unsigned char, TransferFunctionConstants::textureDataSize>& GetTextureData() const;
    std::array<unsigned char, TransferFunctionConstants::textureDataSize>& GetTextureData();

    void UpdateTextureData();

private:
    std::array<TransferFunctionControlPoint, TransferFunctionConstants::maxNumControlPoints> m_controlPoints;
    size_t m_numActivePoints;
    std::array<unsigned char, TransferFunctionConstants::textureDataSize> m_textureData;
};

#endif
