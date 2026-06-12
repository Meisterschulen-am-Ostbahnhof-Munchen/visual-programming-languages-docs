# AW_SPLIT_8


![AW_SPLIT_8](./AW_SPLIT_8.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AW_SPLIT_8** ist ein generischer Baustein, der ein eingehendes unidirektionales AW-Adapter-Signal auf acht identische Ausgangssignale aufteilt. Der Baustein wurde als generischer FB (generic FB) implementiert und kann zur Laufzeit mit einem konkreten Typnamen und Typprüfcode versehen werden. Er dient als 1:8-Verteiler für AW-Datenströme und wird typischerweise in der Automatisierungstechnik eingesetzt, wenn ein Signal gleichzeitig an mehrere Senken weitergeleitet werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden. Die Kommunikation erfolgt ausschließlich über die Adapter-Schnittstellen.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden. Die Datenweitergabe erfolgt über die Adapter-Plugs.

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden. Alle Eingangsdaten werden über den Socket-Adapter `IN` bereitgestellt.

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden. Die Ausgangsdaten werden über die Plug-Adapter `OUT1` bis `OUT8` ausgegeben.

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|------|------|----------|--------------|
| `adapter::types::unidirectional::AW` | `IN` | Socket (Eingang) | Quell-Adapter, der das aufzuteilende Signal liefert |
| `adapter::types::unidirectional::AW` | `OUT1` | Plug (Ausgang) | Erster Ausgang, identisch zum IN-Signal |
| `adapter::types::unidirectional::AW` | `OUT2` | Plug (Ausgang) | Zweiter Ausgang |
| `adapter::types::unidirectional::AW` | `OUT3` | Plug (Ausgang) | Dritter Ausgang |
| `adapter::types::unidirectional::AW` | `OUT4` | Plug (Ausgang) | Vierter Ausgang |
| `adapter::types::unidirectional::AW` | `OUT5` | Plug (Ausgang) | Fünfter Ausgang |
| `adapter::types::unidirectional::AW` | `OUT6` | Plug (Ausgang) | Sechster Ausgang |
| `adapter::types::unidirectional::AW` | `OUT7` | Plug (Ausgang) | Siebter Ausgang |
| `adapter::types::unidirectional::AW` | `OUT8` | Plug (Ausgang) | Achter Ausgang |

## Funktionsweise

Der Baustein verhält sich wie ein passiver Splitter. Sobald am Socket `IN` ein gültiges AW-Adapter-Signal anliegt (z. B. durch ein Ereignis aus dem Adapterprotokoll), wird dieses Signal simultan an alle acht Plug-Adapter (`OUT1`–`OUT8`) weitergegeben. Es erfolgt keine Datenänderung, Pufferung oder Verzögerung. Der Baustein ist ereignisgesteuert im Sinne des zugrundeliegenden Adapterprotokolls: Die Weitergabe wird durch den Adapter-Mechanismus der IEC 61499-2 ausgelöst.

Die Ausgänge liefern stets den identischen Dateninhalt wie der Eingang. Falls der Eingang keine gültigen Daten enthält, geben auch die Ausgänge keine Daten aus.

## Technische Besonderheiten

- **Generischer Funktionsblock (generic FB):** Der Baustein wird als generisch deklariert und trägt die Attribute `eclipse4diac::core::GenericClassName` (Standardwert: `'GEN_AW_SPLIT'`) und `eclipse4diac::core::TypeHash` (Standardwert: `''`). Dies ermöglicht die späte Bindung an einen konkreten Funktionsblock-Typen, z. B. um typsicherere Instanzen zu erzeugen.
- **Keine eigenen Ereignisse oder Variablen:** Der Baustein besitzt keine expliziten Ereignis-Ein-/Ausgänge und keine Daten-Ein-/Ausgänge im klassischen Sinne. Die gesamte Kommunikation wird über die Adapter-Schnittstellen abgewickelt, was die Komplexität reduziert und die Wiederverwendbarkeit erhöht.
- **Unidirektionale Adapter:** Verwendet werden ausschließlich unidirektionale AW-Adapter. Eine Rückkopplung von den Ausgängen zum Eingang ist nicht vorgesehen.

## Zustandsübersicht

Der Funktionsblock besitzt keine eigene Zustandsmaschine (z. B. ECC – Execution Control Chart). Sein Verhalten wird vollständig durch das Verhalten des verwendeten Adaptertyps `adapter::types::unidirectional::AW` bestimmt. Im einfachsten Fall gibt es zwei implizite Zustände:

- **Idle:** Kein gültiges Signal am Eingang. Alle Ausgänge sind inaktiv.
- **Active:** Ein gültiges Signal liegt am Eingang an und wird auf alle Ausgänge repliziert.

Eine genauere Zustandsbeschreibung ist aus den Adapterdefinitionen abzuleiten.

## Anwendungsszenarien

- **Parallelversorgung mehrerer Verbraucher:** Ein Sensor- oder Steuerungssignal (z. B. Geschwindigkeitssollwert) soll gleichzeitig an mehrere Aktoren oder Subsysteme verteilt werden, ohne dass ein eigener Verteiler-Baustein programmiert werden muss.
- **Test- und Simulationsumgebungen:** Ein einzelnes Testsignal kann auf mehrere Analyse- oder Logging-Kanäle aufgeschaltet werden.
- **Datenvervielfachung in hierarchischen Steuerungen:** In modularen Anlagen kann ein zentraler Steuerungsdatenstrom an mehrere dezentrale Einheiten (z. B. Feldgeräte) weitergegeben werden.

## Vergleich mit ähnlichen Bausteinen

- **AW_SPLIT_2, AW_SPLIT_4:** Analog aufgebaute Splitter mit weniger Ausgängen (2 bzw. 4). Die Anzahl der Ausgänge ist der einzige Unterschied. Für Anwendungen mit genau 8 benötigten Ausgängen ist `AW_SPLIT_8` die passende Wahl.
- **Allgemeine Splitter (z. B. für andere Adaptertypen):** Es existieren Splitter für verschiedene Adapter-Datentypen (z. B. `BOOL_SPLIT`, `INT_SPLIT`), die analoge Struktur aufweisen, aber unterschiedliche Adapter-Schnittstellen besitzen.
- **Multicast-Bausteine:** Komplexere Bausteine können zusätzlich Filter-, Priorisierungs- oder Pufferfunktionen bieten; `AW_SPLIT_8` ist absichtlich minimalistisch gehalten, um keine unerwünschten Seiteneffekte zu erzeugen.

## Fazit

Der Baustein `AW_SPLIT_8` ist ein einfacher, aber nützlicher generischer 1:8-Splitter für unidirektionale AW-Adapter. Er erfüllt die grundlegende Anforderung, ein eingehendes Signal ohne Verzögerung oder Veränderung auf acht Ausgänge zu verteilen. Durch seine generische Auslegung kann er in verschiedenen Kontexten eingesetzt werden, in denen eine typsichere Vervielfältigung von Adapterdatenströmen benötigt wird. Die strikte Einhaltung des IEC 61499-2-Standards und die Verwendung von Adaptern erleichtern die Integration in bestehende 4diac-Projekte.