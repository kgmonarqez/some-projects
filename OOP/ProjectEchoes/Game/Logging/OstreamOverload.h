#pragma once
#include <ostream>
#include "Logs/Log.h"

std::ostream& operator<<(std::ostream& f, const Log* Called_log);