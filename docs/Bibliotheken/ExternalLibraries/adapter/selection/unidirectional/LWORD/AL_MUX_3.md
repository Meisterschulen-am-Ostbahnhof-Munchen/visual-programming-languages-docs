# AL_MUX_3


![AL_MUX_3](./AL_MUX_3.svg)

* * * * * * * * * *
## Einleitung
Der **AL_MUX_3** ist ein generischer Multiplexer (Signalweiche) für AL-Datenadapter. Er wählt abhängig vom Index **K** einen von drei Eingängen (IN1, IN2, IN3) aus und leitet dessen Daten auf den Ausgang **OUT** weiter. Der Baustein arbeitet ereignisgesteuert: Mit einem **REQ**-Ereignis wird die Auswahl getroffen und das Ergebnis über **CNF** quittiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| REQ      | Fordert die Auswahl des durch **K** bestimmten Eingangs an. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| CNF      | Bestätigt die Durchführung der Auswahl (keine Datenübergabe) |

### **Daten-Eingänge**

| Variable | Typ  | Beschreibung                               |
|----------|------|--------------------------------------------|
| K        | UINT | Index des zu selektierenden Eingangs (0/1/2) |

### **Daten-Ausgänge**
– Keine direkten Datenausgänge vorhanden. Die Datenweitergabe erfolgt ausschließlich über den Adapter **OUT**.

### **Adapter**

| Richtung | Name | Typ                                   | Beschreibung                           |
|----------|------|---------------------------------------|----------------------------------------|
| Plug     | OUT  | adapter::types::unidirectional::AL    | Ausgang, der den ausgewählten Eingang weitergibt |
| Socket   | IN1  | adapter::types::unidirectional::AL    | Eingang 1 (wird bei K = 0 durchgeschaltet) |
| Socket   | IN2  | adapter::types::unidirectional::AL    | Eingang 2 (wird bei K = 1 durchgeschaltet) |
| Socket   | IN3  | adapter::types::unidirectional::AL    | Eingang 3 (wird bei K = 2 durchgeschaltet) |

## Funktionsweise
Der Baustein wartet auf ein **REQ**-Ereignis. Bei dessen Eintreffen wird der Wert von **K** (0, 1 oder 2) ausgewertet. Der entsprechende Eingangsadapter (IN1 bei K=0, IN2 bei K=1, IN3 bei K=2) wird auf den Ausgangsadapter **OUT** umgeschaltet. Somit stehen die Daten des gewählten Eingangs am Ausgang zur Verfügung. Nach Abschluss der Umschaltung wird ein **CNF**-Ereignis ausgegeben. Bei ungültigen Werten von K (z. B. > 2) bleibt der Ausgang unverändert oder es wird kein gültiges Signal weitergeleitet (abhängig von der Implementierungsumgebung).

## Technische Besonderheiten
- Der Baustein ist als **generischer Funktionsblock** deklariert („GEN_AL_MUX“), d. h. er kann in verschiedenen Kontexten wiederverwendet werden.
- Die Schnittstellen sind ausschließlich als **Adapter** vom Typ `adapter::types::unidirectional::AL` realisiert. Dies ermöglicht eine flexible Kopplung mit anderen AL-kompatiblen Bausteinen.
- Es werden keine eigenen Werte zwischengespeichert – die Selektion erfolgt rein logisch über den Index.
- Die maximale Anzahl der Eingänge ist auf drei festgelegt, kann aber durch abgeleitete Varianten erweitert werden.

## Zustandsübersicht
Da der Baustein keine explizite Zustandsmaschine besitzt (IEC 61499-Basis), kann er als **zustandslos** betrachtet werden. Die Reaktion auf **REQ** erfolgt deterministisch ohne interne Verzweigung. Einziger relevanter Zustand ist die Warte auf das nächste Ereignis nach erfolgter **CNF**-Bestätigung.

## Anwendungsszenarien
- **Signalumschaltung**: Auswahl eines Sensorsignals aus drei Quellen (z. B. Temperatur, Druck, Füllstand) für die Verarbeitung durch einen nachfolgenden Baustein.
- **Betriebsmodus-Umschaltung**: In einer Steuerung kann zwischen verschiedenen Algorithmen oder Parametereinstellungen gewählt werden.
- **Redundanz**: Fallback auf einen zweiten oder dritten Datenpfad, wenn ein Primärsignal ausfällt.

## Vergleich mit ähnlichen Bausteinen
- **AL_MUX** (Standard-Multiplexer mit 2 Eingängen): Bietet nur zwei Kanäle; der AL_MUX_3 erweitert dies auf drei.
- **MUX_ANY**: Ein datentyp-unabhängiger Multiplexer (z. B. für `ANY`-Typen) arbeitet meist mit einfachen Datenvariablen und nicht mit Adaptern. Der AL_MUX_3 ist speziell auf den Adaptertyp **AL** zugeschnitten.
- **SELECT**: Ein ähnlicher Baustein (z. B. aus IEC 61499-2 Standard Library) arbeitet oft ereignisgesteuert mit booleschen Bedingungen. Der AL_MUX_3 verwendet einen numerischen Index.

## Fazit
Der **AL_MUX_3** ist ein einfacher, aber nützlicher Multiplexer-Baustein für Adapter-basierte AL-Daten. Er eignet sich besonders für Szenarien, in denen aus mehreren gleichartigen Datenquellen eine dynamisch ausgewählt werden muss. Durch die klare Ereignissteuerung und die generische Natur lässt er sich gut in Automatisierungslösungen integrieren, die auf IEC 61499 und dem 4diac-Framework basieren.