#pragma once

#include <string>
#include <fstream>
#include <unordered_map>

#define SIZE 8
#define COMMENT "#"
#define GLOBAL "global"

std::ofstream file;
std::string current_section;
std::unordered_map<std::string, std::string> operators;

