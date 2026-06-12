# AUDI_AX_SEL_AUDI


![AUDI_AX_SEL_AUDI](./AUDI_AX_SEL_AUDI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUDI_AX_SEL_AUDI** realisiert eine binäre Auswahl (binary selection) zwischen zwei Eingabewerten. Er fungiert als Multiplexer, der abhängig von einem Selektorsignal einen der beiden Eingänge an den Ausgang durchschaltet. Die Kommunikation erfolgt ausschließlich über unidirektionale Adapter, die sowohl Ereignis- als auch Datensignale kapseln. Dadurch wird eine flexible und typengebundene Einbindung in existierende Signalpfade ermöglicht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der FB besitzt keine dedizierten Ereignis-Eingänge. Ereignisse werden jedoch über den **Selektor-Adapter G** bereitgestellt:
- **G.E1**: Ereignissignal, das die Auswahl logik auslöst.

### **Ereignis-Ausgänge**
Der FB besitzt keine dedizierten Ereignis-Ausgänge. Ereignisse werden jedoch über den **Ausgangs-Adapter OUT** ausgegeben:
- **OUT.E1**: Quittierungssignal, das nach erfolgreicher Durchschaltung des gewählten Eingangs ausgelöst wird.

### **Daten-Eingänge**
Der FB besitzt keine dedizierten Daten-Eingänge. Datenwerte werden über die folgenden Adapter bereitgestellt:
- **IN0.D1** (Typ: AUDI) – erster auswählbarer Datenwert
- **IN1.D1** (Typ: AUDI) – zweiter auswählbarer Datenwert
- **G.D1** (Typ: AX) – Selektorfeld zur Bestimmung der aktiven Quelle

### **Daten-Ausgänge**
Der FB besitzt keine dedizierten Daten-Ausgänge. Der ausgewählte Datenwert wird über den **Ausgangs-Adapter OUT** ausgegeben:
- **OUT.D1** (Typ: AUDI) – ausgewählter Datenwert (entspricht IN0.D1 oder IN1.D1)

### **Adapter**
| Adapter | Richtung | Typ | Kommentar |
|---------|----------|-----|-----------|
| **IN0** | Socket (Eingang) | `adapter::types::unidirectional::AUDI` | Erster auswählbarer Eingang |
| **IN1** | Socket (Eingang) | `adapter::types::unidirectional::AUDI` | Zweiter auswählbarer Eingang |
| **G**   | Socket (Eingang) | `adapter::types::unidirectional::AX`   | Selektor (Ereignis + Daten) |
| **OUT** | Plug (Ausgang)  | `adapter::types::unidirectional::AUDI` | Ausgangsfeld mit Ereignis und Daten |

## Funktionsweise
Der Baustein enthält intern eine Instanz des IEC‑61131‑Funktionsbausteins `F_SEL` (aus der Bibliothek `iec61131::selection`). Die Logik läuft wie folgt ab:

1. **Triggerung**: Ein Ereignis am **G.E1** (über den Selektordapter) startet die Verarbeitung.
2. **Datensammlung**: Die anliegenden Werte von **IN0.D1**, **IN1.D1** und **G.D1** werden an den `F_SEL`-Baustein weitergeleitet.
3. **Auswahl**: `F_SEL` prüft den Wert von **G.D1**. Typische Semantik (abhängig vom Datentyp `AX`):  
   - Ist der Selektorfeld **False** (oder 0), wird **IN0** ausgewählt.  
   - Ist das Selektorfeld **True** (oder ungleich 0), wird **IN1** ausgewählt.
4. **Ausgabe**: Das ausgewählte Signal wird an **OUT.D1** weitergegeben. Gleichzeitig wird ein Ereignis an **OUT.E1** gesendet, um die nachgeschaltete Verarbeitung zu informieren.

Der interne Ablauf ist ereignisgesteuert und vermeidet kontinuierliche Lesezugriffe, was eine effiziente Kommunikation in zeitgesteuerten Umgebungen ermöglicht.

## Technische Besonderheiten
- **Reine Adapter-Kommunikation**: Alle Schnittstellen sind als unidirektionale Adapter definiert. Ereignis- und Datenpfade sind innerhalb eines Adapters zusammengefasst, was die Konfiguration in der 4diac‑IDE vereinfacht.
- **Wiederverwendung von IEC‑61131‑Bibliotheken**: Die Auswahllogik wird vollständig durch den Standard-Baustein `F_SEL` realisiert, der keine zusätzliche Zustandsautomaten oder komplexe Algorithmen erfordert.
- **Typensicherheit**: Die Adapter sind auf die benutzerdefinierten Typen `AUDI` und `AX` spezialisiert. Dadurch wird eine Fehlkopplung mit inkompatiblen Signalen bereits zur Entwurfszeit verhindert.
- **Kein eigener Zustand**: Der Baustein selbst ist zustandslos – er leitet lediglich die Signale an den internen `F_SEL` weiter. Der interne FB verwaltet die Auswahl logik autonom.

## Zustandsübersicht
Der FB **AUDI_AX_SEL_AUDI** besitzt **keinen eigenen Zustandsautomaten**. Die gesamte auswahl logik wird von dem inneren `F_SEL`-Baustein ausgeführt, der seinerseits einen reinen Funktionsblock ohne Zustandspeicher darstellt. Das Verhalten ist therefore **zustandslos**:

- Nach dem Empfang eines Ereignisses an **G.E1** wird die Auswahl sofort getroffen und das Ergebnis in **OUT.D1** ausgegeben.
- Es existieren keine Initialisierungs-, Warte- oder Fehlerzustände; der Baustein ist jederzeit bereit für eine neue Selektoranforderung.

## Anwendungsszenarien
Der Baustein eignet sich ideal für folgende Einsatzfälle in der Automatisierungstechnik:

- **Signalumschaltung** zwischen zwei Sensoren (z. B. Temperaturfühler, Druckaufnehmer) abhängig von einer Betriebsart oder einem manuellen Schalter.
- **Bypass-Selektion** in Steuerungspfaden: bei Störung eines Kanals wird automatisch auf einen Ersatzkanal umgeschaltet.
- **Parameterauswahl**: zwischen zwei festen Parametersätzen (z. B. für unterschiedliche Produkte) wird anhand eines Selektorfeldes gewählt.
- **Testmodus**: Umschaltung zwischen einem realen und einem simulierten Signal für Inbetriebnahme oder Wartung.

Die Verwendung benutzerdefinierter Adaptertypen (`AUDI`, `AX`) erlaubt eine einfache Anpassung an projektspezifische Datenstrukturen.

## Vergleich mit ähnlichen Bausteinen
| Kriterium | **AUDI_AX_SEL_AUDI** | Einfacher Bool-MUX (z. B. `F_SEL`) |
|-----------|------------------------|---------------------------------------|
| **Schnittstelle** | Reine Adapter (Ereignis+Daten gekapselt) | Getrennte Ein-/Ausgangspins |
| **Datentyp** | Benutzerdefinierte Typen (`AUDI`, `AX`) | Beliebig (parametrierbar) |
| **Selektor** | Ereignisgesteuert (über Adapter) | Datenbasiert, ohne extra Ereignis |
| **Wiederverwendbarkeit** | Höher durch Typensicherheit und Kapselung | Flexibler, aber lose Kopplung |
| **Komplexität** | Mittel (Adapter erfordern Vorwissen) | Niedrig (direkte Pins) |

Der **AUDI_AX_SEL_AUDI** bietet eine höhere Integration in adapterbasierte Architekturen und eignet sich besonders für modulare, typengebundene Systeme, während ein reiner `F_SEL` universeller ist.

## Fazit
Der **AUDI_AX_SEL_AUDI** ist ein spezialisierter binärer Selektor, der die Vorteile der adapterbasierten Kommunikation in 4diac nutzt. Durch die Kapselung von Ereignis- und Datenpfaden in einem Adapter wird die Signalverdrahtung im Gesamtsystem reduziert und die Typsicherheit erhöht. Die interne Delegation an den bewährten `F_SEL`-Baustein der IEC‑61131‑Bibliothek gewährleistet eine robuste, zustandslose Auswahl logik. Der Baustein eignet sich hervorragend für den Einsatz in modularen Steuerungsprojekten, bei denen klare Schnittstellen und einfache Wiederverwendbarkeit im Vordergrund stehen.