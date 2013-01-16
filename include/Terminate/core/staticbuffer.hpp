/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source
// for more information.
/////////////////////////////////////////////

#ifndef TERMINATE_STATICBUFFER_HPP
#define TERMINATE_STATICBUFFER_HPP

#include "buffer.hpp"

namespace Term
    {


    class
    StaticBuffer :
        public Buffer
        {
        public:
            StaticBuffer( size_t width, size_t height );

            virtual size_t
            Width() const override;

            virtual size_t
            Height() const override;

            virtual Char
            Get( size_t x, size_t y ) const override;

            virtual void
            Clear() override;

            virtual void
            ClearChar( Char ) override;

            virtual void
            Put( size_t x, size_t y, Char ) override;

            virtual void
            Scroll( int rows, int cols=0 ) override;

            virtual void
            Copy( const Buffer&, int dx, int dy,
                int sx, int sy, size_t sw, size_t sh ) override;

            virtual void
            Copy( const Buffer& ) override;

        private:
            typedef std::unique_ptr<Char[]>
            BufferData;

            size_t      width, height;
            Char        clearChar;
            BufferData  buffer;
        };

    } // namespace Term
#endif //TERMINATE_STATICBUFFER_HPP
