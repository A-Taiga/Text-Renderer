//
// Created by anthony on 12/23/24.
//


#include "file_reader.h"
#include <fstream>
#include <iostream>

GUI::Bitmap::Bitmap(const char* file_name)
{
    std::ifstream file(file_name);

    if (!file.is_open())
    {
        std::cerr << "File could not be opened" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    if(header.type != 0x4D42)
    {
        std::cerr << file_name << " is not a bitmap image" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    file.read(reinterpret_cast<char*>(&info), sizeof(info));

    if (info.bits_per_pixel < 32)
    {
        std::cerr << file_name << " must have 32 bits per pixel" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    const auto width = info.width;
    const auto height = info.height;

    pixels = std::vector<std::uint32_t>(width*height);
    file.seekg(header.offset, std::ios::beg);

    // read in bitmap backgwards because that's how the pixels are stored.
    for(auto i = height-1; i >= 0; --i)
        for(auto j = 0; j < width; ++j)
            file.read(reinterpret_cast<char*>(&pixels[i * width + j]), sizeof(std::uint32_t));

    file.close();
}

std::size_t GUI::Bitmap::size() const
{
    return pixels.size();
}

std::uint32_t GUI::Bitmap::operator[](const std::size_t index) const
{
    try
    {
        return pixels.at(index);
    }
    catch (std::out_of_range& error)
    {
        std::cout << error.what() << " in: " << __PRETTY_FUNCTION__ << '\n';
    }
    return 0;
}


// returns pixels per row
std::int32_t GUI::Bitmap::get_image_width() const
{
    return info.width;
}

// returns pixels per column
std::int32_t GUI::Bitmap::get_image_height() const
{
    return info.height;
}


