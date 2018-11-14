#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;
varying vec4 v_normal;
varying vec4 v_color;
varying vec2 v_texcoord;

//! [0]
void main()
{
    // Set fragment color from texture
    float a = (dot(vec4(0,2,1,0),v_normal)+1.0)*0.5;
    gl_FragColor = texture2D(texture, v_texcoord)*a*v_color;
}
//! [0]

