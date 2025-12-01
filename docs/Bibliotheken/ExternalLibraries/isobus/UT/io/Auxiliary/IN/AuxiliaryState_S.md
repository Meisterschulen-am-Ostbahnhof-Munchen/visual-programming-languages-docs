# AuxiliaryState_S

* * * * * * * * * *
## Einleitung
Der Datentyp `AuxiliaryState_S` ist eine strukturierte Datenstruktur (Struct), die den Zustand eines Hilfseingangs (Auxiliary Input) repräsentiert. Er wird im Kontext der ISOBUS-Schnittstelle (ISO 11783) für die Kommunikation in landwirtschaftlichen und forstwirtschaftlichen Maschinen verwendet. Dieser Datentyp kapselt sowohl den eigentlichen Wert des Eingangs als auch eine Steuerinformation für dessen zyklische Übertragung.

## Schnittstellenstruktur
`AuxiliaryState_S` ist ein strukturierter Datentyp (Struct) und besitzt daher keine Ereignis- oder Adapterschnittstellen im herkömmlichen Sinne eines Funktionsbausteins. Seine Struktur besteht aus den folgenden zwei Datenfeldern:

### **Daten-Eingänge**
*(Nicht anwendbar – Dies ist ein Datentyp, kein Funktionsbaustein)*

### **Daten-Ausgänge**
*(Nicht anwendbar – Dies ist ein Datentyp, kein Funktionsbaustein)*

### **Strukturierte Datenfelder**
| Name | Datentyp | Initialwert | Kommentar |
| :--- | :--- | :--- | :--- |
| `value` | `USINT` (0...255) | 255 | Repräsentiert den Wert des Hilfseingangs. |
| `bCyclic` | `BOOL` | `TRUE` | Steuert die zyklische Übertragung. Wenn auf `FALSE` gesetzt, wird die Nachricht nicht alle 200 ms wiederholt. |

## Funktionsweise
Der Datentyp dient als Container für Informationen über einen Hilfseingang. Das Feld `value` speichert den eigentlichen, gelesenen Wert. Der Initialwert 255 kann einen ungültigen oder undefinierten Zustand repräsentieren. Das Feld `bCyclic` ist ein Steuerflag, das das Übertragungsverhalten in einem ISOBUS-Netzwerk beeinflusst. Gemäß dem Kommentar wird bei `bCyclic = TRUE` die zugehörige Nachricht standardmäßig alle 200 Millisekunden zyklisch gesendet. Wird `bCyclic` auf `FALSE` gesetzt, unterbleibt diese regelmäßige Wiederholung, was den Netzwerkverkehr reduzieren kann, wenn sich der Wert nicht häufig ändert.

## Technische Besonderheiten
*   **ISOBUS-Kontext:** Der Datentyp ist spezifisch für die ISOBUS-Kommunikation (Package `isobus::UT::io::Auxiliary::IN`) konzipiert.
*   **Zyklussteuerung:** Die integrierte Steuerung der Zyklizität (`bCyclic`) ist ein charakteristisches Merkmal, das die Effizienz der Buskommunikation berücksichtigt.
*   **Initialwerte:** Beide Felder haben definierte Initialwerte (`value=255`, `bCyclic=TRUE`), was für eine deterministische Initialisierung sorgt.

## Zustandsübersicht
*(Nicht anwendbar – Dies ist ein passiver Datentyp ohne Zustandsautomaten.)*

## Anwendungsszenarien
Dieser Struct wird typischerweise als Dateneingang oder -ausgang in Funktionsbausteinen (FBs) verwendet, die ISOBUS-Hilfseingänge verarbeiten oder steuern. Beispiele sind:
*   FBs zum Auslesen des Zustands von Schaltern, Potentiometern oder Sensoren, die als Hilfseingänge konfiguriert sind.
*   FBs, die Hilfseingangswerte verarbeiten und an andere Systemkomponenten weiterleiten.
*   FBs, die basierend auf dem `bCyclic`-Flag entscheiden, ob ein Wert aktualisiert und gesendet werden muss.

## Vergleich mit ähnlichen Bausteinen
Als reiner Datentyp ist ein direkter Vergleich mit Funktionsbausteinen nicht sinnvoll. Innerhalb der ISOBUS-Datentypen könnte er mit einfacheren Datentypen wie einem reinen `USINT` für den Wert verglichen werden. Der Vorteil von `AuxiliaryState_S` liegt in der Erweiterung um die Metainformation zur Übertragungssteuerung (`bCyclic`), was eine höhere Integration und effizientere Kommunikation im ISOBUS-Netzwerk ermöglicht.

## Fazit
`AuxiliaryState_S` ist ein spezialisierter, strukturierter Datentyp für die ISOBUS-Kommunikation. Er bietet eine elegante Möglichkeit, nicht nur den Wert eines Hilfseingangs, sondern auch ein wichtiges Protokollattribut für dessen zyklische Übertragung zu kapseln. Seine Verwendung fördert die Klarheit und Wartbarkeit von Applikationen, die ISOBUS-I/O-Funktionalitäten implementieren.