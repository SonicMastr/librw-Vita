const char *default_vert_src =
"void main(\n"
"	float3 in_pos,\n"
"	float3 in_normal,\n"
"	float4 in_color,\n"
"	float2 in_tex0,\n"
"	out float4 gl_Position : POSITION,\n"
"	out float4 v_color : COLOR0,\n"
"	out float2 v_tex0 : TEXCOORD0,\n"
"	out float v_fog : FOG,\n"
"	uniform float4x4 u_world,\n"
"	uniform float4x4 u_proj,\n"
"	uniform float4x4 u_view,\n"
"	uniform float4 u_ambLight,\n"
"	uniform float4 u_surfProps,\n"
"	uniform float4 u_fogData,\n"
"	uniform float4 u_matColor,\n"
"	uniform float4 u_lightParams[MAX_LIGHTS],\n"
"	uniform float4 u_lightDirection[MAX_LIGHTS],\n"
"	uniform float4 u_lightColor[MAX_LIGHTS]\n"
") {\n"
"	float4 V = mul(float4(in_pos, 1.0), u_world);\n"
"	gl_Position = mul(mul(V, u_view), u_proj);\n"
"	float3 N = mul(in_normal, float3x3(u_world));\n"

"	v_tex0 = in_tex0;\n"

"	v_color = in_color;\n"
"	v_color.rgb += u_ambLight.rgb*surfAmbient;\n"
"	float3 color = float3(0.0, 0.0, 0.0);\n"
"	for(int i = 0; i < MAX_LIGHTS; i++){\n"
"		if(u_lightParams[i].x == 0.0)\n"
"			break;\n"
"		if(u_lightParams[i].x == 1.0){\n"
"			float l = max(0.0, dot(N, -u_lightDirection[i].xyz));\n"
"			color += l*u_lightColor[i].rgb;\n"
"		}\n"
"	}\n"
"	v_color.rgb += color*surfDiffuse;\n"
"	v_color = clamp(v_color, 0.0, 1.0);\n"
"	v_color *= u_matColor;\n"

"	v_fog = DoFog(gl_Position.w, u_fogData);\n"
"}\n";
