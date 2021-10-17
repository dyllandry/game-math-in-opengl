# Dependencies

This project requires glfw3 to be available somewhere in your system's C include directories, I think it is dynamically linked to.

# About <GLFW/glfw3.h>

_If you're using <GLFW/glfw3.h> how would you know to link with "glfw"?_

I think this command tells you: `pkg-config --cflags --libs glfw3`. So if you want to use glfw3 library, pkg-config outputs "-lglfw" which is what you should link with.

# About glad.c:

Since we don't know where our OS's opengl functions are at compile time, glad.c will create function pointers to your OS's opengl functions wherever they are located on your system.

