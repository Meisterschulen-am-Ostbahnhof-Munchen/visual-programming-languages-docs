# AL_FIELDBUS_LWORD_TO_SIGNAL


![AL_FIELDBUS_LWORD_TO_SIGNAL](./AL_FIELDBUS_LWORD_TO_SIGNAL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AL_FIELDBUS_LWORD_TO_SIGNAL` dient der filternden Weitergabe eines Feldbus-Signals vom Typ `LWORD`. Er gibt den am Eingang anliegenden Wert nur dann an den Ausgang weiter, wenn das zugehörige Gültigkeitssignal (Valid) gesetzt ist. Gleichzeitig wird der Gültigkeitsstatus über einen separaten Ausgang bereitgestellt und durch einen internen Flipflop stabilisiert. Der Baustein ist als Composite-FB realisiert und kapselt die Logik zur Signalverarbeitung sowie die Zustandshaltung des Valid-Signals.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **`IN.E1`** (über Socket `IN`): Ereignis zum Anfordern der Signalverarbeitung. Ein eingehendes Ereignis startet die Spiegelung des Eingangswerts auf den Ausgang und aktualisiert den Gültigkeitsstatus.

### **Ereignis-Ausgänge**
- **`OUT.E1`** (über Plug `OUT`): Ereignis, das nach erfolgreicher Verarbeitung ausgegeben wird. Signalisiert, dass der aktuelle Ausgangswert (`OUT.D1`) gültig ist.
- **`VALID.E1`** (über Plug `VALID`): Ereignis, das zeitgleich mit `OUT.E1` ausgegeben wird. Bestätigt die Aktualisierung des Gültigkeitssignals (`VALID.D1`).

### **Daten-Eingänge**
- **`IN.D1`** (über Socket `IN`, Typ: `LWORD`): Das zu verarbeitende Feldbus-Signal. Der Wert wird unverändert an den Ausgang weitergegeben, sofern das interne Gültigkeitssignal aktiv ist.

### **Daten-Ausgänge**
- **`OUT.D1`** (über Plug `OUT`, Typ: `LWORD`): Das gefilterte Ausgangssignal. Enthält den Wert von `IN.D1`, wenn das Signal gültig ist, andernfalls bleibt der letzte gültige Wert erhalten (durch das interne Verhalten des verwendeten Bausteins `FIELDBUS_LWORD_TO_SIGNAL`).
- **`VALID.D1`** (über Plug `VALID`, Typ: `BOOL`): Zeigt an, ob das aktuell ausgegebene Signal gültig ist. Der Wert wird durch ein internes Flipflop (E_D_FF) zwischengespeichert und bei jedem Verarbeitungszyklus aktualisiert.

### **Adapter**
| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| `IN` | Socket | `adapter::types::unidirectional::AL` | Empfängt das Ereignis- und Datensignal von einem vorgeschalteten Baustein. |
| `OUT` | Plug | `adapter::types::unidirectional::AL` | Sendet das gefilterte Signal und zugehöriges Ereignis an nachfolgende Bausteine. |
| `VALID` | Plug | `adapter::types::unidirectional::AX` | Sendet den Gültigkeitsstatus als booleschen Wert und ein Bestätigungsereignis. |

## Funktionsweise

Der Baustein arbeitet als Composite-FB mit folgender interner Logik:

1. Ein eingehendes Ereignis an `IN.E1` triggert den internen FB `FIELDBUS_LWORD_TO_SIGNAL` über dessen `REQ`-Eingang.
2. Dieses interne FB spiegelt den Wert von `IN.D1` auf seinen `OUT`-Ausgang und erzeugt gleichzeitig ein boolesches `VALID`-Signal, das angibt, ob der Wert gültig ist.
3. Das `CNF`-Ereignis des internen FB wird auf drei Ziele verteilt:
   - Es triggert den Ausgangsplug `OUT.E1`, sodass der gefilterte Wert (`OUT.D1`) an die nächste Verarbeitungsstufe weitergegeben wird.
   - Es triggert den `CLK`-Eingang des Flipflops `E_D_FF`.
4. Das `VALID`-Signal des internen FB wird an den `D`-Eingang des Flipflops gelegt. Bei jeder positiven Flanke des Takts (ausgelöst durch `CNF`) übernimmt das Flipflop diesen Wert und gibt ihn an `Q` aus.
5. Der Ausgang `Q` des Flipflops wird auf `VALID.D1` gelegt und das gleichzeitige Ereignis `VALID.E1` wird durch das Flipflop-Ereignis `EO` ausgelöst.

Dadurch wird sichergestellt, dass der Gültigkeitsstatus erst dann an den Valid-Ausgang weitergegeben wird, wenn die Signalverarbeitung abgeschlossen ist. Der ausgegebene Wert `OUT.D1` entspricht dem Eingangswert `IN.D1`, sofern dieser als gültig erkannt wurde; andernfalls wird der letzte gültige Wert beibehalten (abhängig von der Implementierung des internen FB `FIELDBUS_LWORD_TO_SIGNAL`).

## Technische Besonderheiten

- **Composite-Architektur:** Die Funktionalität wird durch ein internes Netzwerk aus einem spezialisierten FB (`FIELDBUS_LWORD_TO_SIGNAL`) und einem flankengetriggerten Flipflop (E_D_FF) realisiert. Dies ermöglicht eine modulare und testbare Implementierung.
- **Zustandshaltung:** Der Gültigkeitsstatus wird über ein Flipflop gespeichert. Dadurch bleibt der Valid-Ausgang stabil zwischen zwei Verarbeitungszyklen und wird nur bei neuen Ereignissen aktualisiert.
- **Unidirektionale Adapter:** Alle Schnittstellen sind als unidirektionale Adapter (AL bzw. AX) ausgeführt, was eine klare Trennung von Ereignis- und Datenfluss ermöglicht.
- **Lizenzierung:** Der Baustein ist unter der Eclipse Public License 2.0 verfügbar (Copyright HR Agrartechnik GmbH).

## Zustandsübersicht

Der Baustein besitzt keinen expliziten ECC, da es sich um einen Composite-FB handelt. Die innere Zustandslogik beschränkt sich auf das Flipflop `E_D_FF`, das zwei Zustände kennt:

| Zustand | Q (VALID.D1) | Bedeutung |
|---------|--------------|-----------|
| RESET (Anfang) | FALSE | Signal ist ungültig (initial). |
| SET | TRUE | Signal ist gültig, nachdem ein gültiger Wert erkannt wurde. |

Der Zustandswechsel erfolgt bei jedem eingehenden Ereignis an `CLK` (von `CNF`) in Abhängigkeit des `D`-Eingangs (vom internen `VALID`-Signal). Der Zustand bleibt solange erhalten, bis das nächste Ereignis eintrifft.

## Anwendungsszenarien

- **Feldbus-Signalverarbeitung:** Übernahme von LWORD-Signalen (z.B. aus einem CANopen- oder Profibus-Netzwerk) und deren Weitergabe nur bei gültigem Status.
- **Filterung ungültiger Werte:** Wenn ein Sensor zeitweise ungültige Messwerte liefert, gibt der Baustein den letzten gültigen Wert weiter und signalisiert die Ungültigkeit über `VALID.D1`.
- **Synchronisation mehrerer Pfade:** Durch die getrennten Ausgänge für Signal und Valid können nachgelagerte Bausteine beide Informationen gleichzeitig verarbeiten.

## Vergleich mit ähnlichen Bausteinen

Einfachere Bausteine wie `MOVE` oder `REPEAT` geben eingehende Werte ungefiltert weiter, ohne eine Gültigkeitsprüfung. Der `AL_FIELDBUS_LWORD_TO_SIGNAL` erweitert diese Funktionalität um eine Validierungslogik und einen gesonderten Gültigkeitsausgang. Andere Bausteine aus der `logiBUS`-Bibliothek könnten ähnliche Aufgaben für andere Datentypen (z.B. `WORD` oder `BOOL`) bieten, sind aber nicht auf `LWORD` spezialisiert.

## Fazit

Der Funktionsblock `AL_FIELDBUS_LWORD_TO_SIGNAL` ist ein spezialisierter Composite-Baustein zur zuverlässigen Weitergabe von Feldbus-Signalen unter Berücksichtigung eines Gültigkeitskriteriums. Durch die Kombination aus Signalverarbeitung und Zustandshaltung eignet er sich ideal für sicherheitskritische oder qualitätsbewusste Anwendungen in der Automatisierungstechnik. Die klar definierten Adapter-Schnittstellen erleichtern die Integration in bestehende 4diac-IDE Projekte.