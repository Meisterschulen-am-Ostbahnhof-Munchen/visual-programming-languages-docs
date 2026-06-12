# AULI_SPLIT_7


![AULI_SPLIT_7](./AULI_SPLIT_7.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AULI_SPLIT_7** dient als generischer Splitter, der ein eingehendes AULI-Adapter-Signal (unidirektional) auf sieben separate AULI-Ausgänge verteilt. Er ist speziell für die Aufteilung eines Befehls- oder Datenstroms (AULI-Protokoll) ausgelegt und ermöglicht die gleichzeitige Versorgung mehrerer nachgeschalteter Bausteine mit dem gleichen Signal.

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
| Socket (Eingang) | IN | `adapter::types::unidirectional::AULI` | Empfängt das aufzuteilende AULI-Signal |
| Plug (Ausgang) | OUT1 | `adapter::types::unidirectional::AULI` | Erster Ausgang für das AULI-Signal |
| Plug (Ausgang) | OUT2 | `adapter::types::unidirectional::AULI` | Zweiter Ausgang |
| Plug (Ausgang) | OUT3 | `adapter::types::unidirectional::AULI` | Dritter Ausgang |
| Plug (Ausgang) | OUT4 | `adapter::types::unidirectional::AULI` | Vierter Ausgang |
| Plug (Ausgang) | OUT5 | `adapter::types::unidirectional::AULI` | Fünfter Ausgang |
| Plug (Ausgang) | OUT6 | `adapter::types::unidirectional::AULI` | Sechster Ausgang |
| Plug (Ausgang) | OUT7 | `adapter::types::unidirectional::AULI` | Siebter Ausgang |

## Funktionsweise

Der Baustein leitet das am Socket **IN** anliegende AULI-Signal unverändert an alle sieben Plugs **OUT1** bis **OUT7** weiter. Es findet keine Signalverarbeitung, Filterung oder Verzögerung statt. Jeder Ausgang empfängt simultan dieselbe Signalfolge wie der Eingang. Die Aufteilung erfolgt rein leitungs- bzw. signaltechnisch innerhalb der 4diac-IDE; es sind keine Berechnungen oder Zustandsänderungen erforderlich.

## Technische Besonderheiten

- **Generischer Baustein:** Der FB ist als generischer Typ (`GEN_AULI_SPLIT`) deklariert und verwendet das Attribut `eclipse4diac::core::GenericClassName` für die typsichere Adapterzuordnung.
- **Unidirektionaler Adapter:** Sowohl Eingang als auch Ausgänge basieren auf dem Adapter-Typ `adapter::types::unidirectional::AULI`, der nur eine Datenflussrichtung unterstützt.
- **Keine Ereignissteuerung:** Der FB benötigt keine Trigger-Ereignisse; die Signalweitergabe erfolgt automatisch bei Änderung des Eingangssignals.
- **Keine internen Zustände:** Es gibt keinen Zustandsautomaten oder Speicherverhalten – der Baustein ist rein kombinatorisch.

## Zustandsübersicht

Da keine Zustandsmaschine (ECC) vorhanden ist, besitzt der Baustein keine internen Zustände. Das Ausgangssignal folgt unmittelbar dem Eingangssignal ohne Verzögerung oder Logik.

## Anwendungsszenarien

- **Parallelversorgung mehrerer Aktuatoren**: Ein gemeinsames Steuersignal (z.B. über AULI-Adapter) soll gleichzeitig an mehrere Stellglieder oder Subsysteme verteilt werden.
- **Signal-Multicasting**: Verteilung eines Sensorsignals oder einer Konfigurationsnachricht an mehrere Empfänger in der Automatisierungsanlage.
- **Test- und Simulationsaufbauten**: Aufteilen eines Eingangssignals zur gleichzeitigen Überwachung an verschiedenen Messpunkten.

## Vergleich mit ähnlichen Bausteinen

Die 4diac-Bibliothek enthält Splitter-Bausteine für verschiedene Ausgangszahlen, z.B. `AULI_SPLIT_3` oder `AULI_SPLIT_5`. Der `AULI_SPLIT_7` unterscheidet sich lediglich durch die Anzahl der Ausgänge (7). Bausteine zur Aufteilung anderer Adaptertypen (z.B. `BOOL_SPLIT`, `INT_SPLIT`) haben eine ähnliche Logik, arbeiten jedoch mit unterschiedlichen Daten- bzw. Adapterformaten.

## Fazit

Der `AULI_SPLIT_7` ist ein einfacher, aber essenzieller Baustein zur Signalverteilung innerhalb der AULI-Adapterlandschaft. Er erlaubt die saubere und typsichere Aufteilung eines unidirektionalen Signals auf bis zu sieben Pfade, ohne zusätzliche Logik oder Verzögerungen. Dank seiner generischen Auslegung lässt er sich flexibel in IEC 61499-basierten Automatisierungsprojekten einsetzen.