#include <ft2build.h>
#include FT_FREETYPE_H

#include "shaders.h"

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#elif defined(_WIN32)
    #include <glad/glad.h>
#elif defined(__linux__)
    #include <glad/glad.h>
#else
    #error "unsupported platform!"
#endif

typedef struct {
    GLuint TextureID;   // ID handle of the glyph texture
    int Width, Height;  // Size of glyph
    int BearingX, BearingY; // Offset from baseline to left/top of glyph
    GLuint Advance;     // Offset to advance to next glyph
} Character;

Character Characters[128];

void initFreeType(const char* fontPath) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        fprintf(stderr, "ERROR::FREETYPE: Could not init FreeType Library\n");
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath, 0, &face)) {
        fprintf(stderr, "ERROR::FREETYPE: Failed to load font\n");
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48); // Set size to load glyphs as

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    // Load first 128 ASCII characters
    for (GLubyte c = 0; c < 128; c++) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            fprintf(stderr, "ERROR::FREETYPE: Failed to load Glyph\n");
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Store character information
        Characters[c] = (Character){
            texture,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            face->glyph->bitmap_left,
            face->glyph->bitmap_top,
            face->glyph->advance.x
        };
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

typedef struct {
    unsigned int vaoData, vboData, shaderData;
} textData;

textData initTextRendering() {
    unsigned int textVAO, textVBO;
    unsigned int shaderProgram;
    shaderProgram = createShaderProgram(textVertexShaderSource, textFragmentShaderSource);

    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);
    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    textData result;
    result.vaoData = textVAO;
    result.vboData = textVBO;
    result.shaderData = shaderProgram;

    return result;
}

// Function to render text
void renderText(textData data, const char* text, float x, float y, float scale, float color[3]) {
    glUseProgram(data.shaderData);
    glUniform3f(glGetUniformLocation(data.shaderData, "textColor"), color[0], color[1], color[2]);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(data.vaoData);

    // Iterate through all characters
    const char* c;
    for (c = text; *c; c++) {
        Character ch = Characters[*c];

        float xpos = x + ch.BearingX * scale;
        float ypos = y - (ch.Height - ch.BearingY) * scale;

        float w = ch.Width * scale;
        float h = ch.Height * scale;
        // Update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, data.vboData);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
