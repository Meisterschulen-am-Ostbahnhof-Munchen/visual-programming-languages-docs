# F_DWORD_TO_BYTE

```{index} single: F_DWORD_TO_BYTE
```

<img width="1248" height="184" alt="F_DWORD_TO_BYTE" src="https://github.com/user-attachments/assets/3a6b0a87-3a1e-478f-a160-dfbaca28aa01" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DWORD_TO_BYTE` dient der Konvertierung eines 32-Bit-Wertes (DWORD) in einen 8-Bit-Wert (BYTE). Diese Konvertierung ist nützlich in Szenarien, wo eine Datenreduktion oder Typanpassung erforderlich ist.

![F_DWORD_TO_BYTE](F_DWORD_TO_BYTE.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Beendigung der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `DWORD` (32-Bit), der in ein `BYTE` konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `BYTE` (8-Bit), der das Ergebnis der Konvertierung enthält.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `DWORD` zu `BYTE` durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der Funktion `DWORD_TO_BYTE`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Die Konvertierung kann zu einem Datenverlust führen, wenn der ursprüngliche `DWORD`-Wert außerhalb des darstellbaren Bereichs eines `BYTE` (0-255) liegt.
- Der Funktionsblock ist als einfacher FB (SimpleFB) implementiert und verwendet einen ST-Algorithmus für die Konvertierung.

## Zustandsübersicht
1. **Idle**: Wartet auf das Ereignis `REQ`.
2. **Processing**: Führt die Konvertierung durch.
3. **Completed**: Sendet das Ereignis `CNF` und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Datenreduktion in Steuerungssystemen.
- Typkonvertierung in Kommunikationsprotokollen.
- Anpassung von Daten für spezifische Hardware-Schnittstellen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **F_WORD_TO_BYTE**: Konvertiert einen 16-Bit-Wert (WORD) in ein BYTE.
- **F_DWORD_TO_WORD**: Konvertiert einen 32-Bit-Wert (DWORD) in ein 16-Bit-Wert (WORD).
- **F_BYTE_TO_DWORD**: Führt die umgekehrte Konvertierung durch (BYTE zu DWORD).

## Fazit
Der Funktionsblock `F_DWORD_TO_BYTE` bietet eine einfache und effiziente Möglichkeit, 32-Bit-Werte in 8-Bit-Werte zu konvertieren. Aufgrund des möglichen Datenverlusts bei großen Werten sollte die Verwendung jedoch sorgfältig abgewogen werden.