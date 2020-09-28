#ifndef _dcl_dis_endian_h_
#define _dcl_dis_endian_h_

#if DIS_VERSION == 6
    #include <dis6/msLibMacro.h>       // for library symbols
#elif DIS_VERSION == 7
    #include <dis7/msLibMacro.h>       // for library symbols
#else
    #error "Unsupported DIS version"
#endif

namespace DIS
{
   /// the order of bytes that are on the left
   EXPORT_MACRO enum Endian
   {
      LITTLE=1,
      BIG=0,
   };
}

#endif   // _dcl_dis_endian_h_
