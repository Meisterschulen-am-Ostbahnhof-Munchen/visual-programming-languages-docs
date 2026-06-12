# AR2_REAL_TO_X


![AR2_REAL_TO_X](./AR2_REAL_TO_X.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `AR2_REAL_TO_X` ist ein zusammengesetzter Baustein (Composite FB) zur Konvertierung eines REAL-Wertes in ein AR2-Format. Er kapselt einen bidirektionalen Adapter des Typs `adapter::types::bidirectional::AR2` und fungiert als transparente Schnittstelle zwischen einer einfachen REAL-Variable und dem komplexeren AR2-Datentyp. Die Konvertierungslogik liegt vollständig im verwendeten Adapter, während der FB lediglich die Signal- und Datenweiterleitung übernimmt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar |
|----------|-----------|
| `REQ`    | Anforderung zur Verarbeitung über den Adapter (löst Adapterausgang aus) |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar |
|----------|-----------|
| `CNF`    | Bestätigung nach Abschluss der Adapterverarbeitung |

### **Daten-Eingänge**

| Variable | Typ  | Kommentar |
|----------|------|-----------|
| `OUT`    | REAL | Ausgangsdaten, die an den Adapter gesendet werden (tatsächlich: Eingangswert für die Konvertierung) |

### **Daten-Ausgänge**

| Variable | Typ  | Kommentar                                    |
|----------|------|----------------------------------------------|
| `IN`     | REAL | Vom Adapter zurückgegebene Eingangsdaten (tatsächlich: konvertierter Wert) |

### **Adapter**

| Adapter | Typ                                     | Kommentar             |
|---------|-----------------------------------------|-----------------------|
| `AR2_OUT` | `adapter::types::bidirectional::AR2`     | Bidirektionaler Schnittstellenadapter für AR2-Konvertierung |

## Funktionsweise

Der FB arbeitet als reiner Weiterleitungsbaustein:

1. Ein eingehendes Ereignis am **Ereignis-Eingang `REQ`** wird direkt an den Ereignisausgang `EO1` des Adapters `AR2_OUT` weitergeleitet.
2. Der aktuelle Wert des **Daten-Eingangs `OUT`** wird gleichzeitig an den Datenausgang `DO1` des Adapters gesendet.
3. Der Adapter führt intern die Konvertierung vom REAL- in das AR2-Format durch (und ggf. zurück) und sendet ein Bestätigungs-Ereignis über seinen Ereigniseingang `EI1` zurück.
4. Dieses Ereignis wird an den **Ereignis-Ausgang `CNF`** des FBs weitergegeben.
5. Der vom Adapter bereitgestellte Wert an dessen Dateneingang `DI1` wird auf den **Daten-Ausgang `IN`** des FBs übertragen.

Die tatsächliche Umrechnung (REAL ↔ AR2) erfolgt ausschließlich im Adapter – der FB selbst führt keine arithmetischen Operationen durch.

## Technische Besonderheiten

- **Zusammengesetzter Baustein**: Die Funktionalität wird durch die innere Verschaltung eines externen Adaptertyps realisiert. Der FB ist daher abhängig von der Implementierung des Adapters `adapter::types::bidirectional::AR2`.
- **Bidirektionale Datenrichtung**: Die Namensgebung der Variablen (`OUT` als Eingang, `IN` als Ausgang) kann verwirren. Tatsächlich fließen die Daten wie folgt:  
  - REAL-Wert → Adapter → AR2-Objekt (Hinrichtung)  
  - AR2-Objekt → Adapter → REAL-Wert (Rückrichtung)  
  Der FB stellt beide Richtungen über die Ereignissteuerung `REQ` / `CNF` bereit.
- **Keine Zustandslogik**: Der FB besitzt keinen eigenen Zustandsautomaten – alle Abläufe sind ereignisgesteuert und direkt.

## Zustandsübersicht

Da der FB keine interne Zustandsmaschine besitzt, liegt keine klassische Zustandsübersicht vor. Der Ablauf ist rein sequenziell pro Ereignis:

1. Warten auf `REQ`  
2. Senden an Adapter  
3. Warten auf Adapter-Rückmeldung  
4. Ausgabe von `CNF` und aktualisiertem `IN`

## Anwendungsszenarien

- **Schnittstelle zu externen Systemen**: Wenn ein externes Gerät oder ein anderer Funktionsblock Daten im AR2-Format erwartet, der Anwendercode jedoch mit REAL-Werten arbeitet.
- **Datenvorverarbeitung**: Einbindung in eine Kette von Konvertierungsbausteinen, um REAL-Daten in ein spezifisches binäres oder strukturiertes Format (AR2) zu überführen.
- **Test und Simulation**: Einsatz in Testumgebungen, um Adapterfunktionalität ohne tiefere Einblicke in den Adapter zu prüfen.

## Vergleich mit ähnlichen Bausteinen

- **AR2_REAL_TO_X vs. einfache Typkonvertierung (REAL_TO_INT etc.)**:  
  Einfache Konverter arbeiten direkt auf elementaren Datentypen. `AR2_REAL_TO_X` hingegen verwendet einen Adapter, der eine komplexe Umwandlung (z. B. in ein Array oder eine Struktur) kapselt.
- **AR2_REAL_TO_X vs. direkte Adapter-Nutzung**:  
  Der FB vereinfacht die Handhabung, indem er die Signalverdrahtung (Ereignis- und Datenverbindungen) vornimmt. Der Anwender muss nur noch den FB instanziieren und mit seinem Code verbinden.
- **AR2_REAL_TO_X vs. CONVERT-Adapter-Bausteine**:  
  Ähnliche Bausteine (z. B. aus der IEC 61499-Bibliothek) bieten meist generische Konvertierung. Dieser FB ist spezifisch für die Kopplung von REAL und AR2.

## Fazit

Der Funktionsblock `AR2_REAL_TO_X` bietet eine einfache, ereignisgesteuerte Schnittstelle zur Nutzung eines bidirektionalen AR2-Adapters. Er ist ideal für alle Anwendungen, die eine Konvertierung zwischen dem Standard-Datentyp REAL und einem projektspezifischen AR2-Format benötigen. Durch seine Zusammensetzung bleibt die Komplexität im Adapter verborgen, und der Baustein kann wie ein normaler FB in Anwendungen integriert werden.