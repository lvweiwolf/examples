//////////////////////////////////////////////////////////////////////////////
//
//  Triangles.cpp
//
//////////////////////////////////////////////////////////////////////////////

#include <vermilion.h>

#include "vgl.h"
#include "vapp.h"
#include "LoadShaders.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];

const GLuint  NumVertices = 6;

BEGIN_APP_DECLARATION(KeyPressExample)
    virtual void Initialize(const char * title);
    virtual void Display(bool auto_redraw);
    virtual void Finalize(void);
    virtual void Resize(int width, int height);
    void OnKey(int key, int scancode, int action, int mods);
END_APP_DECLARATION()

DEFINE_APP(KeyPressExample, "Key Press Example")
//----------------------------------------------------------------------------
//
// init
//

void KeyPressExample::Initialize(const char * title)
{
    base::Initialize(title);
	
	// 返回n个未使用的对象名到数组array中，用作顶点数组对象。返回的名字可以
	// 用来分配更多的缓存对象，并且他们已经使用未初始化的顶点数组集合的默认状
	// 态进行了数值的初始化。
    glGenVertexArrays( NumVAOs, VAOs );

	// 负责为顶点数组对象分配内存空间，如果输入的变量array非0，并且是
	// glGenVertexArrays返回的，那么它将创建一个新的顶点数组对象并且与
	// 其名称关联起来。如果绑定到一个已经创建的顶点数组对象中，那么会激
	// 活这个顶点数组对象，并且直接影响对象中所保存的顶点数组状态。如果
	// 输入的变量array为0，那么OpenGL将不再使用程序所分配的任何顶点数组
	// 对象，并且将渲染状态重设为顶点数组的默认状态。
	// 如果array不是glGenVertexArrays返回的数值，或者它已经被
	// glDeleteVertexArrays函数释放了，那么这里将产生一个
	// GL_INVALID_OPERATION错误。
    glBindVertexArray( VAOs[Triangles] );

    GLfloat  vertices[NumVertices][2] = {
        { -0.90f, -0.90f }, {  0.85f, -0.90f }, { -0.90f,  0.85f },  // Triangle 1
        {  0.90f, -0.85f }, {  0.90f,  0.90f }, { -0.85f,  0.90f }   // Triangle 2
    };

	// 返回NumBuffers个当前未使用的缓存对象名称，并保存到Buffers数组中。
	// 返回到Buffers中的名称不一定是连续的整形数据。
	// 这里返回的名称只用于分配其他缓存对象，他们在兵丁之后只会记录一个可
	// 用的状态。0是一个保留的缓存对象名称，glGenBuffers()永远都不会返回这
	// 个值的缓存对象。
    glGenBuffers( NumBuffers, Buffers );

	// 指定当前激活的缓存对象。target必须设置为一下类型的其中一个：
	// GL_ARRAY_BUFFER
	// GL_ELEMENT_ARRAY_BUFFER
	// GL_PIXEL_PACK_BUFFER
	// GL_PIXEL_UNPACK_BUFFER
	// GL_COPY_READ_BUFFER
	// GL_COPY_WRITE_BUFFER
	// GL_TRANSFORM_FEEDBACK_BUFFER
	// GL_UNIFORM_BUFFER
	// Buffers设置的是要绑定缓存对象名称。
    glBindBuffer( GL_ARRAY_BUFFER, Buffers[ArrayBuffer] );

	// 在OpenGL服务端内分配size个存储单元(通常为byte)，用于存储数据或者索引。
	// 如果当前绑定的对象已经存在了关联数据，那么会首先删除这些数据。
	// 对于顶点属性数据，target设置为GL_ARRAY_BUFFER；索引数据为GL_ELEMENT_
	// ARRAY_BUFFER;OpenGL像素数据为GL_PIXEL_UNPACK_BUFFER; 对于OpenGL获取。

	// 的像素数据为GL_PIXEL_PACK_BUFFER; 对于缓存间的复制数据为GL_COPY_READ_
	// BUFFER和GL_COPY_WRITE_BUFFER; 对于纹理缓存中存储的纹理数据为GL_TEXTURE
	// _BUFFER; 对于通过transform feedback着色器获得的结果设置为GL_TRANSFORM_
	// FEEDBACK_BUFFER; 而一致变量要设置为GL_UNIFORM_BUFFER。
	glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    ShaderInfo  shaders[] = {
        { GL_VERTEX_SHADER, "media/shaders/keypress/keypress.vert" },
        { GL_FRAGMENT_SHADER, "media/shaders/keypress/keypress.frag" },
        { GL_NONE, NULL }
    };

	// 加载顶点着色器和片元着色器 
    GLuint program = LoadShaders( shaders );
    glUseProgram( program );

    glVertexAttribPointer(vPosition, 2, GL_FLOAT,
                           GL_FALSE, 0, BUFFER_OFFSET(0) );
    glEnableVertexAttribArray(vPosition);
}

void KeyPressExample::OnKey(int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
            case GLFW_KEY_M:
                {
                    static GLenum  mode = GL_FILL;

                    mode = ( mode == GL_FILL ? GL_LINE : GL_FILL );
                    glPolygonMode( GL_FRONT_AND_BACK, mode );
                }
                return;
        }
    }

    base::OnKey(key, scancode, action, mods);
}

//----------------------------------------------------------------------------
//
// display
//

void KeyPressExample::Display(bool auto_redraw)
{
    glClear( GL_COLOR_BUFFER_BIT );

    glBindVertexArray( VAOs[Triangles] );
    glDrawArrays(GL_TRIANGLES, 0, NumVertices );

    base::Display(auto_redraw);
}

void KeyPressExample::Resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void KeyPressExample::Finalize(void)
{

}
