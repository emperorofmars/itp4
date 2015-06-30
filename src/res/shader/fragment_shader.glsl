#version 330 core

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
						vec4 lightColor, vec4 lightPos);

vec4 calculateSunLight(float diffuseStrength, float specularStrength,
						vec4 lightColor, vec4 lightDir);

vec4 calculateSpotLight(float diffuseStrength, float specularStrength,
						vec4 lightColor, vec4 lightPos, vec4 lightDir, float coneAngle);

void main(void){
	if(fs_in.material.shadingType < 0.5){	//No Shading
		if(fs_in.material.has_texture > 0.5){
			FragColor = texture(tex, vec2(fs_in.uv.x, 1 - fs_in.uv.y));
		}
		else{
			FragColor = fs_in.material.color;
		}
	}
	else if(fs_in.material.shadingType < 1.5){	//Normal Shading
		for(int i = 0; i < numlights; i++){
			vec4 lightInfo = texelFetch(lights, ivec2(0, i), 0);
			if(lightInfo.r < 0.5) continue;
			
			vec4 lightColor = texelFetch(lights, ivec2(1, i), 0);
			vec4 lightPos = texelFetch(lights, ivec2(2, i), 0);
			vec4 lightDir = texelFetch(lights, ivec2(3, i), 0);
			vec4 lightInfo2 = texelFetch(lights, ivec2(4, i), 0);
			
			if(lightInfo.g < 1.5){	//Point Loght
				FragColor += calculatePointLight(lightInfo.b, lightInfo.a, lightColor, lightPos);
			}
			else if(lightInfo.g < 2.5){	//Sun Light
				FragColor += calculateSunLight(lightInfo.b, lightInfo.a, lightColor, lightDir);
			}
			else if(lightInfo.g < 3.5){	//Sun Light
				FragColor += calculateSpotLight(lightInfo.b, lightInfo.a, lightColor, lightPos, lightDir, lightInfo2.r);
			}
			else{
				//nothing
			}
		}
	}
	else{
		//nothing
	}
	
	vec4 Emissive = fs_in.material.emissive;
	vec4 Ambient = fs_in.material.ambient;
	FragColor += vec4(Ambient.rgb, 0);
	FragColor += vec4(Emissive.rgb, 0);
}

vec4 calculatePointLight(float diffuseStrength, float specularStrength,
						vec4 lightColor, vec4 lightPos)
{
	vec4 SurfaceNormal = normalize(vec4(fs_in.norm, 0));
	vec4 LightRay = normalize(lightPos - fs_in.pos);
	float Reflectance = max(dot(SurfaceNormal, LightRay), 0);
	vec4 Diffuse = Reflectance * lightColor * fs_in.material.color;
	
	vec4 CameraRay = normalize(cameraPos - fs_in.pos);
	vec4 LightReflection = reflect(-LightRay, SurfaceNormal);
	float dotRV = max(dot(LightReflection, CameraRay), 0);
	vec4 Specular = pow(dotRV, fs_in.material.shininess) * lightColor * fs_in.material.specular;
	
	vec4 MaterialColor;
	if(fs_in.material.has_texture > 0.5){
		MaterialColor = texture(tex, vec2(fs_in.uv.x, 1 - fs_in.uv.y));
	}
	else{
		MaterialColor = fs_in.material.color;
	}
	
	return vec4((Diffuse * diffuseStrength + Specular * specularStrength).rgb, 1) * MaterialColor;
}

vec4 calculateSunLight(float diffuseStrength, float specularStrength,
						vec4 lightColor, vec4 lightDir)
{
	vec4 SurfaceNormal = normalize(vec4(fs_in.norm, 0));
	vec4 LightRay = normalize(-lightDir);
	float Reflectance = max(dot(SurfaceNormal, LightRay), 0);
	vec4 Diffuse = Reflectance * lightColor * fs_in.material.color;
	
	vec4 CameraRay = normalize(cameraPos - fs_in.pos);
	vec4 LightReflection = reflect(-LightRay, SurfaceNormal);
	float dotRV = max(dot(LightReflection, CameraRay), 0);
	vec4 Specular = pow(dotRV, fs_in.material.shininess) * lightColor * fs_in.material.specular;
	
	vec4 MaterialColor;
	if(fs_in.material.has_texture > 0.5){
		MaterialColor = texture(tex, vec2(fs_in.uv.x, 1 - fs_in.uv.y));
	}
	else{
		MaterialColor = fs_in.material.color;
	}
	
	return vec4((Diffuse * diffuseStrength + Specular * specularStrength).rgb, 1) * MaterialColor;
}

vec4 calculateSpotLight(float diffuseStrength, float specularStrength,
						vec4 lightColor, vec4 lightPos, vec4 lightDir, float coneAngle)
{
	vec4 SurfaceNormal = normalize(vec4(fs_in.norm, 0));
	vec4 LightRay = normalize(lightPos - fs_in.pos);
	float Angle = degrees(acos(dot(normalize(-LightRay), normalize(lightDir))));
	if(Angle > coneAngle){
		return vec4(0, 0, 0, 0);
	}
	float Reflectance = max(dot(SurfaceNormal, LightRay), 0);
	vec4 Diffuse = Reflectance * lightColor * fs_in.material.color;
	
	vec4 CameraRay = normalize(cameraPos - fs_in.pos);
	vec4 LightReflection = reflect(-LightRay, SurfaceNormal);
	float dotRV = max(dot(LightReflection, CameraRay), 0);
	vec4 Specular = pow(dotRV, fs_in.material.shininess) * lightColor * fs_in.material.specular;
	
	vec4 MaterialColor;
	if(fs_in.material.has_texture > 0.5){
		MaterialColor = texture(tex, vec2(fs_in.uv.x, 1 - fs_in.uv.y));
	}
	else{
		MaterialColor = fs_in.material.color;
	}
	
	return vec4((Diffuse * diffuseStrength + Specular * specularStrength).rgb, 1) * MaterialColor;
}





















