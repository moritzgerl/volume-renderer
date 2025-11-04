#ifndef ELEMENT_STORAGE_H
#define ELEMENT_STORAGE_H

#include <vector>

template <typename ElementType, typename ElementIdType>
class ElementStorage
{
public:
    explicit ElementStorage(std::vector<ElementType>&& elements);

    const std::vector<ElementType>& GetElements() const;
    const ElementType& GetElement(ElementIdType elementId) const;
    ElementType& GetElement(ElementIdType elementId);    

private:
    std::vector<ElementType> m_elements;
};

#endif
