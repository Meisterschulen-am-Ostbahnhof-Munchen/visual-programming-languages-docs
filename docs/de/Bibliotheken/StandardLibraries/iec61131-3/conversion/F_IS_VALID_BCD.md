# F_IS_VALID_BCD

![F_IS_VALID_BCD](F_IS_VALID_BCD.svg)

* * * * * * * * * *
## Einleitung

Der `F_IS_VALID_BCD` prüft, ob eine Bitfolge gültige BCD-Daten (Binary Coded Decimal) enthält — also ob jede Nibble (4-Bit-Gruppe) einen Wert zwischen `0` und `9` darstellt. Er dient der Validierung von BCD-kodierten Werten vor deren Konvertierung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Prüfung aus, trägt `IN`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **IN** (ANY_BIT): Die zu prüfende Bitfolge (`BYTE`, `WORD`, `DWORD` oder `LWORD`).

### **Daten-Ausgänge**

- **OUT** (BOOL): `TRUE`, wenn jede Nibble von `IN` einen gültigen BCD-Wert (`0`–`9`) enthält; `FALSE`, wenn mindestens eine Nibble einen ungültigen Wert (`10`–`15`, entspricht `A`–`F`) enthält.

## Funktionsweise

Bei Eintreffen von `REQ` prüft die Algorithmus-ST-Anweisung `OUT := IS_VALID_BCD(IN)` nibble-weise, ob alle 4-Bit-Gruppen von `IN` gültige Dezimalziffern (`0`–`9`) darstellen, und gibt das Ergebnis über `OUT` aus. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **`ANY_BIT`-Eingang**: Akzeptiert Bitfolgen beliebiger Breite (`BYTE`, `WORD`, `DWORD`, `LWORD`), die Anzahl der geprüften Nibbles ergibt sich aus deren Größe.
- **Vorabprüfung für BCD-Konvertierung**: Sinnvolle Ergänzung zu den `*_BCD_TO_*`-Konvertierungsbausteinen (vgl. `F_BYTE_BCD_TO_USINT` etc.), um ungültige Eingabedaten vor der eigentlichen Konvertierung abzufangen.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Prüfung und zu `CNF`.

## Anwendungsszenarien

- **Validierung von Feldbus-/Protokolldaten**, die BCD-kodiert übertragen werden, bevor sie in einen numerischen Wert umgewandelt werden.
- **Fehlererkennung** bei fehlerhaft übertragenen oder falsch interpretierten Bitfolgen, die als BCD interpretiert werden sollen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[F_IS_VALID](F_IS_VALID.md)**: dieselbe Grundidee der Gültigkeitsprüfung, jedoch für Gleitkommazahlen statt BCD-Bitfolgen.
- **`F_BYTE_BCD_TO_USINT`** und verwandte Konvertierungsbausteine: nutzen implizit dieselbe BCD-Gültigkeitsannahme; `F_IS_VALID_BCD` macht die Prüfung explizit und vorgelagert nutzbar.

## Fazit

`F_IS_VALID_BCD` liefert eine einfache Vorabprüfung für BCD-kodierte Bitfolgen und schützt nachgeschaltete BCD-Konvertierungsbausteine vor ungültigen Eingabedaten.
