#ifndef GET_LIGHT_SPACE_MATRIX_H
#define GET_LIGHT_SPACE_MATRIX_H

#include <glm/glm.hpp>

struct GuiParameters;

glm::mat4 GetLightSpaceMatrix(const GuiParameters& guiParameters);

#endif
