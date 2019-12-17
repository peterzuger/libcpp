/**
 * @file   libcpp/src/typeinfo/bad_cast.cpp
 * @author Peter Züger
 * @date   08.05.2019
 * @brief  std::bad_cast
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
#include <typeinfo>

namespace std{
    const char* bad_cast::what()const noexcept{
        return "std::bad_cast";
    }
}
