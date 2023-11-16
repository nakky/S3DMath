
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "S3DMath/S3DMath.h"

using namespace S3DMath;

std::list<Entity *> entityList;

GLint vpos_location = 0;
GLint vuv_location = 0;

GLint vcol_location = 0;

GLint trans_location = 0;
GLint rot_location = 0;
GLint scale_location = 0;

GLint ctrans_location = 0;
GLint crot_location = 0;

GLint projection_location = 0;

GLuint program = 0;

RenderList renderList;

struct MeshGLParameter
{
    GLuint posBuffer;
    GLuint posVao;
    GLuint indexBuffer;
};

struct MaterialGLParameter
{
    GLuint texture;
};

static const char *vertex_shader_text =
    "#version 330\n"
    "vec3 mul(vec3 v1, vec3 v2){"
    "   return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);"
    "}\n"
    "vec3 rotate(vec3 v, vec4 q){"
    "   float rx = v.x * q.w + v.y * -q.z + v.z * q.y;"
    "   float ry = v.x * q.z + v.y * q.w + v.z * -q.x;"
    "   float rz = v.x * -q.y + v.y * q.x + v.z * q.w;"
    "	float rw = v.x * q.x + v.y * q.y + v.z * q.z;"
    "	return vec3( q.x * rw + q.y * rz + q.z * -ry + q.w * rx,"
    "	    q.x * -rz + q.y * rw + q.z * rx + q.w * ry,"
    "	    q.x * ry + q.y * -rx + q.z * rw + q.w * rz);"
    "}\n"
    "uniform mat4 projection;\n"
    "uniform vec3 trans;\n"
    "uniform vec4 rot;\n"
    "uniform vec3 scale;\n"
    "uniform vec3 ctrans;\n"
    "uniform vec4 crot;\n"
    "in vec3 position;\n"
    "void main()"
    "{"
    "   vec4 vec = vec4(rotate(mul(position, scale), rot) + trans, 1.0);"
    "   gl_Position = projection * vec4(rotate((vec.xyz - ctrans), crot), 1.0);"
    "}\n";

static const char *fragment_shader_text =
    "#version 330\n"
    "uniform vec4 color;\n"
    "out vec4 fragment;\n"
    "void main()"
    "{"
    "    fragment = color;"
    "}\n";

static void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void registerEntity(Entity *entity)
{
    entityList.push_back(entity);

    Mesh *mesh = entity->getMesh();
    if (mesh != NULL)
    {
        MeshGLParameter *param = new MeshGLParameter();

        glGenBuffers(1, &param->posBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, param->posBuffer);
        glBufferData(GL_ARRAY_BUFFER, mesh->getVerticesBufferSize(), mesh->getVertices(), GL_STATIC_DRAW);

        glGenVertexArrays(1, &param->posVao);
        glBindVertexArray(param->posVao);

        glEnableVertexAttribArray(vpos_location);
        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);

        glGenBuffers(1, &param->indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, param->indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndicesBufferSize(), mesh->getIndices(), GL_STATIC_DRAW);

        mesh->setUserData(param);
    }

    /*
    Material *mat = entity->getMaterial();
    if (mat != NULL)
    {
    }
    */

    renderList.add(entity);
}

void releaseEntity(Entity *entity)
{
    Mesh *mesh = entity->getMesh();
    if (mesh != NULL)
    {
        MeshGLParameter *param = (MeshGLParameter *)mesh->getUserData();

        glDeleteBuffers(1, &param->posBuffer);
        glDeleteBuffers(1, &param->indexBuffer);
        glDeleteVertexArrays(1, &param->posVao);

        SAFE_DELETE(param);

        mesh->cleanup();
        SAFE_DELETE(mesh);
    }

    Material *mat = entity->getMaterial();
    if (mat != NULL)
    {
        if (mat->userData != NULL)
        {
            MaterialGLParameter *matParam = (MaterialGLParameter *)mat->userData;
            glDeleteTextures(1, &matParam->texture);
            SAFE_DELETE(matParam);
        }
        SAFE_DELETE(mat);
    }

    // entityList.remove(entity);
    entity->cleanup();
    SAFE_DELETE(entity);
}

Vector4 white(1.0f, 1.0f, 1.0f, 1.0f);
void renderEntity(Entity *entity, float ratio)
{
    Mesh *mesh = entity->getMesh();
    Material *mat = entity->getMaterial();

    if (mesh == NULL || mat == NULL)
        return;

    MeshGLParameter *param = (MeshGLParameter *)mesh->getUserData();
    MaterialGLParameter *matparam = (MaterialGLParameter *)mat->userData;

    Matrix44 m;
    m.setUnitMatrix();

    glUseProgram(program);

    glUniform3fv(trans_location, 1, (const GLfloat *)entity->getGlobalPosition());
    glUniform4fv(rot_location, 1, (const GLfloat *)entity->getGlobalOrientation());
    glUniform3fv(scale_location, 1, (const GLfloat *)entity->getGlobalScale());

    glUniform4fv(vcol_location, 1, (const GLfloat *)&mat->color);

    glBindVertexArray(param->posVao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, param->indexBuffer);

    int numIndices = mesh->getIndicesBufferSize() / sizeof(int);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);

    glUniform4fv(vcol_location, 1, (const GLfloat *)&white);
    glDrawElements(GL_LINE_LOOP, numIndices, GL_UNSIGNED_INT, 0);
}

int main(void)
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    vpos_location = glGetAttribLocation(program, "position");
    vcol_location = glGetUniformLocation(program, "color");

    trans_location = glGetUniformLocation(program, "trans");
    rot_location = glGetUniformLocation(program, "rot");
    scale_location = glGetUniformLocation(program, "scale");

    ctrans_location = glGetUniformLocation(program, "ctrans");
    crot_location = glGetUniformLocation(program, "crot");

    projection_location = glGetUniformLocation(program, "projection");

    Entity *entity;
    Mesh *mesh;
    Material *mat;
    MaterialGLParameter *matparam;
    Vector3 v;
    Quaternion4 q;

    // Base
    Cluster *cluster = new Cluster();

    // Camera
    Camera *camera = new Camera();
    camera->init();
    registerEntity(camera);

    cluster->getRootEntity()->addChild(camera);

    Entity *content = new Entity();
    content->init();
    registerEntity(content);

    cluster->getRootEntity()->addChild(content);

    // Red rect
    entity = new Entity();
    entity->init();

    mesh = new Rectangle(1.f, 1.f);
    mesh->init();
    entity->setMesh(mesh);

    mat = new Material();
    mat->color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
    mat->opaque = true;
    mat->shaderId = 0;
    mat->textureId = 0;

    matparam = new MaterialGLParameter();
    matparam->texture = 0;

    mat->userData = matparam;
    entity->setMaterial(mat);

    registerEntity(entity);
    content->addChild(entity);

    entity->setLocalPosition(Vector3(0.5f, 0.5f, 0.0f));

    q.setUnitQuaternion();
    q.convert(Vector3(1.0f, 0.0f, 0.0f), 45.0f / 2.0f / PIF);
    entity->setLocalRotation(q);
    entity->setLocalScale(Vector3(1.2f, 1.2f, 1.2f));

    // blue rect
    entity = new Entity();
    entity->init();

    mesh = new Cuboid(0.5f, 0.5f, 0.5f);

    mesh->init();
    entity->setMesh(mesh);

    mat = new Material();
    mat->color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
    mat->opaque = true;
    mat->shaderId = 0;
    mat->textureId = 0;

    matparam = new MaterialGLParameter();
    matparam->texture = 0;

    mat->userData = matparam;

    entity->setMaterial(mat);

    registerEntity(entity);
    content->addChild(entity);

    content->setLocalPosition(Vector3(0.0f, 0.0f, -3.0f));

    float t = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // window
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = (float)width / (float)height;

        glViewport(0, 0, width, height);

        glEnable(GL_DEPTH_TEST);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        t += 0.01f;
        q.setUnitQuaternion();
        q.convert(Vector3(0.0f, 1.0f, 0.0f), t);
        content->setLocalRotation(q);

        camera->setLocalPosition(Vector3(3.0f, 4.2426f, 0.0f));

        Quaternion4 crx;
        crx.setUnitQuaternion();
        crx.convert(Vector3(1.0f, 0.0f, 0.0), -45.0f / 180.0f * PIF);
        Quaternion4 cry;
        cry.setUnitQuaternion();
        cry.convert(Vector3(0.0f, 1.0f, 0.0), 45.0f / 180.0f * PIF);
        camera->setLocalRotation(cry * crx);

        cluster->tryUpdate();

        // Camera
        camera->ortho(-ratio, ratio, -1.0f, 1.0f, 0.01f, 100.0f);
        // camera->perspective(60.0f / 180.f * (float)PIF, ratio, 0.01f, 100.0f);

        Matrix44 proj = camera->getProjectionMatrix();
        glUniformMatrix4fv(projection_location, 1, GL_FALSE, (const GLfloat *)proj.serial);

        glUniform3fv(ctrans_location, 1, (const GLfloat *)camera->getGlobalPosition());
        Quaternion4 crot = *(camera->getGlobalOrientation());
        crot.inverse();
        glUniform4fv(crot_location, 1, (const GLfloat *)&crot);

        // renderlist
        renderList.sort(Vector3(0.0f, 0.0f, 10.0f));

        std::list<Entity *> opaqueList = renderList.getOpaqueSortedList();
        std::list<Entity *> notOpaqueList = renderList.getNotOpaqueSortedList();

        for (auto ite = opaqueList.begin(); ite != opaqueList.end(); ite++)
        {
            renderEntity((*ite), ratio);
        }

        for (auto ite = notOpaqueList.begin(); ite != notOpaqueList.end(); ite++)
        {
            renderEntity((*ite), ratio);
        }

        // printf("error:%d\n", glGetError());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for (auto ite = entityList.begin(); ite != entityList.end(); ite++)
    {
        releaseEntity((*ite));
    }

    SAFE_DELETE(cluster);

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
