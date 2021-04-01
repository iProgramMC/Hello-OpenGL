#ifndef RENDERER_HPP_INCLUDED
#define RENDERER_HPP_INCLUDED

#include <stdint.h>
struct Color {
    union {
        uint32_t rgba;
        uint8_t as_bytes[4];
        struct {
            uint8_t a,b,g,r;
        };
    };
};
typedef int TextureHandle; //! index in this array
TextureHandle LoadRGBA5551Texture (const uint16_t* data, int width, int height, bool smoothing = false);
void InitializeTextureTable ();
void PrepareGL();
void FinishGL();
void DrawTexturedQuad (TextureHandle handle, int x, int y, int w, int h, uint32_t color = 0xFFFFFFFF);

#endif // RENDERER_HPP_INCLUDED
