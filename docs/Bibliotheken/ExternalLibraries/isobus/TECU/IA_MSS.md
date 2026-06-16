# IA_MSS


![IA_MSS](./IA_MSS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **IA_MSS** stellt einen ISOBUS-Adapter für die maschinenselektierte Geschwindigkeit (Machine Selected Speed, MSS) dar. Er kapselt die Kommunikation mit dem zugrunde liegenden ISOBUS-Protokoll (PGN 61474) und stellt die ermittelten Werte für Geschwindigkeit, zurückgelegte Distanz und Timeout-Status über standardisierte Adapter-Schnittstellen bereit. Der Baustein ist typischerweise in einem ISOBUS-fähigen Steuergerät (TECU) eingebettet und ermöglicht eine einfache Integration in IEC 61499-basierte Automatisierungssysteme.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INIT | EInit | Dienstinitialisierung; wird mit dem Daten-Eingang `QI` ausgelöst. |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INITO | EInit | Bestätigung der Initialisierung; liefert die Ausgangsdaten `QO` und `STATUS`. |

### **Daten-Eingänge**

| Variable | Typ | Beschreibung |
|----------|-----|--------------|
| QI | BOOL | Qualifizierer für den Initialisierungseingang. |

### **Daten-Ausgänge**

| Variable | Typ | Beschreibung |
|----------|-----|--------------|
| QO | BOOL | Qualifizierer für den Initialisierungsausgang. |
| STATUS | STRING | Statusmeldung der Initialisierung. |

### **Adapter**

| Adapter | Typ | Beschreibung |
|---------|-----|--------------|
| SPEED | adapter::types::unidirectional::AUI | Ausgang für die maschinenselektierte Geschwindigkeit (Wert vom Typ `AUI`). |
| DISTANCE | adapter::types::unidirectional::AUDI | Ausgang für die maschinenselektierte Distanz (Wert vom Typ `AUDI`). |
| TIMEOUT | adapter::types::unidirectional::AX | Ausgang für den Timeout-Status (Wert vom Typ `AX`). |

## Funktionsweise
Der **IA_MSS**-Baustein ist als reiner Adapter-Wrapper realisiert. Er enthält intern eine Instanz des Funktionsblocks `isobus::tecu::I_MSS` (*I_CORE*), der die eigentliche ISOBUS-Logik implementiert. Über die Event- und Datenverbindungen werden die externen Schnittstellen des Adapters auf die interne Komponente abgebildet:

1. **Initialisierung** – Ein Ereignis auf `INIT` (mit gesetztem `QI`) aktiviert `I_CORE.INIT`. Nach erfolgreicher Initialisierung wird `INITO` ausgelöst, das die Qualifizierer `QO` und `STATUS` an die Ausgänge des Adapters weitergibt.
2. **Datenbereitstellung** – Der interne Baustein liefert die selektierte Geschwindigkeit (`SELECTEDMACHINESPEED`), die Distanz (`SELECTEDMACHINEDISTANCE`) sowie den Timeout-Status (`Q_timeout`). Diese Werte werden über die Adapter `SPEED`, `DISTANCE` und `TIMEOUT` ausgegeben, sobald die entsprechenden Ereignisse (`IND` bzw. `TIMEOUT`) eintreffen.
Der Adapter stellt also eine saubere Trennung zwischen der ISOBUS-Kommunikation und der Applikationsebene her.

## Technische Besonderheiten
- **Normkonformität** – Der Baustein basiert auf dem ISOBUS-Standard ISO 11783-7 (PGN 61474) für die maschinenselektierte Geschwindigkeit.
- **Unidirektionale Adapter** – Die Ausgänge `SPEED`, `DISTANCE` und `TIMEOUT` sind als unidirektionale Adapter (Typen `AUI`, `AUDI`, `AX`) definiert. Sie übertragen nur Daten vom Baustein zur aufrufenden Applikation; eine Rückkopplung ist nicht vorgesehen.
- **Adapter-Wrapper** – Die interne Logik ist vollständig in der Komponente `I_CORE` gekapselt. `IA_MSS` dient ausschließlich der Schnittstellenanpassung und Event-Weiterleitung.
- **Fehlerbehandlung** – Der Initialisierungsstatus wird über `STATUS` (STRING) und `QO` (BOOL) signalisiert. Ein eventueller Timeout wird über den `TIMEOUT`-Adapter gemeldet.

## Zustandsübersicht
Da der Baustein keinen eigenen Ausführungszustand (ECC) besitzt, ergibt sich der Zustand aus dem Zusammenspiel von Eingangs- und Ausgangsereignissen:

| Zustand | Beschreibung |
|---------|--------------|
| **Nicht initialisiert** | Nach dem Systemstart oder nach einer fehlgeschlagenen Initialisierung. `INIT` kann ausgelöst werden. |
| **Initialisiert** | Nach erfolgreichem Durchlauf von `INIT` → `INITO` mit gesetztem `QO`. Die Adapter liefern gültige Werte. |
| **Fehler/Timeout** | Falls die interne Initialisierung fehlschlägt oder ein Timeout erkannt wird, wird dies über `STATUS` und den `TIMEOUT`-Adapter signalisiert. |

## Anwendungsszenarien
- **ISOBUS-Steuergeräte (TECU)** – Integration in landwirtschaftliche Maschinen, um die von der Zugmaschine oder dem Gerät bereitgestellte Geschwindigkeit auszulesen.
- **Fahrgeschwindigkeitsregelung** – Verwendung der selektierten Geschwindigkeit für teilflächenspezifische Applikationen (z. B. Düngung, Pflanzenschutz).
- **Distanz- und Wegmessung** – Auswertung der zurückgelegten Distanz zur Steuerung von Arbeitsbreiten oder Dokumentationszwecken.
- **Überwachung der Kommunikation** – Erkennung von Timeout-Situationen im ISOBUS-Netzwerk durch den `TIMEOUT`-Adapter.

## Vergleich mit ähnlichen Bausteinen
- **I_MSS (direkt)** – Der interne Baustein `I_CORE` vom Typ `isobus::tecu::I_MSS` bietet die gleiche Funktionalität, aber ohne Adapter-Schnittstellen. `IA_MSS` erleichtert die Einbindung in Systeme, die auf standardisierten Adaptern (AUI, AUDI, AX) basieren.
- **Andere ISOBUS-Adapter** – Es existieren zahlreiche Adapter für andere PGNs (z. B. für GPS, Arbeitsbreite, Motordrehzahl). `IA_MSS` ist spezifisch auf die maschinenselektierte Geschwindigkeit ausgelegt.

## Fazit
Der **IA_MSS**-Baustein ist ein praktischer Adapter-Wrapper für den ISOBUS-Datensatz „Machine Selected Speed“. Er abstrahiert die Kommunikation mit dem ISOBUS-Protokoll und stellt die relevanten Größen (Geschwindigkeit, Distanz, Timeout) über standardisierte unidirektionale Adapter bereit. Dadurch wird eine einfache und wiederverwendbare Integration in IEC 61499-Anwendungen für landwirtschaftliche Maschinen ermöglicht. Der Baustein ist normkonform, robust durch Timeout-Überwachung und eignet sich besonders für den Einsatz in TECU-basierten Steuerungen.