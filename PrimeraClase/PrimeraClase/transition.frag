#version 330 core
out vec4 FragColor;
in vec3 color;

in vec2 texCoord;
uniform sampler2D tex0;
uniform sampler2D tex1;

uniform float mixFactor;

void main()
{
  vec4 tex0Color = texture(tex0, texCoord);
  vec4 tex1Color = texture(tex1, texCoord);
  vec4 mixedColor = mix(tex0Color, tex1Color, mixFactor);
  FragColor = vec4(mixedColor.rgb, 1);
  
}