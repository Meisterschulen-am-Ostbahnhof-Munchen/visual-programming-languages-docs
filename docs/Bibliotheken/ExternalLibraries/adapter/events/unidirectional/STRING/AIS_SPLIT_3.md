# AIS_SPLIT_3


![AIS_SPLIT_3](./AIS_SPLIT_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AIS_SPLIT_3** dient dazu, einen eingehenden AIS-Datenstrom auf drei identische Ausgänge zu verteilen. Er ist als generischer Baustein realisiert und ermöglicht eine einfache Vervielfachung von AIS-Informationen in Steuerungssystemen nach IEC 61499.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Nicht vorhanden – der Baustein arbeitet rein daten- und adaptergesteuert.

### **Ereignis-Ausgänge**
Nicht vorhanden.

### **Daten-Eingänge**
Nicht vorhanden – die Eingangsdaten werden ausschließlich über den Adapter-Socket bereitgestellt.

### **Daten-Ausgänge**
Nicht vorhanden – die Ausgangsdaten werden ausschließlich über die Adapter-Plugs ausgegeben.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AIS` | IN | Socket (Eingang) | Empfängt einen AIS-Datenstrom. |
| `adapter::types::unidirectional::AIS` | OUT1 | Plug (Ausgang) | Erster Ausgangskanal – identische Kopie des Eingangs. |
| `adapter::types::unidirectional::AIS` | OUT2 | Plug (Ausgang) | Zweiter Ausgangskanal – identische Kopie des Eingangs. |
| `adapter::types::unidirectional::AIS` | OUT3 | Plug (Ausgang) | Dritter Ausgangskanal – identische Kopie des Eingangs. |

## Funktionsweise

Der Baustein nimmt über den **IN**-Socket einen AIS-Datenstrom entgegen und leitet diesen ohne Verzögerung oder Manipulation an die drei Ausgangsadapter **OUT1**, **OUT2** und **OUT3** weiter. Jeder Ausgang erhält identische Daten. Es findet keine Pufferung, Filterung oder Protokollumsetzung statt – der Baustein fungiert als reiner Verteiler (Splitter) auf Adapterebene.

## Technische Besonderheiten

- **Generischer Typ**: Der Baustein ist mit dem generischen Klassennamen `GEN_AIS_SPLIT` versehen, sodass er in verschiedenen Kontexten und mit unterschiedlichen AIS-Datentypen wiederverwendet werden kann.
- **Unidirektionale Adapter**: Sowohl Ein- als auch Ausgänge verwenden den unidirektionalen Adapter `adapter::types::unidirectional::AIS`, was eine klare Datenflussrichtung gewährleistet.
- **Keine ereignisgesteuerte Synchronisation**: Da keine Ereignis-Ein-/Ausgänge vorhanden sind, erfolgt die Datenweitergabe sofort und ohne Triggerung durch externe Events.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten. Sein Verhalten entspricht einer ständig aktiven Durchschleifverbindung: Solange der Eingangsadapter Daten liefert, werden diese auf allen drei Ausgängen ausgegeben. Es gibt keine internen Zustände oder Moden.

## Anwendungsszenarien

- **Verteilen von AIS-Daten an mehrere Verbraucher** – z. B. gleichzeitige Visualisierung, Logging und Weiterverarbeitung.
- **Redundante Datenbereitstellung** – Einspeisung in verschiedene Teilsysteme ohne zusätzliche Belastung der Datenquelle.
- **Test- und Diagnoseaufbauten** – paralleles Überwachen eines AIS-Streams an mehreren Stellen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Anzahl Ausgänge | Besonderheit |
|----------|------------------|--------------|
| AIS_SPLIT_2 | 2 | Verteilt auf zwei Kanäle. |
| **AIS_SPLIT_3** | **3** | **Standard-Splitter mit drei Ausgängen.** |
| AIS_SPLIT_N | variabel | Generische Version mit konfigurierbarer Ausgangsanzahl (sofern verfügbar). |

Der AIS_SPLIT_3 füllt die Lücke zwischen dem einfachen 2-Wege-Splitter und einem vollständig parametrierbaren Splitter.

## Fazit

Der **AIS_SPLIT_3** ist ein einfacher, aber effektiver Baustein zur Vervielfachung eines AIS-Datenstroms. Dank seiner generischen Natur und der klaren adapterbasierten Schnittstelle lässt er sich leicht in größere 4diac-Projekte integrieren. Für Anwendungen, die eine mehrfache Verteilung ohne Datenänderung erfordern, bietet er eine robuste und wartbare Lösung.