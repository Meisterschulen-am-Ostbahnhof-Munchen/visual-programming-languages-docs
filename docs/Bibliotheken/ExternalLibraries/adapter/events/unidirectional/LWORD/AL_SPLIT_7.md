# AL_SPLIT_7


![AL_SPLIT_7](./AL_SPLIT_7.svg)

*(Bild des Funktionsblocks nicht verfügbar)*

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **AL_SPLIT_7** dient als generischer Verteiler (Splitter) für einen unidirektionalen Adapter vom Typ `AL`. Er nimmt an seinem Socket `IN` einen einzigen Adapter entgegen und leitet die ankommenden Daten und Ereignisse unverändert an sieben identische Adapter-Ausgänge (`OUT1` … `OUT7`) weiter. Der Baustein ist als generischer Typ (`GEN_AL_SPLIT`) implementiert und ermöglicht so eine flexible Verwendung in Steuerungs- und Automatisierungsanwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt keine expliziten Ereignis-Eingänge. Die gesamte Ereignissteuerung erfolgt über den angeschlossenen Adapter `IN`.

### **Ereignis-Ausgänge**

Es sind keine direkten Ereignis-Ausgänge vorhanden. Ereignisse werden über die sieben Adapter-Ausgänge (`OUT1` … `OUT7`) weitergegeben.

### **Daten-Eingänge**

Der Baustein hat keine eigenständigen Daten-Eingänge. Die Datenübergabe geschieht ausschließlich über den Adapter `IN`.

### **Daten-Ausgänge**

Entsprechend gibt es keine direkten Daten-Ausgänge. Die Daten werden über die sieben Adapter-Ausgänge repliziert.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket   | `IN` | `adapter::types::unidirectional::AL` | Adapter-Eingang, der die zu verteilende AL-Verbindung bereitstellt. |
| Plug     | `OUT1` … `OUT7` | `adapter::types::unidirectional::AL` | Sieben Adapter-Ausgänge, die die identische Kopie des Eingangsadapter bereitstellen. |

## Funktionsweise

Der **AL_SPLIT_7** ist ein reiner Verteilerbaustein. Wenn ein Adapter vom Typ `AL` an den Socket `IN` angeschlossen wird, werden alle über diesen Adapter eingehenden Daten und Ereignisse unverändert an jeden der sieben Plugs (`OUT1` … `OUT7`) weitergeleitet. Es findet keine logische oder zeitliche Bearbeitung statt – die Verteilung erfolgt eins-zu-sieben ohne Verzögerung oder Pufferung. Aufgrund der generischen Implementierung kann der Baustein mit verschiedenen AL-Adapterinstanzen verwendet werden, die denselben Datentyp und dasselbe Ereignisschema aufweisen.

## Technische Besonderheiten

- **Generische Ausführung:** Der Baustein ist als generischer Typ (`GEN_AL_SPLIT`) deklariert. Dadurch kann er in unterschiedlichen Projekten ohne Anpassung des Quellcodes verwendet werden, solange der zugrundeliegende Adaptertyp `AL` dem erwarteten Interface entspricht.
- **Unidirektionalität:** Der Baustein arbeitet ausschließlich unidirektional – Daten und Ereignisse fließen vom Socket zu den Plugs. Eine Rückkopplung oder bidirektionale Kommunikation ist nicht vorgesehen.
- **Keine Zustandslogik:** Der Baustein besitzt keine eigene Zustandsmaschine; er ist transparenter Natur.

## Zustandsübersicht

Der Baustein hat keine internen Zustände. Er ist jederzeit bereit, eingehende Adapter-Verbindungen zu verteilen. Ein aktiver Zustand ergibt sich allein aus der Anwesenheit eines gültigen Adapters am `IN`-Socket.

## Anwendungsszenarien

- **Steuerungsverteilung:** Ein übergeordneter Steuerungsadapter (z. B. zur Ansteuerung einer Achse oder eines Sensors) soll identische Signale an mehrere Parallelkomponenten senden.
- **Testumgebungen:** In Simulations- oder Testsetups können mit einem Adapter mehrere gleichartige Teilsysteme versorgt werden.
- **Signalbündelung:** Der Baustein kann als Verteiler in einer Hierarchie von Adaptern verwendet werden, wenn ein Signal auf mehrere nachfolgende Funktionsbausteine aufgeteilt werden muss.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem **AL_SPLIT_2** oder **AL_SPLIT_4** bietet **AL_SPLIT_7** eine höhere Anzahl von Ausgängen (sieben statt zwei oder vier). Während kleinere Splitter bei geringen Anforderungen ausreichen, ermöglicht dieser Baustein eine direkte Verteilung an sieben Empfänger, ohne mehrere Splitter kaskadieren zu müssen. Gegenüber einem **AL_MERGE** (der mehrere Eingänge zusammenführt) ist die Funktion genau entgegengesetzt.

## Fazit

Der **AL_SPLIT_7** ist ein einfacher, aber nützlicher generischer Baustein zur Vervielfältigung von unidirektionalen AL-Adapterverbindungen. Dank seiner generischen Natur und der klaren Schnittstelle lässt er sich flexibel in Automatisierungs- und Steuerungssysteme integrieren, in denen ein Signal auf mehrere Pfade verteilt werden muss. Seine implementationsbedingte Transparenz gewährleistet eine verlustfreie Weitergabe ohne zusätzliche Latenz.