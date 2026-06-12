# AULI_TO_AUI


![AULI_TO_AUI](./AULI_TO_AUI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AULI_TO_AUI** ist ein zusammengesetzter Baustein (Composite FB), der einen **AULI**-Adapter (basiert auf dem Datentyp `ULINT`) in einen **AUI**-Adapter (basiert auf dem Datentyp `UINT`) umwandelt. Er wird eingesetzt, wenn eine Schnittstelle mit 64‑Bit unsigned Integer (`ULINT`) auf eine 16‑Bit unsigned Integer (`UINT`) Schnittstelle abgebildet werden muss, z. B. bei der Anbindung unterschiedlicher Sensor‑ oder Aktorkomponenten in der Automatisierungstechnik.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Über den Adapter-Socket `AULI_IN` wird ein Ereignis vom Typ `E1` bereitgestellt. Dieses wird intern an den Konvertierungsbaustein weitergeleitet.

### **Ereignis-Ausgänge**
Über den Adapter-Plug `AUI_OUT` wird ein Ereignis vom Typ `E1` ausgegeben, sobald die Konvertierung abgeschlossen ist.

### **Daten-Eingänge**
Über den Adapter-Socket `AULI_IN` wird ein Datenwert vom Typ `D1` (entspricht `ULINT`) entgegengenommen.

### **Daten-Ausgänge**
Über den Adapter-Plug `AUI_OUT` wird ein Datenwert vom Typ `D1` (entspricht `UINT`) ausgegeben.

### **Adapter**
| Name     | Richtung | Typ                        |
|----------|----------|----------------------------|
| AULI_IN  | Socket   | `adapter::types::unidirectional::AULI` |
| AUI_OUT  | Plug     | `adapter::types::unidirectional::AUI`  |

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert:
1. Ein Ereignis am Eingang `AULI_IN.E1` triggert den internen Funktionsblock `F_ULINT_TO_UINT` über dessen Eingang `REQ`.
2. Der Datenwert `AULI_IN.D1` wird direkt als Eingang `IN` an den Konvertierungsbaustein übergeben.
3. Der Konvertierungsbaustein wandelt den `ULINT`-Wert in einen `UINT`-Wert um.
4. Nach Abschluss der Konvertierung signalisiert der Ausgang `CNF` des Konvertierungsbausteins ein Ereignis, welches an den Ausgang `AUI_OUT.E1` weitergeleitet wird.
5. Gleichzeitig wird der konvertierte Wert über den Ausgang `OUT` des Konvertierungsbausteins an den Ausgang `AUI_OUT.D1` übergeben.

Die Umwandlung erfolgt gemäß IEC 61131‑Norm `F_ULINT_TO_UINT`. Bei Werten größer als `65535` (maximaler `UINT`-Wert) kann es zu einem Überlauf kommen, der applikationsseitig zu behandeln ist.

## Technische Besonderheiten
- **Adapterbasierte Kapselung**: Der Baustein erlaubt den nahtlosen Austausch von Adaptern in der 4diac-IDE, ohne die Logik des umgebenden Netzwerks zu ändern.
- **Wiederverwendung der IEC‑Norm‑Konvertierung**: Die eigentliche Typumwandlung wird durch den standardisierten IEC‑Baustein `F_ULINT_TO_UINT` durchgeführt, was Portabilität und Korrektheit sicherstellt.
- **Keine Zustandsspeicherung**: Der Baustein ist rein kombinatorisch – nach jeder Ausführung liegt das aktuelle Ergebnis am Ausgang an.

## Zustandsübersicht
Der Baustein besitzt keinen eigenen endlichen Automaten. Die interne Konvertierung erfolgt ereignisgesteuert und ohne interne Zustände. Die Laufzeit wird allein durch den unterlagerten `F_ULINT_TO_UINT`-Baustein bestimmt.

## Anwendungsszenarien
- **Sensorintegration**: Ein 64‑Bit‑Sensor (z. B. hochauflösende Wegmessung) wird an eine Steuerung angeschlossen, die nur 16‑Bit‑Eingänge akzeptiert.
- **Kommunikations‑Gateway**: Adapter‑Schnittstellen zwischen Bussystemen (z. B. CAN‑open mit 64‑Bit‑Daten auf PROFINET‑I‑Device mit 16‑Bit‑Daten).
- **Datenreduktion**: Gezielte Reduzierung der Auflösung für nachfolgende Verarbeitungsschritte (z. B. Anzeige oder einfache Schwellwertlogik).

## Vergleich mit ähnlichen Bausteinen
| Baustein      | Eingangstyp | Ausgangstyp | Besonderheit |
|---------------|-------------|-------------|--------------|
| `AULI_TO_AUI` | `ULINT`     | `UINT`      | Adapter‑Wrapper, ereignisgesteuert |
| `F_ULINT_TO_UINT` | `ULINT` | `UINT`      | Reine Funktion, kein Adapter |
| `AUI_TO_AULI` | `UINT`      | `ULINT`     | Umgekehrte Richtung (nicht vorhanden) |

Der vorliegende Baustein bietet im Gegensatz zur nackten IEC‑Funktion eine adapterkonforme Ein‑ und Ausgangsschnittstelle und ermöglicht damit die einfache Einbindung in adapterbasierte Architekturen.

## Fazit
Der **AULI_TO_AUI**-Baustein ist eine praktische Lösung, um 64‑Bit‑ULINT‑Daten über einen einheitlichen Adapter‑Mechanismus auf 16‑Bit‑UINT‑Daten abzubilden. Er kombiniert die Robustheit der IEC‑Konvertierungsfunktion mit der Flexibilität von 4diac-Adaptern und eignet sich besonders für heterogene Automatisierungssysteme, in denen unterschiedliche Datentypen aufeinandertreffen.