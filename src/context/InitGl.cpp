#include <context/InitGl.h>
#include <glad/glad.h>

void Context::InitGl()
{
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_CULL_FACE); // OPTIMIZE enable culling, but need to fix normals of unit cube first
    //glCullFace(GL_BACK);
}
