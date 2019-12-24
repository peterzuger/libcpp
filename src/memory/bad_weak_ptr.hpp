/**
 * @file   libcpp/src/memory/bad_weak_ptr.cpp
 * @author Peter Züger
 * @date   22.10.2019
 * @brief  std::bad_weak_ptr
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
#include <memory>

namespace std{
    const char* std::bad_weak_ptr::what()const noexcept{
        return "std::bad_weak_ptr";
    }
}
