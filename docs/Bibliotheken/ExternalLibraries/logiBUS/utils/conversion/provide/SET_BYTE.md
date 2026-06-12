# SET_BYTE


![SET_BYTE](./SET_BYTE.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **SET_BYTE** dient dem einfachen Überschreiben einer BYTE-Variablen. Er liest den Wert des Dateneingangs `IN` und schreibt ihn in die InOut-Variable `OUT`, sobald ein Ereignis am Eingang `REQ` eintrifft. Anschließend wird das Ereignis `CNF` ausgegeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `REQ` | Event | Normaler Ausführungsauftrag (Schreibvorgang starten) |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `CNF` | Event | Bestätigung der erfolgten Zuweisung |

### **Daten-Eingänge**
| Name | Typ | Wertebereich | Initialwert | Kommentar |
|------|-----|--------------|-------------|-----------|
| `IN` | BYTE | 0…255 | 0 | Wert, der auf die Zielvariable geschrieben werden soll |

### **Daten-Ausgänge**
Der FB verwendet eine **InOut**-Variable. Daher gibt es keine separaten Datenausgänge – der ausgegebene Wert ist identisch mit dem Wert der InOut-Variablen `OUT`.

### **Adapter**
_Keine vorhanden._

## Funktionsweise
Bei einem Ereignis am Eingang `REQ` wird der Algorithmus `REQ` ausgeführt. Dieser weist dem InOut-Variable `OUT` den Wert von `IN` zu:
```
OUT := IN;
```
Unmittelbar nach der Zuweisung wird das Ereignis `CNF` gesendet. Die InOut-Variable kann sowohl gelesen als auch von außerhalb des Bausteins (z. B. über eine Verbindung im Applikationsmodell) beschrieben werden – nach dem Schreibvorgang besitzt sie den Wert von `IN`.

## Technische Besonderheiten
- **Einfachste Zuweisung**: Der Algorithmus besteht aus nur einer Zeile – keine Verzögerungen, keine Bedingungen oder Filter.
- **InOut-Variable**: `OUT` ist als InOut deklariert, d. h. sie kann von außen mit einer Variablen verbunden werden, die sowohl gelesen als auch beschrieben wird. Dies ermöglicht eine direkte Manipulation einer globalen oder verbundenen BYTE-Variablen.
- **Kein Zustandsautomat**: Der FB besitzt nur einen impliziten Zustand (`REQ`) und benötigt keine weiteren Zustandslogiken.

## Zustandsübersicht
Der FB hat keine expliziten Zustände. Der Eintritt in die Aktion erfolgt sofort beim Ereignis `REQ`. Es gibt weder Fehlerzustände noch Verzögerungszustände.

## Anwendungsszenarien
- **Initialisierung oder Rücksetzen**: Ein bestimmter Startwert soll in eine bestehende BYTE-Variable geschrieben werden.
- **Umschaltung/Bitmuster setzen**: Ein externes Signal (z. B. von einem Kommunikationsbaustein) wird über `IN` an einen Ausgang oder an eine Speicherstelle weitergegeben.
- **Test / Diagnose**: Temporäres Überschreiben eines Wertes in einer Steuerungsapplikation.

## Vergleich mit ähnlichen Bausteinen
- **MOVE** (allgemeiner): Der einfache MOVE-Baustein für beliebige Datentypen arbeitet meist mit Eingang und Ausgang, nicht mit InOut. `SET_BYTE` ist speziell für BYTE optimiert und verwendet InOut, sodass der Wert direkt in die Zielvariable geschrieben wird (kein separater Ausgang nötig).
- **SET_BOOL** (bei Vorhandensein): Analog für BOOL – beide Bausteine folgen dem gleichen einfachen Prinzip, beschränken sich aber auf ihren jeweiligen Datentyp.

## Fazit
`SET_BYTE` ist ein minimalistischer, klar definierter Funktionsblock zum einmaligen Beschreiben einer BYTE-Variablen. Seine Stärke liegt in der Einfachheit und der Verwendung einer InOut-Schnittstelle, die eine direkte Wertzuweisung ohne zusätzliche Verdrahtung eines Datenausgangs ermöglicht. Er eignet sich besonders für Anwendungen, in denen ein vorgegebener Wert zu einem bestimmten Zeitpunkt in eine persistente Variable geschrieben werden muss.