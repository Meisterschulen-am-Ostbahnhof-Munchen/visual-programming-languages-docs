# AB_SPLIT_7


![AB_SPLIT_7](./AB_SPLIT_7.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **AB_SPLIT_7** dient dazu, einen einzelnen eingehenden Adapter vom Typ `adapter::types::unidirectional::AB` auf sieben identische Ausgangsadapter aufzuteilen. Er ist als generischer Baustein (`GEN_AB_SPLIT`) realisiert und kann daher für verschiedene konkrete Adaptertypen instanziiert werden, die dem unidirektionalen AB-Protokoll entsprechen. Entwickelt wurde er unter der Eclipse Public License 2.0.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine vorhanden.

### **Ereignis-Ausgänge**

Keine vorhanden.

### **Daten-Eingänge**

Keine vorhanden.

### **Daten-Ausgänge**

Keine vorhanden.

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| IN   | `adapter::types::unidirectional::AB` | Socket (Eingang) | Eingehender Adapter, der auf die Ausgänge verteilt wird. |
| OUT1 | `adapter::types::unidirectional::AB` | Plug (Ausgang) | Erster ausgehender Adapter, identisch mit dem Eingang. |
| OUT2 | `adapter::types::unidirectional::AB` | Plug (Ausgang) | Zweiter ausgehender Adapter. |
| OUT3 | `adapter::types::unidirectional::AB` | Plug (Ausgang) | Dritter ausgehender Adapter. |
| OUT4 | `adapter::types::unidirectional::AB` | Plug (Ausgang) | Vierter ausgehender Adapter. |
| OUT5 | `adapter::types::unidirectional::AB` | Plug (Ausgang) | Fünfter ausgehender Adapter. |
| OUT6 | `adapter::types::unidirectional::AB` | Plug (Ausgang) | Sechster ausgehender Adapter. |
| OUT7 | `adapter::types::unidirectional::AB` | Plug (Ausgang) | Siebter ausgehender Adapter. |

## Funktionsweise

Der Baustein arbeitet als reiner Signalverteiler für Adapterverbindungen. Jeder Daten- oder Ereignisfluss, der über den Socket `IN` eintrifft, wird unverändert und parallel an alle sieben Ausgangs-Plugs (`OUT1` – `OUT7`) weitergeleitet. Es findet keine Verarbeitung, Pufferung oder Zustandsänderung statt. Der Baustein ist daher als passiver „Splitter“ zu verstehen.

Da es sich um unidirektionale Adapter handelt, erfolgt die Kommunikation nur in einer Richtung – vom Socket zu den Plugs. Die Ausgänge sind logisch identisch und können unabhängig voneinander mit nachfolgenden Bausteinen verbunden werden.

## Technische Besonderheiten

- **Generischer Typ**: Der Baustein ist als generischer FB (GenericClassName `'GEN_AB_SPLIT'`) deklariert. Das ermöglicht die Wiederverwendung für verschiedene Ausprägungen des unidirektionalen AB-Adapters, ohne die Schnittstelle neu definieren zu müssen.
- **Keine interne Logik**: Es existieren keine Ereignisauslöser, Datenoperationen oder Zustandsautomaten. Der FB ist vollständig durch seine Adapterverdrahtung definiert.
- **Unidirektionalität**: Der Adaptertyp `unidirectional::AB` unterstützt nur eine Datenflussrichtung. Rückkanäle sind nicht vorhanden.

## Zustandsübersicht

Der Funktionsbaustein besitzt keinen internen Zustandsautomaten (ECC). Er ist statisch und führt keinerlei sequenzielle Logik aus. Es gibt keine unterscheidbaren Betriebszustände.

## Anwendungsszenarien

- **Verteilen einer Steuerungsinformation** an mehrere parallele Verbraucher (z. B. Ansteuerung mehrerer gleichartiger Aktoren).
- **Aufteilen eines Rückmeldesignals** für getrennte Auswertungen in verschiedenen Zweigen einer Automatisierungsanwendung.
- **Erzeugen mehrerer identischer Adapterstränge** für Redundanz oder separate Überwachung.

Durch die generische Auslegung kann der Baustein in verschiedenen Kontexten eingesetzt werden, sobald der konkrete Adaptertyp spezifiziert ist.

## Vergleich mit ähnlichen Bausteinen

- **AB_MERGE**: Führt mehrere eingehende Adapter auf einen Ausgang zusammen – gegenteilige Funktion zu AB_SPLIT_7.
- **AB_SPLIT_N**: Verallgemeinerung mit parametrierbarer Anzahl an Ausgängen, falls verfügbar. AB_SPLIT_7 ist eine feste 1:7-Aufteilung.
- **Direkte Verdrahtung ohne Splitter**: Bei Bedarf an mehreren identischen Kopien müsste der Quell-FB mehrfach instanziiert werden, was den Entwurf aufbläht. Der Splitter reduziert Redundanz auf Ebene der Adapterverbindungen.

## Fazit

Der **AB_SPLIT_7** ist ein einfacher, aber nützlicher Baustein zur Vervielfachung einer unidirektionalen Adapterverbindung. Seine generische Natur und die klare Trennung von Ein- und Ausgängen machen ihn zu einem wiederverwendbaren Werkzeug in der 4diac-IDE, insbesondere in Szenarien, die eine parallele Verteilung von Signalen erfordern. Er trägt zur Modularität und Übersichtlichkeit industrieller Steuerungsanwendungen bei.