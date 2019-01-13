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
    float a = dot(normalize(vec4(0,2,1,0)),normalize(v_normal));
    a = 0.1+(a+1)/2.0;
    //a = 0.0;
    fragColor = texture2D(texture, v_texcoord)*a*v_color*gl_FragCoord.z;
    //fragColor = vec4(vec3(gl_FragCoord.z), 1.0);
    //v_fragmentdepth = gl_FragCoord.z;
}
//! [0]

