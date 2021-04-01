#include <GL/gl.h>
#include <GL/glext.h>
#include "Renderer.hpp"
#include "Main.hpp"

#define MaxTextureCount 256 //! Increase if necessary

GLuint g_textureIDs[MaxTextureCount];
int g_texturesLoadedCurrently;

TextureHandle LoadRGBA5551Texture (const uint16_t* data, int width, int height, bool smoothing) {
    //! note: width&height must be powers of 2
    TextureHandle handle = g_texturesLoadedCurrently++;
    //! load the texture itself
    glBindTexture (GL_TEXTURE_2D, g_textureIDs[handle]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smoothing ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smoothing ? GL_LINEAR : GL_NEAREST);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB5_A1, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, data);
    glBindTexture (GL_TEXTURE_2D, 0);

    return handle;
}

void InitializeTextureTable () {
    glGenTextures (MaxTextureCount, &g_textureIDs[0]);
}

void PrepareGL() {
    glClearColor(0.1f, 0.4f, 0.6f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //match projection to window resolution (could be in reshape callback)
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, GetScreenSizeX(), GetScreenSizeY(), 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();
    glDisable(GL_LIGHTING);

    glColor3f(1,1,1);
}

void FinishGL () {
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void DrawTexturedQuad (TextureHandle handle, int x, int y, int w, int h, uint32_t color)
{
    int x2 = x + w;
    int y2 = y + w;
    //! Setup vertex coords
    int vx[4], vy[4];
    vx[0]=x; vy[0]=y;
    vx[1]=x; vy[1]=y2;
    vx[2]=x2;vy[2]=y2;
    vx[3]=x2;vy[3]=y;
    //! Setup texture UV coords
    float tx[4],ty[4];
    tx[0]=0,ty[0]=0;
    tx[1]=0,ty[1]=1;
    tx[2]=1,ty[2]=1;
    tx[3]=1,ty[3]=0;
    //! Setup color
    Color col;
    col.rgba = color;
    glColor4ub ((GLubyte)col.r, (GLubyte)col.g, (GLubyte)col.b, (GLubyte)col.a);
    //! Load texture
    glBindTexture(GL_TEXTURE_2D, g_textureIDs[handle]);
    glEnable (GL_TEXTURE_2D);
    //! Actually draw the quad itself
    glBegin(GL_QUADS);
    //! Each of the vertices
    for (int i=0; i<4; i++) {
        glTexCoord2f(tx[i],ty[i]);
        glVertex2i (vx[i], vy[i]);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void DrawQuad (int x, int y, int w, int h, Color* colors)
{
    int x2 = x + w;
    int y2 = y + w;
    float vx[4], vy[4];
    vx[0]=x; vy[0]=y;
    vx[1]=x; vy[1]=y2;
    vx[2]=x2;vy[2]=y2;
    vx[3]=x2;vy[3]=y;
    glBegin(GL_QUADS);
    for (int i=0; i<4; i++) {
        glColor3ub((GLubyte)colors[i].r,(GLubyte)colors[i].g,(GLubyte)colors[i].b);
        glVertex2f (vx[i], vy[i]);
    }
    glEnd();
}
