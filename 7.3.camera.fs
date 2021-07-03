#version 330 core
in vec4 outColor;
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 myColor;
uniform int startPos;
uniform int endPos;
uniform float blend;


void main()
{
        
    // FragColor = vec4(blend, 0.0, 0.0, 1.0);
    // FragColor = vec4(outColor.r, outColor.g, outColor.b, blend);
    FragColor = vec4(myColor, outColor.w);
}