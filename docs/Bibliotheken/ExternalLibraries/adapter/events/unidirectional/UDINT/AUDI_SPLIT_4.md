# AUDI_SPLIT_4


![AUDI_SPLIT_4](./AUDI_SPLIT_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUDI_SPLIT_4** dient dazu, ein eingehendes unidirektionales **AUDI**-Adapter-Signal auf vier identische Ausgänge zu verteilen. Er fungiert als einfacher Signalverteiler (Fan‑out) für den generischen Adaptertyp **AUDI**. Der Baustein ist als generischer Funktionsblock (Generic FB) realisiert und kann über die Klasse `GEN_AUDI_SPLIT` an unterschiedliche Adapter-Typen angepasst werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket** | `IN` | `adapter::types::unidirectional::AUDI` | Eingangsadapter, der das zu verteilende Signal bereitstellt. |
| **Plug** | `OUT1` | `adapter::types::unidirectional::AUDI` | Erster Ausgang, identisch zum Eingangssignal. |
| **Plug** | `OUT2` | `adapter::types::unidirectional::AUDI` | Zweiter Ausgang, identisch zum Eingangssignal. |
| **Plug** | `OUT3` | `adapter::types::unidirectional::AUDI` | Dritter Ausgang, identisch zum Eingangssignal. |
| **Plug** | `OUT4` | `adapter::types::unidirectional::AUDI` | Vierter Ausgang, identisch zum Eingangssignal. |

## Funktionsweise

Der Baustein arbeitet **ereignislos** und **kontinuierlich**:  
Sobald der Socket `IN` mit einem AUDI-Adapter verbunden ist, werden die über diesen Adapter übertragenen Daten oder Signale unverändert an alle vier Ausgangsadapter (`OUT1` bis `OUT4`) weitergeleitet. Es findet keine Verarbeitung oder Umwandlung der Daten statt – der Baustein fungiert ausschließlich als passiver Verteiler (Splitter). Da keine Ereignisse oder Zustandsänderungen beteiligt sind, erfolgt die Verteilung implizit durch die Verbindungsstruktur.

## Technische Besonderheiten

- **Generischer Funktionsblock**: Der Baustein ist als generischer Typ mit dem Klassennamen `'GEN_AUDI_SPLIT'` deklariert. Dadurch kann der konkrete Adaptertyp (z. B. ein spezialisierter AUDI‑Subtyp) zur Entwurfszeit oder durch Code‑Generierung angepasst werden.
- **Unidirektionale Adapter**: Alle verwendeten Adapter (`AUDI`) sind unidirektional, d. h. der Datenfluss erfolgt nur vom Socket zu den Plugs.
- **Keine Ereignissteuerung**: Der Baustein besitzt keine Ereigniseingänge oder -ausgänge. Die Signalverteilung geschieht datenflussgetrieben und benötigt keine explizite Auslösung.
- **Skalierbarkeit**: Der Baustein ist speziell für 4 Ausgänge ausgelegt. Für andere Anzahlen existieren entsprechende Varianten (z. B. `AUDI_SPLIT_2`, `AUDI_SPLIT_3`).

## Zustandsübersicht

Der Baustein verfügt über **keine Zustandsmaschine (ECC)**, da er keine Ereignisse verarbeitet und keinen internen Zustand speichert. Die Funktion ist rein kombinatorisch: Die Ausgänge spiegeln kontinuierlich den Eingang wider.

## Anwendungsszenarien

- **Signalverteilung in Steuerungssystemen**: Ein vom Sensor oder übergeordnetem System bereitgestelltes AUDI‑Signal soll parallel an mehrere Verbraucher (Aktoren, Visualisierungen, Logikeinheiten) weitergegeben werden.
- **Test- und Simulationsumgebungen**: Ein einzelnes Testsignal wird auf mehrere parallele Prüfpfade aufgeteilt.
- **Prototypische Adapter‑Kopplung**: Wenn mehrere nachgeschaltete Blöcke das gleiche Eingangssignal benötigen, ohne dass eine logische Vervielfachung nötig ist.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion | Besonderheit |
|----------|----------|--------------|
| `AUDI_SPLIT_2` | Verteilt ein AUDI‑Signal auf zwei Ausgänge. | Entspricht dem Prinzip, jedoch mit 2 Ausgängen. |
| `AUDI_SPLIT_4` | Verteilt ein AUDI‑Signal auf vier Ausgänge. | Vorliegender Baustein, einfacher 1:4‑Splitter. |
| `AUDI_MERGE` | Fasst mehrere AUDI‑Eingänge zu einem Ausgang zusammen. | Umkehrung des Splitters (1:1‑Mapping, aber invers). |
| Generische Splitter | Können über Typ-Parameter auf andere Adapter angewendet werden. | Bieten mehr Flexibilität als fest verdrahtete Varianten. |

## Fazit

Der `AUDI_SPLIT_4` ist ein einfacher, aber nützlicher Funktionsblock zur Vervielfachung eines unidirektionalen AUDI‑Adapter‑Signals auf vier parallele Ausgänge. Seine generische Natur erlaubt die Anpassung an verschiedene Adaptertypen, und die ereignislose Arbeitsweise macht ihn besonders geeignet für reine Datenverteilungsaufgaben ohne zusätzliche Steuerlogik. Der Baustein trägt zur Strukturierung und Wiederverwendbarkeit von Signalen in komplexen Automatisierungslösungen bei.