#include <utils/StreamUtils.h>

#if DIS_VERSION == 6
    #include <dis6/EntityStatePdu.h>
    #include <dis6/EntityID.h>
    #include <dis6/DetonationPdu.h>
#elif DIS_VERSION == 7
    #include <dis7/EntityStatePdu.h>
    #include <dis7/EntityID.h>
    #include <dis7/DetonationPdu.h>
#else
    #error "Unsupported DIS version"
#endif


std::ostream& operator <<(std::ostream& lhs, const DIS::EntityType& rhs)
{
   lhs << "EntityType ("
       << (unsigned int)rhs.getEntityKind()
       << "," << (unsigned int)rhs.getDomain()
       << "," << (unsigned int)rhs.getCountry()
       << "," << (unsigned int)rhs.getCategory()
       << "," << (unsigned int)rhs.getSubcategory()
       << ") ";
   return lhs;
}

std::ostream& operator <<(std::ostream& lhs, const DIS::EntityID& rhs)
{
   lhs << "EntityID ("
#if DIS_VERSION == 6
       << (unsigned int)rhs.getEntity()
#elif DIS_VERSION == 7
       << (unsigned int)rhs.getEntityNumber()
#else
           #error "Unsupported DIS version"
#endif
       << ") ";

   return lhs;
}

std::ostream& operator <<(std::ostream& lhs, const DIS::EntityStatePdu& rhs)
{
   lhs << "EntityStatePdu (" << rhs.getEntityID() << ") ";
   return lhs;
}

std::ostream& operator <<(std::ostream& lhs, const DIS::DetonationPdu& rhs)
{
   lhs << "DetonationPDU (" << rhs.getFiringEntityID() << ") ";
   return lhs;
}
