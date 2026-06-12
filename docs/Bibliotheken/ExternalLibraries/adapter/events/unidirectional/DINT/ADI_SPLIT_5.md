# ADI_SPLIT_5


![ADI_SPLIT_5](./ADI_SPLIT_5.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ADI_SPLIT_5** dient dazu, einen eingehenden ADI-Adapter (unidirektional) auf fünf identische Ausgangs-Adapter aufzuteilen. Er ist als generischer Baustein (Generic FB) konzipiert und kann in IEC 61499‑basierten Systemen verwendet werden, um ein Signal oder einen Datenstrom an mehrere nachfolgende Funktionsblöcke weiterzuleiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine

### **Ereignis-Ausgänge**

Keine

### **Daten-Eingänge**

- **IN** (Socket, Typ: `adapter::types::unidirectional::ADI`)  
  Eingangs-Adapter, der das zu verteilende Signal liefert.

### **Daten-Ausgänge**

- **OUT1** (Plug, Typ: `adapter::types::unidirectional::ADI`)  
- **OUT2** (Plug, Typ: `adapter::types::unidirectional::ADI`)  
- **OUT3** (Plug, Typ: `adapter::types::unidirectional::ADI`)  
- **OUT4** (Plug, Typ: `adapter::types::unidirectional::ADI`)  
- **OUT5** (Plug, Typ: `adapter::types::unidirectional::ADI`)  

Alle Ausgänge sind unabhängige Instanzen des gleichen Adaptertyps und erhalten identische Daten.

### **Adapter**

Dieser Baustein arbeitet ausschließlich über Adapter-Schnittstellen. Es werden keine Ereignis‑ oder Daten‑Ein‑/Ausgänge im klassischen Sinne verwendet. Die gesamte Kommunikation erfolgt über die ADI‑Adapter, welche die Signal‑ und Datenweiterleitung implizit steuern.

## Funktionsweise

Der FB **ADI_SPLIT_5** empfängt über den Socket **IN** einen ADI‑Adapter und leitet die darin enthaltenen Daten und Ereignisse parallel an die fünf Plugs **OUT1** bis **OUT5** weiter. Es findet keine Verarbeitung oder Umformung der Daten statt – der Baustein fungiert als passiver Verteiler (Fan‑Out).

Da es sich um unidirektionale ADI‑Adapter handelt, wird das Signal nur von der Eingangsseite zur Ausgangsseite weitergegeben; Rückwirkungen von den Ausgängen sind nicht vorgesehen.

## Technische Besonderheiten

- **Generischer Baustein**: Die Klasse `GEN_ADI_SPLIT` erlaubt eine flexible Wiederverwendung, z. B. durch Parametrisierung des Typs oder der Anzahl der Ausgänge (hier fest auf fünf).
- **Adapterbasiert**: Keine direkten Ereignis‑ oder Daten‑Ein‑/Ausgänge – die komplette Signalweitergabe erfolgt über die Adapter‑Schnittstellen.
- **Unidirektionalität**: Die Adapter sind als `unidirectional` definiert, d. h. Daten fließen nur in eine Richtung (von IN zu OUT1‑5).
- Der Baustein enthält keine interne Zustandslogik oder zeitliche Steuerung.

## Zustandsübersicht

Der **ADI_SPLIT_5** besitzt keine eigenen Zustände. Er ist ein rein kombinatorischer Baustein, der sofort auf eingehende Adapter‑Daten reagiert und diese unverändert an alle Ausgänge weitergibt.

## Anwendungsszenarien

- **Signalkaskade**: Aufteilung eines Sensorsignals (z. B. Temperatur, Druck) an mehrere Auswerte‑ und Steuerungsblöcke.
- **Diagnose und Überwachung**: Gleichzeitige Verteilung eines Datenstroms an Verarbeitungs‑ und Logging‑Module.
- **Lastverteilung**: Parallele Verarbeitung desselben Eingangs in unterschiedlichen Algorithmen (z. B. Filter, Grenzwertüberwachung, Visualisierung).

## Vergleich mit ähnlichen Bausteinen

Im IEC 61499‑Umfeld existieren häufig Varianten wie **SPLIT_2**, **SPLIT_3** oder **SPLIT_N**, die eine unterschiedliche Anzahl von Ausgängen bereitstellen. Der **ADI_SPLIT_5** ist eine spezielle Realisierung für exakt fünf Ausgänge unter Verwendung von unidirektionalen ADI‑Adapter‑Schnittstellen. Im Gegensatz zu ereignisbasierten Split‑Bausteinen (z. B. `E_SPLIT`) erfolgt hier die Verteilung über Adapter, was eine typengebundene und typischerweise datenorientierte Kommunikation ermöglicht.

## Fazit

Der **ADI_SPLIT_5** ist ein einfacher, aber nützlicher Funktionsblock zur Verteilung eines unidirektionalen ADI‑Signals auf bis zu fünf nachfolgende Bausteine. Er eignet sich besonders für modulare Automatisierungslösungen, bei denen ein Eingangssignal mehrfach genutzt werden muss, ohne dass eine zusätzliche Steuerungslogik erforderlich ist. Durch die generische Implementierung kann er in verschiedenen Kontexten wiederverwendet werden.