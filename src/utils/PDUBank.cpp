#include <utils/PDUBank.h>
#if DIS_VERSION == 6
    #include <dis6/Pdu.h>
    #include <dis6/EntityStatePdu.h>
    #include <dis6/FirePdu.h>
    #include <dis6/DetonationPdu.h>
    #include <dis6/CollisionPdu.h>
    #include <dis6/ServiceRequestPdu.h>
    #include <dis6/ResupplyOfferPdu.h>
    #include <dis6/ResupplyReceivedPdu.h>
    #include <dis6/ResupplyCancelPdu.h>
    #include <dis6/RepairCompletePdu.h>
    #include <dis6/RepairResponsePdu.h>
    #include <dis6/CreateEntityPdu.h>
    #include <dis6/RemoveEntityPdu.h>
    #include <dis6/StartResumePdu.h>
    #include <dis6/AcknowledgePdu.h>
    #include <dis6/ActionRequestPdu.h>
    #include <dis6/ActionResponsePdu.h>
    #include <dis6/DataQueryPdu.h>
    #include <dis6/SetDataPdu.h>
    #include <dis6/EventReportPdu.h>
    #include <dis6/CommentPdu.h>
    #include <dis6/StopFreezePdu.h>
#elif DIS_VERSION == 7
    #include <dis7/Pdu.h>
    #include <dis7/EntityStatePdu.h>
    #include <dis7/FirePdu.h>
    #include <dis7/DetonationPdu.h>
    #include <dis7/CollisionPdu.h>
    #include <dis7/ServiceRequestPdu.h>
    #include <dis7/ResupplyOfferPdu.h>
    #include <dis7/ResupplyReceivedPdu.h>
//    #include <dis7/ResupplyCancelPdu.h>
    #include <dis7/RepairCompletePdu.h>
    #include <dis7/RepairResponsePdu.h>
    #include <dis7/CreateEntityPdu.h>
    #include <dis7/RemoveEntityPdu.h>
    #include <dis7/StartResumePdu.h>
    #include <dis7/AcknowledgePdu.h>
    #include <dis7/ActionRequestPdu.h>
    #include <dis7/ActionResponsePdu.h>
    #include <dis7/DataQueryPdu.h>
    #include <dis7/SetDataPdu.h>
    #include <dis7/EventReportPdu.h>
    #include <dis7/CommentPdu.h>
    #include <dis7/StopFreezePdu.h>
#else
    #error "Unsupported DIS version"
#endif


using namespace DIS;

Pdu* PduBank::GetStaticPDU( DIS::PDUType pdu_type )
{
   static EntityStatePdu      entityStatePdu;
   static FirePdu             firePdu;
   static DetonationPdu       detonationPdu;
   static CollisionPdu        collisionPdu;
   static ServiceRequestPdu   ServiceRequestPdu;
   static ResupplyOfferPdu    resupplyOfferPdu;
   static ResupplyReceivedPdu resupplyReceivedPdu;
#if DIS_VERSION == 6
   static ResupplyCancelPdu   resupplyCancelPdu;
#endif
   static RepairCompletePdu   repairCompletePdu;
   static RepairResponsePdu   repairResponsePdu;
   static CreateEntityPdu     createEntityPdu;
   static RemoveEntityPdu     removeEntityPdu;
   static StartResumePdu      startResumePdu;
   static AcknowledgePdu      acknowledgePdu;
   static ActionRequestPdu    actionRequestPdu;
   static ActionResponsePdu   actionResponsePdu;
   static DataQueryPdu        dataQueryPdu;
   static SetDataPdu          setDataPdu;
   static EventReportPdu      eventReportPdu;
   static CommentPdu          commentPdu;
   static StopFreezePdu       stopFreezePdu;

   switch(pdu_type)
   {
      case PDU_ENTITY_STATE:      return &entityStatePdu;      break;
      case PDU_FIRE:              return &firePdu;             break;
      case PDU_DETONATION:        return &detonationPdu;       break;
      case PDU_COLLISION:         return &collisionPdu;        break;
      case PDU_SERVICE_REQUEST:   return &ServiceRequestPdu;   break;
      case PDU_RESUPPLY_OFFER:    return &resupplyOfferPdu;    break;
      case PDU_RESUPPLY_RECEIVED: return &resupplyReceivedPdu; break;
#if DIS_VERSION == 6
      case PDU_RESUPPLY_CANCEL:   return &resupplyCancelPdu;   break;
#endif
      case PDU_REPAIR_COMPLETE:   return &repairCompletePdu;   break;
      case PDU_REPAIR_RESPONSE:   return &repairResponsePdu;   break;
      case PDU_CREATE_ENTITY:     return &createEntityPdu;     break;
      case PDU_REMOVE_ENTITY:     return &removeEntityPdu;     break;
      case PDU_START_RESUME:      return &startResumePdu;      break;
      case PDU_ACKNOWLEDGE:       return &acknowledgePdu;      break;
      case PDU_ACTION_REQUEST:    return &actionRequestPdu;    break;
      case PDU_ACTION_RESPONSE:   return &actionResponsePdu;   break;
      case PDU_DATA_QUERY:        return &dataQueryPdu;        break;
      case PDU_SET_DATA:          return &setDataPdu;          break;
      case PDU_EVENT_REPORT:      return &eventReportPdu;      break;
      case PDU_COMMENT:           return &commentPdu;          break;
      case PDU_STOP_FREEZE:       return &stopFreezePdu;       break;
      default:                                                 break;
   }
   return NULL;
}

