#include <shader/UpdateSsaoFinalShader.h>
#include <shader/Shader.h>
#include <gui/GuiParameters.h>

void ShaderUtils::UpdateSsaoFinalShader(const GuiParameters& guiParameters, const Shader& ssaoFinalShader)
{
    ssaoFinalShader.setInt("enableSsao", static_cast<int>(guiParameters.enableSsao));
}

