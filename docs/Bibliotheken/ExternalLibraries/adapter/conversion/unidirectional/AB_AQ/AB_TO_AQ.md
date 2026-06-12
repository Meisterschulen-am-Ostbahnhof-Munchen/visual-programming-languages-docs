# AB_TO_AQ


![AB_TO_AQ](./AB_TO_AQ.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AB_TO_AQ** dient der Konvertierung eines unidirektionalen Adapters vom Typ **AB (BYTE)** in einen Adapter vom Typ **AQ (Quarter Byte)**. Er übernimmt die direkte Durchleitung eines Ereignisses und eines Datenwerts von der Eingangsschnittstelle zur Ausgangsschnittstelle, wobei die Datenbreite implizit von 8 Bit auf 2 Bit reduziert wird.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **IN.E1** (über Adapter IN): Ereigniseingang des BYTE-Adapters.

### **Ereignis-Ausgänge**
- **OUT.E1** (über Adapter OUT): Ereignisausgang des Quarter-Byte-Adapters.

### **Daten-Eingänge**
- **IN.D1** (über Adapter IN): Dateneingang des BYTE-Adapters (1 Byte).

### **Daten-Ausgänge**
- **OUT.D1** (über Adapter OUT): Datenausgang des Quarter-Byte-Adapters (1 Quarter Byte).

### **Adapter**
| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| **IN**  | Socket   | `adapter::types::unidirectional::AB` | BYTE-Eingangsadapter (8 Bit) |
| **OUT** | Plug     | `adapter::types::unidirectional::AQ` | Quarter-Byte-Ausgangsadapter (2 Bit) |

## Funktionsweise
Der Baustein leitet ein eingehendes Ereignis (E1) und die zugehörigen Daten (D1) direkt vom IN-Adapter zum OUT-Adapter weiter. Dabei erfolgt keine interne Verarbeitung oder Zustandsänderung; die Daten werden durchschleifen. Die Konvertierung von einem 8-Bit- auf ein 2-Bit-Format wird durch die unterschiedlichen Adaptertypen bestimmt – üblicherweise werden die niederwertigsten Bits (LSB) des BYTE-Werts in das Quarter Byte übernommen, sofern nicht anders spezifiziert.

## Technische Besonderheiten
- Reiner Durchschleifbaustein ohne eigene Zustandslogik (keine ECC).
- Ereignis- und Datenpfade sind direkt miteinander verbunden: `IN.E1 → OUT.E1` und `IN.D1 → OUT.D1`.
- Die Datenreduktion von 8 Bit auf 2 Bit erfolgt allein durch die Typanpassung; eine explizite Wandlung (z. B. Beschneidung oder Rundung) ist nicht im FB selbst implementiert.
- Der Baustein ist als unidirektionaler Adapter-Konverter ausgelegt und unterstützt keine bidirektionale Kommunikation.

## Zustandsübersicht
Es existiert keine Zustandsmaschine. Der FB arbeitet rein kombinatorisch: Jedes Ereignis am Eingang wird sofort als Ereignis am Ausgang weitergeleitet, begleitet vom aktuellen Datenwert.

## Anwendungsszenarien
- Anbindung einer Byte-orientierten Schnittstelle an eine Logik, die nur zwei Bit breite Daten verarbeitet (z. B. Statusbits oder Schaltsignale).
- Reduzierung der Datenbreite in einer Adapterkaskade, wenn die ursprüngliche Byte-Information auf die unteren zwei Bits komprimiert werden kann.
- Test- und Simulationsumgebungen, in denen unterschiedliche Adapterformate miteinander verbunden werden müssen.

## Vergleich mit ähnlichen Bausteinen
- **AB_TO_AQ** ähnelt anderen unidirektionalen Adapter-Konvertern wie z. B. `AB_TO_AB` (identische Typen) oder `AQ_TO_AB` (Erweiterung auf ein Byte). Der Unterschied liegt in der Datenbreite und der Art der impliziten Umwandlung.
- Im Gegensatz zu Wandlern mit expliziten Algorithmen (z. B. Skalierung oder Bitmaskierung) bietet dieser FB keine Konfigurationsmöglichkeiten – die Umwandlung ist fest vorgegeben.

## Fazit
Der **AB_TO_AQ** Funktionsblock ist ein einfacher, aber nützlicher Adapter-Konverter, der eine direkte elektrische und logische Verbindung zwischen zwei unterschiedlichen unidirektionalen Adaptertypen herstellt. Er eignet sich hervorragend für Fälle, in denen eine Byte-Information auf die wichtigsten zwei Bits reduziert weitergegeben werden soll, ohne zusätzliche Verarbeitungslast zu erzeugen.