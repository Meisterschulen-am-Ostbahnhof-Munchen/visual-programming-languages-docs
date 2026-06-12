# AUI_CTUD


![AUI_CTUD](./AUI_CTUD.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AUI_CTUD** ist ein ereignisgesteuerter Aufwärts-/Abwärtszähler in der Adapter-Version (Adapter Version). Er basiert auf dem Standardbaustein E_CTUD und erweitert diesen um eine „On-Change“-Triggerung für die Ausgangszustände. Über die Adapter-Schnittstellen werden der Zählerwert (CV), der Preset-Wert (PV) sowie die Vergleichsergebnisse (QU, QD) mit anderen Bausteinen ausgetauscht. Der Baustein ist für den Einsatz in IEC 61499‑Anwendungen vorgesehen, bei denen eine lose Kopplung über Adapter gewünscht ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **CU**   | Zähler um 1 erhöhen (Count Up)   |
| **CD**   | Zähler um 1 verringern (Count Down) |
| **R**    | Zähler auf 0 zurücksetzen (Reset)   |
| **LD**   | Zähler mit dem Preset-Wert (PV) laden (Load) |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **CUO**  | Bestätigung für einen erfolgten Count-Up-Vorgang |
| **CDO**  | Bestätigung für einen erfolgten Count-Down-Vorgang |
| **RO**   | Bestätigung für einen erfolgten Reset           |
| **LDO**  | Bestätigung für einen erfolgten Load-Vorgang    |

### **Daten-Eingänge**

Der Baustein besitzt keine direkten Dateneingänge. Der Preset-Wert (PV) wird über einen **Socket-Adapter** bereitgestellt:

| Adapter (Socket) | Typ | Beschreibung |
|------------------|-----|--------------|
| **PV**           | `adapter::types::unidirectional::AUI` | Preset-Wert (Vorwahl) für den Zähler |

### **Daten-Ausgänge**

Der Baustein besitzt keine direkten Datenausgänge. Die Ergebnisse werden über **Plug-Adapter** ausgegeben:

| Adapter (Plug) | Typ | Beschreibung |
|----------------|-----|--------------|
| **QU**         | `adapter::types::unidirectional::AX` | Wahr, wenn der aktuelle Zählerwert ≥ PV ist |
| **QD**         | `adapter::types::unidirectional::AX` | Wahr, wenn der aktuelle Zählerwert ≤ 0 ist |
| **CV**         | `adapter::types::unidirectional::AUI` | Aktueller Zählerwert (Unsigned Integer) |

### **Adapter**

Der Baustein definiert drei Plug-Adapter (QU, QD, CV) und einen Socket-Adapter (PV). Die Adapter sind vom Typ `adapter::types::unidirectional` und ermöglichen eine lose Kopplung zwischen den Bausteinen – die Werte werden über Ereignisse (z. B. `CV.E1`, `QU.E1`) ausgetauscht.

## Funktionsweise

Der Baustein arbeitet als ereignisgesteuerter Zähler mit einer Auflösung von 0 bis 65535 (maximaler Wert für eine unsigned 16‑Bit-Ganzzahl). Die folgende Schrittfolge wird durchlaufen:

1. **Eingangsereignis** (CU, CD, R oder LD) löst eine Transition vom Startzustand in den entsprechenden Verarbeitungszustand aus.
2. **Berechnung**: Im jeweiligen Algorithmus wird der interne Zähler (`CV.D1`) aktualisiert und die Ausgangsadapter QU und QD neu berechnet:
   - **CU**: `CV.D1 := CV.D1 + 1` (nur, wenn der Wert vorher < 65535)
   - **CD**: `CV.D1 := CV.D1 - 1` (nur, wenn der Wert vorher > 0)
   - **R**:  `CV.D1 := 0`
   - **LD**: `CV.D1 := PV.D1`
   - Anschließend werden `QU.D1 := (CV.D1 >= PV.D1)` und `QD.D1 := (CV.D1 <= 0)` gesetzt.
3. **Ausgabe des Zählerwerts**: Nach jeder Wertänderung wird das Ereignis `CV.E1` gesendet, um den neuen Zählerwert über den Adapter zu propagieren.
4. **On-Change-Triggering**:
   - Nach jedem Zählvorgang oder nach einer Änderung des PV (Ereignis von PV-Adapter) wird der Zustand von QU und QD überprüft.
   - Die internen Variablen `QU_OLD` und `QD_OLD` speichern den vorherigen Zustand. Nur wenn sich der Wert geändert hat, wird das entsprechende Adapter-Ereignis (`QU.E1` bzw. `QD.E1`) ausgelöst.
   - Dieses Verhalten verhindert unnötige Ereignisfluten bei gleichbleibenden Schwellwerten.

5. **Verarbeitung von PV-Änderungen**: Ein eingehendes Ereignis auf dem PV‑Adapter (`PV.E1`) führt in den Zustand `UPDATE_PV`, in dem nur die Vergleichsergebnisse neu berechnet werden (ohne den Zähler zu verändern). Danach erfolgt ebenfalls die On-Change-Überprüfung.

## Technische Besonderheiten

- **On-Change Triggering** (Change Detection): Der Baustein sendet Ereignisse auf den Ausgangsadaptern nur dann, wenn sich der logische Zustand im Vergleich zum letzten Durchlauf tatsächlich geändert hat. Dies reduziert die Buslast und vermeidet Endlosschleifen in zyklischen Systemen.
- **Adapterbasierte Kommunikation**: Alle Ein- und Ausgangswerte werden über Adapter (Plug/Socket) ausgetauscht, was eine flexible Verschaltung ohne feste Datenverbindungen ermöglicht. Der Zählerwert (CV) und die Vergleichsergebnisse (QU, QD) werden als Plug-Adapter bereitgestellt, der Preset-Wert (PV) wird als Socket von externen Bausteinen geliefert.
- **Zustandsüberlaufschutz**: Bei Count-Up wird geprüft, ob der aktuelle Wert kleiner als 65535 ist, bei Count-Down, ob er größer 0 ist. Dadurch wird ein Über- oder Unterlauf verhindert.
- **Zwei interne Zustandsvariablen**: `QU_OLD` und `QD_OLD` dienen als Schattenregister für die Change Detection.
- **Erweiterte ECC**: Der Baustein durchläuft nach jedem Zählvorgang eine sequentielle Kette von Zuständen (z. B. CU → CHECK_QU → CHECK_QD → START), um die Change Detection zu gewährleisten.

## Zustandsübersicht

| Zustand        | Beschreibung |
|----------------|--------------|
| **START**      | Warten auf ein Eingangsereignis (CU, CD, R, LD) oder eine PV‑Änderung |
| **CU**         | Zähler erhöhen und neuen Wert über CV‑Adapter ausgeben |
| **CD**         | Zähler verringern und neuen Wert über CV‑Adapter ausgeben |
| **R**          | Zähler auf 0 setzen und neuen Wert über CV‑Adapter ausgeben |
| **LD**         | Zähler mit PV laden und neuen Wert über CV‑Adapter ausgeben |
| **UPDATE_PV**  | Neuberechnung von QU und QD nach PV‑Änderung (ohne Zähleränderung) |
| **CHECK_QU**   | Prüfung, ob sich QU geändert hat (Vergleich mit QU_OLD) |
| **FIRE_QU**    | Wenn QU geändert: QU_OLD aktualisieren und Ereignis auf QU‑Adapter senden |
| **CHECK_QD**   | Prüfung, ob sich QD geändert hat (Vergleich mit QD_OLD) |
| **FIRE_QD**    | Wenn QD geändert: QD_OLD aktualisieren und Ereignis auf QD‑Adapter senden |

Die Zustandsübergänge werden durch die Ereignisse und die Bedingungen `[QU.D1 <> QU_OLD]`, `[QD.D1 <> QD_OLD]` gesteuert. Nach Abschluss der Change Detection kehrt der Baustein in den START‑Zustand zurück.

## Anwendungsszenarien

- **Zähler mit externem Preset**: In einer Anlage kann der Preset-Wert (PV) von einem übergeordneten System oder einem HMI über den PV‑Adapter dynamisch gesetzt werden. Der Baustein zählt daraufhin Ereignisse und meldet das Erreichen oder Unterschreiten der Schwellen über die QU‑ und QD‑Adapter.
- **Richtungsabhängige Zähler**: Durch Verwendung von CU und CD kann ein Vorwärts-/Rückwärtszähler realisiert werden, z. B. für Positionserfassung oder Bestandszählung.
- **Ereignisgesteuerte Grenzwertüberwachung**: Die On-Change-Triggerung von QU und QD eignet sich ideal, um ein diskretes Signal (z. B. „Füllstand erreicht“) nur bei Zustandswechsel zu senden – ähnlich einem Flanken‑Detektor.
- **Modulare Steuerungsarchitektur**: Dank der Adapter-Schnittstelle kann der Baustein ohne feste Datenport‑Verkabelung in eine vorhandene IEC 61499‑Applikation integriert werden. Die logische Verbindung erfolgt allein über die Adapter‑Laufzeitumgebung.

## Vergleich mit ähnlichen Bausteinen

Der Standardbaustein **E_CTUD** (aus der IEC 61499‑Bibliothek) bietet ebenfalls einen Aufwärts-/Abwärtszähler mit Ereignissteuerung, jedoch:

| Merkmal               | **E_CTUD** (Standard)                         | **AUI_CTUD** (Adapter-Version)                  |
|-----------------------|-----------------------------------------------|-------------------------------------------------|
| Schnittstelle         | Feste Event‑ und Daten‑Ports (z. B. CV als BOOL) | Lose Kopplung über Adapter (Plug/Socket)        |
| Ausgabe Zählerwert    | Datenport CV (INT/UDINT)                      | Adapter CV (Typ AUI)                            |
| Grenzwertausgabe      | Bool‑Ports QU, QD                             | Adapter QU, QD (Typ AX)                         |
| Ereignis bei Änderung | Keine Change Detection; QU/QD werden bei jedem Zählvorgang berechnet | On-Change-Triggerung: Ereignis nur bei Zustandswechsel |
| Rückmeldung über Aktionen | Keine eigenen Rücksignal-Ereignisse       | CUO, CDO, RO, LDO als Bestätigungsereignisse    |

Der AUI_CTUD ist daher flexibler in der Verschaltung und reduziert die Ereignislast in verteilten Systemen. Für einfache Anwendungen ohne Adapter kann jedoch der Standard‑E_CTUD ausreichend sein.

## Fazit

Der Funktionsblock **AUI_CTUD** stellt eine moderne, adaptergestützte Variante eines Aufwärts-/Abwärtszählers dar. Besonders hervorzuheben sind die On-Change-Triggerung der Grenzwerte und die Rückmeldung über eigene Ereignisausgänge. Durch die Verwendung von Adapter‑Schnittstellen wird eine lose Kopplung und Wiederverwendbarkeit in unterschiedlichsten Steuerungsprojekten ermöglicht. Die integrierten Schutzmaßnahmen gegen Über‑/Unterlauf sowie die saubere Trennung von Zähl- und Auswerte-Logik machen ihn zu einem robusten Baustein für industrielle Automatisierungsanwendungen.