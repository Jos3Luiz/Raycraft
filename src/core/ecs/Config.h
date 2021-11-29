#pragma once

using EntityID = unsigned int;
using ComponentID = unsigned int;
using ComponentType = unsigned char;

constexpr EntityID MAX_ENTITIES = 50000;
constexpr ComponentType MAX_COMPONENTS_TYPE = 32;
constexpr ComponentType MAX_SYSTEMS = 32;