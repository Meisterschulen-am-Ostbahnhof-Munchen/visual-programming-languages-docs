# GET_REAL


![GET_REAL](./GET_REAL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **GET_REAL** dient dazu, einen REAL-Wert aus einer **InOut-Variable** auszulesen und diesen in einem gepufferten Ausgang bereitzustellen. Der ausgelesene Wert wird beim Empfang eines Ereignisses am Eingang `REQ` aus der InOut-Variable `IN` gelesen und am Ausgang `OUT` ausgegeben. Nach der Ausführung wird das Bestätigungsereignis `CNF` gesendet.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Mit Variablen |
|----------|---------------|----------------|
| **REQ**  | Normale Ausführungsanforderung – löst das Lesen der InOut-Variable aus. | `IN` |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung | Mit Variablen |
|----------|---------------|----------------|
| **CNF**  | Bestätigung der Ausführung – wird nach der Bearbeitung von `REQ` gesendet. | `OUT`, `IN` |

### **Daten-Eingänge**

| Variable | Typ  | Initialwert | Beschreibung |
|----------|------|-------------|--------------|
| **IN**   | REAL | 0.0         | InOut-Variable, deren aktueller Wert gelesen wird. |

> **Hinweis:** `IN` ist als *InOut-Variable* deklariert – sie kann sowohl gelesen als auch geschrieben werden. In diesem FB wird sie jedoch nur gelesen.

### **Daten-Ausgänge**

| Variable | Typ  | Initialwert | Beschreibung |
|----------|------|-------------|--------------|
| **OUT**  | REAL | 0.0         | Gepufferter Ausgang – hält den gelesenen Wert von `IN` bis zur nächsten Aktualisierung. |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. Ein eingehendes Ereignis am Eingang `REQ` triggert die Ausführung des internen Algorithmus `REQ`.
2. Im Algorithmus wird der aktuelle Wert der InOut-Variable `IN` in die Ausgangsvariable `OUT` kopiert:
   ```structuredtext
   OUT := IN;
   ```
3. Anschließend wird das Bestätigungsereignis `CNF` gesendet. Die Ausgänge `OUT` und `IN` werden mit dem Ereignis assoziiert, sodass sie gleichzeitig gültig sind.
4. Der Ausgangswert bleibt solange erhalten, bis ein weiteres `REQ`-Ereignis eintrifft und `OUT` neu geschrieben wird.

## Technische Besonderheiten
- **InOut-Verwendung:** Der Baustein nutzt eine InOut-Variable (`IN`). Diese kann von außen beschrieben oder gelesen werden; hier dient sie ausschließlich als Quelle.
- **Initialisierung:** Beide REAL-Variablen sind mit `0.0` vorbelegt.
- **Minimaler Overhead:** Der FB hat nur einen Zustand (`REQ`) und einen einfachen Zuweisungsalgorithmus – er arbeitet ohne Verzögerung oder zusätzliche Logik.
- **Standardkonformität:** Der Baustein ist gemäß IEC 61499-1 definiert und für die Verwendung in Automatisierungsumgebungen wie 4diac IDE vorgesehen.

## Zustandsübersicht
Der FB besitzt nur einen einzigen Zustand:
- **Zustand `REQ`:**  
  Beim Eintritt wird der Algorithmus `REQ` ausgeführt (OUT := IN) und das Ereignis `CNF` gesendet. Der FB verbleibt in diesem Zustand und ist stets bereit für die nächste Anforderung.

Es gibt keine weiteren Zustände oder Verzweigungen – der FB ist deterministisch und reagiert unmittelbar auf jedes `REQ`-Ereignis.

## Anwendungsszenarien
- **Lesen eines Prozesswertes:** In einer SPS-Steuerung kann `GET_REAL` verwendet werden, um einen aktuellen Sensorwert, der als InOut-Variable vorliegt, auszulesen und an einen nachfolgenden Funktionsblock weiterzugeben (z. B. für Berechnungen oder Visualisierung).  
- **Werteabgleich zwischen Bausteinen:** Wenn ein anderer FB eine InOut-Schnittstelle mit einem REAL-Wert bereitstellt, kann `GET_REAL` diesen Wert abrufen und als gepufferten Ausgang verfügbar machen.  
- **Test und Simulation:** Der Baustein eignet sich zum Debuggen, um den aktuellen Wert einer Variablen zu einem bestimmten Zeitpunkt festzuhalten und zu protokollieren.

## Vergleich mit ähnlichen Bausteinen
Ähnliche Bausteine existieren für andere Datentypen, z. B. `GET_BOOL`, `GET_INT`, `GET_LREAL` etc. Sie alle teilen das gleiche Prinzip: Lesen einer InOut-Variable und Bereitstellen als gepufferten Ausgang. Der Unterschied liegt ausschließlich im Datentyp und der damit verbundenen Genauigkeit bzw. Wertebereich.

| Baustein   | Datentyp | Einsatzbereich |
|------------|----------|----------------|
| GET_BOOL   | BOOL     | Binäre Signale |
| GET_INT    | INT      | Ganzzahlen (16 Bit) |
| GET_REAL   | REAL     | Gleitkommazahlen (32 Bit) |
| GET_LREAL  | LREAL    | Präzise Gleitkommazahlen (64 Bit) |

Alle diese Bausteine lassen sich analog verwenden und bieten eine einheitliche Schnittstelle für den Zugriff auf InOut-Variablen.

## Fazit
Der `GET_REAL`-Funktionsblock ist ein schlanker und zuverlässiger Baustein zum Lesen einer REAL-InOut-Variable. Er erfüllt eine grundlegende Aufgabe in der IEC‑61499‑Welt: das Weiterleiten eines Wertes aus einer bidirektionalen Schnittstelle in einen gepufferten Ausgang. Durch seine Einfachheit und klare Semantik eignet er sich sowohl für den Produktiveinsatz als auch für Testzwecke. Die Kombination mit den parallelen Bausteinen anderer Datentypen macht ihn zu einem flexiblen Werkzeug in der Automatisierungstechnik.