# IA_RHS


![IA_RHS](./IA_RHS.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **IA_RHS** (ISOBUS Adapter for Rear Hitch Status) dient als Schnittstelle zwischen dem ISOBUS-System (gemäß ISO 11783-7, PGN 65093) und einem Anwendungsnetzwerk. Er kapselt die Kommunikation mit dem internen Baustein I_RHS und stellt die gemessenen Heckkraftheber-Daten (Position, Kraft, Zugkraft) sowie den Timeout-Status über standardisierte, unidirektionale Adapter zur Verfügung. Der Baustein wird hauptsächlich in Traktor- und Landmaschinensteuerungen eingesetzt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar               | Mit Daten |
|------|-------|-------------------------|-----------|
| INIT | EInit | Service Initialization  | QI        |

### **Ereignis-Ausgänge**

| Name  | Typ   | Kommentar                | Mit Daten      |
|-------|-------|--------------------------|----------------|
| INITO | EInit | Initialization Confirm   | QO, STATUS     |

### **Daten-Eingänge**

| Name | Typ  | Kommentar               |
|------|------|-------------------------|
| QI   | BOOL | Event Input Qualifier   |

### **Daten-Ausgänge**

| Name   | Typ    | Kommentar                |
|--------|--------|--------------------------|
| QO     | BOOL   | Event Output Qualifier   |
| STATUS | STRING | Statusmeldung            |

### **Adapter**

| Name    | Typ      | Kommentar                                 |
|---------|----------|-------------------------------------------|
| POSITION| AUS      | Rear Hitch Position                       |
| FORCE   | AUS      | Rear Nominal Lower Link Force             |
| DRAFT   | AUI      | Rear Draft                                |
| TIMEOUT | AX       | Timeout Status                            |

## Funktionsweise

Der Baustein wird durch das Ereignis **INIT** aktiviert. Dabei wird das Qualifier-Signal **QI** an den internen Funktionsblock **I_RHS** weitergeleitet. Nach erfolgreicher Initialisierung (oder einem Fehler) meldet sich der Baustein über das Ereignis **INITO** zurück und gibt die Ausgangssignale **QO** und **STATUS** aus. Gleichzeitig werden die vom I_RHS gelieferten Daten (Position, Unterlenkerkraft, Zugkraft) auf die entsprechenden Adapter **POSITION**, **FORCE** und **DRAFT** gelegt. Der Timeout-Status des I_RHS wird über den Adapter **TIMEOUT** ausgegeben. Die Adapter verwenden jeweils das unidirektionale Datenformat (z. B. AUS für analoge, unskalierte Werte). Die Ausgabe auf die Adapter erfolgt jeweils mit einem eigenen Ereignis (über interne Verbindungen von I_CORE.IND). Somit kann ein empfangender Baustein auf das Eintreffen neuer Daten reagieren.

## Technische Besonderheiten

- Der Baustein basiert auf dem ISOBUS-Standard ISO 11783-7 und verwendet die PGN 65093.
- Die internen Berechnungen und die ISOBUS-Kommunikation werden vollständig vom Baustein **I_RHS** durchgeführt. IA_RHS dient ausschließlich als Adapter-Wrapper zur Bereitstellung der Daten an das 4diac-Netzwerk.
- Alle vier Adapter sind unidirektional (Ausgang), sodass nur Daten gesendet, aber nicht vom angeschlossenen Baustein empfangen werden.
- Die Datenausgabe auf die Adapter erfolgt zeitgleich mit dem Ereignis **IND** (intern), das vom I_RHS ausgeht.
- Timeout-Informationen werden getrennt vom Hauptdatenpfad bereitgestellt.

## Zustandsübersicht

Der Baustein besitzt keine explizit modellierten Zustände. Sein Verhalten wird durch den internen Baustein I_RHS bestimmt:
- **Initialisierung (INIT)**: Der Qualifier QI steuert die Aktivierung.
- **Betrieb**: Nach erfolgreicher Initialisierung liefert I_RHS zyklisch oder ereignisgesteuert neue Daten an die Adapter.
- **Fehler/Timeout**: Ein Timeout wird über den Adapter TIMEOUT signalisiert, der Status über den Ausgang **STATUS** als Text.

## Anwendungsszenarien

- **Traktorsteuerung mit ISOBUS-Anbindung**: Einlesen der Heckkraftheberdaten (Hitch Status) von einem ISOBUS-fähigen Terminal oder Steuergerät und Weiterleitung an eine übergeordnete Steuerung.
- **Landwirtschaftliche Arbeitsgeräte**: Anbindung von Anbaugeräten, die die Heckkraftheberposition oder -kraft benötigen (z. B. Pflugtiefenregelung).
- **Diagnose und Überwachung**: Erfassung von Timeout-Status und Systemzustand für Wartungs- und Fehleranalysen.

## Vergleich mit ähnlichen Bausteinen

Im Unterschied zu einem allgemeinen ISOBUS-Empfänger (z. B. einem rohen PGN-Parser) abstrahiert **IA_RHS** die ISOBUS-spezifische Nachrichtenverarbeitung und stellt die Daten in normierten Adapterformaten bereit. Gegenüber einem direkten I_RHS-Baustein bietet IA_RHS den Vorteil, dass die Datenausgabe über separate Adapter erfolgt, was eine lose Kopplung im Netzwerk und einfachere Wiederverwendung ermöglicht. Bausteine wie **IA_RHC** (Rear Hitch Control) oder **IA_PTO** folgen einem ähnlichen Adapter-Konzept, sind jedoch für andere ISOBUS-Funktionen ausgelegt.

## Fazit

Der IA_RHS-Baustein ist eine praktische, standardkonforme Kapselung des Heckkraftheber-Status nach ISO 11783-7. Er vereinfacht die Integration von ISOBUS-Daten in ein 4diac-basiertes Steuerungssystem, indem er die komplexe Busschnittstelle hinter einfach nutzbaren Adaptern verbirgt. Die Aufteilung in mehrere Datenadapter sowie die Bereitstellung eines Timeout-Status machen ihn flexibel einsetzbar für verschiedene Anwendungen der Agrartechnik.