#include "sprite_sheet.h"
#include "file_reader.h"
#include <cmath>



GUI::Sprite_Sheet:: Sprite_Sheet(const char* file_name, std::size_t _sprite_width, std::size_t _sprite_height)
: sprite_width{_sprite_width}
, sprite_height{_sprite_height}
{
    const Bitmap bitmap{file_name};

    const auto sprites_per_row = bitmap.get_image_width() / _sprite_width;
    const auto sprites_per_col = bitmap.get_image_height() / _sprite_height;
    const auto sprite_area = _sprite_width * _sprite_height;

    sprite_vector = {sprites_per_row * sprites_per_col, std::vector<std::uint32_t>(sprite_area, 0)};

    for(auto i = 0; i < sprite_vector.size(); ++i)
    {
        const auto row = i % sprites_per_col * _sprite_height;
        const auto column = std::floor(i / sprites_per_col) * sprite_area * sprites_per_col;
        
        for(auto j = 0; j < _sprite_width; ++j)
            for(auto k = 0; k < _sprite_height; ++k)
                sprite_vector[i][j + k * _sprite_width] = bitmap[(row+column)+j*bitmap.get_image_width()+k];
    }
}

const GUI::Sprite_Sheet::sheet_type& GUI::Sprite_Sheet::get_sprite_vector() const
{
    return sprite_vector;
}

std::size_t GUI::Sprite_Sheet::get_sprite_width() const
{
    return sprite_width;
}

std::size_t GUI::Sprite_Sheet::get_sprite_height() const
{
    return sprite_height;
}