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

- EBO(element buffer object) stores indices that OpenGL uses to decide what vertices to draw (indexed drawing)

- Uniforms are global

- Texture coordinates go to (0,0) to (1,1), same logic for screen coordinates but having zero as minimal

- Important coordinates system:
  1. Local (object) space
  2. World space
  3. View (eye) space
  4. Clip space
  5. Screen space

- To transform one space to another it's used matrix's (linear) transformations.

- Coordinates order: Local space =(Model matrix)> World space =(View matrix)> View space =(Projection matrix)> Clip space =(Viewport transform)> Screen space

- Local space is where the object beings in (generally (0, 0, 0)).

- World space is the coordinates of all vertices relative to a world. So we basically position any object with this, and a model matrix is used for that.

- Model matrix is a transformation matrix that translate, scales and/or rotates objects to place in the world at a location/orientation they belong to

- View (camera/eye) space is the result of transformation the world space coordinates to coordinates that are in front of the user's view. These combined transformations are generally stored inside a view matrix.

- At the end of each vertex shader run, OpenGL expects the coordinates to be within a specific range (-1.0, 1.0) and any coordinate that falls outside this range is clipped (discarded). To convert vertex coordinates from view to clip space it's used the projection matrix that specifies a range of coordinates. The projection matrix then transforms coordinates within this specified range to normalized device coordinates.

- This viewing box a projection matrix creates is called frustum and each coordinates that ends up inside this frustum will end up on the user's screen. At the end, a final operation in realized with the clip space coordinates, where x, y and z components of the position vectors are divided by the vectors homogeneous w. This step is performed automatically at the end of the vertex shader step

- The projection matrix can take two different forms, an orthographic projection matrix or perspective projection matrix

- $V_{clip} = M_{projection} * M_{view} * M_{model} * V_{local}$

- $LookAt =
\begin{bmatrix}
  R_{x} & R_{y} & R_{z} & 0\\
  U_{x} & U_{y} & U_{z} & 0\\
  R_{x} & R_{y} & R_{z} & 0\\
  0 & 0 & 0 & 1
\end{bmatrix} *
\begin{bmatrix}
  1 & 0 & 0 & -P_{x}\\
  0 & 1 & 0 & -P_{y}\\
  0 & 0 & 1 & -P_{z}\\
  0 & 0 & 0 & 1
\end{bmatrix}$, where R is the right vector, U is the up vector, D is the directional vector and P is the camera position vector
