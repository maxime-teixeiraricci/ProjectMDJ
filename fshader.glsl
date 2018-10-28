#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;
varying vec4 v_normal;
varying vec2 v_texcoord;

//! [0]
void main()
{
    // Set fragment color from texture
   gl_FragColor = texture2D(texture, v_texcoord)*(dot(vec4(0,0,1,0),v_normal)*0.5+0.5);
    //gl_FragColor = v_normal;
}
//! [0]

