#version 330

uniform mat4 mvp_matrix;

uniform int snow;
attribute vec4 a_position;
attribute vec2 a_texcoord;
attribute vec4 a_normal;
attribute vec4 a_color;

out vec2 v_texcoord;
out vec4 v_normal;
out vec4 v_color;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * a_position;

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord =  a_texcoord ;
    v_normal = a_normal;
    v_color = a_color;
}
//! [0]
