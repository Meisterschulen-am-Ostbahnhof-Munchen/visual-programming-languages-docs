# Allgemeines

## Zahlen

[https://de.wikipedia.org/wiki/Nat%C3%BCrliche_Zahl](https://de.wikipedia.org/wiki/Nat%C3%BCrliche_Zahl)

[https://de.wikipedia.org/wiki/Ganze_Zahl](https://de.wikipedia.org/wiki/Ganze_Zahl)

[https://de.wikipedia.org/wiki/Rationale_Zahl](https://de.wikipedia.org/wiki/Rationale_Zahl)

[https://de.wikipedia.org/wiki/Reelle_Zahl](https://de.wikipedia.org/wiki/Reelle_Zahl)

## Datentypen

[https://de.wikipedia.org/wiki/Integer_(Datentyp)](https://de.wikipedia.org/wiki/Integer_(Datentyp))

[https://de.wikipedia.org/wiki/Gleitkommazahl](https://de.wikipedia.org/wiki/Gleitkommazahl)

### Datentypen in der IEC 61131-3

[https://help.codesys.com/webapp/_cds_struct_reference_datatypes;product=codesys;version=3.5.17.0](https://help.codesys.com/webapp/_cds_struct_reference_datatypes;product=codesys;version=3.5.17.0)

[https://help.codesys.com/webapp/_cds_datatype_integer;product=codesys;version=3.5.17.0](https://help.codesys.com/webapp/_cds_datatype_integer;product=codesys;version=3.5.17.0)

### Datentypen in der IEC 61499

Siehe auch: IEC 61499, Table E.1

<table><tbody><tr><td rowspan="2">Typ</td><td rowspan="2">BYTE Länge</td><td rowspan="2">Bit Länge</td><td colspan="2">Wertebereich</td></tr><tr><td>min</td><td>max</td></tr><tr><td>BOOL</td><td>0</td><td>1 Bit</td><td>0</td><td>1</td></tr><tr><td>SINT</td><td>1</td><td>8 Bit</td><td>−128</td><td>127</td></tr><tr><td>INT</td><td>2</td><td>16 Bit</td><td>−32.768</td><td>32.767</td></tr><tr><td>DINT</td><td>4</td><td>32 Bit</td><td>−2.147.483.648</td><td>2.147.483.647</td></tr><tr><td>LINT</td><td>8</td><td>64 Bit</td><td>−9.223.372.036.854.775.808</td><td>9.223.372.036.854.775.807</td></tr><tr><td>USINT</td><td>1</td><td>8 Bit</td><td>0</td><td>255</td></tr><tr><td>UINT</td><td>2</td><td>16 Bit</td><td>0</td><td>65.535</td></tr><tr><td>UDINT</td><td>4</td><td>32 Bit</td><td>0</td><td>4.294.967.295</td></tr><tr><td>ULINT</td><td>8</td><td>64 Bit</td><td>0</td><td>18.446.744.073.709.551.615</td></tr><tr><td>REAL</td><td>4</td><td>32 Bit</td><td>&nbsp;</td><td>&nbsp;</td></tr><tr><td>LREAL</td><td>8</td><td>64 Bit</td><td>&nbsp;</td><td>&nbsp;</td></tr><tr><td>DATE</td><td>8</td><td>64 Bit</td><td>&nbsp;</td><td>&nbsp;</td></tr><tr><td>TIME</td><td>8</td><td>64 Bit</td><td>&nbsp;</td><td>&nbsp;</td></tr><tr><td>TIME_OF_DAY</td><td>12</td><td>96 Bit</td><td>1970-01-01-00:00:00.000</td><td>&nbsp;</td></tr><tr><td>DATE_AND_TIME</td><td>20</td><td>160 Bit</td><td>1970-01-01-00:00:00.000</td><td>&nbsp;</td></tr><tr><td>BYTE</td><td>1</td><td>8 Bit</td><td>0</td><td>255</td></tr><tr><td>WORD</td><td>2</td><td>16 Bit</td><td>0</td><td>65.535</td></tr><tr><td>DWORD</td><td>4</td><td>32 Bit</td><td>0</td><td>4.294.967.295</td></tr><tr><td>LWORD</td><td>8</td><td>64 Bit</td><td>0</td><td>18.446.744.073.709.551.615</td></tr></tbody></table>

in 4diac ist der 64bit Typ optional, und im Moment abgeschaltet.
