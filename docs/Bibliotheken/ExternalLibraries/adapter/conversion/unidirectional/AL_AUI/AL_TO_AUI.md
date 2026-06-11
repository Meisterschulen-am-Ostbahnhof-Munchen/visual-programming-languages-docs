# AL_TO_AUI


![AL_TO_AUI](./AL_TO_AUI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AL_TO_AUI** ist ein Composite-Baustein, der einen LWORD-Adapter (AL) in einen UINT-Adapter (AUI) umwandelt. Er ermöglicht die nahtlose Integration von LWORD-basierten Schnittstellen in Systeme, die UINT-Daten erwarten, indem er die Konvertierung innerhalb einer standardisierten Adapterstruktur kapselt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine eigenständigen Ereignis-Eingänge. Der Socket **AL_IN** liefert über seinen Ereignisausgang `E1` das auslösende Signal für die Konvertierung.

### **Ereignis-Ausgänge**
Keine eigenständigen Ereignis-Ausgänge. Der Plug **AUI_OUT** stellt über seinen Ereigniseingang `E1` die Bestätigung der abgeschlossenen Konvertierung bereit.

### **Daten-Eingänge**
Keine eigenständigen Daten-Eingänge. Der Socket **AL_IN** liefert über seinen Datenausgang `D1` den als `LWORD` zu konvertierenden Wert.

### **Daten-Ausgänge**
Keine eigenständigen Daten-Ausgänge. Der Plug **AUI_OUT** stellt über seinen Dateneingang `D1` den konvertierten `UINT`-Wert zur Verfügung.

### **Adapter**

| Typ | Richtung | Name | Beschreibung |
|-----|----------|------|--------------|
| Socket | Eingang | **AL_IN** | Adapter vom Typ `adapter::types::unidirectional::AL` – liefert ein LWORD-Datum und ein Ereignis zur Auslösung der Konvertierung. |
| Plug | Ausgang | **AUI_OUT** | Adapter vom Typ `adapter::types::unidirectional::AUI` – empfängt das konvertierte UINT-Datum und gibt das Bestätigungsereignis weiter. |

## Funktionsweise

Der Baustein besteht aus einem internen Netzwerk mit einem einzelnen Konvertierungsbaustein `F_LWORD_TO_UINT` aus der IEC-61131-Bibliothek. Die Ablaufsteuerung erfolgt strikt ereignisgesteuert:

1. Ein Ereignis am Socket `AL_IN.E1` wird an den `REQ`-Eingang des Konvertierungsbausteins weitergeleitet.
2. Der Konvertierungsbaustein liest das Datum von `AL_IN.D1` (Typ `LWORD`) und wandelt es nach IEC-61131-Regeln in einen `UINT`-Wert um.
3. Nach Abschluss der Konvertierung erzeugt der Baustein ein Ereignis an seinem `CNF`-Ausgang, das direkt an den Plug `AUI_OUT.E1` übergeben wird.
4. Gleichzeitig wird der konvertierte Wert über den Datenausgang `OUT` an den Dateneingang `AUI_OUT.D1` übergeben.

Damit ist die gesamte Konvertierung in einem einzigen, unidirektionalen Durchlauf abgeschlossen.

## Technische Besonderheiten

- **Kompositstruktur**: Der FB enthält keinen eigenen Zustandsautomaten, sondern delegiert die gesamte Funktionalität an den eingebetteten Konvertierungsbaustein.
- **Unidirektionale Adapter**: Sowohl der Eingangs- als auch der Ausgangsadapter sind vom Typ `unidirectional`. Es findet nur eine Vorwärtskonvertierung statt; Rückwärtsrichtung oder Statusrückmeldungen sind nicht vorgesehen.
- **Paketzuordnung**: Der FB befindet sich im Paket `adapter::conversion::unidirectional`, was auf seine Verwendung in modularen Adapterketten hinweist.
- **Wiederverwendbarkeit**: Der Baustein kann als universeller Umsetzer in beliebigen IEC-61499-Anwendungen eingesetzt werden, die eine LWORD-zu-UINT-Konvertierung über Adapter erfordern.

## Zustandsübersicht

Da es sich um einen Composite-Baustein ohne eigene Zustandsmaschine handelt, ist die Zustandslogik vollständig durch den internen Baustein `F_LWORD_TO_UINT` bestimmt. Dieser arbeitet nach einem einfachen REQ/CNF-Schema:

- **Warten auf REQ**: Inaktiv, kein Ereignis am Eingang.
- **Konvertierung aktiv**: Nach Eintreffen von `REQ` wird die Umwandlung durchgeführt.
- **CNF ausgeben**: Nach Abschluss wird `CNF` gesetzt und die Ausgabedaten aktualisiert.

Eine detaillierte Zustandsbeschreibung des Konvertierungsbausteins ist der IEC-61131-Dokumentation zu entnehmen.

## Anwendungsszenarien

- **Sensordatenanbindung**: Ein Sensor liefert Werte im LWORD-Format (z. B. 64-Bit-Zählerstände), die über einen AL-Adapter in das System eingespeist werden. Der `AL_TO_AUI`-Baustein wandelt diese in UINT (16-Bit) um, um sie an eine Steuerung mit UINT-Schnittstelle weiterzugeben.
- **Protokollkonvertierung**: In modularen Adapterketten dient der Baustein als Zwischenstufe, um von LWORD-basierten zu UINT-basierten Subsystemen zu wechseln, ohne die ursprüngliche Adapterlogik ändern zu müssen.
- **Datenreduktion**: Falls die oberen 48 Bit eines LWORD-Wertes nicht benötigt werden, kann der Baustein gezielt nur die unteren 16 Bit als UINT extrahieren (gemäß IEC-61131-Konvertierungsregeln).

## Vergleich mit ähnlichen Bausteinen

| Baustein | Ausgangstyp | Besonderheit |
|----------|-------------|--------------|
| `AL_TO_AUI` | UINT | Direkter Adapter-Konverter, unidirektional, Composite |
| `AL_TO_AUD` | DINT | Konvertiert LWORD in DINT (32-Bit) |
| `AUI_TO_AL` | LWORD | Rückwärtskonvertierung von UINT nach LWORD (nicht vorhanden, müsste separat implementiert werden) |

Im Vergleich zu einer direkten Verwendung von `F_LWORD_TO_UINT` bietet `AL_TO_AUI` den Vorteil der einfachen Integration in Adapter-Schnittstellen, ohne dass manuell Ereignis- und Datenverbindungen hergestellt werden müssen.

## Fazit

Der **AL_TO_AUI** ist ein komfortabler, standardisierter Adapter-Konverter für die Umwandlung von LWORD nach UINT. Dank seiner Composite-Struktur und der Nutzung bewährter IEC-61131-Konvertierungslogik lässt er sich nahtlos in modulare Adapterketten einfügen. Er eignet sich besonders für Anwendungen, bei denen heterogene Datentypen über einheitliche Adapterschnittstellen verbunden werden müssen.