# ADI_D_FF_HYS_TMIN


![ADI_D_FF_HYS_TMIN](./ADI_D_FF_HYS_TMIN.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ADI_D_FF_HYS_TMIN** realisiert ein Daten-Latch (D-Flipflop) mit einer Hysterese und einer minimalen Zeitverzögerung zwischen aufeinanderfolgenden Ausgangsereignissen. Er dient der stabilen und entstörten Signalweitergabe in industriellen Steuerungsanwendungen, die auf unidirektionalen Adaptern basieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT** (EInit): Init-Anforderung. Dieser Ereigniseingang initialisiert den Baustein mit den Parametern `HYSTERESIS` und `Tmin`.

### **Ereignis-Ausgänge**

- **INITO** (EInit): Init-Bestätigung. Wird nach erfolgreicher Initialisierung ausgegeben.

### **Daten-Eingänge**

- **HYSTERESIS** (DINT): Hystereseband. Definiert die Schaltschwelle, um ein Flattern am Ausgang zu verhindern.
- **Tmin** (TIME): Minimale Zeit zwischen zwei Ausgangsereignissen (Inter-Arrival Time). Verhindert zu schnelles Umschalten.

### **Daten-Ausgänge**

Der Baustein besitzt keine eigenen Daten-Ausgänge. Die Ausgangsdaten werden über einen Adapter bereitgestellt.

### **Adapter**

- **I** (Socket, Typ: `adapter::types::unidirectional::ADI`): Der zu latchnde Wert wird über diesen Adaptereingang empfangen (Ereignis und Daten).
- **Q** (Plug, Typ: `adapter::types::unidirectional::ADI`): Der gelatchte Wert wird über diesen Adapterausgang ausgegeben (Ereignis und Daten).

## Funktionsweise

Der Baustein verwendet intern den FB `E_D_FF_ANY_HYS_TMIN`. Er verarbeitet die über den Adapter **I** eingehenden Ereignisse (`I.E1`) und Daten (`I.D1`). Die eigentliche Latch-Funktion erfolgt mit einer Hysterese, die durch den Parameter `HYSTERESIS` festgelegt wird. Zusätzlich wird eine minimale Wartezeit `Tmin` zwischen zwei Ausgangsereignissen eingehalten, um eine zu hohe Ereignisfrequenz zu unterdrücken. Die Ausgabe erfolgt über den Adapter **Q** (`Q.E1` und `Q.D1`). Die Initialisierung (`INIT`) setzt die Parameter und aktiviert den internen FB.

## Technische Besonderheiten

- **Adapterbasierte Kommunikation:** Der Baustein nutzt unidirektionale Adapter (`ADI`) für den Datenaustausch. Dies ermöglicht eine lose Kopplung von Daten und Ereignissen.
- **Konfigurierbare Hysterese:** Die Hysteresebreite kann anwendungsspezifisch eingestellt werden, um Rauschen oder Prell-Effekte zu unterdrücken.
- **Minimale Ereignisabstandzeit:** Mit `Tmin` lässt sich die maximale Ausgangsfrequenz begrenzen, was zur Entlastung nachfolgender Verarbeitungseinheiten beiträgt.

## Zustandsübersicht

Der FB besitzt zwei stabile interne Zustände (z. B. HIGH/LOW oder TRUE/FALSE), die den gelatchten Ausgangswert repräsentieren. Ein Zustandswechsel erfolgt nur, wenn der eingehende Wert (über **I**) die Hystereseschwelle überschreitet und die seit dem letzten Ausgangsereignis verstrichene Zeit mindestens `Tmin` beträgt. Andernfalls wird das Ereignis unterdrückt.

| Zustand | Beschreibung |
|---------|--------------|
| LOW  | Ausgangswert ist logisch 0 bzw. niedrig |
| HIGH | Ausgangswert ist logisch 1 bzw. hoch |

Wechsel zwischen den Zuständen erfolgen gemäß der Hysterese- und Zeitbedingungen.

## Anwendungsszenarien

- **Entprellung von Schaltern oder Sensoren:** Verhindert mehrfaches Umschalten durch mechanisches Prellen.
- **Signalglättung in der Prozessautomatisierung:** Unterdrückt kleine Störungen oder Rauschen auf analogen oder digitalen Signalen.
- **Ereignisrate-Begrenzung:** Schutz nachfolgender Funktionen vor zu schnellen Ereignisfolgen, z. B. in Zählern oder Kommunikationsschnittstellen.

## Vergleich mit ähnlichen Bausteinen

Ein herkömmliches D-Flipflop (z. B. `E_D_FF`) schaltet bei jedem Takt ohne Hysterese und ohne Zeitverzögerung. Der `ADI_D_FF_HYS_TMIN` hingegen bietet:
- **Hysterese:** Verhindert Oszillationen bei langsam ändernden oder verrauschten Signalen.
- **Minimale Inter-Arrival-Zeit:** Reduziert die Ereignisrate und ermöglicht eine gezielte Zeitsteuerung.
- **Adapter-Schnittstelle:** Speziell für den Einsatz in komplexen, adapterbasierten FB-Netzwerken ausgelegt.

## Fazit

Der `ADI_D_FF_HYS_TMIN` ist ein robuster Funktionsblock für die zuverlässige Signalverarbeitung mit Hysterese und Zeitsteuerung. Er eignet sich besonders für Anwendungen, die eine entstörte, gefilterte und ratenbegrenzte Weitergabe von Ereignissen und Daten erfordern – typischerweise in industriellen Steuerungssystemen, die auf dem 4diac-Framework und unidirektionalen Adaptern basieren.