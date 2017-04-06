#include "glwidget.h"
#include <QImage>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    m_texture(0),
    m_program(0),
    m_vbo(0),
    m_ibo(0),
    m_vao(0)
{
    // if use qopenglwidget, then you must add this,
    // or there will be a black screen, no need for qopenglwindow
    setAttribute(Qt::WA_AlwaysStackOnTop);
    window()->update();
}

GLWidget::~GLWidget()
{
    makeCurrent();

    delete m_ibo;
    delete m_vbo;
    delete m_vao;
    delete m_program;
    delete m_texture;

    doneCurrent();
}

const GLfloat vertices[] = {
    //     ---- pos ----    ---- color ----    - texture coord -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
};

const GLuint indices[] = {
    0, 1, 3, // First Triangle
    1, 2, 3  // Second Triangle
};

void GLWidget::initializeGL()
{
    QImage img(":/container.jpg");
    Q_ASSERT(!img.isNull());
    m_texture = new QOpenGLTexture(img);

    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh");
    m_program->link();

    m_vao = new QOpenGLVertexArrayObject;
    m_vao->create();
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo->create();
    m_ibo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_ibo->create();

    m_vao->bind();
    m_vbo->bind();
    m_vbo->allocate(vertices, sizeof(vertices));
    m_ibo->bind();
    m_ibo->allocate(indices, sizeof(indices));
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
                          8 * sizeof(GLfloat), (GLvoid *)(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                          8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    m_vao->release();
}

void GLWidget::resizeGL(int w, int h)
{

}

void GLWidget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();
    m_texture->bind();

    m_vao->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_vao->release();
    m_texture->release();
}
