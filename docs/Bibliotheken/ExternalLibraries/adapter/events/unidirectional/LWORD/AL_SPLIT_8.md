# AL_SPLIT_8


![AL_SPLIT_8](./AL_SPLIT_8.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AL_SPLIT_8` verteilt ein eingehendes unidirektionales AL-Signal (Socket `IN`) auf acht identische Ausgänge (Plugs `OUT1` bis `OUT8`). Er wird als generischer Baustein deklariert und dient der einfachen Signalvervielfachung in 4diac‑Anwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine

### **Ereignis-Ausgänge**
Keine

### **Daten-Eingänge**
Keine

### **Daten-Ausgänge**
Keine

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AL` | `IN` | Socket (Eingang) | Eingehendes AL-Signal |
| `adapter::types::unidirectional::AL` | `OUT1` … `OUT8` | Plugs (Ausgang) | Acht ausgehende AL-Signale |

## Funktionsweise

Der Baustein besitzt keine eigene Logik oder Zustandsmaschine. Ein an `IN` anliegendes AL‑Adapter-Signal wird unverändert und gleichzeitig an alle acht Ausgangs‑Adapter weitergeleitet. Die Vervielfachung erfolgt rein datenflussgesteuert, ohne Verzögerung oder Pufferung.

## Technische Besonderheiten

- **Generischer Typ**: Der FB ist als generischer Baustein (`GenericClassName = 'GEN_AL_SPLIT'`) deklariert, kann aber aufgrund der festen Adapter‑Definition nur mit dem Typ `AL` verwendet werden.
- **Keine Ereignissteuerung**: Es existiert weder ein ECC noch eine Ereignis‑Schnittstelle; die Weiterleitung erfolgt passiv über den Datenfluss.
- **Unidirektionalität**: Der Adapter ist nur in eine Richtung ausgelegt (Eingang → Ausgänge).

## Zustandsübersicht

Der Baustein besitzt keine internen Zustände. Er ist vollständig zustandslos und führt keine Verarbeitung durch.

## Anwendungsszenarien

- **Alarmverteilung**: Ein zentrales Alarmsignal wird an mehrere Subsysteme (z. B. Anzeige, Protokollierung, Steuerung) weitergegeben.
- **Redundante Signalisierung**: Das gleiche Signal kann parallel an mehrere Empfänger gesendet werden, um Ausfallsicherheit zu erhöhen.
- **Ansteuerung mehrerer Aktoren**: Ein Sensor‑ oder Steuersignal wird auf mehrere unabhängige Aktoren aufgeteilt.

## Vergleich mit ähnlichen Bausteinen

- **Standard‑SPLIT‑Bausteine** (z. B. `SPLIT` für einfache Datentypen) verteilen einzelne Werte, während `AL_SPLIT_8` speziell für den unidirektionalen Adapter `AL` ausgelegt ist.
- **Adapter‑Merger** (wie ein hypothetischer `AL_MERGE`) führen mehrere Signale zu einem zusammen; der `AL_SPLIT_8` realisiert die umgekehrte 1:n‑Funktionalität.

## Fazit

Der `AL_SPLIT_8` ist ein schlichter, aber wichtiger Baustein zur Vervielfachung von AL‑Adapter‑Signalen. Durch seine passive, zustandslose Arbeitsweise fügt er sich nahtlos in datenflussorientierte 4diac‑Anwendungen ein und erleichtert die strukturierte Verteilung von Alarm‑ oder Steuersignalen.