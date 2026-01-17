# AUDI_TO_AD

## Einleitung
Der AUDI_TO_AD Funktionsblock ist ein spezialisierter Adapter-Konvertierungsbaustein. Er dient dazu, einen unidirektionalen **AUDI** (UDINT) Adapter-Socket in einen unidirektionalen **AD** (DWORD) Adapter-Plug umzuwandeln.

Intern nutzt der Baustein die Standard-Konvertierungsfunktion `F_UDINT_TO_DWORD`, um eine saubere Typwandlung zwischen dem numerischen Format (UDINT) und dem Bit-String-Format (DWORD) sicherzustellen.

## Schnittstellenstruktur

### **Adapter**
- **AUDI_IN** (Socket): Eingangsadapter vom Typ `AUDI` (UDINT).
- **AD_OUT** (Plug): Ausgangsadapter vom Typ `AD` (DWORD).

## Funktionsweise
Sobald am `AUDI_IN` ein Ereignis (`E1`) zusammen mit Daten (`D1`) eintrifft, wird der UDINT-Wert intern in einen DWORD-Wert gewandelt. Dieser wird anschließend sofort über den `AD_OUT` Adapter (Ereignis `E1`, Daten `D1`) weitergegeben.

## Technische Besonderheiten
✔ **Direkte Adapter-zu-Adapter Kopplung**.
✔ **Normgerechte Wandlung** durch Verwendung von `F_UDINT_TO_DWORD`.
✔ **Ereignisgesteuert**: Jede Aktualisierung am Eingang löst sofort eine Aktualisierung am Ausgang aus.

## Anwendungsszenarien
- Rückführung von numerischen Berechnungsergebnissen an ISOBUS-Ausgabebausteine (z.B. Bargraph oder numerische Anzeige), die oft DWORD als Eingangsformat erwarten.
- Kompatibilitätsschicht in adapterbasierten Steuerungsarchitekturen.
