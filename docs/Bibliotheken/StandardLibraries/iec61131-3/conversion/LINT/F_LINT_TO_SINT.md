# F_LINT_TO_SINT

```{index} single: F_LINT_TO_SINT
```

<img width="1438" height="214" alt="F_LINT_TO_SINT" src="https://github.com/user-attachments/assets/a76f6188-5a80-4252-a7d7-56944d50fde0" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LINT_TO_SINT` dient der Konvertierung eines 64-Bit-Ganzzahlwerts (`LINT`) in einen 8-Bit-Ganzzahlwert (`SINT`). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen mit unterschiedlicher Wortbreite ausgetauscht oder verarbeitet werden müssen.

![F_LINT_TO_SINT](F_LINT_TO_SINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN** (`LINT`): Der 64-Bit-Ganzzahlwert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`SINT`): Der resultierende 8-Bit-Ganzzahlwert nach der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des Ereignisses `REQ` wird der Algorithmus ausgeführt, der den Wert von `IN` vom Typ `LINT` in einen `SINT`-Wert konvertiert und das Ergebnis an `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um den Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung kann zu einem Datenverlust führen, wenn der ursprüngliche `LINT`-Wert außerhalb des darstellbaren Bereichs eines `SINT` (-128 bis 127) liegt.
- Der Funktionsblock ist einfach und deterministisch, ohne interne Zustände oder komplexe Logik.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt ausschließlich als Reaktion auf das `REQ`-Ereignis.

## Anwendungsszenarien
- Datenreduktion bei der Übertragung zwischen Systemen mit unterschiedlicher Wortbreite.
- Verarbeitung von Sensordaten, bei denen nur die unteren 8 Bit relevant sind.
- Kompatibilität mit älteren Systemen, die nur 8-Bit-Daten verarbeiten können.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_LINT_TO_SINT` spezialisiert und optimiert für die Konvertierung von `LINT` zu `SINT`.
- Andere Konvertierungsblöcke könnten zusätzliche Funktionen wie Überlaufbehandlung oder Skalierung bieten, was hier nicht der Fall ist.

## Fazit
Der `F_LINT_TO_SINT`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von 64-Bit- zu 8-Bit-Ganzzahlen. Seine Einfachheit macht ihn robust und leicht verständlich, allerdings ohne erweiterte Features wie Überlaufkontrolle. Ideal für Anwendungen, bei denen eine direkte und schnelle Konvertierung benötigt wird.