/*
**	Author:		Martin Schwarz
**	Name:		mgf_global.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_INCLUDE
#define MGF_INCLUDE

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <memory>
#include <mutex>
#include <thread>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "lib/mlog.h"

#define MGF_LOG_FILE "log_mgf.txt"

enum renderer_enum{
	OPENGL_4_3 = 0,
	OPENGL_3_3 = 1,
	SOFTWARE = 2,
};

enum loader_flags_enum{
	LOAD_NOT_TO_GPU 	= 0b0000001,
	LOAD_TO_DATA 		= 0b0000010,
	LOAD_NO_INDICES 	= 0b0000100,
	LOAD_SWITCH_UP_ZY 	= 0b0001000,
	LOAD_NO_B_BOXES     = 0b0010000,
	LOAD_NO_INSTANCES   = 0b0100000,
};

enum camera_types_enum{
	CAMERA_FPS_EULER = 0,
	CAMERA_FREE_QUAT = 1,
	CAMERA_FPS_QUAT = 2,
	CAMERA_FOLLOW = 3,
};

namespace mgf{
	struct mgf_info;
	class window;
	class camera;
	class input;
	class shader_program;
	class mgf_data;
	class node;
	class mgf_node_model;
	class mgf_node_model_instance;
	class scene;
}

#endif








