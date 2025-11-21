#include <storage/ElementStorage.h>
#include <shader/Shader.h>
#include <shader/ShaderId.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <buffers/FrameBuffer.h>
#include <buffers/FrameBufferId.h>
#include <renderpass/RenderPass.h>
#include <renderpass/RenderPassId.h>

#include <algorithm>
#include <iostream>

namespace
{
    template <typename ElementType, typename ElementIdType, typename T>
    auto& GetElementImpl(ElementIdType elementId, T& elements)
    {
        auto elementIter = std::find_if(elements.begin(), elements.end(),
            [elementId](const ElementType& element)
            {
                return element.GetId() == elementId;
            }
        );

        if (elementIter == elements.end())
        {
            std::cerr << "ElementStorage::GetElementImpl - could not find element with the specified ID" << std::endl;
            return elements[0];
        }

        return *elementIter;
    }
}

template <typename ElementType, typename ElementIdType>
ElementStorage<ElementType, ElementIdType>::ElementStorage(std::vector<ElementType>&& elements)
    : m_elements{std::move(elements)}
{
}

template <typename ElementType, typename ElementIdType>
const ElementType& ElementStorage<ElementType, ElementIdType>::GetElement(ElementIdType elementId) const
{
    return GetElementImpl<ElementType, ElementIdType>(elementId, m_elements);
}

template <typename ElementType, typename ElementIdType>
ElementType& ElementStorage<ElementType, ElementIdType>::GetElement(ElementIdType elementId)
{
    return GetElementImpl<ElementType, ElementIdType>(elementId, m_elements);
}

template <typename ElementType, typename ElementIdType>
const std::vector<ElementType>& ElementStorage<ElementType, ElementIdType>::GetElements() const
{
    return m_elements;
}

template class ElementStorage<Shader, ShaderId>;
template class ElementStorage<Texture, TextureId>;
template class ElementStorage<FrameBuffer, FrameBufferId>;
template class ElementStorage<RenderPass, RenderPassId>;
