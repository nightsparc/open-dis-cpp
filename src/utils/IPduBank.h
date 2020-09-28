#ifndef _IPDU_BANK_H_
#define _IPDU_BANK_H_

#include <utils/DataStream.h>

#if DIS_VERSION == 6
    #include <dis6/Pdu.h>
#elif DIS_VERSION == 7
    #include <dis7/Pdu.h>
#else
    #error "Unsupported DIS version"
#endif


namespace DIS
{
    /// houses instances for the set of known PDU classes to be returned
    /// when provided with the PDU type's identifier value.
    class IPduBank
    {
    public:
        ~IPduBank(){}

        /// finds the PDU instance corresponding to the identifier
        /// @param pdu_type the 8-bit PDU type identifier
        /// @return NULL when the pdu_type is unknown.
        virtual Pdu* GetStaticPDU( unsigned char pdu_type, DataStream& ds ) = 0;
    };
}

#endif // _IPDU_BANK_H_

