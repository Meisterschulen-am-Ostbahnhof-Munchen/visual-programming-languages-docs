# SET_INT


![SET_INT](./SET_INT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **SET_INT** dient dazu, einen Wert vom Datentyp `INT` aus einem Eingang direkt in eine InOut-Variable zu schreiben. Der Baustein ist ein einfacher, ereignisgesteuerter FB und wird typischerweise verwendet, um globale Parameter oder Variablen anderer FBs durch einen definierten Ereignisimpuls zu setzen. Die Funktionalität ist auf die minimale Aufgabe der Wertzuweisung reduziert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Datentyp | Beschreibung | Mit Daten |
|----------|----------|---------------|-----------|
| `REQ`    | Event    | Normaler Ausführungsanforderung. Löst das Übernehmen des Wertes von `IN` nach `OUT` aus. | `IN`, `OUT` |

### **Ereignis-Ausgänge**

| Ereignis | Datentyp | Beschreibung | Mit Daten |
|----------|----------|---------------|-----------|
| `CNF`    | Event    | Ausführungsbestätigung. Wird gesendet, nachdem der Wert erfolgreich in `OUT` geschrieben wurde. | `OUT` |

### **Daten-Eingänge**

| Variable | Datentyp | Beschreibung | Initialwert |
|----------|----------|---------------|-------------|
| `IN`     | INT      | Der Wert, der in die InOut-Variable kopiert werden soll. | 0 |

### **Daten-Ausgänge**
Der FB besitzt keinen reinen Datenausgang. Die Ausgabe erfolgt über die InOut-Variable (siehe unten).

### **Adapter**
Keine.

### **InOut-Variable**

| Variable | Datentyp | Beschreibung | Initialwert |
|----------|----------|---------------|-------------|
| `OUT`    | INT      | Zielvariable, in die der Wert von `IN` geschrieben wird. Diese Variable ist als InOut deklariert, d. h. sie wird von außerhalb des Bausteins referenziert und kann direkt manipuliert werden. | 0 |

## Funktionsweise
Der Baustein arbeitet nach einem sehr einfachen, direkten Prinzip:

1. Ein Ereignis am Eingang `REQ` wird empfangen.
2. Der Algorithmus `REQ` führt die Zuweisung `OUT := IN` aus. Der aktuelle Wert des Daten-Eingangs `IN` wird also in die InOut-Variable `OUT` kopiert.
3. Nach erfolgreicher Zuweisung wird das Ereignis `CNF` gesendet, um der aufrufenden Umgebung die Fertigstellung zu signalisieren. Das `CNF`-Ereignis ist mit der InOut-Variable `OUT` verknüpft, sodass die Datenkonsistenz gewahrt bleibt.

Die Ausführung erfolgt ohne Verzögerung oder Bedingungen – bei jedem `REQ` wird der Wert sofort überschrieben.

## Technische Besonderheiten
- **InOut-Variable**  
  Der Baustein nutzt einen InOut-Parameter (`OUT`), der eine direkte Referenz auf eine externe Variable (z. B. einen globalen Datenbaustein oder eine Variable eines übergeordneten Funktionsblocks) darstellt. Dadurch entfällt die Notwendigkeit einer expliziten Rückverbindung des Ausgangs zu einem anderen Baustein. Der FB schreibt seinen Wert direkt an die referenzierte Speicherstelle.
- **Keine Pufferung**  
  Der FB führt keine Zwischenspeicherung durch. Der Wert wird bei jedem `REQ-Ereignis` unmittelbar überschrieben.
- **Initialwerte**  
  Die Daten-Eingänge und InOut-Variablen sind mit `0` initialisiert. Im Falle einer fehlenden Verbindung wird dieser Wert verwendet.

## Zustandsübersicht
Der FB besitzt einen einzigen ECC-Zustand (`REQ`), der die Aktion ausführt und sofort das Ausgangsereignis `CNF` aktiviert. Es gibt keine Verzweigungen, Timer oder Fehlerzustände.

| Zustand | Aktion | Auslöser |
|---------|--------|----------|
| `REQ`   | Ausführung des Algorithmus `REQ` (OUT := IN) und Senden von `CNF` | Ereignis `REQ` |

## Anwendungsszenarien
- **Setzen eines Konstantenwerts**  
  Ein externer Sensor oder eine Logik liefert einen Sollwert (`IN`), der bei einem Takt (`REQ`) in eine globale Sollwertvariable (`OUT`) übernommen wird.
- **Initialisierung von Variablen**  
  Beim Start einer Anwendung kann `SET_INT` verwendet werden, um mehrere InOut-Variablen auf definierte Startwerte zu setzen.
- **Parameter-Override**  
  Ein übergeordneter Regler oder eine Bedienschnittstelle überschreibt bei einem speziellen Ereignis den aktuellen Wert eines anderen Bausteins, ohne den Baustein selbst ändern zu müssen (die InOut-Verbindung erlaubt den direkten Zugriff).

## Vergleich mit ähnlichen Bausteinen
- **SET_BOOL / SET_REAL**  
  Analog zu `SET_INT`, jedoch für die Datentypen `BOOL` bzw. `REAL`. Die Funktionsweise ist identisch.
- **MOVE**  
  Ein allgemeiner MOVE-Baustein kopiert einen Wert von einem Daten-Eingang zu einem Daten-Ausgang. Im Unterschied dazu arbeitet `SET_INT` mit einer InOut-Variablen und schreibt direkt an eine externe Stelle, was die Kopplung enger macht. `MOVE` benötigt eine separate Verbindung vom Ausgang zum Ziel.
- **LATCH**  
  Ein Latch-FB kann einen Wert speichern und bei Bedarf ausgeben. `SET_INT` überschreibt dagegen ohne Haltefunktion – jeder Aufruf überschreibt den vorherigen Wert.

## Fazit
Der `SET_INT`-Funktionsblock ist ein minimalistischer, aber effektiver Baustein zum direkten Setzen einer INT-Variable über eine InOut-Schnittstelle. Seine Stärke liegt in der einfachen Logik und der Fähigkeit, von außen auf fremde Variablen zuzugreifen. Er eignet sich besonders für flache Steuerungsstrukturen, bei denen schnelle und direkte Wertzuweisungen benötigt werden. Aufgrund seiner Einfachheit ist er robust und fehlerarm einsetzbar, erfordert jedoch ein durchdachtes Variablenkonzept, um unerwünschte Seiteneffekte zu vermeiden.