# SET_SINT


![SET_SINT](./SET_SINT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **SET_SINT** dient dazu, einen SINT-Wert von seinem Dateneingang **IN** in eine InOut-Variable **OUT** zu schreiben. Er wird verwendet, um einen SINT-Wert an einem bestimmten Punkt der Ablaufsteuerung gezielt zu setzen. Der Baustein realisiert eine einfache, ereignisgesteuerte Zuweisung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **REQ**  | Normale Ausführungsanforderung. Löst die Zuweisung von **IN** nach **OUT** aus. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **CNF**  | Bestätigung der Ausführung. Wird nach erfolgreicher Zuweisung gesendet. |

### **Daten-Eingänge**

| Name | Typ  | Initialwert | Beschreibung |
|------|------|-------------|--------------|
| **IN** | SINT | 0           | Der Wert, der geschrieben werden soll. |

### **Daten-Ausgänge**
Der Funktionsblock besitzt keine separaten Datenausgänge. Der Zielwert wird über die InOut-Variable **OUT** zurückgegeben.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Ein **REQ**-Ereignis startet die Ausführung des Algorithmus. Im Algorithmus wird der aktuelle Wert von **IN** direkt der InOut-Variable **OUT** zugewiesen:
```
OUT := IN;
```
Nach Abschluss der Zuweisung wird das Ereignis **CNF** ausgegeben. Die InOut-Variable **OUT** dient gleichzeitig als Eingabe und Ausgabe – ihr Wert wird überschrieben und steht danach für nachfolgende Bausteine zur Verfügung.

## Technische Besonderheiten
- **InOut-Variable**: Die Variable **OUT** ist als `InOut` deklariert. Sie kann sowohl gelesen als auch geschrieben werden. Der Baustein überschreibt den bisherigen Wert von **OUT** mit dem Wert von **IN**.
- **Einfachster Algorithmus**: Der Baustein führt nur eine einzige Zuweisung durch. Es gibt keine Bedingungen, Schleifen oder zusätzliche Logik.
- **Typsicherheit**: Sowohl **IN** als auch **OUT** sind vom Typ `SINT`, sodass eine direkte, typkonforme Zuweisung erfolgt.

## Zustandsübersicht
Der Funktionsblock besitzt einen einzigen Zustand (ECState) mit dem Namen **REQ**:

| Zustand | Aktion | Ausgabeereignis |
|---------|--------|-----------------|
| REQ     | `OUT := IN` | CNF |

Es gibt nur diesen einen Zustand; nach Ausführung kehrt der Baustein in den initialen Zustand zurück. Eine explizite Zustandsmaschine mit mehreren Zuständen liegt nicht vor.

## Anwendungsszenarien
- **Setzen eines SINT-Wertes zur Laufzeit**: Beispielsweise das Überschreiben eines Grenzwerts oder eines Zählers in einer Steuerung.
- **Initialisieren von SINT-Variablen** in einem bestimmten Schritt der Ablaufsteuerung.
- **Weitergabe eines konstanten oder berechneten Wertes** an einen anderen Baustein über die InOut-Variable, sofern eine Verbindung zu einer globalen Variablen oder einem anderen InOut-Port besteht.

## Vergleich mit ähnlichen Bausteinen
- **SET_BOOL**: Analoge Funktion für den Datentyp `BOOL`. Arbeitet identisch, jedoch mit booleschen Werten.
- **SET_INT**: Entsprechender Baustein für `INT`. Die Struktur (Ereignis REQ/CNF, Zuweisung) ist identisch.
- **MOVE (z. B. MOVE_SINT)**: Ein MOVE-Baustein kopiert einen Wert von einem Eingang zu einem Ausgang, ohne dass die Zielvariable als InOut ausgeführt ist. **SET_SINT** hingegen schreibt direkt in eine bestehende Variable, was in manchen Architekturen den Vorteil bietet, dass die Variable auch von anderen Bausteinen gelesen werden kann, ohne eine separate Verbindung zu einem Ausgang zu benötigen.

## Fazit
**SET_SINT** ist ein minimaler und zuverlässiger Funktionsblock zum Setzen einer SINT-Variablen auf einen gewünschten Wert. Seine Einfachheit macht ihn ideal für Situationen, in denen ein Wert direkt und ohne zusätzliche Logik überschrieben werden soll. Der Einsatz einer InOut-Variable spart separate Ausgangsvariablen und erlaubt eine direkte Verkettung mit anderen Bausteinen, die dieselbe Variable lesen. Für einfache Wertzuweisungen ist er eine effiziente Lösung.