# AE_SPLIT_5


![AE_SPLIT_5](./AE_SPLIT_5.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AE_SPLIT_5** dient zur Vervielfältigung eines eingehenden Adapter-Ereignisses. Er empfängt ein Adapter-Ereignis (AE) an seinem Socket `IN` und leitet es identisch an fünf separate Ausgangs-Plugs (`OUT1` … `OUT5`) weiter. Der Baustein ist als generischer FB (GenericClassName `'GEN_AE_SPLIT'`) ausgeführt und ermöglicht so eine einfache Wiederverwendung in verschiedenen Kontexten.

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

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket (Eingang) | `IN` | `adapter::types::unidirectional::AE` | Ein unidirektionales Adapter-Ereignis, dessen Inhalt an alle Ausgänge weitergeleitet wird. |
| Plug (Ausgang 1) | `OUT1` | `adapter::types::unidirectional::AE` | Erster Ausgang, der das eingehende Ereignis bereitstellt. |
| Plug (Ausgang 2) | `OUT2` | `adapter::types::unidirectional::AE` | Zweiter Ausgang, der das eingehende Ereignis bereitstellt. |
| Plug (Ausgang 3) | `OUT3` | `adapter::types::unidirectional::AE` | Dritter Ausgang, der das eingehende Ereignis bereitstellt. |
| Plug (Ausgang 4) | `OUT4` | `adapter::types::unidirectional::AE` | Vierter Ausgang, der das eingehende Ereignis bereitstellt. |
| Plug (Ausgang 5) | `OUT5` | `adapter::types::unidirectional::AE` | Fünfter Ausgang, der das eingehende Ereignis bereitstellt. |

## Funktionsweise

Der FB **AE_SPLIT_5** ist ein reiner Verteilerbaustein. Sobald am Socket `IN` ein Adapter-Ereignis eintrifft, wird dieses Ereignis – ohne Verzögerung oder Datenmanipulation – parallel an alle fünf Ausgangs-Plugs `OUT1` bis `OUT5` gesendet. Es erfolgt keine interne Speicherung oder Zustandsveränderung; der FB ist vollständig kombinatorisch.

## Technische Besonderheiten

- **Generische Implementierung**: Der Baustein ist als generischer FB deklariert (`GenericClassName = 'GEN_AE_SPLIT'`), sodass er bei Bedarf mit verschiedenen Adapter-Typen verwendet werden kann, sofern diese vom Typ `adapter::types::unidirectional::AE` sind.
- **Unidirektionalität**: Alle beteiligten Adapter sind unidirektional ausgelegt. Es findet keine Kommunikation zurück zum Sender statt.
- **Keine zusätzlichen Logiken**: Der FB besitzt weder Ereignis- noch Dateneingänge/-ausgänge. Die Weiterleitung erfolgt rein über Adapter.

## Zustandsübersicht

Der Baustein besitzt keine definierte Zustandsmaschine oder Sequenzsteuerung. Sein Verhalten ist statisch: Bei jedem eingehenden Ereignis an `IN` werden alle Ausgänge gleichzeitig aktiviert. Es gibt keine Latenz oder Zwischenzustände.

## Anwendungsszenarien

- **Ereignisverteilung in Steuerungssystemen**: Ein Sensor-Ereignis (z. B. „Position erreicht“) soll an mehrere unabhängige Steuerungskomponenten gesendet werden.
- **Multicast in modularen Architekturen**: In einer verteilten Automatisierungsumgebung kann ein zentraler Funktionsblock sein Ereignis an bis zu fünf nachgelagerte Module aufteilen.
- **Prototyping und Testumgebungen**: Zum gleichzeitigen Testen mehrerer Empfänger mit demselben Ereignis.

## Vergleich mit ähnlichen Bausteinen

- **Ereignis-Splitter (E_SPLIT)**: Diese Bausteine verteilen **Ereignisse** (Event-Eingänge) auf mehrere Event-Ausgänge. **AE_SPLIT_5** hingegen verteilt **Adapter-Ereignisse** (komplexe Datenobjekte, die über Adapter kommunizieren) und bietet damit eine höhere Abstraktionsebene.
- **Daten-Splitter (F_SPLIT)**: Trennt Datenströme auf, besitzt aber keine Adapter-Schnittstelle. **AE_SPLIT_5** fokussiert auf die Verteilung von adapterbasierten Ereignisnachrichten.

## Fazit

Der **AE_SPLIT_5** ist ein einfacher, aber effektiver Baustein zur Vervielfältigung eines unidirektionalen Adapter-Ereignisses auf fünf Ausgänge. Aufgrund seiner generischen Natur und der reinen Adapter-Schnittstelle eignet er sich besonders für modulare und skalierbare Steuerungsanwendungen, in denen Informationen parallel an mehrere Empfänger gesendet werden müssen.