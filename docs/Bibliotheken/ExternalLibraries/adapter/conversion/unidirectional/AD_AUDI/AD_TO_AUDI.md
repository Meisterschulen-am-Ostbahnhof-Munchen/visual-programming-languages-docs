# AD_TO_AUDI

```{index} single: AD_TO_AUDI
```

## Einleitung
Der AD_TO_AUDI Funktionsblock ist ein spezialisierter Adapter-Konvertierungsbaustein. Er dient dazu, einen unidirektionalen **AD** (DWORD) Adapter-Socket in einen unidirektionalen **AUDI** (UDINT) Adapter-Plug umzuwandeln.

Intern nutzt der Baustein die Standard-Konvertierungsfunktion `F_DWORD_TO_UDINT`, um eine saubere Typwandlung zwischen dem Bit-String-Format (DWORD) und dem numerischen Format (UDINT) sicherzustellen.

![AD_TO_AUDI](AD_TO_AUDI.svg)

## Schnittstellenstruktur

### **Adapter**
- **AD_IN** (Socket): Eingangsadapter vom Typ `AD` (DWORD).
- **AUDI_OUT** (Plug): Ausgangsadapter vom Typ `AUDI` (UDINT).

## Funktionsweise
Sobald am `AD_IN` ein Ereignis (`E1`) zusammen mit Daten (`D1`) eintrifft, wird der DWORD-Wert intern in einen UDINT-Wert gewandelt. Dieser wird anschließend sofort über den `AUDI_OUT` Adapter (Ereignis `E1`, Daten `D1`) weitergegeben.

## Technische Besonderheiten
✔ **Direkte Adapter-zu-Adapter Kopplung**.
✔ **Normgerechte Wandlung** durch Verwendung von `F_DWORD_TO_UDINT`.
✔ **Ereignisgesteuert**: Jede Aktualisierung am Eingang löst sofort eine Aktualisierung am Ausgang aus.

## Anwendungsszenarien
- Anbindung von ISOBUS-Eingabebausteinen (die oft DWORD liefern) an numerische Verarbeitungslogik auf Adapter-Basis.
- Protokoll- und Typanpassung in komplexen Baustein-Netzwerken.



## 🛠️ Zugehörige Übungen

* [Uebung_011_AUDI](../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_011_AUDI.md)

