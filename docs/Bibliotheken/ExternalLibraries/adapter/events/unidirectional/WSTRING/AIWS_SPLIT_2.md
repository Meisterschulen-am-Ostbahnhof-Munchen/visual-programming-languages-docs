# AIWS_SPLIT_2


![AIWS_SPLIT_2](./AIWS_SPLIT_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AIWS_SPLIT_2** dient dazu, ein eingehendes AIWS‑Adapter-Signal auf zwei identische Ausgänge aufzuteilen. Er ist als generischer Baustein ausgelegt und ermöglicht die Mehrfachverwendung eines AIWS‑Signals innerhalb der gleichen Applikation, ohne dass eine separate Signalverteilung programmiert werden muss.

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
| Socket (Eingang) | **IN** | `adapter::types::unidirectional::AIWS` | Eingehendes AIWS‑Signal, das auf beide Ausgänge verteilt wird. |
| Plug (Ausgang) | **OUT1** | `adapter::types::unidirectional::AIWS` | Erster Ausgang – identisches Signal wie am Eingang. |
| Plug (Ausgang) | **OUT2** | `adapter::types::unidirectional::AIWS` | Zweiter Ausgang – identisches Signal wie am Eingang. |

## Funktionsweise

Der Baustein leitet das am Socket **IN** anliegende AIWS‑Signal unverändert an beide Plugs **OUT1** und **OUT2** weiter. Es findet keine logische oder zeitliche Verarbeitung statt – die Aufteilung erfolgt rein passiv durch die Verdrahtung innerhalb des Funktionsblocks. Dadurch können zwei unabhängige Adapter‑Instanzen gleichzeitig mit denselben Daten versorgt werden.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_AIWS_SPLIT`) deklariert, sodass er für verschiedene AIWS‑Ausprägungen wiederverwendet werden kann.
- **Reine Adapterlogik**: Es werden weder Ereignisse noch Daten-E/A verwendet; die gesamte Kommunikation erfolgt ausschließlich über die Adapter‑Schnittstellen.
- **Keine Zustandsabhängigkeit**: Der FB besitzt keine interne Zustandsmaschine – das Ausgangssignal folgt dem Eingangssignal ohne Verzögerung oder Pufferung.

## Zustandsübersicht

Der Funktionsblock ist zustandslos. Es existieren keine internen Zustände oder Übergänge. Die Ausgänge sind zu jedem Zeitpunkt eine direkte Abbildung des Eingangs.

## Anwendungsszenarien

- **Verteilen eines Sensorsignals**: Ein einzelner AIWS‑Sensor (z. B. analoger Wert) soll von zwei unabhängigen Regelungs- oder Überwachungsbausteinen gleichzeitig gelesen werden.
- **Redundante Verarbeitung**: Bei Sicherheitsanwendungen kann dasselbe Signal an mehrere parallele Auswertefunktionen übergeben werden.
- **Logische Verzweigung**: Aufteilung eines Datenstroms für unterschiedliche Auswertungen oder Visualisierungen in einer 4diac‑Applikation.

## Vergleich mit ähnlichen Bausteinen

- **AIWS_SPLIT_3, AIWS_SPLIT_4**: Erweiterte Varianten mit drei bzw. vier Ausgängen – prinzipiell gleiche Funktionsweise.
- **SPLIT‑Bausteine für andere Adaptertypen**: In 4diac existieren analoge Split‑Bausteine für andere Adapter (z. B. `DINT_SPLIT`), die ein Datensignal auf mehrere Ausgänge verteilen – jedoch auf Datenebene und nicht über Adapter.
- **Ereignis‑Split‑Bausteine**: Bausteine wie `E_SPLIT` verteilen Ereignisse, nicht Datenströme – AIWS_SPLIT_2 adressiert spezifisch die AIWS‑Adapterkommunikation.

## Fazit

Der **AIWS_SPLIT_2** ist ein einfacher, aber nützlicher generischer Funktionsblock zur Vervielfältigung eines AIWS‑Adaptersignals. Er reduziert den Verdrahtungsaufwand in Applikationen, die dasselbe analoge oder gemischte Signal mehrfach benötigen, und fügt sich durch seine passive, zustandslose Architektur transparent in bestehende Abläufe ein.