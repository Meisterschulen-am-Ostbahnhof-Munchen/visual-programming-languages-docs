
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

iso_s16 IsoVtcCmd_SelectActiveWorkingSet(iso_u8 u8Instance, const iso_u8 pau8Name[]);

#endif /* ISO_VTC_UT3 */

