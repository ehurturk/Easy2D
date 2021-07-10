/*
 * Created by Emir Hurturk on 8.07.2021.
 * This is the *PUBLIC* API Header file for the Easy2D engine, which contains all of its functionality.
 * This header file includes all the header files this project uses, and this header file must be included to access all of the engine's functionality.
 * This header file is not included within any other header files this engine uses.
 * The engine is written using C99, but can be used within C++ projects as well.
 *
 * By default, engine's debug output is disabled using a definition.
 * However, if you want to enable engine debug output, you MUST #define EZ_DEBUG_ENABLED
 * BEFORE including the engine.
 *
 * Example:
 * #define EZ_DEBUG_ENABLED
 * #include <Easy2D/easy2d.h>
 *
 * Version 1.0.0:
 *  - Implemented Core Features (by Emir Hurturk)
*/

#ifndef EASY2D_H
#define EASY2D_H


#include "window.h"
#include "log.h"
#include "application.h"
#include "sprite.h"
#include "shader.h"
#include "texture.h"

#endif//EASY2D_H