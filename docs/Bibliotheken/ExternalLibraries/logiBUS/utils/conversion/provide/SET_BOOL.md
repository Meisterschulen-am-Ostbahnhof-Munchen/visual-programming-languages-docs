# SET_BOOL


![SET_BOOL](./SET_BOOL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `SET_BOOL` dient dazu, einen booleschen Eingangswert (`IN`) auf eine InOut-Variable (`OUT`) zu schreiben. Er stellt eine einfache Zuweisungslogik für BOOL-Daten bereit und wird über ein Ereignis gesteuert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Normaler Ausführungsanstoß |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigung der Ausführung |

### **Daten-Eingänge**

| Name | Typ | Initialwert | Kommentar |
|------|-----|-------------|-----------|
| IN   | BOOL | FALSE       | Wert, der auf die Zielvariable geschrieben werden soll |

### **Daten-Ausgänge**

Keine separaten Datenausgänge. Der ausgegebene Wert wird über die InOut-Variable `OUT` bereitgestellt.

### **Adapter**

Keine.

## Funktionsweise

Wird das Ereignis `REQ` empfangen, führt der Baustein die Zuweisung `OUT := IN` aus. Dabei wird der aktuelle Wert des Eingangs `IN` auf die InOut-Variable `OUT` kopiert. Anschließend wird das Bestätigungsereignis `CNF` gesendet. Die InOut-Variable `OUT` kann von außen mit einer beliebigen BOOL-Variablen verbunden werden, sodass der Wert direkt an die entsprechende Stelle im System geschrieben wird.

## Technische Besonderheiten

- Der Baustein verwendet eine **InOut-Variable** (`OUT`), die sowohl als Ausgang als auch als Eingang fungiert. Dadurch kann der Wert direkt in eine externe Variable geschrieben werden, ohne einen separaten Datenausgang zu benötigen.
- Die Initialwerte von `IN` und `OUT` sind jeweils `FALSE`, was bei fehlender Initialisierung einen definierten Zustand sicherstellt.
- Es gibt nur einen Algorithmus und einen Zustand, daher ist die Ausführungslogik deterministisch und nebenläufigkeitsfrei.

## Zustandsübersicht

| Zustand | Aktion | Ereignisausgang | Beschreibung |
|---------|--------|----------------|--------------|
| REQ     | `OUT := IN` | CNF | Bei Ereignis REQ wird der Eingangswert auf die InOut-Variable geschrieben und die Ausführung bestätigt. |

Der Baustein besitzt nur einen aktiven Zustand. Nach der Ausführung verharrt er wartend auf das nächste `REQ`-Ereignis.

## Anwendungsszenarien

- **Setzen eines globalen Flags**: Über eine InOut-Variable kann ein boolesches Flag in einem anderen Baustein oder einer globalen Variable gesetzt werden.
- **Wertübernahme von einem Sensor**: Ein boolescher Sensorwert (z.B. Schalter) wird direkt in eine Steuervariable übernommen.
- **Initialisierung von BOOL-Variablen**: Bei Systemstart kann über `REQ` ein definierter Wert in eine Variable geschrieben werden.

## Vergleich mit ähnlichen Bausteinen

- **`MOVE` (z.B. ANY to ANY)**: `MOVE` kopiert Werte beliebiger Datentypen, benötigt aber getrennte Ein-/Ausgänge. `SET_BOOL` ist auf BOOL spezialisiert und nutzt eine InOut-Variable, was kompaktere Verbindungen ermöglicht.
- **`SET_BOOL` vs. direkte Zuweisung in ST**: Der Baustein abstrahiert die Zuweisung als ereignisgesteuerten Block und kann in grafischen Editoren (z.B. FBD) verwendet werden, wo eine direkte Zuweisung nicht möglich ist.
- **`R_TRIG` / `F_TRIG`**: Diese Bausteine detektieren Flanken und verändern den Ausgang nur bei Signalwechseln. `SET_BOOL` führt dagegen bei jedem `REQ` eine unbedingte Zuweisung durch.

## Fazit

`SET_BOOL` ist ein einfacher, aber praktischer Funktionsblock zur direkten Zuweisung eines booleschen Werts auf eine Variable mittels einer InOut-Schnittstelle. Er eignet sich hervorragend für Steuerungsaufgaben, bei denen ein boolescher Zustand gezielt gesetzt werden muss, und fügt sich nahtlos in das ereignisgesteuerte Paradigma der IEC 61499 ein.