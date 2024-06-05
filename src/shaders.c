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
    "void main() {\n"
    "    FragColor = vec4(ourColor, 1.0f);\n"
    "}";
