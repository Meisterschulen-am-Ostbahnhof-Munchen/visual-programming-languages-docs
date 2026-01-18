# F_LINT_TO_UDINT

```{index} single: F_LINT_TO_UDINT
```

<img width="1448" height="214" alt="F_LINT_TO_UDINT" src="https://github.com/user-attachments/assets/9e88f669-c0d5-4acd-a01f-4274a376f3f3" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_LINT_TO_UDINT` dient zur Konvertierung eines 64-Bit vorzeichenbehafteten Integer-Werts (`LINT`) in einen 32-Bit vorzeichenlosen Integer-Wert (`UDINT`). Der Block ist Teil der `iec61131::conversion`-Bibliothek und eignet sich für Anwendungen, bei denen eine Typumwandlung erforderlich ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`LINT`): Der 64-Bit vorzeichenbehaftete Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`UDINT`): Der resultierende 32-Bit vorzeichenlose Integer-Wert nach der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des Ereignisses `REQ` wird der Algorithmus ausgeführt, der den Wert von `IN` von `LINT` in `UDINT` konvertiert und das Ergebnis an `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Der Block nutzt die eingebaute Funktion `LINT_TO_UDINT` für die Konvertierung.
- Es handelt sich um einen einfachen Funktionsblock ohne Zustandsautomaten oder komplexe Logik.

## Zustandsübersicht
Der Block hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung von `REQ`.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo 64-Bit-Werte in 32-Bit-Werte umgewandelt werden müssen.
- Verwendung in Datenverarbeitungsketten, wo unterschiedliche Datentypen kompatibel gemacht werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Blöcke wie `F_DINT_TO_UDINT` oder `F_INT_TO_UINT` bieten Konvertierungen zwischen anderen Integer-Typen, jedoch nicht für `LINT` zu `UDINT`.
- Im Gegensatz zu generischen Konvertierungsblöcken ist `F_LINT_TO_UDINT` spezialisiert und optimiert für diese spezifische Umwandlung.

## Fazit
Der `F_LINT_TO_UDINT`-Block ist ein effizientes Werkzeug für die Konvertierung von 64-Bit vorzeichenbehafteten zu 32-Bit vorzeichenlosen Integer-Werten. Seine Einfachheit und direkte Funktionsweise machen ihn zu einer zuverlässigen Komponente in Steuerungsanwendungen.