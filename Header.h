#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ToolKit/Typedef.h"
#include "ToolKit/ImgToolKit.h"
#include "ToolKit/FileToolKit.h"
#include "Log/Log.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "Engine/Core/ShaderProgram.h"
#include <functional>
#include "Engine/Core/Texture2D/Texture2D.h"

#define mat4(name) glm::mat4 name(1.0f);
#define LOG(...)  Log::printer(__VA_ARGS__)
#define VEC3_ZERO glm::vec3(0,0,0)