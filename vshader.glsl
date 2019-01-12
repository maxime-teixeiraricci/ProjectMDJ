#version 330
in int gl_InstanceID;

uniform mat4 mvp_matrix;

uniform int snow;
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


    //vec4 v = vec4((gl_InstanceID%100)/10,gl_InstanceID%10,gl_InstanceID/100,0);
    //vec4 v = aPos + vec4(aOffset,0);
    //gl_Position = (mvp_matrix * v);
    gl_Position =  mvp_matrix * aOffset * vec4(aPos, 1.0) ;
    //gl_Position = gl_Position + aOffset;
    //gl_Position = (mvp_matrix *  v);

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord =  aText;
    v_normal = aNormal;// * aNormal;
    v_color = aColor;
}
//! [0]
