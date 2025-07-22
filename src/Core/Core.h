#pragma once

// Third Party Includes
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include <freetype/freetype.h>

#include <box2d/box2d.h>

// Standard Library Includes
#include <print>
#include <stacktrace>
#include <stdexcept>
#include <string_view>
#include <filesystem>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <format>
#include <vector>
#include <map>

// Created Classes
#include "Core/CoreTypes.h"
#include "Core/Log.h"
#include "Physics/3D/Environment.h"
#include "Models/ModelArray.h"

// Third Party Class
#include "stb_image.h"
