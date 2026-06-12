# ASR_SPLIT_6


![ASR_SPLIT_6](./ASR_SPLIT_6.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `ASR_SPLIT_6` verteilt ein eingehendes ASR-Signal (Generic Adapter Typ) auf sechs identische ASR-Ausgänge. Er dient als reiner Signalverteiler (Splitter) und wird als generischer Baustein in der 4diac-IDE bereitgestellt.

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

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| `IN` | Socket | `adapter::types::unidirectional::ASR` | Eingangsadapter – das zu verteilende ASR-Signal |
| `OUT1` – `OUT6` | Plug | `adapter::types::unidirectional::ASR` | Sechs Ausgangsadapter – identische Kopien des Eingangssignals |

## Funktionsweise

Der Baustein führt keine Datenverarbeitung oder Zustandslogik durch. Er leitet den am Socket `IN` anliegenden Adapter (unidirektionales ASR) direkt und ohne Verzögerung an alle sechs Plugs (`OUT1` bis `OUT6`) weiter. Somit liegt an jedem Ausgang dasselbe Signal wie am Eingang an. Die Verteilung geschieht rein auf Adapterebene, ohne dass Ereignisse oder Daten-Ein-/Ausgänge beteiligt sind.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB verwendet die generische Typdefinition `GEN_ASR_SPLIT` (Attribut `eclipse4diac::core::GenericClassName`). Dies erlaubt eine flexible Wiederverwendung mit unterschiedlichen ASR-Adapter-Typen.
- **Unidirektionaler Adapter**: Sowohl Eingang als auch Ausgänge sind vom Typ `adapter::types::unidirectional::ASR`, d. h. die Daten fließen nur in einer Richtung (vom Socket zu den Plugs).
- **Keine Zustandslogik**: Der Baustein besitzt kein ECC (Execution Control Chart) und keine internen Zustände – es handelt sich um eine reine Verbindung ohne zeitliches Verhalten.
- **Skalierbarkeit**: Durch das generische Konzept können ähnliche Splitter mit beliebig vielen Ausgängen (z. B. 2, 4, 8) erstellt werden.

## Zustandsübersicht

Es existiert kein Zustandsdiagramm (ECC), da der Baustein keine sequentielle Logik ausführt. Die Signalverteilung erfolgt statisch und kontinuierlich.

## Anwendungsszenarien

- **Verteilung eines Sensorsignals** an mehrere Steuerungseinheiten oder Subsysteme.
- **Bereitstellung desselben ASR-Kommunikationskanals** für parallele Verarbeitungszweige.
- **Test- und Simulationsumgebungen**, in denen ein Eingangssignal mehrfach benötigt wird.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Ausgänge | Besonderheit |
|----------|----------|--------------|
| `ASR_SPLIT_2` | 2 | Zweifach-Split |
| `ASR_SPLIT_4` | 4 | Vierfach-Split |
| **`ASR_SPLIT_6`** | **6** | **Sechsfach-Split (dieser Baustein)** |
| Generischer Split (z. B. über Template) | variabel | Erfordert individuelle Parametrisierung |

Der `ASR_SPLIT_6` bietet eine feste Anzahl von sechs Ausgängen und ist damit speziell für Anwendungen ausgelegt, die genau diese Anzahl benötigen.

## Fazit

Der `ASR_SPLIT_6` ist ein einfacher, aber nützlicher Funktionsblock zur Signalvervielfältigung auf Adapterebene. Durch seine generische Natur und die klare, ereignislose Funktionsweise eignet er sich ideal für modulare Steuerungsarchitekturen, die eine Mehrfachnutzung eines ASR-Signals erfordern.