#version 330

uniform sampler2D texture;
in vec4 v_normal;
in vec4 v_color;
in vec2 v_texcoord;
in vec2 v_fragmentdepth;

out vec4 fragColor;

//! [0]
void main()
{
    // Set fragment color from texture
    vec4 lightDirection = normalize(vec4(1,2,3,0));

    float a = dot(lightDirection,normalize(v_normal));
    a = 0.5 + (a+1) / 2.4;

    fragColor = texture2D(texture, v_texcoord) * a * v_color;
}
//! [0]

