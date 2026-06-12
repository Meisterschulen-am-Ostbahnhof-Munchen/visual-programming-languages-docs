# logiBUS_QWA_SERVO


![logiBUS_QWA_SERVO](./logiBUS_QWA_SERVO.svg)

* * * * * * * * * *

## Einleitung

Der **logiBUS_QWA_SERVO** ist ein Composite-Funktionsblock (CFB) für die Ausgabe von Servo-Steuerworten über einen logiBUS. Er kapselt die Initialisierung, Parametrierung und Ausgabe auf Basis eines internen Bausteins (`logiBUS_QW_SERVO`) und stellt eine standardisierte Schnittstelle zur Verfügung. Entwickelt unter der Eclipse Public License 2.0 (Copyright 2026 HR Agrartechnik GmbH).  
*Kommentar aus der XML: „Composite FB for servo word output data“.*

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Mit Variablen          | Beschreibung            |
|----------|-------|------------------------|-------------------------|
| `INIT`   | EInit | `QI`, `PARAMS`, `Output` | Service Initialisierung |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Mit Variablen | Beschreibung                          |
|----------|-------|---------------|---------------------------------------|
| `INITO`  | EInit | `QO`, `STATUS` | Bestätigung der Initialisierung       |
| `CNF`    | Event | `QO`, `STATUS` | Bestätigung einer angeforderten Aktion|

### **Daten-Eingänge**

| Name     | Typ         | Initialwert | Beschreibung                                      |
|----------|-------------|-------------|---------------------------------------------------|
| `QI`     | `BOOL`      | –           | Ereignis-Eingangsqualifizierer                    |
| `PARAMS` | `STRING`    | –           | Service-Parameter (z. B. Bus‑Konfiguration)       |
| `Output` | `logiBUS::io::DQ::logiBUS_DO_S` | `Invalid`   | Identifiziert den Ausgang (`Output_Q1` … `Output_Q8`)|

### **Daten-Ausgänge**

| Name     | Typ      | Beschreibung                    |
|----------|----------|---------------------------------|
| `QO`     | `BOOL`   | Ereignis-Ausgangsqualifizierer  |
| `STATUS` | `STRING` | Statusmeldung (Fehler, OK, etc.)|

### **Adapter**

| Adapter | Typ                                   | Richtung | Beschreibung                          |
|---------|---------------------------------------|----------|---------------------------------------|
| `OUT`   | `adapter::types::unidirectional::AW`  | Socket   | Ausgangsdaten zur Ressource (Wortausgabe)|

## Funktionsweise

Der Baustein arbeitet als Composite:  
1. **Initialisierung** (`INIT`):  
   - Qualifizierer `QI`, Parameterstring `PARAMS` und der gewünschte Ausgang (`Output`) werden übergeben.  
   - Der interne FB `logiBUS_QW_SERVO` wird initialisiert; nach erfolgreicher Initialisierung wird `INITO` gesendet.  
2. **Ausführung** (über Adapter `OUT`):  
   - Das Ereignis `OUT.E1` wird vom Adapter empfangen und an den internen FB als `REQ` weitergeleitet.  
   - Gleichzeitig werden die Daten über `OUT.D1` an den internen FB (`QX.OUT`) übergeben.  
3. **Rückmeldung**:  
   - Der interne FB signalisiert Abschluss über `CNF`, das an den externen Ausgang `CNF` weitergereicht wird.  
   - Status und Qualifizierer werden über `QO` und `STATUS` ausgegeben.

Die eigentliche Ansteuerung der Servo-Hardware erfolgt über den Adapter `OUT`, der mit der Ressource verbunden wird.

## Technische Besonderheiten

- **Composite‑Design**: Kapselt die komplexe Initialisierungs‑ und Ablaufsteuerung des Servo‑Wortausgangs.  
- **Adapter‑Schnittstelle**: Der unidirektionale Adapter `AW` ermöglicht eine flexible Anbindung an verschiedene physische Ausgangskanäle.  
- **Ausgangsauswahl**: Über den Eingang `Output` kann zwischen acht verschiedenen Ausgängen (`Q1`…`Q8`) gewählt werden; der Initialwert `Invalid` verhindert ungewollte Aktionen vor der Konfiguration.  
- **Fehlerbehandlung**: Statusinformationen werden über `STATUS` bereitgestellt; Event‑Sequenzen garantieren eine korrekte Ablaufsteuerung.  
- **Lizenz**: Eclipse Public License 2.0 (EPL‑2.0) – freie Nutzung und Weiterentwicklung unter den Lizenzbedingungen.

## Zustandsübersicht

Der FB besitzt keine explizit modellierte Zustandsmaschine, jedoch ergibt sich aus den Ereignis‑Abläufen folgende implizite Zustandslogik:

| Zustand       | Auslöser                | Reaktion                                     |
|---------------|-------------------------|----------------------------------------------|
| **Idle**      | –                       | Warten auf `INIT`                            |
| **Initialize**| `INIT` empfangen        | Interner FB wird gestartet                   |
| **Ready**     | `INITO` gesendet        | Bereit für Anforderungen über den Adapter    |
| **Busy**      | `OUT.E1` empfangen      | Aktion wird ausgeführt (`REQ` läuft)         |
| **Done**      | `CNF` gesendet          | Aktion abgeschlossen, zurück zu **Ready**    |
| **Error**     | Fehler während Initialisierung oder Aktion | `STATUS` enthält Fehlerbeschreibung; evtl. erneute Initialisierung nötig |

## Anwendungsszenarien

- **Landwirtschaftliche Maschinen**: Ansteuerung von Servoantrieben (z. B. für Klappen, Ventile, Aktuatoren) über einen logiBUS‑Fieldbus.  
- **Modularer Ausgangsbaustein**: Einsatz in verteilten Steuerungen, bei denen mehrere Servo‑Ausgänge je nach Maschinenkonfiguration parametriert werden müssen.  
- **Parametrierbare Konfiguration**: Über `PARAMS` können Bus‑Adresse, Protokoll‑Einstellungen oder Zeitverhalten definiert werden.

## Vergleich mit ähnlichen Bausteinen

- **logiBUS_QW_SERVO** (interner FB): Realisiert die direkte Wortausgabe und Bus‑Kommunikation, während `logiBUS_QWA_SERVO` eine höhere Abstraktionsebene mit konsolidierten Ein‑/Ausgängen bietet.  
- **logiBUS_DO_S‑Familie**: Andere Bausteine dieser Familie adressieren einzelne diskrete Ausgänge (z. B. logiBUS_DO) – der hier beschriebene FB ist speziell für Servo‑Wortdaten und mehrere simultane Ausgänge ausgelegt.  
- **Generische Wort‑Ausgangs‑FBs**: Im Vergleich zu standardisierten `W`‑Typ‑Bausteinen bietet dieser FB eine an den Servo‑Anwendungsfall angepasste Schnittstelle (z. B. `logiBUS_DO_S`‑Typ).

## Fazit

Der `logiBUS_QWA_SERVO` ist ein gut strukturierter Composite‑Funktionsblock, der die Ansteuerung von Servo‑Wortausgängen auf einem logiBUS vereinfacht. Durch die Trennung von Initialisierung, Ausführung und Fehlerrückmeldung sowie die Verwendung eines Adapters für die Hardwareschnittstelle eignet er sich hervorragend für modulare Automatisierungslösungen in der Landtechnik und ähnlichen Industrien. Die Lizenzierung unter EPL‑2.0 ermöglicht uneingeschränkte Nutzung und Anpassung.