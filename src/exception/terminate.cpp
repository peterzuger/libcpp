/**
 * @file   libcpp/src/exception/terminate.cpp
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
#include <cstdlib>
#include <__exchange>

namespace std{
    static terminate_handler __current_terminate_handler;

    terminate_handler get_terminate()noexcept{
        return __current_terminate_handler;
    }

    terminate_handler set_terminate(terminate_handler f)noexcept{
        return std::exchange(__current_terminate_handler, f);
    }

    [[noreturn]] void terminate()noexcept{
        (*get_terminate())();
        std::abort();
    }
}
