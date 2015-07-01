#version 330 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec3 uv;

struct mMaterial{
	vec4 color;
	vec4 specular;
	vec4 ambient;
	vec4 emissive;
	float alpha;
	float shininess;
	float has_texture;
	float shadingType;
};

out VS_OUT{
	vec3 uv;
	vec3 norm;
	vec4 pos;
	mMaterial material;
}vs_out;

uniform mat4 m_mat;
uniform mat4 vp_mat;
uniform mat4 norm_mat;
uniform mMaterial material;

void main(void){
	vs_out.pos = m_mat * pos;
	gl_Position = vp_mat * vs_out.pos;
	vs_out.norm = (norm_mat * vec4(norm, 0.0)).xyz;
	vs_out.uv = uv;
	vs_out.material = material;
}