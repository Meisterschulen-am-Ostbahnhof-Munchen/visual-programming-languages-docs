# ARR08B_TO_BOOLS

![ARR08B_TO_BOOLS](https://github.com/user-attachments/assets/5e705423-96ed-4065-bbbf-57e71dd45c35)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ARR08B_TO_BOOLS` dient zur Umwandlung eines 8-Bit-Arrays (ARR08B) in acht einzelne BOOL-Ausgänge. Dies ermöglicht die einfache Extraktion einzelner Bits aus einem Byte für weitere Verarbeitungsschritte.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Normaler Ausführungsanforderung (Trigger für die Umwandlung)

### **Ereignis-Ausgänge**
- `CNF`: Ausführungsbestätigung (wird nach erfolgreicher Umwandlung ausgelöst)

### **Daten-Eingänge**
- `IN` (ARRAY[0..7] OF BOOL): 8-Bit-Eingangsarray (ARR08B Input)

### **Daten-Ausgänge**
- `OUT_00` (BOOL): Bit 00
- `OUT_01` (BOOL): Bit 01
- `OUT_02` (BOOL): Bit 02
- `OUT_03` (BOOL): Bit 03
- `OUT_04` (BOOL): Bit 04
- `OUT_05` (BOOL): Bit 05
- `OUT_06` (BOOL): Bit 06
- `OUT_07` (BOOL): Bit 07

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock extrahiert die einzelnen Bits aus dem Eingangsarray und weist sie den entsprechenden BOOL-Ausgängen zu. Bei Auslösung des `REQ`-Ereignisses werden die Bits 0 bis 7 des Eingangsarrays auf die Ausgänge `OUT_00` bis `OUT_07` kopiert. Nach erfolgreicher Umwandlung wird das `CNF`-Ereignis ausgelöst.

## Technische Besonderheiten
- Verarbeitet genau 8 Bit (1 Byte)
- Direkte 1:1-Zuordnung der Array-Elemente zu den Ausgängen
- Keine zusätzliche Logik oder Transformation

## Zustandsübersicht
1. Wartezustand: Auf `REQ`-Ereignis warten
2. Verarbeitungszustand: Bit-Extraktion durchführen
3. Bestätigungszustand: `CNF` auslösen und zurück in Wartezustand

## Anwendungsszenarien
- Verarbeitung von Byte-weise übertragenen Daten
- Extraktion einzelner Statusbits aus Steuerbytes
- Schnittstellen zu Systemen, die einzelne BOOL-Signale benötigen

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu allgemeinen Array-Splittern ist dieser Baustein speziell für 8-Bit-Arrays optimiert
- Bietet direkte Namensgebung für die einzelnen Bits (OUT_00 bis OUT_07)
- Keine zusätzliche Konfiguration notwendig (im Vergleich zu parametrierbaren Splittern)

## Fazit
Der `ARR08B_TO_BOOLS` Funktionsblock ist ein spezialisiertes und effizientes Werkzeug zur Extraktion einzelner Bits aus einem Byte-Array. Seine einfache und direkte Implementierung macht ihn besonders geeignet für Anwendungen, bei denen die klare Zuordnung von Bits zu einzelnen BOOL-Signalen erforderlich ist.
