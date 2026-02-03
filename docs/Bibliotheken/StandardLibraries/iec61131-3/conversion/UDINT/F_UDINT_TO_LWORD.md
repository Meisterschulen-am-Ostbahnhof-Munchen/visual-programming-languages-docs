# F_UDINT_TO_LWORD

```{index} single: F_UDINT_TO_LWORD
```

<img width="1462" height="216" alt="F_UDINT_TO_LWORD" src="https://github.com/user-attachments/assets/b952fbc8-443f-43ff-9840-5f002a169f93" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UDINT_TO_LWORD` dient der Konvertierung eines 32-Bit unsigned integer Wertes (UDINT) in einen 64-Bit unsigned integer Wert (LWORD). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Erweiterung der Bitbreite von Daten erforderlich ist.

![F_UDINT_TO_LWORD](F_UDINT_TO_LWORD.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Eingang für den zu konvertierenden UDINT-Wert.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang für den konvertierten LWORD-Wert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von UDINT zu LWORD durch, indem der eingehende 32-Bit Wert in einen 64-Bit Wert erweitert wird. Die Konvertierung erfolgt bei jedem Auftreten des `REQ`-Ereignisses und wird durch das `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- Der Funktionsblock verwendet die eingebaute Funktion `UDINT_TO_LWORD` zur Konvertierung.
- Es handelt sich um einen einfachen Funktionsblock ohne Zustandsmaschine oder komplexe Logik.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder interne Zustände.

## Anwendungsszenarien
- Erweiterung von Datenbreiten in Steuerungssystemen.
- Kompatibilität mit Systemen, die unterschiedliche Bitbreiten verwenden.
- Datenverarbeitung in industriellen Automatisierungslösungen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Konvertierungsbausteinen wie `F_DINT_TO_LWORD` oder `F_UINT_TO_LWORD` ist dieser speziell für die Konvertierung von UDINT zu LWORD optimiert. Er bietet eine direkte und effiziente Lösung für diese spezifische Konvertierung.

## Fazit
Der `F_UDINT_TO_LWORD` Funktionsblock ist ein einfacher und effizienter Baustein für die Konvertierung von 32-Bit unsigned integer Werten zu 64-Bit unsigned integer Werten. Seine klare Schnittstellenstruktur und einfache Funktionsweise machen ihn zu einer zuverlässigen Komponente in industriellen Automatisierungslösungen.