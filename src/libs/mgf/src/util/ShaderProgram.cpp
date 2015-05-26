/*
**	Author:		Martin Schwarz
**	Name:		ShaderProgram.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "ShaderProgram.h"

namespace mgf{

ShaderProgram::ShaderProgram(){
	mProgram = 0;
	memset(mLocations, 0, SHADER_LOC_SIZE);
}

ShaderProgram::ShaderProgram(std::vector<struct shader_to_programm> &shaders){
	mProgram = 0;
	memset(mLocations, 0, SHADER_LOC_SIZE);
	mShaders = shaders;
}

ShaderProgram::~ShaderProgram(){
	LOG_F_INFO(MGF_LOG_FILE, "closing shader_program");
	if(mProgram != 0) glDeleteProgram(mProgram);
	mProgram = 0;
	mShaders.clear();
}

void ShaderProgram::addShader(std::string sourcefile, GLenum shader_type){
	struct shader_to_programm s = {sourcefile, shader_type};
	mShaders.push_back(s);
	return;
}

GLuint ShaderProgram::getProgram(){
	return mProgram;
}

GLuint ShaderProgram::get(shader_loc_enum loc){
	return mLocations[loc];
}

int ShaderProgram::createProgram(){
    std::vector<GLuint> s;
	mProgram = 0;

    for(unsigned int i = 0; i < mShaders.size(); i++){
		s.push_back(createShader(mShaders[i].path, mShaders[i].type));
    }
    mProgram = glCreateProgram();
    for(unsigned int i = 0; i < s.size(); i++){
		glAttachShader(mProgram, s[i]);
    }
    glLinkProgram(mProgram);
    GLint compilesuccess = GL_FALSE;
    glGetProgramiv(mProgram,GL_LINK_STATUS, &compilesuccess);
    if(compilesuccess == GL_TRUE){
		LOG_F_INFO(MGF_LOG_FILE, "Program: ", mProgram, " compiled successfully");
    }
    else{
		LOG_F_ERROR(MGF_LOG_FILE, "Program: ", mProgram, " failed to compile!");
        printShaderLog(mProgram);
		glDeleteProgram(mProgram);
        mProgram = 0;
    }
    for(unsigned int i = 0; i < s.size(); i++){
		glDeleteShader(s[i]);
    }
    s.clear();
    mShaders.clear();

	if(mProgram == 0){
		LOG_F_ERROR(MGF_LOG_FILE, "Creating program failed");
		return -1;
	}

	mLocations[MATRIX_MODEL] = glGetUniformLocation(mProgram, _shader_matrix_model);
	mLocations[MATRIX_VP] = glGetUniformLocation(mProgram, _shader_matrix_view_perspective);
	mLocations[MATRIX_NORM] = glGetUniformLocation(mProgram, _shader_matrix_normals);
	mLocations[MATERIAL_COLOR_DIFFUSE] = glGetUniformLocation(mProgram, _shader_material_color_diffuse);
	mLocations[MATERIAL_ALPHA] = glGetUniformLocation(mProgram, _shader_material_alpha);
	mLocations[MATERIAL_HAS_TEXTURE] = glGetUniformLocation(mProgram, _shader_material_has_texture);

	return 0;
}

GLuint ShaderProgram::createShader(std::string &sourcefile, GLenum shader_type){
    GLuint shader = 0;
    std::ifstream input(sourcefile);
    std::string shader_string;
    if(input.is_open()){
        input.seekg(0, std::ios::end);
        shader_string.resize(input.tellg());
        input.seekg(0, std::ios::beg);
        input.read(&shader_string[0], shader_string.size());
        input.close();
    }
    else{
		LOG_F_ERROR(MGF_LOG_FILE, "Shader: ", sourcefile, " could not be opened!");
        return shader;
    }
    shader = glCreateShader(shader_type);
    const GLchar *shader_code = shader_string.c_str();
    glShaderSource(shader, 1, &shader_code, NULL);
    glCompileShader(shader);
    GLint compilesuccess = GL_FALSE;
    glGetShaderiv(shader,GL_COMPILE_STATUS, &compilesuccess);
    if(compilesuccess == GL_TRUE){
		LOG_F_INFO(MGF_LOG_FILE, "Shader: ", sourcefile, " compiled successfully");
    }
    else{
		LOG_F_ERROR(MGF_LOG_FILE, "Shader: ", sourcefile, " failed to compile!");
        printShaderLog(shader);
        glDeleteShader(shader);
        shader = 0;
    }
    return shader;
}

void ShaderProgram::setLocation(int loc, const std::string name){
	mLocations[loc] = glGetUniformLocation(mProgram, name.c_str());
}

void ShaderProgram::printShaderLog(GLuint shader){
	GLint log_length = 0;
	if(glIsShader(shader))
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
	else if(glIsProgram(shader))
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &log_length);
	else{
		LOG_F_WARNING(MGF_LOG_FILE, "printlog: Not a shader or a program");
		return;
	}

	char log[log_length];

	if(glIsShader(shader))
		glGetShaderInfoLog(shader, log_length, NULL, (GLchar *)log);
	else if(glIsProgram(shader))
		glGetProgramInfoLog(shader, log_length, NULL, (GLchar *)log);

	LOG_F_ERROR(MGF_LOG_FILE, "printlog: \n", log, "\n");
	return;
}

void ShaderProgram::use(){
	glUseProgram(mProgram);
	return;
}

} // mgf










