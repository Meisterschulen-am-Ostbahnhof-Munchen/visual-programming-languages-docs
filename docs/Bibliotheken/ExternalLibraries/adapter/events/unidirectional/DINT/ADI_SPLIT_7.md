# ADI_SPLIT_7


![ADI_SPLIT_7](./ADI_SPLIT_7.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ADI_SPLIT_7** dient der Aufteilung eines eingehenden **ADI**-Adapter-Signals auf sieben identische Ausgänge. Er ist als generischer Baustein (Generic FB) implementiert und ermöglicht die unidirektionale Verteilung von Daten über einen Adapter-Socket an sieben Adapter-Plugs.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine – der Baustein verfügt über keine Ereignis-Eingänge. Die Datenweitergabe erfolgt ausschließlich über die Adapter-Schnittstelle.

### **Ereignis-Ausgänge**

Keine – der Baustein verfügt über keine Ereignis-Ausgänge. Die Ausgangsadapter werden direkt mit den empfangenen Daten versorgt.

### **Daten-Eingänge**

Keine – die Daten werden nicht über separate Daten-Eingänge bereitgestellt, sondern über den Adapter-Socket IN.

### **Daten-Ausgänge**

Keine – die Daten werden nicht über separate Daten-Ausgänge ausgegeben, sondern über die Adapter-Plugs OUT1 … OUT7.

### **Adapter**

| Name | Richtung | Typ | Beschreibung |
|------|----------|-----|--------------|
| IN   | Socket   | adi (unidirektional) | Eingangsadapter, der die zu verteilenden Daten empfängt. |
| OUT1 | Plug     | adi (unidirektional) | Erster Ausgangsadapter (identisch zu IN). |
| OUT2 | Plug     | adi (unidirektional) | Zweiter Ausgangsadapter (identisch zu IN). |
| OUT3 | Plug     | adi (unidirektional) | Dritter Ausgangsadapter (identisch zu IN). |
| OUT4 | Plug     | adi (unidirektional) | Vierter Ausgangsadapter (identisch zu IN). |
| OUT5 | Plug     | adi (unidirektional) | Fünfter Ausgangsadapter (identisch zu IN). |
| OUT6 | Plug     | adi (unidirektional) | Sechster Ausgangsadapter (identisch zu IN). |
| OUT7 | Plug     | adi (unidirektional) | Siebter Ausgangsadapter (identisch zu IN). |

## Funktionsweise

Der Baustein fungiert als **1-zu-7-Splitter** für ADI-Adapter-Signale. Wird das Signal am Eingangsadapter **IN** gesetzt, wird es ohne weitere Verarbeitung oder Verzögerung auf alle sieben Ausgangsadapter **OUT1** bis **OUT7** kopiert. Der Baustein besitzt keine interne Logik oder Zustandsmaschine – er leitet die Daten rein passiv weiter.

## Technische Besonderheiten

- **Generischer Baustein** – der Typ wird als `GEN_ADI_SPLIT` instanziiert und kann in verschiedenen Anwendungen wiederverwendet werden.
- **Unidirektionale Adapter** – alle Adapter sind vom Typ `adi` (unidirektional). Ein Rückfluss von Daten von den Ausgängen zum Eingang ist nicht vorgesehen.
- **Keine Ereignissteuerung** – die Datenweitergabe erfolgt rein datengetrieben ohne Ereignis-Ein-/Ausgänge.
- **1:1-Kopie** – die Daten am Eingang werden unverändert auf alle Ausgänge übertragen.

## Zustandsübersicht

Der Baustein besitzt **keine Zustandsmaschine** (ECC). Er ist stateless, d.h. er reagiert nicht auf Ereignisse und hat keine internen Zustände. Die Ausgangsdaten folgen direkt den Eingangsdaten.

## Anwendungsszenarien

- **Signalverteilung** – ein einzelnes ADI-Signal (z.B. Sensorwert, Steuersignal) muss an mehrere Verbraucher (z.B. Steuerungsblöcke, Visualisierungen) verteilt werden.
- **Redundanz** – ein Signal wird für redundante Verarbeitungspfade benötigt.
- **Test- und Simulationsumgebungen** – ein eingehendes Signal wird für verschiedene Testinstanzen aufgeteilt.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Anzahl Ausgänge | Eigenschaften |
|----------|-----------------|---------------|
| ADI_SPLIT_2 | 2 | Verteilt 1 ADI auf 2 Ausgänge |
| ADI_SPLIT_4 | 4 | Verteilt 1 ADI auf 4 Ausgänge |
| ADI_SPLIT_7 | 7 | Verteilt 1 ADI auf 7 Ausgänge |
| ADI_MERGE    | 1 (Eingang: mehrere) | Fasst mehrere ADI-Eingänge zu einem Ausgang zusammen |

Gegenüber einer manuellen Parallelschaltung mehrerer ADI_Split-Bausteine reduziert der `ADI_SPLIT_7` den Konfigurationsaufwand und verbessert die Übersicht im Netzwerk.

## Fazit

Der `ADI_SPLIT_7` ist ein einfacher, aber leistungsfähiger Baustein zur Verteilung eines unidirektionalen ADI-Signals auf sieben identische Ausgänge. Dank seiner generischen Implementierung und dem Verzicht auf Ereignissteuerung eignet er sich ideal für Reinverteilungen in Automatisierungs- und Steuerungsumgebungen, die auf dem ADI-Adapterprotokoll basieren.