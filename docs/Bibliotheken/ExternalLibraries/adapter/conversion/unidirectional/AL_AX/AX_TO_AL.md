# AX_TO_AL


![AX_TO_AL](./AX_TO_AL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AX_TO_AL** ist ein Composite-Baustein zur bidirektionalen Kopplung eines AX-Adapters (BOOL) mit einem AL-Adapter (LWORD). Er ermöglicht das Weiterleiten von Ereignissen und Daten zwischen diesen beiden Adapterschnittstellen, ohne eigene Logik zu implementieren. Der FB dient als einfache Konvertierungsbrücke und wird typischerweise in Automatisierungssystemen eingesetzt, um Komponenten mit unterschiedlichen Adapterformaten zu verbinden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Adapter | Beschreibung |
|------|---------|--------------|
| AX_IN.E1 | AX (BOOL) | Ereigniseingang, der über den AX-Adapter angebunden wird. |

### **Ereignis-Ausgänge**

| Name | Adapter | Beschreibung |
|------|---------|--------------|
| AL_OUT.E1 | AL (LWORD) | Ereignisausgang, der das eingehende Ereignis unverändert weitergibt. |

### **Daten-Eingänge**

| Name | Adapter | Typ | Beschreibung |
|------|---------|-----|--------------|
| AX_IN.D1 | AX (BOOL) | BOOL | Dateneingang für ein boolesches Signal. |

### **Daten-Ausgänge**

| Name | Adapter | Typ | Beschreibung |
|------|---------|-----|--------------|
| AL_OUT.D1 | AL (LWORD) | LWORD | Datenausgang, der das boolesche Signal als LWORD (64‑Bit-Speicher) darstellt. Die Typkonvertierung erfolgt außerhalb des Bausteins. |

### **Adapter**

| Typ | Name | Richtung |
|-----|------|----------|
| Socket | AX_IN | Eingang (BOOL) |
| Plug   | AL_OUT | Ausgang (LWORD) |

## Funktionsweise

Der FB **AX_TO_AL** arbeitet als reiner Durchreiche-Baustein. Im FBNetzwerk werden die Ereignisverbindung `AX_IN.E1 → AL_OUT.E1` und die Datenverbindung `AX_IN.D1 → AL_OUT.D1` direkt hergestellt. Ein eingehendes Ereignis am AX‑Socket löst sofort das entsprechende Ereignis am AL‑Plug aus. Gleichzeitig wird der boolesche Wert von `AX_IN.D1` an `AL_OUT.D1` weitergegeben.

Der Baustein selbst führt keine Wertumwandlung durch; die Konvertierung des booleschen Signals in ein LWORD (z. B. 1 oder 0 in einem 64‑Bit-Wort) wird von der zugrunde liegenden Adapter-Implementierung oder der Host-Umgebung bereitgestellt.

## Technische Besonderheiten

- **Composite‑Architektur**: Der FB enthält kein internes ECC (Execution Control Chart) und keine eigene Logik. Er besteht lediglich aus zwei Adapterverbindungen und einfachen Durchleitungen.
- **Typzuordnung**: Die Zuordnung von BOOL zu LWORD erfolgt implizit. Der Anwender muss sicherstellen, dass die angeschlossenen Adapter die Konvertierung korrekt unterstützen.
- **Projektstruktur**: Der Baustein ist im Paket `adapter::conversion::unidirectional` abgelegt, was seine Funktion als unidirektionaler Konvertierungsadapter kennzeichnet.

## Zustandsübersicht

Der FB besitzt keinen Zustandsautomaten und keine eigenen Zustände. Er arbeitet ereignisgesteuert und reagiert passiv auf Signale des AX‑Adapters.

## Anwendungsszenarien

- Einbinden einer alten Bool‑Schnittstelle (AX) in ein System, das nur LWORD‑Adapter (AL) unterstützt.
- Temporäre Brückenschaltung während der Migration von Feldbusprotokollen.
- Testumgebungen, in denen ein boolesches Signal als 64‑Bit-Wert interpretiert werden soll.

## Vergleich mit ähnlichen Bausteinen

Es existieren weitere Konvertierungsbausteine wie z. B. `AL_TO_AX` (Rückwandlung von LWORD nach BOOL) oder `BOOL_TO_LWORD` (direkte Umwandlung ohne Adapter-Kapselung). Im Gegensatz zu diesen reinen Wertwandlern kapselt **AX_TO_AL** die gesamte Adapter‑Schnittstelle, sodass der Anwender nur die Adapter verbinden muss.

## Fazit

Der Funktionsblock **AX_TO_AL** ist ein schlanker, aber nützlicher Adapter‑Koppler. Er reduziert den Aufwand, wenn unterschiedliche Adapterformate in einem Automatisierungssystem zusammengeführt werden müssen, und erfordert keine eigenen Logik- oder Zustandsdefinitionen. Die einfache Struktur erleichtert das schnelle Einfügen in bestehende IEC‑61499‑Netzwerke.