# ALI_SPLIT_6


![ALI_SPLIT_6](./ALI_SPLIT_6.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock ALI_SPLIT_6 dient dazu, ein eingehendes unidirektionales ALI-Adapter-Signal (Application Layer Interface) auf sechs identische Ausgänge zu verteilen. Er ist als generischer Baustein konzipiert und ermöglicht eine einfache Signalvervielfachung ohne zusätzliche Logik.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*Keine*

### **Ereignis-Ausgänge**
*Keine*

### **Daten-Eingänge**
*Keine*

### **Daten-Ausgänge**
*Keine*

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::ALI` | `IN` | Socket (Eingang) | Ein ALI-Adapter, dessen Signal auf alle Ausgänge verteilt wird. |
| `adapter::types::unidirectional::ALI` | `OUT1` | Plug (Ausgang) | Erster Ausgang mit dem Signal des Eingangs. |
| `adapter::types::unidirectional::ALI` | `OUT2` | Plug (Ausgang) | Zweiter Ausgang mit dem Signal des Eingangs. |
| `adapter::types::unidirectional::ALI` | `OUT3` | Plug (Ausgang) | Dritter Ausgang mit dem Signal des Eingangs. |
| `adapter::types::unidirectional::ALI` | `OUT4` | Plug (Ausgang) | Vierter Ausgang mit dem Signal des Eingangs. |
| `adapter::types::unidirectional::ALI` | `OUT5` | Plug (Ausgang) | Fünfter Ausgang mit dem Signal des Eingangs. |
| `adapter::types::unidirectional::ALI` | `OUT6` | Plug (Ausgang) | Sechster Ausgang mit dem Signal des Eingangs. |

## Funktionsweise

Der ALI_SPLIT_6 realisiert eine einfache 1:6-Verteilung. Das über den Socket `IN` empfangene ALI-Adapter-Signal wird unverändert und gleichzeitig an alle sechs Plugs (`OUT1` bis `OUT6`) weitergeleitet. Es findet keine Signalverarbeitung, Verzögerung oder Zustandsänderung statt. Die Verteilung erfolgt rein strukturell über die Adapterverbindungen.

## Technische Besonderheiten

- **Generischer Baustein:** Der FB ist als generischer Funktionsblock definiert. Über das Attribut `eclipse4diac::core::GenericClassName` kann der konkrete Klassenname (z. B. `'GEN_ALI_SPLIT'`) festgelegt werden. Das Attribut `eclipse4diac::core::TypeHash` kann zur Identifikation der spezifischen Konfiguration verwendet werden.
- **Keine Zustandsautomaten:** Der FB besitzt kein ECC (Execution Control Chart) und keinerlei interne Logik. Er arbeitet rein passiv.
- **Unidirektionale ALI-Adapterschnittstelle:** Sowohl Ein- als auch Ausgänge verwenden den Typ `adapter::types::unidirectional::ALI`, was eine einfache und standardisierte Kommunikation ermöglicht.

## Zustandsübersicht

Der FB besitzt keine eigenen Zustände oder Verhaltensmodi, da er nur eine strukturelle Weiterleitung vornimmt. Eine Zustandsbetrachtung entfällt daher.

## Anwendungsszenarien

- **Steuerung mehrerer Aktoren:** Ein ALI-Signal, z. B. ein Freigabe- oder Stellsignal, soll gleichzeitig an sechs Empfänger (z. B. Servomotoren oder Ventilinseln) weitergegeben werden.
- **Signalverteilung in modularen Systemen:** In einer industriellen Steuerung kann ein zentrales ALI-Signal auf mehrere dezentrale Einheiten aufgeteilt werden.
- **Ersatz von manuellen Verdrahtungen:** Der FB ersetzt die physische Aufteilung eines Signals durch eine softwaredefinierte, wartbare Lösung.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Ausgänge | Besonderheit |
|----------|----------|--------------|
| ALI_SPLIT_2 | 2 | Zweifachverteilung |
| ALI_SPLIT_4 | 4 | Vierfachverteilung |
| **ALI_SPLIT_6** | **6** | **Sechsfachverteilung, generisch** |
| ALI_SPLIT_8 | 8 | Achtfachverteilung |

Der ALI_SPLIT_6 unterscheidet sich von anderen Split-Varianten lediglich durch die Anzahl der Ausgänge. Alle Bausteine dieser Familie arbeiten nach dem gleichen passiven Verteilerprinzip. Der hier beschriebene FB ist als generischer Baustein ausgeführt, während andere Varianten möglicherweise als einfache FB-Typen ohne Generizität implementiert sind.

## Fazit

Der ALI_SPLIT_6 ist ein einfacher, aber nützlicher Funktionsblock zur Vervielfachung eines unidirektionalen ALI-Adapter-Signals auf sechs identische Ausgänge. Dank seiner generischen Eigenschaften lässt er sich flexibel in verschiedene Steuerungssysteme einbinden. Aufgrund der fehlenden Verarbeitungslogik ist er besonders ressourcenschonend und leicht verständlich. Er eignet sich ideal für Anwendungen, bei denen ein Signal parallel mehreren Empfängern zur Verfügung gestellt werden muss.