# AW_TO_AB


![AW_TO_AB](./AW_TO_AB.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `AW_TO_AB` ist ein Composite-Baustein, der einen unidirektionalen WORD-Adapter (`AW`) in einen unidirektionalen BYTE-Adapter (`AB`) umwandelt. Er dient als Schnittstellenkonverter zwischen Komponenten, die auf unterschiedlichen Datentypen basieren. Die Konvertierung erfolgt durch den integrierten Standardfunktionsbaustein `F_WORD_TO_BYTE`.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Baustein besitzt keine eigenen Ereignis-Eingänge. Stattdessen wird das Triggersignal über den Adapter-Eingang `AW_IN` (Ereignis `E1`) bereitgestellt.

### **Ereignis-Ausgänge**
Der Baustein besitzt keine eigenen Ereignis-Ausgänge. Das Ergebnis wird über den Adapter-Ausgang `AB_OUT` (Ereignis `E1`) signalisiert.

### **Daten-Eingänge**
Der Baustein besitzt keine eigenen Daten-Eingänge. Der zu konvertierende WORD-Wert wird über den Adapter-Eingang `AW_IN` (Daten `D1`) bereitgestellt.

### **Daten-Ausgänge**
Der Baustein besitzt keine eigenen Daten-Ausgänge. Das konvertierte BYTE-Ergebnis wird über den Adapter-Ausgang `AB_OUT` (Daten `D1`) ausgegeben.

### **Adapter**

| Name | Richtung | Typ | Beschreibung |
|------|----------|-----|-------------|
| `AW_IN` | Socket (Eingang) | `adapter::types::unidirectional::AW` | WORD-Adapter mit einem Ereignis `E1` und einem Datenwert `D1` (WORD) |
| `AB_OUT` | Plug (Ausgang) | `adapter::types::unidirectional::AB` | BYTE-Adapter mit einem Ereignis `E1` und einem Datenwert `D1` (BYTE) |

## Funktionsweise
Der Baustein realisiert eine reine Datenkonvertierung von WORD (16 Bit) zu BYTE (8 Bit). Der Ablauf ist:
1. Ein Ereignis am Adapter-Eingang `AW_IN.E1` löst den internen Funktionsbaustein `F_WORD_TO_BYTE` aus.
2. Der Datenwert `AW_IN.D1` (WORD) wird als Eingang an `F_WORD_TO_BYTE.IN` übergeben.
3. Nach der Konvertierung wird das Ergebnis über `F_WORD_TO_BYTE.OUT` an den Adapter-Ausgang `AB_OUT.D1` weitergeleitet.
4. Der Ausgang `AB_OUT.E1` wird aktiviert, um die Fertigstellung zu signalisieren.

Die Konvertierung gemäß IEC 61131-3 liefert standardmäßig das niederwertigste Byte (Low‑Byte) des WORD-Wertes.

## Technische Besonderheiten
- **Unidirektionale Adapter**: Der Baustein arbeitet nur in einer Datenflussrichtung – vom Socket zum Plug.
- **Integrierte Konvertierung**: Die eigentliche Umwandlung erfolgt durch den etablierten Baustein `F_WORD_TO_BYTE`, sodass keine eigene Logik implementiert werden muss.
- **Datenverlust**: Da ein WORD (16 Bit) auf ein BYTE (8 Bit) abgebildet wird, gehen die oberen 8 Bit verloren. Dies muss bei der Anwendung berücksichtigt werden.
- **Paketstruktur**: Der Baustein ist im Package `adapter::conversion::unidirectional` eingeordnet und nutzt das Import `iec61131::conversion::F_WORD_TO_BYTE`.

## Zustandsübersicht
Der Composite-Baustein besitzt keinen eigenen Zustandsautomaten. Die Funktionsweise ist rein ereignisgesteuert:
- **Idle**: Warten auf ein Ereignis am Socket `AW_IN`.
- **Konvertierung aktiv**: Nach Empfang eines Ereignisses wird der interne FB `F_WORD_TO_BYTE` ausgeführt (kombinatorische Logik ohne Wartezyklen).
- **Ausgabe**: Sobald die Konvertierung abgeschlossen ist, wird das Ereignis am Plug `AB_OUT` und der neue Datenwert ausgegeben.

## Anwendungsszenarien
- **Protokollanpassung**: Wenn ein Sensor einen WORD-Wert liefert, der Aktor aber nur BYTE-fähige Adapter unterstützt.
- **Schnittstellenreduktion**: In hierarchischen Steuerungssystemen, bei denen aus Performance- oder Speichergründen auf BYTE-Größen zurückgegriffen wird.
- **Adapter-Brücke**: Als Zwischenstück in einer 4diac‑IDE‑Applikation, um Komponenten mit inkompatiblen Adaptertypen zu verbinden.

## Vergleich mit ähnlichen Bausteinen
- **`F_WORD_TO_BYTE`**: Ein reiner Datenkonvertierungsbaustein ohne Adapter-Integration. `AW_TO_AB` kapselt diesen Baustein und stellt eine standardisierte Adapter-Schnittstelle bereit.
- **`AW_TO_AW` (identischer Typ)**: Nicht sinnvoll; der vorliegende Baustein ist speziell für die Typumwandlung konzipiert.
- **Manuelle Konvertierung**: Ohne diesen Baustein müsste der Entwickler im Netzwerk manuell den `F_WORD_TO_BYTE` einfügen und die Adapterverbindungen selbst verdrahten – der Composite-Baustein vereinfacht dies.

## Fazit
`AW_TO_AB` ist ein einfacher, aber nützlicher Composite-Baustein zur Umwandlung eines WORD-Adapters in einen BYTE-Adapter. Er reduziert den Verdrahtungsaufwand in 4diac‑Applikationen und gewährleistet eine konsistente Konvertierung durch Wiederverwendung des Standardbausteins `F_WORD_TO_BYTE`. Anwender sollten sich des möglichen Datenverlusts durch die Reduzierung der Bitbreite bewusst sein.