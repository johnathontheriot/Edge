# Edge
An experimental game engine written in C++.

# What is it?
Edge is an experimental game engine designed with developers in mind. One of the common complaints I hear about graphics developement is that setting up an environment and wiring up boiler plate code takes too much time, and in the end results in a spaghetti mess for anyone who hasnt seen a structured example before. This engine will aim to ease some of these conserns, attempting to provide modern design examples, but also keeping code readable for newcomers.

# But...why?
Short answer, why not? The idea for this engine spawned from my experience using Berkeley's [NachOS](https://homes.cs.washington.edu/~tom/nachos/) as an undergrad. I thought, "Now imagine if there were an environment like this for graphics...a place where I can break things without any consequences." Thus, the idea was born.

# Hasn't this been done?
Of course, but how am I supposed to learn how to build a good wheel if I don't start from scratch?

## Warning: Everything beyond this point is subject to change until a final release is created.

# So how do I make a game?

Good question! The answer is, you can't...yet. But here are some things you _can_ do.

### Create a Scene

Scenes should be fairly easy to understand - they encapsulate all objects in a single view space defined by the user. You can think of them as levels. Scenes are tracked by name by the system, and while you are allowed to have multiple active scenes at the moment, support for drawing them simultaniously is still being fleshed out.

```c++
    Scene * scene = new Scene(system->getActiveWindow());
    SceneManager::getInstance()->scenes->insert({"main", scene});
```

__Note:__ This will change in the future to something like:

```c++
  Scene * mainScene = SceneManager::getInstance()->createScene("main");
```

### Add an Object to the Scene

Easiest peasiest (this will change to `scene->addObject`)

```c++
    scene->objects->insert({"myTextBox", new TextBox("Hey, you can add text now!")});
```

`TextBox` is a bit of a special case. Most of the time, you'll want to create a new `GLObject`. The constructor of `GLObject` accepts a `Geometry`, which is a sharable mesh definition. You can create a `Cube` or `RectangularPlane` like so:

```c++
    scene->objects->insert({"myCube", Cube::getInstance()})
```

Some `Geometry` objects allow access to their constructors. This allows the user to define certain properties of the mesh that mark it as unsharable. This is the case for `RectangularPlane`. Let's say you wanted a grid like mesh rather than a giant 2-triangle plane:

```c++
    scene=>objects->insert({"myTesPlane", new RectangularPlane(2, 2)});
```

This will divide the plane into 2 rows and 2 columns.

### Add a Shader to an Object

Now that you have an object, let's add some color to it with a shader

```
    ShaderProgram * shader = ShaderManager::createShaderProgram("solid_red.vertex.glsl", "solid_red.fragment.glsl");
```

The `ShaderProgram` constructor takes in two paths. The path order is the same as the order shaders appear in the pipeline (we currently only support the vertex and fragment shader, but geometry and tesselation are coming in the future). So in this case the first path is to our vertex shader and the second is to our fragment.

### Bind Variables to Shaders

Variable bindings in shaders are necessary with every draw, so we give access to that stage in the pipeline through a lambda function. This lambda will give you access to the `GLObject` that the `Shader` is bound to as well as the `Scene` that the object sits in

```c++
    shader->bindVars = [](GLObject* obj, Scene* scene) {
        obj->shader->bind4fMatrix("modelTransform", obj->getModelMatrix());
        obj->shader->bindTexture("tex", obj->textures->at(0), GL_TEXTURE0, 0);
    };
```

This example shows how to bind both a `Matrix` and `Texture` to the shader - nothing too complicated but this is likely to become more automated in the future. Speaking of `Texture`s...
