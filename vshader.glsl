#version 330
in int gl_InstanceID;

uniform mat4 mvp_matrix;


layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aText;
layout (location = 2) in vec4 aNormal;
layout (location = 3) in vec4 aColor;
layout (location = 4) in mat4 aOffset;


out vec2 v_texcoord;
out vec4 v_normal;
out vec4 v_color;

//! [0]
void main()
{
    // Calculate vertex position in screen space

    gl_Position =  mvp_matrix * aOffset * vec4(aPos, 1.0) ;

    mat4 rot = aOffset;

    rot[3] = vec4(0,0,0,1);

    v_texcoord =  aText;
    v_normal = rot * aNormal;// * aNormal;
    v_color = aColor;
}
//! [0]
