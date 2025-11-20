# F_ROL

<img width="1340" height="208" alt="F_ROL" src="https://github.com/user-attachments/assets/24e2181b-8b77-46bf-bf08-bc549c06ab07" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ROL` (Rotate Left) führt eine bitweise Linksrotation durch. Er rotiert den Eingabewert um eine angegebene Anzahl von Bits nach links und füllt die freiwerdenden Stellen rechts mit Nullen auf. Dieser Baustein ist gemäß der Norm IEC 61131-3 als Standard-Bitverschiebungsfunktion klassifiziert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Dienstaufforderung, die die Ausführung der Linksrotation auslöst. Wird mit den Daten-Eingängen `IN` und `N` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der durchgeführten Dienstleistung. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingabewert, der rotiert werden soll. Der Datentyp ist `ANY_BIT` (beliebiger Bit-Typ).
- **N**: Die Anzahl der Bits, um die der Eingabewert rotiert werden soll. Der Datentyp ist `ANY_INT` (beliebiger Integer-Typ).

### **Daten-Ausgänge**
- **OUT**: Das Ergebnis der Linksrotation. Der Datentyp ist `ANY_BIT` (derselbe wie der Eingabewert).

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock `F_ROL` führt eine bitweise Linksrotation des Eingabewerts `IN` um `N` Bits durch. Dabei werden die Bits, die links aus dem Wertebereich herausfallen, rechts wieder eingefügt. Die freiwerdenden Stellen werden mit Nullen aufgefüllt.

## Technische Besonderheiten
- Unterstützt beliebige Bit-Typen (`ANY_BIT`) für den Eingabewert `IN` und den Ausgabewert `OUT`.
- Die Anzahl der Rotationen `N` kann beliebige Integer-Werte annehmen (`ANY_INT`).
- Die Operation ist zyklisch, d.h., wenn `N` größer als die Bitlänge von `IN` ist, wird die Rotation modulo der Bitlänge durchgeführt.

## Zustandsübersicht
1. **Initialzustand**: Wartet auf das Ereignis `REQ`.
2. **Ausführungszustand**: Bei Empfang von `REQ` wird die Linksrotation durchgeführt und das Ergebnis über `OUT` ausgegeben. Das Ereignis `CNF` wird ausgelöst.
3. **Rückkehr zum Initialzustand**: Nach Auslösen von `CNF` kehrt der Baustein in den Initialzustand zurück.

## Anwendungsszenarien
- Bitweise Manipulation von Daten in Steuerungsanwendungen.
- Kryptographische Operationen, die bitweise Rotationen erfordern.
- Signalverarbeitung, bei denen Datenbits verschoben werden müssen.

## Vergleich mit ähnlichen Bausteinen
- **F_SHL (Shift Left)**: Verschiebt Bits nach links und füllt mit Nullen auf, führt jedoch keine zyklische Rotation durch.
- **F_ROR (Rotate Right)**: Führt eine Rechtsrotation durch, anstatt einer Linksrotation.

## Fazit
Der Funktionsblock `F_ROL` ist ein effizientes Werkzeug für bitweise Linksrotationen in Steuerungsanwendungen. Seine Flexibilität bei der Unterstützung verschiedener Bit- und Integer-Typen macht ihn vielseitig einsetzbar. Die zyklische Natur der Rotation stellt sicher, dass keine Datenbits verloren gehen, was ihn besonders für Anwendungen mit strengen Datenintegritätsanforderungen geeignet macht.
