# AULI_D_FF


![AULI_D_FF](./AULI_D_FF.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AULI_D_FF realisiert ein taktflankengesteuertes D-Flipflop (Data Latch). Er übernimmt bei einem eingehenden Ereignis den anliegenden Datenwert und hält diesen bis zum nächsten Takt fest. Die Ein- und Ausgabe erfolgt über genormte unidirektionale Adapter, sodass der Baustein in modularen Steuerungsarchitekturen einfach eingebunden werden kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **I.E1** – Taktereignis (positive Flanke): löst das Übernehmen des Datenwertes aus

### **Ereignis-Ausgänge**

- **Q.E1** – Ausgangsereignis: wird nach erfolgreicher Übernahme des Wertes gesendet

### **Daten-Eingänge**

- **I.D1** – zu latchender Datenwert (beliebiger Typ, da der interne Baustein `E_D_FF_ANY` verwendet wird)

### **Daten-Ausgänge**

- **Q.D1** – gelatchter Datenwert (entspricht dem zuletzt übernommenen Wert von I.D1)

### **Adapter**

Der FB besitzt zwei unidirektionale Adapter vom Typ `adapter::types::unidirectional::AULI`:

- **Socket I** (Eingang): nimmt das Taktereignis und den Datenwert auf.
- **Plug Q** (Ausgang): gibt das Quittungsereignis und den gespeicherten Datenwert weiter.

## Funktionsweise

Sobald am Eingangsadapter I ein Ereignis an **I.E1** eintrifft, wird der aktuelle Wert von **I.D1** in das interne Flipflop übernommen. Unmittelbar danach wird am Ausgangsadapter Q das Ereignis **Q.E1** gesendet, und der neue Wert wird an **Q.D1** ausgegeben. Der gespeicherte Wert bleibt solange erhalten, bis ein weiteres Taktereignis einen neuen Wert übernimmt.

Der FB arbeitet als **getakteter Speicher** und eignet sich besonders für die Synchronisation von Datenflüssen in ereignisgesteuerten Automatisierungssystemen.

## Technische Besonderheiten

- Der Baustein ist als **Composition** realisiert und nutzt intern den Standard-FB `iec61499::events::E_D_FF_ANY`, der die eigentliche Flipflop-Funktionalität bereitstellt.
- Die Verwendung von Adaptern ermöglicht eine **einheitliche Anbindung** an verschiedenste Komponenten, die denselben Adaptertyp unterstützen.
- Es sind keine weiteren Konfigurationsparameter oder Initialisierungen erforderlich – der FB arbeitet nach der ersten Takflanke deterministisch.

## Zustandsübersicht

Der interne Zustand des D-Flipflops kann logisch 0 oder 1 sein. Da der Datenwert beliebig sein kann, entspricht der Zustand dem zuletzt gelatchten Wert. Ein explizites Zustandsdiagramm ist nicht erforderlich, da das Verhalten durch die einfache Flankensteuerung vollständig beschrieben wird.

| Takt (I.E1) | Vorheriger Q-Wert | Neuer Q-Wert |
|-------------|-------------------|--------------|
| Ereignis    | beliebig          | Wert von I.D1|
| kein Ereignis| unverändert       | unverändert  |

## Anwendungsszenarien

- **Datenpufferung** in Produktionslinien: Ein Sensorwert wird bei jedem Takt erfasst und zwischengespeichert.
- **Zustandsmaschinen**: Realisierung von Speicherzellen für Schrittketten, in denen der nächste Zustand vom aktuellen Ausgang abhängt.
- **Synchronisation**: Anpassung asynchroner Datenströme an einen einheitlichen Takt in verteilten Steuerungssystemen.
- **Signalverarbeitung**: Halten eines digitalen Signals für die Dauer eines Taktzyklus.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Beschreibung | Unterschied zu AULI_D_FF |
|----------|--------------|----------------------------|
| SR-FF    | Set-Reset-Flipflop | Erfordert zwei getrennte Eingänge; kann illegale Zustände haben. |
| JK-FF    | Universelles Flipflop | Komplexer, mit Toggle-Funktion; hier nicht benötigt. |
| T-FF     | Toggle-Flipflop | Ändert den Zustand bei jedem Takt; kein Dateneingang. |
| AULI_D_FF| D-Flipflop | Einfach, kein Toggle, keine illegalen Zustände, ideal zum Speichern eines Werts. |

## Fazit

Der AULI_D_FF ist ein kompakter, ereignisgesteuerter D-Flipflop-Baustein, der über standardisierte Adapter kommuniziert. Er eignet sich hervorragend zum Zwischenspehern von Datenwerten in ereignisdiskreten Steuerungsumgebungen. Durch die interne Verwendung eines bewährten Standard-FBs ist das Verhalten robust und deterministisch. Die modulare Adapter-Schnittstelle erleichtert die Integration in komplexe Automatisierungsprojekte.