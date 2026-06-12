# AW_SPLIT_3


![AW_SPLIT_3](./AW_SPLIT_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AW_SPLIT_3** dient als generischer Verteiler für einen unidirektionalen Adapter des Typs `AW`. Er nimmt eine einzige Adapterverbindung (Socket `IN`) entgegen und stellt diese identisch auf drei Ausgänge (Plugs `OUT1`, `OUT2`, `OUT3`) bereit. Der Baustein ist als generischer Funktionsblock (Generic FB) ausgelegt, sodass der konkrete Datentyp des Adapters `AW` zur Laufzeit festgelegt werden kann. Die Anwendung liegt in der Signalkopplung oder Befehlsweitergabe an mehrere nachfolgende Komponenten.

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
| Socket   | `IN`   | `adapter::types::unidirectional::AW` | Eingangsadapter – Quelle des zu verteilenden Signals. |
| Plug     | `OUT1` | `adapter::types::unidirectional::AW` | Erster Ausgang – identisches Signal wie `IN`. |
| Plug     | `OUT2` | `adapter::types::unidirectional::AW` | Zweiter Ausgang – identisches Signal wie `IN`. |
| Plug     | `OUT3` | `adapter::types::unidirectional::AW` | Dritter Ausgang – identisches Signal wie `IN`. |

## Funktionsweise

Der Baustein arbeitet ohne eigenen internen Zustandsautomaten oder Datenverarbeitung. Er stellt eine passive Verteilerstruktur dar: Die am Socket `IN` ankommende Adapterverbindung wird auf die drei Plugs `OUT1`, `OUT2` und `OUT3` durchgeschaltet. Alle ausgehenden Adapter sind logisch und zeitlich identisch zum eingehenden Signal. Eine Verzögerung, Pufferung oder Transformation findet nicht statt.

Da es sich um einen generischen Funktionsblock handelt, muss der Adaptertyp `AW` vor der Inbetriebnahme mit einem konkreten, kompatiblen Typ (z. B. `Analogwert` oder `Steuerbefehl`) parametrisiert werden. Dies geschieht über die Angabe des Attributs `eclipse4diac::core::GenericClassName`. Die Typauflösung erfolgt entweder zur Entwurfszeit (IDE) oder zur Laufzeit des Systems.

## Technische Besonderheiten

- **Generischer Ansatz**: Der Baustein ist als *Generic FB* realisiert (`GenericClassName` = `'GEN_AW_SPLIT'`). Dadurch kann derselbe Funktionsblock für verschiedene Adaptertypen verwendet werden, ohne dass für jeden Typ ein eigener FB erstellt werden muss.
- **Unidirektionalität**: Die Adapter sind als `unidirectional` deklariert. Das bedeutet, dass die Datenflussrichtung nur vom Socket zu den Plugs verläuft. Eine Rückmeldung von den Ausgängen zum Eingang ist nicht vorgesehen.
- **Keine Laufzeitlogik**: Der FB ist rein strukturell (passiv) – es werden keine Ereignisse, Zustände oder Berechnungen ausgeführt. Dies reduziert den Ressourcenverbrauch in Echtzeitsystemen.
- **Verwendung der Eclipse 4diac-Umgebung**: Der Baustein setzt auf die von 4diac bereitgestellten Mechanismen für generische Typen und Adapter.

## Zustandsübersicht

Der Funktionsblock besitzt keinen eigenen Zustandsautomaten (ECC). Er ist ein reiner Verbindungsbaustein ohne zeitliches Verhalten oder Zustandsänderungen. Die Funktionalität beschränkt sich auf die statische Weiterleitung des Adapters.

## Anwendungsszenarien

- **Signalfan-out in Steuerungen**: Ein Messwert (z. B. Temperatur, Druck) soll parallel an mehrere Regler oder Überwachungseinheiten gesendet werden.
- **Verteilen von Steuerbefehlen**: Ein zentrales Kommando wird an mehrere Aktoren oder Subsysteme gleichzeitig weitergegeben.
- **Redundante Signalpfade**: In sicherheitskritischen Anwendungen kann das gleiche Signal auf mehrere Pfade aufgeteilt werden, um unabhängige Auswertungen zu ermöglichen.
- **Prototypenentwicklung**: Der generische Charakter erlaubt es, den Baustein frühzeitig einzusetzen und den konkreten Adaptertyp später festzulegen.

## Vergleich mit ähnlichen Bausteinen

- **AW_MERGE_3** (hypothetisch): Ein Zusammenführer von drei AW-Eingängen auf einen Ausgang. Der AW_SPLIT_3 ist die logische Umkehrung.
- **SPLIT_ALL_2**: Ein nicht-generischer Splitter für zwei Ausgänge, der spezifische Datentypen verwendet. Der AW_SPLIT_3 bietet durch die Generizität mehr Flexibilität.
- **REPEATER**: Ein einfacher Verstärker oder Repeater für Adapter, der nur einen Ausgang besitzt. Der AW_SPLIT_3 erweitert dies auf drei parallele Ausgänge.

## Fazit

Der **AW_SPLIT_3** ist ein grundlegender, aber flexibler Verteilerbaustein in Eclipse 4diac. Seine generische Auslegung macht ihn universell einsetzbar für alle unidirektionalen Adaptertypen. Die klare, passive Struktur ohne zusätzliche Logik erlaubt eine effiziente und zuverlässige Signalverteilung in Automatisierungslösungen. Besonders in Kombination mit der Typvariabilität und 4diac-Adaptermechanik stellt er ein wertvolles Werkzeug für modulare und wiederverwendbare Steuerungsarchitekturen dar.