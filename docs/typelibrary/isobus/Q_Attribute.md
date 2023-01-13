### Q\_Attribute

ISO 11783-6

Command change attribute( Part 6 - F.38 )

This command is used to change any attribute with an assigned AID. This message cannot be used to change strings.

Return values

iso\_s16

*   E\_NO\_ERR - OK
*   E\_OVERFLOW - buffer overflow
*   E\_NOACT - Command not possible in current state
*   E\_NO\_INSTANCE - No VT client available
