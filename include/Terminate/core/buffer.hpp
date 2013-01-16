/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source
// for more information.
/////////////////////////////////////////////

#ifndef TERMINATE_CHARBUFFER_HPP
#define TERMINATE_CHARBUFFER_HPP

#include <cstdlib>
#include <memory>
#include "char.hpp"


namespace Term
    {

    class
    Buffer
        {
        public:
            virtual size_t
            Width() const = 0;

            virtual size_t
            Height() const = 0;

            virtual Char
            Get( size_t x, size_t y ) const = 0;

            virtual void
            Clear() = 0;

            virtual void
            ClearChar( Char ) = 0;

            virtual void
            Put( size_t x, size_t y, Char ) = 0;

            virtual void
            Scroll( int rows, int cols=0 ) = 0;

            virtual void
            Copy( const Buffer&, int dx, int dy,
                int sx, int sy, size_t sw, size_t sh ) = 0;

            virtual void
            Copy( const Buffer& ) = 0;
        };


    } // namespace Term

#endif //TERMINATE_CHARBUFFER_HPP
