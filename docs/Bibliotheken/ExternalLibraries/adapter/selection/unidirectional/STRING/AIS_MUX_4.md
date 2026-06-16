# AIS_MUX_4


![AIS_MUX_4](./AIS_MUX_4.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **AIS_MUX_4** ist ein generischer AIS-Multiplexer mit vier Eingängen. Er wählt anhand eines Indexwerts `K` (0–3) einen der vier AIS-Adapter-Eingänge (`IN1`–`IN4`) aus und leitet dessen Daten über den Adapter-Ausgang `OUT` weiter. Der Baustein wird über das Ereignis `REQ` gesteuert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar                     |
|------|-------|-------------------------------|
| REQ  | Event | Setzt den Index `K` und aktiviert die Auswahl |

### **Ereignis-Ausgänge**

| Name | Typ   | Kommentar                                           |
|------|-------|-----------------------------------------------------|
| CNF  | Event | Bestätigung der Index-Auswahl (nach erfolgter Umschaltung) |

### **Daten-Eingänge**

| Name | Typ  | Kommentar                    |
|------|------|------------------------------|
| K    | UINT | Index (0 = IN1, 1 = IN2, …) |

### **Daten-Ausgänge**
_Keine. Die Ausgabedaten werden über den Adapter–Plug `OUT` bereitgestellt._

### **Adapter**

| Name    | Verwendung | Typ                                 | Kommentar                                                   |
|---------|------------|--------------------------------------|-------------------------------------------------------------|
| IN1     | Socket     | adapter::types::unidirectional::AIS | Erster AIS-Eingang (für K = 0)                              |
| IN2     | Socket     | adapter::types::unidirectional::AIS | Zweiter AIS-Eingang (für K = 1)                             |
| IN3     | Socket     | adapter::types::unidirectional::AIS | Dritter AIS-Eingang (für K = 2)                             |
| IN4     | Socket     | adapter::types::unidirectional::AIS | Vierter AIS-Eingang (für K = 3)                             |
| OUT     | Plug       | adapter::types::unidirectional::AIS | Ausgang: liefert die Daten des durch `K` gewählten Eingangs |

## Funktionsweise
1. Ein eingehendes Ereignis `REQ` liest den aktuellen Wert des Daten-Eingangs `K` ein.
2. Abhängig von `K` (0–3) wird der entsprechende AIS-Eingang (`IN1` für K=0, `IN2` für K=1, `IN3` für K=2, `IN4` für K=3) auf den Adapter-Ausgang `OUT` durchgeschaltet.
3. Nach erfolgreicher Auswahl wird das Ereignis `CNF` gesendet.
4. Für Werte außerhalb des Bereichs 0..3 ist das Verhalten undefiniert (der Baustein verlässt sich auf gültige Eingaben).

## Technische Besonderheiten
- **Generischer Typ**: Der Baustein ist als generischer FB deklariert (`GenericClassName = 'GEN_AIS_MUX'`) und kann in verschiedenen Typinstanzen parametrisiert werden.
- **Lizenz**: Eclipse Public License 2.0 (EPL-2.0).
- **Paketstruktur**: Der Baustein ist im Paket `adapter::selection::unidirectional` organisiert.
- **AIS-Adapter**: Alle beteiligten Ein- und Ausgänge verwenden denselben Adapter-Typ `adapter::types::unidirectional::AIS`, was eine einheitliche Datenstruktur sicherstellt.

## Zustandsübersicht
Der Baustein besitzt keine explizite Zustandsmaschine. Das Verhalten ist rein funktional:
- **Ruhezustand**: Es wird kein Ereignis bearbeitet; der Ausgang `OUT` behält den zuletzt gesetzten Wert.
- **Auswahlausführung**: Nach Empfang von `REQ` wird der neue Index übernommen und `OUT` aktualisiert; anschließend wird `CNF` ausgegeben.

## Anwendungsszenarien
- **Datenpfad-Umschaltung**: Auswahl einer von mehreren AIS-Datenquellen in Steuerungssystemen der Landtechnik oder Automatisierung.
- **Redundanz**: Bei mehreren parallelen AIS-Sensoren kann je nach Bedingung eine bestimmte Quelle aktiv geschaltet werden.
- **Test- und Diagnose**: Umschalten zwischen verschiedenen Messstellen zu Analysezwecken.

## Vergleich mit ähnlichen Bausteinen
Im 4diac-Framework existieren generische Multiplexer (z. B. `MUX_2`, `MUX_8`). Der **AIS_MUX_4** ist speziell für den AIS-Adapter-Typ ausgelegt und optimiert für unidirektionale AIS-Daten. Im Gegensatz zu universellen Multiplexern mit einfachen Datentypen (z. B. `INT`, `BOOL`) arbeitet er auf Adapterebene und überträgt komplexe Datenstrukturen in einem Schritt.

## Fazit
Der `AIS_MUX_4` ist ein einfacher, aber effektiver Baustein zur Auswahl eines von vier AIS-Eingängen. Seine generische Auslegung und die klare Ereignissteuerung machen ihn gut geeignet für modulare Automatisierungslösungen mit AIS-Kommunikation.