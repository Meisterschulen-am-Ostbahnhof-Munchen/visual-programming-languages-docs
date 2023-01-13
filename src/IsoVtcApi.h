/* ************************************************************************ */
/*!
   \file
   \brief       ECU Driver VT Client API Header File
   \author      Wegscheider Peter
   \date        Created XX.07.13

   \copyright   Competence Center ISOBUS e.V.

   \par         History:
   \par
   04.07.2013 - author P. Wegscheider
   - API declarations moved to this file
   - Module version define added
   \par
   25.11.2013 - author P. Wegscheider
   - "Direct Pool Transfer" implementation
   - Function IsoPoolInitDirectTransfer() added
   \par
   09.12.2013 - author P. Wegscheider
   - Functions IsoAuxPrefAssignmentCbSet() and IsoAuxPrefAssignmentTrigger() added
   - Function IsoAuxAssignmentSet() disabled per default. 
   - VT_AUXAPP_T extended with baAuxName[8] (ISO name of the auxiliary input device) 
   - Define ISO_AUXFUNC_SINGLEASSIGN_CHECK added to enable the aux function single assignment check
   \par
   15.05.2013 - author P. Wegscheider
   - VERSION_VTC updated to 3.2
   - define ISO_EXTERNAL_POOLBUFFER and function IsoPoolSetBuffer() added
   - Functions IsoPoolObjSize() and IsoPoolObjCopyToRAM() added
   - Function IsoPoolObjectCbSet(), IsoPoObjAttributGet() and IsoPoolObjPtrGet() for AID reading added
   - define ISOVT_AID_DEFINES check and AID_xxx defines added
   \par
   22.07.2014 - author P. Wegscheider
   - VERSION_VTC updated to 3.3
   - IsoPoolObjPtrGet() implementation changed to avoid compiler pointer cast error
   \par
   23.03.2015 - author P. Wegscheider
   - VERSION_VTC updated to 3.4
   - Feature request ID 2122: Optimization of direct load pool transfer
   \par
   14.04.2016 - author E. Hammerl
   - Added IsoVTObjTypeParsableSet()
   - Renamed IsoCheckObjTypeSupported() into IsoVTObjTypeIsSupported()
   - Added defines for VT versions
   - Added enum for VT events, callback installer function for this events 
   - Added defines, AIDs and command functions for new objects of V 4,5,6
   - Changed iso_char into iso_8 ( IsoVTVersionStringGet(), IsoPoolReadPtrLoc() )
   - Changes in Returnvalues of all command functions( #E_USER_ERROR into ##E_NO_INSTANCE )
   - Added bFuncAttribute in struct VT_AUXAPP_T !
   - ObjectExternalObjDef renamed to ExternalObjectDef
   - Added IsoAuxCapabilitiesRequest() for auxiliary capabilities request
   - Changed two parameters of ISOPOOLCTRL_T from iso_u16 to iso_u32
   - VERSION_VTC updated to 5.1
   \par
   01.08.2016 - author P. Wegscheider
   - VERSION_VTC updated to 5.2
   - Feature request ID 4565 Master registration ( VTC solution )
      - Added IsoVTSetNewPreferredVT()
      - Added #IsoEvConnSelectPreferredVT to ISOVT_VTEVENT_e
   \par
   15.12.2016 - author P. Wegscheider
   - Feature request ID 4629: client interfaces should only use handles
     - Replaced source address (SA) parameter with CF handle for functions
       IsoWsSetMaskInst(), IsoWsSetAuxInst() and IsoWsSetSccInst()
     - Removed unneeded parameter rwFctSender from IsoAlarmObjInit()
     - Removed fields bData and wFctofSender from structure #ISOALARM_T
   \par
   10.01.2017 - author P. Wegscheider
   - Feature request ID 4655: IsoCmd_Attribute(): change parameter lvalue from iso_s32 to iso_u32
   - Feature request ID 4656: IsoCmd_LockUnlockMask(): change parameter lvalue from iso_s32 to iso_u16
   - Feature request ID 4657: IsoCmd_NumericValueRef(), IsoCmd_NumericValue(): change parameter lvalue from iso_s32 to iso_u32
   \par
   12.01.2017 - author P. Wegscheider
   - Feature request ID 4638: Added IsoPoolWSSelectableSet() to change WS selectable attribute
   \par
   16.01.2017 - author P. Wegscheider
   - Feature request ID 4654: callback prior to saving the object pool
      - Added ISOVT_VTEVENT_e events IsoEvMaskReadyToStore and IsoEvAuxReadyToStore
      - Added new ISOVT_ANNOUNCE_e state waiting_before_store before request_store_version to signal the new events
   \par
   26.01.2017 - author P. Wegscheider
   - Feature ID  4209: declare pointer parameter in functions as const* where applicable
      - IsoVTInit() - set callback functions parameter ISOVT_MSG_STA_T as const
      - IsoAuxAssignmentSet() - set parameter VT_AUXAPP_T as const
      - IsoPoolReadPtrLoc() - set return value to const iso_u8*
   \par
   20.02.2017 - author P. Wegscheider
   - Feature request ID 6015: event if pool reload is finished \n
     (Added events #IsoEvMaskPoolReloadFinished and #IsoEvAuxPoolReloadFinished)
   \par
   21.02.2017 - author P. Wegscheider
   - Feature request ID 6003: client interfaces should only use handles (rather then ISOBUS NAME)
   - Replaced working set master NAME  parameter with CF handle for functions
     IsoVTInit(), IsoVT_InstallCbConnection(), IsoAuxUnitInit() and IsoAlarmObjInit()
   - Removed IsoWsSetMaskInstWithName()
   \par
   21.02.2018 - author P.Wegscheider
   - Feature ID 7528: add user parameter to callback functions
   - Feature ID 8157: AUX: add a getter to obtain the drivers aux function index of an given object \n
     Added function IsoAuxInputIndexToObjId() to get the index to an input object ID
   \par
   06.05.2018 - author P.Wegscheider
   - Feature ID 3910: header files should include header files they depend on
   \par
   14.06.2018 - author P.Wegscheider
   - Feature request ID 8424: use ISO_CF_NAME_T in API functions
   \par
   15.06.2018 - author P.Wegscheider
   - Feature ID 8822: allow for a secondary pool manipulation
   \par
   18.07.2018 - author P.Wegscheider
   - Feature BugID 8425: integrate APA AUX - pool upload client
   - Moved API and renamed functions
   \par
   10.08.2018 - author P. Wegscheider
   - BugID 8581: add "namespace ISOBUSDRIVER" to header files
   \par
   25.10.2018 - author P.Wegscheider
   - Feature ID 9539: While scanning an Auxiliary Input object additional data ( array index ) shall be made available to the application
   \par
   20.11.2018 - author P.Wegscheider
   - Feature ID 9545: ISO 11783-6_Virtual Terminal (4th edition 2018) -- new graphic objects
   - Added and updated VT 6 objects; Replaced PNGObject enumeration entry with GraphicDataObject
   \par 04.12.2018 - author E. Hammerl
   - Feature ID 9786: 
     - Added function iso_AuxInput_SetDisable() and ISOVT_FUNC_e entry #aux_pre_input_status_enable,
       to allow the aux input client application to manually disable the aux input. 
     - Added: Informing the application about a change of the VT status busy code bit "Auxiliary controls learn mode active" (#aux_learn_mode_changed)
   \par
   01.02.2019 - author P.Wegscheider
   - Feature ID 9277: Removed function IsoVtcGAux_SetPoolServiceBuffer() to avoid conflicts with IsoPoolSetBuffer()
   - Feature ID 9577: make CCI_SECONDARY_POOL_MANIPULATION available as ISO_SECONDARY_POOL_MANIPULATION
   \par
   25.02.2020 - author P.Wegscheider
   - Feature ID 11563, 11638: new GAux features 
     - Added API functions IsoVtcGAux_SetConnection() and IsoVtcGAux_SetAllConnections() 
   \par
   06.04.2020 - authors E. Hammerl, P. Wegscheider
   - Feature ID 11380: Refectory of VTC command buffer to be used also from the GAux
     - Implemented command send functions using an instance (connection) handle
     - GAux: Replaced unused IsoVtcGAux_Msg_Ts with ISOVT_MSG_STA_T
     - ISO_VTC_DISABLE_XCR replaced by ISO_VTC_ENABLE_XCR
   \par
   28.05.2020 - author P.Wegscheider
   - Feature BugID 12231: add convenience function IsoVtcGetStatusInfo()
   - Feature BugID 12245: add convenience Function IsoVtcSetInstance()
   \par
   03.06.2020 - author P.Wegscheider
   - Feature BugID 12245: add more convenience functions with VTC instance as first parameter
   \par
   05.06.2020 - author P. Wegscheider
   - BugID 12266: provide client instance in pool service callback function (structure ISOPOOLCTRL_T)
  \par
   11.01.2021 - author P.Wegscheider
   - Feature BugID 12133: VTC - Disable auxiliary function type 1 functionality by default \n
     (Replaced ISO_VTC_DISABLE_AUX_O with ISO_VTC_ENABLE_AUX_O)
  \par
   25.01.2021 - author P.Wegscheider
   - Feature BugID 12772: removed deprecated module IsoVtXcr (define ISO_VTC_ENABLE_XCR) and deprecated API functions
   \par
   26.01.2021 - author P.Wegscheider
   - Feature request ID 12110: refactor VT client
   - Changed optional callback function ISOVT_CbPoolSecondaryAdaptation_t which an be enabled with define ISO_SECONDARY_POOL_MANIPULATION
   - Changed callback function #iso_fnCbPoolObject_t which can be set with IsoVtcPoolObjectCbSet()
   \par
   12.02.2021 - author E. Hammerl
   - Added screen capture and select active working set command
   \par
   18.02.2021 - author P.Wegscheider
   - Feature BugID 12110: refactor VT client
     - Added IsoVtcCreateInstance(); marked IsoVT_CreateInstance() as deprecated
     - Added IsoVtcCreateAuxInputDevice(); removed IsoAuxUnitInit()
     - Removed VT_TEST_ALIVE_SIGNAL from #ISOVT_STATUS_e: use #VT_ALIVE instead
     - Removed ISOVT_ANNOUNCE_e state entries moveToAnotherVT, waiting_for_SetPrefassign and pref_assignment_send
     - Removed useless #ISOVT_STATUS_e entries VTC_INSTANCE and WS_COUPLE_STATE
     - Removed useless enumeration WSCOUP_STA_e
     - Added utility function IsoVtcPoolConvertPictureObject()
     - Added IsoVtcPoolInitBlockTransfer() and IsoVtcGAux_PoolInitBlockTransfer functions
   \par
   06.04.2021 - author P. Wegscheider
    - Feature BugID 12136: support for manufacturer defined VT objects 
      (define ISO_VTC_CUSTOM_POOL_OBJECTS_HEADER_SIZE)
    - Feature BugID 12110: refactor VT client
      - Provide IsoPoolSecondaryAdaptInit() per default (removed define ISO_SECONDARY_POOL_MANIPULATION)
      - Added API function IsoVtcCmd_Proprietary()
      - Added API function IsoVtcRestartInstance()
      - Added #ISOVT_VTEVENT_e IsoEvInstanceClosed event which is called after an VTC entry was deleted
    - Feature BugID 11187: make used VT version string length configurable
      - Added define ISO_VTC_USE_LEN_VERSIONSTR_V4
      - Replaced LENVERSIONSTRV4, LENVERSIONSTRV5, LENVERSIONSTR
          with ISO_VTC_LEN_VERSIONSTR_V4, ISO_VTC_LEN_VERSIONSTR_V5, ISO_VTC_LEN_VERSIONSTR
      - Replaced POOLVERSIONS with ISO_VTC_MAX_POOLVERSIONS and POOBBUFF with ISO_VTC_WS_POOL_BUFFER
   \par
   16.04.2021 - author P. Wegscheider
   - Feature BugID 12110: refactor VT client
     - Added IsoVtcPoolLoad(), IsoVtcGAux_PoolLoad() and IsoVtcPoolUpdate() functions
       and removed IsoVtcPoolInitBlockTransfer() and IsoVtcGAux_PoolInitBlockTransfer
     - Set old functions 
*/
/* ************************************************************************ */
#ifndef DEF_IsoVtcApi_H
    #define DEF_IsoVtcApi_H

/* include configuration, driver standard types and common definitions */
#include "IsoCommonDef.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

/* ************************************************************************ */
/* ******* Following functions and definitions only for LAYER 6 .. ******** */
/* ************************************************************************ */

/* ********************************* IsoVt.c  ***************************** */
/** \defgroup vtcl VT-Client
   \ingroup  clients
   \brief Part 6 - Virtual Terminal Client

   \defgroup vtclmem VT-Client Memory Footprint Options
   \ingroup  vtcl

   \defgroup vtctypedefs VT-Client Type Definitions
   \ingroup  vtcl

   \defgroup vtmanage VT-Client Management Functions
   \ingroup  vtcl

   \defgroup vttechmsg Annex D technical messages and Annex E memory commands
   \ingroup  vtcl

   \defgroup vtFcmdmsg Annex F commands
   \ingroup  vtcl

   \defgroup vtc_aux Auxiliary
   \ingroup  vtcl

   \defgroup vtc_aux_typedefs Auxiliary Type Defines
   \ingroup  vtc_aux

   \defgroup poolmani VT-Client Object Pool Manipulation
   \ingroup  vtcl

   \defgroup vtc_ala Alarm handling (disabled by default)
   \ingroup  vtcl

   \defgroup grp_vtcl_gaux GAUX-Client: Graphical Auxiliary Input Device Client API
   \ingroup  vtcl

   */

#if defined(DOXYGEN) 
/*! \addtogroup vtclmem 
    \ingroup  vtcl
    \brief Enabling and disabling of VT client features

    Defines with "Disable" in the name reduce the VT-Client RAM and FLASH memory footprint. 
    Defines with "Enable" in the name are disabled per default and switches on these functionalities.
    The following defines can be added to the application specific IsoConf.h.
 @{ */

    /*! \brief Disable UT3 functionality ( VT Version 4 and Version 5 and Version 6 ). */
   #define ISO_VTC_DISABLE_UT3
   #undef  ISO_VTC_DISABLE_UT3

   /*! \brief Disable auxiliary function type 2 functionality. 
         ( IsoAux.c )   
   */
   #define ISO_VTC_DISABLE_AUX_N
   #undef  ISO_VTC_DISABLE_AUX_N

   /*! \brief Enable auxiliary function type 1 functionality. 
         (Location: IsoAuxOld.c )   
   */
   #define ISO_VTC_ENABLE_AUX_O
   #undef  ISO_VTC_ENABLE_AUX_O

   /*! \brief Disable buffered standard and segmented pool upload functionality. 
         (Location: IsoPool.c )
        \details The define is normally only used in combination with #ISO_POOL_DIRECT_LOAD 
                 to reduce the memory footprint of the pool management module.    
   */
   #define ISO_VTC_DISABLE_POOL_BUFFERED_LOAD
   #undef  ISO_VTC_DISABLE_POOL_BUFFERED_LOAD

   /*! \brief Enable VT client alarm management functionality.
         ( IsoAlarm.c )
   */
   #define ISO_VTC_ENABLE_ALARM

   /*! \brief Enable auxiliary input type 1 and 2 functionality. 
         (Location: IsoAux.c, IsoAuxOld.c  )  
       \details This enables a subset of the of the ISO 11783 functionality needed to implement an auxiliary input unit device.     
   */
   #define ISO_VTC_ENABLE_AUX_INPUT

   /*! \brief Enables the support for manufacturer defined VT objects.
       \details If used, must be set to the minimum size needed to calculate the object size. 
       If defined the value must be greater than 3u. \n
       See IsoVtcPoolCustomObjectSizeCbSet() for more information. */
   #define ISO_VTC_CUSTOM_POOL_OBJECTS_HEADER_SIZE (10u) /* Sample: set to 10u */

   /*! \brief   Forces the use of 7 byte length pool version labels. 
       \details If the define is set in the IsoConf.h the driver uses only 
       the part 6 annex E commands for the 7 byte version labels.
       */
   #define ISO_VTC_USE_LEN_VERSIONSTR_V4
   #undef  ISO_VTC_USE_LEN_VERSIONSTR_V4
/*! @} */

   /* make sure that the API documentation can be generated */
   #if !defined(ISO_VTC_ALARM)
      #define ISO_VTC_ALARM
   #endif
   #if !defined(ISO_VTC_AUX_N)
      #define ISO_VTC_AUX_N
   #endif
   #if !defined(ISO_VTC_AUX_O)
      #define ISO_VTC_AUX_O
   #endif
   #if !defined(ISO_VTC_AUX_INP_N)
      #define ISO_VTC_AUX_INP_N
   #endif
   #if !defined(ISO_VTC_AUX_INP_O)
      #define ISO_VTC_AUX_INP_O
   #endif

#endif   /* DOXYGEN memory  */

/* ************************************************************************ */
/*! \addtogroup vtctypedefs 
    \ingroup  vtcl
 @{ */

#if defined(CCI_USE_NAMESPACE) && defined(__cplusplus)
#include "IsoVtcApi.hpp"
#else    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) -> use C defines */

#define ISO_INSTANCE_INVALID  (0xFFu)     /*!< \brief Identifier for instance (connection) invalid */

/* VT versions */
#define VT_V0_FE      (0U)  /**< VT DIS  - draft first edition 2001*/
#define VT_V1_FE      (1U)  /**< VT FDIS - final draft first edition */
#define VT_V2_FE      (2U)  /**< VT IS   - ISO first edition 2004*/
#define VT_V3_SE_UT2  (3U)  /**< VT IS   - ISO second edition with Version 3 reference 2010*/
#define VT_V4_SE_UT3  (4U)  /**< VT IS   - ISO second edition - Version 4 enhancements 2010*/
#define VT_V5_SE_UT3  (5U)  /**< VT IS   - ISO third  edition - Version 5 enhancements 2011 */
#define VT_V6_TE      (6U)  /**< VT IS   - ISO fourth edition - Version 6 enhancements 2018 */

#define ISO_VTC_LEN_VERSIONSTR_V4    (7U)  /**< Length of pool label version strings 4 and earlier */
#define ISO_VTC_LEN_VERSIONSTR_V5   (32U)  /**< Length of pool label version strings 5 and later */

#endif    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) */

#if defined(ISO_VTC_UT3) && (!defined(ISO_VTC_USE_LEN_VERSIONSTR_V4))
   #define ISO_VTC_LEN_VERSIONSTR (ISO_VTC_LEN_VERSIONSTR_V5)
#else
   #define ISO_VTC_LEN_VERSIONSTR (ISO_VTC_LEN_VERSIONSTR_V4)
#endif /* ISO_VTC_UT3 */

#if !defined(ISO_VTC_MAX_POOLVERSIONS)
/*! \brief Max. number of pool versions - see get version */
#if defined(POOLVERSIONS)
   #define ISO_VTC_MAX_POOLVERSIONS (POOLVERSIONS)
   #pragma message("WARNING: POOLVERSIONS is deprecated. Use ISO_VTC_MAX_POOLVERSIONS instead. ")
#else
   #define ISO_VTC_MAX_POOLVERSIONS (5u)
#endif 
#endif /* !defined(ISO_VTC_MAX_POOLVERSIONS) */


/*! \def ISO_WAITVT_SEC 
   \brief Wait time in seconds for preferred VT 
*/
#ifndef ISO_WAITVT_SEC
#define ISO_WAITVT_SEC   (7u) 
#endif /* ISO_WAITVT_SEC */


/*! \brief VTC instance type enumeration */
typedef enum
{
   VTC_MAIN_INSTANCE = 0,  /**< Main VT client instance (primary mask instance) */
   VTC_VT0_INSTANCE = 1   /**< VT function 0 client instance (AUX, SCC instance (primary VT instance)) */

} ISOVT_INSTANCE_TYPE_Te;


/** \brief Typedef of Struct for received VT messages and responses used in VT Messages Callback . 
    \details 
      - Struct is used for giving various VT message data to the application
      - Corresponding Callbackfunction see IsoVT_CreateInstance()  
      - Responses of commands are not documented here (see IsoVTMsg.c  VtcCmdParseResponse())
      - Valid callback message fields depending on the iVtFunction (ISOVT_FUNC_e):

\verbatim                                                                              
    iVtFunction:                                                                            
    softkey_activation            wObjectID       key object ID                   
                                  wPara1          parent object ID                
                                  bPara           key number (hard coded)         
                                  lValue          activation code (0, 1, 2, 3(Version 4)) see [1]
                                  wPara2          TAN (since version 6) else FF 
    button_activation             wObjectID       button object ID                
                                  wPara1          parent object ID                
                                  bPara           button key number               
                                  lValue          activation code (0, 1, 2, 3(Version 4)) see [1]
                                  wPara2          TAN (since version 6) else FF
    pointing_event                wPara1          X position in pixel             
                                  wPara2          Y position in pixel
                                  bPara           touch state: 0xFF for VT3 and prior
                                  wObjectID       parent mask object ID (since Version 6)
                                 (lValue          copy of Byte 6 (touch state and TAN (since version 6) or FF)
    VT_select_input_object        wObjectID       input object ID                 
                                  wPara1          Selected/Deselected
                                  wPara2          Bitmask (Version 5 and later)
                                  bPara           TAN (Version 6 and later)
    VT_esc                        wObjectID       ID of input field where aborted 
                                  iErrorCode      error code see ISO Doku.  
                                  bPara           TAN (Version 6 and later)
    VT_change_numeric_value       wObjectID       ID of input object              
                                  lValue          new value   
                                  bPara           TAN (Version 6 and later)
    VT_change_active_mask         wObjectID       Active Mask or Window Mask or Key Group object ID             
                                  iErrorCode      error code see ISO Doku.        
    VT_change_softkey_mask        wObjectID       Soft Key Mask object ID    
                                  wPara1          Data or Alarm Mask object ID 
                                  iErrorCode      error code see ISO Doku         
    VT_change_string_value        wObjectID       ID of String object             
                                  bPara           Length of string                
                                  pabVtData       Pointer to characters 
    ( Version 4 )                 
    VT_onUserLayout_hideShow      wObjectID       Object ID of WM, DM, SKM, KG
                                  wPara2          Hide/show
                                  wPara1          Object ID of second WM, DM, SKM, KG
                                  bPara           Hide/show of second
                                  lValue          TAN (Version 6 and later)
    get_attribute_value           wObjectID       Object ID
                                  bPara           AID
                                  wPara1          Current value of attribute
                                  iErrorCode      ErrorCode (see F.59)
    ( Version 3 )                 
    preferred_assignment          wObjectID       Auxiliary function object if faulty
                                  iErrorCode      Error code see ISO Doku.
    auxiliary_assign_type_1, .._2 wObjectID       Object ID auxiliary function    
                                  wPara1          Object ID auxiliary input (or input number type 1) 
                                                  0xFFFF for unassign             
                                  wPara2          Type of auxiliary incl. Attribute bits see [2]
                                  bPara           ISO_TRUE: Store as pref. assign, else not (only type 2) 
                                  lValue          Bit 16 - 27: Manufacturer code,         
                                                  Bit  0 - 15 Model Identification code of auxiliary input 
                                                  (only type 2)
                                  pabVtData       only for auxiliary_assign_type_2:
                                                  Pointer to the last/current aux unit ISONAME or 8*0xFF
    auxiliary_input_status_type_2
    aux_input_status_type_1       wObjectID       Object ID Auxiliary function type          
                                  wPara1          Input object ID (type 1 = input number     
                                  lValue          Value 1                                    
                                  wPara2          Value 2                                    
                                  iErrorCode      E_NO_ERR, E_CANMSG_MISSED (Alive of input)
    aux_input_status_enable       wObjectID       Object ID Auxiliary input type 2 
                                  bPara           Enable 
                                  iErrorCode      ErrorCode (see J.7.12)
    ( Version 5 )
    auxiliary_capabilities        bPara           Number of auxiliary Units
                                  pabVtData       Pointer to data ( Byte 3 ... )

    ** proprietary VT client notifications **:
    vtc_pool_aux_input_type_2     wObjectID       Object ID Auxiliary input type 2          
                                  wPara1          Array index number (parameter for IsoVtcAuxInputStatus2())     
                                  wPara2          Type of auxiliary input
    aux_pre_input_status_enable   wObjectID       Object ID Auxiliary input type 2
                                  bPara           Enable
                                                  Called before aux input status enabled response is send in order to manually disable the aux input 
    aux_learn_mode_changed        bPara           ISO_TRUE if learn mode is active (Info VT_status_message Bit 6 of byte 7) 

               [1] Timeout control of softkeys and buttons have to be done of application !
               [2] Attribute bits are given to application as additional information
                   For getting the Auxiliary type application have to mask out it.
\endverbatim

*/
typedef struct 
{
    iso_s16          iVtFunction;       /**< \brief VT function of received message (#ISOVT_FUNC_e) */
    iso_u16          wObjectID;         /**< \brief Object ID (if available) */
    iso_u32          lValue;            /**< \brief Long value depending of command/activation message see table */
    iso_u16          wPara1;            /**< \brief Unsigned short value 1 depending of command/activation message see table */
    iso_u16          wPara2;            /**< \brief Unsigned short value 2 depending of command/activation message see table */
    iso_u8           bPara;             /**< \brief Unsigned char value depending of command/activation message see table */
    iso_u8           u8Instance;        /**< \brief Identifier of the client instance */
    iso_s16          iErrorCode;        /**< \brief Error code of response messages or error code e. g. #E_CANMSG_MISSED */
    iso_s32          lTimeSt;           /**< \brief Time stamp of received message */
    const iso_u8*    pabVtData;         /**< \brief Data of VT e. g. string characters see table */
    ISO_USER_PARAM_T userParam;         /**< \brief User parameter set with IsoVtcCreateInstance() */
} ISOVT_MSG_STA_T, *ISOVT_MSG_STA_t ;


/** \brief
Events for VT Client connection callback function
*/
typedef enum
{
   IsoEvConnSelectPreferredVT,    /**< Initial preferred VT is not available. 
                                       \details This event is only triggered if one or more VTs are available.
                                                In this case the application can set a new preferred VT with IsoVtcSetNewPreferredVT().
                                  */
   IsoEvMaskServerVersAvailable,  /**< Version of mask (VT)server is available */
   IsoEvMaskLanguageCmd,          /**< Language and/or metrics of VT server has been changed */
   IsoEvMaskTechDataV4Request,    /**< Enables requesting of technical data messages Annex D.10 till D.14 */
   IsoEvMaskLoadObjects,          /**< Set and manipulate pool */
   IsoEvMaskReadyToStore,         /**< VTC is ready to store the uploaded object pool. 
                                       \details If defined ISO_VTC_WAITBEFORESTORE the state machine will stay in this state 
                                                until the application calls IsoVtcContinue().
                                                If ISO_VTC_WAITBEFORESTORE is not defined or the callback function is not set, 
                                                we continue immediately with state #request_store_version. */
   IsoEvMaskActivated,            /**< Login finished - client is in state application_running */
   IsoEvMaskTick,                 /**< Mask connection cyclic call */
   IsoEvMaskLoginAborted,         /**< Mask connection uncoverable error during Login */
   IsoEvMaskStateChanged,         /**< Reports changes of VTC maskinstance to statemachine */
   IsoEvMaskPoolReloadFinished,   /**< Mask connection: object pool reload finished */ 
   /* Mask/Aux connection independent */   
   IsoEvConnSafeState,            /**< Application shall go into safe state ( connection closed ) */
   IsoEvInstanceClosed,           /**< VTC instance closed (Instance invalid; do not call any VTC function during this event) */
   /* Only called if Aux functions in pool and second connection is running */
   IsoEvAuxServerVersAvailable,   /**< Version of server is available */
   IsoEvAuxLanguageCmd,           /**< Language and/or metrics of VT server with function instance 0 has been changed */
   IsoEvAuxTechDataV4Request,     /**< Enables requesting of of Annex D.10 till D.14 */
   IsoEvAuxLoadObjects,           /**< Set and manipulate pool */
   IsoEvAuxReadyToStore,          /**< VTC is ready to store the uploaded object pool on the AUX VT instance
                                       \details See #IsoEvMaskReadyToStore for more information. */
   IsoEvAuxActivated,             /**< Login finished - client is in state VtRunning */
   IsoEvAuxTick,                  /**< Auxiliary connection cyclic call */
   IsoEvAuxLoginAborted,          /**< Auxiliary connection uncoverable error during Login */
   IsoEvAuxStateChanged,          /**< Reports changes of VTC auxinstance to statemachine */
   IsoEvAuxPoolReloadFinished     /**< Auxiliary connection: object pool reload finished */
} ISOVT_VTEVENT_e;


/** \brief
States of VT state machine
*/
typedef enum
{
   safe_state                     =  0,    /**< Application is not active */
   announce_stopped               =  1,    /**< No more trials for communication with VT */
   announce_aborted               =  2,    /**< Announcement will be repeated */

   moveVT_deleteVersion           = 11,    /**< Pool in VT RAM has been deleted */
   vt_lost                        = 14,    /**< VT is lost ( move to another VT or missing VT status */

   vt_status_received             = 20,    /**< VT Status message received */
   waiting_after_vt_status_rec    = 21,    /**< Waiting after receiption of vt status message */
   working_set_master_sended      = 22,    /**< Pool in VT RAM is deleted */
   working_set_maintenance_start  = 23,    /**< Start working set maintenance message sending */
   request_get_memory             = 24,    /**< Early get memory request */
   language_command               = 26,    /**< Check Language command, request if necessary */
   language_command_waiting       = 27,    /**< Language command waiting */
   request_get_softkeys           = 30,    /**< Request get softkeys */
   request_get_textfont           = 31,    /**< Request get textfont */
   request_get_hardware           = 32,    /**< Request get hardware */
   request_get_versions           = 36,    /**< Request get versions */
   check_sequenz_control          = 40,    /**< Reading SCM capabilities */
   waiting_after_GetVersions      = 41,    /**< Stop -> pool manipulation -> IsoVtcContinue()! */
   appStartandVersionString       = 43,    /**< Check version strings and decide */
   pool_scan_running              = 44,    /**< GetMemory and Pool scan */
   request_load_version           = 50,    /**< Request load version  */
   pool_service_running           = 51,    /**< Pool transfer is running */
   waiting_before_store           = 52,    /**< Waiting before continue with "Request store version" */
   request_store_version          = 53,    /**< Request store version */
   reload_poolobjects             = 54,    /**< Check and start reloading working set object */
   reload_wsocyclic               = 55,    /**< Reloading working set object */

   announce_finished              = 63,    /**< Last step of login */
   application_running            = 70     /**< Normal operation of application (commands ...)  */
} ISOVT_ANNOUNCE_e;

/** \brief
Enum of all VT object types
*/
typedef enum
{
   /* Top level objects */
   WorkingSet              =  0,  /**< Top level object describes an implement (working set). */
   /* Working set object */
   DataMask                =  1,  /**< Top level object that contains other objects. */
   AlarmMask               =  2,  /**< Top level object: Describes an alarm display. */
   Container               =  3,  /**< Used to group objects. */
   /* Key objects */
   SoftKeyMask             =  4,  /**< Top level object that contains key objects. */
   Key                     =  5,  /**< Used to describe a soft key. */
   Button                  =  6,  /**< Used to describe a button control. */
   /* Input field objects */
   InputBooleanField       =  7,  /**< Used to input a ISO_TRUE/ISO_FALSE type input. */
   InputStringField        =  8,  /**< Used to input a character string. */
   InputNumberField        =  9,  /**< Used to input an integer or float numeric. */
   InputListField          = 10,  /**< Used to select an item from a pre-defined list. */
   /* Output field objects */
   OutputStringField       = 11,  /**< Used to output a character string. */
   OutputNumberField       = 12,  /**< Used to output an integer or float numeric. */
   /* Output shape objects */
   TypLine                 = 13,  /**< Used to output a line. */
   TypRectangle            = 14,  /**< Used to output a rectangle or square. */
   TypEllipse              = 15,  /**< Used to output an ellipse or circle. */
   TypPolygon              = 16,  /**< Used to output a polygon. */
   /* Output graphic objects */
   Meter                   = 17,  /**< Used to output a meter. */
   LinearBarGraph          = 18,  /**< Used to output a linear bar graph. */
   ArchedBarGraph          = 19,  /**< Used to output an arched bar graph. */
   /* Picture graphic object */
   PictureGraphic          = 20,  /**< Used to output a picture graphic (bitmap). */
   /* Variable objects */
   NumberVariable          = 21,  /**< Used to store a 32-bit unsigned integer value. */
   StringVariable          = 22,  /**< Used to store a fixed length string value. */
   /* Attribute object */
   FontAttributesObject    = 23,  /**< Used to group font based attributes. */
   LineAttributesObject    = 24,  /**< Used to group line based attributes. */
   FillAttributesObject    = 25,  /**< Used to group fill based attributes. */
   InputAttributesObject   = 26,  /**< Used to specify a list of valid characters. */
   /* Pointer object */
   ObjectPointer           = 27,  /**< Used to reference another object. */
   /* Macro object */
   Macro                   = 28,  /**< Special object that contains a list of commands. */
   /* Auxiliary control */
   AuxiliaryFunction       = 29,  /**< Defines the designator and function type. */
   AuxiliaryInput          = 30,  /**< Defines the designator, key number, and function type. */
   AuxiliaryFunction2      = 31,  /**< Defines the designator and function type 2. */
   AuxiliaryInput2         = 32,  /**< Defines the designator, key number, and function type 2 */
   AuxiliaryConDesigObjPoi = 33,  /**< Defines the auxiliary control designator object pointer */
   /* Version 4 objects */
   WindowMaskObject        = 34,  /**< Special (parent) object for user layout DM */
   KeyGroupObject          = 35,  /**< Parent object of user layout SKM */
   GraphicsContextObject   = 36,  /**< Graphics Context object */
   OutputListObject        = 37,  /**< Used to output a output list */
   ExtInputAttributeObject = 38,  /**< Extended input attribute object */
   ColourMapObject         = 39,  /**< Changing the colour table */
   ObjectLabelReferList    = 40,  /**< For assigning (textual/graphical) label to objects  */
   /* Version 5 objects */
   ExternalObjectDef       = 41,  /**< Lists objects which another WS can reference */
   ExternalRefName         = 42,  /**< Identifies a WSM of a WS which can be referenced */
   ExternalObjectPointer   = 43,  /**< Allows a WS to display objects from another WS */
   AnimationObject         = 44,  /**< Used to display animations */
   /* Version 6 objects */
   ColourPaletteObject     = 45,  /**< Used for replacing VT standard colour palette */
   GraphicDataObject       = 46,  /**< Graphic Data object; Used for displaying Portable Network Graphic object */
   WSSpecialControlsObject = 47,  /**< Working Set Special Controls object */
   ScaledGraphicObject     = 48,  /**< Scaled Graphic object */
   ObjectUndef             = 255
} OBJTYP_e;

/** \brief
Enum VT functions
*/
typedef enum
{
   /* Annex H: activation messages */
   softkey_activation         =  0,
   button_activation          =  1,
   pointing_event             =  2,
   VT_select_input_object     =  3, 
   VT_esc                     =  4, 
   VT_change_numeric_value    =  5,
   VT_change_active_mask      =  6,
   VT_change_softkey_mask     =  7,
   VT_change_string_value     =  8,
   VT_onUserLayout_hideShow   =  9,   /* V4 */
   VT_controlAudioTermination = 10,   /* V4 - without response for VT 5 and prior */

   /* Annex C: object transport protocol */
   objectpool_transfer_msg    = 17,
   end_of_pool_transfer       = 18, 

   /* Annex J: auxiliary control */
   auxiliary_assign_type_1       = 32, /* type 1 destination specific */
   aux_input_status_type_1       = 33, /* type 1 destination global */
   preferred_assignment          = 34, /* type 2 only */
   aux_input_maintenance         = 35, /* type 2 only */
   auxiliary_assign_type_2       = 36,
   aux_input_status_enable       = 37, /* type 2 only */
   auxiliary_input_status_type_2 = 38,
   auxiliary_capabilities        = 39, /* type 2 only */ 

   /* Annex D, E, F works with the command buffer */
   /* Annex F: command and macro messages */
   select_active_workingset   = 144,   /**< V6 */
   esc                        = 146,
   hide_show_object           = 160,
   enable_disable_object      = 161,
   select_input_object        = 162,
   control_audio_device       = 163,
   set_audio_volume           = 164,
   change_child_location      = 165,
   change_size                = 166,
   change_background_colour   = 167,
   change_numeric_value       = 168,
   change_end_point           = 169,
   change_font_attributes     = 170,
   change_line_attributes     = 171,
   change_fill_attributes     = 172,
   change_activ_mask          = 173,
   change_softkey_mask        = 174,
   change_attribute           = 175,
   change_priority            = 176,
   change_list_item           = 177,
   delete_object_pool         = 178,
   change_string_value        = 179,
   change_child_position      = 180,
   change_object_label        = 181,   /**< V4 */
   change_polygon_point       = 182,   /**< V4 */
   change_polygon_scale       = 183,   /**< V4 */
   graphics_context           = 184,   /**< V4 */
   get_attribute_value        = 185,   /**< V4 */
   select_colour_map          = 186,   /**< V4 */
   identify_VT                = 187,   /**< V4 - now located in Annex D */
   execute_ExtMacro           = 188,   /**< V5 */
   lockunlock_mask            = 189,   /**< V4 */
   execute_Macro              = 190,   /**< V4 */

   /* Annex D: technical data messages */
   get_memory                 = 192,
   get_supported_widechar     = 193,   /**< V4 */
   get_number_softkey         = 194,
   get_textfonddata           = 195,
   get_WM_data                = 196,   /**< V4 */
   get_supported_objects      = 197,   /**< V4 */
   screen_capture             = 198,   /**< V6 */
   get_hardware               = 199,

   /* Annex E: technical data messages */
   store_version              = 208,
   load_version               = 209,
   delete_version             = 210,
   extended_get_version       = 211,   /**< V5 */
   extended_store_version     = 212,   /**< V5 */
   extended_load_version      = 213,   /**< V5 */
   extended_delete_version    = 214,   /**< V5 */
   get_version                = 223,  
   get_version_response       = 224,

   /* G.4/5 (VT 5F.66/67)  */
   unsupported_VTfunction     = 253,   /**< V5 */

   /* Annex G: status messages */
   VT_status_message           = 254,  
   working_set_maintenance_msg = 255,

   /* Proprietary VT client notifications  */
   vtc_pool_aux_input_type_2   = 256,   /**< Found auxiliary input type 2 object in pool */
   aux_pre_input_status_enable = 257,   /**< Called before aux input status enabled response is send in order to manually disable the aux input. */
   aux_learn_mode_changed      = 258,   /**< VT Auxiliary controls learn mode active bit changed (VT_status_message Bit 6 of byte 7)   */

   vtfunction_undef            = -1    /**< Avoids compiler warning */
} ISOVT_FUNC_e;

 /** \brief
 Enum of information request of VT client or command to VT client
 */
 typedef enum
 {
      NAMEFCT_OF_VTUSER,         /**< Function of ECU which uses VT*/
      VT_SOURCE_ADDRESS,         /**< SA of VT */
      VT_HND,                    /**< CF handle of VT */
      CF_SOURCE_ADDRESS,         /**< SA of VT client */
      CF_HND,                    /**< CF handle of VT client */
      SA_OF_VTOWNER_MASTER,      /**< SA of ECU which has VT communication */
      HND_OF_VTOWNER_MASTER,     /**< CF handle of ECU which has VT communication */
      ID_VISIBLE_DATA_MASK,      /**< Data mask open on VT*/
      ID_VISIBLE_SOFTKEY_MASK,   /**< Soft key mask open on VT */
      VT_BUSY_CODE,              /**< Busy code of VT Status message */
      AUXUNITS_TYPE1_ONBUS,      /**< ISO_TRUE means that at least one auxiliary unit type 1 is on bus */
      AUXUNITS_TYPE2_ONBUS,      /**< ISO_TRUE means that at least one auxiliary unit type 2 is on bus */
      VT_ALIVE,                  /**< VT lost for more than three seconds */
      VT_DOWNLOAD_FINISHED,      /**< That means complete announcing finished */
      VT_POOL_ACTIVE_onVT,       /**< Pool active (selected) on VT */
      VT_STATEOFANNOUNCING,      /**< State of announcing - see #ISOVT_ANNOUNCE_e */
      WS_VERSION_NR,             /**< Version number of this working set */
      VT_NUMBOFVERSIONSTRINGS,   /**< Reads the number of version strings sent of VT */

      /* Static properties of actual VT of this working set */
      VT_NAVSOFTKEYS,            /**< Navigation soft keys - Version 4 */
      VT_SOFTKEYXDOT,            /**< Softkey designator - pixel X */
      VT_SOFTKEYYDOT,            /**< Softkey designator - pixel Y */
      VT_VIRTUALSOFTKEYS,        /**< Number of virtual soft keys of VT */
      VT_PHYSICALSOFTKEYS,       /**< Number of physical soft keys of VT */
      VT_SMALLFONTSIZES,         /**< VT TextFontData - small fonts */
      VT_LARGEFONTSIZES,         /**< VT TextFontData - large fonts */
      VT_TYPEATTRIBUTES,         /**< VT TextFontData - text attributes */
      VT_BOOTTIME,               /**< Boot time of VT - time till first VT-Status-Msg */
      VT_GRAPHICTYPE,            /**< VT hardware - grafik type */
      VT_VTHARDWARE,             /**< VT hardware - audio, touch ... */
      VT_DATAMASKRESOLUTION,     /**< Data mask resolution */
      VT_VERSIONNR,              /**< Version of working set VT */
      VT_BGCOLOURULDM,           /**< Background colour of VTs User-Layout Data Mask */
      VT_BGCOLOURKEYCELL,        /**< Background colour of VTs Key Cells */

      /* Command */
      VT_LOGOUT                  /**< Command that resets a VT client - only for IsoVTDataSet() */
 } ISOVT_STATUS_e;

/* Callback function type definitions */

/** \brief ISOVT_STATUS_DATA_T source */

 /*! \brief VT status message callback data structure */
 typedef struct
 {
    iso_u8           u8Instance; /**< \brief Identifier of the client instance */
    iso_bool         qWsActive;  /**< \brief ISO_TRUE, if the working set is active (displayed on screen) */
    iso_u16          wPage;      /**< \brief Contains the object ID of the open/last mask, or NULL object ID if unknown */
    ISOVT_FUNC_e     eMsgSource; /**< \brief Source: #VT_status_message or #VT_onUserLayout_hideShow */
    ISO_USER_PARAM_T userParam;  /**< \brief User parameter set with IsoVtcCreateInstance() */
 } ISOVT_STATUS_DATA_T;

 /*! \brief VTC event callback data structure */
 typedef struct
 {
    iso_u8           u8Instance; /**< \brief Identifier of the client instance */
    ISOVT_VTEVENT_e  eEvent;     /**< \brief VTC connection event */
    ISO_USER_PARAM_T userParam;  /**< \brief User parameter set with IsoVtcCreateInstance() */
 } ISOVT_EVENT_DATA_T;

 /*! \brief  Type definition of the status callback function */
 typedef void(*ISOVT_CbStatus_t)( const ISOVT_STATUS_DATA_T* psStatusData );

 /*! \brief  Type definition of the message callback function */
 typedef void (*ISOVT_CbMsg_t)( const ISOVT_MSG_STA_T * psMsgData );

 /*! \brief  Type definition of the connection event callback function */
 typedef void (*ISOVT_CbConnectionEv_t)( const ISOVT_EVENT_DATA_T* psEvData );

 /** @} */ /* END vtctypedefs                                                */
 /* ************************************************************************ */

 /** \addtogroup vtc_aux_typedefs
   \brief  Auxiliary Function and Input Type Defines
@{
*/

/* ************************************************************************ */
/** \brief Auxiliary (input) function types */
 typedef enum
 {
    Bool_Latched = 0,    /**< Two-position switch */
    Analog_0_100 = 1,    /**< Analog maintains position setting */
    Bool_NonLatched = 2,    /**< Two-position switch - returns to off */
    Analog_Ret50perc = 3,    /**< Two way analog - return to centre position */
    Analog_Ret0perc = 4,    /**< One way analog - return to 0% */
    DualBool_BothLatched = 5,    /**< Three-position switch - latching in all positions */
    DualBool_BothNonLatched = 6,    /**< Three-position switch - return to centre */
    DualBool_LatchedUp = 7,    /**< Three-position switch - latching in up position */
    DualBool_LatchedDown = 8,    /**< Three-position switch - latching in down position */
    CombinedAnalog_Ret50 = 9,    /**< Two way analog - return to centre position - with latching */
    CombinedAnalog_LatchBool = 10,    /**< Analog maintains position setting with latching Boolean at 0% and 100% positions */
    QuadratBool_NonLatched = 11,    /**< Two quadrature mounted Three-position switches - return to centre position */
    QuadratAnalog = 12,    /**< Two quadrature mounted analog maintain position setting - centre is 50% */
    QuadratAnalog_Ret50prec = 13,    /**< Two quadrature mounted analog returns to centre position at 50% */
    BidirectionalCounter = 14,    /**< Count increases when turning in the encoders "increase" direction (analog opposite direction */
                                      /* ... Reserved */
    RemoveAssignment = 31,    /**< Used for remove assignment command */
    AuxFunUndefined = 32      /**< Undefined (used internal for unused/free entries) */
 } VTAUXTYP_e;

/* ************************************************************************ */
/** \brief Value of auxiliary inputs */
 typedef enum
 {
    AuxDisabled = 0,  /**< Off - backward, down, left, or not pressed */
    AuxEnabled = 1,  /**< On  - forward, up, right, or pressed */
    AuxHeld = 2,  /**< Held (forward, up, or right) */
    AuxEnabledBackwards = 4,  /**< On momentary - backward, down or left */
    AuxHeldBackwards = 8,  /**< Held (backwards, down, or left) */
    AuxDefault = 9
 } VTAUXSTATES_e;

/* ************************************************************************ */
/** \brief Structure for auxiliary control assignment of application */ 
/* [DOXYGEN_VT_AUXAPP_T] */
 typedef struct
 {
    iso_u16       wObjID_Fun;      /**< Object ID of auxiliary function */
    iso_u16       wObjID_Input;    /**< Object ID of auxiliary input */
    VTAUXTYP_e    eAuxType;        /**< Function/input type (without attribute bits)
                                        - only because of downwards compatibility  */
    iso_u16       wManuCode;       /**< Manufacturer Code of auxiliary input device */
    iso_u16       wModelIdentCode; /**< Model identification code of aux input device */
    iso_bool      qPrefAssign;     /**< This assignment shall used for preferred assignment */
    iso_u8        bFuncAttribute;  /**< Complete function attribute byte of auxiliary function */
    ISO_CF_NAME_T baAuxName;       /**< ISO name of the auxiliary input device. The bytes must be set to 0xFF if not used. */
 } VT_AUXAPP_T, * VT_AUXAPP_t;
/* [DOXYGEN_VT_AUXAPP_T] */


/* ************************************************************************ */
/*!\brief structure for common preferred assignment callback function parameters. */
 typedef struct
 {
    iso_u8           u8Instance; /**< \brief Identifier of the client instance */
    ISO_USER_PARAM_T userParam;  /**< \brief User parameter set with IsoVtcCreateInstance() */
 } VT_AUX_PREF_PARAM_T;

/* ************************************************************************ */
/*!
   \brief Preferred assignment callback function pointer.

   \param[in]  \wpp{psParams, const #VT_AUX_PREF_PARAM_T*}
                 Pointer to the parameters to identify the VTC client instance  
   \param[in,out]  \wp{asAuxAss, VT_AUXAPP_T []}
                 Pointer to the array, which must be filled from the application.
   \param[in,out]  \wp{ps16MaxNumberOfAssigns, iso_s16*}
                 Pointer to the number of array entries
                 - in:  The value contains the maximum number of assignment array entries, which can be filled.
                 - out: The application must set the value to the number of filled assignment array entries.
*/
 typedef void (*ISOVT_CbAuxPrefAssignment_t)(const VT_AUX_PREF_PARAM_T* psParams, VT_AUXAPP_T asAuxAss[], iso_s16* ps16MaxNumberOfAssigns);

/** @} */ /* END vtc_aux_typedefs */

/* ************************************************************************ */
/* Application functions */
/** \addtogroup vtmanage 
   \brief API functions for controlling a VT client (init, next VT ...)

          Use this functions to create and connect a VT client 
@{
*/

/* ************************************************************************ */
/*!
   \brief      Creates a VT client instance for the given working set master

   \note Deprecated: Use IsoVtcCreateInstance()

   \param[in]  \wp{s16CfHandleMaster, iso_s16}
                  CF handle of a working set master
   \param[in]  \wpp{userParam, const #ISO_USER_PARAM_T}
                  User parameter value for the callback function calls. \n
                  Use #ISO_USER_PARAM_DEFAULT if not used/needed.
   \param[in]  \wp{pfVTStatusCb, ISOVT_CbStatus_t}
                  Pointer to callback function which is called in case of opening a new data, alarm
                  or window mask, or of
                   - Parameter rqInfo is set to ISO_TRUE, if the working set is active.
                   - Parameter rwPage contains the object ID of the open mask, or NULL object ID if rqInfo is ISO_FALSE.
   \param[in]  \wp{pfVtMsgRecCb, ISOVT_CbMsg_t}
                  Pointer to callback function which is called in case of activation messages
                  and command responses to the user application.
                  See #ISOVT_MSG_STA_T for more information.
   \param[in]  \wp{pfVtConnEvCb, ISOVT_CbConnectionEv_t}
                  Pointer to the connection event callback function
                  or NULL pointer if not used.
   \param[in]  \wpp{pau8NamePreferredVT, const #ISO_CF_NAME_T*}
                  Pointer to NAME of preferred VT

   \retval     iso_u8
                - VT client instance identification number
                - #ISO_INSTANCE_INVALID if there is no instance free
   \par Hints:
         - Preferred VT: During Login the driver waits a boot time for this VT.
           This can be useful in order to choice the last plugged VT. The actual
           VT must be stored in NVM and during login initialised with this function.
         - If the VT client has has auxiliary type 2 functions and connects not to
           the primary VT, a second Aux instance is automatically created later to connect
           to the primary VT. This instance has also an other instance identification number.
   \note Deprecated: Use IsoVtcCreateInstance()
*/
ISO_DEPRECATED
ISO_CLIENT_API
    iso_u8 IsoVT_CreateInstance(iso_s16 s16CfHandleMaster,
       const ISO_USER_PARAM_T userParam,
       ISOVT_CbStatus_t pfVTStatusCb,
       ISOVT_CbMsg_t pfVtMsgRecCb,
       ISOVT_CbConnectionEv_t pfVtConnEvCb,
       const ISO_CF_NAME_T* pau8NamePreferredVT);


/* ************************************************************************ */
/*!
   \brief      Creates a VT client instance for the given working set master

   \param[in]  \wp{s16CfHandleMaster, iso_s16}
                  CF handle of a working set master 
   \param[in]  \wpp{userParam, const #ISO_USER_PARAM_T}
                  User parameter value for the callback function calls. \n
                  Use #ISO_USER_PARAM_DEFAULT if not used/needed.
   \param[in]  \wp{pfVTStatusCb, ISOVT_CbStatus_t}
                  Pointer to callback function which is called in case of opening a new data, alarm
                  or window mask, or of
                   - Parameter rqInfo is set to ISO_TRUE, if the working set is active.
                   - Parameter rwPage contains the object ID of the open mask, or NULL object ID if rqInfo is ISO_FALSE.
   \param[in]  \wp{pfVtMsgRecCb, ISOVT_CbMsg_t}
                  Pointer to callback function which is called in case of activation messages
                  and command responses to the user application. 
                  See #ISOVT_MSG_STA_T for more information.
   \param[in]  \wp{pfVtConnEvCb, ISOVT_CbConnectionEv_t}
                  Pointer to the connection event callback function
                  or NULL pointer if not used.
   \param[in]  \wp{pfAuxPrefAssignCb, ISOVT_CbAuxPrefAssignment_t}
                  Pointer to the preferred assignment callback function
                  (Can set to the NULL pointer if the object pool does not contain auxiliary type 2 functions).
   \param[in]  \wpp{pau8NamePreferredVT, const #ISO_CF_NAME_T*}
                  Pointer to NAME of preferred VT
   \param[in]  \wp{u8BootTimePreferredVT, iso_u8}
                  Boot time of preferred VT in seconds \n
                  (Range 0 - 254; if 0xFF for not available ISO_WAITVT_SEC will be used)
   \retval     iso_u8
                - VT client instance identification number
                - #ISO_INSTANCE_INVALID if there is no instance free
   \par Hints:
         - Preferred VT: During Login the driver waits a boot time for this VT.
           This can be useful in order to choice the last plugged VT. The actual
           VT must be stored in NVM and during login initialised with this function.
         - If the VT client has has auxiliary type 2 functions and connects not to 
           the primary VT, a second Aux instance is automatically created later to connect
           to the primary VT. This instance has also an other instance identification number.
         - To create another instance with a different VT for a CF, 
           IsoVtcCreateInstance() can be called again with a different VT name.
*/
ISO_CLIENT_API
iso_u8 IsoVtcCreateInstance(  iso_s16 s16CfHandleMaster,
                     const ISO_USER_PARAM_T userParam,
                     ISOVT_CbStatus_t pfVTStatusCb,
                     ISOVT_CbMsg_t pfVtMsgRecCb,
                     ISOVT_CbConnectionEv_t pfVtConnEvCb,
                     ISOVT_CbAuxPrefAssignment_t pfAuxPrefAssignCb,
                     const ISO_CF_NAME_T* pau8NamePreferredVT,
                     iso_u8 u8BootTimePreferredVT );

/* ************************************************************************ */
/*!
   \brief      Removes the VT client instance
               
   Triggers the shutdown of the VT client instance.
   After the connection to the VT is closed the instance will be removed.

   \par Hint:
   If the instance has active pool on the VT, the #delete_object_pool command 
   is send in the next cycle to the VT. After the VT response the instance is removed.
   If it is necessary to kill the instance immediately, the following command can be used: \n
   IsoVtcDataSet(u8Instance, VT_LOGOUT, 1u); 

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
*/
ISO_CLIENT_API
void IsoVtcCloseInstance(iso_u8 u8Instance);

/* ************************************************************************ */
/*!
   \brief      Restarts a VT client instance

   Triggers the shutdown of the VT client instance.
   After the current pool is removed from the VT, the instance starts again.

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \param[in]  \wp{qReConnect, iso_bool}
                 - #ISO_TRUE: The connection is "closed" and restarted at the beginning of the state machine 
                 - #ISO_FALSE After the pool is removed the instance restarts with the pool upload procedure
   \retval     iso_s16
               - #E_NO_ERR - restart triggered
               - #E_NOACT  - function called again 
               - #E_NO_INSTANCE - Instance not found
*/
ISO_CLIENT_API
iso_s16 IsoVtcRestartInstance(iso_u8 u8Instance, iso_bool qReConnect);


/* ************************************************************************ */
/*!
   \brief       Reading information of a VT client instance

   This function can be used to read information about a VT client and the connected VT.
   This information are useful for controlling the pool on VT e. g. with
   VT_PHYSICALSOFTKEYS it is possible depending on number of phyical softkeys of
   the VT to choice between different soft key masks.

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \param[in]  \wp{eVTInfo, ISOVT_STATUS_e}
                Enum of wished information of VT \n
                Most of them are of the technical data messages

   \retval     iso_u16    Requested value depending of ISOVT_STATUS_e
               - #VT_SOURCE_ADDRESS: actual SA of VT or ISO_NULL_ADDRESS
               - #CF_SOURCE_ADDRESS: actual SA of WS or ISO_NULL_ADDRESS
               - #ID_VISIBLE_DATA_MASK: actual data mask object in VT status message
               - #ID_VISIBLE_SOFTKEY_MASK: actual soft key mask object in VT status message
               - #VT_BUSY_CODE: see VT status message
               - #AUXUNITS_TYPE1_ONBUS: ISO_TRUE -> Auxiliary unit type 1 is on bus
               - #VT_ALIVE: VT alive check (3s), 1 = alive
               - #VT_DOWNLOAD_FINISHED: announce state > announce_finished? 1
               - #VT_POOL_ACTIVE_onVT: 1: Own pool selected on VT
               - #VT_STATEOFANNOUNCING: see enum ISOVT_ANNOUNCE_e
               - #WS_VERSION_NR: Supported version of own pool see ISO_VTVERSION
               - #VT_NUMBOFVERSIONSTRINGS: Number of version strings stored in VT
               - #VT_VERSIONNR: Supported version of VT see Part 6 - D.3
               - #VT_NAVSOFTKEYS: Navigation softkeys ( of Version 4 else 0xFF ) 
               - #VT_SOFTKEYXDOT ... VT_DATAMASKRESOLUTION: \n
                  Technical data messages of actual VT see Part 6 Annex D
               - #VT_BGCOLOURULDM, VT_BGCOLOURKEYCELL: colours see A.3
   \note  \par
     - VT_BOOTTIME: If the VT supports Boottime (>=IL4 and Value != 0xFF) the value (in sec) can be red,
       and then stored in NVM and set with IsoVtcDataSet() next startup.

*/
ISO_CLIENT_API
iso_u16 IsoVtcGetStatusInfo( iso_u8 u8Instance, ISOVT_STATUS_e eVTInfo );

#ifdef ISO_VTC_UT3

/**********************************************************************************/
/*!
   \brief      Manual setting of a supported ( parsable ) object type
   
   This function is used to add object types of higher versions to a list
   which is used for parsing decisions 

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{eObjType, OBJTYP_e}
                Object type (Byte 3 of every object) 
*/
ISO_CLIENT_API
   void IsoVtcObjTypeParsableSet(iso_u8 u8Instance, OBJTYP_e eObjType);

/**********************************************************************************/
/*!
   \brief       Check if object type is supported of VT

   Precondition for this function: VT must be version 4 or higher.
   Then VT sends a sorted list during login with all supported objects. It can used
   for controlling the command messages

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{eObjType, OBJTYP_e}
                Object type (Byte 3 of every object) \n
                Range: 0 - 36, 40 see ISO11783 - 6 - A.1.1 or OBJTYP_e
   \retval      iso_bool     ISO_TRUE if VT supports this object
*/
ISO_CLIENT_API
   iso_bool IsoVtcObjTypeIsSupported( iso_u8 u8Instance, OBJTYP_e eObjType);

#endif  /* ISO_VTC_UT3 */

/* ************************************************************************ */
/*!
   \brief       Setting information of a VT client

   This function enables the change of some Working Set settings or the control
   of the state machine. For settings it should called after IsoVtcCreateInstance().
   Furthermore it can be completely resetted a VT client with VT_LOGOUT.

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \param[in]  \wp{eVTInfo, ISOVT_STATUS_e}
               VT_BOOTTIME          - Boot time of preferredVT in seconds \n
               VT_STATEOFANNOUNCING - Forced setting of Login state machine (test purposes)
                                       see ISOVT_ANNOUNCE_e \n
               WS_VERSION_NR        - Version number of working set ( -> Used object in pool )\n
               VT_LOGOUT            - Shut down a VT client instance ( set wDatNew to 1u to kill instance; 0u for normal logout) \n
                                      For a normal logout you can also use IsoVtcCloseInstance()
   \param[in]  \wp{wDatNew, iso_u16}
               New Value
   \retval     iso_s16
               - E_NO_ERR
               - E_NO_INSTANCE
*/
ISO_CLIENT_API
iso_s16 IsoVtcDataSet( iso_u8 u8Instance, ISOVT_STATUS_e eVTInfo, iso_u16 wDatNew );

/*****************************************************************************/
/*!
   \brief        Continue VT Login state machine

   There are some cases where VT Login stops for application interaction. 
   This function continues the VT state machine.

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \retval   iso_s16
              - E_NO_ERR
              - E_ERROR_INDI - actual state don't supported of this function
              - E_NO_INSTANCE
   \par
       - Supported states:
          - waiting_before_store
*/
ISO_CLIENT_API
     iso_s16 IsoVtcContinue( iso_u8 u8Instance );

/**************************************************************************/
/*!
    \brief    Function reads the Version strings received from VT with (Extended) Get Versions

    The version strings received of VT can be read. If both Working Set and VT are Version 5
    or higher the version strings are ( exactly )32 bytes else 7 bytes.

    \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
    \param[in]  \wp{au8VersionStrings, iso_u8[][ISO_VTC_LEN_VERSIONSTR]}
                Pointer to 2d-array - driver writes the version strings in this array
                - first element is number of version strings (see ISO_VTC_MAX_POOLVERSIONS)
                - second element is string length #ISO_VTC_LEN_VERSIONSTR
    \retval     iso_s16
                Number of version strings received with (Extended) Get Version
*/
ISO_CLIENT_API
     iso_u8 IsoVtcVersionStringGet(iso_u8 u8Instance, iso_u8 au8VersionStrings[][ISO_VTC_LEN_VERSIONSTR]);

/*****************************************************************************/
/*!
   \brief   Function to set the preferred VT to a new CF name.

   The function can only called before the client has selected a VT (safe state). \n
   In this case the given name is set as new preferred VT and the VT boot timeout is reseted. 

   \param[in]  \wp{u8Instance, iso_u8}
                  Identifier of the client instance
   \param[in]  \wpp{rpabVtName, const #ISO_CF_NAME_T*}
                  Pointer to the NAME of the VT or dummy name (8 * 0xFFu)

   \retval       iso_s16
                  - E_NO_ERR      - On success
                  - E_RANGE       - rpabVtName is the NULL pointer or WS instance is not set
                  - E_ERROR_INDI  - Changing only possible while waiting for the currently set preferred VT
                  - E_USER_ERROR  - CF name "rpabVtName" is not a valid VT name (wrong name function)
   \par
       - This function should be used to select the wished VT during the #IsoEvConnSelectPreferredVT event callback. 
*/
ISO_CLIENT_API
     iso_s16 IsoVtcSetNewPreferredVT(iso_u8 u8Instance, const ISO_CF_NAME_T* rpabVtName);

/*****************************************************************************/
/*!
   \brief        Calling this function releases the procedure to move to another VT

   The application have to select an available VT and releases with this function the VT change.

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \param[in]  \wpp{rpabVtName, const #ISO_CF_NAME_T*}
                  Pointer to NAME of "Next VT" see ISO11783 - 5

   \retval       iso_s16
                  - E_NO_ERR      - OK
                  - E_NOACT       - VT is used by an other mask instance of this client
                  - E_ERROR_INDI  - Changing only possible in case of full log-on
                  - E_USER_ERROR  - User "rpabVtName" not found or no VT
   \par
       - Using see example in VT application
*/
ISO_CLIENT_API
     iso_s16 IsoVtcMultipleNextVT( iso_u8 u8Instance,const ISO_CF_NAME_T* rpabVtName );

/******************************************************************************/
/*!
    \brief        This function reads the language of the working set

          The language command of the VT which displays the data masks is retured. If there
          is no VT the language command of the TECU is returned.

   \param[in]    \wp{u8Instance, iso_u8}
                  Identifier of the client instance
   \param[out]   \wp{abLanguageCmd, iso_u8[]}
                   Pointer to language command data array of this working set \n
                   Size of the array must be (at least 8 bytes)
   \retval       iso_s16
                 - E_NO_ERR - OK
                 - E_ERROR_INDI - WS not found
   \par
   - Attention: Function works only correct after login has passed the LC reception
    (e. g.  waiting_after_GetVersions) else it provides the TECU LC
*/
ISO_CLIENT_API
   iso_s16 IsoVtcReadWorkingSetLanguageData( iso_u8 u8Instance, iso_u8 abLanguageCmd[] );

/**********************************************************************/
/*!
   \brief       Calculate free elements of Command FIFO

   This function determines the number of free elements of the command FIFO.
   It has been implemented for LIB Implementation (initiated of Grimme)

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \retval     iso_u16  
               Number of free elements of command FIFO \n
               Range: 0 - ISO_VTC_CMD_BUFFER_MAX
*/
ISO_CLIENT_API
    iso_u16  IsoVtcGetCMDFifoFree( iso_u8 u8Instance );

/**********************************************************************/
/*!
   \brief       Helper function to get the VT client instance identifier to a client CF handle

   This function determines the number of free elements of the command FIFO.
   It has been implemented for LIB Implementation (initiated of Grimme)

   \param[in]  \wp{s16CfHandleMaster, iso_s16}
                 CF handle of a working set master
   \param[in]  \wp{eInstanceType, ISOVT_INSTANCE_TYPE_Te}
                 Instance type which should be returned
   \retval     iso_u8  
               Identifier of the client instance or #ISO_INSTANCE_INVALID if not found
*/
ISO_CLIENT_API
iso_u8 IsoVtcGetInstanceID(iso_s16 s16CfHandleMaster, ISOVT_INSTANCE_TYPE_Te eInstanceType);

/** @} */ /* end VT Client Management Functions */

/* ********************************* IsoVTCmd.c  *************************************** */
/** \addtogroup vttechmsg 
   \brief API functions for sending Annex D and E messages
@{
*/

#ifdef ISO_VTC_UT3
/***************************************************************************/
/*!
   \brief       This technical message requests the supported widechars for a certain code plane ( D.10 )

   The Get Supported Widechars message is used by the Working Set to determine the WideChars supported
   by the VT. This message only applies to version 4 and later VTs.

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \param[in]  \wp{u8CodePlane, iso_u8}
               Codeplane - Range: 0 ... 16
   \param[in]  \wp{u16RangeFirstWidechar, iso_u16}
               First widechar of inquiried code plane
   \param[in]  \wp{u16RangeLastWidechar, iso_u16}
               Last widechar of inquiried code plane
   \retval     iso_s16
               - #E_NO_ERR          - OK
               - #E_OVERFLOW        - buffer overflow
               - #E_NOACT           - Command not possible in current state
               - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_GetSupportedWidechar(iso_u8 u8Instance, iso_u8 u8CodePlane,
                                       iso_u16 u16RangeFirstWidechar, iso_u16 u16RangeLastWidechar);

/***************************************************************************/
/*!
   \brief       This technical message requests background colours ( D.12 )

   The Working Set sends the Get Window Mask Data message to request the background colour
   of UserLayout Data Mask and the background colour of the Key Cells on a User-Layout Soft Key Mask.
   This message applies to version 4 and later VTs.

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \retval     iso_s16
                - #E_NO_ERR          - OK
                - #E_OVERFLOW        - buffer overflow
                - #E_NOACT           - Command not possible in current state
                - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_GetWindowMaskData(iso_u8 u8Instance);

/***************************************************************************/
/*!
\brief       This technical message requests for supported objects ( D.14 )

   This command is used by the WS to get the list of all object types supported by the VT.
   This message applies to version 4 and later VTs.

   \param[in] \wp{u8Instance, iso_u8}
              Identifier of the client instance
   \retval    iso_s16
              - #E_NO_ERR          - OK
              - #E_OVERFLOW        - buffer overflow
              - #E_NOACT           - Command not possible in current state
              - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_GetSupportedObjects(iso_u8 u8Instance);

/*****************************************************************************/
/*!
   \brief      Command Screen capture ( Part 6 - D.16 )

   This command, available in VT version 6 and later, requests a lossless screen (image) capture from the VT
   This message is available in VT Version 6 and later.

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \param[in]  \wp{u8ItemRequested, iso_u8}
               Item requested ( 0 = Screen image )
   \param[in]  \wp{u8Path, iso_u8}
               Path ( 1 = VT accessible storage/removable media ) 
   \retval     iso_s16
               - #E_NO_ERR          - OK
               - #E_OVERFLOW        - buffer overflow
               - #E_NOACT           - Command not possible in current state
               - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_ScreenCapture(iso_u8 u8Instance, iso_u8 u8ItemRequested, iso_u8 u8Path);

/*****************************************************************************/
/*!
   \brief      Command Identify VT ( Part 6 - D.18 )

   The Identify VT message may be sent by either Working Sets or VTs.
   This message is available in VT Version 4 and later.

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \retval     iso_s16
               - #E_NO_ERR          - OK
               - #E_OVERFLOW        - buffer overflow
               - #E_NOACT           - Command not possible in current state
               - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_IdentifyVT(iso_u8 u8Instance);

#endif /* ISO_VTC_UT3 */

/***************************************************************************************/
/*!
   \brief         Command for deleting object pool of VT ROM

   This function releases a command to the VT. The pool selected with the version
   string is deleted of Flash.

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \param[in]  \wpp{au8VersionString, const #iso_u8[] }
               Pointer to version String which shall be deleted \n
               Length of Bytearray: 7 Characters
   \retval     iso_s16
               - #E_NO_ERR          - OK
               - #E_OVERFLOW        - buffer overflow
               - #E_NOACT           - Command not possible in current state
               - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_DeleteVersion(iso_u8 u8Instance, const iso_u8 au8VersionString[]);

/* ************************************************************************ */
/*!
   \brief       Store object pool with version label from VT RAM to VT ROM

   This function stores the actual pool in VT RAM into the Flash (ROM) of the VT.

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \param[in]  \wpp{au8VersionString, const #iso_u8[] }
               Pointer to version String which shall be deleted \n
               Length of Bytearray: 7 Characters
   \retval     iso_s16
              - #E_NO_ERR          - OK
              - #E_OVERFLOW        - buffer overflow
              - #E_NOACT           - Command not possible in current state
              - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_StoreVersion(iso_u8 u8Instance, const iso_u8 au8VersionString[]);

/** @} */ /* END vttechmsg */


/* ********************************* IsoVTCmd.c  *************************************** */
/** \addtogroup vtFcmdmsg
   \brief API functions for sending Annex F command messages
@{
*/
/*****************************************************************************/
/*!
   \brief      Command Hide/Show Object (Container) ( Part 6 - F.2 )

   The Hide/Show Object command is used to hide or show a container object.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16 }
                Object ID of Container
   \param[in]  \wp{qVisible, iso_bool}
                0 = Hide, 1 = Show
   \retval      iso_s16
                 - #E_NO_ERR          - OK
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_ObjHideShow(iso_u8 u8Instance, iso_u16 u16ObjId, iso_bool qVisible);

/*********************************************************************************/
/*!
   \brief      Command enable/disable (input) object - ( Part 6 - F.4 )

   This command is used to enable or disable an input field object and pertains
   to the accessibility of an input object.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID of input object
   \param[in]  \wp{qAbility, iso_bool}
                0 == disable, 1 == enable
   \retval      iso_s16
                 - #E_NO_ERR          - OK
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_ObjEnableDisable(iso_u8 u8Instance, iso_u16 u16ObjId, iso_bool qAbility);

/*********************************************************************************/
/*!
   \brief      Command Select input object ( Part 6 - F.6 )

   This command is used to force the selection of an input field object.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID of input object
   \param[in]  \wp{u8Option,  iso_u8}
                normal: 0xFF, for Version 4 also 0 possible
   \retval      iso_s16
                 - #E_NO_ERR          - OK
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_ObjSelectInput(iso_u8 u8Instance, iso_u16 u16ObjId, iso_u8 u8Option);

/***************************************************************************/
/*!
   \brief         Esc Command

   This command is used to abort operator input ( Part 6 - F.8 ).

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \retval     iso_s16
                - #E_NO_ERR          - OK
                - #E_OVERFLOW        - buffer overflow
                - #E_NOACT           - Command not possible in current state
                - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_ESC(iso_u8 u8Instance);

/* ************************************************************************ */
/*!
   \brief      Command Control audio device ( Part 6 - F.10 ).

   This command can be used to control the audio on the VT.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u8NumOfRepit, iso_u8}
                Number of repetitions
                Range: 1 - 255
   \param[in]  \wp{u16Frequency, iso_u16}
                Frequency
   \param[in]  \wp{u16OnTimeMs, iso_u16}
                On time duration in ms
   \param[in]  \wp{u16OffTimeMs, iso_u16}
                Off time duration in ms
   \retval      iso_s16
                 - #E_NO_ERR          - OK
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_CtrlAudioSignal(iso_u8 u8Instance, iso_u8 u8NumOfRepit, iso_u16 u16Frequency,
                                  iso_u16 u16OnTimeMs, iso_u16 u16OffTimeMs);

/***********************************************************************************/
/*!
   \brief      Command SetAudioVolume

   This command can be used to control the audio on the VT (volume)  ( Part 6 - F.12 )

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u8Volume, iso_u8}
                Volume 0 - 100 (%)
   \retval      iso_s16
                 - #E_NO_ERR          - OK
                 - #E_OVERFLOW        - Buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NOT_AVAILABLE   - VT has got no adjustable volume output
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_SetAudioVolume(iso_u8 u8Instance, iso_u8 u8Volume);

/*********************************************************************************/
/*!
   \brief      Command change child location ( Part 6 - F.14 )

   The Change Child Location command is used to change the relative position of an object.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID
   \param[in]  \wp{u16ObjIdParent, iso_u16}
                Parent object ID
   \param[in]  \wp{u8Xchange, iso_u8}
                Relative change in x position (interpreted as signed!)
   \param[in]  \wp{u8Ychange, iso_u8}
                Relative change in y position (interpreted as signed!)
   \retval      iso_s16
                 - #E_NO_ERR          - OK
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_ChildLocation(iso_u8 u8Instance, iso_u16 u16ObjId, iso_u16 u16ObjIdParent,
                                iso_u8 u8Xchange, iso_u8 u8Ychange);

/****************************************************************************************/
/*!
   \brief      Command change child position ( Part 6 - F.16 )

   The Change Child Location command is used to change the absolute position of an object.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID
   \param[in]  \wp{u16ObjIdParent, iso_u16}
                Parent object ID
   \param[in]  \wp{s16Xposition, iso_s16}
                New X position relative to the top left corner of parent object
   \param[in]  \wp{s16Yposition, iso_s16}
                New Y position relative to the top left corner of parent object.
   \retval      iso_s16
                - #E_NO_ERR          - OK
                - #E_OVERFLOW        - buffer overflow
                - #E_NOACT           - Command not possible in current state
                - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_ChildPosition(iso_u8 u8Instance, iso_u16 u16ObjId, iso_u16 u16ObjIdParent,
                                iso_s16 s16Xposition, iso_s16 s16Yposition);

/***********************************************************************************/
/*!
   \brief      Command change size  ( Part 6 - F.18 )

   The Change Size command is used to change the size of an object.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID
   \param[in]  \wp{u16Width, iso_u16}
                New width
   \param[in]  \wp{u16Height, iso_u16}
                New height
   \retval      iso_s16
                 - #E_NO_ERR          - OK
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_Size(iso_u8 u8Instance, iso_u16 u16ObjId, iso_u16 u16Width, iso_u16 u16Height);

 /*****************************************************************************/
/*!
   \brief      Command change background colour ( Part 6 - F.20 )

   This command is used to change the background colour of an object.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID
   \param[in]  \wp{u8Colour, iso_u16}
                New Background colour see Part 6 - A.3 VT standard colour palette
   \retval      iso_s16
                 - #E_NO_ERR          - OK
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_BackgroundColour(iso_u8 u8Instance, iso_u16 u16ObjId, iso_u8 u8Colour);

/******************************************************************************/
/*!
   \brief      Command change numeric value ( Part 6 - F.22 )

   This command is used to change the value of an object. It applies only to objects
   that have a numeric value attribute.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID
   \param[in]  \wp{u32NewValue, iso_u32}
                New value of ID
   \retval      iso_s16
                 - #E_NO_ERR          - OK
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_NumericValue(iso_u8 u8Instance, iso_u16 u16ObjId, iso_u32 u32NewValue);

/************************************************************************************/
/*!
   \brief      Command change numeric value with command buffer reference ( Part 6 - F.22 )

   This command is used to change the value of an object. It applies only to objects
   that have a numeric value attribute. If the objectID is already in the command FIFO
   then the value of this FIFO entry is updated.

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                 Object ID
   \param[in]  \wp{u32NewValue, iso_u32}
                 New value of ID
   \retval       iso_s16
                  - #E_NO_ERR          - OK
                  - #E_OVERFLOW        - buffer overflow
                  - #E_NOACT           - Command not possible in current state
                  - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_NumericValueRef(iso_u8 u8Instance, iso_u16 u16ObjId, iso_u32 u32NewValue);

/*******************************************************************************/
/*!
   \brief      Command Change String Value ( Part 6 - F.24 )

   This command sends a string to the VT. The length of the string including '\0'
   may not be longer than the define ISO_VTC_CMD_STR_MAX_LENGTH. Take care that '\0' is trailed.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID
   \param[in]  \wpp{pau8String, const #iso_u8[] }
                Pointer to string
   \retval      iso_s16
                 - #E_NO_ERR          - transport started
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_String(iso_u8 u8Instance, iso_u16 u16ObjId, const iso_u8 pau8String[]);

/*******************************************************************************/
/*!
   \brief      Command Change String Value with command buffer reference ( Part 6 - F.24 )

   This command sends a string to the VT. If the ObjectID is already in the command FIFO
   then the value of this FIFO entry is updated.  The length of the string including '\0'
   may not be longer than the define ISO_VTC_CMD_STR_MAX_LENGTH. Take care that '\0' is trailed.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID
   \param[in]  \wpp{pau8String, const #iso_u8[] }
                Pointer to string
   \retval      iso_s16
                 - #E_NO_ERR          - transport started
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_StringRef(iso_u8 u8Instance, iso_u16 u16ObjId, const iso_u8 pau8String[]);

/*******************************************************************************************/
/*!
   \brief      Command change end point ( Part 6 - F.26 )

   This command is used to change the end point of a line object by changing
   the width, height and/or line direction attributes.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID
   \param[in]  \wp{u16Width, iso_u16}
                X value of end point
   \param[in]  \wp{u16Height, iso_u16}
                Y value of end point
   \param[in]  \wp{u8LineDirection, iso_u8}
                Line direction see Part 6 - B.27
   \retval     iso_s16
                - #E_NO_ERR          - OK
                - #E_OVERFLOW        - buffer overflow
                - #E_NOACT           - Command not possible in current state
                - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_EndPoint(iso_u8 u8Instance, iso_u16 u16ObjId, iso_u16 u16Width, iso_u16 u16Height, iso_u8 u8LineDirection);

/*******************************************************************************/
/*!
   \brief      Command change font attributes ( Part 6 - F.28 )

   This command is used to change the font attributes in a font attributes object.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID
   \param[in]  \wp{u8FontColour, iso_u8}
                New font colour (see Part 6 - A.3)
   \param[in]  \wp{u8FontSize, iso_u8}
                New font size (see Part 6 - B.14)
   \param[in]  \wp{u8FontType, iso_u8}
                New font type (see Part 6 - B.14)
   \param[in]  \wp{u8FontStyle, iso_u8}
                New font style (see Part 6 - B.14)
   \retval      iso_s16
                 - #E_NO_ERR          - OK
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16  IsoVtcCmd_FontAttributes( iso_u8 u8Instance, iso_u16 u16ObjId,
                                   iso_u8 u8FontColour, iso_u8 u8FontSize,
                                   iso_u8 u8FontType, iso_u8 u8FontStyle
                                  );

/*******************************************************************************/
/*!
   \brief      Command change line attributes ( Part 6 - F.30 )

   This command is used to change the line attributes in a line attributes object.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID
   \param[in]  \wp{u8LineColour, iso_u8}
                New line colour (see Part 6 - A.3)
   \param[in]  \wp{u8LineWidth, iso_u8}
                New line width (see Part 6 - B.14.3)
   \param[in]  \wp{u16LineArt, iso_u16}
                New line art (see Part 6 - B.14.3)
   \retval     iso_s16
                - #E_NO_ERR          - OK
                - #E_OVERFLOW        - buffer overflow
                - #E_NOACT           - Command not possible in current state
                - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16  IsoVtcCmd_LineAttributes( iso_u8 u8Instance, iso_u16 u16ObjId,
                                   iso_u8 u8LineColour, iso_u8 u8LineWidth, iso_u16 u16LineArt );

/**********************************************************************************/
/*!
   \brief      Command change fill attributes ( Part 6 - F.32 )

   This command is used to change the fill attributes in a fill attributes object.

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                 Object ID
   \param[in]  \wp{u8FillType, iso_u8}
                 New fill type (see Part 6 - B.14.4)
   \param[in]  \wp{u8FillColour, iso_u8}
                 New fill colour (see Part 6 - B.14.4)
   \param[in]  \wp{u16FillPatternId, iso_u16}
                 New fill pattern (see Part 6 - B.14.4)
   \retval       iso_s16
                  - #E_NO_ERR          - OK
                  - #E_OVERFLOW        - buffer overflow
                  - #E_NOACT           - Command not possible in current state
                  - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16	 IsoVtcCmd_FillAttributes( iso_u8 u8Instance, iso_u16 u16ObjId,
                                    iso_u8 u8FillType, iso_u8 u8FillColour, iso_u16 u16FillPatternId );

/******************************************************************************/
/*!
   \brief      Command change active mask( Part 6 - F.34 )

   This command is used to change the active mask of a working set to either
   a data or an alarm mask object.

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \param[in]  \wp{u16WorkSetId, iso_u16}
                 WorkingSet Object ID
   \param[in]  \wp{u16NewMaskId, iso_u16}
                 Object ID of new active (data/alarm)-mask
   \retval       iso_s16
                  - #E_NO_ERR          - OK
                  - #E_OVERFLOW        - buffer overflow
                  - #E_NOACT           - Command not possible in current state
                  - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_ActiveMask(iso_u8 u8Instance, iso_u16 u16WorkSetId, iso_u16 u16NewMaskId);

/******************************************************************************/
/*!
   \brief      Command change soft key mask( Part 6 - F.36 )

   This command is used to change the soft key mask associated with a data or alarm mask object.

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \param[in]  \wp{u8MaskType, iso_u8}
                 1 == Data, 2 == Alarm
   \param[in]  \wp{u16DataMaskId, iso_u16}
                 Object ID of active Mask
   \param[in]  \wp{u16SoftKeyMaskId, iso_u16}
                 Object ID of (new) soft key mask
   \retval       iso_s16
                  - #E_NO_ERR          - OK
                  - #E_OVERFLOW        - buffer overflow
                  - #E_NOACT           - Command not possible in current state
                  - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_SoftKeyMask(iso_u8 u8Instance, iso_u8 u8MaskType, iso_u16 u16DataMaskId, iso_u16 u16SoftKeyMaskId);

/* ************************************************************************ */
/*!
   \brief      Command change attribute( Part 6 - F.38 )

   This command is used to change any attribute with an assigned AID.
   This message cannot be used to change strings.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID
   \param[in]  \wp{u8IdAttribute, iso_u8}
                Attribute ID (AID) - see description of wished object
   \param[in]  \wp{u32ValueAttribute, iso_u32}
                New value for attribute
   \retval      iso_s16
                 - #E_NO_ERR          - OK
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_Attribute(iso_u8 u8Instance, iso_u16 u16ObjId, iso_u8 u8IdAttribute, iso_u32 u32ValueAttribute);

/**********************************************************************************/
/*!
   \brief      Command change priority( Part 6 - F.40 )

   This command is used to change the priority of an alarm mask.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID of alarm mask
   \param[in]  \wp{u8Priority, iso_u8}
                New priority
   \retval      iso_s16
                 - #E_NO_ERR          - OK
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_Priority(iso_u8 u8Instance, iso_u16 u16ObjId, iso_u8 u8Priority);

/*******************************************************************************/
/*!
   \brief      Command change list item ( Part 6 - F.42 )

   This command is used to change a list item in a list input object.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID of a list input object
   \param[in]  \wp{u8ListIndex, iso_u8}
                List index (-> see list)
   \param[in]  \wp{u16NewObjId, iso_u16}
                New object ID or 0xFFFF to set empty
   \retval      iso_s16
                 - #E_NO_ERR          - OK
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_ListItem(iso_u8 u8Instance, iso_u16 u16ObjId, iso_u8 u8ListIndex, iso_u16 u16NewObjId);

#ifdef ISO_VTC_UT3
/*****************************************************************************/
/*!
   \brief      Command Lock/UnlockMask( Part 6 - F.46 )

   This message is available in VT Version 4 and later. This command is used by a
   Working Set to disallow or allow screen refreshes at the VT for the visible Data
   Mask or User-Layout Data Mask owned by the requesting Working Set.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u8LockCmd, iso_u8}
                0 = Unlock, 1 = Lock data mask or user-layout data mask
   \param[in]  \wp{u16MaskId,  iso_u16}
                Object ID of data mask or user layout data mask to lock or unlock
   \param[in]  \wp{u16LockTimeoutMs,  iso_u16}
                Lock timeout in ms or zero for no timeout
   \retval      iso_s16
                - #E_NO_ERR          - OK
                - #E_OVERFLOW        - buffer overflow
                - #E_NOACT           - Command not possible in current state
                - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_LockUnlockMask(iso_u8 u8Instance, iso_u8 u8LockCmd, iso_u16 u16MaskId, iso_u16 u16LockTimeoutMs);

/*****************************************************************************/
/*!
   \brief      Command Execute Macro( Part 6 - F.48 )

   This message is available in VT Version 4 and later.
   This command is used to execute a Macro.

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \param[in]  \wp{u16ObjId,  iso_u16}
               Object ID of Macro object ( max. value 255 )
   \retval     iso_s16
               - #E_NO_ERR          - OK
               - #E_OVERFLOW        - buffer overflow
               - #E_NOACT           - Command not possible in current state
               - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_ExecuteMacro(iso_u8 u8Instance, iso_u16 u16ObjId);

/*****************************************************************************/
/*!
   \brief      Command Change Object Label( Part 6 - F.50 )

   This command is used by an ECU to change a label of an object. See also B.21
   Object Label Reference List object.

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \param[in]  \wp{u16ObjId,  iso_u16}
               Object ID of object to associate label with
   \param[in]  \wp{u16ObIdStringVar, iso_u16}
               Object ID of a String Variable object that contains the label string
               (32 characters maximum) or FFFF if no text is supplied
   \param[in]  \wp{u8FontType,  iso_u8}
               Font type (ignored if String Variable object reference is NULL or the
               string contains a WideString )
   \param[in]  \wp{u16ObIdGrafic,  iso_u16}
               Object ID of an object to be used as a graphic representation of
               the object label or FFFF16 if no designator supplied.
   \retval     iso_s16
               - #E_NO_ERR          - OK
               - #E_OVERFLOW        - buffer overflow
               - #E_NOACT           - Command not possible in current state
               - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_ChangeObjectLabel(iso_u8 u8Instance, iso_u16 u16ObjId, 
                                    iso_u16 u16ObIdStringVar, iso_u8 u8FontType, iso_u16 u16ObIdGrafic);

/*****************************************************************************/
/*!
   \brief      Command Change Polygon Point( Part 6 - F.52 )

   This command is used by a Working Set to modify a point in an Output Polygon object.

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \param[in]  \wp{u16ObjId,  iso_u16}
               Object ID of the Output Polygon object to change
   \param[in]  \wp{u8PointIndex,  iso_u8}
               Point index of the point to replace.
   \param[in]  \wp{u16NewXValue, iso_u16}
               New X value of a point relative to the top left corner of the polygon
   \param[in]  \wp{u16NewYValue,  iso_u16}
               New Y value of a point relative to the top left corner of the polygon
   \retval     iso_s16
               - #E_NO_ERR          - OK
               - #E_OVERFLOW        - buffer overflow
               - #E_NOACT           - Command not possible in current state
               - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_ChangePolygonPoint(iso_u8 u8Instance, iso_u16 u16ObjId, 
                                     iso_u8 u8PointIndex, iso_u16 u16NewXValue, iso_u16 u16NewYValue);

/*****************************************************************************/
/*!
   \brief      Command Change Polygon Scale( Part 6 - F.54 )

   This command is used by a Working Set to change the scale of a complete Output Polygon object.

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
               Object ID of the Output Polygon object to scale
   \param[in]  \wp{u16NewWidth, iso_u16}
               New width attribute
   \param[in]  \wp{u16NewHeight, iso_u16}
               New height attribute
   \retval     iso_s16
               - #E_NO_ERR          - OK
               - #E_OVERFLOW        - buffer overflow
               - #E_NOACT           - Command not possible in current state
               - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_ChangePolygonScale(iso_u8 u8Instance, iso_u16 u16ObjId, iso_u16 u16NewWidth, iso_u16 u16NewHeight);

/*****************************************************************************/
/*!
   \brief      Command Graphics Context ( Part 6 - F.56 )

   This command is used to manipulate a graphics Context object (only on version 4 or later VTs).

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
               Object ID of a Graphics Context object
   \param[in]  \wp{u8SubCommandID, iso_u8}
               Sub-Command ID
   \param[in]  \wpp{u8ParaList[], const #iso_u8[]}
               Parameters based on sub-command ID byte
   \param[in]  \wp{u16LenBytes, iso_u16}
               Length in bytes of parameter list
   \retval     iso_s16
               - #E_NO_ERR          - OK
               - #E_OVERFLOW        - buffer overflow
               - #E_NOACT           - Command not possible in current state
               - #E_NO_INSTANCE     - No VT client available
   \note  \par
   - Function uses string buffer ( Parameterlist has to be smaller than ISO_VTC_CMD_STR_MAX_LENGTH ) 
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_GraphicsContext(iso_u8 u8Instance, iso_u16 u16ObjId, iso_u8 u8SubCommandID,
                                  const iso_u8 u8ParaList[], iso_u16 u16LenBytes);

/*****************************************************************************/
/*!
   \brief      Command GetAttribute( Part 6 - F.58 )

   This message is available in VT Version 4 and later. This command is used by a
   Working Set to query the VT for the current state of objects within the VT.

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjId, iso_u16}
                Object ID
   \param[in]  \wp{u8AID, iso_u8}
                Attribute ID of the object
   \retval      iso_s16
                 - #E_NO_ERR          - OK
                 - #E_OVERFLOW        - buffer overflow
                 - #E_NOACT           - Command not possible in current state
                 - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_GetAttribute(iso_u8 u8Instance, iso_u16 u16ObjId, iso_u8 u8AID);

/* ************************************************************************ */
/*!
   \brief      Command Select Colour Map ( VT version 4 and later ) ( Part 6 - F.60 )

   The Select Colour Map command is used to select the active Colour Map. This command can take a
   long time to execute. The command applies to any presentation from the originating Working Set,
   which includes objects that may be shown on other Working Set screens (e.g. Auxiliary Control
   objects as may be presented on VT proprietary and other Working Set masks using the Auxiliary
   Control Designator Type 2 Object Pointer).

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u16ObjIdColourMap, iso_u16}
                Object ID of Colour map object or FFFF to restore the default
                colour table (see A.3)
   \retval      iso_s16
                - #E_NO_ERR          - OK
                - #E_OVERFLOW        - buffer overflow
                - #E_NOACT           - Command not possible in current state
                - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_SelectColourMap(iso_u8 u8Instance, iso_u16 u16ObjIdColourMap);

/*****************************************************************************/
/*!
   \brief      Command Execute Extended Macro( Part 6 - F.62 )

   This command is used to execute a Macro with 16-bit Object ID.
   This message is available in VT version 5 and later.

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \param[in]  \wp{u16ObjIdMacro,  iso_u16}
               Object ID of Macro object
   \retval     iso_s16
               - #E_NO_ERR          - OK
               - #E_OVERFLOW        - buffer overflow
               - #E_NOACT           - Command not possible in current state
               - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_ExecuteExtendedMacro(iso_u8 u8Instance, iso_u16 u16ObjIdMacro);

/*****************************************************************************/
/*!
   \brief      Command Select Active Working Set( Part 6 - F.64 )

   This command is used by the currently active Working Set to request that the VT select a new active Working Set.
   This message is available in VT version 6 and later.

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \param[in]  \wpp{pau8Name,  const #iso_u8[]}
               Iso NAME of the new active working set
   \retval     iso_s16
               - #E_NO_ERR          - OK
               - #E_OVERFLOW        - buffer overflow
               - #E_NOACT           - Command not possible in current state
               - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_SelectActiveWorkingSet(iso_u8 u8Instance, const iso_u8 pau8Name[]);

#endif /* ISO_VTC_UT3 */

/*****************************************************************************/
/*!
   \brief      Send Proprietary VT Command 

   Proprietary commands should not be used between ECUs and VT with different manufacturer codes. \n
   If the command data size is lower 7 (u8DataSize < 7u) the empty bytes in the message are filled with FF
   (message length is minimal 8 bytes). \n
   Limitation: It is not possible to send 8 data bytes (9 byte TP message) 
   if the last byte is FF (only command the byte + 7 data bytes are sent in this case)

   \param[in]  \wp{u8Instance, iso_u8}
               Identifier of the client instance
   \param[in]  \wp{u8Cmd, iso_u8}
                Proprietary command - Range: 96u - 127u
   \param[in]  \wpp{pau8Data,  const #iso_u8[]}
               Pointer to the command data (without the command byte u8Cmd)
   \param[in]  \wp{u8DataSize, iso_u8}
               Size of the command data array in bytes - Range: 0u - 255u 
   \retval     iso_s16
               - #E_NO_ERR          - OK
               - #E_RANGE           - Command not valid
               - #E_OVERFLOW        - buffer overflow
               - #E_NOACT           - Command not possible in current state
               - #E_NO_INSTANCE     - No VT client available
*/
ISO_CLIENT_API
iso_s16 IsoVtcCmd_Proprietary(iso_u8 u8Instance, iso_u8 u8Cmd, const iso_u8 pau8Data[], iso_u8 u8DataSize);

/** @} */ /* END vtFcmdmsg */


/* ********************************* IsoAux.c  *************************************** */
/** \addtogroup vtc_aux 
   \brief Defines and API functions for auxiliary input and function handling
@{
*/

#ifdef DOXYGEN
    /*! \def ISO_AUXFUNC_SINGLEASSIGN_CHECK  
        \brief  Add the define #ISO_AUXFUNC_SINGLEASSIGN_CHECK to IsoConf.h to enable the 
        aux function single assignment check.
        \details
        If enabled, the ECU driver validates assignments to aux functions to reject 
        invalid assignments with it's own single assignment functions.
    */
    #define ISO_AUXFUNC_SINGLEASSIGN_CHECK    /* enable single assignment check */
#endif

#if defined(ISO_VTC_AUX_N)

/* ************************************************************************ */
/** \name Functions for VT Client Auxiliary function support 
@{
*/
/* **************************************************************************************** */
/*! 
    \brief Set preferred assignment callback function.

   \param[in]   \wp{u8Instance, iso_u8}
                 Identifier of the client instance
    \param[in]  \wp{pfnCallbackFunction, ISOVT_CbAuxPrefAssignment_t}
                Pointer to the callback function.
    \retval iso_s16
                - E_NO_ERR
                - E_NO_INSTANCE
    The function should be called after IsoVtcCreateInstance() to set the preferred assignment callback function.
    The VT client will call this function every time before sending the preferred assignment to the VT.
    \note Deprecated: Use IsoVtcCreateInstance() to provide the callback function
*/
ISO_DEPRECATED
ISO_CLIENT_API
iso_s16 IsoVtcAuxPrefAssignmentCbSet( iso_u8 u8Instance, ISOVT_CbAuxPrefAssignment_t pfnCallbackFunction );

/* **************************************************************************************** */
/*! 
    \brief The function triggers the sending of the preferred assignment to the VT.

    Before sending the preferred assignment the callback function,
    that was set with IsoAuxPrefAssignmentCbSet(), is called to get the 
    preferred assignments from the application.

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
    \retval iso_s16
                - E_NO_ERR  - preferred assignment message is triggered to be send
                - E_NOACT   - triggering not possible
                - E_NO_INSTANCE
*/
ISO_CLIENT_API
iso_s16 IsoVtcAuxPrefAssignmentTrigger( iso_u8 u8Instance );

/*****************************************************************************/
/*!
   \brief        Function for application in order to read assignment and store it

   \param[in]    \wp{u8Instance, iso_u8}
                  Identifier of the client instance
   \param[in]    \wp{asAuxAss, VT_AUXAPP_T[]}
                  Pointer to array of auxiliary assignments
   \param[in]    \wp{riNumberOfFunctions, iso_s16*}
                  Pointer to number of assignments (return value of driver)
   \retval      iso_s16
                 - E_NO_ERR
                 - E_RANGE
                 - E_NO_INSTANCE
   \note  \par
   - V8.01: Use bFuncAttribute instead of eAuxType as Function attribute type
*/
ISO_CLIENT_API
iso_s16 IsoVtcAuxAssignmentRead( iso_u8 u8Instance, VT_AUXAPP_T asAuxAss[], iso_s16* riNumberOfFunctions );

/** @} */
#endif /* defined(ISO_VTC_AUX_N) */

/* ************************************************************************ */
/** \name Functions for implementation of Auxiliary Input Unit devices
@{
*/
#if defined(ISO_VTC_AUX_INP_N) 

/* ************************************************************************ */
/*!
   \brief      Creates a auxiliary input device VT client instance
               with the given model identification code.

   \param[in]  \wp{s16CfHandleMaster, iso_s16}
                  CF handle of the auxiliary input device
   \param[in]    \wp{u16ModelIdentCode, iso_u16}
                  Model identification code
   \param[in]  \wpp{userParam, const #ISO_USER_PARAM_T}
                  User parameter value for the callback function calls. \n
                  Use #ISO_USER_PARAM_DEFAULT if not used/needed.
   \param[in]  \wp{pfVTStatusCb, ISOVT_CbStatus_t}
                  Pointer to callback function which is called in case of opening a new data, alarm
                  or window mask, or of
                   - Parameter rqInfo is set to ISO_TRUE, if the working set is active.
                   - Parameter rwPage contains the object ID of the open mask, or NULL object ID if rqInfo is ISO_FALSE.
   \param[in]  \wp{pfVtMsgRecCb, ISOVT_CbMsg_t}
                  Pointer to callback function which is called in case of activation messages
                  and command responses to the user application. 
                  See #ISOVT_MSG_STA_T for more information.
   \param[in]  \wp{pfVtConnEvCb, ISOVT_CbConnectionEv_t}
                  Pointer to the connection event callback function
                  or NULL pointer if not used.
   \param[in]  \wpp{pau8NamePreferredVT, const #ISO_CF_NAME_T*}
                  Pointer to NAME of preferred VT (only needed for AUX input type 1 (VT version 2))
   \param[in]  \wp{u8BootTimePreferredVT, iso_u8}
                  Boot time of preferred VT in seconds \n
                  (Range 0 - 254; if 0xFF for not available ISO_WAITVT_SEC will be used)
   \retval     iso_u8
                - VT client instance identification number
                - #ISO_INSTANCE_INVALID if there is no instance free
   \par Hints:
         - It is only possible to create one auxiliary input device for a given CF.
           If you call IsoVtcCreateAuxInputDevice() all other VT client instances of this CF will be deleted,
           before the auxiliary input instance is created.
         - Preferred VT: During Login the driver waits a boot time for this VT.
           For auxiliary type 2 input device the parameter is ignored and the client will connect to the primary VT.
*/
ISO_CLIENT_API
iso_u8 IsoVtcCreateAuxInputDevice( iso_s16 s16CfHandleMaster,
                     iso_u16 u16ModelIdentCode,
                     const ISO_USER_PARAM_T userParam,
                     ISOVT_CbStatus_t pfVTStatusCb,
                     ISOVT_CbMsg_t pfVtMsgRecCb,
                     ISOVT_CbConnectionEv_t pfVtConnEvCb,
                     const ISO_CF_NAME_T* pau8NamePreferredVT,
                     iso_u8 u8BootTimePreferredVT );

/***************************************************************************************/
/*!
   \brief         Sending an auxiliary input status message on the bus ( VT version > 2 )

   \param[in]    \wp{u8Instance, iso_u8}
                  Identifier of the client instance
   \param[in]    \wp{iInpNr, iso_s16}
                  Number of auxiliary array - corresponds with the order in the pool \n
                  that means first aux input in pool is iInpNr = 0 etc.
   \param[in]    \wp{Val1_u16, iso_u16}
                  New value for this input
   \param[in]    \wp{Val2_u16, iso_u16}
                  Second new value for this input
   \retval        iso_s16
                  - E_NO_ERR
                  - E_NO_INSTANCE
                  - E_OVERFLOW on send FIFO full
                  - E_COM on bus-off
   \note  \par
      - This function is only necessary for the implementation of Auxiliary Input Units.
      - Supported auxiliary types: 0, 1, 2, 3, 4, 6, 11, 12, 13 see VTAUXTYP_e
      - While pool scanning vtc_pool_aux_input_type_2 (see ISOVT_FUNC_e) can be used for the mapping of objectID and iInpNr
      - Alternativ this can be done with the function IsoAuxInputIndexToObjId()
*/
ISO_CLIENT_API
iso_s16 IsoVtcAuxInputStatus2 ( iso_u8 u8Instance, iso_s16 iInpNr, iso_u16 Val1_u16, iso_u16 Val2_u16 );

/* ************************************************************************ */
/*!
   \brief        Helper function to get the array index for a given input object ID

   \param[in]    \wp{u8Instance, iso_u8}
                  Identifier of the client instance
   \param[in]    \wp{u16ObjIDInput, iso_u16}
                   Pool object ID of the input 
   \retval        iso_s16
                   - >= 0: array index
                   - < 0: Error code
   \par
           This function is only for the implementation of Auxiliary Input Units.
*/
ISO_CLIENT_API
iso_s16 IsoVtcAuxInputIndexToObjId ( iso_u8 u8Instance, iso_u16 u16ObjIDInput);

/* ************************************************************************ */
/*!
   \brief       Manually disable of an auxiliary input

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \param[in]  \wp{u16AuxInputObjID, iso_u16}
                Auxiliary input object ID     
   \retval     iso_s16
   - #E_NO_ERR          - OK
   - #E_NO_INSTANCE     - Aux input not found
*/
ISO_CLIENT_API
iso_s16 IsoVtcAuxInput_SetDisable(iso_u8 u8Instance, iso_u16 u16AuxInputObjID);

#endif /* defined(ISO_VTC_AUX_INP_N) */

#if defined(ISO_VTC_AUX_INP_O) 

/* ************************************************************************ */
/*!
   \brief         Sending an auxiliary input status message on the bus ( VT version <= 2 )

   \param[in]    \wp{u8Instance, iso_u8}
                  Identifier of the client instance
   \param[in]    \wp{iInpNr, iso_s16}
                  Number of auxiliary array - corresponds with the order in the pool \n
                  that means first aux input in pool is iInpNr = 0 etc.
   \param[in]    \wp{Val1_u16, iso_u16}
                   New value for this input
   \retval        iso_s16
                   - #E_NO_ERR
                   - #E_NO_INSTANCE
                   - #E_OVERFLOW on send FIFO full
                   - #E_COM on bus-off
   \note \par
           This function is only necessary for the implementation of Auxiliary Input Units.
*/
ISO_CLIENT_API
iso_s16 IsoVtcAuxInputStatus ( iso_u8 u8Instance, iso_s16 iInpNr, iso_u16 Val1_u16 );

#endif /* defined(ISO_VTC_AUX_INP_O)  */
/** @} */

#if defined(ISO_VTC_AUX_N) || defined(ISO_VTC_AUX_INP_N)
#ifdef ISO_VTC_UT3
/* ************************************************************************ */
/** \name Auxiliary Capabilities request
@{
*/
/* ************************************************************************ */
/*!
   \brief      Auxiliary Capabilities request ( VT version 5 and later )

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{u8RequestType, iso_u8}
                Capabilities for: 0 = Aux Input Unit, 1 = Aux Function Unit
   \retval     iso_s16
                - #E_NO_ERR          - OK
                - #E_OVERFLOW        - buffer overflow
                - #E_NO_INSTANCE     - No VT client available
   \note  \par
   - Every function call causes the sending of this command on the bus.
     Danger of buffer overflow and high bus load !
   - Attention: Correct WS instance must be set ( Calling IsoWsSetMaskInst() !)
*/
ISO_CLIENT_API
iso_s16 IsoVtcReq_AuxCapabilities(iso_u8 u8Instance, iso_u8 u8RequestType);

/** @} */
#endif /* ISO_VTC_UT3 */
#endif /* defined(ISO_VTC_AUX_N) || defined(ISO_VTC_AUX_INP_N) */

/** @} */ /* END aux */


/* ********************************* IsoAlarm.c  *************************************** */
/** \addtogroup vtc_ala 
   \brief Defines and API functions for alarm mask handling (disabled by default)
   \details Can be enabled with the define #ISO_VTC_ENABLE_ALARM. 
   \note
   Deprecated module: Can only be used for VT clients that do not have more than one MASK instance.  
@{
*/

#define ISOALARMPRIO_LIFE_EM    (0x00U)      /**< Alarm priority - high, operator in danger...  */
#define ISOALARMPRIO_PROCESS_EM (0x01U)      /**< Alarm priority - medium, normal alarm */
#define ISOALARMPRIO_LOW        (0x02U)      /**< Alarm priority - low, information only */

/* Alarm-Features */
#define AL_VISIBLE              (0x01U)      /**< \brief Alarms are shown on terminal */
#define AL_STORAGE              (0x02U)      /**< \brief Alarms are entried in non-erasable memory */
#define AL_TIMECONTROLLED       (0x04U)      /**< \brief Time controlled alarms */
#define AL_INTERLOCK            (0x08U)      /**< \brief Interlocking - alarm can be called only one time */
#define AL_QUITofAPPLIC         (0x10U)      /**< \brief Quit of application necessary for deleting alarm */
#define AL_BROADCAST            (0x20U)      /**< \brief Send as broadcast to GLOBAL ADDRESS (Unimog) */


/** \brief
Enum for alarm commands
*/
typedef enum
{
   AlEngage,                 /**< Alarm engaging */
   AlDisengage,              /**< Alarm disengaging */
   AlQuitTest,               /**< Testing if command -AlQuitofApplication- have already set */
   AlQuitofApplication,      /**< see feature AL_QUITofAPPLIC, after quit of VT an application quit */
                             /**< is necessary */
   AlInterlockDisengage,     /**< Possibility for re-activation interlocked alarms */
   AlDelete                  /**< Alarm is deleted */
} ISOAL_CMD_e;

/** \brief
Administration struct for ISO alarms
*/
typedef struct 
{
   iso_u32    dwIdentity;     /**< 16bit: ProjectID | 16bit: AlarmID */
   iso_u8     bFeature;       /**< Properties of an alarm - e.g. AL_QUITofAPPLIC */
   iso_u8     bAlStatus;      /**< Status corresponding features */
   iso_u8     bPriority;      /**< See *.h */
   iso_s32    lTimeStamp;     /**< Time stamp for e.g. broadcast */
   iso_s16    eState;         /**< State machine */
} ISOALARM_T, *ISOALARM_t;

#ifdef ISO_VTC_ALARM
/******************************************************************************/
/*!
   \brief       Initialisation of an alarm object

   This function initializes an alarm object. Every alarm object is associated
   with an alarm mask. The alarm module supports the ISO11783 alarm behavior.

   \param[in]    \wp{rpsIsoAlarm, ISOALARM_t}
                     Pointer to alarm structure provided by application
   \param[in]    \wp{rbPriority, iso_u8}
                     Alarm priority \n
                     Range: ISOALARMPRIO_LIFE_EM (high), ISOALARMPRIO_PROCESS_EM (low)
   \param[in]    \wp{s16CfHandleMaster, iso_s16}
                     CF handle of Working Set Master of this alarm
   \param[in]    \wp{rwAlarmID, iso_u16}
                     Object ID of corresponding alarm mask
   \param[in]    \wp{rbFeatures, iso_u8}
                     Features of this alarm
                      - AL_VISIBLE - Not supported of ISO11783
                      - AL_STORAGE - Not supported of ISO11783
                      - AL_TIMECONTROLLED - Not supported of ISO11783
                      - AL_INTERLOCK - Alarm is interlocked that means second call don't release it
                      - AL_QUITofAPPLIC - also app. must confirm the acknowledge of VT for deleting
                      - AL_BROADCAST - Not supported of ISO11783
*/
ISO_CLIENT_API
void  IsoAlarmObjInit ( ISOALARM_t rpsIsoAlarm,       iso_u8  rbPriority,
                        iso_s16 s16CfHandleMaster,    iso_u16 rwAlarmID,
                        iso_u8 rbFeatures
                     );

/*****************************************************************************/
/*!
   \brief      User interface function to engage, disengage, ... alarms

   This function is used to control an alarm. It can engaged, disengaged, checked
   if VT has acknowledged it, setting the Quit of application or disengage the
   interlock.

   \param[in]    \wp{rpsIsoAlarm, ISOALARM_t}
                       Pointer to controlled alarm
   \param[in]    \wp{reCommand, ISOAL_CMD_e}
                       Control command
                        - AlEngage - an alarm is engaged -> Alarm mask on VT
                        - AlDisengage - an alarm is disengaged (->manual Time control )
                        - AlQuitTest - if an alarm has the feature AL_QUITofAPPLIC the appl.
                        must confirm the acknowledge. AlQuitTest checks if the alarm is
                        acknowledged of VT operator. \n
                        - AlQuitofApplication - if an engaged alarm with feature AL_QUITofAPPLIC
                        ia acknowledged of VT then the appl. must call this control. for
                        deleting the alarm
                        - AlInterlockDisengage - for reactivation of interlocked alarms
   \retval              iso_s16
                        - E_NO_ERR     - OK
                        - E_OVERFLOW   - Alarm buffer is full
                        - E_BUSY       - Repeated calling of an interlocked alarm
                        - E_WARN       - Alarm not found in the alarm list
                        - 1            - Quit of application has been OK (see features)
                        - 2            - Alarm is acknowledged of VT and can be quitted
   \note  \par
          - An alarm can only released if it is not interlocked.
          - Time control can realised manual with disengaging the alarm.
          - With this concept (every alarm has an alarm mask)
            its necessary to create an alarm mask for every alarm.
            Alternatively its possible to change the textual/graphical objects of one
            alarm mask. In this case there is only one alarm mask necessary.
*/
ISO_CLIENT_API
iso_s16  IsoAlarmCmd ( ISOALARM_t rpsIsoAlarm, ISOAL_CMD_e reCommand );

/****************************************************************************************/
/*!
   \brief      User interface function to read number of stored alarm

   This function reads the actual active number of alarms.

   \retval     iso_u16
                Number of alarms which are active
   \note  \par
         e. g. it is possible to avoid unnecessary cyclic calls for controlling the alarms.
*/
ISO_CLIENT_API
iso_u16  IsoAlarmGetNum( void );

/********************************************************************************************/
/*!
   \brief       Setting an "return data mask" before application quit of an alarm

   This function sets the data mask which will appear after application quit or disengaging
   of an alarm.

   \param[in]    \wp{DmObjId_cu16, iso_u16}
                    Object ID of a data mask object
   \note  \par
         In normal behaviour the driver sends "change active mask" of the data mask which
         is referenced in the working set object (default data mask). The reason is when sending
         an alarm without open the pool on VT there is no return mask defined. This function
*/
ISO_CLIENT_API
void IsoAlarmSetReturnObjId( iso_u16 DmObjId_cu16 );

#endif /* ISO_VTC_ALARM */
/** @} */ /* END ala */

/* ********************************* IsoPool.c  *************************************** */
/** \addtogroup poolmani 
   \brief Defines and API functions for pool transfer and manipulation
@{
*/

   #define  ISO_FACTOR_ONE            (10000U)   /**< Scaling factor - 1 - */
   #define  ISO_POOLDATA_READY        (1UL)      /**< Direct transfer: Requested pool objects are ready to upload */
#ifndef ISO_POOLDATA_WAIT_TIME
   #define  ISO_POOLDATA_WAIT_TIME    (0U)       /**< Direct transfer: Maximum wait time in milliseconds to use single (E)TP for pool upload  */
#endif

#ifdef DOXYGEN
    /*! \def ISO_VTC_POOLBUFFERSIZE  
        \brief  Add the define #ISO_VTC_POOLBUFFERSIZE to IsoConf.h to set the size of the VTC pool buffer.
        \details The define is predefined with 10000UL. 
    */
    #define ISO_VTC_POOLBUFFERSIZE  (10000UL)

    /*! \def ISO_POOL_DIRECT_LOAD  
        \brief  Add the define #ISO_POOL_DIRECT_LOAD to IsoConf.h to enable the "Direct Pool Transfer". 
        \details The define is needed to use IsoVtcPoolInitDirectTransfer(). 
    */
    #define ISO_POOL_DIRECT_LOAD  

    /*! \def ISO_VTPO_TP_BUFFER_SIZE
         \brief Size of the direct pool transfer (E)TP data iso_u8 buffer. 
         \details
         You can use iso_CoreTPRepeatSet(x) to set the number of TP data packets which should be send in one loop. \n
         The TP pool buffer size ISO_VTPO_TP_BUFFER_SIZE should be greater or equal (x*7u)+3u to use the full TP transfer speed. \n
         You can use IsoPoolSetDTRepeatRate(y) to increase the call frequency PoolDoDirectLoadPool() in state TPBuffScanSeg, \n
         to make sure that the TP pool buffer can be filled in one loop. \n
            
    */
    #define ISO_VTPO_TP_BUFFER_SIZE  (16u)    

    /*! \def ISO_VTPO_OBJ_FIELD_SIZE
         \brief Size of the direct pool transfer object field array for storing the needed field manipulations 
    */
    #define ISO_VTPO_OBJ_FIELD_SIZE  (6u)      

    /*! \def ISO_EXTERNAL_POOLBUFFER  
        \brief  Add the define #ISO_EXTERNAL_POOLBUFFER to IsoConf.h to enable the external pool RAM buffer functionality.
        \details The define is needed to replace the internal buffer with an external pool RAM buffer. \n
        The external buffer must have the size defined by ISO_VTC_POOLBUFFERSIZE. \n
        The pointer to this buffer must be set with IsoPoolSetBuffer(). 
    */
    #define ISO_EXTERNAL_POOLBUFFER

#endif

   /** \brief
   Enum for read function of special pool information
   */
   typedef enum
   {
       PoolROMStartAddress,       /**< Start address of pool in FLASH */
       PoolROMSize,               /**< Size of original pool */
       PoolRAMStartAddress,       /**< Start address of pool in RAM */
       PoolRAMSize,               /**< Pool size, only valid after download !!! */
       ObjIDWorkingSet,           /**< Object identifier of working set */
       ObjIDFirstDataMask,        /**< First data mask */
       PointerVersionString,      /**< Pointer to the version string */
       PoolGraphicType,           /**< Graphic type of pool - see IsoPoolInit () */
       PoolDataMaskScalFaktor,    /**< Scaling factor of data mask */
       PoolSoftKeyMaskScalFaktor, /**< Scaling factor of soft key mask */
       BufferUsed                 /**< Actual Bytes in pool buffer */
   } ISOPOOLINFO_e;

   /** \brief
   Enum of pool manipulation modes
   */
   typedef enum
   {
       NoScaling = 0,             /**< Object or object range is not scaled */
       Scaling,                   /**< Object or object range is scaled */
       Centering,                 /**< Object or object range is centered */
       NotLoad,                   /**< Object or object range is not loaded during pool transport */
       Proprietary,               /**< Object or object range is manipulated of a proriertary manipulation module */
       LoadMoveID,                /**< Object or object range is loaded to new destination address */
       LoadCopyID,                /**< Object or object range is copied to destination address */
       ColourReduction,           /**< Colour depth of object or object range is reduced */
       AuxToV2,                   /**< Auxiliary object or object range is transformed into version 2 */
       LastMode
   } ISOPOOLMANIMODE_e;

   /** \brief Enum of colour depth of pool */
   typedef enum
   {
       monochrome   = 0,          /**< Monochrome */
       colour_16    = 1,          /**< 16 colour */
       colour_256   = 2,          /**< 256 colour */
       colour_undef = 3
   } ISOGRAPH_TYPE_e;

   /** \brief Enum of pool state machine */
   typedef enum
   {
      PoolLazy = 0,             /**< - Poolservice inactive  */
      PoolLoadInit = 1,         /**< - Initialisation of pool service in order to scan or transport */
      PoolLoadSeg = 2,          /**< 
                                     - Segmented poolservice: Loading objects in buffer 
                                     - Direct transfer: Requesting next pool objects */
      PoolScanSeg = 3,          /**< 
                                     - Segmented poolservice: Scanning objects in buffer 
                                     - Direct transfer: Scanning requested objects */
      PoolScanning = 4,         /**< 
                                     - Scanning for "normal" flashtransfer 
                                     - Direct Transfer: Start pool scanning */
      PoolWaitTransfer = 5,     /**< - Wait till VT client decide if primary pool transfer is necessary */
      PoolGetMemory = 6,        /**< - Sending and receiving GetMemory */
      ETPBuffLoad = 7,          /**< 
                                     - "normal" flashtransfer: Manipulating objects and storing in ETP buffer 
                                     - Direct Transfer: start direct transfer */
      ETPBuffLoadSeg = 8,       /**< 
                                     - Segmented poolservice: Loading pooldata in buffer 
                                     - Direct transfer: Requesting next pool objects */
      ETPBuffScanSeg = 9,       /**< 
                                     - Segmented poolservice: Scanning pooldata in buffer
                                     - Direct transfer: Scanning and sending requested objects */
      ETPBuffManiSeg = 10,      /**< - Segmented poolservice: Manipulating pooldata in buffer */
      ETPBlockManipulated = 11, /**< 
                                     - Decide before ETPstart if last of any block 
                                     - Direct transfer: not used */
      ETPBuffLoadSegAfterETP = 12, /**< 
                                     - Segmented poolservice: Copiing rest pool data at begin of buffer
                                     - Direct transfer: not used */
      ETP_start = 13,           /**< 
                                     - Starting ETP transfer 
                                     - Direct transfer: not used */
      ETP_Trans_running = 14,   /**< - Wainting till ETP transfer is finished */
      ETP_finished = 15,        /**< - Decide if further transfer necessary or finish pool service */
      PoolServiceInUse = 16     /**< - pool service is reserved by a client instance */
   } ISOPOOLSM_e;

   /** \brief Enum for pool service callback */
   typedef enum
   {
       PoolBlockRequest,      /**< Driver request pool data ( segmented pool transfer and TP block size pool transfer) */
       PoolFirstBlockRequest, /**< Driver request first pool data (only TP block size pool transfer: "(re)open file") */
       PoolGetMemoryFailed,   /**< Informs that VT has not enough memory for the pool */
       PoolStatemachine,      /**< Gives actual state of pool state machine to application */
       PoolFileCloseRequest,  /**< Gives the application the possibility to close the pool ( segmented pool transfer and data block size pool transfer) */
       PoolObjectRequest      /**< Driver request some complete objects ( direct pool transfer ) */
   } ISOPOOLCBREQ_e;

   /** \brief Pool transfer modes */
   typedef enum
   {
      PoolTransferRaw = 0,          /**< transfer original flash pool without manipulations */
      PoolTransferFlash = 1,        /**< transfer flash pool with pool manipulations  */
      PoolTransferSeqmented = 2,    /**< use segmented pool transfer functionality  */
      PoolTransferDirectLoad = 3,   /**< use direct load pool transfer functionality */
      PoolTransferDataBlocks = 4    /**< use TP size data block pool transfer functionality */
   } ISOVT_POOL_TRANSFER_MODE_e;

   /** \brief Object pool upload callback function parameter */
   typedef struct
   {
       ISOPOOLCBREQ_e      ePoolCtrl;           /**< \brief Command/Kind of callback call */
       /* for command PoolBlockRequest */
       iso_u8 HUGE_C*      pbAddress;           /**< \brief Address parameter
                                                - Data block size pool transfer - PoolBlockRequest and PoolFirstBlockRequest:
                                                  - Address to the pool buffer where to store the next data 
                                                - Segmented pool transfer - PoolBlockRequest:
                                                  - Address for pool buffer 
                                                - Direct pool transfer - PoolObjectRequest:
                                                  - Start address of the current pool objects buffer. \n
                                                    Must be set from the application in the PoolObjectRequest callback.
                                                - Else: not valid */
       iso_u32            u32BlockSizeReq;      /**<  \brief Block size request parameter
                                                - Data block size pool transfer - PoolBlockRequest and PoolFirstBlockRequest:
                                                  - Requested data block size
                                                - Segmented pool transfer - PoolBlockRequest:
                                                  - Requested data block size 
                                                - Direct pool transfer - PoolObjectRequest:
                                                  - Must be set to #ISO_POOLDATA_READY, if buffer is ready to upload. 
                                                - Else: not valid */
       iso_u32            u32BlockSizeLoad;     /**<  \brief Block size loaded parameter
                                                - Data block size pool transfer - PoolBlockRequest and PoolFirstBlockRequest:
                                                  - App -> Driver: really load/copied bytes \n
                                                    0UL - u32BlockSizeReq: Number of provided/copied data bytes. \n
                                                    Set u32BlockSizeLoad to a value greater than the requested number of bytes, \n
                                                    to signal "end of the object pool" (u32BlockSizeReq > u32BlockSizeReq := EOF pool).
                                                  - Driver -> App:
                                                    Size of already loaded pool data 
                                                - Segmented pool transfer - PoolBlockRequest:
                                                  - App -> Driver: really load bytes \n
                                                    Can be set 0UL, if it is not possible to provide the requested number of bytes in this cycle. \n
                                                    (In this case the pool service will retry to get this block of data in the next cycle.) \n
                                                    Setting u32BlockSizeLoad to an other value as zero or the requested number of bytes, 
                                                    will be treated as end of the object pool.
                                                - Direct pool transfer - PoolObjectRequest:
                                                  - Driver: Request counter starting with 1.
                                                  - App: Size of the buffer that ready to upload
                                                  - App: Set the size to 0 and u32BlockSizeReq to #ISO_POOLDATA_READY, 
                                                    to indicate that no more objects are to send. 
                                                - Else: not valid */
       /* for command PoolStatemachine */
       ISOPOOLSM_e                  ePoolServState;      /**< \brief Delivers state of pool service state machine */
       ISOVT_POOL_TRANSFER_MODE_e   ePoolTransferMode;   /**< \brief Used pool transfer mode (set by the pool init function)  */
       ISO_USER_PARAM_T             userParam;           /**< \brief User parameter of this VT client */
       iso_u8                       u8Instance;          /**< \brief Client instance number (connection handle) */
   } ISOPOOLCTRL_T;
   typedef ISOPOOLCTRL_T *ISOPOOLCTRL_t;

   /** \brief Callback function pointer for driver requesting the pool data / objects from the application. 
       \details The callback function is used from the segmented and the direct pool transfer 
                to get the source location for the next pool data segment or the next complete objects 
                from the application.
       \param[in,out]   \wp{psPoolCtrl,  ISOPOOLCTRL_T* }
                            Pointer to the ISOPOOLCTRL_T object.
   */
   typedef void (*ISO_POOL_CALLBACK_t)( ISOPOOLCTRL_T* psPoolCtrl );

   /* ************************************************************************ */
   /*!
      \brief Type definition for pool object information.
      \details Used as function parameter for the callback functions
      #iso_fnCbPoolObject_t and #ISOVT_CbPoolSecondaryAdaptation_t
   */
   typedef struct
   {
      OBJTYP_e    eObjectType;         /**< \brief The extracted object type. */
      iso_u16     u16ObjectId;         /**< \brief The extracted object ID. */
      ISOPOOLSM_e eState;              /**< \brief The current state of the pool service. */
      iso_u8      u8Instance;          /**< \brief Identifier of the client instance */
      ISO_USER_PARAM_T userParam;      /**< \brief User parameter of this VT client. */
   } ISOVT_PoolObj_Info_Ts;

   /* ************************************************************************ */
   /** \brief Callback function pointer to return an pool object to the application. 
       \details The callback function is used from the pool transfer 
                to give back the current pool object to the application. \n
                The callback function can be set with IsoPoolObjectCbSet().
       \param[in]     \wpp{ psObjectInfo, const #ISOVT_PoolObj_Info_Ts* }
                        Pointer to the object information structure.
       \param[in]   \wpp{pau8Object, const #iso_u8 HUGE_C[] }
                        Pointer to the object data iso_u8 array.
   */
   typedef  void (*iso_fnCbPoolObject_t)(const ISOVT_PoolObj_Info_Ts* psObjectInfo, const iso_u8 HUGE_C pau8Object[]);

/* Function prototyps */
/* **************************************************************************************** */
/*!
   \brief       Initializes the object pool transfer to the VT
   
   This function is used to set the object pool of a CF instance. 
   The given pool is scanned and if needed transfered to the connected VT.
   This function must called after knowing VT characteristics!

   \param[in]  \wp{u8Instance, iso_u8}
                  Identifier of the client instance
   \param[in]  \wp{au8VersionString,  iso_u8[] }
                  Pointer to "Pool Version String" \n
                  Range: exact 7 characters for WS versions less than 5 otherwise exact 32 characters
   \param[in]  \wp{u8DesignatorWidth, iso_u8}
                  Soft key designator width - minimum == 60 \n
                  In order to guarantee proper functionality of pool manipulation
                  this value should be 60
   \param[in]  \wp{u8DesignatorHeight, iso_u8}
                  Soft key designator height - minimum == 32
                  In order to guarantee proper functionality  of pool manipulation
                  this value should be 32
   \param[in]  \wp{u16MaskSize, iso_u16}
                  Data and Alarm Mask size of this pool \n
                  Range: Minimum 200 - Maximum (undefined depends on physical VTs)
   \param[in]  \wp{eTransferMode, ISOVT_POOL_TRANSFER_MODE_e}
                  Transfer mode which should be used for the object pool upload
   \param[in]  \wpp{au8PoolData, const #iso_u8 HUGE_C[]}
                  Pointer to pool data in flash \n
                  Needed only for #PoolTransferFlash (or PoolTransferRaw) else not needed (use NULL pointer)
   \param[in]  \wp{u32PoolSize,  iso_u32}
                  Size of the object pool in bytes. Needed only for #PoolTransferFlash (or PoolTransferRaw) \n
                  Range: 1 - 117440512 or 0UL if not used
   \param[in]  \wp{u32BufferOffset, iso_u32}
                  Used only by #PoolTransferSeqmented and #PoolTransferDataBlocks
                  Buffer offset into Pool buffer -> Start address for load objects \n
                  Details see help - VT client/VT Pool Manipulation/..
   \param[in]  \wp{u16MaxTime, iso_u16}
                  Used only by #PoolTransferDirectLoad \n
                  Maximum time in milliseconds the application needed to load the next pool objects for the driver. \n
                  - 0: The driver has direct access to the pool data memory
                  - else: The application copies the data in a memory zone where the driver has direct access. \n
                    Range: Minimum 0 - Maximum (undefined depends on the ECU hardware)
   \param[in]  \wp{pfPoolLoadCb, ISO_POOL_CALLBACK_t }
                  Callback function pointer for the object pool data requests. \n
                  Needed for PoolTransferSeqmented, PoolTransferDirectLoad and PoolTransferDataBlocks

   \retval     iso_s16
               - #E_NO_ERR on success
               - #E_NO_INSTANCE if the instance identifier is not valid
               - #E_RANGE if one or more parameters are not valid
               - #E_CONFIG if the pool configuration or version label is not valid
               - #E_NOACT  if not compiled to use this mode
*/
ISO_CLIENT_API
iso_s16 IsoVtcPoolLoad(iso_u8 u8Instance, const iso_u8 au8VersionString[],
   iso_u8 u8DesignatorWidth, iso_u8 u8DesignatorHeight, iso_u16 u16MaskSize,
   ISOVT_POOL_TRANSFER_MODE_e eTransferMode, const iso_u8 HUGE_C au8PoolData[], iso_u32 u32PoolSize,
   iso_u32 u32BufferOffset, iso_u16 u16MaxTime, ISO_POOL_CALLBACK_t pfPoolLoadCb);

/* **************************************************************************************** */
/*!
   \brief           Function for reloading object(s) after standard pool transport

   This function initializes a pool reload and starts execution if return value is true.

   \param[in]  \wp{u8Instance, iso_u8}
                  Identifier of the client instance
   \param[in]  \wp{eTransferMode, ISOVT_POOL_TRANSFER_MODE_e}
                  Transfer mode which should be used for the object pool upload
   \param[in]  \wpp{au8PoolData, const #iso_u8 HUGE_C[]}
                  Pointer to pool data in flash \n
                  Needed only for #PoolTransferFlash (or PoolTransferRaw) else not needed (use NULL pointer)
   \param[in]  \wp{u32PoolSize,  iso_u32}
                  Size of the object pool in bytes. Needed only for #PoolTransferFlash (or PoolTransferRaw) \n
                  Range: 1 - 117440512 or 0UL if not used
   \param[in]  \wp{pfPoolLoadCb, ISO_POOL_CALLBACK_t }
                  Callback function pointer for the object pool data requests. \n
                  Needed for PoolTransferSeqmented, PoolTransferDirectLoad and PoolTransferDataBlocks. \n
                  Can be the NULL pointer if already set with IsoVtcPoolLoad() or if the transfer mode is PoolTransferFlash or PoolTransferRaw.

   \retval  iso_bool      
            - ISO_FALSE - Another pool transport is running (or parameter not valid)
            - ISO_TRUE - Pool reload is started
   \par
   Example of usage:
   \code
   if (IsoVtcPoolUpdate(u8Instance, PoolTransferDataBlocks, 0, 0UL) ==  ISO_TRUE)
   {
       iso_u16 wSKM_Scal = 0u;
       *** Reload ranges ***
       IsoVtcPoolSetIDRangeMode( u8Instance, 0,       1099,       0,  NotLoad );
       IsoVtcPoolSetIDRangeMode( u8Instance, 1100,    1100,    1002,  LoadMoveID );    1002 = target(start)ID
       IsoVtcPoolSetIDRangeMode( u8Instance, 1101,    39999,      0,  NotLoad );
       IsoVtcPoolSetIDRangeMode( u8Instance, 42001,   65334,      0,  NotLoad );
       *** Manipulating ranges ***
       wSKM_Scal = (iso_u16)IsoVtcPoolReadInfo( u8Instance, PoolSoftKeyMaskScalFaktor );
       IsoVtcPoolSetIDRangeMode( u8Instance, 40012,      40012,    wSKM_Scal,  Centering );
   }
   \endcode
   - Every call of IsoVtcPoolUpdate() with return "ISO_TRUE" releases a object pool transport!
   - Return "ISO_FALSE" means there is another pool transport running - application must repeat calling IsoVtcPoolUpdate()
   - Reloading object ranges shall handled with "NotLoad" in normal pool manipulation
   - LoadMoveID: Offset for all objects in example is 1100 - 1000 = -100

   \par Hint:
   The "Direct Pool Transfer" mode can only be used if enabled  (IsoConf.h define #ISO_POOL_DIRECT_LOAD). 
*/
ISO_CLIENT_API
iso_bool IsoVtcPoolUpdate( iso_u8 u8Instance, ISOVT_POOL_TRANSFER_MODE_e eTransferMode, 
   const iso_u8 HUGE_C au8PoolData[], iso_u32 u32PoolSize, ISO_POOL_CALLBACK_t pfPoolLoadCb);

#ifdef ISO_POOL_DIRECT_LOAD
/* **************************************************************************************** */
/*!
   \brief       Initialisation of the direct pool transfer 

   This function is used instead of IsoVtcPoolInit() to transfer a pool without using the driver internal pool buffer.
   This function must called after knowing VT characteristics!

    \param[in]    \wp{u8Instance, iso_u8}
                        Identifier of the client instance
    \param[in]    \wp{rasVersionString,  iso_u8[] }
                        Pointer to "Pool Version String" \n
                        Range: exact 7 characters for WS versions less than 5 otherwise exact 32 characters
    \param[in]    \wp{rbDesignatorWidth, iso_u8}
                        Soft key designator width - minimum == 60 \n
                        In order to guarantee proper functionality of pool manipulation
                        this value should be 60
    \param[in]    \wp{rbDesignatorHeight, iso_u8}
                        Soft key designator height - minimum == 32
                        In order to guarantee proper functionality  of pool manipulation
                        this value should be 32
    \param[in]    \wp{rwMaskSize, iso_u16}
                        Data and Alarm Mask size of this pool \n
                        Range: Minimum 200 - Maximum (undefined depends on physical VTs)
    \param[in]    \wp{rwMaxTime, iso_u16}
                        Maximum time in milliseconds the application needed to load the next pool objects for the driver. \n
                        - 0: The driver has direct access to the pool data memory
                        - else: The application copies the data in a memory zone where the driver has direct access. \n
                        Range: Minimum 0 - Maximum (undefined depends on the ECU hardware)
    \param[in]    \wp{rpfPoolLoad, ISO_POOL_CALLBACK_t }
                        Callback function pointer for the driver pool object requests.

   \retval              iso_s16
                         - E_NO_ERR
                         - E_NO_INSTANCE
                         - E_RANGE

    \par
    Add the define #ISO_POOL_DIRECT_LOAD to IsoConf.h to enable the "Direct Pool Transfer".
    \note Deprecated: Use IsoVtcPoolLoad()
*/
ISO_DEPRECATED
ISO_CLIENT_API
iso_s16 IsoVtcPoolInitDirectTransfer( iso_u8 u8Instance, const iso_u8 rasVersionString[], 
                           iso_u8   rbDesignatorWidth, iso_u8  rbDesignatorHeight, iso_u16   rwMaskSize,
                           iso_u16   rwMaxTime,         ISO_POOL_CALLBACK_t rpfPoolLoad );

/* ********************************************************************* */
/*!
   \brief   Set the direct load pool transfer repetition value for one loop

   \param[in]    \wp{s16DTSpeed, iso_s16}  
                   Number of cyclic calls in one loop to speed up the transport\n  
                   Range: 1 - about 10 (depends on #ISO_VTPO_TP_BUFFER_SIZE, and the size of the pool objects ..) \n
                   Default: 1         
   \retval       iso_s16                        
                   - #E_NO_ERR on success   
                   - #E_RANGE on s16DTSpeed is not valid                       
   \details    The value is used  as in the state TPBuffScanSeg to loop over up to s16DTSpeed pool objects
               to fill the internal TP pool buffer. The loop is also terminated if the TP pool buffer is full
               or the last object of the current pool data block is processed. \n
               See also #ISO_VTPO_TP_BUFFER_SIZE and IsoVtcPoolInitDirectTransfer().
   \note Deprecated: Use IsoVtcPoolSetDTRepeatRate()
*/
ISO_DEPRECATED
ISO_CLIENT_API
iso_s16 IsoPoolSetDTRepeatRate( iso_s16 s16DTSpeed );

#endif /* ISO_POOL_DIRECT_LOAD */

/* ********************************************************************* */
/*!
   \brief   Set the direct load pool transfer repetition value for one loop

   \param[in]    \wp{s16DTSpeed, iso_s16}
                   Number of cyclic calls in one loop to speed up the transport\n
                   Range: 1 - about 10 (depends on #ISO_VTPO_TP_BUFFER_SIZE, and the size of the pool objects ..) \n
                   Default: 1
   \retval       iso_s16
                   - #E_NO_ERR on success
                   - #E_RANGE on s16DTSpeed is not valid
   \details    The value is used  as in the state TPBuffScanSeg to loop over up to s16DTSpeed pool objects
               to fill the internal TP pool buffer. The loop is also terminated if the TP pool buffer is full
               or the last object of the current pool data block is processed. \n
               See also #ISO_VTPO_TP_BUFFER_SIZE and IsoVtcPoolLoad() mode #PoolTransferDirectLoad.
*/
ISO_CLIENT_API
iso_s16 IsoVtcPoolSetDTRepeatRate(iso_s16 s16DTSpeed);


#if defined(ISO_POOL_BUFFERED_LOAD)

/* **************************************************************************************** */
/*!
   \brief       Initialisation of the object pool for segmented handling

   This function is used instead of IsoPoolInit() in the case that the pool shall
   load out partial of a mass storage e. g. SD-Card.
   This function must called after knowing VT characteristics!

   \param[in]     \wp{u8Instance, iso_u8}
                        Identifier of the client instance
    \param[in]    \wp{rasVersionString,  iso_u8[] }
                        Pointer to "Pool Version String" \n
                        Range: exact 7 characters for WS versions less than 5 otherwise exact 32 characters
    \param[in]    \wp{rdwBuffOffset, iso_u32}
                        BufferOffset to Poolbuffer -> Startaddress for loaded objects \n
                        Details see help - VT client/VT Pool Manipulation/..
    \param[in]    \wp{rwNumberObjects, iso_u16}
                        Number of objects in object pool
    \param[in]    \wp{reGraphicType, ISOGRAPH_TYPE_e}
                        Graphic type of this pool ( monochrome, colour_16, colour_256 )
    \param[in]    \wp{rbDesignatorWidth, iso_u8}
                        Soft key designator width - minimum == 60 \n
                        In order to guarantee proper functionality of pool manipulation
                        this value should be 60
    \param[in]    \wp{rbDesignatorHeight, iso_u8}
                        Soft key designator height - minimum == 32
                        In order to guarantee proper functionality  of pool manipulation
                        this value should be 32
    \param[in]    \wp{rwMaskSize, iso_u16}
                        Data and Alarm Mask size of this pool \n
                        Range: Minimum 200 - Maximum (undefined depends on physical VTs)
    \param[in]    \wp{rpfPoolLoad, ISO_POOL_CALLBACK_t}
                        Callback function for driver requests of pool

   \retval              iso_s16
                         - E_NO_ERR
                         - E_OVERFLOW: Pool RAM Buffer is NULL pointer
                         - E_NO_INSTANCE
                         - E_RANGE: Parameter not valid ( rasVersionString is a NULL pointer)
    \note Deprecated: Use IsoVtcPoolLoad()
*/
ISO_DEPRECATED
ISO_CLIENT_API
iso_s16 IsoVtcPoolInitSegmented( iso_u8 u8Instance,
                           const iso_u8 rasVersionString[],iso_u32 rdwBuffOffset,
                           iso_u16   rwNumberObjects,  ISOGRAPH_TYPE_e reGraphicType,
                           iso_u8   rbDesignatorWidth, iso_u8  rbDesignatorHeight,
                           iso_u16   rwMaskSize,       ISO_POOL_CALLBACK_t rpfPoolLoad );

#endif /* defined(ISO_POOL_BUFFERED_LOAD) */

/* **************************************************************************************** */
/*!
   \brief       Initialisation of the object pool

   All parameters which are necessary for successful pool initialisation.
   This function must called after knowing VT characteristics!

   \param[in]    \wp{u8Instance, iso_u8}
                        Identifier of the client instance
   \param[in]    \wpp{rasVersionString, const #iso_u8[] }
                        Pointer to "Pool Version String" \n
                        Range: exact 7 characters for WS versions less than 5 otherwise exact 32 characters
   \param[in]    \wpp{rpbPoolFirstAddress,  const #iso_u8* HUGE_C}
                        Absolute address of first iso_u8 of this pool
   \param[in]    \wp{rdwPoolSize,  iso_u32 }
                        Not necessary except in combination with IsoVtcPoolTransferFlashPool() \n
                        Range: 1 - 117440512
   \param[in]    \wp{rwNumberObjects, iso_u16 }
                        Number of objects which are transferred ! \n
                        You can use the function IsoVtcGetNumofPoolObjs() for determination of this value \n
                        Range: 0 - 65535
   \param[in]    \wp{reGraphicType,  ISOGRAPH_TYPE_e }
                        Graphic type of this pool ( monochrome, colour_16, colour_256 )
   \param[in]    \wp{rbDesignatorWidth,  iso_u8 }
                        Soft key designator width - minimum == 60 \n
                        In order to guarantee proper functionality of pool manipulation
                        this value should be 60
   \param[in]    \wp{rbDesignatorHeight, iso_u8 }
                        Soft key designator height - minimum == 32
                        In order to guarantee proper functionality  of pool manipulation
                        this value should be 32
   \param[in]    \wp{rwMaskSize,  iso_u16 }
                        Data and Alarm Mask size of this pool \n
                        Range: Minimum 200 - Maximum (undefined depends on physical VTs)

   \retval              iso_s16
                         - E_NO_ERR
                         - E_OVERFLOW: Pool RAM Buffer is NULL pointer
                         - E_NO_INSTANCE
                         - E_RANGE: Parameter not valid 
   \par
   -  see also IsoVtcPoolInitSegmented()
   \note Deprecated: Use IsoVtcPoolLoad()
*/
ISO_DEPRECATED
ISO_CLIENT_API
iso_s16 IsoVtcPoolInit ( iso_u8 u8Instance,
                   const iso_u8 rasVersionString[], const iso_u8 HUGE_C* rpbPoolFirstAddress, iso_u32 rdwPoolSize,
                   iso_u16  rwNumberObjects,           ISOGRAPH_TYPE_e reGraphicType,
                   iso_u8 rbDesignatorWidth,           iso_u8  rbDesignatorHeight,  iso_u16  rwMaskSize   );

/* **************************************************************************************** */
/*!
   \brief       Installing the pool callbackfunction

   This function installs the pool callback function. It is used instead in the case
   when no segmented pool transfer is used and the application wants to receive the
   GetMemory failure info and/or to monitor the pool state machine

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \param[in]  \wp{rpfPoolLoad, ISO_POOL_CALLBACK_t }
                 Callback function
*/
ISO_CLIENT_API
void IsoVtcPoolCbInstall( iso_u8 u8Instance, ISO_POOL_CALLBACK_t rpfPoolLoad );

/* **************************************************************************************** */
/*!
   \brief           Function for reloading object(s) after standard pool transport

   This function initializes a pool reload and starts execution if return value is true.

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \param[in]  \wpp{rpPoolFirstAddress, const #iso_u8* HUGE_C}
                Pointer to pool in flash \n
                Exception: "0" NULL pointer for segmented or direct pool transfer
   \param[in]  \wp{rwNumberObjects,  iso_u16}
                Number of objects to transfer ( including "notload" ) \n
                Exception: 0 for direct pool transfer

   \retval          iso_bool
                     - ISO_FALSE - Another pool transport is running
                     - ISO_TRUE - Pool reload is started
   \par
   Example of usage:
   \code
   if ( IsoVtcPoolReload( u8Instance, 0, 62 ) )
   {
       iso_u16 wSKM_Scal = 0u;
       *** Reload ranges ***
       IsoVtcPoolSetIDRangeMode( u8Instance, 0,       1099,       0,  NotLoad );
       IsoVtcPoolSetIDRangeMode( u8Instance, 1100,    1100,    1002,  LoadMoveID );    1002 = target(start)ID
       IsoVtcPoolSetIDRangeMode( u8Instance, 1101,    39999,      0,  NotLoad );
       IsoVtcPoolSetIDRangeMode( u8Instance, 42001,   65334,      0,  NotLoad );
       *** Manipulating ranges ***
       wSKM_Scal = (iso_u16)IsoVtcPoolReadInfo( u8Instance, PoolSoftKeyMaskScalFaktor );
       IsoVtcPoolSetIDRangeMode( u8Instance, 40012,      40012,    wSKM_Scal,  Centering );
   }
   \endcode
   - Every call of IsoPoolReload( ) with return "ISO_TRUE" releases a object pool transport!
   - Return "ISO_FALSE" means there is another pool transport running - application must repeat
     calling IsoPoolReload()
   - Reloading object ranges shall handled with "NotLoad" in normal pool manipulation
   - LoadMoveID: Offset for all objects in example is 1100 - 1000 = -100

   \par
   You must add the define #ISO_POOL_DIRECT_LOAD to IsoConf.h 
   to enable the "Direct Pool Transfer" mode for this function.
   \note Deprecated : Use IsoVtcPoolUpdate()
*/
ISO_DEPRECATED
ISO_CLIENT_API
iso_bool IsoVtcPoolReload( iso_u8 u8Instance, const iso_u8 HUGE_C* rpPoolFirstAddress, iso_u16  rwNumberObjects );

/* **************************************************************************************** */
/*!
   \brief      Requesting some important and needed values from the pool - see ISOPOOLINFO_e

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \param[in]  \wp{ePoolReading, ISOPOOLINFO_e}
                 Enumeration which includes all value which can be requested
   \code
      - PoolROMSize               - Size of original pool
      - PoolRAMSize               - Pool size, only valid after download !!!
      - ObjIDWorkingSet           - Object identifier of working set
      - ObjIDFirstDataMask        - First data mask
      - PoolGraphicType           - Graphic type of pool - see IsoVtcPoolInit ()
      - PoolDataMaskScalFaktor    - Scaling factor of data mask (after IsoVtcPoolInit() )
      - PoolSoftKeyMaskScalFaktor - Scaling factor of soft key mask (after IsoVtcPoolInit() )
      - BufferUsed                - Number of bytes in pool buffer
   \endcode
   \retval               iso_u32
                          - Wished value
*/
ISO_CLIENT_API
    iso_u32 IsoVtcPoolReadInfo( iso_u8 u8Instance, ISOPOOLINFO_e ePoolReading );

/* **************************************************************************************** */
/*!
   \brief      Requesting a pointer value - see ISOPOOLINFO_e

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \param[in]   \wp{ePoolReading, ISOPOOLINFO_e }
                  Enumeration which includes all value which can be requested

   \code
      - PointerVersionString      - Pointer to the version string
   \endcode
   \retval     const #iso_u8*
               - Pointer to Working set version string
*/
ISO_CLIENT_API
   const iso_u8 * IsoVtcPoolReadPtrLoc( iso_u8 u8Instance, ISOPOOLINFO_e ePoolReading );

/* **************************************************************************************** */
/*!
   \brief      Function in order to transfer pool of FLASH for test purposes

   This function transfer the original pool in non-volatile-memory (normally Flash)
   This can be useful for comparing the work of the pool manipulation with the original data

   \param[in]  \wp{u8Instance, iso_u8}
                  Identifier of the client instance
   \param[in]   \wp{qFlashTransfer, iso_bool}
                  - ISO_TRUE - Transfer Flash Pool
                  - ISO_FALSE - Use pool manipulation

   \retval        iso_s16
                  - E_NO_ERR
                  - E_NO_INSTANCE
    \note Deprecated: Use IsoVtcPoolLoad() with mode PoolTransferRaw
*/
ISO_DEPRECATED
ISO_CLIENT_API
     iso_s16 IsoVtcPoolTransferFlashPool( iso_u8 u8Instance, iso_bool qFlashTransfer );

/* **************************************************************************************** */
/*!
   \brief       Setting scaling factor and the characteristics of a object ID range

   This function is used for control the manipulation of the driver with pool objects.
   First two parameter determines the range of IDs. Start ID and end ID same value means
   only one Object ID.

   \param[in]  \wp{u8Instance, iso_u8}
                       Identifier of the client instance
   \param[in]   \wp{wStartId, iso_u16}
                       Object ID - Start ID of range \n
                       Range: 0 - 65535
   \param[in]   \wp{wEndId, iso_u16}
                       Object ID - End ID of range \n
                       Range: 0 - 65535 \n
                       Object ID shall be identical or greater than Start ID
   \param[in]   \wp{rwManipulValue, iso_u16}
                 Manipulation value for this range depending of manipulation range: \n
   \code
   - Scaling factor for modes "Scaling" and "Centering" 10000 means factor 1, 20000 means factor 2 ...
   - Target objectID of moved range for "LoadMoveID"
   - Target objectID of copied range for "LoadCopyID"
   - Colour depth see ISOGRAPH_TYPE_e for mode "ColourReduction" ( only pictures )
   - Dont care for other modes
   \endcode
   \param[in]   \wp{eModeMani, ISOPOOLMANIMODE_e}
                       Manipulation mode ( NoScaling, Scaling, Centering, NotLoad, Proprietary,
                       LoadMoveID, LoadCopyID, ColourReduction, AuxToV2 )

   \retval             iso_s16
                       - E_NO_ERR       - OK
                       - E_OVERFLOW     - Setting not possible because list is full
                       - E_NO_INSTANCE
   \note  \par
       - Every call of this function is entried in a struct. Take care that the define
         ISO_NO_SCALING_ELEMENTS_MAX is sufficient. This value defines the maximum number
         of Ranges.
       - LoadCopyID can be used multiple for the same object(s) ( -> define ISO_POOLNUMANICOPY!! )
*/
ISO_CLIENT_API
    iso_s16 IsoVtcPoolSetIDRangeMode( iso_u8 u8Instance, iso_u16 wStartId, iso_u16 wEndId, iso_u16 rwManipulValue, ISOPOOLMANIMODE_e eModeMani );

/* **************************************************************************************** */
/*!
   \brief      Changing Active Mask and Working Set Identifier Object before pool transport

   This function must called after IsoVtcPoolInit().
   Using is necessary if the selection of the active data mask is done during pool manipulation.

   \param[in]  \wp{u8Instance, iso_u8}
                 Identifier of the client instance
   \param[in]  \wp{wDMActive, iso_u16}
                  Active Mask Object ID
   \param[in]  \wp{wWSIdentObjectID, iso_u16}
                  First Working Set Identifier Object ID

   \retval             iso_s16
                        - E_NO_ERR
                        - E_NO_INSTANCE
   \note  \par
           Special function to manipulate the predefined WSO entries before pool manipulation
*/
ISO_CLIENT_API
     iso_s16 IsoVtcPoolDMActiveWSIdentSet ( iso_u8 u8Instance, iso_u16 wDMActive, iso_u16 wWSIdentObjectID );

/* **************************************************************************************** */
/*!
   \brief      Changing Working Set Object selectable attribute before pool transport

   This function must called after IsoVtcPoolInit().

   \param[in]  \wp{u8Instance, iso_u8}
                Identifier of the client instance
   \param[in]  \wp{qSelectable, iso_bool}
                - #ISO_TRUE if the Working Set can be selected by the operator
                - #ISO_FALSE if the Working Set should not be selectable
   \retval     iso_s16
               - E_NO_ERR
               - E_NO_INSTANCE
   \par
   Special function to manipulate the predefined WSO entry before pool manipulation
*/
ISO_CLIENT_API
     iso_s16 IsoVtcPoolWSSelectableSet ( iso_u8 u8Instance, iso_bool qSelectable );

/* **************************************************************************************** */
/*!
   \brief           Determination of number of objects in the pool

   This function counts the number of objects in a pool.

   \param[in]  \wp{pbFlashAct,  iso_u8 HUGE_C[] }
                  Pointer on first iso_u8 of pool
   \param[in]  \wp{lSize, iso_s32}
                  Size of pool in bytes

   \retval           iso_u16  Number of objects in pool
   \note Deprecated: Use IsoVtcGetNumofPoolObjs()
*/
ISO_DEPRECATED
ISO_CLIENT_API
	iso_u16 IsoGetNumofPoolObjs( const iso_u8 HUGE_C pbFlashAct[], iso_s32 lSize );

/* **************************************************************************************** */
/*!
   \brief           Determination of number of objects in the pool

   This function counts the number of objects in a pool.

   \param[in]  \wp{pbFlashAct,  iso_u8 HUGE_C[] }
                  Pointer on first iso_u8 of pool
   \param[in]  \wp{lSize, iso_s32}
                  Size of pool in bytes

   \retval           iso_u16  Number of objects in pool
   \par
         This function can be used before IsoVtcPoolInit() for determining the number of
         objects in a pool.
*/
ISO_CLIENT_API
iso_u16 IsoVtcGetNumofPoolObjs(const iso_u8 HUGE_C pbFlashAct[], iso_s32 lSize);


/***************************************************************************/
/*!
   \brief   Determination of the size of specific object in the pool

   This function returns the size of the given object in bytes.

   \param[in]  \wp{pbFlashObj,  iso_u8 HUGE_C[] }
                  Pointer to the object iso_u8 array
   \retval        iso_u32  size of the object in bytes or zero in case of an error
   \note Deprecated: Use IsoVtcPoolObjSize()
*/
ISO_DEPRECATED
ISO_CLIENT_API
   iso_u32 IsoPoolObjSize( const iso_u8 HUGE_C pbFlashObj[] );

/***************************************************************************/
/*!
   \brief   Determination of the size of specific object in the pool

   This function returns the size of the given object in bytes.

   \param[in]  \wp{pbFlashObj,  iso_u8 HUGE_C[] }
                  Pointer to the object iso_u8 array
   \retval        iso_u32  size of the object in bytes or zero in case of an error
*/
ISO_CLIENT_API
iso_u32 IsoVtcPoolObjSize(const iso_u8 HUGE_C pbFlashObj[]);

#ifdef ISO_EXTERNAL_POOLBUFFER
/***************************************************************************/
/*! 
   \brief  Pool RAM buffer set function
   \details Use the function to replace the internal with an extern buffer. \n
   The external buffer must have the size defined by ISO_VTC_POOLBUFFERSIZE and set before 
   calling a IsoVtcPoolInit() function. \n
   Add the define #ISO_EXTERNAL_POOLBUFFER to IsoConf.h to enable this function.
   \param[in]  \wp{abPoolRAMBuffer,  iso_u8 HUGE_C[] }
                  Pointer to the external pool RAM buffer array.
   \retval     iso_s16
               - E_NO_ERR
   \note Deprecated: Use IsoVtcPoolSetBuffer()
*/
ISO_DEPRECATED
ISO_CLIENT_API
   iso_s16 IsoPoolSetBuffer ( iso_u8 HUGE_C abPoolRAMBuffer[] );

/***************************************************************************/
/*!
   \brief  Pool RAM buffer set function
   \details Use the function to replace the internal with an extern buffer. \n
   The external buffer must have the size defined by ISO_VTC_POOLBUFFERSIZE and set before
   calling a IsoVtcPoolInit() function. \n
   Add the define #ISO_EXTERNAL_POOLBUFFER to IsoConf.h to enable this function.
   \param[in]  \wp{abPoolRAMBuffer,  iso_u8 HUGE_C[] }
                  Pointer to the external pool RAM buffer array.
   \retval     iso_s16
               - E_NO_ERR
*/
ISO_CLIENT_API
iso_s16 IsoVtcPoolSetBuffer(iso_u8 HUGE_C abPoolRAMBuffer[]);

#endif

#ifdef POOLPROP_

/* ************************************************************************ */
/*!
	\brief       Type definition of the proprietary pool object manipulation callback function 

	\retval             iso_s16
                         - E_NO_ERR    - done/copied
                         - E_OVERFLOW  - to large for free RAM buffer -> do in next (E)TP
                         - E_NOACT  - not handled/copied -> use pool service functions
	\note  \par
		    Special feature initiated of Company Kuhn
*/
typedef iso_s16 (*ISOVT_CbPoolProprietaryAdaptation_t)(OBJTYP_e eObjType, iso_u16 u16ObjID, iso_u32 u32BufferUsed, 
                                             const iso_u8 HUGE_C* pu8ObjAdr, iso_u8 HUGE_C* pu8DestAdr, 
                                             iso_u32* pu32ObjSize, ISO_USER_PARAM_T userParam);

/* ************************************************************************ */
/*!
	\brief       Initialisation of own pool manipulation

	This function enables proprietary pool manipulation. Preprozessor POOLPROP_ must be set.
	The function behind "rpf_ProprietaryAdaptation" replaces the driver intern pool manipulation


    \param[in]       \wp{rpf_ProprietaryAdaptation,  ISOVT_CbPoolProprietaryAdaptation_t}
 			            Pointer to own proprietary pool manipulation function
	\retval             iso_s16
                         - E_NO_ERR
	\note  \par
		    Special feature initiated of Company Kuhn
*/
ISO_CLIENT_API
    iso_s16 IsoPoolPropAdaptInit( ISOVT_CbPoolProprietaryAdaptation_t rpf_ProprietaryAdaptation );

/* ************************************************************************ */
/*!
    \brief        Copy a object from Flash to RAM

    \param[in]  \wp{pbFlashObjOffset, iso_u8 HUGE_C*}
                   Absolut start address of an object
    \param[in]  \wp{dwUsedBuff, iso_u32}
                  Actually occupied object buffer
    \param[in]  \wp{pbRAMPos, iso_u8 HUGE_C*}
                  Absolut target address of an object in the RAM
    \param[in]  \wp{wObjFlashSize, iso_u16}
                  Object size

    \retval      iso_s16
                  - E_NO_ERR         - OK
                  - E_OVERFLOW       - if RAM buffer is full
*/
ISO_CLIENT_API
   iso_s16 IsoPoolObjCopyToRAM( const iso_u8 HUGE_C pbFlashObjOffset[], iso_u32 dwUsedBuff,
                             iso_u8 HUGE_C pbRAMPos[], iso_u16 wObjFlashSize );


#endif /* POOLPROP_ */

/* ************************************************************************ */
/*! 
   \brief Callback function pointer to return an pool object to the application.
   \details The callback function is called from the pool transfer
   to give back the current pool object to the application 
   and can be used to manipulate the object attributes in the RAM buffer 
   before the object is transferred to the VT. \n
   The callback function can be set with IsoPoolSecondaryAdaptInit().

   \param[in]     \wpp{psObjectInfo, const #ISOVT_PoolObj_Info_Ts* }
                     Pointer to the object information structure. 
   \param[in,out] \wp{pau8Object, iso_u8 HUGE_C[] }
                     Pointer to the object data byte array in the RAM buffer.
   \param[in,out] \wp{pu32ObjectSize, iso_u32* }
                     Size of the pool object in bytes. \n
                     Can be set to 0UL to skip the object.
*/
   typedef  void (*ISOVT_CbPoolSecondaryAdaptation_t)(const ISOVT_PoolObj_Info_Ts* psObjectInfo,
                                                      iso_u8 HUGE_C pau8Object[], iso_u32* pu32ObjectSize);
    
/* ************************************************************************ */
/*!
   \brief   Sets the callback function for a secondary pool object manipulation

	This function enables the proprietary pool manipulation. 
   The given callback function is called for every object after the internal manipulation of the object. 
   
   \param[in]       \wp{rpf_SecondaryAdaptation,  ISOVT_CbPoolSecondaryAdaptation_t}
 			            Pointer to own secondary pool manipulation function,
                     or NULL pointer to disable.
*/
ISO_CLIENT_API
   void IsoPoolSecondaryAdaptInit(ISOVT_CbPoolSecondaryAdaptation_t rpf_SecondaryAdaptation);


/* ************************************************************************ */
/*!
   \brief Callback function pointer to provide the size of an manufacturer defined pool object.
   \details The callback function is called from the pool transfer
   to get the size of a custom pool object from the application. \n
   The callback function can be set with IsoVtcPoolCustomObjectSizeCbSet().

   \param[in]     \wp{u8ObjectTypeID, iso_u8 }
                     Extracted object type ID; Range: 240u - 254u
   \param[in]     \wpp{pau8Object, const #iso_u8 HUGE_C[] }
                     Pointer to the object (header) data.
                     (Contains valid data up to ISO_VTC_CUSTOM_POOL_OBJECTS_HEADER_SIZE bytes)
   \retval       iso_u32
                  - Size of the pool object in bytes
*/
typedef  iso_u32 (*ISOVT_CbPoolObjectSizeCalc_t)( iso_u8 u8ObjectTypeID, 
   const iso_u8 HUGE_C pau8Object[]);


#if defined(ISO_VTC_CUSTOM_POOL_OBJECTS_HEADER_SIZE)
/* ************************************************************************ */
/*!
   \brief   Sets the callback function for the size calculation for custom pool objects

   If enabled and configured with the define #ISO_VTC_CUSTOM_POOL_OBJECTS_HEADER_SIZE
   the given callback function is called for manufacturer defined objects (Type ID 240 - 254) 
   to get the size of the custom object.

   \param[in]       \wp{pf_ObjectSizeCalcCb,  ISOVT_CbPoolSecondaryAdaptation_t}
                     Pointer to the object size calculation function,
                     or NULL pointer to disable.
*/
ISO_CLIENT_API
void IsoVtcPoolCustomObjectSizeCbSet(ISOVT_CbPoolObjectSizeCalc_t pf_ObjectSizeCalcCb);
#endif /* defined(ISO_VTC_CUSTOM_POOL_OBJECTS_HEADER_SIZE) */

/* ************************************************************************ */
/*!
    \brief      Crops a picture object.
                The cropped image is taken from the center of the original image. \n

                The function supports 256 color picture objects (format 2) without limitations.
                For 16 and 2 color picture objects the function has following limitations:
                - The x-offset for the cropped picture is set byte-aligned (16-colors: factor 2; 2-colors: factor 8). 
                - For RLE compressed pictures, the width of the cropped picture must use complete bytes (width % factor = 0). \n
                  if not, the next lower fully filled byte is used as width.

    \param[in,out] \wp{pau8PicObj, iso_u8 HUGE_C []}  
                Pointer to the picture object byte array which should be manipulated

    \param[in] \wp{u16Width, iso_u16}    
                new picture width 
    \param[in] \wp{u16Height, iso_u16}    
                new picture height
    \param[out] \wp{pu32PicObjSize, iso_u32*}  
                Return value with the (new) picture size 
    
    \retval                iso_s16
                           - #E_NO_ERR         - OK                    
                           - #E_RANGE          - Parameter not valid
                           - #E_VALUE_WRONG    - Not a valid picture object

*/
ISO_CLIENT_API
iso_s16 IsoPoolCropCenterOfPictureObject(iso_u8 HUGE_C pau8PicObj[], iso_u16 u16Width, iso_u16 u16Height, iso_u32* pu32PicObjSize);

/* ************************************************************************ */
/*!
    \brief      Crops a picture object 

                The function supports 256 color picture objects (format 2) without limitations.
                For 16 and 2 color picture objects the function has following limitations:
                - The x-offset must be byte-aligned (16-colors: factor 2; 2-colors: factor 8). \n
                  If not byte-aligned, the next lower byte-aligned position is used as x-offset.
                - For RLE compressed pictures, the width of the cropped picture must use complete bytes (width % factor = 0). \n
                  if not, the next lower fully filled byte is used as width.

    \param[in,out] \wp{pau8PicObj, iso_u8 HUGE_C []}  
                Pointer to the picture object byte array which should be manipulated
    \param[in] \wp{u16OffsetX, iso_u16}    
                x start position (x-offset) 
    \param[in] \wp{u16OffsetY, iso_u16}    
                y start position (y-offset) 
    \param[in] \wp{u16Width, iso_u16}    
                new picture width 
    \param[in] \wp{u16Height, iso_u16}    
                new picture height
    \param[out] \wp{pu32PicObjSize, iso_u32*}  
                Return value with the (new) picture size 
    
    \retval                iso_s16
                           - #E_NO_ERR         - OK                    
                           - #E_RANGE          - Parameter not valid
                           - #E_VALUE_WRONG    - Not a valid picture object

*/
ISO_CLIENT_API
iso_s16 IsoPoolCropPictureObject(iso_u8 HUGE_C pau8PicObj[], iso_u16 u16OffsetX, iso_u16 u16OffsetY,
                                 iso_u16 u16Width, iso_u16 u16Height, iso_u32* pu32PicObjSize);

/* ************************************************************************* */
/*!
   \brief      Converts a picture object to a lower colour depth 
   \details    If the colour depth of the source picture is already equal or lower 
               to the destination colour depth, the picture is only copied. 

   \param[in]  \wpp{ pu8PicObjSrc, const #iso_u8 HUGE_C [] }
                  Pointer to the source picture object
   \param[in]  \wp{ pbRAMDest, iso_u8 HUGE_C [] }
                  Pointer to the destination address of in the RAM
   \param[in]  \wp{ u32SizeRAMDest, iso_u32 }
                  Size of the destination RAM buffer in bytes
   \param[in]  \wp{ eColDepth, ISOGRAPH_TYPE_e }
                  Target colour depth for the conversion (if a conversion is needed)
   \param[out] \wp{ pu32DestPicObjSize, iso_u32* }
                  Pointer to the variable to store the RAM size used for the (new) picture object. \n
                  (Size of the new picture object, or 0UL in case of an error)
   \retval         iso_s16
                  - #E_NO_ERR    - if copied or converted
                  - #E_RANGE     - if the parameter are not valid
                  - #E_OVERFLOW  - if the given RAM buffer is to small to convert the picture
   \par Hint:
   A real device should normally not need this function, since the driver can convert picture objects during the 
   pool upload if the pool buffer is large enough to convert the picture on the fly (picture object size + at least 200 bytes).
   If a device needs to support an old monochrome or 16-color VT, it is recommended to provide a pool with already converted images,
   since the internal conversion function cannot provide high-quality monochrome or 16-color images.
*/
ISO_CLIENT_API
iso_s16 IsoVtcPoolConvertPictureObject(const iso_u8 HUGE_C pu8PicObjSrc[], iso_u8 HUGE_C pbRAMDest[],
   iso_u32 u32SizeRAMDest, ISOGRAPH_TYPE_e eColDepth, iso_u32* pu32DestPicObjSize);

/* ************************************************************************ */
/**   \brief Use IsoVtcPoolObjectCbSet() to set an "object processing" callback function. 
      \details The given callback function is called from the pool transfer 
               for every pool object while scanning or uploading a pool to the VT. \n
               The callback function can be used to read the attributes of the object.
      \param[in]  \wp{u8Instance, iso_u8}
                     Identifier of the client instance
      \param[in]   \wp{pfnCallbackFunction,  iso_fnCbPoolObject_t }
                     Pointer to the application function which should be called 
                     when processing a new pool object. \n
                     Can be set to the NULL pointer to disable the functionality.
      \retval      iso_s16
                     - E_NO_ERR         - OK
                     - E_NO_INSTANCE
*/
ISO_CLIENT_API
   iso_s16 IsoVtcPoolObjectCbSet( iso_u8 u8Instance, iso_fnCbPoolObject_t pfnCallbackFunction );


   /** \brief
   Enum of result size for attribute-ID
   */
   typedef enum
   {
       UnsignedLong,                 /**< value is iso_u32 */
       SignedLong,                   /**< value is int32 */
       Float                         /**< value is iso_f32 */
   } ISOPO_AID_VALUETYPE_e;

   /*! \ brief AID value */
   typedef struct
   {
       ISOPO_AID_VALUETYPE_e  eAID_valuetype; /*! \brief witch AID type is required */
       iso_u32    u32AID_value;               /*! \brief AID value unsigned type */
       iso_s32    s32AID_value;               /*! \brief AID value signed type */
       iso_f32    f32AID_value;               /*! \brief AID value float type */
   }   ISOPoAID_Value_T;


   /***************************************************************************/
   /*!
	   \brief Use IsoPoObjAttributGet() to get the value of the appropriate attribute ID. 

       \param[in]     \wpp{pau8Objekt[], const iso_u8 HUGE_C }
                        iso_u8 array pointer to the pool object
       \param[in]     \wp{u16AID,  iso_u16 }
                        desired attribut ID (AID)
       \param[out]    \wp{psIsoPoAID_Val,  ISOPoAID_Value_T* }
                        Pointer to the result value \n
					   	   depending on result size type, the value will be stored as \n
					   	   u32AID_value, s32AID_value or f32AID_value. \
					       	The required data type is defined in eAID_valuetype.
       \retval        iso_s16
                        - E_NO_ERR         - OK
                        - E_RANGE          - wrong parameter
   */
ISO_CLIENT_API
   iso_s16 IsoPoObjAttributGet( const iso_u8 HUGE_C pau8Objekt[], iso_u16 u16AID, ISOPoAID_Value_T* const psIsoPoAID_Val );

   /* ************************************************************************ */
   /*! 
	   \brief Use IsoPoolObjPtrGet() to get the pointer to the object data. 

       \param[in]     \wp{u8Instance, iso_u8}
                        Identifier of the client instance
       \param[in]     \wpp{pau8Pool, const iso_u8 HUGE_C [] }
                        iso_u8 array pointer to the pool
       \param[in]     \wp{u32ObjOffset,  iso_u32 }
                        desired object offset in bytes
       \retval         const iso_u8 HUGE_C *
                        Pointer to the object data or NULL pointer in case of an error \n

   */
ISO_CLIENT_API
   const iso_u8 HUGE_C * IsoPoolObjPtrGet(iso_u8 u8Instance, const iso_u8 HUGE_C pau8Pool[], iso_u32 u32ObjOffset );

/* ************************************************************************ */
#ifdef DOXYGEN
   /*!  \def ISOVT_AID_DEFINES 
        \brief Add the define ISOVT_AID_DEFINES to your IsoConf.h 
         to make the object pool attribute defines visible. 
   */
   #define ISOVT_AID_DEFINES 
#endif

#if defined(CCI_USE_NAMESPACE) && defined(__cplusplus)
   /* IsoVtcApi.hpp  is already included above */
#else    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) -> use C defines */

#ifdef ISOVT_AID_DEFINES  /* use the AID defines of the ECU Driver */
/* ************************************************************************ */
/** \addtogroup gr_isovt_aids Object pool attribute id defines
    \brief Add the define ISOVT_AID_DEFINES to your IsoConf.h 
         to make the object pool attribute defines visible. 
 @{ */
/*! \name Object type object attribute id 
 @{ */
#define AID_TYPE        0U       /*!< \brief 0: AID object type */
/*!@}*/

/*! \name Working set object attribute id's 
 @{ */
#define AID_WS_BG_COLOUR   1U    /*!< \brief 1: AID_WS_BG_COLOUR */
#define AID_WS_SELECTABLE  2U    /*!< \brief 2: AID_WS_SELECTABLE */
#define AID_WS_ACTIVE_MASK 3U    /*!< \brief 3: AID_WS_ACTIVE_MASK */
/*!@}*/

/*! \name Data mask object attribute id's 
 @{ */
#define AID_DM_BG_COLOUR      1U    /*!< \brief 1: AID_DM_BG_COLOUR */
#define AID_DM_SOFT_KEY_MASK  2U    /*!< \brief 2: AID_DM_SOFT_KEY_MASK */
/*!@}*/

/*! \name Alarm mask object attribute id's 
 @{ */
#define AID_AM_BG_COLOUR      1U    /*!< \brief 1: AID_AM_BG_COLOUR */
#define AID_AM_SOFT_KEY_MASK  2U    /*!< \brief 2: AID_AM_SOFT_KEY_MASK */
#define AID_AM_PRIORITY       3U    /*!< \brief 3: AID_AM_PRIORITY */
#define AID_AM_ACOUSTIC       4U    /*!< \brief 4: AID_AM_ACOUSTIC */
/*!@}*/
 

/*! \name Container object attribute id'
 @{ */
#define AID_CO_WIDTH       1U    /*!< \brief 1: AID_CO_WIDTH */
#define AID_CO_HEIGHT      2U    /*!< \brief 2: AID_CO_HEIGHT */
#define AID_CO_HIDDEN      3U    /*!< \brief 3: AID_CO_HIDDEN */
/*!@}*/

/*! \name Soft key mask object attribute id's 
 @{ */
#define AID_SKM_BG_COLOUR  1U    /*!< \brief 1: AID_SKM_BG_COLOUR */
/*!@}*/

/*! \name Soft key object attribute id's 
 @{ */
#define AID_SK_BG_COLOUR   1U    /*!< \brief 1: AID_SK_BG_COLOUR */
#define AID_SK_KEY_CODE    2U    /*!< \brief 2: AID_SK_KEY_CODE */
/*!@}*/

/*! \name Button object attribute id's 
 @{ */
#define AID_BO_WIDTH       1U    /*!< \brief 1: AID_BO_WIDTH */
#define AID_BO_HEIGHT      2U    /*!< \brief 2: AID_BO_HEIGHT */
#define AID_BO_BG_COLOUR   3U    /*!< \brief 3: AID_BO_BG_COLOUR */
#define AID_BO_BORDERCOLOUR  4U  /*!< \brief 4: AID_BO_BORDERCOLOUR */
#define AID_BO_KEY_CODE    5U    /*!< \brief 5: AID_BO_KEY_CODE */
#define AID_BO_OPTIONS     6U    /*!< \brief 6: AID_BO_OPTIONS */
/*!@}*/

/*! \name Input boolean object attribute id's 
 @{ */
#define AID_IB_BG_COLOUR   1U    /*!< \brief 1: AID_IB_BG_COLOUR */
#define AID_IB_WIDTH       2U    /*!< \brief 2: AID_IB_WIDTH */
#define AID_IB_FG_COLOUR   3U    /*!< \brief 3: AID_IB_FG_COLOUR */
#define AID_IB_VARIABLE_REF 4U   /*!< \brief 4: AID_IB_VARIABLE_REF */
#define AID_IB_VALUE       5U    /*!< \brief 5: AID_IB_VALUE */
#define AID_IB_ENABLED     6U    /*!< \brief 6: AID_IB_ENABLED */
/*!@}*/

/*! \name Input string object attribute id's 
 @{ */
#define AID_IS_WIDTH       1U    /*!< \brief 1: AID_IS_WIDTH */
#define AID_IS_HEIGHT      2U    /*!< \brief 2: AID_IS_HEIGHT */
#define AID_IS_BG_COLOUR   3U    /*!< \brief 3: AID_IS_BG_COLOUR */
#define AID_IS_FONT_ATT    4U    /*!< \brief 4: AID_IS_FONT_ATT */
#define AID_IS_INP_ATT     5U    /*!< \brief 5: AID_IS_INP_ATT */
#define AID_IS_OPTIONS     6U    /*!< \brief 6: AID_IS_OPTIONS */
#define AID_IS_VARIABLE_REF  7U  /*!< \brief 7: AID_IS_VARIABLE_REF */
#define AID_IS_JUSTIFICATION 8U  /*!< \brief 8: AID_IS_JUSTIFICATION */
#define AID_IS_ENABLED     9U    /*!< \brief 9: AID_IS_ENABLED */
/*!@}*/

/*! \name Input number object attribute is's 
 @{ */
#define AID_IN_WIDTH          1U    /*!< \brief  1: AID_IN_WIDTH */
#define AID_IN_HEIGHT         2U    /*!< \brief  2: AID_IN_HEIGHT */
#define AID_IN_BG_COLOUR      3U    /*!< \brief  3: AID_IN_BG_COLOUR */
#define AID_IN_FONT_ATT       4U    /*!< \brief  4: AID_IN_FONT_ATT */
#define AID_IN_OPTIONS        5U    /*!< \brief  5: AID_IN_OPTIONS */
#define AID_IN_VARIABLE_REF   6U    /*!< \brief  6: AID_IN_VARIABLE_REF */
#define AID_IN_MIN_VALUE      7U    /*!< \brief  7: AID_IN_MIN_VALUE */
#define AID_IN_MAX_VALUE      8U    /*!< \brief  8: AID_IN_MAX_VALUE */
#define AID_IN_OFFSET         9U    /*!< \brief  9: AID_IN_OFFSET */
#define AID_IN_SCALE         10U    /*!< \brief 10: AID_IN_SCALE */
#define AID_IN_NUMB_DECIMALS 11U    /*!< \brief 11: AID_IN_NUMB_DECIMALS */
#define AID_IN_FORMAT        12U    /*!< \brief 12: AID_IN_FORMAT */
#define AID_IN_JUSTIFICATION 13U    /*!< \brief 13: AID_IN_JUSTIFICATION */
#define AID_IN_VALUE         14U    /*!< \brief 14: AID_IN_VALUE */
#define AID_IN_OPTIONS_2     15U    /*!< \brief 15: AID_IN_OPTIONS_2 */
/*!@}*/

/*! \name input list object attribute id's 
 @{ */
#define AID_IL_WIDTH          1U    /*!< \brief 1: AID_IL_WIDTH */
#define AID_IL_HEIGHT         2U    /*!< \brief 2: AID_IL_HEIGHT */
#define AID_IL_VARIABLE_REF   3U    /*!< \brief 3: AID_IL_VARIABLE_REF */
#define AID_IL_VALUE          4U    /*!< \brief 4: AID_IL_VALUE */
#define AID_IL_OPTIONS        5U    /*!< \brief 5: AID_IL_OPTIONS */
/*!@}*/

/*! \name Output string object attribute id's
 @{ */
#define AID_OS_WIDTH          1U    /*!< \brief 1: AID_OS_WIDTH */
#define AID_OS_HEIGHT         2U    /*!< \brief 2: AID_OS_HEIGHT */
#define AID_OS_BG_COLOUR      3U    /*!< \brief 3: AID_OS_BG_COLOUR */
#define AID_OS_FONT_ATT       4U    /*!< \brief 4: AID_OS_FONT_ATT */
#define AID_OS_OPTIONS        5U    /*!< \brief 5: AID_OS_OPTIONS */
#define AID_OS_VARIABLE_REF   6U    /*!< \brief 6: AID_OS_VARIABLE_REF */
#define AID_OS_JUSTIFICATION  7U    /*!< \brief 7: AID_OS_JUSTIFICATION */
/*!@}*/

/*! \name Output number object attribute id's 
 @{ */
#define AID_ON_WIDTH           1U    /*!< \brief  1: AID_ON_WIDTH */
#define AID_ON_HEIGHT          2U    /*!< \brief  2: AID_ON_HEIGHT */
#define AID_ON_BG_COLOUR       3U    /*!< \brief  3: AID_ON_BG_COLOUR */
#define AID_ON_FONT_ATT        4U    /*!< \brief  4: AID_ON_FONT_ATT */
#define AID_ON_OPTIONS         5U    /*!< \brief  5: AID_ON_OPTIONS */
#define AID_ON_VARIABLE_REF    6U    /*!< \brief  6: AID_ON_VARIABLE_REF */
#define AID_ON_OFFSET          7U    /*!< \brief  7: AID_ON_OFFSET */
#define AID_ON_SCALE           8U    /*!< \brief  8: AID_ON_SCALE */
#define AID_ON_NUMB_DECIMALS   9U    /*!< \brief  9: AID_ON_NUMB_DECIMALS */
#define AID_ON_FORMAT         10U    /*!< \brief 10: AID_ON_FORMAT */
#define AID_ON_JUSTIFICATION  11U    /*!< \brief 11: AID_ON_JUSTIFICATION */
#define AID_ON_VALUE          12U    /*!< \brief 12: AID_ON_VALUE */
/*!@}*/

/*! \name Output line object attribute id's 
 @{ */
#define AID_OL_LINE_ATT    1U    /*!< \brief 1: AID_OL_LINE_ATT */
#define AID_OL_WIDTH       2U    /*!< \brief 2: AID_OL_WIDTH */
#define AID_OL_HEIGHT      3U    /*!< \brief 3: AID_OL_HEIGHT */
#define AID_OL_LINE_DIR    4U    /*!< \brief 4: AID_OL_LINE_DIR */
/*!@}*/

/*! \name Output rectangle object attribute id's
 @{ */
#define AID_OR_LINE_ATT    1U    /*!< \brief 1: AID_OR_LINE_ATT */
#define AID_OR_WIDTH       2U    /*!< \brief 2: AID_OR_WIDTH */
#define AID_OR_HEIGHT      3U    /*!< \brief 3: AID_OR_HEIGHT */
#define AID_OR_LINE_SUPPR  4U    /*!< \brief 4: AID_OR_LINE_SUPPR */
#define AID_OR_FILL_ATT    5U    /*!< \brief 5: AID_OR_FILL_ATT */
/*!@}*/

/*! \name Output ellipse object attribute id's 
 @{ */
#define AID_OE_LINE_ATT       1U    /*!< \brief 1: AID_OE_LINE_ATT */
#define AID_OE_WIDTH          2U    /*!< \brief 2: AID_OE_WIDTH */
#define AID_OE_HEIGHT         3U    /*!< \brief 3: AID_OE_HEIGHT */
#define AID_OE_ELLIPSE_TYPE   4U    /*!< \brief 4: AID_OE_ELLIPSE_TYPE */
#define AID_OE_START_ANGLE    5U    /*!< \brief 5: AID_OE_START_ANGLE */
#define AID_OE_END_ANGLE      6U    /*!< \brief 6: AID_OE_END_ANGLE */
#define AID_OE_FILL_ATT       7U    /*!< \brief 7: AID_OE_FILL_ATT */
/*!@}*/

/*! \name Output polypon object attribute id's 
 @{ */
#define AID_OP_WIDTH          1U    /*!< \brief 1: AID_OP_WIDTH */
#define AID_OP_HEIGHT         2U    /*!< \brief 2: AID_OP_HEIGHT */
#define AID_OP_LINE_ATT       3U    /*!< \brief 3: AID_OP_LINE_ATT */
#define AID_OP_FILL_ATT       4U    /*!< \brief 4: AID_OP_FILL_ATT */
#define AID_OP_POLYGON_TYPE   5U    /*!< \brief 5: AID_OP_POLYGON_TYPE */
/*!@}*/

/*! \name Output meter object attribute id's 
 @{ */
#define AID_OM_WIDTH             1U    /*!< \brief  1: AID_OM_WIDTH */
#define AID_OM_NEEDLE_COLOUR     2U    /*!< \brief  2: AID_OM_NEEDLE_COLOUR */
#define AID_OM_BORDER_COLOUR     3U    /*!< \brief  3: AID_OM_BORDER_COLOUR */
#define AID_OM_ARC_THICK_COLOUR  4U    /*!< \brief  4: AID_OM_ARC_THICK_COLOUR */
#define AID_OM_OPTIONS           5U    /*!< \brief  5: AID_OM_OPTIONS */
#define AID_OM_NUMB_TICKS        6U    /*!< \brief  6: AID_OM_NUMB_TICKS */
#define AID_OM_START_ANGLE       7U    /*!< \brief  7: AID_OM_START_ANGLE */
#define AID_OM_END_ANGLE         8U    /*!< \brief  8: AID_OM_END_ANGLE */
#define AID_OM_MIN_VALUE         9U    /*!< \brief  9: AID_OM_MIN_VALUE */
#define AID_OM_MAX_VALUE        10U    /*!< \brief 10: AID_OM_MAX_VALUE */
#define AID_OM_VARIABLE_REF     11U    /*!< \brief 11: AID_OM_VARIABLE_REF */
#define AID_OM_VALUE            12U    /*!< \brief 12: AID_OM_VALUE */
/*!@}*/

/*! \name Output linear bar graph object attribute id's 
 @{ */
#define AID_OLBG_WIDTH              1U    /*!< \brief   1: AID_OLBG_WIDTH */
#define AID_OLBG_HEIGHT             2U    /*!< \brief   2: AID_OLBG_HEIGHT */
#define AID_OLBG_COLOUR             3U    /*!< \brief   3: AID_OLBG_COLOUR */
#define AID_OLBG_TARGET_LINE_COLOUR 4U    /*!< \brief   4: AID_OLBG_TARGET_LINE_COLOUR */
#define AID_OLBG_OPTIONS            5U    /*!< \brief   5: AID_OLBG_OPTIONS */
#define AID_OLBG_NUMB_TICKS         6U    /*!< \brief   6: AID_OLBG_NUMB_TICKS */
#define AID_OLBG_MIN_VALUE          7U    /*!< \brief   7: AID_OLBG_MIN_VALUE */
#define AID_OLBG_MAX_VALUE          8U    /*!< \brief   8: AID_OLBG_MAX_VALUE */
#define AID_OLBG_VARIABLE_REF       9U    /*!< \brief   9: AID_OLBG_VARIABLE_REF */
#define AID_OLBG_TARGET_VAL_VAR_REF 10U   /*!< \brief  10: AID_OLBG_TARGET_VAL_VAR_REF */
#define AID_OLBG_TARGET_VALUE       11U   /*!< \brief  11: AID_OLBG_TARGET_VALUE */
#define AID_OLBG_VALUE              12U   /*!< \brief  12: AID_OLBG_VALUE */
/*!@}*/

/*! \name Output arched bar graph object attribute id's 
 @{ */
#define AID_OABG_WIDTH               1U    /*!< \brief   1: AID_OABG_WIDTH */
#define AID_OABG_HEIGHT              2U    /*!< \brief   2: AID_OABG_HEIGHT */
#define AID_OABG_COLOUR              3U    /*!< \brief   3: AID_OABG_COLOUR */
#define AID_OABG_TARGET_LINE_COLOUR  4U    /*!< \brief   4: AID_OABG_TARGET_LINE_COLOUR */
#define AID_OABG_OPTIONS             5U    /*!< \brief   5: AID_OABG_OPTIONS */
#define AID_OABG_START_ANGLE         6U    /*!< \brief   6: AID_OABG_START_ANGLE */
#define AID_OABG_END_ANGLE           7U    /*!< \brief   7: AID_OABG_END_ANGLE */
#define AID_OABG_BAR_GRAPH_WIDTH     8U    /*!< \brief   8: AID_OABG_BAR_GRAPH_WIDTH */
#define AID_OABG_MIN_VALUE           9U    /*!< \brief   9: AID_OABG_MIN_VALUE */
#define AID_OABG_MAX_VALUE          10U    /*!< \brief  10: AID_OABG_MAX_VALUE */
#define AID_OABG_VARIABLE_REF       11U    /*!< \brief  11: AID_OABG_VARIABLE_REF */
#define AID_OABG_TARGET_VAL_VAR_REF 12U    /*!< \brief  12: AID_OABG_TARGET_VAL_VAR_REF */
#define AID_OABG_TARGET_VALUE       13U    /*!< \brief  13: AID_OABG_TARGET_VALUE */
#define AID_OABG_VALUE              14U    /*!< \brief  14: AID_OABG_VALUE */
/*!@}*/

/*! \name Picture graphic object attribute id's 
 @{ */
#define AID_PG_WIDTH          1U    /*!< \brief 1: AID_PG_WIDTH */
#define AID_PG_OPTIONS        2U    /*!< \brief 2: AID_PG_OPTIONS */
#define AID_PG_TRANSPARENCY_COLOUER  3U   /*!< \brief 3: AID_PG_TRANSPARENCY_COLOUER */
#define AID_PG_ACTUAL_WIDTH   4U    /*!< \brief 4: AID_PG_ACTUAL_WIDTH */
#define AID_PG_ACTUAL_HEIGHT  5U    /*!< \brief 5: AID_PG_ACTUAL_HEIGHT */
#define AID_PG_FORMAT         6U    /*!< \brief 6: AID_PG_FORMAT */
/*!@}*/

/*! \name Number variable object attribute id's 
 @{ */
#define AID_NV_VALUE          1U    /*!< \brief 1: AID_NV_VALUE */
/*!@}*/

/*! \name Font attributes object attribute id's 
 @{ */
#define AID_FA_FONT_COLOUR    1U    /*!< \brief 1: AID_FA_FONT_COLOUR */
#define AID_FA_FONT_SIZE      2U    /*!< \brief 2: AID_FA_FONT_SIZE */
#define AID_FA_FONT_TYPE      3U    /*!< \brief 3: AID_FA_FONT_TYPE */
#define AID_FA_FONT_STYLE     4U    /*!< \brief 4: AID_FA_FONT_STYLE */
/*!@}*/

/*! \name Line attributes object attribute id's 
 @{ */
#define AID_LA_LINE_COLOUR    1U    /*!< \brief 1: AID_LA_LINE_COLOUR */
#define AID_LA_LINE_WIDTH     2U    /*!< \brief 2: AID_LA_LINE_WIDTH */
#define AID_LA_LINE_ART       3U    /*!< \brief 3: AID_LA_LINE_ART */
/*!@}*/

/*! \name Fill attributes object attribute id's 
 @{ */
#define AID_FA_FILL_TYPE      1U    /*!< \brief 1: AID_FA_FILL_TYPE */
#define AID_FA_FILL_COLOUR    2U    /*!< \brief 2: AID_FA_FILL_COLOUR */
#define AID_FA_FILL_PATTERN   3U    /*!< \brief 3: AID_FA_FILL_PATTERN */
/*!@}*/

/*! \name Input object attribute id's 
 @{ */
#define AID_IP_VALIDATION_TYPE 1U   /*!< \brief 1: AID_IP_VALIDATION_TYPE */
/*!@}*/

/*! \name Object pointer attribute id's 
 @{ */
#define AID_OP_VALUE          1U   /*!< \brief 1: AID_OP_VALUE */
/*!@}*/

/*! \name Auxiliary function type 2 object attribute id's 
 @{ */
#define AID_AUXF2_BG_COLOUR   1U    /*!< \brief 1: AID_AUXF2_BG_COLOUR */
#define AID_AUXF2_FUNCTION    2U    /*!< \brief 2: AID_AUXF2_FUNCTION */
/*!@}*/

/*! \name Auxiliary input type 2 object attribute id's 
 @{ */
#define AID_AUXI2_BG_COLOUR   1U    /*!< \brief 1: AID_AUXI2_BG_COLOUR */
#define AID_AUXI2_FUNCTION    2U    /*!< \brief 2: AID_AUXI2_FUNCTION */
/*!@}*/

/*! \name Auxiliary control designator type 2 object pointer attribute id's 
 @{ */
#define AID_AUXC2_PTR_TYPE    1U    /*!< \brief 1: AID_AUXC2_PTR_TYPE */
#define AID_AUXC2_OBJ_ID      2U    /*!< \brief 2: AID_AUXC2_OBJ_ID */
/*!@}*/

/*! \name Window mask object attribute id's 
 @{ */
#define AID_WM_BG_COLOUR      1U   /*!< \brief 1: AID_WM_BG_COLOUR */
#define AID_WM_OPTIONS        2U   /*!< \brief 2: AID_WM_OPTIONS */
#define AID_WM_NAME           3U   /*!< \brief 3: AID_WM_NAME */
/*!@}*/ 

/*! \name Key group object attribute id's 
 @{ */
#define AID_KG_OPTIONS        1U   /*!< \brief 1: AID_KG_OPTIONS */
#define AID_KG_NAME           2U   /*!< \brief 2: AID_KG_NAME */
/*!@}*/

/*! \name Graphic context attribute id's
@{ */
#define AID_GC_VP_WIDTH        1U  /*!< \brief  1: AID_GC_VP_WIDTH     */
#define AID_GC_VP_HEIGHT       2U  /*!< \brief  2: AID_GC_VP_HEIGHT    */
#define AID_GC_VP_X            3U  /*!< \brief  3: AID_GC_VP_X         */
#define AID_GC_VP_Y            4U  /*!< \brief  4: AID_GC_VP_Y         */
#define AID_GC_CANVAS_WIDTH    5U  /*!< \brief  5: AID_GC_CANVAS_WIDTH */
#define AID_GC_CANVAS_HEIGHT   6U  /*!< \brief  6: AID_GC_CANVAS_HEIGHT*/
#define AID_GC_VP_ZOOM         7U  /*!< \brief  7: AID_GC_VP_ZOOM      */
#define AID_GC_GR_CURSOR_X     8U  /*!< \brief  8: AID_GC_GR_CURSOR_X  */
#define AID_GC_GR_CURSOR_Y     9U  /*!< \brief  9: AID_GC_GR_CURSOR_Y  */
#define AID_GC_FG_COLOUR      10U  /*!< \brief 10: AID_GC_FG_COLOUR    */
#define AID_GC_BG_COLOUR      11U  /*!< \brief 11: AID_GC_BG_COLOUR    */
#define AID_GC_FONTATT        12U  /*!< \brief 12: AID_GC_FONTATT      */
#define AID_GC_LINEATT        13U  /*!< \brief 13: AID_GC_LINEATT      */
#define AID_GC_FILLATT        14U  /*!< \brief 14: AID_GC_FILLATT      */
#define AID_GC_FORMAT         15U  /*!< \brief 15: AID_GC_FORMAT       */
#define AID_GC_OPTIONS        16U  /*!< \brief 16: AID_GC_OPTIONS      */
#define AID_GC_TRANS_COLOUR   17U  /*!< \brief 17: AID_GC_TRANS_COLOUR */
/*!@}*/

/*! \name Output list object id's
@{ */
#define AID_OLA_WIDTH          1U  /*!< \brief 1: AID_OLA_WIDTH  */
#define AID_OLA_HEIGHT         2U  /*!< \brief 2: AID_OLA_HEIGHT */
#define AID_OLA_VARREF         3U  /*!< \brief 3: AID_OLA_VARREF */
#define AID_OLA_VALUE          4U  /*!< \brief 4: AID_OLA_VALUE  */
/*!@}*/

/*! \name Extended input attributes id's
@{ */
#define AID_EIA_VALTYPE        1U  /*!< \brief 1: AID_EIA_VALTYPE */
/*!@}*/

/*! \name Object label reference list object attribute id's 
 @{ */
#define AID_OLRL_NUMB_LABLED_OBJ    1U   /*!< \brief 1: AID_OLRL_NUMB_LABLED_OBJ */
/*!@}*/

/*! \name External object attribute id's 
 @{ */
#define AID_EX_OPTIONS        1U   /*!< \brief 1: AID_EX_OPTIONS */
#define AID_EX_NAME_0         2U   /*!< \brief 2: AID_EX_NAME_0 */
#define AID_EX_NAME_1         3U   /*!< \brief 3: AID_EX_NAME_1 */
/*!@}*/

/*! \name External reference name object attribute id's 
 @{ */
#define AID_EXRN_OPTIONS      1U   /*!< \brief 1: AID_EXRN_OPTIONS */
#define AID_EXRN_NAME_0       2U   /*!< \brief 2: AID_EXRN_NAME_0 */
#define AID_EXRN_NAME_1       3U   /*!< \brief 3: AID_EXRN_NAME_1 */
/*!@}*/

/*! \name External object pointer object attribute id's 
 @{ */
#define AID_EXOP_DEF_OBJ_ID      1U   /*!< \brief 1: AID_EXOP_DEF_OBJ_ID */
#define AID_EXOP_EXT_REF_NAME_ID 2U   /*!< \brief 2: AID_EXOP_EXT_REF_NAME_ID */
#define AID_EXOP_EXT_OBJ         3U   /*!< \brief 3: AID_EXOP_EXT_OBJ */
/*!@}*/

/*! \name Animation object id's
@{ */
#define AID_AO_WIDTH          1U    /*!< \brief  1: AID_AO_WIDTH        */
#define AID_AO_HEIGHT         2U    /*!< \brief  2: AID_AO_HEIGHT       */
#define AID_AO_REFRESHINT     3U    /*!< \brief  3: AID_AO_REFRESHINT   */
#define AID_AO_VALUE          4U    /*!< \brief  4: AID_AO_VALUE        */
#define AID_AO_ENABLED        5U    /*!< \brief  5: AID_AO_ENABLED      */
#define AID_AO_FICHILDINDEX   6U    /*!< \brief  6: AID_AO_FICHILDINDEX */
#define AID_AO_LACHILDINDEX   7U    /*!< \brief  7: AID_AO_LACHILDINDEX */
#define AID_AO_DEFCHILDINDEX  8U    /*!< \brief  8: AID_AO_DEFCHILDINDEX*/
#define AID_AO_OBJECTS        9U    /*!< \brief  9: AID_AO_OBJECTS      */
/*!@}*/

/*! \name Colour palette object id's
@{ */
#define AID_CP_OPTIONS        1U    /*!< \brief 1: AID_CP_OPTIONS   */
/*!@}*/


/*! \name Graphic data object (PNG) id's
@{ */
#define AID_GD_FORMAT         1U    /*!< \brief 1: AID_GD_FORMAT  */
/*!@}*/

/*! \name Scaled Graphic object id's
@{ */
#define AID_SG_WIDTH         1U    /*!< \brief 1: AID_SG_WIDTH      */
#define AID_SG_HEIGHT        2U    /*!< \brief 2: AID_SG_HEIGHT     */
#define AID_SG_SCALE_TYPE    3U    /*!< \brief 3: AID_SG_SCALE_TYPE */
#define AID_SG_OPTIONS       4U    /*!< \brief 4: AID_SG_OPTIONS    */
#define AID_SG_VALUE         5U    /*!< \brief 5: AID_SG_VALUE      */
/*!@}*/

/*! \name Working Set Special Controls object id's
@{ */
#define AID_WSSC_NUMOFBYTES  1U    /*!< \brief 1: AID_WSSC_NUMOFBYTES     */
#define AID_WSSC_COLOUR_MAP  2U    /*!< \brief 2: AID_WSSC_COLOUR_MAP     */
#define AID_WSSC_COLOUR_PALETTE 3U /*!< \brief 3: AID_WSSC_COLOUR_PALETTE */
/*!@}*/

/** @} */ /* END gr_isovt_aids */
#endif /* ISOVT_AID_DEFINES */
/* ************************************************************************ */

#endif    /* not: defined(CCI_USE_NAMESPACE) && defined(__cplusplus) */

/** @} */ /* END poolmani */


/* ************************************************************************ */
/*! \addtogroup grp_vtcl_gaux
    \brief Client to connect and upload an object pool to an graphical auxiliary input device

    Can be enabled with the IsoConf.h define #ISO_VTC_GRAPHIC_AUX.

    @{
*/
/* **************************** defines *********************************** */
#if defined(DOXYGEN) 
/*! \brief Enable graphical auxiliary VT client functionality. */
#define ISO_VTC_GRAPHIC_AUX
/*! \brief Enables the proprietary assignment functionality between the graphical auxiliary client 
           and the graphical auxiliary input unit.
    \details If enabled and supported by the input unit, the graphical auxiliary client 
    can send the preferred assignment directly to the VT service of the input unit 
    and it accepts the assignment commands of the input unit.
*/
#define ISO_VTC_GRAPHIC_AUX_DIRECT_ASSIGN
#endif 

/*!
   \name   Configuration:
   \brief  The following define can be set by the application
   @{
   \def ISO_VTC_GAUX_CLIENTS_MAX
   \brief   Number of internal graphical auxiliary VT clients
   \def ISO_VTC_GAUX_SERVERS_MAX
   \brief   Number of external graphical auxiliary VT servers
   \def ISO_VTC_GAUX_CONNECTIONS_MAX
   \brief   Maximum number of possible connections between all clients and servers
   \details Should be (ISO_VTC_GAUX_CLIENTS_MAX * ISO_VTC_GAUX_SERVERS_MAX)
   \def ISO_VTC_GAUX_WSVERSION
   \brief   Working set (VT) version for graphical auxiliary clients
   @}
*/
#if !defined(ISO_VTC_GAUX_WSVERSION)
   #if !defined(ISO_VTVERSION)
      #ifdef ISO_VTC_UT3
         #define ISO_VTC_GAUX_WSVERSION   (6u)   
      #else
         #define ISO_VTC_GAUX_WSVERSION   (3u)   
      #endif /* ISO_VTC_UT3 */
   #else    /* defined(ISO_VTVERSION) */
      #define ISO_VTC_GAUX_WSVERSION   (ISO_VTVERSION)
   #endif   /* defined(ISO_VTVERSION) */
#endif   /* !defined(ISO_VTC_GAUX_WSVERSION) */

#if !defined(ISO_VTC_GAUX_CLIENTS_MAX)
   #define ISO_VTC_GAUX_CLIENTS_MAX  4u
#endif   /* !defined(ISO_VTC_GAUX_CLIENTS_MAX) */

#if !defined(ISO_VTC_GAUX_SERVERS_MAX)
   #define ISO_VTC_GAUX_SERVERS_MAX  4u
#endif   /* !defined(ISO_VTC_GAUX_SERVERS_MAX) */

#if !defined(ISO_VTC_GAUX_CONNECTIONS_MAX)
   #define ISO_VTC_GAUX_CONNECTIONS_MAX  16u
#endif   /* !defined(ISO_VTC_GAUX_CONNECTIONS_MAX) */


/* **************************** constants ********************************* */

/* **************************** type definitions ************************** */
/*! \brief Graphical auxiliary client connection command enumeration */
typedef enum
{
   IsoVtcAux_ConnOpen = 0,       /*!< \brief Restart only the state machine of closed connection */
   IsoVtcAux_ConnReopen = 1,     /*!< \brief Restart the state machine of an active or closed connection */
   IsoVtcAux_ConnClose = 2,      /*!< \brief Close an active connection to the VT server of an GAux client */
   IsoVtcAux_ConnWait = 3,       /*!< \brief Set the state machine on hold (Wait for continue) */
   IsoVtcAux_ConnContinue = 4    /*!< \brief Continue processing */

} IsoVtcGAux_ConnCmd_eT;

/*! \brief Graphical auxiliary client connection event enumeration */
typedef enum
{
   IsoVtcAux_EvReadyToConnect,      /*!< \brief Ready to connect to server (New connection or restart) */
   IsoVtcAux_EvGetVersions,         /*!< \brief Stored version strings received */
   IsoVtcAux_EvWaitForPool,         /*!< \brief Waiting for a pool to upload */
   IsoVtcAux_EvActivated,           /*!< \brief Running state (pool (up)load finished)  */
   IsoVtcAux_EvAborted,             /*!< \brief Connection aborted (will be restarted) */
   IsoVtcAux_EvSafeState            /*!< \brief Connection disabled (will not automatically restarted */
} IsoVtcGAux_EventId_eT;

/*!< \brief Graphical auxiliary client connection event message */
typedef struct
{
   IsoVtcGAux_EventId_eT   eEventId;      /*!< \brief Event type identifier */
   iso_u8                  u8ConnHnd;     /*!< \brief Connection handle (Instance identifier) */
   iso_s16                 s16WsCfHnd;    /*!< \brief CF handle of the client */
   iso_s16                 s16VtCfHnd;    /*!< \brief CF handle of the server */
   iso_u16                 u16DataSize;   /*!< \brief  > 0 for Event specific data else 0 */
   const iso_u8 HUGE_C    *pau8Data;      /*!< \brief  if u16DataSize > 0 pointer to Event specific data else NULL pointer */
   ISO_USER_PARAM_T        userParam;     /*!< \brief User parameter */
} IsoVtcGAux_ConnEv_Ts;

/* old: typedef iso_s16 (*IsoVtcGAuxMsgCb_fpt)(const ISOVT_MSG_STA_T *psMsg);
   new  typedef void    (*IsoVtcGAuxMsgCb_fpt)(const ISOVT_MSG_STA_T *psMsg); */
/*! \brief Type definition of the graphical auxiliary F-command message response callback function */
typedef ISOVT_CbMsg_t IsoVtcGAuxMsgCb_fpt;

/*!< \brief Type definition of the graphical auxiliary client connection event message callback function */
typedef iso_s16 (*IsoVtcGAuxEventCb_fpt)(const IsoVtcGAux_ConnEv_Ts *psEvent);

/* **************************** functions ********************************* */

/* ************************************************************************ */
/*!
   \brief   Set the direct load pool transfer repetition value for one loop

   \param[in]    \wp{s16DTSpeed, iso_s16}  
                   Number of cyclic calls in one loop to speed up the transport\n  
                   Range: 1 - about 10 (depends on #ISO_VTPO_TP_BUFFER_SIZE, and the size of the pool objects ..) \n
                   Default: 1         
   \retval       iso_s16                        
                   - #E_NO_ERR on success 
                   - #E_RANGE on s16DTSpeed is not valid.   
   \details    The value is used  as in the state TPBuffScanSeg to loop over up to s16DTSpeed pool objects
               to fill the internal TP pool buffer. The loop is also terminated if the TP pool buffer is full
               or the last object of the current pool data block is processed.  \n
               See also #ISO_VTPO_TP_BUFFER_SIZE and IsoVtcGAux_PoolInitDirectTransfer().
   \note Deprecated: Use IsoVtcPoolSetDTRepeatRate()
*/
ISO_DEPRECATED
ISO_CLIENT_API
iso_s16 IsoVtcGAux_SetPoolServiceDTRepeatRate(iso_s16 s16DTSpeed);

/* ************************************************************************ */
/*!
   \brief   Initialisation of a graphical auxiliary client
   
            With this function a VT-Client CF is added to the list of instances 
            which supports "VT server" connections to graphical auxiliary input devices.


   \param[in]    \wp{s16CfHandleMaster, iso_s16}
                  CF handle of the internal client (working set master)
   \param[in]  \wpp{userParam, const #ISO_USER_PARAM_T}
                  User parameter value for the callback function calls. \n
                  Use #ISO_USER_PARAM_DEFAULT if not used/needed.
   \param[in]    \wp{fpEventCb, IsoVtcGAuxEventCb_fpt}
                  Pointer to the application specific event callback function.
   \param[in]    \wp{fpMsgCb, IsoVtcGAuxMsgCb_fpt}
                  Pointer to the application specific message callback function. \n
                  (currently not needed. preparation for next release) 

   \retval  iso_s16
            - #E_NO_ERR on success
            - #E_CONFIG if driver module not initialized
            - #E_OVERFLOW if internal storage array is full
            - #E_RANGE if one ore more parameters are not valid
            - #E_WARN  if the specified CF handle has already been added

*/
ISO_CLIENT_API
iso_s16 IsoVtcGAux_CfInit(iso_s16             s16CfHandleMaster,
                             const ISO_USER_PARAM_T userParam,
                             IsoVtcGAuxEventCb_fpt  fpEventCb, 
                             IsoVtcGAuxMsgCb_fpt    fpMsgCb);

/* ************************************************************************ */
/*!
   \brief   Set the connection states of a graphical auxiliary client

   \param[in]    \wp{s16CfHandleMaster, iso_s16}
                  CF handle of the internal client (working set master)
   \param[in]  \wpp{eCmd, IsoVtcGAux_ConnCmd_eT}
                  Connection command. 

   \retval  iso_s16
            - #E_NO_ERR on success
            - #E_CONFIG if driver module not initialized
            - #E_RANGE if one ore more parameters are not valid
            - #E_NOACT if the command can not be triggered in the current state
*/
ISO_CLIENT_API
iso_s16 IsoVtcGAux_SetAllConnections(iso_s16 s16CfHandleMaster, IsoVtcGAux_ConnCmd_eT eCmd);

/* ************************************************************************ */
/*!
   \brief   Set the connection states of a graphical auxiliary client connection

   \param[in]   \wp{u8ConnHnd, iso_u8}
                     Handle of the connection
   \param[in]  \wpp{eCmd, IsoVtcGAux_ConnCmd_eT}
                  Connection command. 

   \retval  iso_s16
            - #E_NO_ERR on success
            - #E_NO_INSTANCE if the connection handle is not valid
            - #E_RANGE if one ore more parameters are not valid
            - #E_NOACT if the command can not be triggered in the current state
*/
ISO_CLIENT_API
iso_s16 IsoVtcGAux_SetConnection(iso_u8 u8ConnHnd, IsoVtcGAux_ConnCmd_eT eCmd);

/* ************************************************************************ */
/*!
   \brief   Forwards a received auxiliary assignment message to the VT server 
            of a graphical auxiliary input device.

   \param[in]    \wp{s16CfHandleMaster, iso_s16}
                  CF handle of the internal client (working set master)
   \param[in]  \wpp{pVtMsg, const #ISOVT_MSG_STA_T*}
                  Pointer to the received aux assignment message
   \param[in]    \wp{qCheckConnection, iso_bool}
                 - #ISO_TRUE to forward the message only if the client has already a connection to the device.
                 - #ISO_FALSE forward the message also without a connection

   \retval  iso_s16
            - #E_NO_ERR on success
            - #E_CONFIG if driver module not initialized
            - #E_NOACT if not connected and qCheckConnection is ISO_TRUE
            - #E_OVERFLOW send buffer full
            - #E_RANGE if one ore more parameters are not valid
            - else other error

*/
ISO_CLIENT_API
iso_s16 IsoVtcGAux_ForwardAssignment(iso_s16     s16CfHandleMaster,
                                        const ISOVT_MSG_STA_T* pVtMsg,
                                        iso_bool qCheckConnection);

/* ************************************************************************ */
/*!
   \brief   Sends an auxiliary assignment message to the VT server 
            of a graphical auxiliary input device.

   \param[in]    \wp{s16CfHandleMaster, iso_s16}
                  CF handle of the internal client (working set master)
   \param[in]    \wp{s16CfHandleGAux, iso_s16}
                  CF handle of the external auxiliary input device
   \param[in]    \wp{u8Flags, iso_u8}
                 Flags (see byte 10 of the Auxiliary Assignment Type 2 command)  
   \param[in]    \wp{u16IdInput, iso_u16}
                  Auxiliary type 2 input pool object ID
   \param[in]    \wp{u16IdFunction, iso_s16}
                  Auxiliary type 2 function pool object ID
   \param[in]    \wp{qCheckConnection, iso_bool}
                 - #ISO_TRUE to forward the message only if the client has already a connection to the device.
                 - #ISO_FALSE forward the message also without a connection
 
  \retval  iso_s16
            - #E_NO_ERR on success
            - #E_CONFIG if driver module not initialized
            - #E_NOACT if not connected and qCheckConnection is ISO_TRUE
            - #E_OVERFLOW send buffer full
            - #E_RANGE if one ore more parameters are not valid
            - else other error

*/
ISO_CLIENT_API
iso_s16 IsoVtcGAux_SendAssignment(iso_s16 s16CfHandleMaster,   /* sender: internal CF (implement) */
                                     iso_s16 s16CfHandleGAux,     /* receiver: external graphical aux unit (VT service) */  
                                     iso_u8  u8Flags, 
                                     iso_u16 u16IdInput, 
                                     iso_u16 u16IdFunction,
                                     iso_bool qCheckConnection);


#if defined(ISO_VTC_GRAPHIC_AUX_DIRECT_ASSIGN)
/* ************************************************************************ */
/*!
   \brief Set preferred assignment callback function.

   \param[in]  \wp{s16CfHandleMaster, iso_s16}
                CF handle of the internal client (working set master)
   \param[in]  \wp{pfAuxPrefAssignCb, ISOVT_CbAuxPrefAssignment_t}
                Pointer to the callback function.
   \retval iso_s16
                - E_NO_ERR
                - E_NO_INSTANCE
    The function should be called after IsoVtcGAux_CfInit() to set the preferred assignment callback function.
    The GAUX instances will call this function every time before sending the preferred assignment to the GAUX VT service.
    To trigger the preferred assignment sending use IsoVtcAuxPrefAssignmentTrigger().
*/
ISO_CLIENT_API
iso_s16 IsoVtcGAux_SetPrefAssignmentCb(iso_s16 s16CfHandleMaster, ISOVT_CbAuxPrefAssignment_t pfAuxPrefAssignCb);
#endif /* defined(ISO_VTC_GRAPHIC_AUX_DIRECT_ASSIGN) */

/* ************************************************************************ */
/*!
   \brief   Determining the number of objects in the pool

    This function counts the number of objects in a pool.

   \param[in]   \wp{au8Pool, iso_u8 HUGE_C[]}
                  Pointer on first byte of pool data array
   \param[in]    \wp{u32Size, iso_u32}
                  Size of pool in bytes

   \retval     iso_u16  
               Number of objects in pool
   \par
         This function can be used before IsoVtcGAux_PoolInit() 
         for determining the number of objects in a pool.
*/
ISO_CLIENT_API
iso_u16 IsoVtcGAux_GetNumberOfPoolObjects(const iso_u8 HUGE_C au8Pool[], iso_u32 u32Size);

/* ************************************************************************ */
/*!
   \brief  Set object pool version label

   \param[in]   \wp{u8ConnHnd, iso_u8}
                     Handle of the connection
   \param[in]   \wp{u8VersionLabelSize, iso_u8}
                  Length of the version label \n
                  Range: 7-32 bytes (normally 7 or 32 bytes)
   \param[in]  \wpp{au8VersionLabel, const #iso_u8[]}
                  Pointer to the label data byte array

   \retval     iso_s16  
               - #E_NO_ERR on success
               - #E_RANGE  if one or more parameters are not valid
   \par
         The Label must be set before calling one of the IsoVtcGAux_PoolInit() functions. 
*/
ISO_CLIENT_API
iso_s16 IsoVtcGAux_PoolSetVersionLabel(iso_u8 u8ConnHnd, iso_u8 u8VersionLabelSize, const iso_u8 au8VersionLabel[]);

/* ************************************************************************ */
/*!
   \brief  Set object pool configuration

   \param[in]   \wp{u8ConnHnd, iso_u8}
                     Handle of the connection
   \param[in]   \wp{eGraphicType, ISOGRAPH_TYPE_e}
                     Graphic type of this pool ( monochrome, colour_16, colour_256 )
   \param[in]   \wp{u8DesignatorWidth, iso_u8}
                     Soft key designator width of this pool - minimum == 60 
   \param[in]   \wp{u8DesignatorHeight, iso_u8}
                     Soft key designator height of this pool - minimum == 32
   \param[in]   \wp{u16MaskSize, iso_u16}
                     Data (and Alarm) Mask size of this pool \n
                     Range: Minimum 200 - Maximum (undefined depends on physical VTs)

   \retval     iso_s16  
               - #E_NO_ERR on success
               - #E_RANGE  if one or more parameters are not valid
   \par
         The configuration must be set before calling one of the IsoVtcGAux_PoolInit() functions.
         The configuration must match with the pool which should be uploaded.
*/
ISO_CLIENT_API
iso_s16 IsoVtcGAux_PoolSetConfig(iso_u8 u8ConnHnd, ISOGRAPH_TYPE_e eGraphicType,
   iso_u8  u8DesignatorWidth, iso_u8  u8DesignatorHeight, iso_u16 u16MaskSize);

/* **************************************************************************************** */
/*!
   \brief       Initializes the object pool transfer to the server

   \param[in]  \wp{u8ConnHnd, iso_u8}
                  Handle of the connection
   \param[in]  \wp{eTransferMode, ISOVT_POOL_TRANSFER_MODE_e}
                  Transfer mode which should be used for the object pool upload
   \param[in]  \wpp{au8PoolData, const #iso_u8 HUGE_C[]}
                  Pointer to pool data in flash \n
                  Needed only for #PoolTransferFlash (or PoolTransferRaw) else not needed (use NULL pointer)
   \param[in]  \wp{u32PoolSize,  iso_u32}
                  Size of the object pool in bytes. Needed only for #PoolTransferFlash (or PoolTransferRaw) \n
                  Range: 1 - 117440512 or 0UL if not used
   \param[in]  \wp{u32BufferOffset, iso_u32}
                  Used only by #PoolTransferSeqmented and #PoolTransferDataBlocks
                  Buffer offset into Pool buffer -> Start address for load objects \n
                  Details see help - VT client/VT Pool Manipulation/.. 
   \param[in]  \wp{u16MaxTime, iso_u16}
                  Used only by #PoolTransferDirectLoad \n
                  Maximum time in milliseconds the application needed to load the next pool objects for the driver. \n
                  - 0: The driver has direct access to the pool data memory
                  - else: The application copies the data in a memory zone where the driver has direct access. \n
                    Range: Minimum 0 - Maximum (undefined depends on the ECU hardware)
   \param[in]  \wp{pfPoolLoadCb, ISO_POOL_CALLBACK_t }
                  Callback function pointer for the object pool data requests. \n
                  Needed for PoolTransferSeqmented, PoolTransferDirectLoad and PoolTransferDataBlocks

   \retval     iso_s16
               - #E_NO_ERR on success
               - #E_NO_INSTANCE if the connection handle is not valid
               - #E_RANGE if one or more parameters are not valid
               - #E_CONFIG if the pool configuration or version label is not valid
               - #E_NOACT  if not compiled to use this mode
   \par
         The pool configuration and the version label must be set before calling this functions
         (see IsoVtcGAux_PoolSetConfig(), IsoVtcGAux_PoolSetVersionLabel()).
*/
ISO_CLIENT_API
iso_s16 IsoVtcGAux_PoolLoad(iso_u8 u8ConnHnd, ISOVT_POOL_TRANSFER_MODE_e eTransferMode,
   const iso_u8 HUGE_C au8PoolData[], iso_u32 u32PoolSize,
   iso_u32 u32BufferOffset, iso_u16 u16MaxTime, ISO_POOL_CALLBACK_t pfPoolLoadCb);

/* ************************************************************************ */
/*!
   \brief  Initializes the standard object pool upload to the server

   \param[in]   \wp{u8ConnHnd, iso_u8}
                     Handle of the connection
   \param[in]  \wpp{au8PoolData, const #iso_u8 HUGE_C[]}
                     Pointer to the pool data array
   \param[in]   \wp{u16NumberObjects, iso_u16}
                     Number of objects in this pool. \n
                     Can be determined with IsoVtcGAux_GetNumberOfPoolObjects().
   \param[in]   \wp{pfCBPoolLoad, ISO_POOL_CALLBACK_t}
                     Optional pointer to the pool service callback function to get the service events.
                     Can be set to NULL pointer if not needed.

   \retval     iso_s16  
               - #E_NO_ERR on success
               - #E_NO_INSTANCE if the connection handle is not valid
               - #E_RANGE  if one or more parameters are not valid
               - #E_CONFIG if the pool configuration or version label is not valid
               - #E_NOACT  if not compiled to use this mode ( ISO_POOL_BUFFERED_LOAD not defined)
               - #E_OVERFLOW if no external pool buffer was set with IsoPoolSetBuffer()

   \par
         The pool configuration and the version label must be set before calling this functions.
         (see IsoVtcGAux_PoolSetConfig(), IsoVtcGAux_PoolSetVersionLabel())
   \note Deprecated: Use IsoVtcGAux_PoolLoad()
*/
ISO_DEPRECATED
ISO_CLIENT_API
iso_s16 IsoVtcGAux_PoolInit(iso_u8 u8ConnHnd,
   const iso_u8 HUGE_C au8PoolData[], iso_u16  u16NumberObjects,
   ISO_POOL_CALLBACK_t pfCBPoolLoad);


/* ************************************************************************ */
/*!
   \brief  Initializes the raw object pool upload to the server

   In this mode the pool is transmitted without any manipulations.

   \param[in]   \wp{u8ConnHnd, iso_u8}
                     Handle of the connection
   \param[in]  \wpp{au8PoolData, const #iso_u8 HUGE_C[]}
                     Pointer to the pool data array
   \param[in]   \wp{u32PoolSize, iso_u32}
                     Size of the pool data array).
   \param[in]   \wp{u16NumberObjects, iso_u16}
                     Number of objects in this pool. \n
                     Can be determined with IsoVtcGAux_GetNumberOfPoolObjects().
   \param[in]   \wp{pfCBPoolLoad, ISO_POOL_CALLBACK_t}
                     Optional pointer to the pool service callback function to get the service events.
                     Can be set to NULL pointer if not needed.

   \retval     iso_s16  
               - #E_NO_ERR on success
               - #E_NO_INSTANCE if the connection handle is not valid
               - #E_RANGE  if one or more parameters are not valid
               - #E_CONFIG if the pool configuration or version label is not valid

   \par
         The pool configuration and the version label must be set before calling this functions.
         (see IsoVtcGAux_PoolSetConfig(), IsoVtcGAux_PoolSetVersionLabel())
   \note Deprecated: Use IsoVtcGAux_PoolLoad()
*/
ISO_DEPRECATED
ISO_CLIENT_API
iso_s16 IsoVtcGAux_PoolInitRaw(iso_u8 u8ConnHnd,
   const iso_u8 HUGE_C au8PoolData[], iso_u32 u32PoolSize, iso_u16  u16NumberObjects,
   ISO_POOL_CALLBACK_t pfCBPoolLoad);

/* ************************************************************************ */
/*!
   \brief  Initializes the direct transfer object pool upload to the server

   In this mode the pool is transmitted without using the big internal pool buffer.
   It uses only a small buffer to store some TP packages (default 16 bytes).
   The pool data given with the callback function must contain one or more complete objects.

   \param[in]   \wp{u8ConnHnd, iso_u8}
                     Handle of the connection
   \param[in]   \wp{u16MaxTime, iso_u16}
                     Maximum time in milliseconds the application needed to load the next pool objects for the pool service. \n
                     - 0: The service has direct access to the pool data memory
                     - else: The application copies the data in a memory zone where the service has direct access. \n
                     Range: Minimum 0 - Maximum (undefined depends on the ECU hardware)
   \param[in]   \wp{pfCBPoolLoad, ISO_POOL_CALLBACK_t}
                    Pointer to the pool service callback function
                    which should be called for requesting the pool data.

   \retval     iso_s16  
               - #E_NO_ERR on success
               - #E_NO_INSTANCE if the connection handle is not valid
               - #E_RANGE  if one or more parameters are not valid
               - #E_CONFIG if the pool configuration or version label is not valid
               - #E_NOACT  if not compiled to use this mode ( ISO_POOL_BUFFERED_LOAD not defined)

   \par
         The pool configuration and the version label must be set before calling this functions.
         (see IsoVtcGAux_PoolSetConfig(), IsoVtcGAux_PoolSetVersionLabel()) \n
   \note Deprecated: Use IsoVtcGAux_PoolLoad()
*/
ISO_DEPRECATED
ISO_CLIENT_API
iso_s16 IsoVtcGAux_PoolInitDirectTransfer(iso_u8 u8ConnHnd,
   iso_u16   u16MaxTime, ISO_POOL_CALLBACK_t pfCBPoolLoad);

/* ************************************************************************ */
/*!
   \brief  Initializes the segmented object pool upload to the server


   \param[in]   \wp{u8ConnHnd, iso_u8}
                     Handle of the connection
   \param[in]   \wp{u32BuffOffset, iso_u32}
                     Offset to the pool buffer -> start address/index for loaded objects \n
                     see also IsoVtcPoolInitSegmented()
   \param[in]   \wp{u16NumberObjects, iso_u16}
                     Number of objects in this pool. 
   \param[in]   \wp{pfCBPoolLoad, ISO_POOL_CALLBACK_t}
                    Pointer to the pool service callback function
                    which should be called for getting the pool data.

   \retval     iso_s16  
               - #E_NO_ERR on success
               - #E_NO_INSTANCE if the connection handle is not valid
               - #E_RANGE  if one or more parameters are not valid
               - #E_CONFIG if the pool configuration or version label is not valid
               - #E_NOACT  if not compiled to use this mode ( ISO_POOL_BUFFERED_LOAD not defined)
               - #E_OVERFLOW if no external pool buffer was set with IsoPoolSetBuffer()

   \par
         The pool configuration and the version label must be set before calling this functions 
         (see IsoVtcGAux_PoolSetConfig(), IsoVtcGAux_PoolSetVersionLabel()).
         Add the define #ISO_POOL_DIRECT_LOAD to IsoConf.h to enable the "Direct Pool Transfer" mode
         for pictures which are bigger than the internal pool buffer.
   \note Deprecated: Use IsoVtcGAux_PoolLoad()
*/
ISO_DEPRECATED
ISO_CLIENT_API
iso_s16 IsoVtcGAux_PoolInitSegmented(iso_u8 u8ConnHnd,
   iso_u32 u32BuffOffset, iso_u16 u16NumberObjects, ISO_POOL_CALLBACK_t pfCBPoolLoad);

/* ************************************************************************ */
/*!
   \brief      Requesting some important and needed values from the pool - see ISOPOOLINFO_e

   \param[in]  \wp{u8ConnHnd, iso_u8}
                Handle of the connection
   \param[in]   \wp{ePoolReading, ISOPOOLINFO_e }
               Enumeration which includes all value which can be requested

   \code
      - PoolROMSize               - Size of original pool
      - PoolRAMSize               - Pool size, only valid after download !!!
      - ObjIDWorkingSet           - Object identifier of working set
      - ObjIDFirstDataMask        - First data mask
      - PoolGraphicType           - Graphic type of pool 
      - PoolDataMaskScalFaktor    - Scaling factor of data mask (after IsoVtcGAux_PoolInit() )
      - PoolSoftKeyMaskScalFaktor - Scaling factor of soft key mask (after IsoVtcGAux_PoolInit() )
      - BufferUsed                - Number of bytes in pool buffer
   \endcode
   \retval               iso_u32
                          - Wished value or 0 if not possible to return the value....
*/
ISO_CLIENT_API
iso_u32 IsoVtcGAux_PoolReadInfo(iso_u8 u8ConnHnd, ISOPOOLINFO_e ePoolReading);

/* ************************************************************************ */
/*!
   \brief       Setting scaling factor and the characteristics of a object ID range

   This function is used for control the manipulation of the driver with pool objects.
   First two parameter determines the range of IDs. Start ID and end ID same value means
   only one Object ID.

   \param[in]   \wp{u8ConnHnd, iso_u8}
                     Handle of the connection
   \param[in]   \wp{u16StartId, iso_u16}
                     Object ID - Start ID of range \n
                     Range: 0 - 65535
   \param[in]   \wp{u16EndId, iso_u16}
                     Object ID - End ID of range \n
                     Range: 0 - 65535 \n
                     Object ID must be identical or greater than Start ID
   \param[in]   \wp{u16ManipulValue, iso_u16}
                     Manipulation value for this range depending of manipulation range: \n
   \code
   - Scaling factor for modes "Scaling" and "Centering" 10000 means factor 1, 20000 means factor 2 ...
   - Target objectID of moved range for "LoadMoveID"
   - Target objectID of copied range for "LoadCopyID"
   - Colour depth see ISOGRAPH_TYPE_e for mode "ColourReduction" ( only pictures )
   - Dont care for other modes
   \endcode
   \param[in]   \wp{eModeMani, ISOPOOLMANIMODE_e}
                       Manipulation mode ( NoScaling, Scaling, Centering, NotLoad, Proprietary,
                       LoadMoveID, LoadCopyID, ColourReduction, AuxToV2 )

   \retval             iso_s16
                       - E_NO_ERR       - OK
                       - E_OVERFLOW     - Setting not possible because list is full
                       - E_NO_INSTANCE
   \note  \par
       - Every call of this function is entried in a struct. Take care that the define
         ISO_NO_SCALING_ELEMENTS_MAX is sufficient. This value defines the maximum number
         of Ranges.
       - LoadCopyID can be used multiple for the same object(s) ( -> define ISO_POOLNUMANICOPY!! )
*/
ISO_CLIENT_API
iso_s16 IsoVtcGAux_PoolSetIDRangeMode(iso_u8 u8ConnHnd,
   iso_u16 u16StartId, iso_u16 u16EndId, iso_u16 u16ManipulValue, ISOPOOLMANIMODE_e eModeMani);

/* ************************************************************************ */
/*! @} */ /* END grp_vtcl_gaux                                                       */
/* ************************************************************************ */
#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* DEF_IsoVtcApi_H */
/* ************************************************************************ */
