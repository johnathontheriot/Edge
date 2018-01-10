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
