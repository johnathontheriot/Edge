#ifndef BufferObject_hpp
#define BufferObject_hpp


class BufferObject {
protected:
    friend class Geometry;
    friend class GLObject;
    GLuint id;
    GLuint location;
    int dimension;
    GLenum type;
    int size;
    void * data;
public:
    virtual void bind() {
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->size, this->data, GL_STATIC_DRAW);
    }
    
    virtual void update(GLfloat * vertices, int size) {
        this->data = vertices;
        this->size = size;
        this->bind();
    }
};

template <class BufferType>
class GLBufferObject: public BufferObject {
private:
    friend class Geometry;
    friend class GLObject;
    BufferType * data;
public:
    GLBufferObject(GLuint location, int dimension, GLenum type, int size, BufferType * data) {
        this->createBuffer(this->id);
        this->location = location;
        this->dimension = dimension;
        this->type = type;
        this->size = size;
        this->data = data;
    }
    
    void createBuffer(GLuint & id) {
        glGenBuffers(1, &id);
    }
    
    virtual void bind() {
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(BufferType) * this->size, this->data, GL_STATIC_DRAW);
    }
    
    virtual void update(GLfloat * vertices, int size) {
        this->data = vertices;
        this->size = size;
        this->bind();
    }
protected:
};

#endif /* BufferObject_hpp */
