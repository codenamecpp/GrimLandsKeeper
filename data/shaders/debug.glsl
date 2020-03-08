
//////////////////////////////////////////////////////////////////////////
#ifdef VERTEX_SHADER

// constants
uniform mat4 view_projection_matrix;

// attributes
in vec3 in_position0;
in vec4 in_color0;

// pass to fragment shader
out vec4 Color;

// entry point
void main() 
{
	Color = in_color0;

    gl_Position = view_projection_matrix * vec4(in_position0, 1.0f);
}

#endif

//////////////////////////////////////////////////////////////////////////
#ifdef FRAGMENT_SHADER

// passed from vertex shader
in vec4 Color;

// result
out vec4 FinalColor;

// entry point
void main() 
{
	FinalColor = Color;
}

#endif