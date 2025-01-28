# Allgemeines

## Namen

Bitte Vermeiden: ä ü ö $ % & / 


1. Namen dürfen maximal 31 Stellen lang sein. 
2. Sie können aus den Buchstaben A-Z und a-z, den Ziffern 0-9 und dem Unterstrich bestehen.
3. Die einzige Einschränkung besteht darin, dass am Anfang von Variablennamen keine Ziffern stehen dürfen; 
4. Unterstriche am Anfang von Variablennamen sind zwar erlaubt, sollten aber vermieden werden, da diese üblicherweise für Bibliotheksfunktionen reserviert sind.


### Beispiele: 

#### Erlaubt: 

`Maehwerk_links_15`

#### Verboten: 

`14_Klappung_Mähwerk`

`Klappung Maehwerk`


Quelle <https://www.grund-wissen.de/informatik/c/variablen-und-datentypen.html>

## Zahlen

&#8469; [Natürliche Zahl – Wikipedia](https://de.wikipedia.org/wiki/Nat%C3%BCrliche_Zahl)

&#8469;₀ Natürliche Zahlen inkl. Null

&#8484; [Ganze Zahl – Wikipedia](https://de.wikipedia.org/wiki/Ganze_Zahl)

&#8474; [Rationale Zahl – Wikipedia](https://de.wikipedia.org/wiki/Rationale_Zahl)

&#8477; [Reelle Zahl – Wikipedia](https://de.wikipedia.org/wiki/Reelle_Zahl)

gibt viele weitere, siehe: [Zahlenmengen ](https://www.matheretter.de/wiki/mathe-zeichen#zahlenmengen)

## Datentypen

[Integer (Datentyp) – Wikipedia](https://de.wikipedia.org/wiki/Integer_(Datentyp))

[Gleitkommazahl – Wikipedia](https://de.wikipedia.org/wiki/Gleitkommazahl)

### Datentypen in der IEC 61131-3

[Data Types](https://help.codesys.com/webapp/_cds_struct_reference_datatypes;product=codesys;version=3.5.17.0)

[https://help.codesys.com/webapp/_cds_datatype_integer;product=codesys;version=3.5.17.0](https://help.codesys.com/webapp/_cds_datatype_integer;product=codesys;version=3.5.17.0)

[Datentypen](https://content.helpme-codesys.com/de/CODESYS%20Development%20System/_cds_reference_datatypes.html)



### Datentypen in der IEC 61499

Siehe auch: IEC 61499, Table E.1



#### Datentypen zum Rechnen

| Typ | BYTE Länge | Bit Länge | Wertebereich min | Wertebereich max |
| --- | --- | --- | --- | --- |
| BOOL | 0 | 1 Bit | 0 = FALSE | 1 = TRUE |
| SINT | 1 | 8 Bit | −128 | 127 |
| INT | 2 | 16 Bit | −32.768 | 32.767 |
| DINT | 4 | 32 Bit | −2.147.483.648 | 2.147.483.647 |
| LINT | 8 | 64 Bit | −9.223.372.036.854.775.808 | 9.223.372.036.854.775.807 |
| USINT | 1 | 8 Bit | 0 | 255 |
| UINT | 2 | 16 Bit | 0 | 65.535 |
| UDINT | 4 | 32 Bit | 0 | 4.294.967.295 |
| ULINT | 8 | 64 Bit | 0 | 18.446.744.073.709.551.615 |
| REAL | 4 | 32 Bit |   |   |
| LREAL | 8 | 64 Bit |   |   |
| DATE | 8 | 64 Bit |   |   |
| TIME | 8 | 64 Bit |   |   |
| TIME\_OF\_DAY | 12 | 96 Bit | 1970-01-01-00:00:00.000 |   |
| DATE\_AND\_TIME | 20 | 160 Bit | 1970-01-01-00:00:00.000 |   |


#### Datentypen für I/O (Input / Output)

| Typ | BYTE Länge | Bit Länge | Wertebereich min | Wertebereich max |
| --- | --- | --- | --- | --- |
| BOOL | 1/8 | 1 Bit | 0 = FALSE | 1= TRUE |
| QUARTER [^1] | 1/4 | 2 Bit | 0 | 3 |
| BYTE | 1 | 8 Bit | 0 | 255 |
| WORD | 2 | 16 Bit | 0 | 65.535 |
| DWORD | 4 | 32 Bit | 0 | 4.294.967.295 |
| LWORD | 8 | 64 Bit | 0 | 18.446.744.073.709.551.615 |


[^1]: QUARTER ist nicht normativ festgelegt.


