# SET_WSTRING


![SET_WSTRING](./SET_WSTRING.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **SET_WSTRING** dient dazu, einen Wert vom Datentyp `WSTRING` an einen InOut-Parameter zu übertragen. Er wird typischerweise eingesetzt, um einen berechneten oder extern vorgegebenen Zeichenkettenwert in eine übergeordnete Variable (z. B. einer anderen Instanz oder eines übergeordneten Bausteins) zu schreiben.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Beschreibung |
|----------|--------------|
| `REQ`    | Normaler Ausführungsauftruf: Die Zuweisung des Eingabewerts an die InOut-Variable wird ausgelöst. |

### **Ereignis-Ausgänge**
| Ereignis | Beschreibung |
|----------|--------------|
| `CNF`    | Bestätigung der Ausführung. Wird nach erfolgreicher Zuweisung gesendet. |

### **Daten-Eingänge**
| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| `IN`  | `WSTRING`| Quellwert, der in die Zielvariable geschrieben werden soll. |

### **Daten-Ausgänge**
Der Baustein besitzt keine klassischen Datenausgänge. Die Weitergabe des Werts erfolgt über die **InOut-Variable** `OUT`.

### **Adapter**
Keine.

## Funktionsweise
Wird der Ereigniseingang `REQ` aktiviert, führt der Baustein die folgende Zuweisung aus:
```
OUT := IN;
```
Der am Eingang `IN` anliegende `WSTRING`-Wert wird unverändert in die InOut-Variable `OUT` kopiert. Anschließend wird das Ereignis `CNF` gesendet, um dem aufrufenden Baustein die Beendigung der Operation zu signalisieren.

## Technische Besonderheiten
- **InOut‑Variable**: `OUT` ist als InOut-Parameter deklariert. Dies bedeutet, dass die Variable sowohl gelesen als auch beschrieben werden kann und ihre Lebensdauer außerhalb des Bausteins liegt. Der Baustein überschreibt den aktuellen Inhalt von `OUT` mit dem Wert von `IN`.
- **Datentyp `WSTRING`**: Es handelt sich um einen Zeichenketten-Typ, der Breitzeichen (Unicode) unterstützt. Der Baustein führt keine Längenprüfung oder Konvertierung durch – die Zuweisung erfolgt direkt.
- **Einfachster Zustandsautomat**: Der Zustandsautomat besteht aus einem einzigen Zustand (`REQ`), der die gesamte Funktionalität abdeckt. Es gibt keine Verzweigungen oder Zeitverzögerungen.

## Zustandsübersicht
Der Baustein enthält genau einen Zustand:

| Zustand | Beschreibung |
|---------|--------------|
| `REQ`   | Wird nach dem Eintreffen des Ereignisses `REQ` aktiv. Führt die Zuweisung `OUT := IN` aus und sendet `CNF`. Danach kehrt der Baustein in den initialen Zustand zurück. |

## Anwendungsszenarien
- **Übergabe eines formatierten Strings**: Angenommen, ein Baustein erzeugt eine Fehlermeldung als `WSTRING` und möchte diese in eine übergeordnete Variable schreiben. `SET_WSTRING` übernimmt diese Zuweisung auf einen Trigger hin.
- **Parametrierung**: In einer Steuerung kann ein externer Parameter (z. B. eine Produktbezeichnung) über `SET_WSTRING` in einen globalen Datenbaustein kopiert werden.
- **Debugging**: Temporäres Setzen einer WSTRING-Variablen durch eine Test- oder Initialisierungslogik.

## Vergleich mit ähnlichen Bausteinen
- **SET_BOOL**: Arbeitet analog, jedoch mit dem Datentyp `BOOL`. Beide nutzen ein InOut, um Werte in externe Variablen zu schreiben.
- **MOVE (IEC‑Baustein)**: Der Standard-MOVE-Baustein kopiert Daten von einem Eingang auf einen Ausgang. Im Unterschied dazu verwendet `SET_WSTRING` einen InOut-Parameter, was die Anbindung an bestehende Variablen ohne zusätzlichen Ausgangsport erlaubt.
- **WRITE_STRING**: Manche Bibliotheken bieten spezielle Write‑Bausteine mit Längenkontrolle. `SET_WSTRING` ist bewusst einfach gehalten und verzichtet auf Prüfungen.

## Fazit
Der Baustein **SET_WSTRING** ist eine minimalistische, aber effektive Lösung zum Beschreiben einer WSTRING‑InOut-Variablen. Seine einfache Zustandsmaschine und die klare Schnittstelle machen ihn leicht verständlich und einsetzbar, wo eine triviale Zuweisung auf ein Ereignis hin benötigt wird. Für Aufgaben mit zusätzlichen Funktionen (Konvertierung, Längenbeschränkung) sind spezialisierte Bausteine vorzuziehen.