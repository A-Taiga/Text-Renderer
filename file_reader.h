//
// Created by anthony on 12/23/24.
//

#ifndef FILE_READER_H
#define FILE_READER_H

#include <cstdint>
#include <vector>
#include <cstring>


static_assert(true); // this gets clangD to shut up about pragma pack(push,1) not having a terminator (idk why)
#pragma pack(push, 1)
struct File_Header
{
    std::uint16_t type;
    std::uint32_t size;
    std::uint16_t reserved_1;
    std::uint16_t reserved_2;
    std::uint32_t offset;
    File_Header(){std::memset(static_cast<void*>(this), 0, sizeof(*this));}
};

struct Bitmap_Info
{
    std::uint32_t   size;
    std::int32_t    width;
    std::int32_t    height;
    std::uint16_t   color_planes;
    std::uint16_t   bits_per_pixel;
    std::uint32_t   compression_method;
    std::uint32_t   raw_image_size;
    std::int32_t    horizontal_resolution;
    std::int32_t    vertical_resolution;
    std::uint32_t   color_palette_size;
    std::uint32_t   important_color_size;
    Bitmap_Info(){std::memset(static_cast<void*>(this), 0, sizeof(*this));}
};
#pragma pack(pop)


namespace GUI
{
    class Bitmap
    {
    public:
        explicit Bitmap(const char* file_name);

        std::size_t size() const;

        std::uint32_t operator[](const std::size_t index) const noexcept;
       
        std::int32_t get_image_width() const;
        std::int32_t get_image_height() const;

    private:
        using pixel_vector = std::vector<std::uint32_t>;
        File_Header header;
        Bitmap_Info info;
        pixel_vector pixels;
    };
}

#endif //FILE_READER_H
