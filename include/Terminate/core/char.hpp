/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source
// for more information.
/////////////////////////////////////////////

#ifndef TERMINATE_CHAR_HPP
#define TERMINATE_CHAR_HPP


#include <cstdint>


namespace Term
    {

    struct
    Color
        {
        typedef uint8_t
        component_t;

        component_t r,g,b;

        Color() = default;

        Color( component_t r_, component_t g_, component_t b_ ) :
            r(r_), g(g_), b(b_)
            {}

        static Color
        Black, White;
        };



    class
    Char
        {
        public:
            typedef uint8_t
            char_t;

            Char() = default;

            Char( char_t, uint8_t pal_i, Color, Color );

            Char( char_t, uint8_t pal_i=0 );

            char_t
            ASCII() const;

            Color
            PriColor() const;

            Color
            SecColor() const;

            Char&
            ASCII( char_t );

            Char&
            PriColor( Color );

            Char&
            SecColor( Color );
        private:
            union
                {
                char16_t wc;
                struct
                    {
                    char_t  c;
                    uint8_t pal_i;
                    };
                };

            Color priColor;
            Color secColor;
        };

    } // namespace Term

#endif //TERMINATE_CHAR_HPP
