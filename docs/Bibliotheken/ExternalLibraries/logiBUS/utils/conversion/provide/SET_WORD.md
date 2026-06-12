# SET_WORD


![SET_WORD](./SET_WORD.svg)

* * * * * * * * * *

## Einleitung

Der SET_WORD Funktionsbaustein schreibt einen WORD-Wert von seinem Dateneingang IN in eine InOut-Variable OUT. Er wird verwendet, um einen Ausgang oder eine global zugängliche WORD-Variable mit einem bestimmten Wert zu überschreiben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Event): Normaler Ausführungsauftrag. Der Baustein wird ausgelöst, wenn ein Ereignis an diesem Eingang eintrifft.  
  Mit den Variablen `IN` und `OUT` verbunden.

### **Ereignis-Ausgänge**
- **CNF** (Event): Bestätigung der Ausführung. Wird nach erfolgreicher Zuweisung gesendet.  
  Mit der Variable `OUT` verbunden.

### **Daten-Eingänge**
- **IN** (WORD): Der Wert, der in die Zielvariable geschrieben werden soll. Initialwert: `0`.

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden. Die Ausgabe erfolgt ausschließlich über die InOut-Variable `OUT`.

### **Adapter**
Keine.

## Funktionsweise

Bei einem Ereignis am Eingang **REQ** wird der Algorithmus ausgeführt:  
`OUT := IN;`  
Anschließend wird ein Bestätigungsereignis am Ausgang **CNF** gesendet. Der Baustein überschreibt den aktuellen Wert von `OUT` mit dem Wert von `IN`.

## Technische Besonderheiten

- `OUT` ist als **InOut-Variable** deklariert. Sie dient gleichzeitig als Eingabe (lesend) und Ausgabe (schreibend). Der vorherige Wert von `OUT` wird durch die Zuweisung überschrieben.
- Es gibt keine eigenen Datenausgänge – die Änderung wirkt direkt auf die verbundene Variable.
- Der Baustein ist typspezifisch auf `WORD` ausgelegt. Für andere Datentypen stehen entsprechende Varianten zur Verfügung.

## Zustandsübersicht

Der Baustein besitzt einen aktiven Zustand:

- **REQ**: Beim Eintritt in diesen Zustand wird die Zuweisung `OUT := IN` ausgeführt und das Ereignis **CNF** ausgelöst.

Es gibt keine weiteren Zustände oder Verzweigungen.

## Anwendungsszenarien

- Setzen eines WORD-Ausgangs auf einen berechneten oder festen Wert.
- Überschreiben einer globalen WORD-Variablen in einer SPS-Steuerung.
- Einmalige Initialisierung einer WORD-Variablen durch einen externen Baustein.

## Vergleich mit ähnlichen Bausteinen

- **MOVE**: Kopiert einen Wert von einem Eingang zu einem Ausgang (separate Ein-/Ausgänge). SET_WORD verwendet stattdessen eine InOut-Variable.
- **SET_BOOL**: Analoge Funktionalität für den Datentyp BOOL.
- **F_MOVE**: Funktionsbaustein zur allgemeinen Datenübergabe, oft mit mehreren Eingängen/Ausgängen. SET_WORD ist spezifischer und direkter.

## Fazit

SET_WORD ist ein einfacher und effizienter Baustein, um einen WORD-Wert direkt in eine InOut-Variable zu schreiben. Durch die Verwendung eines InOut-Parameters reduziert er die Anzahl der benötigten Variablen und ist besonders in Szenarien nützlich, in denen ein Wert überschrieben werden muss, ohne einen separaten Ausgang zu nutzen.