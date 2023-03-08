```{index} pair: isobus; Q_Attribute
Q_Attribute
```
# Q_Attribute

![](https://user-images.githubusercontent.com/69573151/212329228-8c605296-7915-4def-a497-2860e14ae509.png)

ISO 11783-6

Command change attribute( Part 6 - F.38 )

This command is used to change any attribute with an assigned AID. This message cannot be used to change strings.

Return values

iso\_s16

*   E\_NO\_ERR - OK
*   E\_OVERFLOW - buffer overflow
*   E\_NOACT - Command not possible in current state
*   E\_NO\_INSTANCE - No VT client available
