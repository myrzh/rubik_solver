// const char* vertexShaderSource = "#version 330 core\n"
//     "layout (location = 0) in vec3 position;\n"
//     "layout (location = 1) in vec3 color;\n"
//     "out vec3 ourColor;\n"
//     "void main()\n"
//     "{\n"
//     "gl_Position = vec4(position, 1.0);\n"
//     "ourColor = color;\n"
//     "}\0";

// const char* fragmentShaderSource = "#version 330 core\n"
//     "out vec4 color;\n"
//     "uniform vec4 ourColor;\n"
//     "void main()\n"
//     "{\n"
//     "color = ourColor;\n"
//     "}\n\0";

// const char* vertexShaderSource2 = "#version 330 core\n"
//     "layout(location = 0) in vec2 position;\n"
//     "layout(location = 1) in float offset;\n"
//     "void main()\n"
//     "{\n"
//     "gl_Position = vec4(position.x + offset, position.y, 0.0, 1.0);\n"
//     "}\0";

// const char* fragmentShaderSource2 = "#version 330 core\n"
//     "layout(location = 0) out vec4 color;\n"
//     "void main()\n"
//     "{\n"
//     "color = vec4(1.0, 1.0, 1.0, 1.0f);\n"
//     "}\n\0";

const char* vertexShaderInstanceSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos, 1.0);\n"
    "    ourColor = aColor;\n"
    "}";

const char* fragmentShaderInstanceSource = 
    "#version 330 core\n"
    "in vec3 ourColor;\n" 
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(ourColor, 1.0f);\n"
    "}";
