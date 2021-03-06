/**
 * @file   libcpp/src/new/new_handler.cpp
 * @author Peter Züger
 * @date   17.10.2019
 * @brief  std::get/set_new_handler
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
#include <new>
#include <__exchange>

namespace std{
    static new_handler __current_new_handler = nullptr;

    new_handler get_new_handler()noexcept{
        return __current_new_handler;
    }

    new_handler set_new_handler(new_handler new_p)noexcept{
        return std::exchange(__current_new_handler, new_p);
    }
}
