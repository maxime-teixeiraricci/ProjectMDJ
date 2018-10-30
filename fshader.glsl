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
    float a =dot(vec4(0,0,1,0),v_normal);
   //gl_FragColor = texture2D(texture, v_texcoord)*a*a*v_color;
    //gl_FragColor = v_normal;
    gl_FragColor = texture2D(texture, v_texcoord)* (dot(vec4(0,0,1,0),v_normal)*0.5+0.5);//+vec4(1,1,1,0)*0.25*v_color;
}
//! [0]

