# AUDI_TO_AR


![AUDI_TO_AR](./AUDI_TO_AR.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `AUDI_TO_AR` ist ein zusammengesetzter Baustein (Composite FB), der eine UDINT-große Ganzzahl, die über einen unidirektionalen AUDI‑Adapter empfangen wird, in einen REAL‑Wert umwandelt und über einen unidirektionalen AR‑Adapter ausgibt. Er kapselt die Konvertierungslogik und ermöglicht so eine saubere Schnittstellenanpassung zwischen unterschiedlichen Adaptertypen.

## Schnittstellenstruktur

Dieser FB besitzt keine direkten Ereignis‑ oder Datenein‑/ausgänge. Die gesamte Kommunikation erfolgt ausschließlich über Adapter‑Schnittstellen.

### **Ereignis-Eingänge**

Keine.

### **Ereignis-Ausgänge**

Keine.

### **Daten-Eingänge**

Keine.

### **Daten-Ausgänge**

Keine.

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| `AUDI_IN` | `adapter::types::unidirectional::AUDI` | Socket (Eingang) | Liefert einen UDINT‑Wert sowie ein zugehöriges Ereignis. Der Adapter stellt intern einen Ereignisausgang `E1` und einen Datenausgang `D1` (Datentyp UDINT) bereit. |
| `AR_OUT`  | `adapter::types::unidirectional::AR`  | Plug (Ausgang)  | Gibt den konvertierten REAL‑Wert aus. Der Adapter besitzt intern einen Ereigniseingang `E1` und einen Dateneingang `D1` (Datentyp REAL). |

## Funktionsweise

1. Ein externes Signal triggert das Ereignis `AUDI_IN.E1`.
2. Dieses Ereignis wird an den internen Konvertierungsbaustein `F_UDINT_TO_REAL` (Typ `iec61131::conversion::F_UDINT_TO_REAL`) weitergeleitet (`Convert.REQ`).
3. Gleichzeitig wird der UDINT‑Wert von `AUDI_IN.D1` an den Dateneingang `Convert.IN` übergeben.
4. Der Konvertierungsbaustein führt die Umwandlung von UDINT in REAL durch.
5. Nach Abschluss löst er das Ereignis `Convert.CNF` aus, welches an den Ereigniseingang `AR_OUT.E1` weitergegeben wird.
6. Der konvertierte REAL‑Wert wird von `Convert.OUT` auf den Dateneingang `AR_OUT.D1` geschrieben und steht damit am AR‑Adapter zur Verfügung.

## Technische Besonderheiten

- Die Umwandlung nutzt einen IEC‑61131‑3‑Standardbaustein (`F_UDINT_TO_REAL`), der innerhalb des Composite FB instanziiert wird.
- Die Adapter sind als unidirektionale Schnittstellen ausgeführt, was eine klare Datenflussrichtung (vom AUDI‑ zum AR‑Adapter) erzwingt.
- Der Composite FB erzeugt keinerlei eigene Zustandslogik, sondern delegiert die gesamte Verarbeitung an den internen Konvertierungsbaustein.

## Zustandsübersicht

Der Baustein besitzt keine eigene Zustandsmaschine. Seine Funktionalität folgt dem einfachen Ablauf:

- **Warten auf Eingangsereignis** – solange `AUDI_IN.E1` nicht aktiv ist, bleibt der FB passiv.
- **Konvertierung** – nach Eintreffen von `AUDI_IN.E1` wird der integrierte `F_UDINT_TO_REAL` ausgeführt.
- **Ausgabe** – nach erfolgreicher Konvertierung wird `AR_OUT.E1` ausgelöst und der REAL‑Wert bereitgestellt.

## Anwendungsszenarien

- Anbindung eines UDINT‑basierten Zählers (z. B. Impulszähler) an eine Steuerung, die REAL‑Werte für Berechnungen oder Visualisierungen erwartet.
- Umwandlung von Adaptersignalen zwischen unterschiedlichen Datentypen in einer modularen, adapterbasierten Kommunikationsarchitektur.
- Als Baustein in einer Bibliothek für typsichere Adapter‑Konvertierungen.

## Vergleich mit ähnlichen Bausteinen

Dieser FB ist speziell auf die Kombination von AUDI‑ (UDINT) und AR‑ (REAL) Adaptern zugeschnitten. Vergleichbare Bausteine existieren für andere Datentypen, z. B.:

- `SINT_TO_AR` (SINT → REAL)
- `AUDI_TO_AI` (UDINT → INT)

Der Vorteil dieses Bausteins liegt in der klaren Kapselung und der Wiederverwendbarkeit innerhalb eines adapterbasierten Systemdesigns.

## Fazit

Der `AUDI_TO_AR`‑Funktionsblock bietet eine einfache, aber effektive Möglichkeit, UDINT‑Daten über Adapterschnittstellen in REAL‑Daten zu konvertieren. Durch die Verwendung eines IEC‑Standardbausteins und die rein adapterbasierte Kommunikation ist er leicht verständlich, wartbar und in vielen Automatisierungsprojekten einsetzbar.