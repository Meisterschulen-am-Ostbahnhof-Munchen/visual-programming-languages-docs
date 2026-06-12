# AQ


![AQ](./AQ.svg)

* * * * * * * * * *
## Einleitung
Der Adapter `AQ` stellt eine unidirektionale Schnittstelle (Plug-Seite) für die Übertragung eines Ereignisses und eines Byte-Wertes (genutzt für 2 Bit) bereit. Er dient als Standarddefinition für die Kommunikation zwischen Funktionsbausteinen nach IEC 61499-1 und ermöglicht eine einfache, gerichtete Datenübergabe.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| E1 | Event | Indication (or Request) Event from Plug (wird zusammen mit D1 ausgelöst) |

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| D1 | BYTE | Indication (or Request) Data from Plug (2 Bit genutzt) |

### **Adapter**
Keine.

## Funktionsweise
Der Adapter `AQ` definiert eine unidirektionale Verbindung. Ein angeschlossener Funktionsbaustein kann über das Ereignis `E1` signalisieren, dass der am Datenausgang `D1` anliegende Byte-Wert gültig ist. Der Datenwert ist ein Byte, von dem die unteren 2 Bits die eigentliche Information tragen. Die restlichen 6 Bits sind für die Anwendung nicht definiert. Der Adapter selbst besitzt keine Verarbeitungslogik – er stellt ausschließlich die Schnittstellenspezifikation dar.

## Technische Besonderheiten
- **Unidirektional**: Nur Ereignis- und Datenausgänge vorhanden, keine Eingänge. Geeignet für Plug-Seiten in Adapter-Paarungen.
- **Datennutzung**: Von den 8 Bit des Byte-Wertes werden nur die unteren 2 Bit als signifikant angesehen. Die übrigen Bits sollten durch den sendenden FB auf `0` gesetzt oder ignoriert werden.
- **Event + Data**: Das Ereignis `E1` ist mit dem Datenausgang `D1` verknüpft (`With`-Relation). Beide werden gemeinsam ausgesendet.
- **Kompakt**: Minimale Schnittstelle mit einem Ereignis und einem Byte.

## Zustandsübersicht
Der Adapter selbst besitzt keinen internen Zustand. Der sendende Funktionsbaustein steuert die Ausgaben basierend auf seiner eigenen Zustandsmaschine. Der Adapter definiert lediglich das Protokoll: Ereignis und Daten werden gemeinsam übertragen.

## Anwendungsszenarien
- Übertragung von 2‑Bit‑Statusinformationen (z. B. Betriebszustand “Ein/Aus/Störung” oder zwei separate Flags).
- Einfache Befehlsübermittlung mit kodiertem Byte (z. B. 2‑Bit‑Steuerworte in Automatisierungssystemen).
- Als Teil einer übergeordneten Adapter-Paarung für minimale, gerichtete Kommunikation zwischen FBs.

## Vergleich mit ähnlichen Bausteinen
| Merkmal | AQ (dieser Adapter) | Andere Adapter (z. B. mit mehreren Events) |
|---------|---------------------|--------------------------------------------|
| Ereignisse | 1 Ausgang | Oft mehrere Ein-/Ausgänge |
| Daten | 1 Byte (2 Bit genutzt) | Häufig mehrere Variablen oder komplexe Typen |
| Ausrichtung | Unidirektional (Plug-Seite) | Bidirektional oder reine Socket-Seite |
| Komplexität | Sehr gering | Mittel bis hoch |

Der `AQ` ist speziell für den Minimalfall “Ein Ereignis + ein Byte” optimiert.

## Fazit
Der Adapter `AQ` bietet eine schlanke und standardisierte Schnittstelle für die unidirektionale Übertragung eines Ereignisses und eines 2‑Bit‑Signals. Seine Einfachheit macht ihn ideal für Anwendungen, die eine reduzierte Kommunikation erfordern und gleichzeitig die IEC‑61499‑Kompatibilität wahren. Der Adapter ist als Plug-Seite definiert und erwartet einen entsprechenden Socket-Gegenpart.