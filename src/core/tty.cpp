/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source
// for more information.
/////////////////////////////////////////////

#include "tty.hpp"



namespace Term
    {


    TTY::TTY( Buffer& buf ) :
        buffer(&buf),
        curs_x(0), curs_y(0),
        state(0),
        pri( 255,255,255 ),
        sec( 0,0,0 )
        {}


    TTY&
    TTY::Set( StateBit b, bool setTo )
        {
        if( setTo )
            state |= b;
        else
            state ^= b;
        return *this;
        }


    bool
    TTY::IsSet( StateBit b ) const
        {
        return (b & state) == b;
        }


    TTY&
    TTY::Place( size_t x, size_t y )
        {
        if( IsSet(Wrap) && x >= buffer->Width() )
            {
            ++y;
            x %= buffer->Width();
            }

        if( IsSet(VScroll) && y >= buffer->Height() )
            {
            buffer->Scroll( y - buffer->Height() + 1 );
            y = buffer->Height() - 1;
            }
        curs_x = x;
        curs_y = y;
        return *this;
        }


    TTY&
    TTY::ClearLine()
        {
        for( size_t x=0; x<buffer->Width(); ++x )
            buffer->Put(x,curs_y, Char() );

        Place(0,curs_y);
        return *this;
        }


    Char
    TTY::Peek() const
        {
        return buffer->Get(curs_x,curs_y);
        }


    TTY&
    TTY::Put( Char ch )
        {
        if( IsSet(Insert) &&
            Peek().ASCII() != '\0' )
            {
            TTY insert(*buffer);
            insert.Place(curs_x+1, curs_y);
            Char next = Peek();
            do  {
                Char tmp = insert.Peek();
                insert.Put(next);
                next = tmp;
                }
            while( next.ASCII() != '\0' );
            }

        if( ch.ASCII() == '\n' )
            Place( 0, curs_y + 1 );
        else
            {
            buffer->Put( curs_x, curs_y, ch );
            Place( curs_x + 1, curs_y );
            }
        return *this;
        }


    TTY&
    TTY::Put( const String& str )
        {
        for( Char ch : str )
            Put(ch);
        return *this;
        }



    TTY&
    TTY::Put( char c )
        {
        Put( Char(c,0,pri,sec) );
        return *this;
        }


    TTY&
    TTY::Put( const std::string& str )
        {
        for( auto c : str )
            Put(c);
        return *this;
        }


    TTY&
    TTY::PriColor( Color color )
        {
        pri = color;
        return *this;
        }


    TTY&
    TTY::SecColor( Color color )
        {
        sec = color;
        return *this;
        }


    } // namespace Term
