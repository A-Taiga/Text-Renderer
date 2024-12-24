//
// Created by anthony on 12/23/24.
//

#pragma once

#include <vector>
#include <cstdint>


namespace GUI
{
    class Sprite_Sheet
    {
    public:
        using sheet_type = std::vector<std::vector<std::uint32_t>>;
        Sprite_Sheet(const char* file_name, std::size_t _sprite_width, std::size_t _sprite_height);
        
        const sheet_type& get_sprite_vector() const;
        std::size_t get_sprite_width() const;
        std::size_t get_sprite_height() const;

    private:
        sheet_type sprite_vector;
        std::size_t sprite_width;
        std::size_t sprite_height;
    };
}

