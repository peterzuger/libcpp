/**
 * @file   terminate.cpp
 * @author Peter Züger
 * @date   02.05.2019
 * @brief  std::terminate implementation
 *
 * This file is part of libcpp (https://gitlab.com/peterzuger/libcpp).
 * Copyright (c) 2019 Peter Züger.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <exception>
#include <cstddef>
#include <cstdlib>

static std::terminate_handler __handler;

std::terminate_handler get_terminate()noexcept{
    return __handler;
}

std::terminate_handler set_terminate(std::terminate_handler f)noexcept{
    std::terminate_handler tmp = __handler;
    __handler = f;
    return tmp;
}

[[noreturn]] void terminate()noexcept{
    (*get_terminate())();
    std::abort();
}
