#version 330 core
#extension GL_ARB_shading_language_420pack : enable

uniform sampler2D lights;
uniform sampler2D tex;

uniform vec4 cameraPos;
uniform int numlights;

out vec4 FragColor;

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

in VS_OUT{
	vec3 uv;
	vec3 norm;
	vec4 pos;
	mMaterial material;
}fs_in;

vec4 calculatePointLight(float diffuseStrength, float specularStrength,
						vec4 lightColor, vec4 lightPos, vec4 lightDir);

void main(void){
	if(fs_in.material.shadingType < 0.5){	//No Shading
		if(fs_in.material.has_texture > 0.5){
			FragColor = texture(tex, vec2(fs_in.uv.x, 1 - fs_in.uv.y));
		}
		else{
			FragColor = fs_in.material.color;
		}
	}
	else if(fs_in.material.shadingType > 0.5){	//Normal Shading
		for(int i = 0; i < numlights; i++){
			vec4 lightInfo = texelFetch(lights, ivec2(0, i), 0);
			if(lightInfo.r < 0.5) continue;
			
			vec4 lightColor = texelFetch(lights, ivec2(1, i), 0);
			vec4 lightPos = texelFetch(lights, ivec2(2, i), 0);
			vec4 lightDir = texelFetch(lights, ivec2(3, i), 0);
			
			if(lightInfo.g < 1.5){	//Point Loght
				FragColor += calculatePointLight(lightInfo.b, lightInfo.a, lightColor, lightPos, lightDir);
			}
			else{
				FragColor = vec4(0, 0, 0, 1);
				break;
			}
		}
		FragColor /= numlights;
	}
	
	vec4 Emissive = fs_in.material.emissive;
	FragColor += vec4(Emissive.rgb, 0);
}

vec4 calculatePointLight(float diffuseStrength, float specularStrength,
						vec4 lightColor, vec4 lightPos, vec4 lightDir){
	vec4 Ambient = fs_in.material.ambient;
	
	vec4 N = normalize(vec4(fs_in.norm, 0));
	vec4 L = normalize(lightPos - fs_in.pos);
	float dotNL = max(dot(N, L), 0);
	vec4 Diffuse = dotNL * lightColor * fs_in.material.color;
	
	vec4 V = normalize(cameraPos - fs_in.material.color);
	vec4 H = normalize(L + V);
	vec4 R = reflect(-L, N);
	float dotRV = max(dot(R, V), 0);
	float dotNH = max(dot(N, H), 0);
	vec4 Specular = pow(dotRV, fs_in.material.shininess) * lightColor * fs_in.material.specular;
	
	vec4 MaterialColor;
	if(fs_in.material.has_texture > 0.5){
		MaterialColor = texture(tex, vec2(fs_in.uv.x, 1 - fs_in.uv.y));
	}
	else{
		MaterialColor = fs_in.material.color;
	}
	
	return (Ambient + Diffuse * diffuseStrength + Specular * specularStrength) * MaterialColor;
}























