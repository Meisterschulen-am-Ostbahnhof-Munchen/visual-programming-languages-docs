# AX_NOOP_INIT

![AX_NOOP_INIT](./AX_NOOP_INIT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AX_NOOP_INIT` ist ein No-Operation-Baustein, der eingehende Ereignisse und Daten von einer Adapter-Schnittstelle unverändert an eine Ausgangs-Schnittstelle weiterleitet. Zusätzlich besitzt er eine Initialisierungsfunktion, die beim Eintreffen des INIT-Ereignisses sowohl die Bestätigung INITO als auch das Ausgangsereignis des Adapters auslöst. Er dient als einfacher Durchschleif- oder Platzhalter-Baustein in der Automatisierungstechnik.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (Typ: `EInit`): Initialisierungsanforderung. Löst beim Eintreffen die Ereignisausgänge `INITO` und `OUT.E1` aus.

### **Ereignis-Ausgänge**

- **INITO** (Typ: `EInit`): Initialisierungsbestätigung. Wird direkt durch `INIT` ausgelöst.

### **Daten-Eingänge**

Der Baustein besitzt keine separaten Dateneingänge auf der obersten Ebene. Sämtliche Daten werden über den eingehenden Adapter (`IN`) transportiert.

### **Daten-Ausgänge**

Der Baustein besitzt keine separaten Datenausgänge auf der obersten Ebene. Sämtliche Daten werden über den ausgehenden Adapter (`OUT`) transportiert.

### **Adapter**

- **IN** (Socket): Eingangsadapter vom Typ `adapter::types::unidirectional::AX`. Stellt eine Ereignisschnittstelle `E1` und eine Datenschnittstelle `D1` zur Verfügung.
- **OUT** (Plug): Ausgangsadapter vom Typ `adapter::types::unidirectional::AX`. Stellt eine Ereignisschnittstelle `E1` und eine Datenschnittstelle `D1` zur Verfügung.

## Funktionsweise

Der Baustein arbeitet als reiner Durchlaufschieber:

1. **Ereignisweiterleitung**:
   - Das INIT-Ereignis wird nach `INITO` und nach `OUT.E1` weitergeleitet.
   - Das Ereignis `IN.E1` wird direkt zu `OUT.E1` durchgeschliffen.

2. **Datenweiterleitung**:
   - Der Wert von `IN.D1` wird unverändert auf `OUT.D1` kopiert.

Es erfolgt keinerlei Verarbeitung oder Veränderung der Daten. Der Baustein ist zustandslos und führt lediglich die Signal- und Datenpfade zusammen.

## Technische Besonderheiten

- Der Baustein kombiniert die reine Durchschleiffunktion eines No-Operation-Bausteins mit einer initialisierungsgesteuerten Ausgabe auf den Ausgangsadapter.
- Die Verwendung von Adaptern (plug/socket) ermöglicht eine saubere Kapselung und Wiederverwendbarkeit der Schnittstellendefinition.
- Es existieren keine internen Zustände oder Zeitverhalten – die Reaktion erfolgt unmittelbar bei Ereigniseingang.

## Zustandsübersicht

Der `AX_NOOP_INIT` besitzt keine eigenen Zustände. Er reagiert sofort auf jedes eingehende Ereignis und leitet es samt den zugehörigen Daten weiter. Eine Zustandsmaschine ist nicht vorhanden.

## Anwendungsszenarien

- **Initialisierungskaskaden**: Wenn mehrere Bausteine in einer Kette initialisiert werden müssen, kann `AX_NOOP_INIT` als Verbindungsglied dienen, das eine INIT-Anforderung sowohl bestätigt als auch an den nachfolgenden Baustein weitergibt.
- **Test- und Simulationsumgebungen**: Als Platzhalter, um Schnittstellen zu überbrücken und Funktionalitäten ohne tatsächliche Logik zu testen.
- **Adapter-Durchschleifung**: Wenn ein Adapter-Signal unverändert von einer Quelle zu einem Ziel geführt werden soll, ohne zusätzliche Verarbeitung.

## Vergleich mit ähnlichen Bausteinen

Ein reiner `AX_NOOP` (ohne INIT) würde nur die IN/OUT-Ereignisse und -Daten durchschleifen, aber keine separate Initialisierungsbestätigung (`INITO`) generieren. Der `AX_NOOP_INIT` erweitert diese Funktion um die INIT-Behandlung, sodass er in Initialisierungsabläufen direkt eingesetzt werden kann.

## Fazit

Der `AX_NOOP_INIT` ist ein einfacher, aber nützlicher Funktionsblock für die Durchleitung von Ereignissen und Daten auf Adapterebene. Seine INIT-Funktionalität macht ihn besonders in Initialisierungsketten oder als Test-Ersatzbaustein wertvoll. Durch seine Zustandslosigkeit ist er leicht verständlich und ressourcenschonend.
