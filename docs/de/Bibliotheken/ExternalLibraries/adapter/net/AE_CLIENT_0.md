# AE_CLIENT_0

![AE_CLIENT_0](AE_CLIENT_0.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AE_CLIENT_0** ist ein Composite-Funktionsblock, der den netzwerkbasierten `CLIENT_0`-Funktionsblock aus der IEC 61499-Standardbibliothek kapselt und dessen Schnittstelle auf einen unidirektionalen **AE-Adapter** abbildet. Jedes am Adapter-Socket `TRIGGER` eintreffende Ereignis löst über `CLIENT_0` einen entfernten OPC-UA-**Methodenaufruf** unter der unter `ID` konfigurierten Adresse aus.

Im Unterschied zu `CLIENT_1_0` (Remote-Write eines Datenwerts) ruft `CLIENT_0` eine entfernte **Methode ohne Nutzdaten** auf – der passende Baustein für ereignisgesteuerte Trigger-Aktionen wie „Set“, „Reset“ oder „Toggle“ auf einem entfernten Knoten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (EInit): Initialisierungsereignis, verbunden mit `QI` und `ID`

### **Ereignis-Ausgänge**

- **INITO** (EInit): Bestätigung der Initialisierung, verbunden mit `QO` und `STATUS`
- **CNF** (Event): Bestätigung, dass der Methodenaufruf gesendet wurde, verbunden mit `QO` und `STATUS`

### **Daten-Eingänge**

- **QI** (BOOL): Qualifier-Eingang, öffnet (TRUE) bzw. schließt (FALSE) die Verbindung zum Server
- **ID** (WSTRING): Remote-Methodenadresse für den Aufruf

### **Daten-Ausgänge**

- **QO** (BOOL): Qualifier-Ausgang, Verbindungsstatus (identisch mit `CLIENT_0_1.QO`)
- **STATUS** (WSTRING): Statusinformationen als Unicode-String (identisch mit `CLIENT_0_1.STATUS`)

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| TRIGGER | adapter::types::unidirectional::AE | Socket (Eingang) | Auslösendes Ereignis für den Methodenaufruf |

## Funktionsweise

1. Über das `INIT`-Ereignis wird der interne `CLIENT_0_1`-Block mit `QI` und `ID` initialisiert; er baut die Verbindung zum entfernten Server auf. Bei Erfolg quittiert er mit `INITO`.
2. Jedes am Adapter-Socket `TRIGGER` eintreffende Ereignis (`TRIGGER.E1`) löst direkt das Sendeereignis `REQ` des internen `CLIENT_0_1`-Blocks aus.
3. `CLIENT_0_1` ruft daraufhin die unter `ID` konfigurierte Remote-Methode auf und bestätigt mit `CNF`, das nach außen geführt wird.

## Technische Besonderheiten

- **Reiner Trigger, keine Nutzdaten**: Anders als `AX_CLIENT_1_0` überträgt `AE_CLIENT_0` keinen Datenwert – der Adapter liefert lediglich das auslösende Ereignis.
- **Kapselung**: Die ursprüngliche Ereignis-/Daten-Schnittstelle von `CLIENT_0` (inkl. `REQ`) wird nach innen verlegt; nach außen ist nur noch die AE-Adapter-Schnittstelle sichtbar.
- Baustein der Grundfamilie, aus der [ASR_CLIENT_0](ASR_CLIENT_0.md) (2 Trigger) und [ASRT_CLIENT_0](ASRT_CLIENT_0.md) (3 Trigger) durch Parallelschaltung mehrerer `CLIENT_0`-Instanzen hervorgehen.

## Zustandsübersicht

1. **Nicht initialisiert**: Der Block wartet auf das `INIT`-Ereignis.
2. **Initialisiert**: Die Verbindung zum entfernten Server ist aufgebaut, der Block ist bereit, Methodenaufrufe auszulösen.
3. **Sendeaktiv**: Ein am AE-Socket eintreffendes Ereignis löst den Remote-Methodenaufruf über den internen `CLIENT_0`-Block aus.

## Anwendungsszenarien

- Fernauslösen einer einzelnen entfernten Aktion (z. B. „Start“, „Trigger“) ohne zugehörigen Datenwert
- Baustein für zusammengesetzte Mehrfach-Trigger-Bausteine wie [ASR_CLIENT_0](ASR_CLIENT_0.md) und [ASRT_CLIENT_0](ASRT_CLIENT_0.md)
- Netzwerkkopplung in AE-Adapter-basierten Anwendungen

## Vergleich mit ähnlichen Bausteinen

- **CLIENT_0**: Der reine Standardbaustein exponiert seine Schnittstelle als Events/Variablen (`REQ`, ...). **AE_CLIENT_0** kapselt diesen Baustein und stellt nur noch den AE-Adapter bereit.
- **AX_CLIENT_1_0**: Strukturell ähnlich aufgebaut, kapselt aber `CLIENT_1_0` (Remote-Write eines Datenwerts) statt `CLIENT_0` (reiner Methodenaufruf ohne Daten).
- **[ASR_CLIENT_0](ASR_CLIENT_0.md)** / **[ASRT_CLIENT_0](ASRT_CLIENT_0.md)**: Erweitern dasselbe Muster auf 2 bzw. 3 parallele Trigger (Set/Reset bzw. Set/Reset/Toggle).

## Fazit

**AE_CLIENT_0** verbindet die Trigger-Semantik des Standardbausteins `CLIENT_0` mit der Adapter-basierten Ereignisverarbeitung. Die reduzierte AE-Schnittstelle macht den Baustein ideal, um in durchgängig adapterbasierten IEC 61499-Anwendungen einen entfernten OPC-UA-Methodenaufruf direkt auszulösen.
