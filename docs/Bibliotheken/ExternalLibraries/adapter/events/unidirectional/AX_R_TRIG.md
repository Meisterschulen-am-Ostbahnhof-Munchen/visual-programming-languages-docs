# AX_R_TRIG

![AX_R_TRIG](.././AX_R_TRIG.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsbaustein **AX_R_TRIG** (Boolean rising edge detection) dient der Erkennung einer steigenden Flanke basierend auf einem über einen Adapter bereitgestellten booleschen Signal. Er ist speziell für die Verwendung mit unidirektionalen Adaptern vom Typ `AX` konzipiert und leitet ein Ereignis nur dann weiter, wenn der übermittelte Datenwert `TRUE` ist.

## Schnittstellenstruktur

Der Baustein verwendet primär eine Adapter-Schnittstelle zur Kommunikation der Eingangsdaten und Ereignisse.

### **Ereignis-Eingänge**
Dieser Baustein verfügt über keine direkten Ereignis-Eingänge. Die Ereignisse werden über den Adapter `QI` empfangen.

### **Ereignis-Ausgänge**
*   **EO**: (Event Output) Bestätigung, dass eine steigende Flanke (oder ein High-Signal) erkannt wurde.

### **Daten-Eingänge**
Dieser Baustein verfügt über keine direkten Daten-Eingänge. Die Daten werden über den Adapter `QI` empfangen.

### **Daten-Ausgänge**
Dieser Baustein verfügt über keine direkten Daten-Ausgänge.

### **Adapter**
*   **QI** (Socket): Vom Typ `adapter::types::unidirectional::AX`. Dieser Adapter liefert den zu prüfenden Wert (boolesch) und das dazugehörige Ereignis.
    *   Erwartet typischerweise ein Ereignis (z. B. `E1`) und ein boolesches Datum (z. B. `D1`).

## Funktionsweise
Der Baustein ist als Composite Function Block (CFB) implementiert und basiert auf der internen Verschaltung eines D-Flip-Flops (`E_D_FF`) und eines Ereignis-Schalters (`E_SWITCH`).

1.  Sobald über den Adapter **QI** ein Ereignis empfangen wird, wird dieses an den Takteingang des internen `E_D_FF` geleitet.
2.  Gleichzeitig wird der boolesche Datenwert vom Adapter in das Flip-Flop geladen.
3.  Das Flip-Flop gibt den gespeicherten Wert an einen `E_SWITCH` weiter.
4.  Ist der Wert `TRUE` (High), schaltet der `E_SWITCH` durch und löst das Ausgangsereignis **EO** aus.
5.  Ist der Wert `FALSE` (Low), wird das Ereignis blockiert und **EO** wird nicht ausgelöst.

Technisch gesehen fungiert der Baustein als Gate, das das Adapter-Ereignis nur passieren lässt, wenn das Adapter-Datum `TRUE` ist. In einem ereignisbasierten System, das nur bei Wertänderungen sendet, entspricht dies der Logik einer Flankenerkennung (0 -> 1).

## Technische Besonderheiten
*   **Interne Struktur:** Verwendet Standard-IEC-61499-Bausteine (`E_D_FF`, `E_SWITCH`).
*   **Adapter-basiert:** Im Gegensatz zu klassischen Trigger-Bausteinen, die separate `CLK` und `QI` Eingänge haben, kapselt dieser Baustein die Signale in einem `AX`-Adapter.

## Zustandsübersicht
Da es sich um einen Composite Function Block handelt, besitzt dieser Baustein keine eigene Zustandsmaschine (ECC). Das Verhalten wird rein durch den Datenfluss und die Verschaltung der internen Unterbausteine bestimmt.

## Anwendungsszenarien
*   **Signalfilterung:** Weiterleitung von Ereignissen nur dann, wenn ein bestimmter Zustand aktiv ist.
*   **Adapter-Logik:** Einsatz in Systemen, die stark auf Adapter-Verbindungen setzen, um den Verdrahtungsaufwand zu minimieren.
*   **Start-Trigger:** Auslösen von Prozessen, sobald ein boolesches Flag innerhalb einer Adapter-Struktur auf `TRUE` wechselt.

## Vergleich mit ähnlichen Bausteinen
*   **E_R_TRIG:** Der Standard-Baustein für Ereignis-basierte steigende Flankenerkennung mit separaten Ereignis- und Dateneingängen. `AX_R_TRIG` ist das Äquivalent für Adapter-Verbindungen.
*   **R_TRIG:** Der klassische SPS-Baustein (IEC 61131-3), der zyklisch abgefragt wird. `AX_R_TRIG` arbeitet hingegen rein ereignisgesteuert.

## Fazit
Der **AX_R_TRIG** ist ein spezialisierter Baustein für die 4diac-Umgebung, der die Logik einer steigenden Flankenerkennung oder eines High-Pass-Filters nahtlos in Designs integriert, die `AX`-Adapter verwenden. Er vereinfacht das Netzwerk, indem er das explizite Aufsplitten von Adapter-Signalen zur Prüfung unnötig macht.