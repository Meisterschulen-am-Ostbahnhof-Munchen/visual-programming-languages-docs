/* ************************************************************************ */
/*!
   \file
   \brief       ISOBUS ECU driver base definitions
   \details     This file is used instead of IsoDef.h to hold the commonly used definitions
                and debug functions

   \author      Wegscheider Peter
   \date        Created 27.02.2015

   \copyright   Competence Center ISOBUS e.V.

   \par  History:
   \par
   27.02.2015 - author P. Wegscheider
   - Version 8.00.00, VERSION_BASE 1.04
   - added definitions and debug functions
   - Feature request ID 1710: Change location of header files
   - Feature request ID 1716: Use multi node API as default
   \par
   29.09.2015 - author P. Wegscheider
   - Version 8.01.00, VERSION_BASE 1.05
   - Feature request ID 1711: Resolve typdef conflicts with ISO_TRUE;ISO_FALSE and types definitions
   - include IsoStdTypes.h
   \par
   24.03.2016 - author P. Wegscheider
   - Feature request ID 3846: Add interface to Krone's NIU software
   \par
   01.08.2016 - author P. Wegscheider
   - Version 8.02.00
   \par
   05.08.2016 - author P. Wegscheider
   - Version 8.02.01
   \par
   03.11.2016 - author P. Wegscheider
   - Version 8.02.02
   \par
   04.11.2016 - author P. Wegscheider
   - Updated driver version to 9.00.00 and VERSION_BASE to 1.07
   - Feature request ID 4625: removed single node api
   \par
   10.11.2016 - author P. Wegscheider
   - Feature request ID 4510: can send should get a return value
      - Added ISO_DL_CbCanSend_t and ISO_DL_CbGetFreeCanSendFiFo_t typedef
   \par
   14.02.2017 - author P. Wegscheider
   - Removed M_J1939 error defines
   \par
   18.09.2017 - author P. Wegscheider
   - V09.00.02 released
   \par
   12.02.2018 - author P. Wegscheider
   - Added defines for feature BugID 7347: use _Pragma ("section") for GCC, instead of \#pragma section .xxx
   \par
   15.02.2018 - author P.Wegscheider
   - Feature ID 7528: add a "void* userParam" to CF and PGN callback functions
   \par
   05.03.2018 - author P. Wegscheider
   - Feature request ID 4815: replace iso_DebugPuts() with iso_DebugPrint() and an trailing '\n'
      - iso_DebugPuts() deleted and calls replaced with iso_DebugPrint()
   - Feature request ID 8115: Added optional network events Isonet_MemberTimeout and Isonet_MemberResume
   - Added feature for ISO_ETP_IN_PKG to report a data group packet with TP status record_etp_in_pkg
   \par
   08.06.2018 - author P.Wegscheider
   - Feature request ID 7504: Moved internal CF network and data link callbacks from Core to Base.
   \par
   12.06.2018 - author P.Wegscheider
   - Feature request ID 8459: use iso_u8 for ISOBUS addresses in API
   - Replaced ISO_TPINFO_T iso_u16 wSAInternUser and u8SAPartner with iso_u8 u8SAIntern and u8SAPartner
   - Replaced ISONETEVENT_T iso_u16 wSAMember with iso_u8 u8SAMember
   - Replaced ISOMEMBDAT_T iso_u16 wMemSrcAdd with iso_u8 u8MemSrcAdd
   - Replaced ISOUSERAPP_T iso_u16 wIsoSourceAdd with iso_u8 u8IsoSourceAdd and set content of pointers to const
   \par
   13.06.2018 - author P.Wegscheider
   - Feature request ID 8424: use ISO_CF_NAME_T in API functions
   \par
   08.08.2018 - author P. Wegscheider
   - BugID 8581: add "namespace ISOBUSDRIVER" to header files. \n
     Include files IsoCommonDef.hpp IsoPgnDef.hpp if C++ compiler and CCI_USE_NAMESPACE is defined.
   \par
   29.08.2018 - author P. Wegscheider
   - Version 10.00.00
   \par
   20.03.2019 - author P. Wegscheider
   - Version 10.01.00
   \par
   25.03.2019 - author P.Wegscheider
   - Feature request ID 10348: activate base shadow copying
   \par
   03.04.2019 - author P.Wegscheider
   - Feature request ID 10507: remove obsolete entries in ISO_NM_CMD_Te
   \par
   08.07.2019 - author P.Wegscheider
   - Added optional defines CCI_CORE_API, CCI_BASE_API and CCI_CLIENT_API to most API functions for a test implementation.
     (see also feature ID 10891)
   - Added optional define CCI_HSI and functions for a high speed ISOBUS test implementation (see also feature ID 10522). \n
     Hint: If you enable CCI_HSI you should also enable ISO_BASE_SHADOW_COPY.
   \par
   27.09.2019 - author P. Wegscheider
   - Feature request BugID 11199: The A3 should send the "VT Status Msg" through propriatary command 96 \n
     To activate add define CCI_CUSTOM_GAUX_VT_STATUS to the IsoConf.h
   \par
   15.11.2019 - author P.Wegscheider
   - Feature request ID 10185: refactor TL -- use case for dual CPU implementations \n
     Removed defines CCI_TL_IN_BASE and CAST_TO_U8_PTR added define CAST_TO_CONST_U8_HUGE_PTR
   \par
   20.11.2019 - author P.Wegscheider
   - Removed deprecated/unneeded address_conflict forwarding to clients.
   - Removed unused ISO_TPREP_E enum values tp_pause and pgn_missed.
   \par
   16.01.2020 - author E. Hammerl
   - Feature request ID 11555: Added device classes feeder/mixer and weeder and some non-specific class functions
   \par
   30.01.2020 - author P.Wegscheider
   - Feature request BugID 11667: rename CCI_CORE_API into ISO_CORE_API
   - Feature request BugID 11700: rename CCI_BASE_API into ISO_BASE_API \n
     renamed CCI_CLIENT_API into ISO_CLIENT_API and added missing API functions
   - Feature request BugID 10424: ISOMEMBDAT_T ->eMemLogState shall be replaced by bFullyAnnounced
   - Feature request BugID 11706: add iso_s32 time as last parameter to error callbacks
   \par
   07.02.2020 - author P.Wegscheider
   - Feature request BugID 10185: refactor TL - Added "const" to the definition of the ISO_TPINFO_T field pabData
   - Feature request BugID 10542: move functions and data not required by core into base \n
     Structure ISONAMEFIELD_T fields converted to iso_bitfield \n
     Use ISO_NETEVENT_e events Isonet_MemberAdd and Isonet_MemberRemove to keep core and base network variables in sync
   \par
   27.04.2020 - author P.Wegscheider
   - Fixed ISONAMEFIELD_T structure for usage with 16-Bit compiler 
     (iso_bitfield  dwIdentNumb : 21 not possible with all 16-bit compilers. 
     Add define ISO_LIMIT_BITFIELD_TO_16BIT to your IsoConf.h if you get an compiler error for this structure)
   \par
   12.05.2020 - author P.Wegscheider
   - BugID 12299: make (E)TP packet group size configurable
   \par
   14.09.2020 - author P.Wegscheider
   - BugID 12648: conditionally remove iso_coreTlFindFreeChannel()
  \par
   12.01.2021 - author P.Wegscheider
   - Feature BugID 12133: VTC - Disable auxiliary function type 1 functionality by default \n
     (Replaced ISO_VTC_DISABLE_AUX_O with ISO_VTC_ENABLE_AUX_O) 
   - Feature BugID 12772: removed deprecated structure ISOUSERAPP_T
   \par
    01.02.2021 - author P.Wegscheider
    - Feature BugID 11868: use ISO_ETP_IN only in TL_TP_Filter_CB
    - Feature BugID 12939: removed non-standard option ISO_NM_CF_PASSIVE
   \par
    16.02.2021 - author P.Wegscheider
     - Feature BugID 12831: Added bExternalCf field to structure ISOMEMBDAT_T
*/
/* ************************************************************************ */

#ifndef DEF_ISOCOMMONDEF_H
#define DEF_ISOCOMMONDEF_H

#include "IsoVersion.h"

/* ************************************************************************ */
#ifdef ISOCONF_APPFILE
    /* Use the application specific IsoConf header file */
    #include ISOCONF_APPFILE
#else
    /* Use the IsoConf.h header file */
    #include "IsoConf.h"
#endif

/* ************************************************************************ */
#ifndef DEF_ISOSTDTYPES_H
    /* Include the libray type definitions for the used standard C types */
    #include "IsoStdTypes.h"
#endif

/* ************************************************************************ */
#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

#if !defined(CCI_USE_ISO_TIME)
#if defined(ISO_TIME) || defined(ISO_TIME_F)
#error Do not use ISO_TIME. It is currently reserved for CCI for evaluation.
#endif /* defined(ISO_TIME) || defined(ISO_TIME_F) */
#endif /* !defined(CCI_USE_ISO_TIME) */

#if !defined(ISO_TIME)
/* e.g. "#define ISO_TIME(X) ISO_TIME_##X" */
#define ISO_TIME 
#endif /* !defined(ISO_TIME) */
#if !defined(ISO_TIME_F)
/* e.g. "#define ISO_TIME_F(x) ((iso_s32)(x * 128 / 125))" */
#define ISO_TIME_F 
#endif /* !defined(ISO_TIME_F) */
#if !defined(ISO_TIMEOUT)
#define ISO_TIMEOUT(factor,timebase,timemargin) (((factor)*ISO_TIME(timebase))+ISO_TIME(timemargin)) 
#endif /* !defined(ISO_TIMEOUT) */
/*
Note: 
The longest time in [ms] within the isobus driver is 255 seconds. 
That will allow for a smallest resolution for the timer to be ~1 micro second;
meaning a maximum value using 28 bits for representing the time.
*/

/* ************************************************************************ */
/* ******************** Common Driver API ******************************** */
/* ************************************************************************ */

#if !defined(CCI_COMMON_API)
#define CCI_COMMON_API
#endif /* !defined(CCI_COMMON_API) */

/* ************************************************************************ */
/* ******************** Core Driver API *********************************** */
/* ************************************************************************ */

/* Since V12 defined ISO_ETP_IN is ISO_DEPRECATED */
#if defined(ISO_ETP_IN_PKG) && !defined(ISO_ETP_IN)
   /* define also ISO_ETP_IN */
   #define ISO_ETP_IN
#endif /*  defined(ISO_ETP_IN_PKG) && !defined(ISO_ETP_IN) */

#if !defined(ISO_CORE_API)
#define ISO_CORE_API
#endif /* !defined(ISO_CORE_API) */

#if defined(ISO_NM_CF_PASSIVE)
/* passive (slave) CFs are not standard conform and have been removed in version 12. */
#error ISO_NM_CF_PASSIVE was removed in version 12 (reason: not standard conform). 
#endif /* defined(ISO_NM_CF_PASSIVE) */

/* ************************************************************************ */
/* ******************** Base Driver API *********************************** */
/* ************************************************************************ */

#if !defined(ISO_BASE_API)
#define ISO_BASE_API
#endif /* !defined(ISO_BASE_API) */

#ifdef _LAY78_
   /*! \brief Enable "Multi CAN Node " part 7 application layer module compilation */
   #define ISO_MODULE_APPLAYER
   #if !defined(NUMBERSPN_MAX) || ( NUMBERSPN_MAX > 0 )
      /*! \brief Enable "Multi CAN Node " SPN module compilation */
      #define ISO_MODULE_SPN
   #endif
#endif

#if !defined(ISO_OMIT_APP_RET_WARNING)
#if defined(ISO_MODULE_APPLAYER_OMIT_RETURN_VALUE)
#error the define ISO_MODULE_APPLAYER_OMIT_RETURN_VALUE is deprecated and will be removed in V13; if your application requires it, then call CCI
#endif
#endif /* !defined(ISO_OMIT_APP_RET_WARNING) */

/* ************************************************************************ */
/* ******************** Base Core Wrapper Driver API ********************** */
/* ************************************************************************ */

#if !defined(CCI_WRAP_BASE_CORE_API)
#define CCI_WRAP_BASE_CORE_API
#endif /* !defined(CCI_WRAP_BASE_CORE_API) */

/* ************************************************************************ */
/* ******************** Clients Base Wrapper Driver API ******************* */
/* ************************************************************************ */

#if !defined(CCI_WRAP_CLIENT_BASE_API)
#define CCI_WRAP_CLIENT_BASE_API
#endif /* !defined(CCI_WRAP_CLIENT_BASE_API) */

#ifdef DOXYGEN
/*! \brief Enable client network distributer functionality 
    \details If enabled the distributor function for the client layer must be set with iso_BaseSetClientNetworkDistributor() */
#define ISO_CLIENT_NETWORK_DISTRIBUTOR
#endif /* DOXYGEN */

/* ************************************************************************ */
/* ******************** NIU - Network interconnection Unit API ************ */
/* ************************************************************************ */
#ifdef _LAY4_
   /*! \brief Enable "Network Interconnection Unit" module compilation */
   #define ISO_MODULE_NIU
#else    /* not  _LAY4_ */
#ifdef _LAY4_EXTERNAL
/*! \brief Enable external "Network Interconnection Unit" integration */
   #define ISO_EXTERNAL_NIU
#endif   /* _LAY4_EXTERNAL */
#endif   /* not  _LAY4_ */

#if defined(ISO_MODULE_NIU) || defined(ISO_EXTERNAL_NIU) || defined(DRV_USE_CAN_MSG_QUEUE)
/* TODO check if we can remove this for V13 or later... */
/*! \brief Helper define for enabling ISO_CAN_MSG_T s32TimeStamp field */
#define DRV_USE_CAN_MSG_TIMESTAMP
#endif   /* defined(ISO_MODULE_NIU) || defined(ISO_EXTERNAL_NIU) || defined(DRV_USE_CAN_MSG_QUEUE) */


/* ************************************************************************ */
/* ******************** HB - Heartbeat client/server API ****************** */
/* ************************************************************************ */
#ifdef DOXYGEN
   /* make sure that the documentation for the defines is generated */
   #define ISO_HBC_MAX  (0u)
   #define ISO_HBS_MAX  (0u)
   #define ISO_HB_MISSMAX  (3u)
   #define ISO_HB_RATEMIN  (100u)  /* used as iso_u16 in [ms]; ISO_TIME() is required if its [ms] value is required */
   #define ISO_HB_REQ_TIME_OUT (ISO_TIME(1250L))
   #define ISO_HB_MSG_TIME_OUT_FACTOR (3L)
#endif /* DOXYGEN */

/*! \addtogroup hbapi
   @{

   \def   ISO_HBC_MAX
   \brief Number possible heartbeat clients
   \details
   If defined and greater than zero the heartbeat client functionality and compilation is enabled. \n
   The value specifies the array size for the heartbeat client/server connection entries and should be unsigned.
   The value must be set at least to the number of external heartbeat servers
   which should be monitored with iso_HBClient_Request(). \n
   Sample:
   If you want to monitor the heartbeat message from server S1 and S2 with the internal (client) CF C1
   and Server S2 and S3 with the client CF C2 the value for ISO_HBC_MAX must be set at least to 4u.

   \def   ISO_HBS_MAX
   \brief Number possible heartbeat server
   \details
   If defined and greater than zero the heartbeat server functionality and compilation is enabled. \n
   The value specifies the array size for the heartbeat server entries and should be unsigned.
   The value must be set at least to the number of internal CF
   which should be added with iso_HBServer_Install() as heartbeat server.

   \def   ISO_HB_MISSMAX
   \brief Number of allowed missing HB message sequence numbers.
          Range: 0u - 3u

   \def   ISO_HB_RATEMIN
   \brief Minimum repetition rate for the HB message.
          Default is 100 ms as defined in the norm.

   \def ISO_HB_REQ_TIME_OUT
   \brief Heartbeat request for repetition rate request response timeout.
          If not defined it is set to 1250L ms (Should be set to 250L ms).

   \def ISO_HB_MSG_TIME_OUT_FACTOR
   \brief Heartbeat message time out factor.
          The time out value in ms is ISO_HB_MSG_TIME_OUT_FACTOR * "repetition rate". \n
          If not defined it is set to 3 (3L). \n
          Range: 1L - 3L
   @}
*/

#if defined(ISO_HBC_MAX) && (ISO_HBC_MAX > 0)
   /*! \brief Enable heartbeat client compilation and integration */
   #define ISO_MODULE_HBCL
#endif /* defined(ISO_HBC_MAX) && (ISO_HBC_MAX > 0) */

#if defined(ISO_HBS_MAX) && (ISO_HBS_MAX > 0)
   /*! \brief Enable heartbeat server compilation and integration */
   #define ISO_MODULE_HBSRV
#endif /* defined(ISO_HBS_MAX) && (ISO_HBS_MAX > 0) */

#if defined(ISO_MODULE_HBCL) || defined(ISO_MODULE_HBSRV)
   /* check defines and set defaults if missed */
#ifndef ISO_HB_MISSMAX
   #define ISO_HB_MISSMAX  (3u)
#endif /* !ISO_HB_MISSMAX */
#ifndef ISO_HB_RATEMIN
   #define ISO_HB_RATEMIN  (100u) /* used as iso_u16 in [ms]; ISO_TIME() is required if its [ms]value is required */
#endif /* !ISO_HB_MISSMAX */

#ifndef ISO_HB_REQ_TIME_OUT
   #define ISO_HB_REQ_TIME_OUT (ISO_TIME(1250L))
#endif /* ! ISO_HB_REQ_TIME_OUT */

#ifndef  ISO_HB_MSG_TIME_OUT_FACTOR
   #define ISO_HB_MSG_TIME_OUT_FACTOR (3L)
#endif /* ! ISO_HB_MSG_TIME_OUT_FACTOR */

#endif /* defined(ISO_MODULE_HBCL) || defined(ISO_MODULE_HBSRV) */


/* ************************************************************************ */
#ifdef DOXYGEN
/* make sure that the documentation for the optional diagnostic module is generated */
   #define ISO_DIAG_EXTERNAL
#endif /* DOXYGEN */

#if defined(ISO_DIAG_EXTERNAL)
/*! \addtogroup diagapi
   @{
      \def ISO_DIAG_EXTERNAL
      \brief    Define to enable the optional diagnostic data request module.
      \details
   @}
*/

   /*! \brief Enable diagnostic module compilation and integration */
   #define ISO_MODULE_DIAG
#endif /* defined(ISO_DIAG_EXTERNAL) */


/* ************************************************************************ */
/* ******************** CLIENTS ******************************************* */
/* ************************************************************************ */

#if !defined(ISO_OMIT_VT6_PNG_DRAFT_WARNING)
#if defined(ISO_VT6_PNG_DRAFT)
#error the define ISO_VT6_PNG_DRAFT is deprecated and will be removed in V13; if your application requires it, then call CCI
#endif
#endif /* !defined(ISO_OMIT_VT6_PNG_DRAFT_WARNING) */

/* ************************************************************************ */
/** \addtogroup clientsshared
@{ */
/*! \brief  NULL Object ID 
   \details The pool object ID FFFF is reserved for use as the "NULL" Object ID. */
#define NULL_OBJECTID   (0xFFFFu)         
/** @} */

#if !defined(ISO_CLIENT_API)
#define ISO_CLIENT_API
#endif /* !defined(ISO_CLIENT_API) */

#if defined(_LAY6_) || defined(_LAY10_) || defined(_LAY13_) || defined(_LAY14_) || defined(ISO_VT_SERVICE)
   /*! \brief Enable client shared module compilation */
   #define ISO_MODULE_CLIENTS
   /*! \brief Enable basic client wrapper module compilation */
   #define ISO_MODULE_BASIC_CL_WRAPPER

   #if !defined (WORKING_SETS)
   #define  WORKING_SETS  (1)    /**< Number of working sets */  
   #endif /* WORKING_SETS */

   #if defined(ISO_VTC_GRAPHIC_AUX) && (!defined(CCI_CUSTOM_GAUX_VT_STATUS))
      /* enable custom VT status message processing from A3 for GAux clients per default */
      #define CCI_CUSTOM_GAUX_VT_STATUS
   #endif /* defined(ISO_VTC_GRAPHIC_AUX) && (!defined(CCI_CUSTOM_GAUX_VT_STATUS)) */
   #if defined(ISO_VT_SERVICE) && (!defined(CCI_NO_GAUX_VT)) && (!defined(CCI_CUSTOM_GAUX_VT_STATUS))
   /* enable custom VT status message sending (A3 VT service) */
   #define CCI_CUSTOM_GAUX_VT_STATUS
   #endif /* defined(ISO_VTC_GRAPHIC_AUX) && (!defined(CCI_NO_GAUX_VT)) && (!defined(CCI_CUSTOM_GAUX_VT_STATUS)) */

   #if defined(CCI_CUSTOM_GAUX_VT_STATUS)
      /* use custom function code for VT status message of graphical aux */
      #if !defined(CCI_GAUX_VT_STATUS_MSG)
         #define CCI_GAUX_VT_STATUS_MSG  (96u)
      #endif   /* !defined(CCI_GAUX_VT_STATUS_MSG) */
      #if !defined(CCI_GAUX_VT_STATUS_MANU)
         #define CCI_GAUX_VT_STATUS_MANU  (339u)
      #endif   /* !defined(CCI_GAUX_VT_STATUS_MANU) */
      #if !defined(GRIMME_GAUX_VT_STATUS_MANU)
         #define GRIMME_GAUX_VT_STATUS_MANU  (107u)
      #endif   /* !defined(GRIMME_GAUX_VT_STATUS_MANU) */
   #endif   /* defined(CCI_CUSTOM_GAUX_VT_STATUS) */


   #ifdef _LAY6_
      /*! \brief Enable VT client module compilation */
      #define ISO_MODULE_VTC

      #if !defined(ISO_VTC_DISABLE_UT3)
      /*! \brief Enable functionality for VT4 and VT5 */
      #define ISO_VTC_UT3
      #endif

      #if !defined(ISO_VTC_DISABLE_AUX_N)
      /*! \brief Enable auxiliary function type 2 functionality.
          ( IsoAux.c )
      */
      #define ISO_VTC_AUX_N
      #endif

      #if defined(ISO_VTC_ENABLE_AUX_O)
      /*! \brief Enable auxiliary function type 1 functionality.
          ( IsoAuxOld.c )
      */
      #define ISO_VTC_AUX_O
      #endif

      #if defined(ISO_VTC_ENABLE_AUX_INPUT)
      /*! \brief Enable auxiliary input type 1 and 2 functionality.
          ( IsoAux.c, IsoAuxOld.c  )
      */
      #define ISO_VTC_AUX_INP_N
      #define ISO_VTC_AUX_INP_O /* needs also ISO_VTC_AUX_INP_N */
      #endif

      #if defined(ISO_VTC_ENABLE_ALARM)
            /*! \brief Enable VT client alarm management functionality.
            ( IsoAlarm.c )
            */
      #define ISO_VTC_ALARM
      #endif

      #if !defined(ISO_VTC_DISABLE_POOL_BUFFERED_LOAD)
      /*! \brief Enable buffered standard and segmented pool upload functionality.
          ( IsoPool.c )
      */
      #define ISO_POOL_BUFFERED_LOAD
      #endif

      /* Check V11 command buffer defines */
      #if defined(VTMSG_BUFSIZE) || defined(STRBUFFSIZE)
         #if (!defined(ISO_VTC_CMD_BUFFER_MAX)) || (!defined(ISO_VTC_CMD_STR_BLOCK_SIZE))
         #error VTMSG_BUFSIZE, STRBUFFSIZE and STRLENGTHMAX not longer valid. Use ISO_VTC_CMD_BUFFER_MAX, ISO_VTC_CMD_EXDATA_MAX_BLOCKS and ISO_VTC_CMD_STR_BLOCK_SIZE to configure the VTC command buffer.
         #endif
      #endif

   #endif /* _LAY6_ */

   #ifdef _LAY10_
      /*! \brief Enable TC client module compilation */
      #define ISO_MODULE_TCC
   #endif

   #ifdef _LAY14_
      /*! \brief Enable SQC client module compilation */
      #define ISO_MODULE_SQCC
   #endif

   #ifdef _LAY13_
      /*! \brief Enable FS client module compilation */
      #define ISO_MODULE_FSC
   #endif

#endif    /* ISO_MODULE_CLIENTS */


/****************************************************************************/
/****************************************************************************/
/*! \addtogroup isoconfig
@{ */

#ifndef ISO_CAN_NODES
   #define  ISO_CAN_NODES       1u      /**< Default number of CAN nodes */
#endif /* ISO_CAN_NODES */

#ifndef ISO_CAN_VT
   #define  ISO_CAN_VT          0u      /**< Default CAN node for clients */
#endif /* ISO_CAN_VT */

/*! \def ISO_CANMSG_QUEUE_SIZE
   \brief Size of the NIU CAN message buffer array
   \details Default:  20 * ISO_CAN_NODES := ( 10 ms * 2 msg/ms * CanNodes )
*/
#ifndef ISO_CANMSG_QUEUE_SIZE
   #define ISO_CANMSG_QUEUE_SIZE ( 20u * ISO_CAN_NODES )
#endif

/*! 
   \def ISO_TP_PACKET_GROUP_SIZE
   \brief Maximum number of TP data packets to be received with a single CTS
   \details Default:  16u Range: 8u - 255u 

   \def ISO_ETP_PACKET_GROUP_SIZE
   \brief Maximum number of ETP data packets to be received with a single CTS
   \details Default:  255u Range: 8u - 255u

*/

#ifndef ISO_TP_PACKET_GROUP_SIZE
#define ISO_TP_PACKET_GROUP_SIZE (16u)
#else /* ISO_TP_PACKET_GROUP_SIZE */
#if (ISO_TP_PACKET_GROUP_SIZE > 255u) || (ISO_TP_PACKET_GROUP_SIZE < 8u)
#error Value of ISO_TP_PACKET_GROUP_SIZE is not in allowded range ( 8u - 255u)
#endif /* (ISO_TP_PACKET_GROUP_SIZE > 255u) || (ISO_TP_PACKET_GROUP_SIZE < 8u) */
#endif /* ISO_TP_PACKET_GROUP_SIZE -- PACKET_GROUP */

#ifndef ISO_ETP_PACKET_GROUP_SIZE
#define ISO_ETP_PACKET_GROUP_SIZE (255u)
#else /* ISO_ETP_PACKET_GROUP_SIZE */
#if (ISO_ETP_PACKET_GROUP_SIZE > 255u) || (ISO_ETP_PACKET_GROUP_SIZE < 8u)
#error Value of ISO_ETP_PACKET_GROUP_SIZE is not in allowded range ( 8u - 255u)
#endif /* (ISO_ETP_PACKET_GROUP_SIZE > 255u) || (ISO_ETP_PACKET_GROUP_SIZE < 8u) */
#endif /* ISO_ETP_PACKET_GROUP_SIZE */

#ifndef TP_PARALLEL_MAX
   #define      TP_PARALLEL_MAX       (5)        /* max parallel transport channels */
#endif /* TP_PARALLEL_MAX */

/* for high speed ISOBUS */
#if defined (CCI_HSI)
#ifndef HSI_TP_PARALLEL_MAX
   #define      HSI_TP_PARALLEL_MAX       (5)        /* max HSI parallel transport channels */
#endif /* HSI_TP_PARALLEL_MAX */
#else /* defined (CCI_HSI) */
#ifdef HSI_TP_PARALLEL_MAX
   #error HSI_TP_PARALLEL_MAX may only be defined if CCI_HSI is defined.
#endif /* HSI_TP_PARALLEL_MAX */
#endif /* defined (CCI_HSI) */

#ifndef ISO_USER_MAX
   /** \brief Default value for the maximum number of network members for a CAN Node - predefined with 32 */
   #define ISO_USER_MAX        (32)
#endif /* ISO_USER_MAX */

#ifndef PARAM_UNUSED
   /*! \brief  use this macro for all your unused function parameters */
   #define PARAM_UNUSED(x) (void)(x)
#endif

/* ************************************************************************** */
/*! \name Huge Memory Type Qualifier And Pointer Casts

   Add this defines only to your IsoConf.h, if use the VTC or FSC module \n
   and the normal memory model and pointer arithmetic is limited to 16kB or 64 kB \n
   and your pool buffer or file data arrays are greater than the limit of 16kB or 64 kB.
   \n
   IsoConf.h Sample for Tasking VX-Toolset for C166:
   \code{.c}

   #define   HUGE_C       __huge
   #define   CAST_TO_U8_HUGE_PTR( ptr )    ((iso_u8 HUGE_C *)( ptr ))
   #define   CAST_TO_CONST_U8_HUGE_PTR( ptr )    ((const iso_u8 HUGE_C *)( ptr ))

   \endcode
   \note
   It is not recommend to use this defines for SRL1. \n
   Use for SRL1 a memory model where no casts are needed.
@{ */

/* ************************************************************************** */
/*!
   \def HUGE_C
   \brief Memory Type for pointers to huge size variables.
   \details This define is normally only needed for 16-Bit systems.
   If defined you must also define #CAST_TO_U8_HUGE_PTR and #CAST_TO_CONST_U8_HUGE_PTR.
*/
#ifndef HUGE_C
   #define   HUGE_C
   /*! \brief define to optimize code for using only one memory model... */
   #define   HUGE_C_NOT_USED
#endif

/* ************************************************************************** */
/*!
   \def CAST_TO_U8_HUGE_PTR
   \brief Macro to cast a standard memory iso_u8 array pointer to #HUGE_C iso_u8 array pointer.
   \details
   Define this macro only if your compiler needs an explicit cast to a huge pointer.
*/
#ifndef CAST_TO_U8_HUGE_PTR
#ifndef HUGE_C_NOT_USED
#pragma message("WARNING: CAST_TO_U8_HUGE_PTR not defined but HUGE_C is defined. ")
#endif /* !HUGE_C_NOT_USED */
#define   CAST_TO_U8_HUGE_PTR
#endif

/* ************************************************************************** */
/*!
\def CAST_TO_CONST_U8_HUGE_PTR
\brief Macro to cast a standard memory iso_u8 array pointer to const #HUGE_C iso_u8 array pointer.
\details
Define this macro only if your compiler needs an explicit cast to a const huge pointer.
*/
#ifndef CAST_TO_CONST_U8_HUGE_PTR
#ifndef HUGE_C_NOT_USED
#pragma message("WARNING: CAST_TO_CONST_U8_HUGE_PTR not defined but HUGE_C is defined. ")
#endif /* !HUGE_C_NOT_USED */
#define   CAST_TO_CONST_U8_HUGE_PTR
#endif

/* ************************************************************************** */
/*! @} */ /* End group Huge Memory Type Qualifier And Pointer Casts           */
/* ************************************************************************** */

/* ************************************************************************** */
/*!
   \def ISO_DEPRECATED
   \brief Macro to mark functions as deprecated
   \details
   Functions marked with ISO_DEPRECATED will be removed in later versions.

   You can add an empty ISO_DEPRECATED define to our IsoConf.h to disable the warning message.\n
   With the define ISO_REMOVE_DEPRECATED you can disable the compilation of deprecated functions.
*/
#ifndef ISO_DEPRECATED
   #ifdef __GNUC__
      #define ISO_DEPRECATED __attribute__ ((deprecated))
   #elif defined(_MSC_VER)
      #define ISO_DEPRECATED __declspec(deprecated)
   #else /* use empty define */
      #pragma message("WARNING: You need to implement ISO_DEPRECATED for this compiler")
      #define ISO_DEPRECATED
   #endif
#endif /* !ISO_DEPRECATED */

/* ************************************************************************** */
/*! \name Linker Memory Section Defines

   Add this defines only to your IsoConf.h to use special memory locations.
   \n
   IsoConf.h Sample for Core, Base and Clients linker memory sections:
   \code{.c}

   #define ISO_ALLOCATE_CORE_VARS_BEGIN _Pragma ("section\".ISO_Core_Task_data\"")
   #define ISO_ALLOCATE_CORE_VARS_END _Pragma ("section")

   #define ISO_ALLOCATE_BASE_VARS_BEGIN _Pragma ("section\".ISO_Base_Task_data\"")
   #define ISO_ALLOCATE_BASE_VARS_END _Pragma ("section")

   #define ISO_ALLOCATE_CLIENT_VARS_BEGIN _Pragma ("section\".ISO_Client_Task_data\"")
   #define ISO_ALLOCATE_CLIENT_VARS_END _Pragma ("section")

   \endcode
@{ */

/*!
   \def     ISO_ALLOCATE_CORE_VARS_BEGIN
   \brief   Begin of a core driver memory block for static variables
   \def     ISO_ALLOCATE_CORE_VARS_END
   \brief   End of a core driver memory block for static variables
   \def     ISO_ALLOCATE_BASE_VARS_BEGIN
   \brief   Begin of a base driver memory block for static variables
   \def     ISO_ALLOCATE_BASE_VARS_END
   \brief   End of a base driver memory block for static variables
   \def     ISO_ALLOCATE_CLIENT_VARS_BEGIN
   \brief   Begin of a client driver memory block for static variables
   \def     ISO_ALLOCATE_CLIENT_VARS_END
   \brief   End of a client driver memory block for static variables
*/

#ifndef ISO_ALLOCATE_CORE_VARS_BEGIN
   #define ISO_ALLOCATE_CORE_VARS_BEGIN
   #define ISO_ALLOCATE_CORE_VARS_END
#endif /* !ISO_ALLOCATE_CORE_VARS_BEGIN */

#ifndef ISO_ALLOCATE_BASE_VARS_BEGIN
   #define ISO_ALLOCATE_BASE_VARS_BEGIN
   #define ISO_ALLOCATE_BASE_VARS_END
#endif /* !ISO_ALLOCATE_BASE_VARS_BEGIN */

#ifndef ISO_ALLOCATE_CLIENT_VARS_BEGIN
   #define ISO_ALLOCATE_CLIENT_VARS_BEGIN
   #define ISO_ALLOCATE_CLIENT_VARS_END
#endif /* !ISO_ALLOCATE_CLIENT_VARS_BEGIN */



/* ************************************************************************** */
/*! @} */ /* End group Linker memory sections                                 */
/* ************************************************************************** */

/* ************************************************************************** */
/*! \name User Parameter Defines

   Add this defines to your IsoConf.h to use special user parameters.
   If not defined the driver uses as type iso_u32 with 0uL as default value.
   \n
   IsoConf.h Sample void pointer:
   \code{.c}

   #define ISO_USER_PARAM_TYPE      void*
   #define ISO_USER_PARAM_DEFAULT   0

   \endcode
   IsoConf.h Sample with own struct:
   \code{.c}

   #define ISO_USER_PARAM_TYPE      struct { iso_s16 s16Param1; iso_u8 au8Opt[2]; }
   #define ISO_USER_PARAM_DEFAULT   {-1L, {0u,5u}}

   \endcode

@{ */

#ifndef ISO_USER_PARAM_TYPE
   /* use iso_u32 as default */
   #define ISO_USER_PARAM_TYPE      iso_u32
   #define ISO_USER_PARAM_DEFAULT   (0uL)
#else  /* ISO_USER_PARAM_TYPE */
   #ifndef ISO_USER_PARAM_DEFAULT
      #error ISO_USER_PARAM_DEFAULT value not defined for type ISO_USER_PARAM_TYPE.
   #endif /* !ISO_USER_PARAM_DEFAULT */
#endif /* ISO_USER_PARAM_TYPE */

/*! \brief type definition of the user parameter type */
typedef ISO_USER_PARAM_TYPE ISO_USER_PARAM_T;


/* ************************************************************************** */
/*! @} */ /* End group User Parameter                                         */
/* ************************************************************************** */

#if defined(DOXYGEN)
#define ISO_FIX_ISONAME_COMPILER_WARNING
#endif

/* ************************************************************************** */
/*! \name Optional compiler fixes

@{ */
/*!
   \def ISO_FIX_ISONAME_COMPILER_WARNING
   \brief Add this define to your IsoConf.h to use the default definition
          of #CAST_TO_CONST_ISONAME_PTR to fix the ISO_CF_NAME_T* GCC compiler warnings
   \def CAST_TO_CONST_ISONAME_PTR
   \brief Optional definition to explicitly convert #ISO_CF_NAME_T* to a constant pointer
*/

#if defined(ISO_FIX_ISONAME_COMPILER_WARNING)
   #define CAST_TO_CONST_ISONAME_PTR /*lint -e{929} */ (const ISO_CF_NAME_T*)
#else /* defined(ISO_FIX_ISONAME_COMPILER_WARNING) */
#ifndef CAST_TO_CONST_ISONAME_PTR
   #define CAST_TO_CONST_ISONAME_PTR
#endif /* CAST_TO_CONST_ISONAME_PTR */
#endif /* defined(ISO_FIX_ISONAME_COMPILER_WARNING) */

/* ************************************************************************** */
/*! @} */ /* End group Optional compiler fixes                                */
/* ************************************************************************** */

#if defined(DOXYGEN)
#define ISO_REMOVE_TP_FINDFREECHANNEL
#endif

/* ************************************************************************** */
/*! \name Optional wrapper defines

@{ */
/*!
   \def ISO_REMOVE_TP_FINDFREECHANNEL
   \brief Add this define to your IsoConf.h to remove the compilation of iso_coreTlFindFreeChannel() 
          and the wrapper functions depending on it if the FSC module is not enabled. 
*/

#if (!defined(ISO_REMOVE_TP_FINDFREECHANNEL)) || defined(_LAY13_)
/*! \cond HIDDEN_SYMBOLS
    \def ISO_TP_FINDFREECHANNEL
    \brief internal define to enable TP find free channel functions compilation
*/
#define ISO_TP_FINDFREECHANNEL
/*! \endcond */
#endif /* (!defined(ISO_REMOVE_TP_FINDFREECHANNEL)) || defined(_LAY13_) */

/* ************************************************************************** */
/*! @} */ /* End group Optional wrapper defines                                */
/* ************************************************************************** */



/* ************************************************************************ */
/** @} */ /* END addtogroup isoconfig                                    */
/* ************************************************************************ */


/* ************************************************************************ */
/** \addtogroup datalink_types Datalink Layer Type Definitions
    \ingroup coredl mndl
@{
*/
/* ************************************************************************ */

/* Defines */
/* Timing defines */
#define ISO_TIME_0_MS     (ISO_TIME(0L))
#define ISO_TIME_250_MS   (ISO_TIME(250L))      /*  250ms: replaces MSEC_250 */
#define ISO_TIME_100_MS   (ISO_TIME(100L))      /*  100ms:  used for 100 msec. cycle times / rate */
#define ISO_TIME_200_MS   (ISO_TIME(200L))      /*  200ms:  used for 200 msec. cycle times / rate  */
#define ISO_TIME_1000_MS  (ISO_TIME(1000L))     /* 1000ms:  used for 1 sec. cycle times / rate  */
#define ISO_TIME_2000_MS  (ISO_TIME(2000L))     /* 2000ms:  used for 2 sec. cycle times / rate  */
#define ISO_TIME_OUT      (ISO_TIME(1250L))     /**< Communication timeout in ms for expecting an answer from the external CF. */
/* */
#define ISO_TIME_10_MS    (ISO_TIME(10L))       /*   10ms */
#define ISO_TIME_20_MS    (ISO_TIME(20L))       /*   20ms */
#define ISO_TIME_50_MS    (ISO_TIME(50L))       /*   50ms */
#define ISO_TIME_300_MS   (ISO_TIME(300L))      /*  300ms */
#define ISO_TIME_500_MS   (ISO_TIME(500L))      /*  500ms */
#define ISO_TIME_6000_MS  (ISO_TIME(6000L))     /* 6000ms */
/* TODO: add further defines as appropriate */

#define ISO_DUMMY             (0u)      /**< Used in case of unused parameter */
#define ISO_DEFAULT      (0xFFFFu)      /**< 16bit default value for parameter */

/* ************************************************************************ */
/** \brief Enums of control iso_u8 of PGN  ACKM */
typedef enum { ACK = 0, NACK = 1, ACCESS_DENIED = 2, CANNOT_RESPOND = 3 } ISO_ACK_E;

/* ************************************************************************ */
/** \brief Message direction enum (used in #ISO_TPINFO_T field iInfoDirection ) */
typedef enum { received, sended, not_known } ISO_DIR_E;

/* ************************************************************************ */
/** \brief   Typedef of the message transport data structure
    \details Info for application or intern modules about send or received data. \n
             The the values of the fields depend on the ISO_TPREP_E status value of the callback.
    \note    pabData can be the NULL pointer also if dwNumberofBytes has a value greater than zero. \n
    \par

             - record_start:        dwNumberofBytes is zero, pabData not valid
             - record_firstdata:    dwNumberofBytes of the first data packet, pabData valid
             - record_finish:       dwNumberofBytes of received bytes, pabData is valid

             - record_request:      ( application layer specific )

             - send_buffed:         dwNumberofBytes is zero and pabData is the NULL pointer
             - send_start_OK:       dwNumberofBytes is zero, pabData not valid
             - send_packet_request: dwNumberofBytes is zero, pabData not valid ( only direct transfer )
             - send_finished:       dwNumberofBytes is between 0 and 8, pabData is valid \n
                                    dwNumberofBytes contains only the size of the first data given with pabData. \n
                                    (V10.00 feature ID 8312: Do not pass TP session data back to Clients layer)
             - datatrans_abort:     dwNumberofBytes is between 0 and 8, pabData is valid
*/
typedef struct
{
    ISO_DIR_E     iInfoDirection;      /**< \brief Message direction (Data send or received) */
    iso_u32       dwPGN;               /**< \brief PGN of the transported message */
    iso_s16       s16HndIntern;        /**< \brief Network member handle of the internal CF ( or #HANDLE_GLOBAL for incoming PDU2 )  */
    iso_s16       s16HndPartner;       /**< \brief Network member handle of the external CF ( or #HANDLE_GLOBAL for outgoing  PDU2 ) */
#if !defined(CCI_OMIT_ADDRESS_INFO) /* to be removed in V13 BugID 13107 */
    iso_u8        u8SAIntern;          /**< \brief SA of internal user / CF */
    iso_u8        u8SAPartner;         /**< \brief SA of the external user / CF */  /* Hint for V13: u8SAPartner is used as byte5 by the driver for ACK message... */
#endif /* !defined(CCI_OMIT_ADDRESS_INFO) */
    iso_u32       dwNumberofBytes;     /**< \brief Amount of bytes recorded */
    const iso_u8 HUGE_C *pabData;      /**< \brief Pointer to the data buffer or NULL pointer */
    iso_u8        bMsgPrio;            /**< \brief Priority of the CAN message */
/* V10.0 Parameter for data link callback function of CF */
    iso_s16          s16OwnCfHnd;      /**< \brief CF handle of the entry for which the callback is triggered */
    ISO_USER_PARAM_T userParam;        /**< \brief User defined parameter set with iso_NmMemberNew() for data link CB */
#if defined(CCI_TIMESTAMP)
   iso_s32        s32TimeStamp;        /**< \brief Time stamp of the message in ms */
#endif /* defined(CCI_TIMESTAMP) */
} ISO_TPINFO_T;

typedef ISO_TPINFO_T *ISO_TPINFO_t;   /**< \brief Pointer typedef of the message transport data structure  */

/* ************************************************************************ */
/** \brief Enum for informing the application about a running TP or incoming ISO Message with lower or equal 8 bytes  */
typedef enum
{
    record_start,           /**< An extern ECU has started a TP */
    record_firstdata,       /**< An extern ECU has send the first data message (7 bytes, TP ...)  */
    record_finish,          /**< An extern ECU has finished sending data (8 bytes, TP ...)  */
    record_request,         /**< An extern ECU has sent an request - only Multi node API */
    send_buffed,            /**< An intern ECU has called IsoOpenTP successfully, data buffered */
    send_start_OK,          /**< An intern ECU has started a transport successfully */
    send_packet_request,    /**< The transport module is ready to send the next data packet ( 7 Bytes ) - Direct transfer only  */
    send_finished,          /**< An intern ECU has finished a transport successfully */
    datatrans_abort,        /**< A transport is aborted */
    tl_internal             /**< only for base driver (driver internal cmd IsoTL_ReceivedData or IsoTL_ReadyForNextData ) */
} ISO_TPREP_E;

/* ************************************************************************ */
/** \brief transport layer command enum (used in #ISO_CORE_DD_MSGINFO_T field u4TlCmd ) */
typedef enum
{
   IsoTL_StatusInfo = 0,      /**< Process status information ( #ISO_TPREP_E) */
   IsoTL_ProvideNextData = 1, /**< Send next data block to TL */
   IsoTL_ReceivedData = 2     /**< Received new data block (ETP packet group) */
#if defined(ISO_ETP_IN_PKG)
  ,IsoTL_ReadyForNextData = 3 /**< Ready for sending CTS / ECTS to receive next data group */
#endif /* defined(ISO_ETP_IN_PKG) */
} ISO_TLCMD_E;

/* ************************************************************************ */
/**
   \brief Typedef of the core to base data message information structure
*/
typedef struct
{
   iso_bitfield   u8TpChannel : 8;     /**< \brief Core driver transport channel ( 0 ==no TP Channel ) */
   /* for receiving prio only Bits 0-3 needed !!! */
   iso_bitfield   u8Priority : 8;      /**< \brief Bits 0-3: Priority of PGN ( 7 for (E)TP ); Bits 4-7: Optional CAN channel priority (0 is default) */
   iso_bitfield   u4TlCmd : 4;         /**< \brief TL command (see #ISO_TLCMD_E) */
   iso_bitfield   u4CanIdx : 4;        /**< \brief CAN node index */
   iso_bitfield   u4TpStatus : 4;      /**< \brief Message status (see #ISO_TPREP_E ) */
   iso_bitfield   qSended : 1;         /**< \brief ISO_TRUE if sended else received */

   iso_u32        u32PGN;              /**< \brief PGN of the transported message */
   iso_s16        s16HndIntern;        /**< \brief Network member handle of the internal CF ( or #HANDLE_GLOBAL for incoming PDU2 )  */
   iso_s16        s16HndPartner;       /**< \brief Network member handle of the external CF ( or #HANDLE_GLOBAL for outgoing  PDU2 ) */
#if !defined(CCI_OMIT_ADDRESS) /* to be removed in V13 */
   iso_u8         u8SAIntern;          /**< \brief SA of internal user / CF (TODO remove if not needed) */
   iso_u8         u8SAPartner;         /**< \brief SA of the external user / CF (TODO remove if not needed) */
#endif /* !defined(CCI_OMIT_ADDRESS) */
   iso_u8         u8ClientID;          /**< \brief Client identifier - set from base before forwarding to clients else not valid */
   iso_u32        u32DataStartIndex;   /**< \brief Data start index (StartIndex = Offset + 1) */
   iso_u32        u32DataLength;       /**< \brief Number of data bytes (or ISO_TPINFO_T dwNumberofBytes) */
#if defined(CCI_TIMESTAMP)
   iso_s32        s32TimeStamp;        /**< \brief Time stamp of the message in ms */
#endif /* defined(CCI_TIMESTAMP) */
} ISO_CORE_DD_MSGINFO_T;

/* ************************************************************************ */
/** @} */ /* END group datalink_types Datalink Layer Type Definitions       */
/* ************************************************************************ */

/*! \addtogroup common_init_types Type definitions of common callback functions
    \ingroup core_init base_mn_init clientscommon
  @{
*/

/****************************************************************************/
/*!
   \brief   Type definition of time stamp callback function.

   \retval  iso_s16
            current time in milliseconds since ECU startup.
 */
typedef iso_s32   (*ISO_CbGetTimeMs_t)( void );

/****************************************************************************/
/*!
   \brief   Type definition of the watchdog trigger callback function.
 */
typedef void      (*ISO_CbTriggerWatchdog_t)( void );

/****************************************************************************/
/*!
   \brief   Type definition of the error report callback function.

   \param[in]  \wp{u8Function,  iso_u8}
                 Number to identify the function which reports the error.
   \param[in]  \wp{u8Location,  iso_u8}
                 Error location (module or layer) ( M_DATA, M_USER, M_NET ...)
   \param[in]  \wp{s16ErrCode,  iso_s16}
                 Error code ( E_NO_ERR, E_UNKNOWN_ERR, E_WARN ...)
   \param[in]  \wp{s32TimeMs,  iso_s32}
                 Time stamp in milliseconds
 */
typedef void      (*ISO_CbErrorHandler_t)( iso_u8 u8Function, iso_u8 u8Location, iso_s16 s16ErrCode, iso_s32 s32TimeMs);

/* ************************************************************************ */
/** @} */ /* END group common_init_types                                    */
/* ************************************************************************ */

/*! \addtogroup core_init_types Type definitions of specific callback functions
    \ingroup core_init
  @{
*/
/* ************************************************************************ */
/** \brief Type definition of the CAN message send callback function.
    \details This function must be implemented from the application and given to the driver with iso_CoreInit()
    \param[in]    \wp{u8CanIdx, iso_u8}
                  CAN-bus index number \n
                  Range: 0u .. ( ISO_CAN_NODES - 1u )
    \param[in]    \wp{u32MsgId, iso_u32}
                  CAN message identifier
    \param[in]    \wpp{au8MsgData, const #iso_u8[]}
                  CAN message data array pointer
    \param[in]    \wp{u8Dlc, iso_u8}
                  CAN message data length  \n
                  Range: 0u .. 8u
    \retval       iso_s16
                  - #E_NO_ERR on success
                  - #E_OVERFLOW on send FIFO full
                  - #E_COM on bus-off

*/
typedef iso_s16 (*ISO_DL_CbCanSend_t)(iso_u8 u8CanIdx, iso_u32 u32MsgId, const iso_u8 au8MsgData[], iso_u8 u8Dlc);

/* ************************************************************************ */
/** \brief Type definition of the callback function for returning the current available CAN message FIFO size.
    \details This function must be implemented from the application and given to the driver with iso_CoreInit().
             The function should return the free entries of the buffer and NOT the size of the buffer.
    \param[in]    \wp{u8CanIdx, iso_u8}
                  CAN-bus index number \n
                  Range: 0u .. ( ISO_CAN_NODES - 1u )
    \param[in]    \wp{u8MsgPrio, iso_u8}
                  An ISO 11783 CAN message priority \n
                  The priority corresponds to the the priority bits 26 to 28 of a can message ID.
    \retval       iso_s16
                  -   0 .. 0x7FFF available FIFO
                  - < 0 in case of an error
                  - #E_COM on bus-off

    \par Hint
    The application is not required to provide different queues.
    The parameters can be used if different CAN send queues are used.
    It is recommended to provide at least a separate queue for each CAN node.

*/
typedef iso_s16 (*ISO_DL_CbGetFreeCanSendFiFo_t)(iso_u8 u8CanIdx, iso_u8 u8MsgPrio);

/* ************************************************************************ */
/*! \brief Type definition of the data distribution callback function.
    \details This function must be implemented from the application and given to the driver with iso_CoreInit()
    \param[in]   \wpp{psMsgInfo, const #ISO_CORE_DD_MSGINFO_T*}
                 Pointer to the message information data
    \param[in]   \wpp{pau8Data, const #iso_u8 HUGE_C []}
                 Pointer to the message data byte array or NULL pointer
    \param[in]   \wp{u32DataSize, iso_u32}
                  Size of the given message data byte array
*/
typedef void (*ISO_CoreBase_CbDoMsg_t)(const ISO_CORE_DD_MSGINFO_T *psMsgInfo, const iso_u8 HUGE_C pau8Data[], iso_u32 u32DataSize);


/* ************************************************************************ */
/*! \brief Type definition of the optional TP and ETP RTS filter call back function for incoming messages

   If set with iso_CoreInit(), the callback function can be used to check incoming transport messages (RTS, BAM, E_RTS)
   and reject unwanted messages.

   \param[in]  \wp{u32PGN,  iso_u32}
                  PGN of the transported message
   \param[in]  \wp{s16CfHndIntern,  iso_s16}
                  Network member handle of the internal CF
   \param[in]  \wp{s16CfHndPartner,  iso_s16}
                  Network member handle of the external CF
   \param[in]  \wp{u32TpSize,  iso_u32}
                   Size of the incoming data transport in bytes

   \retval  iso_bool
               - ISO_TRUE  - Receive incoming transport message
               - ISO_FALSE - Reject incoming transport message
*/
typedef iso_bool ( *ISO_TP_Filter_fpt )(iso_u32 u32PGN, iso_s16 s16CfHndIntern, iso_s16 s16CfHndPartner, iso_u32 u32TpSize );

/* ************************************************************************ */
/** @} */ /* END group core_init_types                                      */
/* ************************************************************************ */


/* ************************************************************************ */
/** \addtogroup driverpart3
@{
*/
/* ************************************************************************ */

/*! \name Optional receiving of extended transport protocol messages
     Can be enabled the define #ISO_ETP_IN or #ISO_ETP_IN_PKG
  @{ */

/*! \brief Callback mode flag: free memory */
#define ISO_ETP_MEMORY_FREE 0u

/*! \brief Callback mode flag: allocate memory */
#define ISO_ETP_MEMORY_ALLOCATE 1u

/*! \brief Callback mode flag: check if ready for receiving next data
     only used for "file IO" (if data pointer is set to null in the "ISO_ETP_MEMORY_ALLOCATE" callback call)
*/
#define ISO_ETP_MEMORY_RECEIVE_READY 2u

/*! @} */

/* ************************************************************************ */
/*! \brief Type definition of the extended ETP memory management call back function for incoming CAN Messages

   If enabled with the define #ISO_ETP_IN the callback function of this type
   must be set with iso_BaseSetETPMemoryCb() to enable the receiving from ETP CAN messages.

   If enabled with the define #ISO_ETP_IN_PKG the callback function
   is used to receive incoming ETP messages in packet groups (<= 1785 bytes) without the need for allocating an buffer (set *pau8Data = 0).
   In this case the received data are forwarded with the function iso_BaseSetETPMemoryCb() to the application.

   \param[in]  \wp{u32PGN,  iso_u32}
                  PGN of the transported message
   \param[in]  \wp{s16CfHndIntern,  iso_s16}
                  Network member handle of the internal CF
   \param[in]  \wp{s16CfHndPartner,  iso_s16}
                  Network member handle of the external CF
   \param[in]  \wp{pau8Data, iso_u8**}
                  Pointer to data byte array pointer
   \param[in]  \wp{u32DataLength,  iso_u32}
                - u8Mode #ISO_ETP_MEMORY_ALLOCATE, #ISO_ETP_MEMORY_FREE:
                  Size of the needed data byte array (ETP size)
                - u8Mode #ISO_ETP_MEMORY_RECEIVE_READY: ETP size on first call else size of next packet group
   \param[in]  \wp{u8Mode, iso_u8}
               Calling mode: \n
               - ETP memory management enabled with define #ISO_ETP_IN or #ISO_ETP_IN_PKG:
                 - #ISO_ETP_MEMORY_FREE: Free buffer stored in pau8Data (called after ETP EOMA)
                 - #ISO_ETP_MEMORY_ALLOCATE: Allocate memory and store pointer in pau8Data (Called after receiving an ETP RTS) \n
                   With #ISO_ETP_IN_PKG the *pau8Data can be set to a ETP size buffer (normal ETP_IN)
                   or to a NULL pointer (no buffer). In second case iso_BaseEtpBufferWrite() called to forward the data to the application.
                 - #ISO_ETP_MEMORY_RECEIVE_READY: only called with define #ISO_ETP_IN_PKG and memory null pointer \n
                   to check if the application is ready for the next ETP data.
                   Return E_NO_ERR if ready or E_BUSY if not.
   \retval  iso_s16
               - E_NO_ERR on success or u8Mode := 0u
               - E_OUT_OF_MEMORY for u8Mode := 1u if it was not possible to allocate the needed memory
               - E_BUSY for u8Mode := 2u and the memory is not ready for writing the next packets.


*/
typedef iso_s16( *ISO_ETP_Memory_fpt )(iso_u32 u32PGN, iso_s16 s16CfHndIntern, iso_s16 s16CfHndPartner,
                                       iso_u8* pau8Data[], iso_u32 u32DataLength, iso_u8 u8Mode );


/* ************************************************************************ */
/** @} */  /* END group driverpart3 Part 3 Configuration                    */
/* ************************************************************************ */


/* *********************** Network Management ***************************** */
/** \addtogroup nmma_types Network Management Type Definitions
    \ingroup nmma base_nmma
@{
*/

/* ************************************************************************ */
/*! \brief type definition of a CF ISOBUS NAME
    \details A control function (CF) name has always 8 bytes.
*/
typedef iso_u8 ISO_CF_NAME_T[8];

/* ************************************************************************ */
/** \brief CF / User network location
*/
typedef enum
{
    intern = 0,     /**< Internal CF / user */
    network = 1,    /**< External CF / user */
    thisMember = 2, /**< Event is for this internal CF / user */
    notdef = -1     /**< Value not valid */
} ISOUSERHOME_e;

/* ************************************************************************ */
/** \brief CF network location (for search function)
*/
typedef enum
{
   IsoCf_Internal = 0,    /**< Internal CF / user */
   IsoCf_External = 1,    /**< External CF / user */
   IsoCf_All      = 3     /**< Value not valid */
} ISO_CF_LOCATION_e;

/* ************************************************************************ */
/** \brief User function (similar with NAME function)
    \details Used for intern sorting the ISO user and (driver module) identification
*/
typedef enum
{    working_set_master = 0,
     task_controller = 1,
     virtual_terminal = 2,
     tractor_ecu = 3,
     auxiliary = 4,
     sequenz_control_master = 5,
     working_set_member = 6,
     steering_control = 7,
     off_vehicle_gateway = 8,
     network_interconnection_unit = 9,
     unknown = 10,
     file_server = 11,
     virtual_cf  = 12,  /* virtual CF on this network segment managed from the NIU */
     bridged_cf  = 13,  /* NIU bridged CF on this network segment */
     datalogger  = 14,
     tim_server = 16,
     tim_server_slave = 17,  /**< Use only in clients see IsoClientsReadListofExtHandles() */
     all_clients = 20,
     all_server = 21,
     undefined = -1
} ISO_USERFUNC_e;

/* ************************************************************************ */
/** \brief Announcement state of ISO user */
typedef enum
{    isouser_OK,                   /**< Network member if full announced ( logged on ) */
     isouser_NOTOK,                /**< State is not announced (off, empty, preannounce ..) */
     isouser_last
} ISO_USERSTAAPP_e;

/* ************************************************************************ */
/** \brief Network management event type */
typedef enum
{
     Isonet_MemberActive,          /**< There is a new member on network (intern or extern) */
     Isonet_MemberAddressConflict, /**< Network member has lost address conflict */
     Isonet_MemberInactive,        /**< Member stopped or commanded address */
     Isonet_MemberNewAddress,      /**< Address claimed after SA conflict */
     Isonet_MemberAddressViolation,/**< Address violation: internal SA conflicts with SA from extern msg */
#if defined(ISO_NM_MSG_MONITOR)
     Isonet_MemberTimeout,         /**< Message monitor event: No CAN message received in the given interval */
     Isonet_MemberResume,          /**< Message monitor event: Received first message after a timeout */
#endif /* defined(ISO_NM_MSG_MONITOR) */
     Isonet_MemberAdd,            /**< Core/base internal: Add(ed) CF to list */
     Isonet_MemberRemove,         /**< Core/base internal: Remove CF from list () */
#if defined (CCI_HSI)
     Isonet_HsiActive,
     Isonet_HsiInactive,
#endif /* defined (CCI_HSI) */
     Isonet_Last
} ISO_NETEVENT_e;

/* ************************************************************************ */
/** \brief      Typedef of the network management event structure
    \details
        The event structure is used from the network management callback function,
        to inform the user / CF about changes of the announcement state of this or an external CF. \n
        The following list shows the possible events depending on the member location: \n

        - \b eMemberRefer == #thisMember:\n
            \n
            - eNetEvent == #Isonet_MemberActive \n
              250 ms after the "address claimed" message for this CF was sent.
            - eNetEvent == #Isonet_MemberNewAddress \n
              250 ms after this CF has lost an address conflict and claimed a new source address.

            - eNetEvent == #Isonet_MemberAddressConflict \n
              The CF has lost its source address and will claim a new one. \n
              The field wSAMember contains already the new source address.
            - eNetEvent == #Isonet_MemberInactive \n
              if this CF has send "can not claim source address", \n
              or if it is logged out with a iso_NmMemberLoggedOut() function call \n
              or if the "commanded address" message is accepted and the CF has to claim the new address. \n
              The field wSAMember contains the old source address or #ISO_NULL_ADDRESS \n
              if the CF has lost an address conflict and can not claim a new source address. \n
              In the case of the commanded address message wSAMember contains the new source address.

            - eNetEvent == #Isonet_MemberAddressViolation \n
              if an external message is received with the same source address. \n
              The ECU driver sends in this case automatically the address claimed message for this CF. \n
        \n
        - \b eMemberRefer == #network:\n
            \n
            - eNetEvent == #Isonet_MemberActive \n
              250 ms after the "address claimed" message of this CF arrived.
            - eNetEvent == #Isonet_MemberAddressConflict \n
              The extern CF has lost its source address and has to claim a new one. \n
              The field wSAMember contains the conflicted source address.
            - eNetEvent == #Isonet_MemberInactive \n
              if the external CF has sent "can not claim source address", \n
              or if the CF is logged out in case of a alive timeout or a iso_NmMemberLoggedOut() function call. \n
        \n
        - \b eMemberRefer == #intern: \n
          not used in the callback ( used only internal to identify internal CFs in the network management member table).

*/
typedef struct
{
    ISO_NETEVENT_e   eNetEvent;     /**< \brief Which event occurs in the network member administration? */
    ISOUSERHOME_e    eMemberRefer;  /**< \brief Which member concerned: Owner of this callback, another internal or external CF */
    iso_s16          s16OwnCfHnd;   /**< \brief CF handle of the entry for which the callback is triggered */
    iso_s16          s16Handle;     /**< \brief Network member handle of the CF / user (event source CF handle) */
    iso_u8           u8SAMember;    /**< \brief Current source address (SA) of the network member */
    ISO_USER_PARAM_T userParam;     /**< \brief User defined parameter set with iso_NmMemberNew() */
#if defined(ISO_CLIENT_NETWORK_DISTRIBUTOR) || defined (ISO_BASE_SHADOW_COPY)  /* additional fields for a shadow copy */
    ISO_USERFUNC_e   eUserFunction; /**< Function of user / CF on the bus (internal used) */
    ISO_CF_NAME_T    cfName;        /**< ISOBUS name of the control function  */
#endif /* defined(ISO_CLIENT_NETWORK_DISTRIBUTOR) || defined (ISO_BASE_SHADOW_COPY) */
} ISONETEVENT_T;

typedef ISONETEVENT_T *ISONETEVENT_t;    /**< Pointer typedef of the network event structure */

/* ************************************************************************ */
/*! \brief Type definition of network event callback function

   \param[in]  \wpp{psEv, const #ISONETEVENT_T*}
               Pointer to the network management event data
*/
typedef void(*ISO_NM_CbCfEvent_t)(const ISONETEVENT_T* psEv);


/* ************************************************************************ */
/** \brief Typdef of the CF name field structure - see ISO Part 5 table 1 */
typedef struct
{
   iso_bitfield   bSelfConf : 1;    /**< \brief self-configurable-address ECU? */
   iso_bitfield   bIndGroup : 3;    /**< \brief NAMES associated with industries */
   iso_bitfield   bDevClassInst : 4;/**< \brief Identifier if a device class more than 1 times in net */
   iso_bitfield   bDevClass : 7;    /**< \brief ISO Defined */
   iso_bitfield   bReserved : 1;    /**< \brief Reserved (not used) */
   iso_bitfield   bFunction : 8;    /**< \brief ISO defined, -> SA */
   iso_bitfield   bFunctionInst : 5;/**< \brief subgroup of function */
   iso_bitfield   bEcuInstance : 3; /**< \brief which ECU associated with a given function */
   iso_bitfield   wManufCode : 11;  /**< \brief ISO defined */
#ifdef ISO_LIMIT_BITFIELD_TO_16BIT  /* for 16-Bit compilers */
   /* HINT: we can not use a 21 bit bitfield with a 16-bit compiler - use iso_u32 */
   iso_u32        dwIdentNumb;      /**< \brief Used when the NAME is not unique in same network */
#else  /* ISO_LIMIT_BITFIELD_TO_16BIT*/
   iso_bitfield   dwIdentNumb : 21; /**<   \brief Used when the NAME is not unique in same network */
#endif /* ISO_LIMIT_BITFIELD_TO_16BIT */

   

} ISONAMEFIELD_T;

typedef ISONAMEFIELD_T *ISONAMEFIELD_t; /**< Pointer typdef of the CF name field structure */

/* ************************************************************************ */
/** \brief   Typedef of the ISO CF/user information data structure */
typedef struct
{
    iso_s16          s16Handle;           /**< \brief Network member handle of the CF / user */
    iso_u8           u8SourceAddress;     /**< \brief Source address (SA) of the control function (CF) / user */
    iso_u8           u8CanIdx;            /**< \brief CAN-Bus node / index of the control function (CF) / user */
    ISO_CF_NAME_T    au8Name;             /**< \brief CF ISOBUS NAME */
    ISO_USERFUNC_e   eIsoUserFunct;       /**< \brief Internal used CF function type */
    iso_bitfield     bExternalCf : 1;     /**< \brief External CF on the CAN network */
    iso_bitfield     bIsAnnounced : 1;    /**< \brief ISO_TRUE if the CF is active and full announced */
    iso_bitfield     bIsActive : 1;       /**< \brief NIU specific (for normal applications use bIsAnnounced):
                                                      ISO_TRUE if the CF is not in an error state or logged off */
/* unused iso_bitfield     bIsAclPending : 1;   \brief ISO_TRUE if an external CF has not send yet it's "Address claimed" (ACL) message after a "Request for ACL" message */
}  ISO_CF_INFO_T;

/* ************************************************************************ */
/** \name CF helper functions
   @{ */

/** \brief Control function (CF) data of an ISO user - used from the client modules */
typedef struct
{
   ISO_CF_NAME_T    acMemName;           /**< CF Name */
   ISO_USERFUNC_e   eMemFunct;           /**< Function of network member on the bus */
   iso_s16          s16MmHandle;         /**< Handle of member ( CF / user ) */
   iso_u8           u8MemSrcAdd;         /**< Source address (SA) */
   iso_bool         bFullyAnnounced;     /**< ISO_TRUE if CF is fully annonced else ISO_FALSE */
   iso_bool         bExternalCf;         /**< ISO_TRUE if CF is an external CAN network member; ISO_FALSE if an internal CF */
} ISOMEMBDAT_T;

/*! \brief iso_nmDoCmd() NM command / function enumeration.
    Hint: iso_nmDoCmd() is a special Base/Core wrapper function to reduce the number of interface functions.
*/
typedef enum
{
/* NmCmd_CheckCfIsAnnounced = 0,  removed
   NmCmd_CheckUsersAnnounced = 1, removed */
   NmCmd_TriggerAddressClaim = 2,
   NmCmd_CfLogout = 3,
   NmCmd_CfExternAdd = 4 
   /*     NmCmd_GetCanNodeFromCfHandle = 5, removed, use iso_NmGetCanIdxFromCfHandle() instead
     NmCmd_CheckCfIsValid = 6,  removed
     NmCmd_CheckHndIsValid = 7, removed 
     NmCmd_CheckCfIsPassive = 8 removed */
} ISO_NM_CMD_Te;

/*! \brief   Function pointer declaration for network event callback function of a CF
    \details This function must be implemented from the application and given to the driver with iso_CoreInit()
    \param[in]  \wpp{psNetEv, const #ISONETEVENT_T*}
                  Pointer to the event data
*/
typedef void(*ISO_CoreBase_CbIsoNetwork_t)(const ISONETEVENT_T* psNetEv);

/** @} */


/* ************************************************************************ */
/** @} */ /* END group nmma_types Network Management Type Definitions       */
/* ************************************************************************ */

/* ************************************************************************ */
/*! \ingroup base_mn_init
    \brief  Callback function pointer declaration for forwarding CAN messages to the clients
    \details This function must be implemented from the application and given to the driver with iso_BaseInit()
    \param[in]   \wpp{psMsgInfo, const #ISO_CORE_DD_MSGINFO_T*}
                 Pointer to the message information data
    \param[in]   \wpp{pau8Data, const #iso_u8 HUGE_C []}
                 Pointer to the message data byte array or NULL pointer
    \param[in]   \wp{u32DataSize, iso_u32}
                  Size of the given message data byte array
*/
typedef void(*ISO_BaseClients_CbDoMsg_t)(const ISO_CORE_DD_MSGINFO_T *psMsgInfo, const iso_u8 HUGE_C pau8Data[], iso_u32 u32DataSize);


/* ************************************************************************ */
/*! \ingroup mndl
    \brief  Function pointer declaration for data link callback function of a CF
    \details This function must be implemented from the application and given to the driver with iso_BaseMemberAdd()
    \param[in]  \wp{eTpRep,  ISO_TPREP_E}
                   Status of the message
    \param[in]  \wpp{psTpInfo, const #ISO_TPINFO_T *}
                    Pointer to the message data
*/
typedef void(*ISO_DD_CbDaTrans_t)(ISO_TPREP_E eTpRep, const ISO_TPINFO_T* psTpInfo);


/* *********************** External NIU Definitions *********************** */
#if defined(ISO_EXTERNAL_NIU) || defined(DOXYGEN)
/** \addtogroup grp_extniutypedef External NIU Type Definitions
 @{
*/

/*! \brief typedef of the CAN Message structure*/
typedef struct
{
   iso_u32  u32Id;          /**< \brief CAN identifier */
   iso_u8   u8Node;         /**< \brief Bit 0..3: CAN node index */
   iso_u8   u8Length;       /**< \brief CAN data length 0..8 */
   iso_u8   au8Data[8];     /**< \brief CAN data */
   iso_s32  s32TimeStamp;   /**< \brief time received in ms */
} ISO_NL_CAN_MSG_T;

/*! \brief Function pointer for receiving CAN messages
   \param[in]  \wp{psMessage, ISO_NL_CAN_MSG_T*}
               Pointer to the message.
   \retval     iso_s16
               - #E_NO_ERR on success
*/
typedef iso_s16 (*ISO_NL_CbMsgReceived_t)(ISO_NL_CAN_MSG_T* psMessage);

/*! \brief Function pointer for calling the external NIU cyclic */
typedef void (*ISO_NL_CbCyclicCall_t)(void);

/* ************************************************************************ */
/** @} */ /* END group grp_extniutypedef External NIU Type Definitions      */
#endif
/* ************************************************************************ */


/* ************************************************************************ */
/* **************** DEFINES *********************************************** */
/* ************************************************************************ */

/* ************************************************************************ */
/** \defgroup isodefines Defines */
/** \defgroup isofuncnames Function Names
    \ingroup  isodefines
*/
/* ************************************************************************ */
/** \defgroup isodevclass Device Classes
    \ingroup  isodefines
*/
/* ************************************************************************ */
/** \defgroup isopgns PGNs - Parameter Group Numbers
    \ingroup  isodefines
*/
/* ************************************************************************ */
/** \defgroup isospns SPNs - Suspect Parameter Numbers
    \ingroup  isodefines
*/
/* ************************************************************************ */
/** \defgroup isofmis FMIs (see J1939-73)
    \ingroup  isodefines
*/
/* ************************************************************************ */
/** \defgroup isodefslayer78 Common definitions for LAYER 7, 8
    \ingroup  isodefines
*/
/* ************************************************************************ */
/** \defgroup errorhand Errorhandler Definitions
    \ingroup  isodefines
    \brief This section contains the definitions for the error responses.
    \see IsoErrorhandlerInit
*/
/* ************************************************************************ */

#if defined(CCI_USE_NAMESPACE) && defined(__cplusplus)
#include "IsoCommonDef.hpp"
#else    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) -> use C defines */
/* ************************************************************************ */
/** \addtogroup isodefines
    @{
*/

/** \name ISO special source addresses
@{
*/
/* SAs and handles with special meaning */
#define ISO_NULL_ADDRESS    254u    /**< \brief 0xFEu NULL address - only sender with network man. */
#define ISO_GLOBAL_ADDRESS  255u    /**< \brief 0xFFu GLOBAL address - only destination address field */

#define HANDLE_UNVALID  (-1)    /**< \brief 0xFFFF Invalid or unused handle */
#define HANDLE_GLOBAL  32767    /**< \brief 0x7FFF pseudo handle to address a global destination */

/** @} */

/** @} */ /* END isodefines */
/* ************************************************************************ */
#endif    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) */

/* ************************************************************************ */
/* include PGN and SPN definitions                                          */
/* ************************************************************************ */
#if defined(CCI_USE_NAMESPACE) && defined(__cplusplus)
#include "IsoPgnDef.hpp"
#else    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) */
#include "IsoPgnDef.h"
#endif   /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) */
/* ************************************************************************ */

#if defined(CCI_USE_NAMESPACE) && defined(__cplusplus)
/* IsoCommonDef.hpp is already included above */
#else    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) */

/* ************************************************************************ */
/* Name function defines                                                    */
/* ************************************************************************ */

/** \addtogroup isofuncnames
@{
*/

/** \name Industry non-specific function defines (other see https://www.isobus.net/isobus/nameFunction/index )
@{
*/
#define F_ENGINE                                  0u     /**< Function: engine 1 */
#define F_AUX_POWER_UNIT                          1u     /**< Function: auxiliary power unit - Power source for OS */
#define F_ELEC_PROPULSION_CONTROL                 2u     /**< Function: electric propulsion control */
#define F_TRANSMISSION                            3u     /**< Function: transmission */
#define F_BRAKES_SYSTEMCONTROL                    9u     /**< Function: system control of brakes */
#define F_RETARDER_ENGINE                        12u     /**< Function: retarder */
#define F_RETARDER_DRIVELINE                     13u     /**< Function: retarder driveline */
#define F_CRUISE_CONTROL                         14u     /**< Function: cruise control */
#define F_STEERING_CONTROL                       16u     /**< Function: steering controller */
#define F_AERODYNAMIC_CONTROL                    22u     /**< Function: aerodynamic controller */
#define F_VEHICLE_NAVIGATION                     23u     /**< Function: vehicle navigation */
#define F_NETWORK_INTERCONNECT_UNIT              25u     /**< Function: network interconnect unit ( NIU ) */
#define F_OFF_VEHICLE_GATEWAY                    28u     /**< Function: off vehicle gateway */
#define F_VTERMINAL                              29u     /**< Function: virtual terminal */
#define F_AUXILIARY_DEVICE                       57u     /**< Operator Controls, Steering Column \n
                                                              or auxiliary inputs ... */
#define F_FILESERVER                             61u     /**< Function: file server / printer */
#define F_NOT_AVAILABLE                         255u     /**< Function: not available function; used as a place holder for all functions */
/** @} */


/** \name Industry group 2, device class 0 functions (functions for other device classes see link above)
@{ */
#define F_NONVIRTUAL_TERMINAL                   128u
#define F_OPERATOR_CONTROL                      129u     /**< Operator Controls,  Auxiliary control inputs */
#define F_TASKCONTROL                           130u
#define F_POSITION_CONTROL                      131u
#define F_MACHINE_CONTROL                       132u
#define F_FOREIGN_OBJECT_DETECTION              133u
#define F_TRACTOR_ECU                           134u
#define F_SEQUENZ_CONTROL_MASTER                135u
#define F_PRODUCT_DOSING                        136u
#define F_PRODUCT_TREATMENT                     137u
#define F_DATALOGGER                            139u
#define F_DECISION_SUPPORT                      140u
#define F_LIGHTING_CONTROLLER                   141u
#define F_TIMSERVER                             142u
/** @} */
/** @} */ /* END isofuncnames */
/* ************************************************************************ */

/** \addtogroup isodevclass
@{
*/
/** \name Device classes for industry group 2
@{ */
#define DC_NONSPECIFIC_SYSTEM                0u    /**< Device Class Non-Specific-System        */
#define DC_TRACTOR                           1u    /**< Device Class Tractor                    */
#define DC_TILLAGE                           2u    /**< Device Class Tillage                    */
#define DC_SECONDARY_TILLAGE                 3u    /**< Device Class Secondary Tillage          */
#define DC_PLANTERS_SEEDERS                  4u    /**< Device Class Planters/ Seeders          */
#define DC_FERTILIZERS                       5u    /**< Device Class Fertilizers                */
#define DC_SPRAYERS                          6u    /**< Device Class Sprayers                   */
#define DC_HARVESTERS                        7u    /**< Device Class Harvesters                 */
#define DC_ROOT_HARVESTERS                   8u    /**< Device Class Root Harvesters            */
#define DC_FORAGE                            9u    /**< Device Class Forage                     */
#define DC_IRRIGATION                       10u    /**< Device Class Irrigation                 */
#define DC_TRANSPORT_TRAILER                11u    /**< Device Class Transport/Trailer          */
#define DC_FARM_YARD_OPERATIONS             12u    /**< Device Class Farm Yard Operations       */
#define DC_POWERED_AUXILIARY_DEVICES        13u    /**< Device Class Powered Auxiliary Devices  */
#define DC_SPECIAL_CROPS                    14u    /**< Device Class Special Crops              */
#define DC_EARTH_WORK                       15u    /**< Device Class Earth Work                 */
#define DC_SKIDDER                          16u    /**< Device Class Skidder                    */
#define DC_SENSORSYSTEMS                    17u    /**< Device Class Sensor systems             */
#define DC_TIMBER_HARVESTERS                19u    /**< Device Class Timber harvesters          */
#define DC_FORWARDERS                       20u    /**< Device Class Forwarders                 */
#define DC_TIMBER_LOADERS                   21u    /**< Device Class Timber loaders             */
#define DC_TIMBER_PROCESSING_MACHINES       22u    /**< Device Class Timber processing machines */
#define DC_MULCHERS                         23u    /**< Device Class Mulchers                   */
#define DC_UTILITY_VEHICLES                 24u    /**< Device Class Utility vehicles           */
#define DC_SLURRY_APPLICATORS               25u    /**< Device Class Slurry applicators         */
#define DC_FEEDERS_MIXERS                   26u    /**< Device Class Feeders/Mixers             */
#define DC_WEEDERS                          27u    /**< Device Class Weeders                    */

/** @} */
/** @} */ /* END isodevclass */

/* ************************************************************************ */
/** \addtogroup errorhand
@{
*/

/* ErrorCause - common */
/** \name Common error codes
    \details These defines are used as parameter iCause in the error handler callback function and as return value of the interface functions.
@{
*/
#define E_NO_ERR            ( 0 )  /**< \brief ErrorCause: No error */
#define E_UNKNOWN_ERR       (-1 )  /**< \brief ErrorCause: Unknown error */
#define E_WARN              (-2 )  /**< \brief ErrorCause: System warnings */
#define E_DEFAULT           (-3 )  /**< \brief ErrorCause: Called function works with default values */
#define E_BUSY              (-4 )  /**< \brief ErrorCause: Repeated calling of a function */
#define E_RANGE             (-5 )  /**< \brief ErrorCause: One ore more input parameter wrong */
#define E_OVERFLOW          (-6 )  /**< \brief ErrorCause: Buffer overflow */
#define E_RD_WR             (-7 )  /**< \brief ErrorCause: Write- or read-error */
#define E_NOACT             (-8 )  /**< \brief ErrorCause: Called functionality has not been executed */
#define E_COM               (-9 )  /**< \brief ErrorCause: Communication error with other application hardware */
#define E_CONFIG            (-10)  /**< \brief ErrorCause: Configuration error (function call not possible ) */
#define E_CHECKSUM          (-11)  /**< \brief ErrorCause: Checksum error */
/** @} */
/* ISO special */
/** \name ISO special error codes
    \details These defines are used as parameter iCause in the error handler callback function and as return value of the interface functions.
@{
*/
#define E_ERROR_INDI        (-16)  /**< \brief ErrorCause: ISO error indicator */
#define E_NOT_AVAILABLE     (-17)  /**< \brief ErrorCause: Parameter, value ... not available */
#define E_PGN_UNKNOWN       (-18)  /**< \brief ErrorCause: unknown PGN */
#define E_USER_ERROR        (-19)  /**< \brief ErrorCause: IsoUser unknown, not announced ... */
#define E_DATA_LINK         (-20)  /**< \brief ErrorCause: Transport protocol used ... */
#define E_NO_INSTANCE       (-21)  /**< \brief ErrorCause: Instance not found */
#define E_CANMSG_MISSED     (-22)  /**< \brief ErrorCause: CAN message was not received */
#define E_VALUE_WRONG       (-23)  /**< \brief ErrorCause: Value or parameter has the wrong value */
#define E_OUT_OF_MEMORY     (-24)  /**< \brief ErrorCause: VT, TC has run out of memory */
#define E_NACK              (-25)  /**< \brief ErrorCause: NACK or PDNACK received of bus */
#define E_RESPTOCMDERROR    (-26)  /**< \brief ErrorCause: Response to Command with ErrorCode != 0 */
/** @} */
/** \name User defined error codes
    \brief Range for own error codes - application errors can integrated with IsoErrorOut( ... )
@{
*/
#define E_USER_DEFINED_START   (-32)
#define E_USER_DEFINED_END     (-47)
/** @} */  /* END Error cause / code definitions */

/* ************************************************************************ */
/** \name Modul error location numbers
    \details These defines are used as parameter bLoc in the error handler callback function.
@{
*/
#define M_DATA          0u      /**< Error in IsoTL.c, IsoDataM.c  */
#define M_USER          1u      /**< IsoUser.c */
#define M_NET           2u      /**< IsoNet.c */
#define M_DRV           3u      /**< IsoDrvN.c, IsoMnDl.c */
/*#define M_J1939         4u     **< unused */
#define M_BASE          5u      /**< Base driver module */
#define M_VT            6u      /**< IsoVt.c */
#define M_ALARM         7u      /**< IsoAlarm.c */
/*#define M_POOL          8u      **< unused - old IsoPool.c */
#define M_INTERN        9u      /**< Intern functions */
#define M_APP          10u      /**< User application*/
#define M_AUX          11u      /**< IsoAux.c */
#define M_TCCTRL       12u      /**< IsoTcCtrl.c */
#define M_UTPICT       13u      /**< UtPoPict.c */
#define M_VTCMD        14u      /**< IsoVTCmd.c */
/* #define M_VTXCR        15u      **< unused - old IsoVtXcr.c */
#define M_WOSE         16u      /**< IsoWoSe.c */
#define M_SC           17u      /**< IsoSCWork.c, IsoSCCtrl.c, IsoSCLogin.c */
#define M_SPN          18u      /**< SPN-Module */
#define M_FSC          19u      /**< FSC-Module (File server client) - IsoFSC.c */
#define M_NIU          20u      /**< NIU-Management-Module - IsoMnNlm.c */
#define M_NL           21u      /**< NIU-Service-Module - IsoMnNl.c */
#define M_DD           22u      /**< (PGN) Data Distributor - IsoDD.c */
#define M_CLSH         23u      /**< Client shared IsoClShCtrl.c */
#define M_TCCONN       24u      /**< IsoTcConn.c - TC connection module */
#define M_TCPOOL       25u      /**< IsoTcPool.c - TC pool service */
#define M_TCPD         26u      /**< IsoTcPd.c - TC process data module */
#define M_NMNET        29u      /**< Multi node network management - IsoMnNm.c */
#define M_APLAY        30u      /**< Application Layer */
#define M_VTCAUX       31u      /*!< VTC graphical auxiliary module */
#define M_VTCPOOL      32u      /**< VTC graphical auxiliary pool service module */
/** @} */

/* ************************************************************************ */
/** \name Errorhandler function numbers
    \brief The number of the function is only unique in combination with a module or layer location number.
    \details These defines are used as parameter bFun in the error handler callback function.
@{
*/
#define ISODRVINIT                            1u       /* IsoDrvN.c, IsoCore.c */
#define ISOGETPTRCANNODE                      2u
#define ISODRVCYCLE                           3u
#define ISOCANMSGREC                          4u       /* IsomnDl.c */
#define ISODRVCANINIT                         5u


#define ISODDPROCMSG                          2u       /* IsoDD.c function iso_ddDistributeMsg() */

#define ISODLPGNSEND                          1u       /* IsoData, IsoTL, IsoDataM.c */
/* #define ISOBROADCASTSEND                      2u */
#define ISOFPPRECEIVE                         3u
#define ISOOPENTP                             4u
#define ISORELEASETP                          5u
#define ISOTLDOSEND                           6u
#define ISOTLDIRECTSEND                       7u
#define ISOCORESETSTATE                       8u       /* IsoData.c iso_CoreSetState() */

#define ISOUSERANNOUNCE                       1u       /* IsoNet.c and IsoUser.c */
#define ISOUSERFORCEANNOUNCE                  2u
/* #define ISOUSERLOGOUT                         4u */
#define ISOUSERADD                            5u
#define ISOUSERGETDATA                        6u

#define ISONM_LISTOFHANDLES                   30u     /* IsoMnNm.h, IsoMnApi.h */

#define ISOADDWORKINGSETMEMBER                1u       /* IsoWoSe.c */

#define ISOCLSHREADLISTEXTHAND                1u       /* IsoClShCtrl.c */
#define ISOCLSHMSGDISTRIBUTOR                 2u

/* IsoVTCmd.c  */
/* For commands and messages are used the ISOVT_FUNC_e enum
   for the errorhandler message ( Version >=8 ) */

/* IsoVt  */
#define ISOVTMULTIPLENEXTVT                   1u
#define ISOVTRUN                              2u
#define ISOVTINIT                             4u
#define ISOWORKINGSET                         5u

#define ISOALARMCMD                           2u       /* IsoAlarm.c */

#define ISOAUXIMPCYCLIC                       1u       /* IsoAux.c (Intern call) */
#define ISOAUXASSIGNEXT                       2u       /* Intern call */
#define ISOAUXFUNCTOAPP                       3u       /* Intern call */
#define ISOAUXPREFASSIGN                      4u       /* Intern call */

#define ISOPOOLSETIDRANGEMODE                 1u       /* IsoPool.c */
#define ISOPOOLSCAN                           3u
#define ISOPOOLRUN                            4u
#define ISOPOOLMANIPULATE                     5u
#define ISOPOOLTESTIFLOAD                     6u

#define POOLOBJPICTCONVERT                    1u       /* UtPoPict.c */

#define ISOTC_STATUSREC                       1u      /* IsoTcCtrl.c */
#define ISOTC_INSTCMD                         1u      /* IsoTcConn.c */
#define ISOTC_CONDOPROCESS                    2u
#define ISOTC_SUBCOMMANDREC                   3u

#define ISOTC_SETPREFDL                       9u
#define ISOTC_MOVETOANOTHERTC                10u
#define ISOTC_DEVICESETVERSION               11u
#define ISOTC_SETPREFTC                      12u
#define ISOTC_PROCESSDATADEFTRIGGER_SET      10u      /* IsoTcPd.c */
#define ISOTC_SUBCMDPOOL                      1u      /* IsoTcPool.c */
#define ISOTC_DEVICE_SET                      2u
#define ISOTC_DEVICEELEMENT_SET               3u
#define ISOTC_DEVICEPROCESSDATA_SET           4u
#define ISOTC_DEVICEPROPERTY_SET              5u
#define ISOTC_DEVICEVALUEPRESENT_SET          6u
#define ISOTC_CHANGE_DESIGNATOR               7u
#define ISOTC_RELOADDDOBJECTS                 8u
#define ISOTC_ADDDPDOBJECT                   13u
#define ISOTC_ADDDPTOBJECT                   14u

#define ISOSCCtoSCMSEND                       1u       /* IsoSCCtrl.c, IsoSCWork.c  .. */
#define ISOSC_INSTCMD                         2u
#define ISOSC_FUNCTIONOBJSET                  3u
#define ISOSC_FUNCTVALUESET                   4u
#define ISOSC_STATEOBJSET                     5u
#define ISOSC_EXECUTIONINDICATION             6u
#define ISOSC_EXECUTIONSTATUS                 7u
#define ISOSC_CLIENTABORT                     8u
#define ISOSC_FUNERRORSTATUSSET               9u
#define ISOSC_FUNTRIGGERSET                  10u
#define ISOSC_LOGINREC                       11u
#define ISOSCDPOOLPREPARE                    12u
#define ISOSC_EXTOBJDEFSET                   13u
#define ISOSC_SETVERSION                     14u
#define ISOSC_INIT                           15u

#define ISOAL_PGNTXNEW                        1u      /* IsoMnAl.h, IsoMnApi.h */
#define ISOAL_PGNRXNEW                        2u
#define ISOAL_PGNACTIVATE                     3u
#define ISOAL_PGNDEACTIVATE                   4u
#define ISOAL_PGNCHANGEPRIORITY               5u
#define ISOAL_PGNCHANGESRCDEST                6u
#define ISOAL_PGNSETREPETITIONRATE            7u
#define ISOAL_PGNGETREPETITIONRATE            8u
#define ISOAL_PGNRXREQUEST                    9u
#define ISOAL_PGNRXREQUESTCYC                 10u
#define ISOAL_PGNTXSETLIMITS                  11u
#define ISOAL_PGNTXSEND                       12u
#define ISOAL_PGNDISABLE                      13u
#define ISOAL_PGNSEND                         15u     /* Intern function */
#define ISOAL_RUN                             16u
#define ISOAL_PGNCHANGEDATASIZE               17u

#define ISOSPNDEFINE                          1u      /* SPN module */
#define ISOALPGNDATASET                       2u
#define ISOALPGNDATAREAD                      3u
#define ISOALSPNADDDTC                        4u

#define ISOFSC_FUNCTION                       0u      /* File server client internal functions */
#define ISOFSC_INIT                           1u
#define ISOFSC_PROCESSMSG                     2u
#define ISOFSC_RUN                            3u
#define ISOFSC_SEND                           4u
#define ISOFSC_DOCALLBACK                     5u
#define ISOFSC_CLOSE_CONNECTION               6u
#define ISOFSC_CLOSE_IO                       7u
#define ISOFSC_IOMODE_CALLBACK                8u
#define ISOFSC_FUNCTION_CALL                 20u     /* File server client interface / public functions */

/** @} */
/** @} */   /* END errorhand */
/* ************************************************************************ */
#endif   /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) */


/* ************************************************************************ */
/*!
   \ingroup core_general
   \brief       Giving errors to the application

   This is the intern function which is called in case of errors to the application.
   It can be used for extension of the error handler to the application. The
   corresponding defines can be found at the end of IsoDef.h.


   \param[in]  \wp{bFunction, iso_u8}
               Number of function occurring the error. Every function with an error
               call has a define at the end of IsoDef.h
   \param[in]  \wp{Location, iso_u8}
               Error location that means module or layer ( M_DATA, M_USER, M_NET ...)
   \param[in]  \wp{iCause, iso_s16}
               Error cause ( E_NO_ERR, E_UNKNOWN_ERR, E_WARN ...)
   \note  \par
   Function number and Error location has to define for own application modules.
   Dont use the same numbers like the driver
*/
void IsoErrorOut( iso_u8 bFunction, iso_u8 Location, iso_s16 iCause );


/* *********************** Debugging ***************************** */
/** \addtogroup debugging Debugging
    \ingroup commonapi
    \brief   The use of the debugging functionality is only allowed for testing. \n
             You must disable debugging for a SRL1 release version.
    \details The debug output functions are not thread safe. \n
             To use debugging, you must add the define ISO_DEBUG_ENABLED \n
             You can add the define ISO_DEBUG_USE_EXTERN_FUNCTIONS
             and replace the default implementation for iso_DebugPrint() and iso_DebugTrace(). \n
             Or if you add the define #ISO_DEBUG_USE_CALLBACK_FUNCTION to your configuration file
             you can set a callback function with iso_DebugSetCallbackFunction()
             to redirect the debug output to your callback function. \n
    @{
*/

/* For documentation */
#ifdef DOXYGEN
/* ************************************************************************ */
/** \name Debugging Macros
@{ */
/* ************************************************************************ */
#define ISO_DEBUG_ENABLED /*!< \brief define to enable the developer debug output */
#define ISO_DEBUG_USE_CALLBACK_FUNCTION /*!< \brief define to enable the developer debug output callback function  */
/* ************************************************************************ */
/** @} */ /* debugging macros */
#endif
/* ************************************************************************ */

/* ************************************************************************ */
#ifdef ISO_DEBUG_ENABLED
/* ************************************************************************ */

/*! \brief Automatically set by the driver to enable the debug module compilation */
#define ISO_MODULE_DEBUG

/* ********************************************************************* */
/*! \brief      debuging printf() function
    \param[in]   \wpp{pacFormat, const iso_char []}
    \param[in]  ...
                Parameters specified in pacFormat
*/
void   iso_DebugPrint( const iso_char pacFormat[], ... );

/***********************************************************************/
/*! \brief      debuging trace() function
    \param[in]   \wpp{pacFormat, const iso_char []}
    \param[in]  ...
                Parameters specified in pacFormat
*/
void   iso_DebugTrace( const iso_char pacFormat[], ... );


#ifdef ISO_DEBUG_USE_CALLBACK_FUNCTION

#include <stdarg.h>  /* needed for va_list definition... */

/* replacement for typedef void (*ISO_DEBUG_CALLBACK_t)( const iso_char pacFormat[], ... ); */
/*! \brief Typedef of the debug output callback function pointer
    \param[in] \wpp{pacFormat, const iso_char[]}
      Format string ( have a look at printf() for more information )
    \param[in] \wpp{args, va_list}
      Parameters specified in pacFormat
*/
typedef void (*ISO_DEBUG_CALLBACK_t)( const iso_char pacFormat[], va_list args );


/*! \brief Function to set the external debug output callback function
    \param[in] \wp{ pfDebugTraceFunc, ISO_DEBUG_CALLBACK_t }
                Pointer to the callback function. \n
                Use the NULL pointer to disable the callback execution.
    \retval                iso_s16
                           - #E_NO_ERR

    \par Example
    Callback function:
    \code{.c}
    void cb_app_debug_out( const iso_char pacFormat[], va_list args )
    {
    #ifdef __cplusplus
       iso_char sOut[500];
       vsprintf( sOut, pacFormat, args );
       std::cout << sOut;
    #else
       vprintf( pacFormat, args );
    #endif
    }
    \endcode
    Set the callback function:
    \code{.c}
    (void)iso_DebugSetCallbackFunction(cb_app_debug_out);
    \endcode
*/
iso_s16 iso_DebugSetCallbackFunction( ISO_DEBUG_CALLBACK_t  pfDebugTraceFunc );

#endif

/* ************************************************************************ */
#endif      /* ISO_DEBUG_ENABLED */
/** @} */   /* debugging */
/* ************************************************************************ */


/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_ISOCOMMONDEF_H */
/* ************************************************************************ */
