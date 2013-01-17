set( CORE_HEADERS
    buffer.hpp
    char.hpp
    context.hpp
    staticbuffer.hpp
    string.hpp
    tty.hpp )

install( FILES ${CORE_HEADERS} DESTINATION include/Terminate/core )
