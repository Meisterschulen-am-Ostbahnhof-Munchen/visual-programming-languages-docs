# AX_TO_AUDI


![AX_TO_AUDI](./AX_TO_AUDI.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AX_TO_AUDI** ist ein zusammengesetzter Baustein (Composite FB), der einen Booleschen Wert (BOOL), der über einen AX‑Adapter bereitgestellt wird, in einen vorzeichenlosen Doppelwort‑Wert (UDINT) umwandelt und über einen AUDI‑Adapter ausgibt. Er wird eingesetzt, um Signale zwischen Adapter‑Schnittstellen zu konvertieren, wobei die eigentliche Umwandlung durch einen internen IEC‑61131‑Konvertierungsbaustein erfolgt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **AX_IN.E1** (über Socket‑Adapter AX_IN): Ereignis, das die Konvertierung anstößt.

### **Ereignis-Ausgänge**
- **AUDI_OUT.E1** (über Plug‑Adapter AUDI_OUT): Bestätigungsereignis nach erfolgreicher Konvertierung.

### **Daten-Eingänge**
- **AX_IN.D1** (über Socket‑Adapter AX_IN, Datentyp **BOOL**): Der umzuwandelnde Boolesche Wert.

### **Daten-Ausgänge**
- **AUDI_OUT.D1** (über Plug‑Adapter AUDI_OUT, Datentyp **UDINT**): Der konvertierte Ganzzahlwert (0 oder 1).

### **Adapter**
- **AX_IN** – Socket‑Adapter vom Typ `adapter::types::unidirectional::AX`  
  Nimmt einen Booleschen Wert (und ein zugehöriges Ereignis) entgegen.
- **AUDI_OUT** – Plug‑Adapter vom Typ `adapter::types::unidirectional::AUDI`  
  Stellt den konvertierten UDINT‑Wert (und ein quittierendes Ereignis) bereit.

## Funktionsweise

Der Baustein arbeitet ereignisgesteuert:

1. Ein Ereignis am Ereignis‑Eingang **AX_IN.E1** triggert den internen Konvertierungsbaustein `F_BOOL_TO_UDINT` über dessen Ereigniseingang **REQ**.
2. Der Datenwert **AX_IN.D1** (BOOL) wird an den Dateneingang **IN** des Konvertierungsbausteins weitergeleitet.
3. Der Konvertierungsbaustein wandelt den Booleschen Wert in einen UDINT um (FALSE → 0, TRUE → 1) und gibt das Ergebnis an seinem Ausgang **OUT** aus.
4. Das Ergebnis wird an den Datenausgang **AUDI_OUT.D1** übergeben.
5. Nach Abschluss der Umwandlung wird das quittierende Ereignis des Konvertierungsbausteins (**CNF**) an den Ereignis‑Ausgang **AUDI_OUT.E1** weitergegeben.

## Technische Besonderheiten

- **Zusammengesetzter Baustein (Composite FB)** nach IEC 61499‑2.
- Verwendet den internen FB `iec61131::conversion::F_BOOL_TO_UDINT` für die eigentliche Konvertierung.
- Die Adapter‑Schnittstellen (`AX` und `AUDI`) ermöglichen eine modulare und standardisierte Anbindung an andere Bausteine.
- Der Baustein ist quelloffen unter der Eclipse Public License 2.0 lizenziert.

## Zustandsübersicht

Der Baustein besitzt keine eigenen Zustandsautomaten. Das Verhalten wird vollständig durch die sequenzielle Abarbeitung des internen Konvertierungsbausteins bestimmt:
- **Idle**: Warten auf ein Ereignis an **AX_IN.E1**.
- **Konvertierung aktiv**: Nach Empfang des Ereignisses wird die Umwandlung durchgeführt; während dieser Zeit werden keine weiteren Ereignisse verarbeitet (Single‑Execution).
- **Abschluss**: Das Ausgangsereignis wird gesendet, danach kehrt der Baustein in den Idle‑Zustand zurück.

## Anwendungsszenarien

- Umwandlung eines digitalen Sensorsignals (z. B. Endschalter) in einen numerischen Wert, der in einer SPS‑Steuerung weiterverarbeitet werden soll.
- Anpassung zwischen unterschiedlichen Adapter‑Schnittstellen in IEC‑61499‑basierten Automatisierungssystemen.
- Einsatz in Systemen, in denen nur Boolesche Werte über eine AX‑Schnittstelle verfügbar sind, aber eine UDINT‑Schnittstelle (z. B. für Diagnose‑ oder Zählzwecke) benötigt wird.

## Vergleich mit ähnlichen Bausteinen

- **F_BOOL_TO_UDINT** (direkt): Führt die gleiche Konvertierung durch, erfordert aber separate Ereignis‑ und Datenverbindungen. **AX_TO_AUDI** kapselt diese Logik in einem Adapter‑basierten Interface.
- **AX_TO_*‑Bausteine**: Analog zu diesem Baustein, jedoch mit anderen Ziel‑Datentypen (z. B. INT, DINT). Diesem Baustein liegt die UDINT‑Variante zugrunde.
- **Adapter‑Koppler**: Reine Durchleit‑Bausteine ohne Konvertierung – im Gegensatz zu **AX_TO_AUDI**, das eine aktive Typumwandlung vornimmt.

## Fazit

Der Funktionsblock **AX_TO_AUDI** stellt eine einfache, aber nützliche Brücke zwischen booleschen und ganzzahligen Adapter‑Schnittstellen dar. Durch die Kapselung der Konvertierung in einem Composite‑Baustein wird der Entwurf übersichtlicher und die Wiederverwendbarkeit erhöht. Er eignet sich besonders für Standard‑Umwandlungsaufgaben in IEC‑61499‑Projekten, bei denen modulare Adapter‑Schnittstellen verwendet werden.