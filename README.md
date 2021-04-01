# Hello, OpenGL
I'm trying out OpenGL, let's go. Note that this is a **barebones** project, as such it does not include any actual gameplay and you will have to add it yourself.

### Graphics
Graphics?! Well I don't have much graphics wrapper functions to show you, there's DrawQuad which takes 4 colors (`struct Color`), and there's DrawTexturedQuad which takes in a `TextureHandle` (just an index into an array of `GLuint`s). I haven't even implemented functions to draw text yet, sadly.

### Build
To build, you need to either:
- Use the provided Code::Blocks project
- Use g++ with -lopengl32, -lglu32 and -lgdi32 (This is a windows only project, might try it out on Linux at some point though)

### Sprites
The sprites you see are taken from Mario 64, because I can't load png files yet. The data is stored as "RGBA5551", the native format for N64.

### Why?
I was just bored, and I'm testing out some new stuff :)
