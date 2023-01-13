

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




