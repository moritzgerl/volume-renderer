/**
* \file ElementStorage.h
*
* \brief Generic storage container for indexed collections of elements.
*/

#ifndef ELEMENT_STORAGE_H
#define ELEMENT_STORAGE_H

#include <vector>

/**
* \class ElementStorage
*
* \brief Template class for storing and retrieving elements by ID.
*
* Provides a type-safe container for collections of elements that can be
* accessed by enum-based IDs. Elements are stored in a vector and accessed
* by casting the enum ID to an integer index.
*
* This pattern is used throughout the application for storing shaders,
* textures, framebuffers, and render passes, allowing type-safe retrieval
* by ID while maintaining efficient vector storage.
*
* @tparam ElementType The type of elements stored (e.g., Shader, Texture).
* @tparam ElementIdType The enum type used for element IDs (e.g., ShaderId, TextureId).
*
* @see Storage for using ElementStorage with various resource types.
* @see ShaderId, TextureId, FrameBufferId for example ID enums.
*/
template <typename ElementType, typename ElementIdType>
class ElementStorage
{
public:
    /**
    * Constructor.
    * @param elements Vector of elements to store (moved).
    */
    explicit ElementStorage(std::vector<ElementType>&& elements);

    /**
    * Gets all elements.
    * @return Const reference to the vector of all elements.
    */
    const std::vector<ElementType>& GetElements() const;

    /**
    * Gets a const element by ID.
    * @param elementId The ID of the element to retrieve.
    * @return Const reference to the requested element.
    */
    const ElementType& GetElement(ElementIdType elementId) const;

    /**
    * Gets a mutable element by ID.
    * @param elementId The ID of the element to retrieve.
    * @return Mutable reference to the requested element.
    */
    ElementType& GetElement(ElementIdType elementId);

private:
    std::vector<ElementType> m_elements; /**< Storage vector for elements. */
};

#endif
