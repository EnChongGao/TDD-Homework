#include "gmock/gmock.h"

int main( int argc, char* argv[] )
{
    testing::InitGoogleMock( &argc, argv);
    int nReturnCode = RUN_ALL_TESTS();
    system( "pause" );
    return 0;
}

