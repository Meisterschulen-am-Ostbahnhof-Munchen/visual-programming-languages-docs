# AUS_SPLIT_4


![AUS_SPLIT_4](./AUS_SPLIT_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AUS_SPLIT_4` verteilt ein eingehendes **AUS**-Signal (typischerweise ein binäres Steuersignal für „Aus“) auf vier identische Ausgangssignale. Er dient als generischer Splitter und ermöglicht es, einen einzelnen Befehl oder Zustand an mehrere nachgeschaltete Komponenten weiterzuleiten, ohne dass eine separate Verzweigungslogik erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine.

### **Ereignis-Ausgänge**

Keine.

### **Daten-Eingänge**

Keine.

### **Daten-Ausgänge**

Keine.

### **Adapter**

Der Baustein kommuniziert ausschließlich über Adapter vom Typ `adapter::types::unidirectional::AUS`. Es handelt sich um einen unidirektionalen Adapter, der ein boolesches Signal (AUS-Kommando) überträgt.

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket (Eingang)** | `IN` | `adapter::types::unidirectional::AUS` | Empfängt das ursprüngliche AUS-Signal. |
| **Plug (Ausgang)** | `OUT1` | `adapter::types::unidirectional::AUS` | Erster ausgehender AUS-Pfad. |
| **Plug (Ausgang)** | `OUT2` | `adapter::types::unidirectional::AUS` | Zweiter ausgehender AUS-Pfad. |
| **Plug (Ausgang)** | `OUT3` | `adapter::types::unidirectional::AUS` | Dritter ausgehender AUS-Pfad. |
| **Plug (Ausgang)** | `OUT4` | `adapter::types::unidirectional::AUS` | Vierter ausgehender AUS-Pfad. |

## Funktionsweise

Der Baustein arbeitet als reine Signalverteilung: Sobald am Socket `IN` ein AUS-Signal anliegt, wird dieses unverändert an alle vier Plugs (`OUT1` bis `OUT4`) weitergegeben. Es findet keine logische Verarbeitung, Verzögerung oder Zustandsänderung statt. Die Verteilung erfolgt parallel und sofort.

Der generische Charakter des Bausteins (erkennbar am Attribut `GenericClassName = 'GEN_AUS_SPLIT'`) erlaubt die Wiederverwendung in verschiedenen Applikationen, bei denen der gleiche AUS-Signaltyp verwendet wird.

## Technische Besonderheiten

- **Lizenz**: Der Quellcode unterliegt der **Eclipse Public License 2.0** (EPL-2.0).  
- **Urheber**: Entwickelt von **HR Agrartechnik GmbH**, Version 1.0 vom 24.01.2025.  
- **Generische Implementierung**: Der Baustein ist als generischer FB deklariert (`GenericClassName` = `'GEN_AUS_SPLIT'`), was eine einfache Anpassung an verschiedene Signaltypen oder Konfigurationen ermöglicht.  
- **Adapterbasiert**: Die Kommunikation erfolgt ausschließlich über Adapter, nicht über klassische Ereignis- oder Datenports. Dadurch kann der Baustein in einer adapterbasierten Architektur nahtlos integriert werden.  
- **Keine Zustandsmaschine**: Es existiert keine interne Zustandslogik – die Verteilung ist rein kombinatorisch.

## Zustandsübersicht

Der Baustein besitzt keine Zustandsmaschine. Die Ausgangssignale folgen direkt dem Eingangssignal. Eine grafische Zustandsübersicht entfällt daher.

## Anwendungsszenarien

- **Rückkopplung von AUS-Signalen**: Ein zentrales „Aus“-Kommando einer Steuerung soll gleichzeitig mehrere Aktoren oder Subsysteme abschalten.  
- **Redundante Überwachung**: Verteilen eines AUS-Signals an mehrere Überwachungseinheiten, die unabhängig voneinander auf den Befehl reagieren müssen.  
- **Modulare Maschinenstruktur**: In einer modularen Anlage wird ein einmal erfasstes AUS-Signal über Busse oder Koppelelemente zu mehreren Modulen geführt. `AUS_SPLIT_4` ersetzt aufwändige Verdrahtung oder logische ODER-Verknüpfungen.  
- **Test und Simulation**: Zum gleichzeitigen Ansteuern mehrerer simulierter Komponenten mit demselben Signal.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion | Besonderheit |
|----------|----------|--------------|
| `AUS_SPLIT_2` | Verteilt ein AUS-Signal auf zwei Ausgänge | Weniger Ports, kompakter. |
| `AUS_SPLIT_4` | Verteilt auf vier Ausgänge | Dieses FB. |
| `AUS_SPLIT_N` | Parametrierbarer Splitter (z. B. durch generische Adapterlisten) | Flexiblere Anzahl, aber aufwändiger in der Konfiguration. |
| `AUS_MERGE` | Fasst mehrere AUS-Eingänge zu einem Ausgang zusammen | Gegenstück zum Splitter. |

Der `AUS_SPLIT_4` liegt in der Mitte zwischen einem einfachen 2‑fach-Splitter und einem vollparametrierbaren Splitter. Er ist ideal, wenn exakt vier Ausgänge benötigt werden – ohne zusätzliche Konfiguration.

## Fazit

Der `AUS_SPLIT_4` ist ein einfacher, aber nützlicher generischer Funktionsblock zur Verteilung eines AUS-Signals auf vier parallele Pfade. Seine adapterbasierte Schnittstelle und die klare Trennung von Logik und Signalweitergabe machen ihn zu einem robusten Baustein in der IEC 61499‑basierten Automatisierung. Dank der generischen Deklaration kann er problemlos in verschiedene Projekte eingebunden und ggf. an eigene Signaltypen angepasst werden.