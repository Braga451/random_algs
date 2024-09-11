# Part 1 notes

- Technically, OpenGL is merely a specification, developed and maintained by khronos.org

- The OpenGL specification specifies exactly what the result/output of each function should be and how it should perform

- Most implementations of OpenGL are built by graphics card manufactures

- OpenGL is by itself a large state machine

- An object in OpenGL is a collection of options that represents a subset of OpenGL's state

- GLFW can be used to create an OpenGL context, define a window parameters, and handle user input

- The major part of OpenGL work is to convert 3D coordinates to 2D pixels that fit on screen. This process is manage by process pipeline

- The graphics pipeline can be divided into several steps and, because the parallel nature of this process, graphics cards of today have thousand of small processing cores to quickly process your data within the graphics pipeline, where each one of small programs that run in those cores are called shaders.

- Shaders are written in OpenGL Shading Language (GLSL)

- We can crate vertex, geometry and fragment shaders

- A vertex is a collection of data per 3D coordinate. This vertex's data is represented using vertex attributes

- The vertex shader takes as input a single vertex and his main purpose is to transform 3D coordinates into different 3D coordinates

- The primitive assembly stage takes as input all the vertices from the vertex shader that form a primitive and assembles all the points in the primitive shape given. The output is passed to the geometry shader

- The geometry shader takes as input a collection of all vertices that form a primitive and has the ability to generate other shapes by emitting new vertices to form new (or other) primitive(s). The output is then passed on the rasterization stage, where it maps the resulting primitive(s) to the corresponding pixels on the final screen, resulting in fragment for the fragment shader to use

- Before the fragment shader run, all fragment that are outside our views are discarted (clipping)

- The main purpose of fragment shader is to calculate the final color of a pixel

- The final object will then pass to through one more stage called alpha test and blending test, where the corresponding depth (and stencil) value of the fragment and uses those to check if the resulting fragment is in front or behind other objects and should be discarded accordingly. The stage also checks for alpha values (alpha values define the opacity of an object) and blends the objects accordingly.

- Coordinates must be in NDC (normalized device coordinates)

- VBO(vertex buffer objects) can store a large number of vertices in GPU's memory

-
