#pragma once

// Grim Lands Keeper is open source reimplementation of Dungeon Keeper II.

// Licensed under the MIT license. See LICENSE file in the project root for details.

#include "macro.h"
#include "version.h"

#pragma warning ( disable : 4351 ) // new behavior: elements of array will be default initialized
#pragma warning ( disable : 4201 ) // nonstandard extension used: nameless struct/union

#include <stdlib.h>

// stdlib
#include <math.h>
#include <stdarg.h>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <cctype>
#include <functional>
#include <thread>

#ifdef FS_EXPERIMENTAL
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#else
    #include <filesystem>
    namespace fs = std::filesystem;
#endif

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/glm.hpp>

// physics

// lib
#include "enum_utils.h"
#include "noncopyable.h"
#include "object_pool.h"
#include "string_utils.h"
#include "math_defs.h"
#include "math_utils.h"
#include "file_utils.h"
#include "path_utils.h"
#include "intrusive_list.h"
#include "json_document.h"