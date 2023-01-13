

#define E_NO_ERR            ( 0 )  /** ( 0 ) ErrorCause: No error */
#define E_UNKNOWN_ERR       (-1 )  /** (-1 ) ErrorCause: Unknown error */
#define E_WARN              (-2 )  /** (-2 ) ErrorCause: System warnings */
#define E_DEFAULT           (-3 )  /** (-3 ) ErrorCause: Called function works with default values */
#define E_BUSY              (-4 )  /** (-4 ) ErrorCause: Repeated calling of a function */
#define E_RANGE             (-5 )  /** (-5 ) ErrorCause: One ore more input parameter wrong */
#define E_OVERFLOW          (-6 )  /** (-6 ) ErrorCause: Buffer overflow */
#define E_RD_WR             (-7 )  /** (-7 ) ErrorCause: Write- or read-error */
#define E_NOACT             (-8 )  /** (-8 ) ErrorCause: Called functionality has not been executed */
#define E_COM               (-9 )  /** (-9 ) ErrorCause: Communication error with other application hardware */
#define E_CONFIG            (-10)  /** (-10) ErrorCause: Configuration error (function call not possible ) */
#define E_CHECKSUM          (-11)  /** (-11) ErrorCause: Checksum error */
#define E_ERROR_INDI        (-16)  /** (-16) ErrorCause: ISO error indicator */
#define E_NOT_AVAILABLE     (-17)  /** (-17) ErrorCause: Parameter, value ... not available */
#define E_PGN_UNKNOWN       (-18)  /** (-18) ErrorCause: unknown PGN */
#define E_USER_ERROR        (-19)  /** (-19) ErrorCause: IsoUser unknown, not announced ... */
#define E_DATA_LINK         (-20)  /** (-20) ErrorCause: Transport protocol used ... */
#define E_NO_INSTANCE       (-21)  /** (-21) ErrorCause: Instance not found */
#define E_CANMSG_MISSED     (-22)  /** (-22) ErrorCause: CAN message was not received */
#define E_VALUE_WRONG       (-23)  /** (-23) ErrorCause: Value or parameter has the wrong value */
#define E_OUT_OF_MEMORY     (-24)  /** (-24) ErrorCause: VT, TC has run out of memory */
#define E_NACK              (-25)  /** (-25) ErrorCause: NACK or PDNACK received of bus */
#define E_RESPTOCMDERROR    (-26)  /** (-26) ErrorCause: Response to Command with ErrorCode != 0 */




