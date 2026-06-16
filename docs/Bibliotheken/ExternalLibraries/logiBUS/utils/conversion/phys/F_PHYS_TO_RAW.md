# F_PHYS_TO_RAW


![F_PHYS_TO_RAW](./F_PHYS_TO_RAW.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **F_PHYS_TO_RAW** wandelt einen physikalischen REAL-Wert in einen ISOBUS-Rohwert (UDINT) um. Dabei werden Sättigungsgrenzen beachtet und Über- bzw. Unterlaufalarme ausgegeben. Die Umrechnung basiert auf der ISOBUS-Formel: `Anzeige = (Rohwert + Offset) * Skalierung`. Die inverse Berechnung lautet: `Rohwert = UDINT(DINT(physikalischer Wert / Skalierung) - Offset)`.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| REQ | Anforderung zur Umrechnung des physikalischen Wertes. Wird mit den Parametern `rPhys` und `stObj` ausgeführt. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| CNF | Bestätigung, dass die Umrechnung abgeschlossen ist. Liefert den berechneten Rohwert sowie die Alarmflags `xOver` und `xUnder`. |

### **Daten-Eingänge**

| Variable | Typ | Beschreibung |
|----------|-----|--------------|
| rPhys | REAL | Der physikalische Wert, der umgerechnet werden soll. |
| stObj | NumericObjectPool_S | Struktur mit den Parametern `i32Offset` (DINT) und `r32Scale` (REAL) für die ISOBUS-Formel. |

### **Daten-Ausgänge**

| Variable | Typ | Beschreibung |
|----------|-----|--------------|
| * | UDINT | Der berechnete ISOBUS-Rohwert (Rückgabewert der Funktion). Gesättigt auf den Bereich 0 bis 4294967295. |
| xOver | BOOL | TRUE, wenn der physikalische Wert den oberen Grenzwert überschreitet. |
| xUnder | BOOL | TRUE, wenn der physikalische Wert den unteren Grenzwert unterschreitet. |

### **Adapter**
Keine.

## Funktionsweise
Der FB berechnet zunächst die untere und obere Grenze:
- Untere Grenze: `lrLower = Offset * Skalierung`
- Obere Grenze: `lrUpper = (Offset + 4294967295) * Skalierung`

Anschließend wird der physikalische Wert mit diesen Grenzen verglichen:
1. **Überlauf (xOver = TRUE):** Wenn `rPhys > lrUpper`, wird der Rohwert auf den maximalen UDINT-Wert (4294967295) gesetzt.
2. **Unterlauf (xUnder = TRUE):** Wenn `rPhys < lrLower`, wird der Rohwert auf 0 gesetzt.
3. **Normalbereich:** Im gültigen Bereich wird der Rohwert nach der Formel `UDINT(DINT(rPhys / Skalierung) - Offset)` berechnet.

Die Berechnung erfolgt innerhalb des Structured-Text-Codes bei jedem REQ-Ereignis.

## Technische Besonderheiten
- Der Rückgabetyp ist UDINT, die Sättigung erfolgt auf den vollen Wertebereich von 0 bis 4294967295.
- Die Offset- und Skalierungsdaten werden aus einer externen Struktur (`NumericObjectPool_S`) gelesen, die typischerweise vom ISOBUS-Objektpool bereitgestellt wird.
- Der Baustein verwendet keine internen Zustände; die Berechnung ist rein kombinatorisch und wird bei jedem REQ komplett neu durchgeführt.
- Die Konvertierung von REAL zu DINT erfolgt mit `REAL_TO_DINT`, was bei großen Werten zu Rundungsfehlern führen kann.

## Zustandsübersicht
Der FB besitzt keine explizite Zustandsmaschine. Er arbeitet zustandslos auf Basis der aktuellen Eingänge. Bei jedem REQ-Ereignis wird die Ausgabe neu berechnet.

## Anwendungsszenarien
- **ISOBUS-Steuergeräte:** Umrechnung von Sensormesswerten (z. B. Temperatur, Druck) in den ISOBUS-konformen Rohdatenwert für die Anzeige in einem Terminal.
- **Landwirtschaftliche Maschinensteuerung:** Konvertierung von physikalischen Größen, die mit einer spezifischen Skalierung und Offset im ISOBUS-Diagnoseprotokoll dargestellt werden.
- **Test- und Simulationsumgebungen:** Erzeugung von ISOBUS-Rohwerten aus simulierten physikalischen Werten.

## Vergleich mit ähnlichen Bausteinen
Bausteine wie `F_RAW_TO_PHYS` führen die inverse Umrechnung durch (Rohwert → physikalischer Wert). Während dieser Baustein die physikalische Größe in den Rohwert wandelt, bietet `F_PHYS_TO_RAW` zusätzlich die Sättigung und Alarmsignalisierung für Über- und Unterlauf. Im Gegensatz zu allgemeinen Arithmetikbausteinen ist er speziell auf die ISOBUS-Konvention mit Offset und Skalierung ausgelegt.

## Fazit
Der Funktionsblock `F_PHYS_TO_RAW` ist ein spezialisierter Baustein für die ISOBUS-Konvertierung mit integrierter Bereichsüberwachung. Er bietet eine einfache und robuste Schnittstelle, um physikalische Messwerte in das ISOBUS-Protokoll einzubinden, und stellt sicher, dass der Rohwert immer innerhalb des gültigen Bereichs liegt. Die Alarmausgänge ermöglichen eine sofortige Fehlererkennung bei Grenzwertüberschreitungen.