#include "Engine/zEngine.h"
#include "ToolKit/FileToolKit.h"
#include "ToolKit/TimerToolkit.h"

using namespace std;

void show(ShaderProgram* program)
{
    std::vector<std::string> ss;
    program->GetAllUniformBlockName(ss);
    for (auto& s : ss)
    {
        // 获取块索引
        GLID blockIndex = program->GetUniformBlockIndex(s);

        // 获取成员名和偏移
        {
            GLint numUniforms = program->GetUniformBlockMemberNumbers(blockIndex);

            std::vector<GLID> Ids;
            program->GetUniformBlockMemberId(numUniforms, blockIndex, Ids);

            for (GLint i = 0; i < numUniforms; ++i) {
                std::string name = program->GetUniformBlockMemberName(Ids[i]);

                GLint size = program->GetUniformBlockMemberSize(Ids[i]);
                GLenum type = program->GetUniformBlockMemberType(Ids[i]);
                GLint offset = program->GetUniformBlockMemberOffset(Ids[i]);

                LOG(s, name, offset, size, type);
            }
        }
    }
}



int main()
{
    system("chcp 65001");

    Engine engine;

    // ShaderProgram sp {"MeshLightWithUbo"};
    //
    // show(&sp);
    //
    // return 0;   
    engine.SetLevel(1);
    engine.Run();
    return 0;
}