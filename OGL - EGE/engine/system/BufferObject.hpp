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
    
    virtual void attach() {
        glEnableVertexAttribArray(this->location);
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
        glVertexAttribPointer(this->location, this->dimension, this->type, GL_FALSE, 0, (void*)0);
    }
    
    virtual void detach() {
        glDisableVertexAttribArray(this->location);

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


template <class BufferType>
class DivisingBufferObject: public GLBufferObject<BufferType> {
private:
    int divisions;
public:
    DivisingBufferObject(int divisions, GLuint location, int dimension, GLenum type, int size, BufferType * data): GLBufferObject<BufferType>(location, dimension, type, size, data) {
        this->divisions = divisions;
    }
    
    virtual void attach() {
        GLBufferObject<BufferType>::attach();
        glVertexAttribDivisor(this->location, this->divisions);
    }

};

#endif /* BufferObject_hpp */
