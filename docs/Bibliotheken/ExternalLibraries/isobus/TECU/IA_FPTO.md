# IA_FPTO


![IA_FPTO](./IA_FPTO.svg)

*[Bild des Funktionsblocks, falls vorhanden]*

* * * * * * * * * *

## Einleitung

Der Funktionsblock **IA_FPTO** dient als ISOBUS-Adapter für die Frontzapfwelle (Front Power Take Off, FPTO) gemäß ISO 11783-7 (PGN 65092). Er kapselt die interne Logik des Bausteins **I_FPTO** und stellt die relevanten Signale über standardisierte Adapter-Schnittstellen zur Verfügung. Damit wird eine nahtlose Integration in ISOBUS-basierte Steuerungssysteme ermöglicht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Beschreibung | Mit Variablen |
|----------|-----|--------------|---------------|
| INIT | EInit | Service-Initialisierung | QI |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Beschreibung | Mit Variablen |
|----------|-----|--------------|---------------|
| INITO | EInit | Bestätigung der Initialisierung | QO, STATUS |

### **Daten-Eingänge**

| Variable | Typ | Beschreibung |
|----------|-----|--------------|
| QI | BOOL | Qualifikator für den INIT-Eingang |

### **Daten-Ausgänge**

| Variable | Typ | Beschreibung |
|----------|-----|--------------|
| QO | BOOL | Qualifikator für den INITO-Ausgang |
| STATUS | STRING | Statusmeldung nach der Initialisierung |

### **Adapter**

| Adapter | Typ | Beschreibung |
|---------|-----|--------------|
| SPEED | adapter::types::unidirectional::AUI | Ausgangsdrehzahl der Frontzapfwellenwelle (Istwert) |
| SPEED_SET | adapter::types::unidirectional::AUI | Sollwert der Frontzapfwellendrehzahl |
| TIMEOUT | adapter::types::unidirectional::AX | Timeout-Status der Kommunikation |

Alle Adapter sind unidirektional ausgeführt: Die Werte werden vom FB gesendet, aber nicht empfangen.

## Funktionsweise

Der FB wird über das Ereignis **INIT** aktiviert. Sofern der Eingangsqualifikator **QI** gesetzt ist, initialisiert die interne Logik die Verbindung zur ISOBUS-Kommunikationsschicht. Nach erfolgreicher Initialisierung wird das Ereignis **INITO** ausgelöst, die Ausgangsvariablen **QO** und **STATUS** geben den Status der Initialisierung zurück.

Nach der Initialisierung arbeitet der Baustein autonom: Er liefert zyklisch die aktuelle Drehzahl der Frontzapfwelle über den Adapter **SPEED** sowie den zugehörigen Sollwert über **SPEED_SET**. Der Adapter **TIMEOUT** zeigt an, ob ein Kommunikationszeitfehler aufgetreten ist (z.B. wenn das Steuergerät keine aktuellen Daten sendet). Diese Ausgaben werden kontinuierlich aktualisiert, solange die Initialisierung gültig bleibt.

## Technische Besonderheiten

- Der FB basiert auf dem internen Baustein **I_FPTO** aus der Bibliothek `isobus::tecu`. Die Adapter-Schnittstellen entkoppeln die Anwendung von der konkreten Signalkodierung des ISOBUS.
- Die Adapter **SPEED** und **SPEED_SET** verwenden den unidirektionalen Typ **AUI** (Adresse unbekannt, Integer), der für analoge Werte wie Drehzahlen geeignet ist.
- Der Adapter **TIMEOUT** nutzt den Typ **AX** (Adresse unbekannt, Boolescher Wert), um den Timeout-Zustand binär darzustellen.
- Der FB enthält kein eigenes Verhalten auf Ereignisse außerhalb der Initialisierung; die Datenaktualisierung erfolgt implizit über die Netzwerkverbindungen des Bausteins **I_FPTO**.

## Zustandsübersicht

Der FB besitzt keine explizite Zustandsmaschine. Das Verhalten lässt sich wie folgt beschreiben:

1. **Initialisierungsphase**: Nach dem Ereignis **INIT** wird der interne FB **I_FPTO** initialisiert. Während dieser Phase sind die Adapterausgänge ungültig oder auf einem definierten Startwert (0/FALSE).
2. **Aktive Phase**: Nach Bestätigung der Initialisierung (**INITO**) stehen die aktuellen Werte an den Adaptern **SPEED**, **SPEED_SET** und **TIMEOUT** stabil zur Verfügung.
3. **Fehlerzustand**: Tritt ein Timeout auf, wird der Adapter **TIMEOUT** auf TRUE gesetzt. Die Drehzahlwerte bleiben möglicherweise auf dem letzten gültigen Wert stehen, bis die Kommunikation wiederhergestellt ist.

Eine erneute Initialisierung (erneuter INIT-Impuls) kann den FB zurücksetzen und neu starten.

## Anwendungsszenarien

- **Steuerung der Frontzapfwelle in landwirtschaftlichen Traktoren**: Der FB empfängt über den ISOBUS die Soll- und Ist-Drehzahlen der Frontzapfwelle und gibt sie an übergeordnete Steuerungen oder Anzeigen weiter.
- **Integration in ISOBUS-konforme Anbaugeräte**: Anbaugeräte wie Frontmähwerke oder Frontlader können die Drehzahl- und Timeout-Informationen nutzen, um ihre Funktionen daran anzupassen.
- **Ferndiagnose und Überwachung**: Das Timeout-Signal ermöglicht eine Überwachung der Kommunikationsverbindung zur Zapfwellensteuerung, was für Fehlererkennung und Sicherheitsfunktionen wichtig ist.

## Vergleich mit ähnlichen Bausteinen

Im ISOBUS-Umfeld gibt es weitere Adapter für andere Zapfwellen (z.B. **IA_RPTO** für die Heckzapfwelle) oder für allgemeine Steuergeräte. **IA_FPTO** ist speziell auf die Frontzapfwelle zugeschnitten und enthält nur die für diese Anwendung relevanten Signale (Drehzahl Ist/Soll und Timeout). Im Vergleich zu einem generischen ISOBUS-Adapter bietet er somit eine höhere Abstraktion und einfachere Handhabung für den Anwendungsentwickler.

## Fazit

Der Funktionsblock **IA_FPTO** stellt eine schlanke und spezifische Schnittstelle für die ISOBUS-konforme Nutzung der Frontzapfwelle dar. Durch die Kapselung der internen Kommunikationslogik und die Bereitstellung über unidirektionale Adapter wird die Integration in Steuerungsanwendungen erheblich vereinfacht. Der Baustein eignet sich besonders für Traktoren und landwirtschaftliche Maschinen, bei denen eine zuverlässige Drehzahlüberwachung und Timeout-Erkennung erforderlich ist.