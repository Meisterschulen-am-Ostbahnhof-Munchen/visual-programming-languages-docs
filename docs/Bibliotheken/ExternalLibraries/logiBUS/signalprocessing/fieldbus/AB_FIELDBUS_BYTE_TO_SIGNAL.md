# AB_FIELDBUS_BYTE_TO_SIGNAL


![AB_FIELDBUS_BYTE_TO_SIGNAL](./AB_FIELDBUS_BYTE_TO_SIGNAL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AB_FIELDBUS_BYTE_TO_SIGNAL** dient dazu, ein eingehendes Byte-Signal (über den Adapter *IN*) auf den Ausgang (*OUT*) zu spiegeln, sofern das Signal als gültig erkannt wird. Die Gültigkeit wird über einen separaten Ausgang (*VALID*) signalisiert. Der Baustein kapselt die Verarbeitung eines Feldbus-Byte-Signals und stellt sicher, dass nur valide Daten an die nachfolgende Logik weitergegeben werden. Er basiert auf einem internen `FIELDBUS_BYTE_TO_SIGNAL`-Baustein, ergänzt durch ein D-Flipflop zur stabilen Ausgabe des Gültigkeitssignals.

## Schnittstellenstruktur
Der FB besitzt **keine** direkten Ereignis- oder Daten-Ein-/Ausgänge auf der obersten Ebene. Die gesamte Kommunikation erfolgt über drei **Adapter-Schnittstellen**:

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| `IN` | Socket | `adapter::types::unidirectional::AB` | Eingangsadapter für das Byte-Signal und das zugehörige Ereignis. |
| `OUT` | Plug | `adapter::types::unidirectional::AB` | Ausgangsadapter für das gespiegelte Byte-Signal. |
| `VALID` | Plug | `adapter::types::unidirectional::AX` | Ausgangsadapter, der den Gültigkeitszustand des Signals anzeigt. |

Die Adapter sind vom Typ **unidirectional**, d.h. sie übertragen Daten und Ereignisse in eine Richtung. Die Typen `AB` und `AX` enthalten jeweils einen Ereignis-Eingang/-Ausgang (E1) und einen Daten-Eingang/-Ausgang (D1, vom Typ `ANY` bzw. `BOOL`).

### **Ereignis-Eingänge**
Keine (die Ereignisse werden über den Socket-Adapter `IN` empfangen).

### **Ereignis-Ausgänge**
Keine (die Ereignisse werden über die Plug-Adapter `OUT` und `VALID` gesendet).

### **Daten-Eingänge**
Keine (die Daten werden über den Socket-Adapter `IN` empfangen).

### **Daten-Ausgänge**
Keine (die Daten werden über die Plug-Adapter `OUT` und `VALID` gesendet).

### **Adapter**

**IN (Socket)**
- **E1**: Ereigniseingang – löst die Verarbeitung eines neuen Byte-Wertes aus.
- **D1**: Dateneingang – das zu verarbeitende Byte (z.B. ein Feldbus-Datagramm).

**OUT (Plug)**
- **E1**: Ereignisausgang – wird nach erfolgreicher Spiegelung eines gültigen Signals aktiviert.
- **D1**: Datenausgang – das gespiegelte Byte-Signal (nur bei gültigem Wert).

**VALID (Plug)**
- **E1**: Ereignisausgang – wird bei jedem Verarbeitungsdurchlauf aktiviert, unabhängig von der Gültigkeit.
- **D1**: Datenausgang (BOOL) – `TRUE`, wenn das aktuell verarbeitete Signal gültig ist; sonst `FALSE`.

## Funktionsweise
1. Ein eingehendes Ereignis am Adapter `IN.E1` triggert den internen Baustein `FIELDBUS_BYTE_TO_SIGNAL`, der das Byte an `IN.D1` verarbeitet.
2. Der interne Baustein gibt an seinen Ausgängen `OUT` (das gespiegelte Byte) und `VALID` (die Gültigkeitsinformation) weiter.
3. Das Ausgangssignal wird sofort an den Adapter `OUT` weitergeleitet und ein Ereignis (`OUT.E1`) ausgelöst.
4. Gleichzeitig wird das Gültigkeitssignal des internen Bausteins an den D-Eingang des D-Flipflops (`E_D_FF`) gelegt. Das gleiche Ereignis (`CNF` des internen Bausteins) taktet das Flipflop.
5. Das Flipflop speichert den Gültigkeitswert und gibt ihn stabil an `VALID.D1` aus. Ein Ereignis wird an `VALID.E1` gesendet.

Somit wird das Byte immer dann an `OUT` weitergegeben, wenn es gültig ist. Der Gültigkeitszustand bleibt bis zum nächsten Verarbeitungsdurchlauf erhalten.

## Technische Besonderheiten
- **Adapter-basierte Kommunikation**: Der FB nutzt ausschließlich Adapter-Schnittstellen, was eine modulare und typisierte Verbindung in der 4diac-IDE ermöglicht.
- **D-Flipflop zur Entprellung**: Das Gültigkeitssignal wird durch ein Flipflop getaktet, um Stabilität zu gewährleisten und Hutschiene-Effekte zu vermeiden.
- **Lizenz**: Der Baustein ist unter der **Eclipse Public License 2.0** veröffentlicht (Copyright HR Agrartechnik GmbH).
- **Compiler-Package**: `logiBUS::signalprocessing::fieldbus` – spezifisch für Feldbus-Anwendungen.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten auf der obersten Ebene; die Zustände ergeben sich aus dem Zusammenwirken der internen Komponenten:

| Zustand | Beschreibung |
|---------|--------------|
| **Idle** | Warten auf ein Ereignis an `IN.E1`. |
| **Processing** | Interner `FIELDBUS_BYTE_TO_SIGNAL` verarbeitet das Byte; `OUT` und `VALID` werden aktualisiert. |
| **Valid stable** | Nachdem das Flipflop getaktet wurde, bleibt `VALID.D1` bis zum nächsten Ereignis stabil. |

In jedem Zyklus wird der Zustand durchlaufen.

## Anwendungsszenarien
- **Feldbus-Integration**: Empfang eines Byte-Wertes von einem Feldbus (z.B. CAN, Profibus) und dessen Weitergabe an eine Steuerungslogik, wobei nur gültige Telegramme durchgereicht werden.
- **Signalaufbereitung**: Umwandlung eines rohen Byte-Streams in ein getaktetes, gültigkeitsgeprüftes Signal für nachgeschaltete Funktionsblöcke.
- **Fehlererkennung**: Der Baustein kann mit einem externen Gültigkeitsprüfer kombiniert werden, der am `IN`-Adapter anliegt.

## Vergleich mit ähnlichen Bausteinen
Einfachere **Mirror**-Bausteine leiten ein Signal ohne Gültigkeitsprüfung weiter. Dieser FB fügt eine explizite Validierung hinzu und gibt das Gültigkeitssignal separat aus. Im Gegensatz zu einem reinen Flipflop-basierten Haltebaustein verarbeitet er hier ein Byte und nicht nur boolesche Werte. Der interne `FIELDBUS_BYTE_TO_SIGNAL` übernimmt die spezifische Feldbus-Interpretation.

## Fazit
Der `AB_FIELDBUS_BYTE_TO_SIGNAL` ist ein spezialisierter Baustein für die sichere Weitergabe von Feldbus-Byte-Signalen. Durch die Kombination aus Spiegelung und Gültigkeitsprüfung eignet er sich ideal für Echtzeit-Anwendungen, bei denen nur valide Daten weiterverarbeitet werden dürfen. Die Adapter-basierte Schnittstelle erlaubt eine einfache Integration in bestehende 4diac-Projekte.