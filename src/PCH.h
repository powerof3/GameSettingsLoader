#pragma once

#include "RE/Oblivion.h"
#include "OBSE/OBSE.h"

#include <ClibUtil/simpleINI.hpp>

#ifdef NDEBUG
#	include <spdlog/sinks/basic_file_sink.h>
#else
#	include <spdlog/sinks/msvc_sink.h>
#endif

#include <xbyak/xbyak.h>

namespace ini = clib_util::ini;
namespace string = clib_util::string;
using namespace std::literals;

#include "Version.h"
