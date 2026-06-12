# AL_TO_ALR


![AL_TO_ALR](./AL_TO_ALR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AL_TO_ALR** ist ein zusammengesetzter Baustein (Composite FB), der einen unidirektionalen AL‑Adapter (LWORD) in einen unidirektionalen ALR‑Adapter (LREAL) umwandelt. Er nutzt intern den Konvertierungsbaustein `F_LWORD_TO_LREAL`, um einen eingehenden LWORD‑Wert (64‑Bit‑Integer) in einen LREAL‑Wert (64‑Bit‑Gleitkommazahl) zu wandeln und diesen über den Ausgangsadapter bereitzustellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine direkten Ereignis-Eingänge. Das für die Auslösung der Konvertierung erforderliche Ereignis wird über den Socket **AL_IN** (Typ `AL`) bereitgestellt. Dieses Ereignis (E1) wird intern mit dem `REQ`-Eingang des Konvertierungsbausteins verbunden.

### **Ereignis-Ausgänge**

Der FB besitzt keine direkten Ereignis-Ausgänge. Das Abschlussereignis der Konvertierung wird über den Plug **ALR_OUT** (Typ `ALR`) ausgegeben. Das Ereignis (E1) des internen Bausteins (`CNF`) wird an den Ausgangsadapter weitergeleitet.

### **Daten-Eingänge**

Der FB besitzt keine direkten Daten-Eingänge. Der zu konvertierende LWORD‑Wert wird über den Socket **AL_IN** (Daten-Signal D1) bereitgestellt und an den `IN`-Eingang des Konvertierungsbausteins übergeben.

### **Daten-Ausgänge**

Der FB besitzt keine direkten Daten-Ausgänge. Der konvertierte LREAL‑Wert wird über den Plug **ALR_OUT** (Daten-Signal D1) ausgegeben; er stammt vom `OUT`-Ausgang des internen Bausteins.

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| **AL_IN** | Socket (Eingang) | `adapter::types::unidirectional::AL` | LWORD‑Adapter, der das Eingangssignal (LWORD) und ein Auslöseereignis bereitstellt. |
| **ALR_OUT** | Plug (Ausgang) | `adapter::types::unidirectional::ALR` | LREAL‑Adapter, der das konvertierte Signal (LREAL) und ein Bestätigungsereignis ausgibt. |

## Funktionsweise

Der Baustein arbeitet in einem einfachen ereignisgesteuerten Ablauf:

1. Ein eingehendes Ereignis am Socket **AL_IN.E1** wird an den `REQ`-Eingang des internen Funktionsblocks `F_LWORD_TO_LREAL` weitergeleitet.
2. Gleichzeitig wird der Datenwert von **AL_IN.D1** (LWORD) an den `IN`-Eingang des Konverters übergeben.
3. Der interne FB führt die Umwandlung `LWORD → LREAL` durch.
4. Nach Abschluss der Konvertierung wird das Ereignis `CNF` an den Plug **ALR_OUT.E1** gesendet.
5. Der konvertierte LREAL‑Wert wird auf **ALR_OUT.D1** ausgegeben.

Die gesamte Verarbeitung erfolgt innerhalb eines Taktzyklus (keine Blockierung).

## Technische Besonderheiten

- **Adapter‑basierte Schnittstelle**: Der FB nutzt ausschließlich unidirektionale Adapter (`AL` und `ALR`). Dies ermöglicht eine lose Kopplung zwischen Sender und Empfänger sowie eine einfache Wiederverwendung in verschiedenen Systemarchitekturen.
- **Typkonvertierung**: Die Umwandlung von `LWORD` (64‑Bit‑Integer ohne Vorzeichen) in `LREAL` (64‑Bit‑Gleitkommazahl nach IEEE 754) erfolgt ohne Genauigkeitsverluste, solange der Integerwert im darstellbaren Bereich der Gleitkommazahl liegt (max. 2⁵³‑1).
- **Durchgereichte Ereignissteuerung**: Der Baustein führt keine interne Zustandslogik aus; er leitet Ereignisse und Daten transparent weiter. Die Laufzeit des Aufrufs entspricht der Ausführungszeit des internen Konverters.

## Zustandsübersicht

Der zusammengesetzte Baustein selbst besitzt **keine eigenen Zustände**. Die Verarbeitung wird vollständig durch den intern verwendeten Funktionsblock `F_LWORD_TO_LREAL` gesteuert, der folgendes minimales Zustandsverhalten aufweist:

- **IDLE**: Warten auf ein `REQ`-Ereignis.
- **CONVERT**: Ausführen der Konvertierung (unmittelbar nach `REQ`).
- **SEND**: Ausgeben des `CNF`-Ereignisses und des konvertierten Werts.

Da der innere FB in einem einzigen Ausführungsschritt arbeitet, sind die Zustände nicht von außen beobachtbar.

## Anwendungsszenarien

- **Sensordatenverarbeitung**: Ein Sensor liefert Messwerte im LWORD‑Format (z. B. Zählerstände, Rohdaten). Der Baustein wandelt diese in LREAL um, sodass sie in Gleitkomma‑Algorithmen (z. B. Regelung, Filterung) verwendet werden können.
- **Protokoll‑Konvertierung**: In Systemen, die unterschiedliche Datenformate über Adapter austauschen, dient `AL_TO_ALR` als Brücke zwischen LWORD‑ und LREAL‑basierten Komponenten.
- **Test und Simulation**: Erzeugung von LREAL‑Testdaten aus vordefinierten LWORD‑Werten oder umgekehrt (durch entsprechende Gegenbausteine).

## Vergleich mit ähnlichen Bausteinen

- **`LWORD_TO_LREAL`** – Ein einfacher Konvertierungsbaustein ohne Adapter‑Schnittstelle. `AL_TO_ALR` kapselt diesen Baustein und integriert ihn in eine adapterbasierte Architektur.
- **`LINT_TO_LREAL`** – Konvertiert signed 64‑Bit‑Integer in LREAL. `AL_TO_ALR` arbeitet mit dem vorzeichenlosen LWORD.
- **`UDINT_TO_LREAL`** – Analog für 32‑Bit‑Breite. Der vorliegende Baustein ist auf 64‑Bit ausgelegt und nutzt unidirektionale Adapter.

## Fazit

`AL_TO_ALR` ist ein spezialisierter Composite‑Baustein zur formalen Umwandlung von LWORD‑ in LREAL‑Daten über unidirektionale Adapter. Er vereinfacht die Integration von Integer‑basierten Komponenten in Gleitkomma‑Umgebungen und fördert durch die Adapter‑Schnittstelle eine modulare, wiederverwendbare Systemstruktur. Die einfache ereignisgesteuerte Arbeitsweise macht ihn zuverlässig und leicht verständlich.