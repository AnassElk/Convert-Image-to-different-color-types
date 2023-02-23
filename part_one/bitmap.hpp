/*
 *****************************************************************************
 *                                                                           *
 *                          Platform Independent                             *
 *                    Bitmap Image Reader Writer Library                     *
 *                                                                           *
 * Author: Arash Partow - 2002                                               *
 * Copyright notice:                                                         *
 * Free use of the Platform Independent Bitmap Image Reader Writer Library   *
 * is permitted under the guidelines and in accordance with the most current *
 * version of the MIT License.                                               *
 * http://www.opensource.org/licenses/MIT                                    *
 *                                                                           *
 *****************************************************************************
*/

#ifndef TP3_BITMAP_HPP
#define TP3_BITMAP_HPP

#include <cstring>
#include <fstream>
#include <iostream>
#include "Pixel.h"

namespace bitmap {
    struct RGBQUAD
    {
        unsigned char b;
        unsigned char g;
        unsigned char r;
        unsigned char reserved;
    };

    struct bitmap_information_header
    {
        unsigned int   size;
        unsigned int   width;
        unsigned int   height;
        unsigned short planes;
        unsigned short bit_count;
        unsigned int   compression;
        unsigned int   size_image;
        unsigned int   x_pels_per_meter;
        unsigned int   y_pels_per_meter;
        unsigned int   clr_used;
        unsigned int   clr_important;

        unsigned int struct_size() const
        {
            return sizeof(size) +
                sizeof(width) +
                sizeof(height) +
                sizeof(planes) +
                sizeof(bit_count) +
                sizeof(compression) +
                sizeof(size_image) +
                sizeof(x_pels_per_meter) +
                sizeof(y_pels_per_meter) +
                sizeof(clr_used) +
                sizeof(clr_important);
        }

        void clear()
        {
            std::memset(this, 0x00, sizeof(bitmap_information_header));
        }
    };

    struct bitmap_file_header
    {
        unsigned short type;
        unsigned int   size;
        unsigned short reserved1;
        unsigned short reserved2;
        unsigned int   off_bits;

        unsigned int struct_size() const
        {
            return sizeof(type) +
                sizeof(size) +
                sizeof(reserved1) +
                sizeof(reserved2) +
                sizeof(off_bits);
        }

        void clear()
        {
            std::memset(this, 0x00, sizeof(bitmap_file_header));
        }
    };

    inline bool big_endian()
    {
        unsigned int v = 0x01;

        return (1 != reinterpret_cast<char*>(&v)[0]);
    }

    template <typename T>
    inline void write_to_stream(std::ofstream& stream, const T& t)
    {
        stream.write(reinterpret_cast<const char*>(&t), sizeof(T));
    }

    inline unsigned short flip(const unsigned short& v)
    {
        return ((v >> 8) | (v << 8));
    }

    inline void write_bfh(std::ofstream& stream, const bitmap_file_header& bfh)
    {
        if (big_endian())
        {
            write_to_stream(stream, flip(bfh.type));
            write_to_stream(stream, flip(bfh.size));
            write_to_stream(stream, flip(bfh.reserved1));
            write_to_stream(stream, flip(bfh.reserved2));
            write_to_stream(stream, flip(bfh.off_bits));
        }
        else
        {
            write_to_stream(stream, bfh.type);
            write_to_stream(stream, bfh.size);
            write_to_stream(stream, bfh.reserved1);
            write_to_stream(stream, bfh.reserved2);
            write_to_stream(stream, bfh.off_bits);
        }
    }

    inline void write_bih(std::ofstream& stream, const bitmap_information_header& bih)
    {
        if (big_endian())
        {
            write_to_stream(stream, flip(bih.size));
            write_to_stream(stream, flip(bih.width));
            write_to_stream(stream, flip(bih.height));
            write_to_stream(stream, flip(bih.planes));
            write_to_stream(stream, flip(bih.bit_count));
            write_to_stream(stream, flip(bih.compression));
            write_to_stream(stream, flip(bih.size_image));
            write_to_stream(stream, flip(bih.x_pels_per_meter));
            write_to_stream(stream, flip(bih.y_pels_per_meter));
            write_to_stream(stream, flip(bih.clr_used));
            write_to_stream(stream, flip(bih.clr_important));
        }
        else
        {
            write_to_stream(stream, bih.size);
            write_to_stream(stream, bih.width);
            write_to_stream(stream, bih.height);
            write_to_stream(stream, bih.planes);
            write_to_stream(stream, bih.bit_count);
            write_to_stream(stream, bih.compression);
            write_to_stream(stream, bih.size_image);
            write_to_stream(stream, bih.x_pels_per_meter);
            write_to_stream(stream, bih.y_pels_per_meter);
            write_to_stream(stream, bih.clr_used);
            write_to_stream(stream, bih.clr_important);
        }
    }

    template <typename T>
    inline void read_from_stream(std::ifstream& stream, T& t)
    {
        stream.read(reinterpret_cast<char*>(&t), sizeof(T));
    }

    inline void read_bfh(std::ifstream& stream, bitmap_file_header& bfh)
    {
        read_from_stream(stream, bfh.type);
        read_from_stream(stream, bfh.size);
        read_from_stream(stream, bfh.reserved1);
        read_from_stream(stream, bfh.reserved2);
        read_from_stream(stream, bfh.off_bits);

        if (big_endian())
        {
            bfh.type = flip(bfh.type);
            bfh.size = flip(bfh.size);
            bfh.reserved1 = flip(bfh.reserved1);
            bfh.reserved2 = flip(bfh.reserved2);
            bfh.off_bits = flip(bfh.off_bits);
        }
    }

    inline void read_bih(std::ifstream& stream, bitmap_information_header& bih)
    {
        read_from_stream(stream, bih.size);
        read_from_stream(stream, bih.width);
        read_from_stream(stream, bih.height);
        read_from_stream(stream, bih.planes);
        read_from_stream(stream, bih.bit_count);
        read_from_stream(stream, bih.compression);
        read_from_stream(stream, bih.size_image);
        read_from_stream(stream, bih.x_pels_per_meter);
        read_from_stream(stream, bih.y_pels_per_meter);
        read_from_stream(stream, bih.clr_used);
        read_from_stream(stream, bih.clr_important);

        size_t size_buffer = bih.size - bih.struct_size();
        if (size_buffer > 0) {
            char* buffer = new char[size_buffer];
            stream.read(buffer, sizeof(char) * size_buffer);
            delete[] buffer;
        }

        if (big_endian())
        {
            bih.size = flip(bih.size);
            bih.width = flip(bih.width);
            bih.height = flip(bih.height);
            bih.planes = flip(bih.planes);
            bih.bit_count = flip(bih.bit_count);
            bih.compression = flip(bih.compression);
            bih.size_image = flip(bih.size_image);
            bih.x_pels_per_meter = flip(bih.x_pels_per_meter);
            bih.y_pels_per_meter = flip(bih.y_pels_per_meter);
            bih.clr_used = flip(bih.clr_used);
            bih.clr_important = flip(bih.clr_important);
        }
    }

    inline std::size_t file_size(const std::string& file_name)
    {
        std::ifstream file(file_name.c_str(), std::ios::in | std::ios::binary);
        if (!file) return 0;
        file.seekg(0, std::ios::end);
        return static_cast<std::size_t>(file.tellg());
    }
}
#endif // !TP3_BITMAP_HPP