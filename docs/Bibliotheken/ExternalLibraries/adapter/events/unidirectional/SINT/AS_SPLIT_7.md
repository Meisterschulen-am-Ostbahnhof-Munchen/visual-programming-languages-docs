# AS_SPLIT_7


![AS_SPLIT_7](./AS_SPLIT_7.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AS_SPLIT_7** dient dazu, ein ankommendes unidirektionales AS‑Signal (z. B. ein analoges oder binäres Automatisierungssignal) auf sieben identische Ausgänge zu verteilen. Der Baustein ist als generischer FB realisiert und wird häufig in der Automatisierungstechnik eingesetzt, um ein Signal mehreren nachfolgenden Verbrauchern oder Prozessschritten bereitzustellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine

### **Ereignis-Ausgänge**

Keine

### **Daten-Eingänge**

Keine (Die Signalweitergabe erfolgt ausschließlich über Adapter.)

### **Daten-Ausgänge**

Keine

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| IN | `adapter::types::unidirectional::AS` | Socket | Empfängt das zu verteilende AS‑Signal. |
| OUT1 | `adapter::types::unidirectional::AS` | Plug | Erster Ausgang – gleiches Signal wie am Eingang. |
| OUT2 | `adapter::types::unidirectional::AS` | Plug | Zweiter Ausgang – gleiches Signal wie am Eingang. |
| OUT3 | `adapter::types::unidirectional::AS` | Plug | Dritter Ausgang – gleiches Signal wie am Eingang. |
| OUT4 | `adapter::types::unidirectional::AS` | Plug | Vierter Ausgang – gleiches Signal wie am Eingang. |
| OUT5 | `adapter::types::unidirectional::AS` | Plug | Fünfter Ausgang – gleiches Signal wie am Eingang. |
| OUT6 | `adapter::types::unidirectional::AS` | Plug | Sechster Ausgang – gleiches Signal wie am Eingang. |
| OUT7 | `adapter::types::unidirectional::AS` | Plug | Siebter Ausgang – gleiches Signal wie am Eingang. |

## Funktionsweise

Der Baustein leitet das am Socket `IN` anliegende AS‑Signal unverändert an alle sieben Plug‑Ausgänge weiter. Es findet keine Signalaufbereitung, Verstärkung oder Verarbeitung statt. Der FB arbeitet rein passiv und ohne zeitliche Verzögerung – sobald am Eingang ein Signal anliegt, steht es an allen Ausgängen gleichzeitig zur Verfügung.

## Technische Besonderheiten

- **Generischer Baustein:** Der FB ist als generischer Typ (`GEN_AS_SPLIT`) implementiert und kann durch Parametrierung in verschiedenen Kontexten verwendet werden.
- **Adapter‑basierte Schnittstelle:** Die Kommunikation erfolgt ausschließlich über unidirektionale Adapter des Typs `adapter::types::unidirectional::AS`. Dadurch ist der FB besonders geeignet für modulare Architekturen, bei denen Signale über klar definierte Schnittstellen ausgetauscht werden.
- **Keine Zustandslogik:** Der FB besitzt keine internen Zustände, keine Ereignisse und keine Verarbeitungslogik – die Verteilung erfolgt rein kombinatorisch.
- **Einfache Erweiterbarkeit:** Durch die generische Natur des Bausteins lassen sich analoge Splitter‑Varianten (z. B. `AS_SPLIT_2`, `AS_SPLIT_4`) leicht ableiten oder durch Anpassung der Parameter erzeugen.

## Zustandsübersicht

Der **AS_SPLIT_7** besitzt keine Zustandsautomaten, da er rein passiv arbeitet. Es gibt keine Start‑, Stopp‑ oder Fehlerzustände. Das Verhalten ist zu jeder Zeit ausschließlich durch den aktuellen Wert des Eingangssignals bestimmt.

## Anwendungsszenarien

- **Signalverteilung in Leitsystemen:** Ein analoges Messsignal (z. B. Druck, Temperatur) wird auf mehrere Anzeigen, Regler oder Datensammler verteilt.
- **Parallelschaltung von Aktoren:** Ein Steuersignal (z. B. 0‑10 V) soll gleichzeitig mehrere Stellglieder ansteuern.
- **Redundante Signalpfade:** Das gleiche Signal wird mehreren unabhängigen Verarbeitungseinheiten zur Verfügung gestellt, um Redundanz zu schaffen.
- **Test- und Simulationsumgebungen:** Ein generiertes Testsignal wird auf mehrere Simulationskomponenten aufgeteilt.

## Vergleich mit ähnlichen Bausteinen

Der **AS_SPLIT_7** gehört zu einer Familie von Splitter‑Bausteinen, die sich nur in der Anzahl der Ausgänge unterscheiden (z. B. `AS_SPLIT_2`, `AS_SPLIT_3`, …, `AS_SPLIT_N`). Gegenüber einer manuellen Verkabelung bietet der FB den Vorteil der Wiederverwendbarkeit, klaren Schnittstellendefinition und einfachen Parametrierbarkeit. Im Gegensatz zu aktiven Signalverteilern (z. B. mit Verstärkung) nimmt der Baustein keinerlei Einfluss auf das Signal und verhält sich daher ideal für passive Anwendungen.

## Fazit

Der **AS_SPLIT_7** ist ein einfacher, aber nützlicher Funktionsblock zur passiven Verteilung eines unidirektionalen AS‑Signals auf sieben Ausgänge. Dank seiner generischen Implementierung und der Adapter‑Schnittstelle fügt er sich nahtlos in moderne, komponentenbasierte Automatisierungslösungen ein. Für Anwendungen, die eine reine Signalvervielfachung ohne Verarbeitung erfordern, stellt er eine zuverlässige und leicht verständliche Lösung dar.