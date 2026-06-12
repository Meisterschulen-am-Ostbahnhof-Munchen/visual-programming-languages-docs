# IA_RPTO


![IA_RPTO](./IA_RPTO.svg)

**********

## Einleitung

Der Baustein IA_RPTO ist ein ISOBUS-Adapter für die hintere Zapfwelle (Rear Power Take Off, RPTO) gemäß ISO 11783‑7 (PGN 65091). Er stellt eine gekapselte Schnittstelle zu einem inneren I_RPTO-Funktionsblock bereit und gibt die wichtigsten Größen (Drehzahl, Sollwert, Timeout‑Status) über Adapter‑Ports nach außen.

## Schnittstellenstruktur

### **Ereignis‑Eingänge**

| Name  | Typ    | Kommentar                     | Mit Daten |
|-------|--------|-------------------------------|-----------|
| INIT  | EInit  | Service Initialization        | QI        |

### **Ereignis‑Ausgänge**

| Name  | Typ    | Kommentar                     | Mit Daten          |
|-------|--------|-------------------------------|--------------------|
| INITO | EInit  | Initialization Confirm        | QO, STATUS         |

### **Daten‑Eingänge**

| Name | Typ    | Kommentar                    |
|------|--------|------------------------------|
| QI   | BOOL   | Event Input Qualifier        |

### **Daten‑Ausgänge**

| Name   | Typ    | Kommentar                     |
|--------|--------|-------------------------------|
| QO     | BOOL   | Event Output Qualifier        |
| STATUS | STRING | Statusmeldung                 |

### **Adapter**

| Name      | Typ                                    | Kommentar                                   |
|-----------|----------------------------------------|---------------------------------------------|
| SPEED     | adapter::types::unidirectional::AUI    | Rear PTO output shaft speed                 |
| SPEED_SET | adapter::types::unidirectional::AUI    | Rear PTO output shaft speed set point       |
| TIMEOUT   | adapter::types::unidirectional::AX     | Timeout Status                              |

## Funktionsweise

Der Baustein instanziiert intern einen `I_RPTO`-Block, der die eigentliche ISOBUS-Kommunikation für die hintere Zapfwelle durchführt. Über ein INIT-Ereignis wird die Initialisierung angestoßen; bei erfolgreicher Ausführung quittiert INITO mit QO = TRUE und einem passenden STATUS. Die Werte `REAR_PTO_OUTP_SHAFT_SPEED`, `REAR_PTO_OUTP_SH_SPEED_SET` und `Q_timeout` des inneren Blocks werden direkt auf die entsprechenden Adapter-Ports SPEED, SPEED_SET und TIMEOUT weitergeleitet.

## Technische Besonderheiten

– Der Baustein arbeitet nach ISO 11783‑7 (PGN 65091) und ist für den Einsatz in landwirtschaftlichen Steuergeräten (Tractor ECU) vorgesehen.  
– Alle Adapter sind unidirektional (AUI, AX), d.h. sie liefern Daten nur in eine Richtung.  
– Der innere Block stammt aus dem Paket `isobus::tecu`.  
– Lizenz: Eclipse Public License 2.0.

## Zustandsübersicht

Der Funktionsblock kennt zwei Hauptzustände: **nicht initialisiert** und **initialisiert**. Nach Empfang von INIT führt der innere Block die Initialisierung durch. Bei Erfolg wird QO = TRUE gesetzt und der STATUS zeigt einen positiven Wert. Tritt ein Fehler oder Timeout auf, wird dies über den TIMEOUT‑Adapter und den STATUS signalisiert. Ein detailliertes Zustandsdiagramm liegt nicht als Teil der äußeren Beschreibung vor, da die komplette Logik im inneren Block implementiert ist.

## Anwendungsszenarien

– Integration einer ISOBUS‑kompatiblen Hinterzapfwelle in ein Traktorensteuergerät.  
– Überwachung und Regelung der Zapfwellendrehzahl über das ISOBUS‑Netzwerk.  
– Zeitüberwachung der Datenkommunikation zur Erkennung von Verbindungsabbrüchen.

## Vergleich mit ähnlichen Bausteinen

Verwandte Adapter‑Bausteine existieren für andere ISOBUS‑Funktionen, z.B. IA_FPTO (vordere Zapfwelle), IA_HITCH (Hubwerk) oder IA_TSC (Traktorsteuerung). Der wesentliche Unterschied liegt im verwendeten PGN (65091) und den spezifischen Datenpunkten (Drehzahl, Sollwert, Timeout). IA_RPTO bietet somit eine auf die hintere Zapfwelle zugeschnittene Schnittstelle.

## Fazit

IA_RPTO kapselt die ISOBUS‑Kommunikation für die hintere Zapfwelle und stellt die relevanten Informationen über klar definierte Adapter‑Ports zur Verfügung. Der Baustein vereinfacht die Einbindung in IEC 61499‑Applikationen und gewährleistet eine normkonforme Anbindung gemäß ISO 11783‑7.