# F_SHR

```{index} single: F_SHR
```

<img width="1350" height="208" alt="F_SHR" src="https://github.com/user-attachments/assets/7ff0f80c-c8c6-4472-85d8-32658fa25627" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_SHR` führt eine bitweise Rechtsverschiebung (Shift Right) durch. Er ist Teil der Standard-Bit-Operatoren gemäß IEC 61131-3 und wird für logische und arithmetische Operationen in Steuerungsanwendungen eingesetzt.

![F_SHR](F_SHR.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Rechtsverschiebung. Wird mit den Daten `IN` und `N` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigt die abgeschlossene Rechtsverschiebung. Liefert das Ergebnis `OUT`.

### **Daten-Eingänge**
- `IN` (`ANY_BIT`): Der Eingabewert, der rechtsverschoben werden soll.
- `N` (`ANY_INT`): Die Anzahl der Bits, um die verschoben werden soll.

### **Daten-Ausgänge**
- `OUT` (`ANY_BIT`): Das Ergebnis der Rechtsverschiebung. Die freiwerdenden Bits links werden mit Nullen aufgefüllt.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. Bei einem `REQ`-Ereignis wird der Wert `IN` um `N` Bits nach rechts verschoben.
2. Die freiwerdenden Bits auf der linken Seite werden mit Nullen aufgefüllt (logische Rechtsverschiebung).
3. Das Ergebnis wird über `OUT` ausgegeben und das `CNF`-Ereignis ausgelöst.

## Technische Besonderheiten
- Unterstützt alle Bit-Datentypen (`ANY_BIT`), z. B. `BOOL`, `BYTE`, `WORD`, `DWORD`, `LWORD`.
- `N` kann jeden ganzzahligen Typ (`ANY_INT`) verwenden, z. B. `SINT`, `INT`, `DINT`, `LINT`, `USINT`, `UINT`, `UDINT`, `ULINT`.
- Die Rechtsverschiebung ist unabhängig vom Vorzeichen (logische Verschiebung).

## Zustandsübersicht
- **Idle**: Wartet auf `REQ`.
- **Processing**: Führt die Rechtsverschiebung durch.
- **Completed**: Sendet `CNF` mit dem Ergebnis.

## Anwendungsszenarien
- Bitmanipulation in Steuerungsalgorithmen.
- Datenkompression oder -extraktion.
- Schnelle Division durch Zweierpotenzen (bei vorzeichenlosen Zahlen).

## ⚖️ Vergleich mit ähnlichen Bausteinen
- `F_SHL`: Führt eine Linksverschiebung durch.
- `F_ROR`/`F_ROL`: Rotationsoperationen statt Verschiebungen.
- `F_SHR` ist spezifisch für logische Rechtsverschiebungen (Null-Auffüllung).

## Fazit
Der `F_SHR`-Funktionsblock ist ein effizientes Werkzeug für bitweise Operationen in IEC 61131-3-Umgebungen. Seine einfache Schnittstelle und Standardkonformität machen ihn ideal für Steuerungsanwendungen mit Bitmanipulationen.