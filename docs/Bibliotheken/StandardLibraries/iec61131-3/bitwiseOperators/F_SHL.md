# F_SHL

```{index} single: F_SHL
```

<img width="1342" height="208" alt="F_SHL" src="https://github.com/user-attachments/assets/91a9f7fd-3552-4524-91ed-e888afe9acdd" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SHL` führt eine Linksverschiebung (Shift Left) auf einen beliebigen Bit-Datentyp aus. Dabei werden die Bits des Eingabewertes um eine bestimmte Anzahl von Stellen nach links verschoben und die freiwerdenden Stellen rechts mit Nullen aufgefüllt. Dieser Baustein ist gemäß dem Standard IEC 61131-3 klassifiziert und eignet sich für bitweise Operationen.

![F_SHL](F_SHL.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Dienst-Anforderung. Löst die Linksverschiebung aus. Verknüpft mit den Daten-Eingängen `IN` und `N`.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Dienstleistung. Signalisiert die Beendigung der Operation. Verknüpft mit dem Daten-Ausgang `OUT`.

### **Daten-Eingänge**
- **IN**: Der Eingabewert, der linksverschoben werden soll. Der Datentyp ist `ANY_BIT` (beliebiger Bit-Datentyp).
- **N**: Die Anzahl der Stellen, um die verschoben werden soll. Der Datentyp ist `ANY_INT` (beliebiger Integer-Datentyp).

### **Daten-Ausgänge**
- **OUT**: Das Ergebnis der Linksverschiebung. Der Datentyp entspricht dem des Eingabewertes `IN`. Die freiwerdenden Stellen rechts werden mit Nullen aufgefüllt.

### **Adapter**
Es sind keine Adapter definiert.

## Funktionsweise
Der Funktionsblock `F_SHL` führt eine bitweise Linksverschiebung des Eingabewertes `IN` um `N` Stellen durch. Dabei werden die Bits nach links verschoben und die neu entstehenden Stellen auf der rechten Seite mit Nullen aufgefüllt. Die Operation wird durch das Ereignis `REQ` ausgelöst und durch `CNF` bestätigt.

## Technische Besonderheiten
- Unterstützt beliebige Bit-Datentypen (`ANY_BIT`) für den Eingabewert `IN`.
- Die Verschiebungsanzahl `N` kann von jedem Integer-Datentyp (`ANY_INT`) sein.
- Die Operation ist gemäß IEC 61131-3 standardisiert.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das Ereignis `REQ`.
2. **Ausführungszustand**: Führt die Linksverschiebung durch, wenn `REQ` empfangen wird.
3. **Bestätigungszustand**: Sendet `CNF` nach Abschluss der Operation.

## Anwendungsszenarien
- Bitmanipulation in Steuerungsanwendungen.
- Verschiebeoperationen in digitalen Signalverarbeitungsalgorithmen.
- Generelle bitweise Operationen in IEC 61131-3-konformen Steuerungssystemen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **F_SHR**: Führt eine Rechtsverschiebung durch, im Gegensatz zur Linksverschiebung von `F_SHL`.
- **F_ROL** und **F_ROR**: Rotieren Bits statt sie zu verschieben, wobei überlaufende Bits auf der anderen Seite wieder eingefügt werden.




## 🛠️ Zugehörige Übungen

* [Uebung_034](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_034.md)

## Fazit
Der `F_SHL`-Funktionsblock ist ein effizientes Werkzeug für bitweise Linksverschiebungen in Steuerungssystemen. Seine Flexibilität bei der Unterstützung verschiedener Bit- und Integer-Datentypen macht ihn vielseitig einsetzbar. Die klare Ereignissteuerung und Standardkonformität nach IEC 61131-3 gewährleisten eine zuverlässige Integration in bestehende Systeme.