# SET_STRUCT_VALUE

![SET_STRUCT_VALUE](https://github.com/user-attachments/assets/9fcb0d2f-482b-4368-af7c-d3c7c994d2e7)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SET_STRUCT_VALUE` dient zum Setzen eines Wertes innerhalb einer Struktur. Er ermöglicht den Zugriff auf einzelne Elemente einer Struktur und die Zuweisung eines neuen Wertes zu einem spezifischen Mitglied der Struktur.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Löst die Operation aus, um einen Wert innerhalb der Struktur zu setzen. Wird mit den Daten `member`, `in_struct` und `element_value` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der `REQ`-Operation. Wird mit dem Datenausgang `out_struct` verknüpft.

### **Daten-Eingänge**
- **in_struct**: Die Eingangsstruktur, in der ein Wert gesetzt werden soll (Typ: `ANY`).
- **member**: Der Name des Strukturmitglieds, das geändert werden soll (Typ: `STRING`). Innere Mitglieder können über den Punktoperator (.) angesprochen werden.
- **element_value**: Der neue Wert, der dem angegebenen Mitglied zugewiesen werden soll (Typ: `ANY`).

### **Daten-Ausgänge**
- **out_struct**: Die modifizierte Struktur nach der Zuweisung des neuen Werts (Typ: `ANY`).

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock `SET_STRUCT_VALUE` empfängt über den Ereigniseingang `REQ` eine Anfrage, um einen bestimmten Wert innerhalb einer Struktur zu ändern. Dabei werden die Daten `in_struct`, `member` und `element_value` verwendet. Der Block sucht das angegebene Mitglied in der Struktur und weist ihm den neuen Wert zu. Nach erfolgreicher Operation wird das Ereignis `CNF` ausgelöst, und die modifizierte Struktur wird über `out_struct` ausgegeben.

## Technische Besonderheiten
- Unterstützt den Zugriff auf verschachtelte Strukturen über den Punktoperator (.).
- Kann mit beliebigen Datentypen (`ANY`) umgehen, solange die Struktur und der neue Wert kompatibel sind.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Verarbeitet die Anfrage und setzt den neuen Wert in der Struktur.
3. **Completed**: Löst das `CNF`-Ereignis aus und gibt die modifizierte Struktur aus.

## Anwendungsszenarien
- Ändern von Werten in komplexen Datenstrukturen.
- Dynamische Aktualisierung von Konfigurationsparametern in Echtzeitsystemen.
- Verwendung in Steuerungssystemen, wo Strukturdaten zur Laufzeit angepasst werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfachen Zuweisungsblöcken ermöglicht `SET_STRUCT_VALUE` den Zugriff auf verschachtelte Strukturen.
- Ähnliche Blöcke wie `GET_STRUCT_VALUE` bieten nur Lesezugriff, während dieser Block Schreibzugriff unterstützt.

## Fazit
Der `SET_STRUCT_VALUE`-Funktionsblock ist ein leistungsfähiges Werkzeug zur Manipulation von Strukturdaten in Echtzeitsystemen. Seine Fähigkeit, auf verschachtelte Mitglieder zuzugreifen und Werte dynamisch zu ändern, macht ihn besonders nützlich in komplexen Steuerungsanwendungen.
