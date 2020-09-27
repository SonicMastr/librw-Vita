const char *skin_vert_src =
"void main(\n"
"	float3 in_pos,\n"
"	float3 in_normal,\n"
"	float4 in_color,\n"
"	float2 in_tex0,\n"
"	float4 in_weights,\n"
"	float4 in_indices,\n"
"	out float4 v_color : COLOR,\n"
"	out float4 gl_Position : POSITION,\n"
"	out float2 v_tex0 : TEXCOORD0,\n"
"	out float v_fog : FOG,\n"
"	uniform float4x4 u_boneMatrices[64]\n"
")\n"
"{\n"
"	float3 SkinVertex = float3(0.0, 0.0, 0.0);\n"
"	float3 SkinNormal = float3(0.0, 0.0, 0.0);\n"
"	for(int i = 0; i < 4; i++){\n"
"		float3 temp = mul(u_boneMatrices[int(in_indices[i])], float4(in_pos, 1.0)).xyz;\n"
"		SkinVertex += temp * in_weights[i];\n"
"		temp = mul(float3x3(u_boneMatrices[int(in_indices[i])]), in_normal);\n"
"		SkinNormal += temp * in_weights[i];\n"
"	}\n"

"	float4 V = mul(u_world, float4(SkinVertex, 1.0));\n"
"	gl_Position = mul(mul(u_proj, u_view), V);\n"
"	float3 N = mul(float3x3(u_world), SkinNormal);\n"

"	v_tex0 = in_tex0;\n"

"	v_color = in_color;\n"
"	v_color.rgb += u_ambLight.rgb*surfAmbient;\n"
"	v_color.rgb += DoDynamicLight(V.xyz, N)*surfDiffuse;\n"
"	v_color = clamp(v_color, 0.0, 1.0);\n"
"	v_color *= u_matColor;\n"

"	v_fog = DoFog(gl_Position.z);\n"
"}\n";