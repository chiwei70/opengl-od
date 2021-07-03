#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture2;

void main()
{
	// FragColor = texture(texture2, TexCoord);
	FragColor = texture(texture2, TexCoord);// *0.7 + texture(texture2, TexCoord) * 0.3 * vec4(ourColor, 1.0);
}