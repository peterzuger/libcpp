/**
 * @file   libcpp/src/new/new.cpp
 * @author Peter Züger
 * @date   14.12.2018
 * @brief  new/delete implementation
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
#include <cstdlib>
#include <exception>

void* operator new(std::size_t size){
    if(size == 0)
        size = 1;
    void* p;
    while((p = std::malloc(size)) == 0){
        std::new_handler nh = std::get_new_handler();
        if(nh){
            nh();
        }else{
#if defined(__cpp_exceptions)
            throw std::bad_alloc();
#else
            std::terminate();
#endif
        }
    }
    return p;
}

void* operator new(std::size_t size, std::align_val_t alignment){
    if(size == 0)
        size = 1;
    void* p;
    while((p = std::aligned_alloc(static_cast<std::size_t>(alignment), size)) == 0){
        std::new_handler nh = std::get_new_handler();
        if(nh){
            nh();
        }else{
#if defined(__cpp_exceptions)
            throw std::bad_alloc();
#else
            std::terminate();
#endif
        }
    }
    return p;
}

void* operator new(std::size_t size, const std::nothrow_t&)noexcept{
    if(size == 0)
        size = 1;
    void* p;
    while((p = std::malloc(size)) == 0){
        std::new_handler nh = std::get_new_handler();
        if(nh){
            nh();
        }else{
            return nullptr;
        }
    }
    return p;
}

void* operator new(std::size_t size, std::align_val_t alignment, const std::nothrow_t&)noexcept{
    if(size == 0)
        size = 1;
    void* p;
    while((p = std::aligned_alloc(static_cast<std::size_t>(alignment), size)) == 0){
        std::new_handler nh = std::get_new_handler();
        if(nh){
            nh();
        }else{
            return nullptr;
        }
    }
    return p;
}

void operator delete(void* ptr)noexcept{
    std::free(ptr);
}

void operator delete(void* ptr, std::size_t)noexcept{
    std::free(ptr);
}

void operator delete(void* ptr, std::align_val_t)noexcept{
    std::free(ptr);
}

void operator delete(void* ptr, std::size_t, std::align_val_t)noexcept{
    std::free(ptr);
}

void operator delete(void* ptr, const std::nothrow_t&)noexcept{
    std::free(ptr);
}

void operator delete(void* ptr, std::align_val_t, const std::nothrow_t&)noexcept{
    std::free(ptr);
}

void* operator new[](std::size_t size){
    return ::operator new(size);
}

void* operator new[](std::size_t size, std::align_val_t alignment){
    return ::operator new(size, alignment);
}

void* operator new[](std::size_t size, const std::nothrow_t&)noexcept{
    return ::operator new(size, std::nothrow);
}

void* operator new[](std::size_t size, std::align_val_t alignment, const std::nothrow_t&)noexcept{
    return ::operator new(size, alignment, std::nothrow);
}

void operator delete[](void* ptr)noexcept{
    std::free(ptr);
}

void operator delete[](void* ptr, std::size_t)noexcept{
    std::free(ptr);
}

void operator delete[](void* ptr, std::align_val_t)noexcept{
    std::free(ptr);
}

void operator delete[](void* ptr, std::size_t, std::align_val_t)noexcept{
    std::free(ptr);
}

void operator delete[](void* ptr, const std::nothrow_t&)noexcept{
    std::free(ptr);
}

void operator delete[](void* ptr, std::align_val_t, const std::nothrow_t&)noexcept{
    std::free(ptr);
}

void* operator new (std::size_t, void* ptr)noexcept{
    return ptr;
}

void* operator new[](std::size_t, void* ptr)noexcept{
    return ptr;
}

void operator delete (void*, void*)noexcept{}
void operator delete[](void*, void*)noexcept{}
