```{index} pair: isobus; Q_Attribute
Q_Attribute
```
# Q_Attribute

![](https://user-images.githubusercontent.com/69573151/212329228-8c605296-7915-4def-a497-2860e14ae509.png)

ISO 11783-6

Command change attribute( Part 6 - F.38 )

This command is used to change any attribute with an assigned AID. This message cannot be used to change strings.

Return values

iso_s16

*   [E_NO_ERR](c/IsoCommonDef.md#c.E_NO_ERR) ( 0 ) - OK
*   [E_OVERFLOW](c/IsoCommonDef.md#c.E_OVERFLOW) (-6 ) - buffer overflow
*   [E_NOACT](c/IsoCommonDef.md#c.E_NOACT) (-8 ) - Command not possible in current state
*   [E_NO_INSTANCE](c/IsoCommonDef.md#c.E_NO_INSTANCE) (-21) - No VT client available

Related to: [IsoVtcCmd_Attribute](c/IsoVtcApi.md#c.IsoVtcCmd_Attribute)
